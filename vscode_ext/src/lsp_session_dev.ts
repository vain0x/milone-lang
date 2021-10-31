// LSP session for development environment.
// Live reload is enabled. Whenever LSP server binary is updated, session restarts.

// See also: <https://github.com/vain0x/vscode-auto-reload-lsp-server>

import fs, { FSWatcher } from "fs"
import { debounce } from "lodash"
import path from "path"
import { ExtensionContext, window } from "vscode"
import { Disposable, LanguageClient } from "vscode-languageclient/node"
import { copyDirRecursively, unlinkDirRecursively } from "./util/fs_ext"

const RETRY_TIME = 60 * 1000
const RETRY_INTERVAL = 100
const RELOAD_STATUS_DURATION = 5000

const delay = (timeMs: number) => new Promise<void>(resolve => setTimeout(resolve, timeMs))

const retrying = async <A>(action: () => Promise<A>, options: { count: number, intervalMs: number }): Promise<A> => {
  const { count, intervalMs } = options
  if (count <= 0) throw new Error() // Illegal call.

  for (let i = 0; i < count - 1; i++) {
    try {
      return await action()
    } catch (err) {
      console.warn("warn: Error occurred.", err, "Retrying...")
    }
    await delay(intervalMs)
  }

  return await action()
}

const stopClient = async (client: LanguageClient): Promise<void> => {
  if (!client.needsStop()) {
    console.log("stopClient (no need)")
    return
  }

  console.log("stopClient: stopping")
  await client.stop()

  // https://github.com/microsoft/vscode-languageserver-node/blob/cec94077ddb30bf1f4c5542b51c30494368c7cdc/client/src/node/main.ts#L228
  await delay(2 * 1000 + 300) // Wait until the process ends.
  console.log("stopClient: end")
}

// -----------------------------------------------
// Interface
// -----------------------------------------------

export const startLspSessionDev = (options: {
  lspCommand: string
  context: ExtensionContext
  newLanguageClient: (lspCommand: string) => LanguageClient
}): void => {
  console.log("LSP session development mode.")

  const { newLanguageClient, context } = options
  const outputLspCommand = path.normalize(options.lspCommand)
  const outputDir = path.dirname(outputLspCommand)
  const backupDir = path.join(path.dirname(outputDir), path.basename(outputDir) + "_backup")
  const backupLspCommand = outputLspCommand.replace(outputDir, backupDir)
  console.log({ outputDir, outputLspCommand, backupDir, backupLspCommand })

  // Notification:
  let notification: Disposable | undefined
  context.subscriptions.push({ dispose: () => notification?.dispose() })

  const setNotification = (action: () => Disposable): void => {
    notification?.dispose()
    notification = action()
  }

  const notifyStarting = (p: Promise<unknown>): void => {
    setNotification(() => window.setStatusBarMessage("Reloading LSP client.", p))
  }

  const notifyStarted = (): void => {
    setNotification(() => window.setStatusBarMessage("LSP client has reloaded.", RELOAD_STATUS_DURATION))
  }

  let initialError = true
  const reportError = (err: unknown) => {
    console.error("err:", err)
    if (initialError) {
      initialError = false
      window.showErrorMessage("Error. " + (err as any)?.message)
    }
  }

  // Watch:
  let watcher: FSWatcher | undefined
  context.subscriptions.push({ dispose: () => watcher?.close() })
  const ensureWatch = () => {
    watcher?.close()
    watcher = fs.watch(outputDir)
    watcher.once("change", requestReload)
    watcher.on("error", reportError)
  }

  // Backup:
  const backup = async () => retrying(async () => {
    await copyDirRecursively(outputDir, backupDir)
  }, {
    count: RETRY_TIME / RETRY_INTERVAL,
    intervalMs: RETRY_INTERVAL,
  })
  context.subscriptions.push({
    dispose: () => {
      unlinkDirRecursively(backupDir).catch(err => {
        console.error("warn: Couldn't delete backup dir.", backupDir, err)
      })
    }
  })

  // Client:
  const client = newLanguageClient(backupLspCommand)
  context.subscriptions.push({ dispose: () => { client.stop() } })

  context.subscriptions.push(
    client.onDidChangeState(e => {
      const s = (n: number) => ({ 1: "Stopped", 2: "Running", 3: "Starting" })[n] ?? "Unknown"
      console.log("client state:", s(e.oldState), "->", s(e.newState))
    }))

  // Reload:
  const reload = async (): Promise<void> => {
    console.log("reload begin")
    await stopClient(client)

    await backup()
    ensureWatch()

    client.start()
    console.log("reload end")
  }

  const reloadWithNotification = async (): Promise<void> => {
    try {
      const promise: Promise<void> = reload()
      notifyStarting(promise)
      await promise
      notifyStarted()
    } catch (err) {
      reportError(err)
      requestReload()
    }
  }

  const requestReload = debounce(async (): Promise<void> => {
    await reloadWithNotification()
  })

  // Start.
  requestReload()
}
