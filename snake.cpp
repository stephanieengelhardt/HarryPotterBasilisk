#include "snake.h"
#include <stdlib.h>

void snake_set_y(snake *s, int16_t y){
  s->yposition=y;
}

void snake_set_x(snake *s, int16_t x){
  s->xposition=x;
}

void snake_set_alive(snake *s, int16_t al){
  s->alive=al;
}
void snake_set_oldy(snake *s, int16_t y){
  s->yOldPosition=y;
}
void snake_set_oldx(snake *s, int16_t x){
  s->xOldPosition=x;
}
int snake_alive(const snake *s){
  return s->alive;
}

