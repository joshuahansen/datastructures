#######################################################################
#	COSC1254 - PROGRAMMING USING C++
#	SEMESTER 1 2017
#	ASSIGNMENT 1 - DATA STRUCTURES
#	NAME:		JOSHUA HANSEN
#	STUDENT NUMBER: S3589185
########################################################################
CC = g++
CFLAGS = -Wall -pedantic -std=c++14 -lboost_system -lboost_program_options
DFLAG = -d
TFLAG = -t
OFLAG = -o
SFLAG = -s
DICT = files/dict.dat
SHUF_DICT = files/shuf_dict.dat
FILE_1 = files/big.txt
FILE_2 = files/kaddath.txt
FILE_3 = files/kjv.txt
TEST_FILE = prac_files/text.txt
OUTPUT = files/word_count.csv
OUTPUT2 = files/word_count2.csv
MAIN = datastructures.cpp
PROG = test_datastructures
RUN = ./
CUSTOM_LIST = custom_list
CUSTOM_TREE = custom_tree
VECTOR = vector
SET = set
LIST = list

make:
	$(CC) $(OFLAG) $(PROG) $(MAIN) $(CFLAGS)
debug:
	$(CC) -g $(OFLAG) $(PROG) $(MAIN) $(CFLAGS)

custom_list:
	$(RUN)$(PROG) $(SFLAG) $(CUSTOM_LIST) $(DFLAG) $(DICT) $(TFLAG) $(FILE_1) $(OFLAG) $(OUTPUT)

custom_tree:
	$(RUN)$(PROG) $(SFLAG) $(CUSTOM_TREE) $(DFLAG) $(SHUF_DICT) $(TFLAG) $(FILE_1) $(OFLAG) $(OUTPUT2)

vector:
	$(RUN)$(PROG) $(SFLAG) $(VECTOR) $(DFLAG) $(DICT) $(TFLAG) $(FILE_1) $(OFLAG) $(OUTPUT)

set:
	$(RUN)$(PROG) $(SFLAG) $(SET) $(DFLAG) $(DICT) $(TFLAG) $(FILE_1) $(OFLAG) $(OUTPUT)

list:
	$(RUN)$(PROG) $(SFLAG) $(LIST) $(DFLAG) $(DICT) $(TFLAG) $(FILE_1) $(OFLAG) $(OUTPUT)

clean:
	rm $(PROG) $(OUTPUT)
