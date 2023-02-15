import path from "path"
import { CancellationToken, commands, ExtensionContext, ProviderResult, TextDocumentContentProvider, TextEditor, Uri, window, workspace } from "vscode"
import { LanguageClient } from "vscode-languageclient/node"

export const registerShowSyntaxTreeCommand = (context: ExtensionContext, options: { getClient: () => LanguageClient | undefined }) => {

  context.subscriptions.push(
    commands.registerTextEditorCommand(
      "milone-lang.show-syntax-tree",
      showSyntaxTree,
    ))

  context.subscriptions.push(
    workspace.registerTextDocumentContentProvider(
      "milone-syntax-tree",
      new SyntaxTreeDocumentProvider(
        () => options.getClient(),
      )))
}

const showSyntaxTree = (textEditor: TextEditor): void => {
  const uri = textEditor.document.uri
  if (uri.scheme !== "file") {
    window.showErrorMessage("Can't show syntax tree of non-file. Save it first.")
    return
  }

  // `milone-syntax-tree://path?uri=file:///path/to/file.milone`
  const syntaxTreeUri = Uri.from({
    scheme: "milone-syntax-tree",
    path: path.basename(uri.path) + ".json",
    query: new URLSearchParams([["uri", uri.toString()]]).toString(),
  })
  window.showTextDocument(syntaxTreeUri)
}

class SyntaxTreeDocumentProvider implements TextDocumentContentProvider {
  constructor(
    private readonly getClient: () => LanguageClient | undefined,
  ) { }

  provideTextDocumentContent(uri: Uri, token: CancellationToken): ProviderResult<string> {
    return (async () => {
      const textDocumentUri = Uri.parse(new URLSearchParams(uri.query).get("uri") as string)

      const client = this.getClient()
      if (!client) {
        return null
      }

      const result = await client.sendRequest("$/syntaxTree", { textDocument: { uri: textDocumentUri.toString() } }, token)
      if (!isResultObject(result)) {
        return null
      }

      return result.content
    })()
  }
}

const isResultObject = (value: unknown): value is { content: string } =>
  typeof value === "object" && value != null && !Array.isArray(value) && "content" in value
