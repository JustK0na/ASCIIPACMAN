#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(){

  printf("SINTABLE\n");
  float rad = 0;
  for(int i=0; i<=360; i++){
    if(i%10==0&&i!=0)
      printf("\n");
    rad = (i * M_PI) / 180;
    printf("%f,",sin(rad));
  }

  
  return 0;

}
