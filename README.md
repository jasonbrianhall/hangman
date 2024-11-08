# 🎮 Ultimate Terminal Hangman Game

[![Python](https://img.shields.io/badge/Python-3.6%2B-blue.svg)](https://www.python.org/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE.md)
[![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20macOS%20%7C%20Windows-lightgrey.svg)](https://github.com/yourusername/terminal-hangman)

A blazing-fast, ASCII-art powered Hangman game that runs right in your terminal! This isn't your grandmother's Hangman - it's a modernized, Python-powered version with smooth animations and dynamic gameplay.

## ✨ Features

- **Dynamic ASCII Art**: Watch the hangman come to life with smooth, progressive drawing
- **Smart Word Selection**: Curated dictionary with words between 5-25 letters
- **Intelligent Character Handling**: Special character support for compound words
- **Real-time Feedback**: Instant visual updates for every guess
- **Customizable Difficulty**: Adjust max guesses with command-line arguments
- **Clean Terminal UI**: Beautiful curses-based interface with available letters tracking

## 🚀 Quick Start

```bash
# Clone the repository
git clone https://github.com/jasonbrianhall/hangman

# Navigate to the directory
cd hangman

# Run with default settings
python hangman.py

# Run with custom max guesses (e.g., 8 guesses)
python hangman.py -m 8
```

## 🎯 Gameplay

1. A random word is selected from the dictionary
2. Guess letters one at a time
3. Watch the hangman develop with each incorrect guess
4. Track your available letters and progress
5. Win by completing the word or lose when the hangman is complete

## 🛠️ Requirements

- Python 3.6+
- curses library (built-in for Unix systems, requires windows-curses for Windows)
- A terminal that supports ASCII characters

## 🎮 Controls

- Any letter key (a-z): Make a guess
- 'y': Play again
- 'n': Exit game

## 🔧 Advanced Usage

Customize the difficulty by modifying the maximum number of incorrect guesses:

```bash
python hangman.py -m <number_of_guesses>
```

Example:
```bash
# For an easier game with more guesses
python hangman.py -m 15

# For a challenging game with fewer guesses
python hangman.py -m 6
```

## 🎨 Game Preview

```
_______
|     |
|     O
|    /|\
|     |
|    / \
|
|
-------

Available letters: A B C _ E F G H I J K L M N O P Q R S T U V W X Y Z
Word: _ _ _ _ _
Wrong guesses left: 6
```

## 🤝 Contributing

Contributions are welcome! Feel free to:
- Add new features
- Expand the word dictionary
- Improve the ASCII art
- Optimize the code
- Report bugs

## 📝 License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.

## 🌟 Why This Game?

- Perfect for learning Python
- Great for teaching kids vocabulary
- Fun terminal-based entertainment
- Excellent example of curses library usage
- Clean, well-documented code

## 🔍 Keywords

hangman, python game, terminal game, ascii art, curses, command-line game, educational game, vocabulary game, python curses, terminal ui, cli game, text-based game, programming example, learning tool

---

Made with ❤️  by Jason Hall <jasonbrianhall@gmail.com>
