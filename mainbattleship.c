#include "battleship.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv){
  mainscrn();
  srand(time(0));
  int size=8, maxshots, err;
  err = parseArgs(argc,argv,&size,&maxshots);

  //Check that users input is valid
  if(err == -1) printUsage();

  else{
    
  //Create new Board
  board *b;
  b = createBoard(size);

  //Arrange Fleet
  randomFleetArrangement(b);
  printBoard(b);

  play(b,maxshots);
  }
}
