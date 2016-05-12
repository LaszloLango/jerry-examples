#!/bin/bash

CURRENT_DIR=`pwd -P`
JERRY_HOME="$CURRENT_DIR/deps/source/jerryscript"
CONFIG=debug
BIN_DIR="$CURRENT_DIR/bin"

rm -rf ${BIN_DIR}
mkdir -p ${BIN_DIR}

rm -rf deps/lib
mkdir -p deps/lib

cd $JERRY_HOME
make clean
make ${CONFIG}.linux
STATUS=$?
cd $CURRENT_DIR

if [ $STATUS -ne 0 ]
then
  echo "JerryScript build failed"
  exit $STATUS
fi

rm -f "$CURRENT_DIR/deps/lib/*.a"

cp "$JERRY_HOME/build/obj/linux/jerry-core/lib$CONFIG.jerry-core.a" "$CURRENT_DIR/deps/lib/libjerry-core.a"
cp "$JERRY_HOME/build/obj/linux/jerry-libc/lib$CONFIG.jerry-libc.linux.lib.a" "$CURRENT_DIR/deps/lib/libjerry-libc.a"
cp "$JERRY_HOME/build/obj/linux/jerry-libm/lib$CONFIG.jerry-libm.lib.a" "$CURRENT_DIR/deps/lib/libjerry-libm.a"

gcc -std=c99 -static -g -Wall \
    -o ${BIN_DIR}/example1 src/example1.c \
    -I'deps/include' -I'include' \
    -flto -L'deps/lib' \
    -ljerry-core -ljerry-libm

gcc -std=c99 -static -g -Wall \
    -o ${BIN_DIR}/example2 src/example2.c \
    -I'deps/include' -I'include' \
    -flto -L'deps/lib' \
    -ljerry-core -ljerry-libm

gcc -std=c99 -static -g -Wall \
    -o ${BIN_DIR}/example3 src/example3.c \
    -I'deps/include' -I'include' \
    -flto -L'deps/lib' \
    -ljerry-core -ljerry-libm

gcc -std=c99 -static -g -Wall \
    -o ${BIN_DIR}/example4 src/example4.c \
    -I'deps/include' -I'include' \
    -flto -L'deps/lib' \
    -ljerry-core -ljerry-libm

gcc -std=c99 -static -g -Wall \
    -o ${BIN_DIR}/example5 src/example5.c \
    -I'deps/include' -I'include' \
    -flto -L'deps/lib' \
    -ljerry-core -ljerry-libm

gcc -std=c99 -static -g -Wall \
    -o ${BIN_DIR}/example6 src/example6.c \
    -I'deps/include' -I'include' \
    -flto -L'deps/lib' \
    -ljerry-core -ljerry-libm

gcc -std=c99 -static -g -Wall \
    -o ${BIN_DIR}/example7 src/example7.c \
    -I'deps/include' -I'include' \
    -flto -L'deps/lib' \
    -ljerry-core -ljerry-libm
