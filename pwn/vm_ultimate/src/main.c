#include "./vm/vm.h"
#include <stdlib.h>
char memory[0x1000*2]={0};

int main(){
    setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
    Vm vm = init_vm(memory+0x1000, memory, 0x1000, 0x1000);
    puts("[+] Welcome to ultimate vm!!!");
    puts("Enter your code you need to execute:");
    fgets(memory+0x1000,0x1000,stdin);
    puts("[+] Succesfully writed your code");
    puts("[+] Started execution...");
    while(1){
        Command* cmd = read_command(&vm);
        int result = execute_command(&vm, cmd);
        if(!result)
            break;
    };
};
