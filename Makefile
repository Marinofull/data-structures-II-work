#   Description: Makefile.
#   Author: Marino Souza [intmarinoreturn0@gmail.com] <@marinofull>
#

#syntax
#
# target: dependencies
# [TAB]system command
#
# UPCASEWORD= means constant expression
#
# $^ is substituted with all of the target ’ s dependancy files
# $< is the first dependancy and $@ is the target files

CC=gcc
# CFLAGS= -c -Wall
CFLAGS= -c
LDFLAGS= -g -o
EXECUTABLE=trabalho2-marino
SOURCE=$(EXECUTABLE).c


all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCE)
	$(CC) -o $@ $^
	# enjoy :D

# Regular Expression very OverPower
# bin/%.o: %.cpp
# 	$(CC) $(CFLAGS) $< -o $@
# #

# every command above belongs to the tree of "all" command.
# from here, the commands below are independents.

run:
	./$(EXECUTABLE)

clean: cleanBin cleanFiles

cleanBin:
	rm -rf $(EXECUTABLE)

cleanFiles:
	rm -rf lili

# help

help:
	@echo "type 'make' to compile the toll"
	@echo "type 'make clean' to clear the binaries, files and tests flags"
	@echo "to run, type './lala < input'"
