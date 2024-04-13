#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>

void logic();
void menu();
void writeshell();
void drop_address(void){
  char local_1018 [4108];
  int local_c;
  
  local_c = open("/proc/self/maps",0);
  memset(local_1018,0,0x1000);
  read(local_c,local_1018,0x1000);
  char * line = strtok(local_1018, "\n");
  while (line != NULL){
    if (strstr(line, "rwx")!=0){
      printf("%s\n", line);
      break;
    }
    line = strtok(NULL, "\n");
  }
  return;
}

void funfunc(){
  printf("You can have some fun here :D\n");
  char buf[32];
  read(0, buf, 0x100);
  return;
}

int main(void){
  setvbuf(stdin,(char *)0x0,2,0);
  setvbuf(stdout,(char *)0x0,2,0);
  write(1,"Hi, you can do a lot here, hehe :D\n",35);
  while (1){
    menu();
    int ch;
    int stat = scanf("%d", &ch);
    if (stat != 1){
      return 0;
    }
    switch(ch){
      case 1:{
        writeshell();
        break;
             }
      case 2:
        funfunc();
        break;
      case 0:
        return 0;
    }

  }
  
  return 0;
}

void menu(){
  printf("1. write shell\n2. do fun staff\n0.exit\n");
}

void writeshell(void){
  printf("You can write some shell here XD\n");
  void * buf =(void *) mmap(0x0,28,7,0x22,-1,0);
  read(0,buf,28);
  return;
}

void fun(void * sc){
  return;
}
