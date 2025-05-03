#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <string.h>

#define FRAMERATE 30

struct termios enableRAWmode(){
  struct termios oldConf;
  struct termios rawConf;
  
  tcgetattr(STDIN_FILENO, &oldConf);
  tcgetattr(STDIN_FILENO, &rawConf);

  rawConf.c_lflag &= ~(ICANON | ECHO);

  tcsetattr(STDIN_FILENO,TCSANOW ,&rawConf);
  printf("\033[?25l");

  fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

  return oldConf;
};

struct termios escapeRAWmode(struct termios oldConf){
  struct termios rawConf;
  tcgetattr(STDIN_FILENO, &rawConf);

  tcsetattr(STDIN_FILENO,TCSANOW ,&oldConf);
  printf("\033[2J\033[H\033[?25h");
  
  return rawConf;
}
  

void clearScreen(){
  printf("\033[2J\033[H");
  fflush(stdout);
}

void infoPrint(char *gameName, char key, int a, clock_t deltaTmicro){
  printf("somethinf button: %c\t%s\ttps %f\tfps: %.2f",key, gameName,
	 (float)a*deltaTmicro/1000000.0, 1000000.0/deltaTmicro);
  fflush(stdout);  
}
void update(){}
void draw(){}

int main() {
  
  struct termios oldConf = enableRAWmode();
  clock_t nowClock, pastClock, deltaTmacro;
  float seconds_in_micro=0, nanoseconds_in_micro=0, timeNow=0, timePast=0;
  char key;
  char gameName[32]="Game Name";
  ssize_t readError;
  int a=0;

  printf("\033[2J\033[H");
  pastClock = clock();
  
  while(1){

    nowClock = clock();
    read(STDIN_FILENO, &key, 1);

    
    if(key=='q')
      break;

    deltaTmacro = 1000000*(nowClock - pastClock)/CLOCKS_PER_SEC;
    a++;
    
    if(deltaTmacro>(float)1000000/FRAMERATE){
      pastClock = clock();
      clearScreen();
      infoPrint(gameName, key, a, deltaTmacro);
      update();
      draw();
      a=0;
      }

  }
  
  escapeRAWmode(oldConf);

  return 0;
}
