/*
 * main.c
 * 
 * Copyright 2013 Miguel Alonso Jr <drmiguelalonsojr@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

/*
	Header definitions
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h> // This lets us capture the Ctrl-C interrupt
#include <pthread.h> // This lets us create threads
#include <ncurses.h> // This lets us create a text-based user interface
#include "dspThread.h" // DSP thread definitions
#include "debug.h" // DBG and ERR macros
#include "audioIO.h" // Audio IO definitions

/*
	Global variables
*/

#define WIDTH 40 // This defines the width of the window
#define HEIGHT 10 // This defines the height of the window
int startx = 0; // Defines window starting point for x
int starty = 0; // Defines window starting point for y
// Defines menu choices
char *choices[] = { 
			"Tuner On",
			"Tuner Off",
			"Exit"
		  };
int n_choices = sizeof(choices) / sizeof(char *);
dsp_thread_env dsp_env = {0,1,1.0,0,0,0}; // This is used for main to communicate to the dspThread (initializes the variables in struct)
void (*pSigPrev)(int sig); // Store previous signal handler and call it

/*
	Function prototypes
*/

void signal_handler(int sig);
void print_menu(WINDOW *menu_win, int highlight);

/*
	Main function
*/

int main(int argc, char **argv)
{
	int status = EXIT_SUCCESS;
	pthread_t thr;
	void *dspThreadReturn;
	WINDOW *menu_win;
	int highlight = 1;
	int choice = 0;
	int c;
	
	// Set the signal callback for Ctrl-C
    pSigPrev = signal(SIGINT, signal_handler);
    
    // Starts the DSP thread
    //dspThreadReturn = dsp_thread_start( (void *) &dsp_env );   
    if(pthread_create(&thr, NULL, &dsp_thread_start, (void *) &dsp_env))
    {
        printf("Could not create thread\n");
        return -1;
    }
    
    // text UI section
    initscr();
    clear();
	noecho();
	cbreak();
	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;
	menu_win = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(menu_win, TRUE);
	mvprintw(1, 1, "JC Vazquez - DSP Music Tuner");
	mvprintw(2, 1, "Use up and down arrow keys to choose tuner on/off ");
	mvprintw(3, 1, "Use left and right arrow keys to choose which note to tune.");
	mvprintw(4, 1, "Hint: You must tune from high to low frequency notes.");
	refresh();
	print_menu(menu_win, highlight);
	wtimeout(menu_win,0);
	while(1)
	{	c = wgetch(menu_win);
		switch(c)
		{	case KEY_UP:
				if(highlight == 1)
					highlight = n_choices;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices)
					highlight = 1;
				else 
					++highlight;
				break;
			case 10:
				choice = highlight;
				break;
			case KEY_RIGHT:
				//if (dsp_env.volume < 1)
					//dsp_env.volume+=0.1;
				if(dsp_env.cnote >= 0 && dsp_env.cnote < 7) //adjust the note variable
					dsp_env.cnote += 1;
				break;
			case KEY_LEFT:
				//if (dsp_env.volume >= 0.1)
					//dsp_env.volume-=0.1;
				if(dsp_env.cnote <= 7 && dsp_env.cnote > 0) //adjust the note variable
					dsp_env.cnote -= 1;
				break;
			default:
				mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
				refresh();
				break;
		}
		switch(choice){
			case 1:
				dsp_env.filter_on = 1;
				break;
			case 2:
				dsp_env.filter_on = 0;
				dsp_env.cnote = 0; //reset the note variable
				break;
			default:
				break;
		}
		print_menu(menu_win, highlight);
		if(choice == 3)	/* User did a choice come out of the infinite loop */
			break;
	}
	dsp_env.quit = 1;
	
	if ( pthread_join ( thr, &dspThreadReturn ) ) {
		printf("error joining thread.");
		abort();
	}
    
    while(!dsp_env.done);
	
	mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1]);
	clrtoeol();
	refresh();
    clear();
	endwin();
	return status;
}
// Signal handling callback function for CTRL-C
void signal_handler(int sig)
{
    DBG( "\nCtrl-C pressed, cleaning up and exiting..\n" );
    dsp_env.quit = 1;
    dsp_env.done = 1;

    if( pSigPrev != NULL )
        (*pSigPrev)( sig );
}

// prints_menu inside window
void print_menu(WINDOW *menu_win, int highlight)
{
	int x, y, i;	
	char wnote; //note chosen to tune
	char signote; //input signal note
	int max = dsp_env.avgpwr; //assign the max value of avgpwr into max
	switch(dsp_env.cnote){
	case 0: //X debug note
		wnote = 'X';
		signote = 'X';
		break;
	case 1: //C
		wnote = 'C';
		if(max >= 7){
			signote = 'C';
		} else if(max >= 6){
			signote = 'c';
		  }
		     else if(max >= 5){
			signote = 'D';
		     }
		        else if(max <= 4){
			   signote = 'd';
		        }
		else {
			signote = 'X';
		}
		break;
	case 2: //D
		wnote = 'D';
		if(max >= 7){
			signote = 'D';
		} else if(max >= 6){
			signote = 'd';
		  }
		     else if(max >= 5){
			signote = 'E';
		     }
		        else if(max <= 4){
			   signote = 'F';
		        }
		else {
			signote = 'X';
		}
		break;
	case 3: //E
		wnote = 'E';
		if(max >= 7){
			signote = 'E';
		} else if(max >= 6){
			signote = 'F';
		  }
		     else if(max >= 5){
			signote = 'f';
		     }
		        else if(max <= 4){
			   signote = 'G';
		        }
		else {
			signote = 'X';
		}
		break;
	case 4: //F
		wnote = 'F';
		if(max >= 7){
			signote = 'F';
		} else if(max >= 5){
			signote = 'f';
		  }
		     else if(max >= 2){
			signote = 'G';
		     }
		        else if(max == 0){
			   signote = 'g';
		        }
		else {
			signote = 'X';
		}
		break;
	case 5: //G
		wnote = 'G';
		if(max >= 7){
			signote = 'G';
		} else if(max >= 6){
			signote = 'g';
		  }
		     else if(max >= 4){
			signote = 'A';
		     }
		        else if(max <= 3){
			   signote = 'a';
		        }
		else {
			signote = 'X';
		}
		break;
	case 6: //A
		wnote = 'A';
		if(max >= 7){
			signote = 'A';
		} else if(max >= 6){
			signote = 'a';
		  }
		     else if(max >= 5){
			signote = 'B';
		     }
		        else if(max <= 4){
			   signote = 'B';
		        }
		else {
			signote = 'X';
		}
		break;
	case 7: //B
		wnote = 'B';
		if(max >= 7){
			signote = 'B';
		}
		else {
			signote = 'X';
		}
		break;
	default:
		break;
	}

	mvwprintw(menu_win, 1, 2, "Note Calibration: %c", wnote); //show which note is chosen
	//mvwprintw(menu_win, 2, 2, "Avg Power: %i", max);
	mvwprintw(menu_win, 3, 2, "Current Note: %c", signote);  //display current note that is filtered
	mvwprintw(menu_win, 4, 2, "_________________________________");
	x = 2;
	y = 5;
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

