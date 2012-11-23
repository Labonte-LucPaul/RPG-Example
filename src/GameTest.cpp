//============================================================================
// Name        : GameTest.cpp
// Author      : Luc Paul Labonté
// Version     : Alpha
// Copyright   : 2012
// Description : RPG game test with ncurses
//============================================================================

#include <iostream>
#include <curses.h>

#include <stdlib.h>

using namespace std;

char map[10][20] = {

		"###################",
		"#@                #",
		"#        +        #",
		"#    *            #",
		"#          *      #",
		"#     +           #",
		"#   *        +    |",
		"#                 #",
		"###################"

};

char map2[10][20] = {
		"###################",
		"#                 #",
		"#        +        #",
		"#    *            #",
		"#          *      #",
		"#     +           #",
		"    *        +    #",
		"#                 #",
		"###################"
};

int posX = 1;
int posY = 1;
int health = 10;

void loadMap( char mapName[10][20], int x, int y ) {
	int i;
	for( i = 0; i < 10; ++i ) {
		mvprintw( i + y, x, "%s", mapName[i] );
	}
}
void moveDude( char m[10][20], int newX, int newY ) {
	m[posY][posX] = ' ';
	m[newY][newX] = '@';
	posX = newX;
	posY = newY;
}

void obstacle( char m[10][20], int x, int y ) {

	switch( m[y][x] ) {

		case ' ':
			moveDude( m, x, y );
			mvprintw( 15, 0, "" );
		break;

		case '#':
			mvprintw( 15, 0, "Position [%d,%d] out of bounce!", x, y );
		break;

		case '+':
			if( health < 10 ) {
				++health;
			}
			moveDude( m, x, y );
		break;

		case '*':
			if( health > 0 ) {
				health -= 3;
			}
			moveDude( m, x, y );
		break;

		case '|':

			x -= 18;
			moveDude( map2, x, y );
			loadMap( map2, 19, 0 );
		break;

	}
}


int main() {

	int c = 0;
	int run = 1;

	initscr();
	clear();
	noecho();
	cbreak();

	keypad(stdscr, TRUE);
	clear();


	while( run == 1 ) {

		loadMap( map, 0, 0 );

		mvprintw( 18, 0, "Health: %02d/10", health );
		refresh();

		c = getch();

		switch(c) {

			case KEY_UP:
				mvprintw( 11, 0, "UP" );
				obstacle( map, posX, posY - 1);
			break;

			case KEY_DOWN:
				mvprintw( 11, 0, "DOWN" );
				obstacle( map, posX, posY + 1);
			break;

			case KEY_LEFT:
				mvprintw( 11, 0, "LEFT" );
				obstacle( map, posX - 1, posY);
			break;

			case KEY_RIGHT:
				mvprintw( 11, 0, "RIGHT" );
				obstacle( map, posX + 1, posY);
			break;

			case KEY_END:	// this one may not work in Unix... to fix.
				run = 0;
			break;
		}
		refresh();

	}


	return 0;
}
