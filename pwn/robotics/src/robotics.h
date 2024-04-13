#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "./heap/heap.h"

typedef struct SafeRobo{
    wonderful_pointer robo;
    int allocated;
}SafeRobo;

typedef struct RoboDetail{
    int len;
    void* action;
    wonderful_pointer description;
}RoboDetail;

wonderful_pointer create_detail();

void destroy_detail(wonderful_pointer robo);

wonderful_pointer create_message(char* buffer,int len);

void add_message(wonderful_pointer robo,wonderful_pointer msg,int len);

void read_message(wonderful_pointer robo,char* buffer);

void change_message(wonderful_pointer robo,char* buffer);

void run_action(wonderful_pointer robo);

RoboDetail getRobo(wonderful_pointer robo);

void saveRobo(wonderful_pointer robo,RoboDetail* rob);


