/*************************************
*	CMSC 125 PROJECT- HANGMAN		 *
*	Reblora, Kyle Matthew B.		 *
*	Sunga, Jasper					 *
*************************************/


#include "../../sdk/dexsdk.h"
#include "../../sdk/time.h"
#define difficulties 	3
#define timer 			120  /* sets timer to 2 mins (optional)*/

/* main menu controls */
#define play 			'p'
#define instructions 	'i'
#define about 			'a'
#define highscores		'h'
#define exit			'e'
#define back_to_menu	'b'

#define YELLOW 			54
#define PALE_YELLOW 	62
#define ROYAL_BLUE 		1
#define DARK_BLUE 		8
#define GRAY 			56
#define WHITE 			63
#define ORANGE			20

int main() {
	
	char keypress;
	set_graphics(VGA_320X200X256);			// set graphics and resolution
	
	clrscr();

	do {
		erase(1,1,400,220);					// paint the whole screen with black pixels
		mainmenu(&keypress);				

		if(keypress == about) {
			about_game(&keypress);
		} else if (keypress == instructions) {
			instructions_page(&keypress);
		} else if (keypress == highscores) {
			highscores_page(&keypress);
		} else if (keypress == play) {
			play_game(&keypress);
		}

	} while (keypress != exit);
	set_graphics(VGA_TEXT80X25X16);
	clrscr();			
}

void mainmenu(char * keypress) {
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

	char input = (char)getch();
	*keypress = input;
}

void play_game(char * keypress) {
	do {
		erase(1,1,400,220);
		write_text("B", 7, 5, ORANGE, 1);
		write_text("ack", 16, 5, WHITE, 1);

		write_text("Choose a Category", 80, 45, YELLOW, 1);

		write_text("G", 100, 70, ORANGE, 1);
		write_text("eneral Info", 110, 70, WHITE, 1);
		write_text("M", 100, 95, ORANGE, 1);
		write_text("ovies", 110, 95, WHITE, 1);
		write_text("U", 100, 120, ORANGE, 1);
		write_text("PLB", 110, 120, WHITE, 1);
		
		
		char input = (char)getch();
		*keypress = input;
	} while (*keypress != back_to_menu);
}

void about_game(char * keypress) {
	do{
		erase(1,1,400,220);
		write_text("B", 7, 5, ORANGE, 1);
		write_text("ack", 16, 5, WHITE, 1);
		
		write_text("AUTHORS", 120, 15, YELLOW, 1);
		write_text("Kyle Reblora", 100, 35, WHITE, 1);
		write_text("Jasper Sunga", 100, 50, WHITE, 1);

		write_text("SECTION", 120, 75, YELLOW, 1);
		write_text("CMSC 125 T-5L", 93, 95, WHITE, 1);
		
		write_text("ABOUT THE GAME", 85, 120, YELLOW, 1);
		write_text("A simple hangman game", 45, 140, WHITE, 1);
		write_text("made in ICS-OS. Enjoy!", 45, 155, WHITE, 1);
		
		char input = (char)getch();
		*keypress = input;
	} while (*keypress != back_to_menu);				// loop through the about page until user goes back to menu
}

void instructions_page(char * keypress) {
	do{
		erase(1,1,400,220);
		write_text("B", 7, 5, ORANGE, 1);
		write_text("ack", 16, 5, WHITE, 1);
		write_text("INSTRUCTIONS", 100, 10, YELLOW, 1);
		write_text("The player is to guess the word on", 5, 35, WHITE, 1);
		write_text("the basis of trial-and-error. He/", 5, 50, WHITE, 1);
		write_text("she is given a definite number of", 5, 65, WHITE, 1);
		write_text("blanks that describe the length ", 5, 80, WHITE, 1);
		write_text("of the word to be guessed. For ", 5, 95, WHITE, 1);
		write_text("every wrong letter selected, the ", 5, 110, WHITE, 1);
		write_text("game draws a part of the human body", 5, 125, WHITE, 1);
		write_text("(traditionally the head, then the", 5, 140, WHITE, 1);
		write_text("torso, then the limbs).", 5, 155, WHITE, 1);
		
		char input = (char)getch();
		*keypress = input;
	} while (*keypress != back_to_menu);
}

void highscores_page(char * keypress) {
	erase(1,1,400,220);
	write_text("B", 7, 5, ORANGE, 1);
	write_text("ack", 16, 5, WHITE, 1);
	write_text("HIGH SCORES", 100, 10, YELLOW, 1);
	char input = (char)getch();
	*keypress = input;
}

void erase(int x, int y, int w, int h){ //basically covers an area with a black rectangle 
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,100);
}