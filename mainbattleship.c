#include "battleship.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv){
  void mainScreen();
  srand(time(0));
  int size=8, maxshots, err;
  err = parseArgs(argc,argv,&size,&maxshots);
  if(err == -1) printUsage();
  else{
  board *b;
  b = createBoard(size);
  randomFleetArrangement(b);
  play(b,maxshots);
  }
}
