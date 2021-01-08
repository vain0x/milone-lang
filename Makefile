# USAGE:
#    make
#    make install
#    make install-dev

# Makefile is a thin-wrapper of ninja.
# When ninja fails, refresh build script for ninja and retry.

.PHONY: default build test install install-dev clean

# (This is the first rule in file and therefore it's default.)
default:
	ninja || ( ./build-ninja-gen && ninja )

# ------------------------------------------------
# Utilities
# ------------------------------------------------

# Directory for intermediate files.
target:
	mkdir -p target

# ------------------------------------------------
# ninja wrapper
# ------------------------------------------------

build: **/*.fs **/*.milone
	ninja test_self || ( ./build-ninja-gen && ninja test_self )

test: build

clean:
	./clean

# ------------------------------------------------
# install
# ------------------------------------------------

install: target/install.timestamp

target/install.timestamp: target build.ninja
	./install
	touch target/install.timestamp



install-dev: target build.ninja target/install-dev.timestamp

target/install-dev.timestamp: target build
	./install-dev
	touch target/install-dev.timestamp
