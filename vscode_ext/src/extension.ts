import { homedir } from "os"
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

const getMiloneLsp = (home: string, logger: Logger): string | null => {
  const config = workspace.getConfiguration("milone-lang")

  const enabled = config.get<boolean>("lsp-enabled", true)
  if (!enabled) {
    logger.info("Config 'milone-lang.lsp-enabled' is false. LSP server won't start.")
    return null
  }

  const lspBin = config.get("lsp-bin") as string | undefined
  if (lspBin) {
    return lspBin
  }
  logger.info("Config 'milone-lang.lsp-bin' is unset or empty.")

  if (process.env.MILONE_LSP_BIN) {
    return process.env.MILONE_LSP_BIN
  }
  logger.info("Environment variable 'MILONE_LSP_BIN' is unset or empty.")

  return path.join(home, "bin/milone_lsp")
}

const startLspSession = (_context: ExtensionContext, logger: Logger) => {
  const miloneHome = getMiloneHome(logger)
  if (miloneHome == null) {
    return
  }
  logger.info("miloneHome =", miloneHome)

  const miloneLsp = getMiloneLsp(miloneHome, logger)
  if (miloneLsp == null) {
    return
  }
  logger.info("miloneLsp =", miloneLsp)

  const serverOptions: ServerOptions = {
    command: miloneLsp,
    args: [
      "start",
    ],
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
    "milone",
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
  const logger: Logger =  {
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
