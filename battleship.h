#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct _board{
  int size;
  int *data;
  int cells_with_ships;
  int carrier;
  int battleship;
  int cruiser;
  int submarine;
};

