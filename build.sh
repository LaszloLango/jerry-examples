#!/bin/bash

rm -rf bin
mkdir bin

gcc -std=c99 -static -g -Wall \
	-o bin/example1 src/example1.c \
	-I'deps/include' -I'include' \
	-flto -L'deps/lib' \
	-ljerry-core -ljerry-libm

gcc -std=c99 -static -g -Wall \
        -o bin/example2 src/example2.c \
        -I'deps/include' -I'include' \
        -flto -L'deps/lib' \
        -ljerry-core -ljerry-libm

gcc -std=c99 -static -g -Wall \
        -o bin/example3 src/example3.c \
        -I'deps/include' -I'include' \
        -flto -L'deps/lib' \
        -ljerry-core -ljerry-libm

gcc -std=c99 -static -g -Wall \
        -o bin/example4 src/example4.c \
        -I'deps/include' -I'include' \
        -flto -L'deps/lib' \
        -ljerry-core -ljerry-libm

gcc -std=c99 -static -g -Wall \
        -o bin/example5 src/example5.c \
        -I'deps/include' -I'include' \
        -flto -L'deps/lib' \
        -ljerry-core -ljerry-libm
