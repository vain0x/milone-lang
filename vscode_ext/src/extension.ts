// Entrypoint of extension.

import { homedir } from "os"
import cp, { ChildProcess } from "child_process"
import path from "path"
import { ExtensionContext, workspace } from "vscode"
import { Disposable, LanguageClient, LanguageClientOptions, ServerOptions, State } from "vscode-languageclient/node"
import { startLspSessionDev } from "./lsp_session_dev"

const DEV = process.env["MILONE_LSP_SERVER_DEV"] === "1"
const MILONE_LSP_COMMAND = process.env["MILONE_LSP_COMMAND"] ?? ""
const MILONE_LSP_SERVER_LOG_LEVEL = process.env["MILONE_LSP_SERVER_LOG_LEVEL"]
const MILONE_HOME = process.env["MILONE_HOME"]

type Logger = {
  info: (...args: unknown[]) => void
}

const getMiloneHome = (logger: Logger): string => {
  const config = workspace.getConfiguration("milone-lang")

  const home = config.get<string>("home")
  if (home) {
    return home
  }
  logger.info("Config 'milone-lang.home' is unset or empty.")

  if (MILONE_HOME) {
    return MILONE_HOME
  }
  logger.info("Environment variable 'MILONE_HOME' is unset or empty.")

  return path.join(homedir(), ".local/share/milone")
}

const getLspCommand = (miloneHome: string, logger: Logger): string | undefined => {
  const config = workspace.getConfiguration("milone-lang")

  const enabled = config.get<boolean>("lsp-enabled", true)
  if (!enabled) {
    logger.info("Config 'milone-lang.lsp-enabled' is false. LSP server won't start.")
    return undefined
  }

  const command = config.get("lsp-command") as string | undefined
  if (command) {
    return command
  }
  logger.info("Config 'milone-lang.lsp-command' is unset or empty.")

  if (MILONE_LSP_COMMAND) {
    return MILONE_LSP_COMMAND
  }
  logger.info("Environment variable 'MILONE_LSP_COMMAND' is unset or empty.")

  return path.join(miloneHome, "bin/milone_lsp/MiloneLspServer")
}

const newLanguageClient = (lspCommand: string, miloneHome: string, dotnetCommand: string | undefined, logger: Logger): LanguageClient => {
  let server: ChildProcess | undefined
  let clientDisposable: Disposable | undefined

  const serverOptions: ServerOptions = async (): Promise<ChildProcess> => {
    const p = cp.spawn(lspCommand, {
      env: {
        MILONE_HOME: miloneHome,
        MILONE_LSP_SERVER_LOG_LEVEL,
        MILONE_LSP_SERVER_DOTNET_COMMAND: dotnetCommand,

        // Heap limit ~2GB. https://docs.microsoft.com/en-us/dotnet/core/runtime-config/garbage-collector#heap-limit
        DOTNET_GCHeapHardLimit: "0x70001000",
      },
    })
    server = p

    p.stderr.on("readable", () => {
      let buf = ""
      while (true) {
        const chunk = (p.stderr.read() as Buffer | null)?.toString() ?? ""
        if (chunk.length === 0) break
        buf += chunk
      }
      logger.info("[server]", buf.trimEnd())
    })

    p.on("exit", code => console.log("server exited with", code))
    p.on("error", err => console.error("spawn error", err))
    return p
  }

  const clientOptions: LanguageClientOptions = {
    documentSelector: [
      {
        language: "milone",
      },
    ],
    synchronize: {
      fileEvents: [
        workspace.createFileSystemWatcher("**/*.fs"),
        workspace.createFileSystemWatcher("**/*.milone"),
        workspace.createFileSystemWatcher("**/milone_manifest"),
      ],
    },
  }

  const client = new LanguageClient("milone-lang", "Milone Language", serverOptions, clientOptions)

  clientDisposable?.dispose()
  clientDisposable = client.onDidChangeState(e => {
    // Log state change.
    const s = (n: number) => ({ 1: "Stopped", 2: "Running", 3: "Starting" })[n] ?? "Unknown"
    console.log("client state:", s(e.oldState), "->", s(e.newState))

    // Kill server process forcibly. (Server should exit by itself but sometimes it doesn't. Just my guess, client fails to send exit notification.)
    if (e.oldState === State.Running && e.newState === State.Stopped && server != undefined) {
      const p = server
      console.log("terminating server")
      p.kill()
      setTimeout(() => {
        console.log("killing server")
        p.kill("SIGKILL")
      }, 5000)
    }
  })
  return client
}

const startLspSession = (context: ExtensionContext, logger: Logger) => {
  const miloneHome = getMiloneHome(logger)
  logger.info("miloneHome =", miloneHome)
  if (miloneHome == undefined) return

  const lspCommand = getLspCommand(miloneHome, logger)
  logger.info("lspCommand =", lspCommand)
  if (lspCommand == undefined) return

  const dotnetCommand = workspace.getConfiguration("milone-lang").get<string>("dotnet-command") ?? undefined
  logger.info("dotnetCommand = ", dotnetCommand)

  if (DEV) {
    startLspSessionDev({
      lspCommand,
      context,
      newLanguageClient: command => newLanguageClient(command, miloneHome, dotnetCommand, logger),
    })
  } else {
    const client = newLanguageClient(lspCommand, miloneHome, dotnetCommand, logger)
    context.subscriptions.push(client.start())
  }
}

/** Called when the extension is activated. */
export const activate = (context: ExtensionContext): void => {
  const logger: Logger = {
    info: (...args) => console.info("[milone]", ...args),
  }

  startLspSession(context, logger)
}

/** Called when the extension is being terminated. */
export const deactivate = (): Thenable<void> | undefined => undefined
