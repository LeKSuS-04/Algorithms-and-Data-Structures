.PHONY: build run all

all: build run

run:
	/tmp/problem < input.txt

build:
	g++ -fdiagnostics-color=always -g -DLOCALENV "$(SOURCE)" -o /tmp/problem
