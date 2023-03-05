#!/usr/bin/env python

import random
import curses
import traceback

# Define the hangman drawing function
def draw_hangman(screen, incorrect_guesses, max_incorrect_guesses, guesses, progress):
    screen.clear()
    screen.addstr(0, 0, '_______ ')
    screen.addstr(1, 0, '|     |')
    screen.addstr(2, 0, '|')      
    screen.addstr(3, 0, '|')
    screen.addstr(4, 0, '|')
    screen.addstr(5, 0, '|')
    screen.addstr(6, 0, '|')
    screen.addstr(7, 0, '|')
    screen.addstr(8, 0, '|')
    screen.addstr(9, 0, '-------')
    if incorrect_guesses>0:
        screen.addstr(2, 6, 'O')
    if incorrect_guesses>1:
        screen.addstr(3, 6, '|')
    if incorrect_guesses>2:
        screen.addstr(4, 6, '|')
    if incorrect_guesses>3:
        screen.addstr(4, 5, '/')
    if incorrect_guesses>4:
        screen.addstr(4, 7, '\\')
    if incorrect_guesses>5:
        screen.addstr(5, 6, '|')
    if incorrect_guesses>6:
        screen.addstr(6, 5, '/')
    if incorrect_guesses>7:
        screen.addstr(6, 7, '\\')
    if incorrect_guesses>8:
        screen.addstr(7, 4, '/')
    if incorrect_guesses>9:
        screen.addstr(7, 8, '\\')
    if incorrect_guesses>10:
        screen.addstr(8, 3, '/')
    if incorrect_guesses>11:
        screen.addstr(8, 9, '\\')


    screen.addstr(11, 0, ' '.join(['Available letters:'] + [l.upper() if l not in guesses else '_' for l in 'abcdefghijklmnopqrstuvwxyz']))
    screen.addstr(14, 0, ' '.join(progress))
    screen.addstr(16, 0, f'Wrong guesses left: {max_incorrect_guesses - incorrect_guesses}')
    screen.refresh()

def main():
    # Load words from the file
    with open('words') as f:
        words = f.read().splitlines()

    # Filter words to include only those with 5-25 letters
    words = [word.lower() for word in words if len(word) >= 5 and len(word) <= 25]

    # Select a random word from the list
    word = random.choice(words)

    # Initialize the game state
    progress = ['_'] * len(word)
    guesses = set()
    incorrect_guesses = 0
    max_incorrect_guesses = 12

    # Initialize curses
    screen = curses.initscr()


    # Play the game
    play_again = True
    try:
        while play_again:
            # Reset game state
            word = random.choice(words)
            progress = ['_'] * len(word)
            guesses = set()
            incorrect_guesses = 0
            draw_hangman(screen, incorrect_guesses, max_incorrect_guesses, guesses, progress)

            # Play the game
            while '_' in progress and incorrect_guesses < max_incorrect_guesses:
                guess = ''
                while not guess.isalpha():
                    guess = screen.getkey().lower()
                if guess in guesses:
                    screen.addstr(12, 0, f"You've already guessed {guess}.")
                elif guess in word:
                    screen.addstr(12, 0, 'Correct!')
                    for i, letter in enumerate(word):
                        if letter == guess:
                            progress[i] = letter
                else:
                    screen.addstr(12, 0, 'Incorrect.')
                    incorrect_guesses += 1
                    draw_hangman(screen, incorrect_guesses, max_incorrect_guesses, guesses, progress)
                guesses.add(guess)
                draw_hangman(screen, incorrect_guesses, max_incorrect_guesses, guesses, progress)
            # End the game
            if '_' not in progress:
                screen.addstr(16, 0, f'Congratulations! You guessed the word "{word}" with {incorrect_guesses} incorrect guesses.')
            else:
                screen.addstr(16, 0, f'Sorry, you lost. The word was "{word}".')
            screen.addstr(18, 0, 'Do you want to play again? (y/n)')
            play_again_input = ''
            while play_again_input not in ['y', 'n']:
                play_again_input = screen.getkey().lower()
            play_again = play_again_input == 'y'
    except:
        curses.endwin()
        traceback.print_exc()
        pass
    curses.endwin()

if __name__=="__main__":
    main()
