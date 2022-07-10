#!/bin/sh
ldd wolfman
patchelf --replace-needed libc.so.6 ./libc.so.6 ./wolfman
patchelf --set-interpreter ./ld-2.31.so ./wolfman
ldd wolfman