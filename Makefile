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

build.ninja: bin/ninja build-meta.ninja build-template.ninja
	bin/ninja -f build-meta.ninja

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
