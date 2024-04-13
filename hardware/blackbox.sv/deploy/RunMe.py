import string
import os
from subprocess import DEVNULL, check_call
def hex_(v):
    return hex(v).replace('0x', '').upper().rjust(2, '0')


def block_construct_stage1(string, a, opcode):
    block_template = "AA{}\nEE{}\n{}\n0000\n7777"
    return '\n'.join([block_template.format(hex_(ord(c)), hex_(a), opcode) for c in string]) + '\nFFFF'


def exec_program(program_hex):
    # print(program_hex)
    with open('mem.hex.txt', 'w') as f:
        f.write(program_hex)
    check_call(['run_cpu.bat'], stdout=DEVNULL, stderr=DEVNULL)
    with open('output.txt', 'r') as f:
        return [int(i, 16) for i in f.read().splitlines(keepends=False)]


def stage1(string):
    As = [3, 0xFD, 0xFE, 99, 11, 55]
    results = []
    for a in As:
        results.append(exec_program(block_construct_stage1(string, a, 'CCCC')))
    return results


def stage2(stage1out: list):
    stage2_program_template = "AA{}\nEE{}\nBBBB\nEE{}\nBBBB\nEE{}\nBBBB\nEE{}\nBBBB\nEE{}\nDDDD\n0000\n7777\nFFFF"
    operands = []
    for j in range(len(stage1out[0])):
        op_ = []
        for i in range(len(stage1out)):
            op_.append(hex_(stage1out[i][j]))
        operands.append(op_)
    res = []
    for op_group in operands:
        p = stage2_program_template.format(*op_group)
        res.append(exec_program(p)[0])
    return res


flag = input('flag: ')

for c in flag:
    if c not in (string.ascii_letters + string.digits + '_{}'):
        print('ERROR: flag chars can be only letters/digits/underscore')
        exit(0)

ciphertext = stage2(stage1(flag))
print('Зашифрованный флаг:', ciphertext)

if ciphertext == [287, 283, 259, 265, 276, 266, 305, 280, 259, 278, 260, 285, 259, 278, 263, 245, 280, 259, 265, 289, 83, 290, 269, 245, 83, 281, 245, 259, 285, 263, 281, 80, 287, 89, 303]:
    print('Вы успешно решили задание! Скорее сдавайте флаг!')
else:
    print('Попробуйте ещё! (неверный флаг)')

os.remove('mem.hex.txt')
os.remove('output.txt')