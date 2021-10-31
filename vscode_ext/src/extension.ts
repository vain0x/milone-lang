import { homedir } from "os"
import * as ChildProcess from "child_process"
import * as path from "path"
import { ExtensionContext, workspace } from "vscode"
import { LanguageClient, LanguageClientOptions, ServerOptions } from "vscode-languageclient/node"
import { startLspSessionDev } from "./lsp_session_dev"

const DEV = process.env["MILONE_LSP_SERVER_DEV"] === "1"
const MILONE_LSP_COMMAND = process.env["MILONE_LSP_COMMAND"] ?? ""
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

  return path.join(homedir(), ".milone")
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

const newLanguageClient = (lspCommand: string, miloneHome: string, logger: Logger): LanguageClient => {
  const serverOptions: ServerOptions = async (): Promise<ChildProcess.ChildProcess> => {
    const p = ChildProcess.spawn(lspCommand, {
      env: { MILONE_HOME: miloneHome },
    })

    p.stderr.on("readable", () => {
      let buf = ""
      while (true) {
        const chunk = (p.stderr.read() as Buffer | null)?.toString() ?? ""
        if (chunk.length === 0) break
        buf += chunk
      }
      logger.info("[server]", buf.trimEnd())
    })
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
      ],
    },
  }

  return new LanguageClient("milone-lang", "Milone Language", serverOptions, clientOptions)
}

const startLspSession = (context: ExtensionContext, logger: Logger) => {
  const miloneHome = getMiloneHome(logger)
  logger.info("miloneHome =", miloneHome)
  if (miloneHome == undefined) return

  const lspCommand = getLspCommand(miloneHome, logger)
  logger.info("lspCommand =", lspCommand)
  if (lspCommand == undefined) return

  if (DEV) {
    startLspSessionDev({
      lspCommand,
      context,
      newLanguageClient: command => newLanguageClient(command, miloneHome, logger),
    })
  } else {
    const client = newLanguageClient(lspCommand, miloneHome, logger)
    context.subscriptions.push({ dispose: () => { console.log("client stopped."); client.stop() } })
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
