/*************************************
*	CMSC 125 PROJECT- HANGMAN		 *
*	Reblora, Kyle Matthew B.		 *
*	Sunga, Jasper					 *
*************************************/


#include "dexsdk.h"
#include "time.h"

#define difficulties 	3
#define timer 			120  /* sets timer to 2 mins (optional)*/

/* main menu controls */
#define play 			'p'
#define instructions 	'i'
#define about 			'a'
#define highscores		'h'
#define exit			'`'

#define YELLOW 			54
#define PALE_YELLOW 	62
#define ROYAL_BLUE 		1
#define DARK_BLUE 		8
#define GRAY 			56
#define WHITE 			63
#define ORANGE			20

int main() {
	
	char keypress = play;

	set_graphics(VGA_320X200X256);
	// erase(1,1,400,220);
	
	clrscr();
	mainmenu();
	keypress = (char)getch();
	// erase(1,1,400,220);



	if (keypress == exit) {
		set_graphics(VGA_TEXT80X25X16);
		clrscr();			
	}

		

}

mainmenu() {
	write_text("HANGUMANU", 120, 40, YELLOW, 1);

	write_text("P", 120, 80, ORANGE, 1);
	write_text("lay Game", 130, 80, WHITE, 1);

	write_text("I", 120, 100, ORANGE, 1);
	write_text("nstructions", 130, 100, WHITE, 1);

	write_text("A", 120, 120, ORANGE, 1);
	write_text("bout", 130, 120, WHITE, 1);

	write_text("H", 120, 140, ORANGE, 1);
	write_text("igh Scores", 130, 140, WHITE, 1);

	write_text("E", 120, 160, ORANGE, 1);
	write_text("xit", 130, 160, WHITE, 1);
}

// about() {
// 	write_text("Made by Kyle Reblora and Jasper Sunga", 80, 40, YELLOW, 1);

// }

void erase(int x, int y, int w, int h){ //basically covers an area with a black rectangle 
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,100);
}