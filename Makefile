# USAGE:
#    make
#    make install
#    make install-dev

# Makefile is a thin-wrapper of ninja.

.PHONY: build build.ninja clean default install install-dev test uninstall

# (This is the first rule in file and therefore it's default.)
default: build.ninja bin/ninja
	bin/ninja

# ------------------------------------------------
# ninja wrapper
# ------------------------------------------------

build.ninja:
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

bin/milone:
	scripts/dev-install-milone

bin/ninja:
	scripts/install-ninja
