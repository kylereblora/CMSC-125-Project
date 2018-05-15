/*************************************
*	CMSC 125 PROJECT- HANGMAN		 *
*	Reblora, Kyle Matthew B.		 *
*	Sunga, Jasper					 *
*************************************/

#include "../../sdk/dexsdk.h"
#include "../../sdk/time.h"
// #include <stdio.h>
#include <string.h>
#define difficulties 	3
#define timer 			120  /* sets timer to 2 mins (optional)*/

/* main menu controls */
#define play 			'p'
#define instructions 	'i'
#define about 			'a'
#define highscores		'h'
#define exit			'e'
#define back_to_menu	'b'
#define play_back       '0'

/* main menu colors*/
#define YELLOW 			54
#define GRAY 			56
#define WHITE 			63
#define ORANGE			20

int main() {
	
	char keypress;
    int flag = 0;
	set_graphics(VGA_320X200X256);			// set graphics and resolution
	
	clrscr();
    srand(time(NULL));                      // randomize in c
	do {
		erase(1,1,400,220);					// paint the whole screen with black pixels

        if(flag == 0){                      // if-else statements for handling user choices in main menu
		    mainmenu(&keypress,&flag);				
        } else if(flag == 1) {
			about_game(&keypress,&flag);
		} else if (flag == 2) {
			instructions_page(&keypress,&flag);
		} else if (flag == 3) {
			highscores_page(&keypress,&flag);
		} else if (flag == 4) {
			play_game(&keypress,&flag);
		}

	} while (keypress != exit || flag != -1); // loops until the user does not wish to exit yet
	set_graphics(VGA_TEXT80X25X16);         // if exit, revert back to original resolution
	clrscr();			
}

void mainmenu(char * keypress, int * flag) {
	int i;
	for(i=10; i<305; i++) write_pixel(i,10,ORANGE); // top border
	for(i=15; i<300; i++) write_pixel(i,15,WHITE);
	for(i=10; i<190; i++) write_pixel(10,i,ORANGE); // left border
	for(i=15; i<185; i++) write_pixel(15,i,WHITE);
	for(i=10; i<191; i++) write_pixel(305,i,ORANGE); // right border
	for(i=15; i<186; i++) write_pixel(300,i,WHITE);
	for(i=10; i<305; i++) write_pixel(i,190,ORANGE); // bottom border
	for(i=15; i<300; i++) write_pixel(i,185,WHITE); 
	
    write_text("HANGUMANU", 120, 40, YELLOW, 1);

    write_text("P", 120, 70, ORANGE, 1);
    write_text("lay Game", 130, 70, WHITE, 1);

    write_text("I", 120, 90, ORANGE, 1);
    write_text("nstructions", 130, 90, WHITE, 1);

    write_text("A", 120, 110, ORANGE, 1);
    write_text("bout", 130, 110, WHITE, 1);

    write_text("H", 120, 130, ORANGE, 1);
    write_text("igh Scores", 130, 130, WHITE, 1);

    write_text("E", 120, 150, ORANGE, 1);
    write_text("xit", 130, 150, WHITE, 1);
    do{

        char input = (char)getch();
        *keypress = input;
        if(*keypress == play){              // flags are for the user choices
            *flag = 4;    
        }else if(*keypress == about){
            *flag= 1;
        }else if(*keypress == instructions){
            *flag = 2;
        }else if(*keypress == highscores){
            *flag = 3;
        }else if(*keypress == exit){
            *flag = -1;
        }
    } while (*keypress != play && *keypress != about && *keypress != instructions && *keypress != highscores && *keypress != exit);
}


void play_game(char * keypress, int * flag) {
    write_text("B", 7, 5, ORANGE, 1);
    write_text("ack", 16, 5, WHITE, 1);

    write_text("Choose a Category", 80, 45, YELLOW, 1);

    write_text("M", 115, 95, ORANGE, 1);
    write_text("ovies", 125, 95, WHITE, 1);
    write_text("U", 115, 120, ORANGE, 1);
    write_text("PLB", 125, 120, WHITE, 1);
	do {	
		char input = (char)getch();   // loop inside "choose a category" until user
		*keypress = input;      
		if(*keypress==back_to_menu){   // selects "back" or 'm' or 'u'
            *flag = 0;  
        }
	} while (*keypress != back_to_menu && *keypress != 'm' && *keypress != 'u');
    if(*keypress == back_to_menu){
        return;                         // go back to menu if user selects "back"
    }
    
    loading();
    // game
    char category = *keypress;
    char category_name[10];
    FILE* fp;               
    if(category=='u'){                  // if the category is UPLB,
        strcpy(category_name,"UPLB");   // copy UPLB to category_name for further use
        fp = fopen("uplb.txt","r");     // open the file that contains the questions for uplb
    }else{
        strcpy(category_name,"MOVIES"); // open the file that contains the questions for movies
        fp = fopen("movies.txt","r");
    }
    char easy[3][4], medium[3][5], hard[3][6];  // arrays that will contain the easy, medium, and hard questions
    
    fread(easy[0],3,1,fp);    easy[0][3] = '\0';          // read the words inside the file according to their length
    fread(easy[1],3,1,fp);    easy[1][3] = '\0';          // then end the string with a '\0'
    fread(easy[2],3,1,fp);    easy[2][3] = '\0';
    fread(medium[0],4,1,fp);    medium[0][4] = '\0';
    fread(medium[1],4,1,fp);    medium[1][4] = '\0';
    fread(medium[2],4,1,fp);    medium[2][4] = '\0';
    fread(hard[0],5,1,fp);    hard[0][5] = '\0';
    fread(hard[1],5,1,fp);    hard[1][5] = '\0';
    fread(hard[2],5,1,fp);    hard[2][5] = '\0';
    fclose(fp);
    
    int letters[26];                    // array that will store letters a-z
    reinitialize(letters);              // initialize all values of letters to 0 (0 if not yet picked, 1 if picked)
    int wrong = 0;                      // monitors the wrong attempts
    int level = 1;
    int new_word = 1;
    int score = 0;
    int length = 3;
    int guessed[10];                    // array that store the right letters that the user guessed
    rezero(guessed);                    // 0 if not guessed, 1 if guessed
    int used[3];
    used[0] = used[1] = used[2] = 0;
    char word[10];
    int curr = 0;
    do{
        if(new_word==1){                // checks if a new word is loaded
            new_word = 0;
            reinitialize(letters);
            rezero(guessed);
            // get new word
            if(used[0]==1 && used[1]==1 && used[2]==1){
                level++;
                used[0] = used[1] = used[2] = 0;
            }
            int num;
            do{
                num = (rand() %(2 - 0 + 1)) + 0;        // randomize the word to be guessed
            }while(used[num]==1);                       // while a previous word is selected
            used[num] = 1;
            if(level==1){
                strcpy(word,easy[num]);                 //copy the randomized word to the word array
                length = 3;                             // since it is easy, length = 3. medium = 4, hard = 5.
            }
            else if(level==2){
                strcpy(word,medium[num]);
                length = 4;
            }
            else if(level==3){
                strcpy(word,hard[num]);
                length = 5;
            }
            else
                continue;
        }
        // update screen
        erase(1,1,400,220);
        print_blanks(guessed,length,word);          // print number of blanks based on length
        print_letters(letters);                     // print letters
        // print stand
        draw_pole();
        
        int temp_wrong = wrong;
        if(temp_wrong){                             // draw a body part for each wrong attempt
            // print head
            draw_head();
            temp_wrong--;
        }
        if(temp_wrong){
            draw_torso();
            temp_wrong--;
        }
        if(temp_wrong){
            draw_left_arm();
            temp_wrong--;
        }
        if(temp_wrong){
            draw_right_arm();
            temp_wrong--;
        }
        if(temp_wrong){
            draw_left_leg();
            temp_wrong--;
        }
        if(temp_wrong){
            draw_right_leg();
        }

        write_text("Back - [0]", 16, 5, WHITE, 1);
        write_text(category_name, 200,5, ORANGE ,1);
        write_text("Level", 200,20,WHITE,1);
        char levelS[1];
        sprintf(levelS, "%d",level);                // printing which level the user is currently in
        write_text(levelS,250,20,WHITE,1);
        char input = (char)getch();
		*keypress = input;
		if(*keypress==play_back){                   // if the user decides to go back to menu
            *flag = 0;
        }

        int num_input = input-97;                   // convert user input to integer
        if(num_input<0 || num_input>25)             // if letter selected is valid
            continue;
        
        if(letters[num_input]==1)                   // if the letter is already selected, continue
            continue;
        else
            letters[num_input] = 1;

        int i, instance = 0;
        for(i = 0; i < length; i++){                // loops through the word to be guessed's length
            if(word[i]==input){                     // check if user input is correct
                instance++;
                guessed[i] = 1;                     // update the guessed[] array based on the index of the correct letter
            }
        }
        if(instance == 0){
            wrong++;
            score -= level*2;
            if(score < 0)
                score = 0;
        }

        int full = 1;
        for(i = 0; i < length; i++){
            if(guessed[i] == 0){
                full = 0;
                break;
            }
        }
        
        if(full==1){                                // if the user completes the word, update score and word
            score += 5+level*5;
            new_word = 1;
            write_text("Correct guess!", 160, 50, GREEN, 1);
            for(i = 0; i < length; i++){
                guessed[i] = 1;
            }
            erase(150, 240, 100, 60);
            print_letters(letters);
            print_blanks(guessed,length,word);          // print number of blanks based on length
            sleep(150);
        }

    }while (wrong != 6 && level != 4 &&  *keypress != play_back);       // while the user has not won yet
    // Save Score
    int scores[6];
    char scoreS[3];
    int i;
    
    fp = fopen("scores.txt","r");                               // open scores for reading
    for(i = 0; i<5; i++){
        int lengthI = fgetc(fp);                                // basically stores all scores in an array for later use
        char lengthC = (char) lengthI;
        int actual_length = lengthC - '0';
        fread(scoreS, actual_length, 1, fp);
        int j;
        int result = 0;
        for(j = 0; j < actual_length; j++){
            result = result * 10+ (scoreS[j] - '0');
        }
        scores[i] = result;
    }
    fclose(fp);

    scores[5] = score;
    
    int a,b,c;
    for (a = 0; a < 6; ++a) {                   // sort the scores in descending order
        for (b = a + 1; b < 6; ++b){
            if (scores[a] > scores[b]){
                c =  scores[a];
                scores[a] = scores[b];
                scores[b] = c;
            }
        }
    }

    int scores_length[6];
    for(i = 0; i<6; i++){
        scores_length[i] = count_digit(scores[i]);  // store the length in array based on the number of its digits
    }
    fp = fopen("scores.txt","w");

    for(i = 5; i>0;i--){
        char char_length = scores_length[i]+'0';            // write the scores in scores.txt to save the high scores
        fputc(char_length,fp);
        char current_score[scores_length[i]];
        sprintf(current_score,"%d",scores[i]);
        fwrite(current_score, 1, sizeof(current_score), fp);
    }

    fclose(fp);
    if(*keypress==play_back){
        return;
    }
    erase(1,1,400,220);
    draw_pole();                    // draw stick figure
    int temp_wrong = wrong;
    if(temp_wrong){
        // print head
        draw_head();
        temp_wrong--;
    }
    if(temp_wrong){
        draw_torso();
        temp_wrong--;
    }
    if(temp_wrong){
        draw_left_arm();
        temp_wrong--;
    }
    if(temp_wrong){
        draw_right_arm();
        temp_wrong--;
    }
    if(temp_wrong){
        draw_left_leg();
        temp_wrong--;
    }
    if(temp_wrong){
        draw_right_leg();
    }
    write_text(category_name, 200,5,ORANGE,1);
    write_text("Level", 200,20,WHITE,1);
    char levelS[1];
    sprintf(levelS, "%d",level);
    write_text(levelS,250,20,WHITE,1);
    if(wrong==6){                                       // if the number of wrong attempts have been met
        // Game over                                    
        write_text("GAME OVER.",195,70,RED,1);
    }else if(level==4){
        // Win
        erase(195, 21, 120, 15);
        write_text("YOU WIN!",195,70,GREEN,1);
    }
    write_text("Score: ",200,100,WHITE,1);                // display user's score at the end of the game
    char character_score[3];
    sprintf(character_score, "%d", score);
    write_text(character_score,210,120,WHITE,1);
    write_text("B", 7, 5, ORANGE, 1);
    write_text("ack", 16, 5, WHITE, 1);
    do{
        char input = (char)getch();
		*keypress = input;
		if(*keypress==back_to_menu){
            *flag = 0;
        }
    }while(*keypress!=back_to_menu);

}

void about_game(char * keypress, int * flag) {
    write_text("B", 7, 5, ORANGE, 1);
    write_text("ack", 16, 5, WHITE, 1);
    
    write_text("AUTHORS", 120, 15, YELLOW, 1);
    write_text("Kyle Reblora", 100, 35, WHITE, 1);
    write_text("Jasper Sunga", 100, 50, WHITE, 1);

    write_text("SECTION", 120, 75, YELLOW, 1);
    write_text("CMSC 125 T-5L", 93, 95, WHITE, 1);
    
    write_text("ABOUT THE GAME", 90, 120, YELLOW, 1);
    write_text("A simple hangman game", 55, 140, WHITE, 1);
    write_text("made in ICS-OS. Enjoy!", 55, 155, WHITE, 1);
	do{
		
		char input = (char)getch();
		*keypress = input;
        if(*keypress == back_to_menu){
            *flag = 0;
        }

	} while (*keypress != back_to_menu);				// loop through the about page until user goes back to menu
}

void instructions_page(char * keypress, int * flag) {           // print the instructions of the game
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
	do{
		
		char input = (char)getch();
		*keypress = input;
        if(*keypress == back_to_menu){
            *flag = 0;
        }
	} while (*keypress != back_to_menu);
}

void loading() {
    erase(1, 1, 400, 220);
    write_text("LOADING...", 120, 70, YELLOW, 1);
    int i, j;
    for (j=100; j<102; j++) {
		for (i=100;i<225;i++)write_pixel(i,j,GRAY);
	}

	for (i=100; i<102; i++) {
		for (j=100; j<115; j++) write_pixel(i,j,GRAY);
	}

    for (j=115; j<117; j++) {
		for (i=100;i<225;i++)write_pixel(i,j,GRAY);
	}

    for (i=223; i<225; i++) {
		for (j=100; j<115; j++) write_pixel(i,j,GRAY);
	}

    for (i=102; i<223; i++) {
		for (j=102; j<115; j++) {
            write_pixel(i,j,WHITE);
        }
        sleep(2);
	}
}

void highscores_page(char * keypress, int * flag) {

    write_text("B", 7, 5, ORANGE, 1);
    write_text("ack", 16, 5, WHITE, 1);                 // print the high scores page
    write_text("HIGH SCORES", 110, 30, YELLOW, 1);

    char score[3];
    int i;
    FILE *fp;
    fp = fopen("scores.txt","r");                       // open file that contains previous scores (if any)
    for(i = 0; i<5; i++){                               // display the scores inside the game
        int lengthI = fgetc(fp);
        char lengthC = (char) lengthI;
        int actual_length = lengthC - '0';
        fread(score, actual_length, 1, fp);
        score[actual_length] = '\0';                    // limits the printing of the score on its actual number of digits
        write_text(score,150,70+(i*20),WHITE,1);
    }
    fclose(fp);

    do{
        char input = (char)getch();
        *keypress = input;
        if(*keypress == back_to_menu){
            *flag = 0;
        }
    } while (*keypress != back_to_menu);
}

void reinitialize(int * letters){           // reinitialize all values of the letters to 0, meaning it hasnt been 
    int i;                                  // selected yet. 1 if it has been selected.
    for(i = 0; i < 26; i++)
        letters[i] = 0;
}

void rezero(int* guessed){
    int i;
    for(i = 0; i< 10; i++)
        guessed[i] = 0;                     // 0 if letter in the word hasnt been guessed yet, 1 if it has been guessed.
}

void erase(int x, int y, int w, int h){ //basically covers an area with a black rectangle 
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,100);
}

void draw_pole() {                                  // draw the pole where the stick figure will be hanged (yes, hanged)
	int i, j;
	for (j=55; j<175; j++) {
		for (i=15;i<25;i++)write_pixel(i,j,56);
	}

	for (j=55; j<58; j++) {
		for (i=25; i<85; i++) write_pixel(i,j,56);
	}
}


void draw_head() {                                  // draw the stick figure's head
	int i, j;
	for (i=8;i<18;i++)write_pixel(i+50,59,WHITE);
	for (i=6;i<20;i++)write_pixel(i+50,60,WHITE);
	for (i=4;i<21;i++)write_pixel(i+50,61,WHITE);
	for (i=3;i<22;i++)write_pixel(i+50,62,WHITE);
	for (i=2;i<23;i++)write_pixel(i+50,63,WHITE);
	for (i=1;i<24;i++)write_pixel(i+50,64,WHITE);
	for (i=1;i<25;i++)write_pixel(i+50,65,WHITE);
	for (i=0;i<25;i++)write_pixel(i+50,66,WHITE);
	for (i=0;i<25;i++)write_pixel(i+50,67,WHITE);
	for (i=0;i<25;i++)write_pixel(i+50,68,WHITE);
	for (i=0;i<25;i++)write_pixel(i+50,69,WHITE);
	for (i=0;i<25;i++)write_pixel(i+50,70,WHITE);
	for (i=1;i<24;i++)write_pixel(i+50,71,WHITE);
	for (i=1;i<24;i++)write_pixel(i+50,72,WHITE);
	for (i=2;i<23;i++)write_pixel(i+50,73,WHITE);
	for (i=3;i<22;i++)write_pixel(i+50,74,WHITE);
	for (i=5;i<20;i++)write_pixel(i+50,75,WHITE);
	for (i=7;i<18;i++)write_pixel(i+50,76,WHITE);
	for (i=9;i<15;i++)write_pixel(i+50,77,WHITE);
}


void draw_torso() {                                     // draw stick figure's torso    
	int i, j;
	for (i=60;i<65;i++) {
		for (j=70; j<140; j++) write_pixel(i,j,WHITE);
	}
}

void draw_right_arm() {                                 // right arm
	int i, j;
	for (i=65;i<95;i++) {
		for (j = 20; j < 25; j++) write_pixel(i,i+j,WHITE);
	}
}

void draw_left_arm() {                                  // left arm
	int i, j;
	for (i=30;i<60;i++) {
		for (j = 84; j < 89; j++) write_pixel(i,(60-i)+j,WHITE);
	}
}


void draw_right_leg() {
	int i, j;
	for (i=65;i<95;i++) {
		for (j = 70; j < 75; j++) write_pixel(i,i+j,WHITE);
	}
}

void draw_left_leg() {
	int i, j;
	for (i=30;i<60;i++) {
		for (j = 135; j < 140; j++) write_pixel(i,(60-i)+j,WHITE);
	}
}

void print_blanks(int * guessed, int length, char * word) {
	char * character[2];    
	character[1] = '\0';

	int i;
	for(i = 0; i < length; i++) {
		if (guessed[i] == 0) {
			write_text("_", 200+(i*20), 80, WHITE, 1); // printing the blanks based on the length of the word to be guessed
		} else {	
			character[0] = word[i]; 
			write_text(character, 200+(i*20), 80, WHITE, 1); // display the letter if the letter has been guessed correctly
		}
	}
}

void print_letters(int * letters) {
	char * character[2];
	character[1] = '\0';
	int i;
	for(i = 0; i < 26; i++) {
		if (letters[i] == 0) {              // prints all letters from a-z. 
			character[0] = i+97;
			if (i <= 13) write_text(character, 150+(i*10), 160, WHITE, 1); // white if not yet selected
			else write_text(character, 150+((i%14)*10), 175, WHITE, 1);
		} else if (letters[i] == 1){
			character[0] = i+97;
			if (i <= 13) write_text(character, 150+(i*10), 160, ORANGE, 1); // orange if selected
			else write_text(character, 150+((i%14)*10), 175, ORANGE, 1);
		}
	}
}

int count_digit(int num){       // function that counts the number of digits of the score
    if(num==0)
        return 1;
    int count = 0;
    while(num != 0){
        num /= 10;
        ++count;
    }
    return count;
}