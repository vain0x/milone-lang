# Makefile as a thin wrapper of ninja.
#
# USAGE:
#    make
#    make install
#    make install-dev

default: build.ninja bin/ninja
	bin/ninja

.PHONY: build clean default install install-dev test uninstall

# ------------------------------------------------
# ninja wrapper
# ------------------------------------------------

build.ninja: \
		$(wildcard scripts/GenNinjaFile/*.fs) \
		$(wildcard scripts/GenNinjaFile/*.fsproj) \
		build-template.ninja \
		$(wildcard tests/*)
	scripts/build-ninja-gen

build: bin/ninja build.ninja
	bin/ninja test_self

test: build

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

# https://deno.land/
.deno:
	env DENO_INSTALL="${PWD}/.deno" sh -c 'curl -fsSL https://deno.land/x/install/install.sh | sh'
