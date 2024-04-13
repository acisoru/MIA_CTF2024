#include <stdio.h>
#include <stdlib.h>
#include "robotics.h"
#include "./heap/heap.h"

SafeRobo robotics[0x100]={0};

int get_idx(int bounds){
    char buf[10];
    memset(buf,0,10);
    fgets(buf,10,stdin);
    int index = atoi(buf);
    if(index<0 || index >=bounds){
        return -1;
    }
    return index;
}

void menu(){
    puts("1. Add robo detail");
    puts("2. Add robo detail description.");
    puts("3. Read robo detail description.");
    puts("4. Run robo detail action.");
    puts("5. Change robo description.");
    puts("6. Delete detail.");
    puts(">> ");
}

int main(){
    setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
    char buffer [0x100]={0};
    while(1){
        menu();
        int option = get_idx(7);
        switch(option){
        case 1:
        {
            puts("Enter index from 0 to 255.");
            puts(">> ");
            int idx = get_idx(0x100);
            if(idx==-1)
                break;
            if(!robotics[idx].allocated){
                robotics[idx].robo=create_detail();
                robotics[idx].allocated=1;
            }
            puts("Sucesfully created detail.");
        }
        break;
        case 2:
        {   
            puts("Enter your description");
            puts(">>");
            fgets(buffer,0x100,stdin);
            puts("Enter index from 0 to 255.");
            puts(">> ");
            int idx = get_idx(0x100);
            if(idx==-1)
                break;

            if(robotics[idx].allocated){
                wonderful_pointer msg = create_message(buffer, strlen(buffer));
                add_message(robotics[idx].robo,msg,strlen(buffer));
                puts("Sucesfully added description.");

            }
            else {
                puts("Detail not exist. :(");
            }
        }
        break;
        case 3:
        {
            puts("Enter index from 0 to 255.");
            puts(">> ");
            int idx = get_idx(0x100);
            if(idx==-1)
                break;
            if(robotics[idx].allocated){
                read_message(robotics[idx].robo, buffer);
                puts("Message is:");
                puts(buffer);
            }
            else {
                puts("Detail not exist.");
            }
        }
        break;
        case 4:
        {
            puts("Enter index from 0 to 255.");
            puts(">> ");
            int idx = get_idx(0x100);
            if(idx==-1)
                break;
            if(robotics[idx].allocated){
                run_action(robotics[idx].robo);
            }
            else {
                puts("Detail not exist.");
            }
        }
        break;
        case 5:
        {
            puts("Enter index from 0 to 255");
            puts(">>");
            int idx = get_idx(0x100);
            if(idx==-1)
                break;
            if(robotics[idx].allocated){
                puts("Enter your description");
                puts(">>");
                fgets(buffer,0x100,stdin);
                change_message(robotics[idx].robo, buffer);
            }
            else {
                puts("Detail not exist");
            }
        }
        break;
        case 6:
        {
            puts("Enter index from 0 to 255.");
            puts(">> ");
            int idx = get_idx(0x100);
            if(idx==-1)
                break;
            if(robotics[idx].robo){
                destroy_detail(robotics[idx].robo);
                puts("Sucesfully destroyed detail");
                robotics[idx].allocated=0;
            }
            else{
                puts("Detail not exist.");
            }
        }
        break;
        default:
        puts("Unknown option");
        break;
        }
    }
    return 0;
}
