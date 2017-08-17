#######################################################################
#	COSC1254 - PROGRAMMING USING C++
#	SEMESTER 1 2017
#	ASSIGNMENT 1 - DATA STRUCTURES
#	NAME:		JOSHUA HANSEN
#	STUDENT NUMBER: S3589185
########################################################################
CC = g++
CFLAGS = -Wall -pedantic -std=c++14 -lboost_system -lboost_program_options
DICT = -d files/dict.dat
FILE_1 = -t files/big.txt
FILE_2 = -t files/kaddath.txt
FILE_3 = -t files/kjv.txt
TEST_FILE = -t prac_files/text.txt
OUTPUT = -o files/output.txt
MAIN = datastructures.cpp
PROG = test_datastructures
RUN = ./
CUSTOM_LIST = -s custom_list
CUSTOM_TREE = -s custom_tree
VECTOR = -s vector
SET = -s set
LIST = -s list

make:
	$(CC) -o $(PROG) $(MAIN) $(CFLAGS)
debug:
	$(CC) -g -o $(PROG) $(MAIN) $(CFLAGS)

custom_list:
	$(RUN)$(PROG) $(CUSTOM_LIST) $(DICT) $(FILE_3) $(OUTPUT)

custom_tree:
	$(RUN)$(PROG) $(CUSTOM_TREE) $(DICT) $(TEST_FILE) $(OUTPUT)

vector:
	$(RUN)$(PROG) $(VECTOR) $(DICT) $(FILE_1) $(OUTPUT)

set:
	$(RUN)$(PROG) $(SET) $(DICT) $(FILE_2) $(OUTPUT)

list:
	$(RUN)$(PROG) $(LIST) $(DICT) $(FILE_2) $(OUTPUT)
