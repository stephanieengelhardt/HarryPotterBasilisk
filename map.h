
#ifndef MAP_H
#define MAP_H
#include <vector>
#include <cstdlib>
#include "snake.h"

typedef struct  map{
  snake *s;
  std:: vector<egg> Eggs;
  int traps[50][50];
  int EG[50][50];
  int numTraps;
  int numEggs;
}map_t;

void new_map(map_t *m);
void delete_map(map_t *m);
void printMap(map_t *m);
void do_move(map_t *m);
void move_eggs(map_t *m);
void io_queue_message(const char *format, ...);
#endif
