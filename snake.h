#ifndef SNAKE_H
#define SNAKE_H
#include <stdint.h>

class snake{
 public:
  snake(){};
  int xposition, yposition;
  int xOldPosition, yOldPosition;
  int32_t alive;
};

class egg{
 public:
  egg(){};
  ~egg(){};
  int xposition, yposition;
};

void snake_set_y(snake *s, int16_t y);
void snake_set_x(snake *s, int16_t x);
void snake_set_oldy(snake *s, int16_t y);
void snake_set_oldx(snake *s, int16_t x);
void snake_set_alive(snake *s, int16_t al);
int snake_alive(const snake *s);

#endif

