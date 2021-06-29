# Makefile as a thin wrapper of MyBuildTool.
#
# USAGE:
#    make
#    make install
#    make install-dev

default: test

.PHONY: build clean default install install-dev test uninstall

# ------------------------------------------------
# entrypoints
# ------------------------------------------------

clean:
	scripts/clean

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

.PHONY: dotnet_restore gen2 gen3 integration_tests my_build self test_self

target/.timestamp/dotnet_restore: \
		$(wildcard **/*.fsproj)
	dotnet restore && mkdir -p $(shell dirname $@) && touch $@

${MY_BUILD}: target/.timestamp/dotnet_restore \
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
	${MY_BUILD} gen3 && touch $@

gen3: target/.timestamp/gen3

self: gen2

test_self: gen3

integration_tests: bin/ninja ${MY_BUILD} target/milone \
		$(wildcard tests/**/*.fs) \
		$(wildcard tests/**/*.milone) \
		$(wildcard tests/**/*.out)
	${MY_BUILD} tests

test: test_self integration_tests
