#!/bin/bash

BASE_DIR=`git rev-parse --show-toplevel`
JERRY_HOME="$BASE_DIR/deps/source/jerryscript"
CONFIG=debug
BIN_DIR="$BASE_DIR/bin"
LIBRARIES_DIR="$BASE_DIR/deps/lib"
INCLUDE_DIR="$BASE_DIR/deps/include"

IS_JERRY=`ls deps/source/jerryscript`

if [ -z "$IS_JERRY" ]
then
  git submodule update --recursive --init
fi

rm -rf ${BIN_DIR}
mkdir -p ${BIN_DIR}

rm -rf ${LIBRARIES_DIR}
mkdir -p ${LIBRARIES_DIR}

rm -rf ${INCLUDE_DIR}
mkdir -p ${INCLUDE_DIR}

cp "$JERRY_HOME/jerry-core/jerry-api.h" "$INCLUDE_DIR/jerry-api.h"
cp "$JERRY_HOME/jerry-core/jerry-port.h" "$INCLUDE_DIR/jerry-port.h"
cp "$JERRY_HOME/jerry-core/jerry-snapshot.h" "$INCLUDE_DIR/jerry-snapshot.h"
cp "$JERRY_HOME/jerry-core/jerry.h" "$INCLUDE_DIR/jerry.h"

cd $JERRY_HOME
make clean
make ${CONFIG}.linux
STATUS=$?
cd $BASE_DIR

if [ $STATUS -ne 0 ]
then
  echo "JerryScript build failed"
  exit $STATUS
fi

cp "$JERRY_HOME/build/obj/linux/jerry-core/lib$CONFIG.jerry-core.a" "$LIBRARIES_DIR/libjerry-core.a"
cp "$JERRY_HOME/build/obj/linux/jerry-libc/lib$CONFIG.jerry-libc.linux.lib.a" "$LIBRARIES_DIR/libjerry-libc.a"
cp "$JERRY_HOME/build/obj/linux/jerry-libm/lib$CONFIG.jerry-libm.lib.a" "$LIBRARIES_DIR/libjerry-libm.a"

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
