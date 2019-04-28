#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "battleship.h"

//Associates the word for each color with its approprate ASCII color equivalent
#define RED   "\x1B[31m"
#define GRN   "\x1B[92m"
#define BLU   "\x1B[94m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define YEL   "\x1B[93m"
#define BOLD  "\x1B[1m"
#define RSTCOL "\x1B[0m"

struct _board{
  int size;
  int *data;
  int unhit;
  int *tracker;
  int cells_with_ships;
  int carrier;
  int battleship;
  int cruiser;
  int submarine;
};

void printUsage(){
  printf(YEL BOLD "Error!"RSTCOL" Invalid input. You must input in the following format:\n");
  printf(YEL"Size of board:"RSTCOL" integer between 5 and 20\n");
  printf(YEL"Max Shots:"RSTCOL" Integer between 12 and n^2 - 1 (where n is the size of the board)\n");
}

void mainScreen(){
  printf(RED"\n~~~~~~~~~~~~~~~~~~~~~\n"RSTCOL);
  printf(BOLD YEL "WELCOME TO BATTLESHIP"RSTCOL);
  printf(RED BOLD"\n~~~~~~~~~~~~~~~~~~~~~\n"RSTCOL);
}
board * createBoard(int size) {
  int i; board * b;
  if(size <= 0) return NULL;
   b = (board *) malloc(sizeof(board));
   if(!b) return NULL;
   b->size = size;
   b->data = (int*) malloc(size*size*sizeof(int));
   b->tracker = (int*)malloc(size*size*sizeof(int));
   if(!b->data) {
     free(b);
     return NULL;
   }
   if(!b->tracker) {
     free(b);
     return NULL;
   }
   for(i = 0; i < size*size; i++){
     b->data[i] = 0;
     b->tracker[i] = 0;
   }
  return b;
}

int getTracker(board*b, int i, int j) {
   return b->tracker[(j-1) * b->size + i];
}
 
int get(board *b, int row, int col){
  return b->data[(col-1)*b->size+row];
}

void setTracker(board * b, int row, int col, double val) {
  b->tracker[(col-1) * b->size + row] = val;
}

void set(board * b, int row, int col, double val) {
  b->data[(col-1) * b->size + row] = val;
}

void printBoard(board*b) {
  int i, j = 0;
  for(i = 1; i<=b->size; i++)
    {
      printf("\n");
      for(j=1;j<=b->size;j++){
      if(getTracker(b, i, j) == 0){
	printf(".  ");
      }
      else if(getTracker(b,i,j)==1){
	printf("O  ");
      }
      else if(getTracker(b,i,j)==-1){
	printf("X  ");
      }
      }
    }
  printf("\n\n");
}

void revealBoard(board*b){
  int i, j;
  for(i = 1; i <= b->size; i++){
    printf("\n");
    for(j=1;j<=b->size;j++){
      printf("%d ", get(b,i,j));
    }
  }
  printf("\n\n");
}

int parseArgs(int argc, char ** argv,int *size, int *maxshots) {
  if (argc < 2 || argc > 3){
	printUsage();
	return -1;
      }
  else if (argc == 2){
    if(sscanf(argv[1],"%d",maxshots) != 1 || *maxshots<12||*maxshots>((*size)*(*size))-1){
      printUsage();
      return -1;
    }
  }
  else if(argc == 3){
    if ( sscanf(argv[2],"%d",maxshots) != 1 || *maxshots<12||*maxshots>((*size)*(*size)-1)){
      printUsage();
      return -1;
    }
    if(sscanf(argv[1],"%d",size) != 1 || *size<5 || *size > 20) {
	    printUsage();
	    return -1;
      }
  }
  return 0;
}

void deleteBoard(board*b) {
 if(b) {
   free(b->data);
   free(b->tracker);
   free(b);
  }
}

void arrangeCarrier(board *b){
  int dir,randrow,randcol;
  while(1){
  dir = rand() % 4; 
  if(dir == 0){ 
    randrow = rand() % (b->size - 4 + 1) + 4;
    randcol = rand() % (b->size - 1 + 1) + 1;
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow-1,randcol) !=0 || get(b,randrow-2,randcol) !=0 || get(b,randrow-3,randcol) !=0 ) continue;
    set(b,randrow,randcol,1);
    set(b,randrow-1,randcol,1);
    set(b,randrow-2,randcol,1);
    set(b,randrow-3,randcol,1);
    break; 
  }
  else if(dir == 1){
    randrow = rand() % ((b->size - 3) - 1 + 1) + 1; 
    randcol = rand() % (b->size - 1 + 1) + 1;  
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow+1,randcol) !=0 || get(b,randrow+2,randcol) !=0 || get(b,randrow+3,randcol) !=0 ) continue;
    set(b,randrow,randcol,1);
    set(b,randrow+1,randcol,1);
    set(b,randrow+2,randcol,1);
    set(b,randrow+3,randcol,1);
    break; 
  }
   else if(dir == 2){  
    randrow = rand() % (b->size - 1 + 1) + 1;  
    randcol = rand() % (b->size - 4 + 1) + 4;  
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow,randcol-1) !=0 || get(b,randrow,randcol-2) !=0 || get(b,randrow,randcol-3) !=0 ) continue;
    set(b,randrow,randcol,1);
    set(b,randrow,randcol-1,1);
    set(b,randrow,randcol-2,1);
    set(b,randrow,randcol-3,1);
    break; 
  }
   else if(dir == 3){ 
    randrow = rand() % (b->size - 1 + 1) + 1;  
    randcol = rand() % ((b->size-3) - 1 + 1) + 1;
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow,randcol+1) !=0 || get(b,randrow,randcol+2) !=0 || get(b,randrow,randcol+3) !=0 ) continue;
    set(b,randrow,randcol,1);
    set(b,randrow,randcol+1,1);
    set(b,randrow,randcol+2,1);
    set(b,randrow,randcol+3,1);
    break; 
    }
  }
}

void arrangeBattleship(board *b){
  int dir,randrow,randcol;
  while(1){
  dir = rand() % 4;  
  if(dir == 0){ 
    randrow = rand() % (b->size - 3 + 1) + 3; 
    randcol = rand() % (b->size - 1 + 1) + 1;
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow-1,randcol) !=0 || get(b,randrow-2,randcol) !=0) continue;
    set(b,randrow,randcol,2);
    set(b,randrow-1,randcol,2);
    set(b,randrow-2,randcol,2);
    break; 
  }
  else if(dir == 1){ 
    randrow = rand() % ((b->size - 2) - 1 + 1) + 1;  
    randcol = rand() % (b->size - 1 + 1) + 1;  
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow+1,randcol) !=0 || get(b,randrow+2,randcol) !=0) continue;
    set(b,randrow,randcol,2);
    set(b,randrow+1,randcol,2);
    set(b,randrow+2,randcol,2);
    break; 
  }
   else if(dir == 2){  
     randrow = rand() % (b->size - 1 + 1) + 1;   
     randcol = rand() % (b->size - 3 + 1) + 3;   
     if (get(b,randrow,randcol) !=0 ||  get(b,randrow,randcol-1) !=0 || get(b,randrow,randcol-2) !=0) continue;
     set(b,randrow,randcol,2);
     set(b,randrow,randcol-1,2);
     set(b,randrow,randcol-2,2);
     break; 
  }
   else if(dir == 3){  
     randrow = rand() % (b->size - 1 + 1) + 1;  
     randcol = rand() % ((b->size-2) - 1 + 1) + 1;   
     if (get(b,randrow,randcol) !=0 ||  get(b,randrow,randcol+1) !=0 || get(b,randrow,randcol+2) !=0) continue;
     set(b,randrow,randcol,2);
     set(b,randrow,randcol+1,2);
     set(b,randrow,randcol+2,2);
     break;
    }
  }
}

void arrangeCruiser(board *b){
  int dir,randrow,randcol;
  while(1){
  dir = rand() % 4; 
  if(dir == 0){ 
   randrow = rand() % (b->size - 3 + 1) + 3;   
   randcol = rand() % (b->size - 1 + 1) + 1; 
   if (get(b,randrow,randcol) !=0 ||  get(b,randrow-1,randcol) !=0 || get(b,randrow-2,randcol) !=0) continue;
   set(b,randrow,randcol,3);
   set(b,randrow-1,randcol,3);
   set(b,randrow-2,randcol,3);
   break;  
  }
  else if(dir == 1){ 
   randrow = rand() % ((b->size - 2) - 1 + 1) + 1;  
   randcol = rand() % (b->size - 1 + 1) + 1;   
   if (get(b,randrow,randcol) !=0 ||  get(b,randrow+1,randcol) !=0 || get(b,randrow+2,randcol) !=0) continue;
   set(b,randrow,randcol,3);
   set(b,randrow+1,randcol,3);
   set(b,randrow+2,randcol,3);
   break;  
  }
   else if(dir == 2){  
    randrow = rand() % (b->size - 1 + 1) + 1;  
    randcol = rand() % (b->size - 3 + 1) + 3;   
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow,randcol-1) !=0 || get(b,randrow,randcol-2) !=0) continue;
    set(b,randrow,randcol,3);
    set(b,randrow,randcol-1,3);
    set(b,randrow,randcol-2,3);
    break; 
  }
   else if(dir == 3){ 
    randrow = rand() % (b->size - 1 + 1) + 1;  
    randcol = rand() % ((b->size-2) - 1 + 1) + 1;  
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow,randcol+1) !=0 || get(b,randrow,randcol+2) !=0) continue;
    set(b,randrow,randcol,3);
    set(b,randrow,randcol+1,3);
    set(b,randrow,randcol+2,3);
    break; 
    }
  }
}

void arrangeSubmarine(board *b){
  int dir,randrow,randcol;
  while(1){
  dir = rand() % 4; 

  if(dir == 0){ 
    randrow = rand() % (b->size - 2 + 1) + 2;
    randcol = rand() % (b->size - 1 + 1) + 1;   
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow-1,randcol) !=0) continue;
    set(b,randrow,randcol,4);
    set(b,randrow-1,randcol,4);
    break; 
  }
  else if(dir == 1){
    randrow = rand() % ((b->size - 1) - 1 + 1) + 1; 
    randcol = rand() % (b->size - 1 + 1) + 1;  
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow+1,randcol) !=0) continue;
    set(b,randrow,randcol,4);
    set(b,randrow+1,randcol,4);
    break;  
  }
   else if(dir == 2){ 
    randrow = rand() % (b->size - 1 + 1) + 1;  
    randcol = rand() % (b->size - 2 + 1) + 2;   
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow,randcol-1) !=0) continue;
    set(b,randrow,randcol,4);
    set(b,randrow,randcol-1,4);;
    break;  
  }
   else if(dir == 3){ 
    randrow = rand() % (b->size - 1 + 1) + 1;
    randcol = rand() % ((b->size-1) - 1 + 1) + 1;
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow,randcol+1) !=0) continue;
    set(b,randrow,randcol,4);
    set(b,randrow,randcol+1,4);
    break; 
    }
  }
}

void randomFleetArrangement (board * b){
 arrangeCarrier(b);
 arrangeBattleship(b);
 arrangeCruiser(b);
 arrangeSubmarine(b);
 b->unhit = 12;
 b->carrier = 4;
 b->battleship = 3;
 b->cruiser = 3;
 b->submarine = 2;
}

void readTargets(board * b, int * targetRow, int * targetCol){
  char cell[4];
  int row;
  char col;
  int ret;
  int size = b->size;
  char *p;

  while(1){
    printf("Enter target cell: ");
    if(fgets(cell,sizeof(cell),stdin) != NULL) {

      if ((p=strchr(cell,'\n'))) {
	  *p=0;
	}
	else {
	scanf("%*[^\n]");
	scanf("%*c");
	}
      ret = sscanf(cell,"%d%c",&row,&col);
      if (ret != 2 || col<97 || col>122){
      printf(YEL BOLD "Error! "RSTCOL"You must input the number of rows followed by the letter column.\n"); 
      continue;
      }
      if (row<1 || row > size) {
      printf(YEL BOLD "Error! "RSTCOL" You must input a positive number of rows followed by the letter column.\n"RSTCOL); 
      continue;
      }
      if (col-96 > size) {
      printf(YEL BOLD "Error! "RSTCOL" You must input a number within the range of the board size\n"RSTCOL); 
      continue; 
      }
      if (getTracker(b,row,col-96) != 0) {
        printf("You already shot this target!\n");
        continue;
      }
      *targetRow = row;
      *targetCol = col - 96;
      break;
    } 
    else {
      printf(YEL BOLD "Error! "RSTCOL"You must input the number of rows followed by the letter column.\n"); 
      continue;
    }      
  }
}

void play(board *b, int maxshots) {
 int row, col;
 int remain = maxshots;
 int a1 = 0;
 int a2 = 0;
 int a3 = 0;
 int a4 = 0;

 while (b->unhit > 0 && remain > 0 && (remain >= b->unhit)) {
  printBoard(b);
  printf("You have %d shots remaining\n",remain);
  readTargets(b,&row,&col);
  if (get(b,row,col) == 0) {
    printf("Miss!\n");
    setTracker(b,row,col,-1);
    remain--;
  }
   if (get(b,row,col) == 1) {
    printf("Hit!\n");
    setTracker(b,row,col,1);
    b->carrier--;
    b->unhit--;
    remain--;
   }
  if (get(b,row,col) == 2) {
    printf(YEL"Hit!\n"RSTCOL);
    setTracker(b,row,col,1);
    b->battleship--;
    b->unhit--;
    remain--;
  }
  if (get(b,row,col) == 3) {
    printf(YEL"Hit!\n"RSTCOL);
    setTracker(b,row,col,1);
    b->cruiser--;
    b->unhit--;
    remain--;
  }
  if (get(b,row,col) == 4) {
    printf(YEL"Hit!\n"RSTCOL);
    setTracker(b,row,col,1);
    b->submarine--;
    b->unhit--;
    remain--;
   }
  if (b->carrier == 0 && a1 == 0 ) {
    printf(RED "\nYou sunk my "BOLD" carrier"RSTCOL RED"!\n" RSTCOL);
    a1 = 1;
  }
   if (b->battleship == 0 && a2 == 0 ) {
    printf(RED "\nYou sunk my "BOLD" battleship"RSTCOL RED"!\n" RSTCOL);
    a2 = 1;
  }
  if (b->cruiser == 0 && a3 == 0 ) {
    printf(RED "\nYou sunk my "BOLD" cruiser"RSTCOL RED"!\n" RSTCOL);
    a3 = 1;
  }
  if (b->submarine == 0 && a4 == 0 ) {
    printf(RED "\nYou sunk my "BOLD" submarine"RSTCOL RED"!\n" RSTCOL);
    a4 = 1;
  }
 }
 if (remain == 0 && b->unhit > 0) {
   printf(BLU BOLD"\nYOU LOSE - GAME OVER - YOU RAN OUT OF SHOTS! \n"RSTCOL); 
 }
 if (remain < b->unhit && b->unhit>0 && remain>0) {
   printf(BLU BOLD"\nYOU LOSE - GAME OVER - NOT ENOUGH SHOTS REMAINING! \n"RSTCOL);
 }
 if (b->unhit == 0 && remain > 0) {
   printf(RED BOLD"\nYOU WIN - GAME OVER - CONGRATULAIONS!\n"RSTCOL);
 }
}

