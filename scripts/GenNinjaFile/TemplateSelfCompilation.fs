module rec GenNinjaFile.TemplateSelfCompilation

open System.IO
open System.Text

let private objBuildTemplate = """
build target/{{ GEN }}/{{ NAME }}.o: $
  compile_c_to_obj $
    target/{{ GEN }}/{{ NAME }}.c $
    | runtime/milone.h
"""

type SelfCompilationTemplateOptions =
  { MiloneCoreSrc: string list
    MiloneStdSrc: string list
    MiloneLangSrc: string list
    NinjaTemplate: string }

let templateSelfCompilation (options: SelfCompilationTemplateOptions) : string =
  let moduleNames =
    [| let projects =
         [ "MiloneCore", options.MiloneCoreSrc
           "MiloneStd", options.MiloneStdSrc
           "MiloneLang", options.MiloneLangSrc ]

       for projectName, files in projects do
         for name in files do
           let ext = Path.GetExtension(name)

           if ext = ".fs" || ext = ".milone" then
             let name = Path.GetFileNameWithoutExtension(name)

             if name = projectName then
               name
             else
               sprintf "%s_%s" projectName name |]
    |> Array.sort

  let generatedFiles gen suffix =
    seq { for name in moduleNames -> sprintf "target/%s/%s%s" gen name suffix }
    |> String.concat " "

  let objBuild gen =
    let t =
      objBuildTemplate.Replace("{{ GEN }}", gen)

    let sb = StringBuilder()

    for name in moduleNames do
      sb.Append(t.Replace("{{ NAME }}", name)) |> ignore

    sb.ToString()

  options
    .NinjaTemplate
    .Replace("{{ GEN2_C_FILES }}", generatedFiles "gen2" ".c")
    .Replace("{{ GEN2_OBJ_FILES }}", generatedFiles "gen2" ".o")
    .Replace("{{ GEN2_OBJ_BUILD }}", objBuild "gen2")
    .Replace("{{ GEN3_C_FILES }}", generatedFiles "gen3" ".c")
