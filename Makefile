.PHONY: build

build:
	g++ -fdiagnostics-color=always -g -DLOCALENV "$(SOURCE)" -o /tmp/problem
