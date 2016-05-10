#!/bin/bash

CURRENT_DIR=`pwd -P`
JERRY_HOME="$CURRENT_DIR/deps/source/jerryscript"

rm -rf bin
mkdir bin

cd $JERRY_HOME
make clean
make release.linux
STATUS=$?
cd $CURRENT_DIR

if [ $STATUS -ne 0 ]
then
  echo "JerryScript build failed"
  exit $STATUS
fi

rm -f "$CURRENT_DIR/deps/lib/*.a"

cp "$JERRY_HOME/build/obj/linux/jerry-core/librelease.jerry-core.a" "$CURRENT_DIR/deps/lib/libjerry-core.a"
cp "$JERRY_HOME/build/obj/linux/jerry-libc/librelease.jerry-libc.linux.lib.a" "$CURRENT_DIR/deps/lib/libjerry-libc.a"
cp "$JERRY_HOME/build/obj/linux/jerry-libm/librelease.jerry-libm.lib.a" "$CURRENT_DIR/deps/lib/libjerry-libm.a"

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
