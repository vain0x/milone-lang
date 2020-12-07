# USAGE:
#    make
#    make install-dev

.PHONY: all build test install-dev clean

all: build.ninja
	ninja

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

install-dev: install-dev.timestamp

install-dev.timestamp: build
	./install-dev
	touch install-dev.timestamp
