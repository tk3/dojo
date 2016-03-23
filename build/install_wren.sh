#!/bin/sh

mkdir -p ~/opt/wren
mkdir -p ~/opt/wren/include
mkdir -p ~/opt/wren/lib
cp src/include/wren.h ~/opt/wren/include
cp -r ./lib ~/opt/wren
cp -r ./bin ~/opt/wren

