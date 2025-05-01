#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


struct termios enableRAWmode(){
  struct termios oldConf;
  struct termios rawConf;
  
  tcgetattr(STDIN_FILENO, &oldConf);
  tcgetattr(STDIN_FILENO, &rawConf);

  rawConf.c_lflag &= ~(ICANON | ECHO);

  tcsetattr(STDIN_FILENO,TCSANOW ,&rawConf);
  printf("\033[?25l");

  //fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

  return oldConf;
};

struct termios escapeRAWmode(struct termios oldConf){
  struct termios rawConf;
  tcgetattr(STDIN_FILENO, &rawConf);

  tcsetattr(STDIN_FILENO,TCSANOW ,&oldConf);
  printf("\033[2J\033[H\033[?25h");
  
  return rawConf;
}


int main() {

  struct termios oldConf = enableRAWmode();
  int a = 0;  

  char key;
  while (1) {
    a++;
    if(read(STDIN_FILENO, &key, 1)==-1){
      perror("couldn't read");
      exit(-1);
    }
    if(key=='q')
      break;

    printf("\033[2J\033[H");
    printf("somethinf %d", a);
    fflush(stdout);
  }

  escapeRAWmode(oldConf);

  return 0;
}
