# USAGE:
#    make
#    make install-dev

.PHONY: build test install-dev clean

# ------------------------------------------------
# build & test
# ------------------------------------------------

build: test

test: milone-netcore.timestamp dotnet-test.timestamp milone

milone-netcore.timestamp: MiloneLang/*.fs
	dotnet build -nologo MiloneLang
	touch milone-netcore.timestamp

dotnet-test.timestamp: MiloneLang/*.fs MiloneTests/*.fs
	dotnet test -nologo
	touch dotnet-test.timestamp

milone: MiloneLang/*.fs runtime/*.c runtime/*.h
	./test-self

# ------------------------------------------------
# install
# ------------------------------------------------

install-dev: install-dev.timestamp

install-dev.timestamp: build
	./install-dev
	touch install-dev.timestamp

# ------------------------------------------------
# clean
# ------------------------------------------------

clean:
	rm -f *.generated.*
	rm -f tests/*/*/*.generated.*
	rm -f *.timestamp
	rm -f milone
	rm -rf \
		MiloneLang/bin \
		MiloneLang/obj \
		MiloneTests/bin \
		MiloneTests/obj \
		milone_lsp/bin \
		milone_lsp/obj
