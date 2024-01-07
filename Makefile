# Makefile as a thin(?) wrapper of MyBuildTool and scripts in `scripts/`.
#
# USAGE:
#    make
#    make install
#    make install-dev

# FIXME: add scripts/test-std, scripts/test-stdio

default: test

.PHONY: build clean default install install-dev pack test uninstall

clean:
	scripts/clean

install-dev:
	scripts/install-dev

# ------------------------------------------------
# misc
# ------------------------------------------------

bin/ninja:
	scripts/install-ninja

src/libmilonert/hashmap.h:
	scripts/install-hashmap

# ------------------------------------------------
# MyBuildTool wrapper
# ------------------------------------------------

DOTNET_RESTORE_TIMESTAMP := target/.timestamp/dotnet_restore

MY_BUILD := src/MyBuildTool/bin/Debug/net8.0/MyBuildTool

MY_BUILD_TIMESTAMP := target/.timestamp/my_build_tool

# Compiler to be used for bootstrapping, built by .NET version.
# (This will become outdated over development. Delete the file to rebuild.)
MILONE_BOOTSTRAP := target/bootstrap/bin/milone

# Compiler to be used for testing, built from source files in the worktree with MILONE_BOOTSTRAP.
MILONE_WORKTREE := target/MiloneCli/bin/milone

.PHONY: bootstrap building_tests dotnet_restore my_build self test_self

${DOTNET_RESTORE_TIMESTAMP}: $(wildcard src/*/*.fsproj)
	dotnet restore && mkdir -p $(shell dirname $@) && touch $@

${MY_BUILD_TIMESTAMP}: ${DOTNET_RESTORE_TIMESTAMP} \
		$(wildcard src/MyBuildTool/*.fs) \
		$(wildcard src/MyBuildTool/*.fsproj)
	dotnet build -nologo --no-restore src/MyBuildTool && mkdir -p $(shell dirname $@) && touch $@

my_build: ${MY_BUILD_TIMESTAMP}

install: ${MY_BUILD_TIMESTAMP} bin/ninja
	${MY_BUILD} self-install

uninstall: ${MY_BUILD_TIMESTAMP}
	${MY_BUILD} self-uninstall

pack: ${MY_BUILD_TIMESTAMP}
	${MY_BUILD} pack

${MILONE_BOOTSTRAP}: bin/ninja ${DOTNET_RESTORE_TIMESTAMP}
	env MILONE_HOME=${PWD} dotnet run --project src/MiloneCli -- build src/MiloneCli --target-dir target/bootstrap -o $@ && touch $@

bootstrap: ${MILONE_BOOTSTRAP}

${MILONE_WORKTREE}: bin/ninja \
		${MILONE_BOOTSTRAP} \
		${MY_BUILD_TIMESTAMP} \
		src/libmilonert/hashmap.h \
		src/libmilonert/milone.h \
		src/libmilonert/milone.c \
		src/libmilonert/milone_platform.c \
		$(wildcard src/*/*.fs) \
		$(wildcard src/*/*.fsproj) \
		$(wildcard src/*/*.milone)
	env MILONE_HOME=${PWD} ${MILONE_BOOTSTRAP} build src/MiloneCli -o $@ && touch $@

worktree: ${MILONE_WORKTREE}

target/milone: ${MILONE_WORKTREE}
	cp ${MILONE_WORKTREE} $@

# Building tests: Testing by building projects in the tests directory.
target/.timestamp/building_tests: ${MY_BUILD_TIMESTAMP} ${MILONE_WORKTREE} \
		$(shell find tests -type f -mtime -1)
	env MILONE=${MILONE_WORKTREE} ${MY_BUILD} building-tests && mkdir -p $(shell dirname $@) && touch $@

building_tests: target/.timestamp/building_tests

# Self-hosting tests: Testing by running the self-hosted compiler to verify the generated code equality.
target/.timestamp/self_hosting_tests: ${MY_BUILD_TIMESTAMP} ${MILONE_WORKTREE}
	 MILONE=${MILONE_WORKTREE} ${MY_BUILD} self-hosting-tests && mkdir -p $(shell dirname $@) && touch $@

self_hosting_tests: target/.timestamp/self_hosting_tests

test: building_tests self_hosting_tests
