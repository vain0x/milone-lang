# Makefile as a thin wrapper of ninja.
#
# USAGE:
#    make
#    make install
#    make install-dev

default: target/gen3_files.txt

.PHONY: build clean default install install-dev test uninstall

# ------------------------------------------------
# temporary build rules
# ------------------------------------------------

src/MiloneCli/bin/Debug/net5.0/MiloneCli: \
	$(wildcard src/*/*.fs) \
	$(wildcard src/*/*.fsproj) \
	$(wildcard src/*/*.milone)
	dotnet build --no-restore src/MiloneCli && \
	touch src/MiloneCli/bin/Debug/net5.0/MiloneCli

target/gen2_files.txt: src/MiloneCli/bin/Debug/net5.0/MiloneCli
	src/MiloneCli/bin/Debug/net5.0/MiloneCli compile src/MiloneCli --profile --target-dir target/gen2 | sed 's;^;target/gen2/;' | tee target/gen2_files.txt >&2

target/milone: target/gen2_files.txt
	cat target/gen2_files.txt | \
		xargs -I{} sh -c 'clang -Wno-parentheses-equality -Iruntime -c {} -o $$(dirname {})/$$(basename {} .c).o' && \
	clang runtime/milone.o $(shell cat target/gen2_files.txt | sed 's;\.c$$;.o;') -o target/milone

target/gen3_files.txt: target/milone
	target/milone compile src/MiloneCli --profile --target-dir target/gen3 | sed 's;^;target/gen3/;' | tee target/gen3_files.txt >&2 && \
		if scripts/verify-gen3; then echo 'OK'; else echo 'NG'; fi

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
