import { homedir } from "os"
import * as ChildProcess from "child_process"
import * as path from "path"
import { ExtensionContext, workspace } from "vscode"
import {
  LanguageClient,
  LanguageClientOptions,
  ServerOptions,
} from "vscode-languageclient"

let client: LanguageClient | undefined

type Logger = {
  info: (...args: unknown[]) => void
}

const getMiloneHome = (logger: Logger): string | null => {
  const config = workspace.getConfiguration("milone-lang")

  const home = config.get<string>("home")
  if (home) {
    return home
  }
  logger.info("Config 'milone-lang.home' is unset or empty.")

  if (process.env.MILONE_HOME) {
    return process.env.MILONE_HOME
  }
  logger.info("Environment variable 'MILONE_HOME' is unset or empty.")

  return path.join(homedir(), ".milone")
}

const getLspCommand = (miloneHome: string, logger: Logger): string | null => {
  const config = workspace.getConfiguration("milone-lang")

  const enabled = config.get<boolean>("lsp-enabled", true)
  if (!enabled) {
    logger.info("Config 'milone-lang.lsp-enabled' is false. LSP server won't start.")
    return null
  }

  const command = config.get("lsp-command") as string | undefined
  if (command) {
    return command
  }
  logger.info("Config 'milone-lang.lsp-command' is unset or empty.")

  if (process.env.MILONE_LSP_COMMAND) {
    return process.env.MILONE_LSP_COMMAND
  }
  logger.info("Environment variable 'MILONE_LSP_COMMAND' is unset or empty.")

  return path.join(miloneHome, "bin/milone_lsp/MiloneLsp")
}

const startLspSession = (_context: ExtensionContext, logger: Logger) => {
  const miloneHome = getMiloneHome(logger)
  if (miloneHome == null) {
    return
  }
  logger.info("miloneHome =", miloneHome)

  const lspCommand = getLspCommand(miloneHome, logger)
  if (lspCommand == null) {
    return
  }
  logger.info("lspCommand =", lspCommand)

  // const serverOptions: ServerOptions = {
  //   command: lspCommand,
  // }

  const serverOptions: ServerOptions = async (): Promise<ChildProcess.ChildProcess> => {
    const p = ChildProcess.spawn(lspCommand, {
      env: {
        MILONE_HOME: miloneHome,
      },
    })

    p.stderr.on("readable", () => {
      let buf = ""

      while (true) {
        const chunk = p.stderr.read() as Buffer | null
        if (!chunk || chunk.length === 0) {
          break
        }

        buf += chunk.toString("utf-8")
      }

      logger.info("[server] ", buf)
    })
    return p
  }

  const clientOptions: LanguageClientOptions = {
    documentSelector: [
      {
        language: "milone",
      },
    ],
    synchronize: {
      fileEvents: workspace.createFileSystemWatcher("**/.clientrc"),
    },
  }

  // Start LSP client, which spawns server instance.
  client = new LanguageClient(
    "milone-lang",
    "Milone Language",
    serverOptions,
    clientOptions,
  )
  client.start()
}

/**
 * Called when the extension is activated.
 */
export const activate = (context: ExtensionContext): void => {
  const logger: Logger = {
    info: (...args) => console.info("[milone-lsp]", ...args),
  }

  startLspSession(context, logger)
}

/**
 * Called when the extension is being terminated.
 */
export const deactivate = (): Thenable<void> | undefined => {
  if (client) {
    return client.stop()
  }
}
