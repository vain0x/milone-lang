# USAGE:
#    make
#    make install
#    make install-dev

.PHONY: all build test install install-dev clean

all: target build.ninja
	ninja

# Directory for intermediate files.
target:
	mkdir -p target

# ninja config file.
build.ninja: build.ninja-template
	./build-ninja-gen

# ------------------------------------------------
# ninja wrapper
# ------------------------------------------------

build: build.ninja **/*.fs **/*.milone
	ninja test_self

test: build

clean: build.ninja
	ninja clean

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
