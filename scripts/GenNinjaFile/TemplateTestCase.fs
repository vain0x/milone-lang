module rec GenNinjaFile.TemplateTestCase

let buildTemplate = """
# {{ CATEGORY }}/{{ PROJECT }}
build {{ C_FILE }}: $
  take_snapshot $
    {{ FS_FILE }} $
    | $milone_dotnet_debug
  milone = $milone_dotnet_debug
  project = tests/{{ CATEGORY }}/{{ PROJECT }}
  out_file = {{ OUT_FILE }}

build {{ EXE_FILE }}: $
  build_test $
    {{ C_FILE }} $
    | runtime/milone.h $
      runtime/milone.c
  out_file = {{ OUT_FILE }}

build {{ OUT_FILE }}: $
  execute_test $
    {{ EXE_FILE }}
   c_file = {{ C_FILE }}

build {{ DIFF_FILE }}: $
  diff_test_output $
    {{ OUT_FILE }} $
    tests/{{ CATEGORY }}/{{ PROJECT }}/{{ PROJECT }}.out
  test = {{ PROJECT }}
"""

let renderTestCaseBuildStatements category projectName =
  let file ext =
    sprintf "tests/%s/%s/%s%s" category projectName projectName ext

  buildTemplate
    .Replace("{{ CATEGORY }}", category)
    .Replace("{{ PROJECT }}", projectName)
    .Replace("{{ C_FILE }}", file ".c")
    .Replace("{{ FS_FILE }}", file ".fs")
    .Replace("{{ DIFF_FILE }}", file ".generated.diff")
    .Replace("{{ EXE_FILE }}", file ".generated.exe")
    .Replace("{{ OUT_FILE }}", file ".generated.out")
