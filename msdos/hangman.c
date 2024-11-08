#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#include <dos.h>

#define MAX_WORD_LENGTH 25
#define MIN_WORD_LENGTH 5
#define MAX_WORDS 1000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

// Global variables
char words[MAX_WORDS][MAX_WORD_LENGTH + 1];
int num_words = 0;

// Function to clear the screen
void clear_screen(void) {
    clrscr();
}

// Function to draw the hangman
void draw_hangman(int incorrect_guesses, int max_incorrect_guesses) {
    int temp = max_incorrect_guesses / 12;
    
    gotoxy(1, 1);
    printf("_______");
    gotoxy(1, 2);
    printf("|     |");
    gotoxy(1, 3);
    printf("|");
    gotoxy(1, 4);
    printf("|");
    gotoxy(1, 5);
    printf("|");
    gotoxy(1, 6);
    printf("|");
    gotoxy(1, 7);
    printf("|");
    gotoxy(1, 8);
    printf("|");
    gotoxy(1, 9);
    printf("|");
    gotoxy(1, 10);
    printf("-------");

    if(incorrect_guesses > 0) {
        gotoxy(7, 3);
        printf("O");
    }
    if(incorrect_guesses > temp) {
        gotoxy(7, 4);
        printf("|");
    }
    if(incorrect_guesses > 2 * temp) {
        gotoxy(7, 5);
        printf("|");
    }
    if(incorrect_guesses > 3 * temp) {
        gotoxy(6, 5);
        printf("/");
    }
    if(incorrect_guesses > 4 * temp) {
        gotoxy(8, 5);
        printf("\\");
    }
    if(incorrect_guesses > 5 * temp) {
        gotoxy(7, 6);
        printf("|");
    }
    if(incorrect_guesses > 6 * temp) {
        gotoxy(6, 7);
        printf("/");
    }
    if(incorrect_guesses > 7 * temp) {
        gotoxy(8, 7);
        printf("\\");
    }
    if(incorrect_guesses > 8 * temp) {
        gotoxy(5, 8);
        printf("/");
    }
    if(incorrect_guesses > 9 * temp) {
        gotoxy(9, 8);
        printf("\\");
    }
    if(incorrect_guesses > 10 * temp) {
        gotoxy(4, 9);
        printf("/");
    }
    if(incorrect_guesses > 11 * temp) {
        gotoxy(10, 9);
        printf("\\");
    }
}

// Function to load words from file
int load_words(void) {
    FILE *fp;
    char word[MAX_WORD_LENGTH + 1];
    
    fp = fopen("WORDS", "r");
    if(fp == NULL) {
        printf("Error: Cannot open words file\n");
        return 0;
    }
    
    while(fgets(word, MAX_WORD_LENGTH + 1, fp) != NULL && num_words < MAX_WORDS) {
        // Remove newline
        word[strcspn(word, "\n")] = 0;
        
        // Check word length
        if(strlen(word) >= MIN_WORD_LENGTH && strlen(word) <= MAX_WORD_LENGTH) {
            strcpy(words[num_words], word);
            num_words++;
        }
    }
    
    fclose(fp);
    return num_words > 0;
}

// Function to display available letters
void display_available_letters(char *guessed) {
    int i;
    gotoxy(1, 12);
    printf("Available letters: ");
    for(i = 0; i < 26; i++) {
        if(!guessed[i]) {
            printf("%c ", 'A' + i);
        } else {
            printf("_ ");
        }
    }
}

// Main game function
void play_game(int max_incorrect_guesses) {
    char word[MAX_WORD_LENGTH + 1];
    char progress[MAX_WORD_LENGTH + 1];
    char guessed[26] = {0};
    int incorrect_guesses = 0;
    int i, word_len, game_over = 0;
    char guess;
    int found;
    
    // Select random word
    strcpy(word, words[rand() % num_words]);
    word_len = strlen(word);
    
    // Initialize progress
    for(i = 0; i < word_len; i++) {
        if(isalpha(word[i])) {
            progress[i] = '_';
        } else {
            progress[i] = word[i];
        }
    }
    progress[word_len] = '\0';
    
    while(!game_over) {
        clear_screen();
        draw_hangman(incorrect_guesses, max_incorrect_guesses);
        display_available_letters(guessed);
        
        gotoxy(1, 15);
        printf("Word: ");
        for(i = 0; i < word_len; i++) {
            printf("%c ", progress[i]);
        }
        
        gotoxy(1, 17);
        printf("Wrong guesses left: %d", max_incorrect_guesses - incorrect_guesses);
        
        // Get guess
        gotoxy(1, 19);
        printf("Enter your guess (or ESC to quit): ");
        guess = toupper(getch());
        
        if(guess == 27) { // ESC key
            game_over = 1;
            continue;
        }
        
        if(!isalpha(guess)) {
            continue;
        }
        
        // Check if letter was already guessed
        if(guessed[guess - 'A']) {
            gotoxy(1, 21);
            printf("You've already guessed that letter!");
            getch();
            continue;
        }
        
        guessed[guess - 'A'] = 1;
        
        // Check guess
        found = 0;
        for(i = 0; i < word_len; i++) {
            if(toupper(word[i]) == guess) {
                progress[i] = word[i];
                found = 1;
            }
        }
        
        if(!found) {
            incorrect_guesses++;
        }
        
        // Check win/lose conditions
        if(strchr(progress, '_') == NULL) {
            clear_screen();
            draw_hangman(incorrect_guesses, max_incorrect_guesses);
            gotoxy(1, 17);
            printf("Congratulations! You guessed the word \"%s\"!", word);
            game_over = 1;
        } else if(incorrect_guesses >= max_incorrect_guesses) {
            clear_screen();
            draw_hangman(incorrect_guesses, max_incorrect_guesses);
            gotoxy(1, 17);
            printf("Sorry, you lost. The word was \"%s\".", word);
            game_over = 1;
        }
    }
    
    gotoxy(1, 21);
    printf("Press any key to continue...");
    getch();
}

int main(int argc, char *argv[]) {
    int max_guesses = 12;
    char play_again;
    
    // Parse command line arguments
    if(argc == 3 && strcmp(argv[1], "-m") == 0) {
        max_guesses = atoi(argv[2]);
        if(max_guesses <= 0) {
            printf("Invalid number of guesses\n");
            return 1;
        }
    }
    
    // Initialize random number generator
    srand(time(NULL));
    
    // Load words
    if(!load_words()) {
        printf("Failed to load words\n");
        return 1;
    }
    
    // Main game loop
    do {
        play_game(max_guesses);
        
        gotoxy(1, 22);
        printf("Play again? (Y/N): ");
        do {
            play_again = toupper(getch());
        } while(play_again != 'Y' && play_again != 'N');
        
    } while(play_again == 'Y');
    
    clear_screen();
    return 0;
}

