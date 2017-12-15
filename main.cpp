#include "snake.h"
#include "map.h"
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <curses.h>
#include <vector>
#include <time.h>
#include <unistd.h>
using namespace std;

const char *victory=
" \n \n \n \n \n Yer a wizard! You've won! \n \n \n "
"            _            _.,----,\n "
" __   _.-._/ '_.        -  ,._ \\) \n "
"|  '-)_    '_.  \\      /   < _   )/   \n"
"//_    '_.   \\  '_, ___(c-(6)=(6) \n"
"   ''.    '.  '.  _,    >\\   ''  )\n"
"     |._.   '___'  (   ( ''/' =  '/ \n"
"        |..__    ,'-.')  '-  '__'  \n"
"  ''''''     /'._|    Y/     _/' \\ \n"
"    '''''\\  |   |   _| _.'._    \\  \n"
"  ''''''   \\|   \\  \\/     '._  \\ \n"
"   .-,-,_ ___|    '.  \\       \\  |  \n"
"  //               \\, \\______|   L \n "
" |                  \\_________\\ \\ \n" 
" '__'-'_.\\__/  |  .'/          \\ \\ \n"
"               [  (              \\ \\\n"
"               )  (               \\/\n"
"               \\_) \n \n \n \n \n";

const char *startingPage =
" \n"
"\n"
"\n"  
"    The king of the serpents... \n"
  " \n"
  "     |~~~~~~|     /\\      ~~~~~  | |     |  ~~~~~  |  / \n"
  "     |      |    /  \\     |        |        |      | /    \n "
  "    |~~~~~~|   /~~~~\\    |~~~~| | |     |  |~~~~| |<        \n"
  "     |      |  /      \\        | | |     |       | | \\   \n"
  "     |~~~~~~| /        \\  ~~~~~| | |~~~~ |  ~~~~~| |  \\ \n"
"\n"
"\n"
"\n"
  "                     Press 1 to play \n"
  "                Press 2 to get instructions \n"
  "              Or Press Any Other Key to Quit \n";

const char *loser=
"\n \n \n \n \n \n \n \n        Your loserness is an unforgivable curse... \n \n \n \n"
"       /\\   \\    /   /\\   ~~\\    /\\        |  /   /\\   ~~\\   /\\  \\    /  ~~\\   /\\ \n"
"      /--\\   \\  /   /--\\  |  |  /--\\       |<    /--\\  |  | /--\\  \\  /   |_|  /--\\ \n"
"     /    \\   \\/   /    \\ |_ / /    \\      |  \\ /    \\ |_/ /    \\  \\/    | \\ /    \\ \n"
"\n \n \n                                                    You're dead.  \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n";


const char *instructions=
"\n \n \n \n     So, you think you have what it takes to be a basilisk? We'll see... \n"
"     Voldemort has entered Hogwarts, and has trapped different muggle borns \n"
"     in the chamber of secrets. You must go around and petrify each of them\n"
"     in order to help Voldemort (and not be killed by him)\n \n \n"
"     To play, use the arrow keys to move up (or k), down (or j),\n"
"     left (or h), and right (or l)                                   \n"
"     But be quick, or you will start moving diagonally automatically \n"
"     Making it harder to petrify all of them. You can hold down the \n"
"     arrow keys to move faster. Also, don't try to go outside of the\n"
"     or you trip over yourself or you will be seen and killed. Good luck.\n \n \n"
"     Press 1 to continue, or any other key if you are too afraid \n";

int main(int argc, char *argv[]){
  srand(time(NULL));
  initscr();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);
  cbreak();
  printw( startingPage);
  int key;
  switch(key=getch()){
  case '2':
    clear();
    printw(instructions);
    switch(key=getch()){
    case '1':
      break;
    default:
      endwin();
      return 1;
    }
  case '1':
    map_t m;
    new_map(&m);
    refresh();
    while((m.s->alive)==1){
      printMap(&m);
      do_move(&m);
      refresh();
      if(m.numTraps==0){
	endwin();
	delete_map(&m);
        printf("%s", victory);
	return 1;
      }
    }
    endwin();
    delete_map(&m);
    printf("%s",loser);   
  }
  return 1;

}

