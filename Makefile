# USAGE:
#    make
#    make install
#    make install-dev

# Makefile is a thin-wrapper of ninja.

.PHONY: build build.ninja default test install install-dev clean

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

install: target/install.timestamp

target/install.timestamp: build.ninja
	./install
	touch target/install.timestamp



install-dev: build.ninja target/install-dev.timestamp

target/install-dev.timestamp: build
	./install-dev
	touch target/install-dev.timestamp
