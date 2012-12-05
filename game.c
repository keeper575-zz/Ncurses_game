#include <stdio.h>
#include <ncurses.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 30
#define HEIGHT 10 

int startx = 0;
int starty = 0;

char *choices[] = { 
	"UP",
	"DOWN",
	"LEFT",
	"RIGHT",
	"STOP",
};
int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight);
void send_comm(int i);

int main()
{	WINDOW *menu_win;
	int highlight = 1;
	int choice = 0;
	int r;
	char c;

	initscr();
	clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
	startx = 70;//(80 - WIDTH) ;
	starty = 10;//(24 - HEIGHT) ;

	menu_win = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(menu_win, TRUE);
	mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
	refresh();
	print_menu(menu_win, highlight);
	while(1)
	{	r = wgetch(menu_win);
		switch(r)
		{	case KEY_UP:
			highlight = 1;
			printw("up key pressed");
			break;

			case KEY_DOWN:
			//mvprintw(24, 0, "down key pressed");
			highlight=2;
			break;

			case KEY_LEFT:
			//mvprintw(24, 0, "left key pressed");
			highlight =3;
			break;

			case KEY_RIGHT:
			//mvprintw(24, 0, "right key pressed");
			highlight=4;
			break;

			case 115:
			//mvprintw(24, 0, "stop key pressed");
			highlight=5;
			break;

			case 10:
			choice=highlight ;
			break;
			default:
			mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
			refresh();
			break;
		}
		print_menu(menu_win, highlight);
		if(choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}	
	mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1]);
	clrtoeol();
	refresh();
	endwin();
	return 0;
}


void print_menu(WINDOW *menu_win, int highlight)
{
	int x, y, i;	

	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	for(i = 0; i < n_choices; ++i)
	{	if(highlight == i + 1) /* High light the present choice */
		{	wattron(menu_win, A_REVERSE); 
			mvwprintw(menu_win, y, x, "%s", choices[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", choices[i]);
		++y;
	}
	wrefresh(menu_win);
}

