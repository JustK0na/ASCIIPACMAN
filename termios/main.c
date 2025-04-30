#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>

struct termios old_tio, new_tio;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &= ~(ICANON | ECHO); // Disable line buffering & echo
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
    atexit(disableRawMode);
}

char simpleMap[6][6]={'#','#','#','#','#','#',
                      '#','O','O','O','O','#',
                      '#','O','O','O','O','#',
                      '#','O','O','O','O','#',
                      '#','O','O','O','O','#',
                      '#','#','#','#','#','#',};


void inputHandle(char c, int* a, int* b){

  printf("a: [%d],\tb: [%d]\n", *a, *b);
  if(c=='a'){
	simpleMap[*a][*b] = 'O';	
	*b--;
	simpleMap[*a][*b] = '@';
      }

  if(c=='d'){
	simpleMap[*a][*b] = 'O';	
	*b++;
	simpleMap[*a][*b] = '@';
      }
  if(c=='w'){
	simpleMap[*a][*b] = 'O';	
	*a--;
	simpleMap[*a][*b] = '@';
      }
  if(c=='s'){
	simpleMap[*a][*b] = 'O';	
	*a++;
	simpleMap[*a][*b] = '@';
      } 

}
int main() {
    enableRawMode();
    srand(time(NULL));
    char c;
    printf("Press 'q' to quit.\n");
    	int a = rand()%4+1;
	int b = rand()%4+1;
    while (1) {
      write(STDOUT_FILENO, "\033[2J\033[H", 7);

      /*      for(int i=0; i<6; i++){

	for(int j=0; j<6; j++){
	  printf("%c", simpleMap[i][j]);
	}
	printf("\n");
	//	  printf("You pressed: %c\n", c);
      }*/

      read(STDIN_FILENO, &c, 1);
      inputHandle(c, &a, &b);
      usleep(500000);
    }
    return 0;
}
