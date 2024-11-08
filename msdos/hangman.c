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

// Function to load words from file
int load_words(void) {
    FILE *fp;
    char word[MAX_WORD_LENGTH + 1];
    
    fp = fopen("WORDS.TXT", "r");
    if(fp == NULL) {
        printf("Error: Cannot open WORDS.TXT\n");
        return 0;
    }
    
    while(fgets(word, MAX_WORD_LENGTH + 1, fp) != NULL && num_words < MAX_WORDS) {
        // Remove newline and carriage return
        word[strcspn(word, "\n")] = 0;
        word[strcspn(word, "\r")] = 0;
        
        // Check word length
        if(strlen(word) >= MIN_WORD_LENGTH && strlen(word) <= MAX_WORD_LENGTH) {
            strcpy(words[num_words], word);
            num_words++;
        }
    }
    
    fclose(fp);
    return num_words > 0;
}

// Function to clear screen
void clear_screen(void) {
    clrscr();
}

// Function to draw the hangman
void draw_hangman(int incorrect_guesses, int max_incorrect_guesses) {
    int temp = max_incorrect_guesses / 12;
    
    printf("  +---+\n");
    printf("  |   |\n");
    printf("  |   %c\n", (incorrect_guesses > 0) ? 'O' : ' ');
    printf("  |  %c%c%c\n",
           (incorrect_guesses > 3) ? '/' : ' ',
           (incorrect_guesses > 1) ? '|' : ' ',
           (incorrect_guesses > 4) ? '\\' : ' ');
    printf("  |   %c\n", (incorrect_guesses > 2) ? '|' : ' ');
    printf("  |  %c %c\n",
           (incorrect_guesses > 5) ? '/' : ' ',
           (incorrect_guesses > 6) ? '\\' : ' ');
    printf("  | %c   %c\n",
           (incorrect_guesses > 7) ? '/' : ' ',
           (incorrect_guesses > 8) ? '\\' : ' ');

    printf("  |\n");
    printf("=====\n\n");
}

// Function to display available letters
void display_available_letters(const char *guessed) {
    int i;
    printf("\nAvailable letters: ");
    for(i = 0; i < 26; i++) {
        if(!guessed[i]) {
            printf("%c ", 'A' + i);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
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
        
        // Display word progress
        printf("\nWord: ");
        for(i = 0; i < word_len; i++) {
            printf("%c ", progress[i]);
        }
        printf("\n");
        
        printf("\nWrong guesses left: %d", max_incorrect_guesses - incorrect_guesses);
        
        display_available_letters(guessed);
        
        printf("\nEnter your guess (ESC to quit): ");
        guess = toupper(getch());
        
        if(guess == 27) { // ESC key
            game_over = 1;
            continue;
        }
        
        if(!isalpha(guess)) {
            continue;
        }
        
        if(guessed[guess - 'A']) {
            printf("\nYou've already guessed that letter!");
            getch();
            continue;
        }
        
        guessed[guess - 'A'] = 1;
        
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
        
        if(strchr(progress, '_') == NULL) {
            clear_screen();
            draw_hangman(incorrect_guesses, max_incorrect_guesses);
            printf("\nCongratulations! You guessed the word \"%s\"!", word);
            game_over = 1;
        } else if(incorrect_guesses >= max_incorrect_guesses) {
            clear_screen();
            draw_hangman(incorrect_guesses, max_incorrect_guesses);
            printf("\nSorry, you lost. The word was \"%s\".", word);
            game_over = 1;
        }
    }
    
    printf("\n\nPress any key to continue...");
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
        
        printf("\nPlay again? (Y/N): ");
        do {
            play_again = toupper(getch());
        } while(play_again != 'Y' && play_again != 'N');
        
    } while(play_again == 'Y');
    
    clear_screen();
    return 0;
}
