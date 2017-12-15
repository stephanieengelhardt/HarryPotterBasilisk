#include "snake.h"
#include "map.h"
#include <curses.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <err.h>
#include <time.h>

using namespace std;
//This code is given from my professor
typedef struct io_message{
char msg[71];
  struct io_message *next;
} io_message_t;
static io_message_t *io_head, *io_tail;

void io_queue_message(const char *format, ...)
{
  io_message_t *tmp;
  va_list ap;
  if (!(tmp = (io_message_t *) malloc(sizeof (*tmp)))) {
    perror("malloc");
    exit(1);
  }
  tmp->next = NULL;
  va_start(ap, format);
  vsnprintf(tmp->msg, sizeof (tmp->msg), format, ap);
  va_end(ap);
  if (!io_head) {
    io_head = io_tail = tmp;
  } else {
    io_tail->next = tmp;
    io_tail = tmp;
  }
}

static void io_print_message_queue(uint32_t y, uint32_t x)
{
  while (io_head) {
    io_tail = io_head;
    //attron(COLOR_PAIR(COLOR_CYAN));
    mvprintw(y, x, "%-80s", io_head->msg);
    //attroff(COLOR_PAIR(COLOR_CYAN));
    io_head = io_head->next;
    free(io_tail);
  }
  io_tail = NULL;
}

//Starting my own code
void new_map(map_t *m){
  int i,k, y, x;
  snake *sn= new snake();
  y=(rand()%46)+1;
  x=(rand()%46)+1;
  snake_set_alive(sn, 1);
  snake_set_x(sn,x);
  snake_set_y(sn,y);
  m->s=sn;
  m->numEggs=0;
  m->numTraps=20;
  for(i=0; i<50; i++){
    for(k=0; k<50; k++){
      m->EG[i][k]=0;
      m->traps[i][k]=0;
     }
   }
  for(i=0; i<m->numTraps; i++){
    y=rand()%46 +1;
    x=rand()%46 +1;
    while(m->traps[y][x]==1 ||( m->s->xposition==x && m->s->yposition==y)){
      y=rand()%46 +1;
      x=rand()%46 +1;
    }
    m->traps[y][x]=1;
  }
  
}

void delete_map(map_t *m){
  delete(m->s);
  int i;
  /*for(i=0; i<m->numEggs; i++){
    
    free(m->Eggs[i]);
    }*/
}

void do_move(map_t *m){
  move_eggs(m);
  fflush(stdout);
  int i;
  fd_set readfs;
  struct timeval tv;

    FD_ZERO(&readfs);
    FD_SET(0, &readfs);
    tv.tv_sec=0;
    tv.tv_usec=300000;
    switch(select(1, &readfs,NULL, NULL, &tv)){
    case -1:
    case 0:
      if(m->s->yOldPosition > m->s->yposition){
	snake_set_oldy(m->s, m->s->yposition);
	snake_set_y(m->s, (m->s->yposition)-1);
      }
      else{
	snake_set_oldy(m->s, m->s->yposition);
	  snake_set_y(m->s, (m->s->yposition)+1);
      }
      if(m->s->xOldPosition > m->s->xposition){
	  snake_set_oldx(m->s, m->s->xposition);
	  snake_set_x(m->s, (m->s->xposition)-1);
      }
      else{
	snake_set_oldx(m->s, m->s->xposition);
	snake_set_x(m->s, (m->s->xposition)+1);
      }
      break;
    case 1:
      switch(i=getch()){
      case KEY_LEFT:
      case 'h':
	snake_set_oldx(m->s, m->s->xposition);
	snake_set_x(m->s, (m->s->xposition)-1);
	break;
      case KEY_DOWN:
      case 'j':
	snake_set_oldy(m->s, m->s->yposition);
	snake_set_y(m->s, (m->s->yposition)+1);	
	break;
      case KEY_RIGHT:
      case 'l':
	snake_set_oldx(m->s, m->s->xposition);
	snake_set_x(m->s, (m->s->xposition)+1);	
	break;
      case KEY_UP:
      case 'k':
	snake_set_oldy(m->s, m->s->yposition);
	snake_set_y(m->s, (m->s->yposition)-1);	
	break;
      }
      break;
    }
    if(m->s->xposition==0 || m->s->xposition==48
       || m->s->yposition==0 || m->s->yposition==48){
      snake_set_alive(m->s, 0);
    }
    for(i=0; i<(m->numEggs); i++){
      if(m->Eggs[i].xposition==m->s->xposition
	 && m->Eggs[i].yposition==m->s->yposition){
	snake_set_alive(m->s, 0);
      }
    }
}
const char *mudbloods[]={
  "Hermione Granger",
  "Lily Potter",
  "Colin Creevey",
  "Mary Cattermole",
  "Moaning Myrtle",
  "Ted Tonks",
  "Justin Finch-Fletchley",
  "Mary Cattermole",
  "Dennis Creevey",
  "Dirk Cresswell",
  "Kendra Dumbledore",
  "Kevin Entwhistle",
  "Johannes Jonker",
  "Nobby Leach",
  "Garrick Ollivander's mother",
  "Tertius",
  "Donaghan Tremlett",
  "Wandless"
};
void move_eggs(map_t *m){
  int i,k;
  if(m->traps[m->s->yposition][m->s->xposition]){
    k=rand()%18;
    io_queue_message("You petrified %s.", mudbloods[k]);
   
    egg *e=new egg();
    e->xposition=m->s->xposition;
    e->yposition=m->s->yposition;
    if(m->numEggs==0){
      (m->Eggs).insert(m->Eggs.begin(), *e);
    }
    else{
     std::vector<egg>:: iterator it= m->Eggs.begin();
     (m->Eggs).insert(it+1,*e);
    }
    m->traps[m->s->yposition][m->s->xposition]=0;
    m->numTraps--;
    m->EG[e->yposition][e->xposition]=1;
    m->numEggs++;
  }
  else{
   
    for(i=0; i<m->numEggs; i++){
      if(i==0){
	m->EG[m->Eggs[i].yposition][m->Eggs[i].xposition]=0;
	(m->Eggs[i]).yposition=(m->Eggs[i+1]).yposition;
	(m->Eggs[i]).xposition=(m->Eggs[i+1]).xposition;
	m->EG[m->Eggs[i].yposition][m->Eggs[i].xposition]=1;
      }
      if(i==(m->numEggs -1)){
	m->Eggs[i].yposition=m->s->yposition;
	m->Eggs[i].xposition=m->s->xposition;
	m->EG[m->Eggs[i].yposition][m->Eggs[i].xposition]=1;
      }
      else{
	(m->Eggs[i]).yposition=(m->Eggs[i+1]).yposition;
	(m->Eggs[i]).xposition=(m->Eggs[i+1]).xposition;
	m->EG[m->Eggs[i].yposition][m->Eggs[i].xposition]=1;
      }
    }
  }
  
}

 void printMap(map_t *m){
   if(m->numEggs==0){
   clear();
   }
   init_pair(2, COLOR_GREEN, COLOR_BLACK);
   init_pair(6, COLOR_CYAN, COLOR_BLACK);
   int i,k;

   start_color();
   for(i=0; i<50; i++){
     for(k=0; k<50; k++){
       io_print_message_queue(1,51);
       if(i==0 && k==9){
	 mvaddch(i,k, ' ');
       }
       else if(i==0 && k==10){
	 attron(COLOR_PAIR(6));
	 mvaddch(i,k, 'C');
       }
       else if(i==0 && k==11){
	 mvaddch(i,k, 'h');
       }
       else if(i==0 && k==12){
	 mvaddch(i,k, 'a');
       }
       else if(i==0 && k==13){
	   mvaddch(i,k, 'm');
       }
       else if(i==0 && k==14){
	 mvaddch(i,k, 'b');
       }
       else if(i==0 && k==15){
	 mvaddch(i,k, 'e');
       }
       else if(i==0 && k==16){
	 mvaddch(i,k, 'r');
       }
       else if(i==0 && k==17){
	 mvaddch(i,k, ' ');
       }
       else if(i==0 && k==18){
	 mvaddch(i,k, 'o');
       }
       else if(i==0 && k==19){
	 mvaddch(i,k, 'f');
       }
       else if(i==0 && k==20){
	 mvaddch(i,k, ' ');
       }
       else if(i==0 && k==21){
	 mvaddch(i,k, 'S');
       }
       else if(i==0 && k==22){
	 mvaddch(i,k, 'e');
       }
       else if(i==0 && k==23){
	 mvaddch(i,k, 'c');
       }
       else if(i==0 && k==24){
	 mvaddch(i,k, 'r');
       }
       else if(i==0 && k==25){
	 mvaddch(i,k, 'e');
       }
       else if(i==0 && k==26){
	 mvaddch(i,k, 't');
       }
       else if(i==0 && k==27){
	 mvaddch(i,k, 's');
       }
       else if(i==0 && k==28){
	 mvaddch(i,k, ' ');
	 attroff(COLOR_PAIR(6));
       }
	      
       else if((i==0 && k!=49) || (k==0 && i!=49) || (i==48 && k!=49) || (k==48 && i!=49)){ 
	 mvaddch(i,k, 'X');
       }
       else if(m->s->yposition==i && m->s->xposition==k){
	 //green
	 attron(COLOR_PAIR(2));
	 mvaddch(i,k, 'S');
	 attroff(COLOR_PAIR(2));
       }
       
       else if(m->traps[i][k]==1){
	 mvaddch(i,k,'m');
       }
       else if(m->EG[i][k]==1){
	 attron(COLOR_PAIR(2));
	   mvaddch(i,k, '0');
	   attroff(COLOR_PAIR(2));
       }
       else{
	 mvaddch(i,k, ' ');
       }
       
     }
   }
 }
