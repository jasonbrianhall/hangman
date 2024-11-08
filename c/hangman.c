#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdarg.h>
#ifdef WIN32
#include <windows.h>
#define MSDOS
#endif

#ifdef MSDOS
#include <conio.h>
#include <dos.h>
#else
#include <curses.h>
#endif

#define MAX_WORD_LENGTH 25
#define MIN_WORD_LENGTH 5
#define MAX_WORDS 5000000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

void print_message(const char *format, ...) {
    va_list args;
    va_start(args, format);
    #ifdef MSDOS
    vprintf(format, args);
    #else
    vw_printw(stdscr, format, args);
    refresh();
    #endif
    va_end(args);
}

// Global variables
char words[MAX_WORDS][MAX_WORD_LENGTH + 1];
int num_words = 0;

// Function to load words from file  (MSDOS is memory efficient but slow)
int load_words(void) {
    FILE *fp;
    char word[MAX_WORD_LENGTH + 1];
    char selected_word[MAX_WORD_LENGTH + 1];
    long file_position;
    int valid_words = 0;
    int selected_index;
    
    #ifdef MSDOS
    // Initialize random seed
    srand((unsigned)time(NULL));
    
    // First pass: count valid words
    fp = fopen("WORDS.TXT", "r");
    if(fp == NULL) {
        print_message("Error: Cannot open WORDS.TXT\n");
        return 0;
    }
    
    while(fgets(word, MAX_WORD_LENGTH + 1, fp) != NULL) {
        // Remove newline and carriage return
        word[strcspn(word, "\n")] = 0;
        word[strcspn(word, "\r")] = 0;
        
        if(strlen(word) >= MIN_WORD_LENGTH && strlen(word) <= MAX_WORD_LENGTH) {
            valid_words++;
        }
    }
    
    if(valid_words == 0) {
        fclose(fp);
        return 0;
    }
    
    // Pick a random valid word index
    selected_index = rand() % valid_words;
    
    // Second pass: get the selected word
    rewind(fp);
    valid_words = 0;
    
    while(fgets(word, MAX_WORD_LENGTH + 1, fp) != NULL) {
        word[strcspn(word, "\n")] = 0;
        word[strcspn(word, "\r")] = 0;
        
        if(strlen(word) >= MIN_WORD_LENGTH && strlen(word) <= MAX_WORD_LENGTH) {
            if(valid_words == selected_index) {
                strcpy(words[0], word);
                num_words = 1;
                break;
            }
            valid_words++;
        }
    }
    
    fclose(fp);
    return num_words;
    
    #else
    // Original implementation for non-MSDOS systems
    fp = fopen("WORDS.TXT", "r");
    if(fp == NULL) {
        print_message("Error: Cannot open WORDS.TXT\n");
        return 0;
    }
    
    while(fgets(word, MAX_WORD_LENGTH + 1, fp) != NULL && num_words < MAX_WORDS) {
        word[strcspn(word, "\n")] = 0;
        word[strcspn(word, "\r")] = 0;
        
        if(strlen(word) >= MIN_WORD_LENGTH && strlen(word) <= MAX_WORD_LENGTH) {
            strcpy(words[num_words], word);
            num_words++;
        }
    }
    
    fclose(fp);
    return num_words;
    #endif
}

// Function to clear screen
void clear_screen(void) {
    #ifdef _WIN32
        system("cls");
    #elif defined(__DJGPP__) || defined(__MSDOS__)
        clrscr();
    #else
        system("clear");
    #endif
}
// Function to draw the hangman
void draw_hangman(int incorrect_guesses, int max_incorrect_guesses) {
    int temp = max_incorrect_guesses / 12;
    
    print_message("  +-----+\n");
    print_message("  |     |\n");
    print_message("  |     %c\n", (incorrect_guesses > 0) ? 'O' : ' ');
    print_message("  |    %c%c%c\n",
           (incorrect_guesses > 3 || incorrect_guesses >= max_incorrect_guesses) ? '/' : ' ',
           (incorrect_guesses > 1 || incorrect_guesses >= max_incorrect_guesses) ? '|' : ' ',
           (incorrect_guesses > 4 || incorrect_guesses >= max_incorrect_guesses) ? '\\' : ' ');
    print_message("  |     %c\n", (incorrect_guesses > 2 || incorrect_guesses >= max_incorrect_guesses) ? '|' : ' ');
    print_message("  |    %c %c\n",
           (incorrect_guesses > 5 || incorrect_guesses >= max_incorrect_guesses) ? '/' : ' ',
           (incorrect_guesses > 6 || incorrect_guesses >= max_incorrect_guesses) ? '\\' : ' ');
    print_message("  |   %c   %c\n",
           (incorrect_guesses > 7 || incorrect_guesses >= max_incorrect_guesses) ? '/' : ' ',
           (incorrect_guesses > 8 || incorrect_guesses >= max_incorrect_guesses) ? '\\' : ' ');
    print_message("  |  %c     %c\n",
           (incorrect_guesses > 9 || incorrect_guesses >= max_incorrect_guesses) ? '/' : ' ',
           (incorrect_guesses > 10 || incorrect_guesses >= max_incorrect_guesses) ? '\\' : ' ');
    print_message("  | %c       %c\n",
           (incorrect_guesses > 11 || incorrect_guesses >= max_incorrect_guesses) ? '/' : ' ',
           (incorrect_guesses > 12 || incorrect_guesses >= max_incorrect_guesses) ? '\\' : ' ');
    print_message("  |%c         %c\n",
           (incorrect_guesses > 13 || incorrect_guesses >= max_incorrect_guesses) ? '/' : ' ',
           (incorrect_guesses >= max_incorrect_guesses) ? '\\' : ' ');

    print_message("  |\n");
    print_message("=====\n\n");
}

// Function to display available letters
void display_available_letters(const char *guessed) {
    int i;
    print_message("\nAvailable letters: ");
    for(i = 0; i < 26; i++) {
        if(!guessed[i]) {
            print_message("%c ", 'A' + i);
        } else {
            print_message("_ ");
        }
    }
    print_message("\n");
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
    
    // Select a random index from 0 to num_words-1
    int random_index = rand() % num_words;
    // Copy the randomly selected word
    strcpy(word, words[random_index]);
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
        print_message("\nWord: ");
        for(i = 0; i < word_len; i++) {
            print_message("%c ", progress[i]);
        }
        print_message("\n");
        
        print_message("\nWrong guesses left: %d", max_incorrect_guesses - incorrect_guesses);
        
        display_available_letters(guessed);
        
        print_message("\nEnter your guess (ESC to quit): ");
        guess = toupper(getch());
        
        if(guess == 27) { // ESC key
            game_over = 1;
            continue;
        }
        
        if(!isalpha(guess)) {
            continue;
        }
        
        if(guessed[guess - 'A']) {
            print_message("\nYou've already guessed that letter!");
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
            print_message("\nCongratulations! You guessed the word \"%s\"!", word);
            game_over = 1;
        } else if(incorrect_guesses >= max_incorrect_guesses) {
            clear_screen();
            draw_hangman(incorrect_guesses, max_incorrect_guesses);
            print_message("\nSorry, you lost. The word was \"%s\".", word);
            game_over = 1;
        }
    }
    
    print_message("\n\nPress any key to continue...");
    getch();
}

int main(int argc, char *argv[]) {
    int max_guesses = 12;
    char play_again;
    int total_words;
    // Parse command line arguments
    if(argc == 3 && strcmp(argv[1], "-m") == 0) {
        max_guesses = atoi(argv[2]);
        if(max_guesses <= 0) {
            print_message("Invalid number of guesses\n");
            return 1;
        }
    }
    
    #ifndef MSDOS
    initscr();          // Start curses mode
    cbreak();           // Line buffering disabled
    //noecho();           // Don't echo keystrokes
    keypad(stdscr, TRUE);  // Enable keypad (for arrow keys etc)
    #endif
    
    // Initialize random number generator
    srand(time(NULL));
    
    // Load words
    #ifndef MSDOS
    total_words = load_words();
    if(total_words == 0) {
        print_message("Failed to load words\n");
        endwin();           // End curses mode
        return 1;
    }
    #endif
    // Main game loop
    do {
        #ifdef MSDOS
        total_words = load_words();
        if(total_words == 0) {
            print_message("Failed to load words\n");
            return 1;
        }
        #endif

        play_game(max_guesses);
        
        print_message("\nPlay again? (Y/N): ");
        do {
            play_again = toupper(getch());
        } while(play_again != 'Y' && play_again != 'N');
        
    } while(play_again == 'Y');
    
    clear_screen();
    #ifndef MSDOS
    endwin();           // End curses mode
    #endif
    return 0;
}
