#!/bin/sh
ldd not_isolated
patchelf --replace-needed libc.so.6 ./libc.so.6 ./not_isolated
patchelf --set-interpreter ./ld-2.31.so ./not_isolated
ldd not_isolated