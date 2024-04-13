#include "robotics.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "./heap/heap.h"

void predefined_action(){
    puts("Bzzzzzzzz");
}

RoboDetail getRobo(wonderful_pointer robo){
    RoboDetail rob;
    safe_read(robo, (char *)&rob, sizeof(RoboDetail));
    return rob;
}

void saveRobo(wonderful_pointer robo, RoboDetail *rob){
    safe_write(robo, (char *)rob, sizeof(RoboDetail));
    return;
}

wonderful_pointer create_detail(){
    wonderful_pointer detail = wonderful_malloc(sizeof(RoboDetail));
    RoboDetail robo;
    robo.len = 0;
    robo.action = (void*)predefined_action;
    robo.description = 0;
    saveRobo(detail, &robo);
    return detail;
}

void run_action(wonderful_pointer robo){
    RoboDetail rob = getRobo(robo);
    void (*func_ptr)(void) =rob.action;
    func_ptr();
    return;
}

wonderful_pointer create_message(char*buffer, int len){
    wonderful_pointer msg = wonderful_malloc(len);
    safe_write(msg, buffer, len);
    return msg;
}

void add_message(wonderful_pointer robo, wonderful_pointer msg,int len){
    RoboDetail rob = getRobo(robo);
    rob.len = len;
    if(rob.description!=0)
        wonderful_free(rob.description);
    rob.description = msg;
    saveRobo(robo, &rob);
    return;
}

void change_message(wonderful_pointer robo, char *buffer){
    RoboDetail rob = getRobo(robo);
    if(rob.description!=0){
        safe_write(rob.description, buffer, rob.len);
    }
    return;
}

void destroy_detail(wonderful_pointer robo){
    RoboDetail rob = getRobo(robo);
    if(rob.description)
        wonderful_free(rob.description);
    saveRobo(robo, &rob);
    wonderful_free(robo);
    return;
}

void read_message(wonderful_pointer robo, char *buffer){
    RoboDetail rob = getRobo(robo);
    safe_read(rob.description,buffer,rob.len);
    return;
}
