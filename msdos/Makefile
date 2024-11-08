# Makefile for Hangman Game
VERSION=1.0

# Source files
SRCS = hangman.c

# Output executable and required files
DOS_TARGET = hangman.exe
UNIX_TARGET = hangman
WORDS_FILE = ../words
DOS_WORDS = words

# Docker image for DJGPP
DJGPP_IMAGE = djfdyuruiry/djgpp

# Correct CSDPMI URL
CSDPMI_URL = http://na.mirror.garr.it/mirrors/djgpp/current/v2misc/csdpmi7b.zip

# Get current user and group IDs for Docker
USER_ID = $(shell id -u)
GROUP_ID = $(shell id -g)

# Default target
all: msdos unix

# Clean target to remove generated files
clean:
	rm -f $(DOS_TARGET) csdpmi7b.zip || true
	rm -rf csdpmi || true
	rm *.exe || true
	rm *.EXE || true
	rm *.zip || true
	rm $(DOS_WORDS) || true

# Target to pull the DJGPP Docker image
pull-djgpp:
	docker pull $(DJGPP_IMAGE)

# Target to download CSDPMI
get-csdpmi:
	wget $(CSDPMI_URL)
	unzip -o csdpmi7b.zip -d csdpmi

# Target to copy and convert words file to DOS format
get-words:
	cp $(WORDS_FILE) $(DOS_WORDS)
	unix2dos $(DOS_WORDS) || true

# Target to build for MS-DOS using DJGPP in Docker
msdos: pull-djgpp get-csdpmi get-words
	docker run --rm -v $(PWD):/src:z -u $(USER_ID):$(GROUP_ID) $(DJGPP_IMAGE) /bin/sh -c "cd /src && gcc $(SRCS) -o $(DOS_TARGET)"
	cp csdpmi/bin/CWSDPMI.EXE .

unix: gcc hangman.c -lcurses -o $(UNIX_TARGET)

# Target to run the MS-DOS executable using DOSBox
run: msdos
	dosbox $(DOS_TARGET)

.PHONY: all clean pull-djgpp get-csdpmi get-words msdos run
