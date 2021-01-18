# USAGE:
#    make
#    make install
#    make install-dev

# Makefile is a thin-wrapper of ninja.

.PHONY: build build.ninja default install install-dev clean test

# (This is the first rule in file and therefore it's default.)
default: build.ninja
	ninja

# ------------------------------------------------
# ninja wrapper
# ------------------------------------------------

build.ninja:
	./build-ninja-gen

build: build.ninja **/*.fs **/*.milone
	ninja test_self

test: build

clean:
	./clean

# ------------------------------------------------
# install
# ------------------------------------------------

install:
	./install

install-dev:
	./install-dev
