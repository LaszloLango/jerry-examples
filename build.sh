#!/bin/bash

BASE_DIR=`git rev-parse --show-toplevel`
JERRY_HOME="$BASE_DIR/deps/source/jerryscript"
CONFIG=debug
BIN_DIR="$BASE_DIR/bin"
LIBRARIES_DIR="$JERRY_HOME/build/lib"
INCLUDE_DIRS="-I$JERRY_HOME/jerry-core/include -I$JERRY_HOME/jerry-ext/include"

IS_JERRY=`ls deps/source/jerryscript`

if [ -z "$IS_JERRY" ]
then
  echo "Init JerryScript repository"
  git submodule update --recursive --init
fi

rm -vrf ${BIN_DIR}
mkdir -vp ${BIN_DIR}

cd $JERRY_HOME
echo "Building JerryScript..."
./tools/build.py -v --clean --lto=off --jerry-cmdline=off
STATUS=$?
cd $BASE_DIR

if [ $STATUS -ne 0 ]
then
  echo "JerryScript build failed"
  exit $STATUS
fi

gcc -std=c99 -nostdlib -static -g -Wall \
    -o ${BIN_DIR}/example1 src/example1.c \
    ${INCLUDE_DIRS} -I'include' \
    -isystem "$JERRY_HOME/jerry-libc/include" \
    -flto -L"$LIBRARIES_DIR" \
    -ljerry-core -ljerry-libm -ljerry-libc -ljerry-port-default -lgcc

gcc -std=c99 -nostdlib -static -g -Wall \
    -o ${BIN_DIR}/example2 src/example2.c \
    ${INCLUDE_DIRS} -I'include' \
    -flto -L"$LIBRARIES_DIR" \
    -ljerry-core -ljerry-libm -ljerry-libc -ljerry-port-default -ljerry-ext -lgcc

gcc -std=c99 -nostdlib -static -g -Wall \
    -o ${BIN_DIR}/example3 src/example3.c \
    ${INCLUDE_DIRS} -I'include' \
    -flto -L"$LIBRARIES_DIR" \
    -ljerry-core -ljerry-libm -ljerry-libc -ljerry-port-default -ljerry-ext -lgcc

gcc -std=c99 -nostdlib -static -g -Wall \
    -o ${BIN_DIR}/example4 src/example4.c \
    ${INCLUDE_DIRS} -I'include' \
    -flto -L"$LIBRARIES_DIR" \
    -ljerry-core -ljerry-libm -ljerry-libc -ljerry-port-default -ljerry-ext -lgcc

gcc -std=c99 -static -g -Wall \
    -o ${BIN_DIR}/example5 src/example5.c \
    ${INCLUDE_DIRS} -I'include' \
    -flto -L"$LIBRARIES_DIR" \
    -ljerry-core -ljerry-libm -ljerry-port-default -ljerry-ext -lgcc

gcc -std=c99 -nostdlib -static -g -Wall \
    -o ${BIN_DIR}/example6 src/example6.c \
    ${INCLUDE_DIRS} -I'include' \
    -flto -L"$LIBRARIES_DIR" \
    -ljerry-core -ljerry-libm -ljerry-libc -ljerry-port-default -ljerry-ext -lgcc

gcc -std=c99 -nostdlib -static -g -Wall \
    -o ${BIN_DIR}/example7 src/example7.c \
    ${INCLUDE_DIRS} -I'include' \
    -flto -L"$LIBRARIES_DIR" \
    -ljerry-core -ljerry-libm -ljerry-libc -ljerry-port-default -ljerry-ext -lgcc
