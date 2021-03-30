module rec GenNinjaFile.TemplateTestCase

let buildTemplate = """
# {{ CATEGORY }}/{{ PROJECT }}
build {{ NINJA_FILE }}: $
  take_snapshot $
    {{ FS_FILE }} $
    | target/milone
  exe_file = {{ EXE_FILE }}
  expected_out_file = {{ EXPECTED_OUT_FILE }}
  milone = target/milone
  name = {{ PROJECT }}
  out_file = {{ OUT_FILE }}
  project = tests/{{ CATEGORY }}/{{ PROJECT }}

build {{ EXE_FILE }}: $
  build_test $
    {{ NINJA_FILE }} $
    | runtime/milone.h $
      runtime/milone.o
  expected_out_file = {{ EXPECTED_OUT_FILE }}
  out_file = {{ OUT_FILE }}
  project = tests/{{ CATEGORY }}/{{ PROJECT }}

build {{ OUT_FILE }}: $
  execute_test {{ EXE_FILE }}
  expected_out_file = {{ EXPECTED_OUT_FILE }}
  project = tests/{{ CATEGORY }}/{{ PROJECT }}

build {{ DIFF_FILE }}: $
  diff_test_output $
    {{ OUT_FILE }} $
    tests/{{ CATEGORY }}/{{ PROJECT }}/{{ PROJECT }}.out
  name = {{ PROJECT }}

build target/tests/{{ CATEGORY }}/{{ PROJECT }}/test.timestamp: $
  verify_test_output {{ DIFF_FILE }}
  pool = console

build {{ PROJECT }}: $
  phony target/tests/{{ CATEGORY }}/{{ PROJECT }}/test.timestamp
  pool = console
"""

let renderTestCaseBuildStatements category projectName =
  let file ext =
    sprintf "tests/%s/%s/%s%s" category projectName projectName ext

  buildTemplate
    .Replace("{{ CATEGORY }}", category)
    .Replace("{{ PROJECT }}", projectName)
    .Replace("{{ FS_FILE }}", file ".fs")
    .Replace("{{ EXPECTED_OUT_FILE }}", file ".out")
    .Replace("{{ DIFF_FILE }}", file ".generated.diff")
    .Replace("{{ EXE_FILE }}", file ".generated.exe")
    .Replace("{{ NINJA_FILE }}", file ".generated.ninja")
    .Replace("{{ OUT_FILE }}", file ".generated.out")
