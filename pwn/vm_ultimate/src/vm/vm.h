#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

#define TRUE 1
#define FALSE 0
//

#define READABLE 0x1
#define WRITEABLE 0x2
#define EXECUTABLE 0x3 


//flags

#define ZERO 0x1
#define GREATER 0x2
//commands
#define MOVRR 0x10
#define MOVRM 0x11
#define MOVMR 0x12

#define IN 0x20
#define OUT 0x21

#define ADDRV 0x30
#define SUBRV 0x31
#define XORRV 0x32


#define ADDRR 0x40
#define SUBRR 0x41
#define XORRR 0x42


#define JMPV 0x50
#define JZV 0x51
#define JGZV 0x52

#define CMPRR 0x60
#define CMPRV 0x61

//

typedef struct Command{
    signed char opcode;
    signed char op1;
    signed char op2;
    signed char padding;  //4 byte command
}Command;

typedef struct Memory{
    int flags; //READABLE || WRITEABLE || EXECUTABLE
    void* mem_ptr;
    size_t size;
}Memory;

typedef struct Registers{
    size_t regs[3];
}Registers;

typedef struct Vm{
    int eflags;
    Memory data;
    Memory code;
    void* ip;
    Registers regs;
}Vm;

Vm init_vm(void* code,void* data,size_t code_size,size_t data_size);

void run_vm(Vm* vm);

Command* read_command(Vm* vm);

int execute_command(Vm* vm,Command* cmd);






