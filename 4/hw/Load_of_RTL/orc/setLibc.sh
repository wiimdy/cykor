#!/bin/sh
ldd orc
patchelf --replace-needed libc.so.6 ./libc.so.6 ./orc
patchelf --set-interpreter ./ld-2.31.so ./orc
ldd orc