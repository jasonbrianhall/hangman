# 🎮 Ultimate Terminal Hangman Game

[![Python](https://img.shields.io/badge/Python-3.6%2B-blue.svg)](https://www.python.org/)
[![C](https://img.shields.io/badge/C-MS--DOS-red.svg)](msdos/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE.md)
[![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20macOS%20%7C%20Windows%20%7C%20MS--DOS-lightgrey.svg)](https://github.com/jasonbrianhall/hangman)

A blazing-fast, ASCII-art powered Hangman game available in both Python and MS-DOS versions! This isn't your grandmother's Hangman - it's a modernized version with smooth animations and dynamic gameplay.

## 🖥️ Available Versions

### Python Version (root directory)
- Modern terminal-based implementation
- Dynamic ASCII art
- Cross-platform compatibility
- Real-time feedback

### MS-DOS Version (c/ directory)
- Authentic DOS gaming experience
- DJGPP C implementation using conio.h
- Compatible with DOSBox and real DOS systems
- Optimized for vintage hardware
- Classic ASCII interface

### UNIX Version (c/ directory)
- Authentic CLI gaming experience
- C implementation using NCurses
- Compatible with most UNIXes
- Optimized for vintage hardware
- Classic ASCII interface

### Windows Version (c/ directory)
- Authentic CLI gaming experience
- C implementation using conio.h
- Compatible with Windows
- Optimized for modern hardware
- Classic ASCII interface

## ✨ Features

- **Dynamic ASCII Art**: Watch the hangman come to life with smooth, progressive drawing
- **Smart Word Selection**: Curated dictionary with words between 5-25 letters
- **Intelligent Character Handling**: Special character support for compound words
- **Real-time Feedback**: Instant visual updates for every guess
- **Customizable Difficulty**: Adjust max guesses with command-line arguments
- **Clean Terminal UI**: Beautiful text-based interface with available letters tracking

## 🚀 Quick Start

### Python Version
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

### MS-DOS Version
```bash
# Navigate to the c directory
cd hangman/c

# Build using DJGPP (via Docker)
make msdos

# Run in DOSBox
make run

# Or run directly in DOS
hangman.exe (requires cwsdpmi.exe which is downloaded during the build)
```

### UNIX Version
```bash
# Navigate to the c directory
cd hangman/c

# Build using gcc
make unix

# Run in the CLI
./hangman
```

### UNIX Version
```bash
# Navigate to the c directory
cd hangman/c

# Build using gcc
make windows

# Run in the CLI
hangman_windows.exe or wine hangman_windows.exe if on Linux
```

## 🎯 Gameplay

1. A random word is selected from the dictionary
2. Guess letters one at a time
3. Watch the hangman develop with each incorrect guess
4. Track your available letters and progress
5. Win by completing the word or lose when the hangman is complete

## 🛠️ Requirements

### Python Version
- Python 3.6+
- curses library (built-in for Unix systems)
- A terminal that supports ASCII characters

### MS-DOS Version
For building:
- Docker (for DJGPP compilation environment)
- Make
- Internet connection (first build only)

For running:
- DOSBox or
- MS-DOS 5.0 or higher
- 286 or better CPU
- 640K RAM (memory efficient but slow words file)

### MS-DOS Version
For building:
- Docker (for mingw compilation environment)
- Make
- Internet connection (first build only)

For running:
- Windows

### UNIX Version
For building:
- gcc
- Make
- ncurses-devel library

For running:
- Unix or Linux
- 586 or better CPU
- 6MB RAM (Loads entire Words file into memory)

## 🎮 Controls

- Any letter key (a-z): Make a guess
- 'y': Play again
- 'n': Exit game
- ESC: Quit current game

## 🔧 Advanced Usage

Customize the difficulty by modifying the maximum number of incorrect guesses:

```bash
# Python version
python hangman.py -m <number_of_guesses>

# DOS version
hangman.exe -m <number_of_guesses>

# UNIX version
./hangman -m <number_of_guesses>

# windows version
hangman_windows.exe -m <number_of_guesses>
```

## 🤝 Contributing

Contributions are welcome! Feel free to:
- Add new features
- Expand the word dictionary
- Improve the ASCII art
- Optimize the code
- Report bugs
- Add support for new platforms

## 📝 License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.

## 🌟 Why This Game?

- Perfect for learning Python or C
- Great for teaching kids vocabulary
- Fun terminal-based entertainment
- Excellent example of cross-platform development
- Clean, well-documented code
- DOS gaming nostalgia

## 🔍 Keywords

hangman, python game, terminal game, dos game, windows cli game, unix game, ascii art, curses, command-line game, educational game, vocabulary game, python curses, terminal ui, cli game, text-based game, programming example, learning tool, msdos, djgpp

---

Made with ❤️  by Jason Hall <jasonbrianhall@gmail.com>
