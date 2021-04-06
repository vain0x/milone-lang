# Makefile as a thin wrapper of ninja.
#
# USAGE:
#    make
#    make install
#    make install-dev

default: test

.PHONY: build clean default install install-dev test uninstall

# ------------------------------------------------
# temporary build rules
# ------------------------------------------------

# src/MiloneCli/bin/Debug/net5.0/MiloneCli: \
# 	$(wildcard src/*/*.fs) \
# 	$(wildcard src/*/*.fsproj) \
# 	$(wildcard src/*/*.milone)
# 	dotnet build --no-restore src/MiloneCli && \
# 	touch src/MiloneCli/bin/Debug/net5.0/MiloneCli

# target/gen2_files.txt: src/MiloneCli/bin/Debug/net5.0/MiloneCli
# 	src/MiloneCli/bin/Debug/net5.0/MiloneCli compile src/MiloneCli --profile --target-dir target/gen2 | sed 's;^;target/gen2/;' | tee target/gen2_files.txt >&2

# target/milone: target/gen2_files.txt
# 	cat target/gen2_files.txt | \
# 		xargs -I{} sh -c 'clang -Wno-parentheses-equality -Iruntime -c {} -o $$(dirname {})/$$(basename {} .c).o' && \
# 	clang runtime/milone.o $(shell cat target/gen2_files.txt | sed 's;\.c$$;.o;') -o target/milone

# target/gen3_files.txt: target/milone
# 	target/milone compile src/MiloneCli --profile --target-dir target/gen3 | sed 's;^;target/gen3/;' | tee target/gen3_files.txt >&2 && \
# 		if scripts/verify-gen3; then echo 'OK'; else echo 'NG'; fi

# ------------------------------------------------
# ninja wrapper
# ------------------------------------------------

# build.ninja: \
# 		$(wildcard scripts/GenNinjaFile/*.fs) \
# 		$(wildcard scripts/GenNinjaFile/*.fsproj) \
# 		build-template.ninja \
# 		$(wildcard tests/*)
# 	scripts/build-ninja-gen

# build: bin/ninja build.ninja
# 	bin/ninja test_self

# test: build

clean:
	scripts/clean

# ------------------------------------------------
# install
# ------------------------------------------------

install:
	scripts/install

install-dev:
	scripts/install-dev

uninstall:
	scripts/uninstall

# ------------------------------------------------
# misc
# ------------------------------------------------

bin/ninja:
	scripts/install-ninja

# ------------------------------------------------
# MyBuildTool wrapper
# ------------------------------------------------

MY_BUILD := scripts/MyBuildTool/bin/Debug/net5.0/MyBuildTool

.PHONY: gen2 gen3 integration_tests my_build self test_self

${MY_BUILD}: \
		$(wildcard scripts/MyBuildTool/*.fs) \
		$(wildcard scripts/MyBuildTool/*.fsproj)
	dotnet build -nologo scripts/MyBuildTool

my_build: ${MY_BUILD}

target/milone: bin/ninja ${MY_BUILD} \
		$(wildcard src/*/*.fs) \
		$(wildcard src/*/*.fsproj) \
		$(wildcard src/*/*.milone)
	${MY_BUILD} gen2

gen2: target/milone

target/.timestamp/gen3: bin/ninja ${MY_BUILD} target/milone
	${MY_BUILD} gen3 && \
	touch target/.timestamp/gen3

gen3: target/.timestamp/gen3

self: gen2

test_self: gen3

integration_tests: bin/ninja ${MY_BUILD} target/milone \
		$(wildcard tests/**/*.fs) \
		$(wildcard tests/**/*.milone) \
		$(wildcard tests/**/*.out)
	${MY_BUILD} tests

test: test_self integration_tests
