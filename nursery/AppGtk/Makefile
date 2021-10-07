# USAGE:
#	make
#
# Prerequisites:
#	- gcc, milone-lang installed

default: build

.PHONY: build run

target/app_gtk.c: $(wildcard *.fs) $(wildcard *.milone)
	./build-1

target/app: target/app_gtk.c app_gtk.c
	./build-2

build: target/app

run: build
	target/app
