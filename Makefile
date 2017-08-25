#######################################################################
#	COSC1254 - PROGRAMMING USING C++
#	SEMESTER 2 2017
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
BIG = files/big.txt
KADDATH = files/kaddath.txt
KJV = files/kjv.txt
TEST_FILE = prac_files/text.txt
CL_BIG_OP = files/word_count_clbig.csv
CL_KAD_OP = files/word_count_clkaddath.csv
CL_KJV_OP = files/word_count_clkjv.csv
CT_BIG_OP = files/word_count_ctbig.csv
CT_KAD_OP = files/word_count_ctkaddath.csv
CT_KJV_OP = files/word_count_ctkjv.csv
V_BIG_OP = files/word_count_vbig.csv
V_KAD_OP = files/word_count_vkaddath.csv
V_KJV_OP = files/word_count_vkjv.csv
S_BIG_OP = files/word_count_sbig.csv
S_KAD_OP = files/word_count_skaddath.csv
S_KJV_OP = files/word_count_skjv.csv
L_BIG_OP = files/word_count_lbig.csv
L_KAD_OP = files/word_count_lkaddath.csv
L_KJV_OP = files/word_count_lkjv.csv
OUTPUTFILES = files/word_count_clbig.csv files/word_count_clkaddath.csv files/word_count_clkjv.csv files/word_count_ctbig.csv files/word_count_ctkaddath.csv files/word_count_ctkjv.csv files/word_count_vbig.csv files/word_count_vkaddath.csv files/word_count_vkjv.csv files/word_count_sbig.csv files/word_count_skaddath.csv files/word_count_skjv.csv files/word_count_lbig.csv files/word_count_lkaddath.csv files/word_count_lkjv.csv
MAIN = datastructures.cpp loadDatastructures.cpp edit_dist.cpp
PROG = test_datastructures
OBJECTS = datastructures.o loadDatastructures.o edit_dist.o
RUN = ./
CUSTOM_LIST = custom_list
CUSTOM_TREE = custom_tree
VECTOR = vector
SET = set
LIST = list

main: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(OFLAG) $(PROG)
debug:
	$(CC) -g $(OFLAG) $(PROG) $(MAIN) $(CFLAGS)

#RUN CUSTOM LIST ON EACH FILE
custom_list_big:
	$(RUN)$(PROG) $(SFLAG) $(CUSTOM_LIST) $(DFLAG) $(DICT) $(TFLAG) $(BIG) $(OFLAG) $(CL_BIG_OP)
custom_list_kaddath:
	$(RUN)$(PROG) $(SFLAG) $(CUSTOM_LIST) $(DFLAG) $(DICT) $(TFLAG) $(KADDATH) $(OFLAG) $(CL_KAD_OP)
custom_list_kjv:
	$(RUN)$(PROG) $(SFLAG) $(CUSTOM_LIST) $(DFLAG) $(DICT) $(TFLAG) $(KJV) $(OFLAG) $(CL_KJV_OP)

#RUN CUSTOM TREE ON EACH FILE
custom_tree_big:
	$(RUN)$(PROG) $(SFLAG) $(CUSTOM_TREE) $(DFLAG) $(SHUF_DICT) $(TFLAG) $(BIG) $(OFLAG) $(CT_BIG_OP)
custom_tree_kaddath:
	$(RUN)$(PROG) $(SFLAG) $(CUSTOM_TREE) $(DFLAG) $(SHUF_DICT) $(TFLAG) $(KADDATH) $(OFLAG) $(CT_KAD_OP)
custom_tree_kjv:
	$(RUN)$(PROG) $(SFLAG) $(CUSTOM_TREE) $(DFLAG) $(SHUF_DICT) $(TFLAG) $(KJV) $(OFLAG) $(CT_KJV_OP)

#RUN VECTOR ON EACH FILE
vector_big:
	$(RUN)$(PROG) $(SFLAG) $(VECTOR) $(DFLAG) $(DICT) $(TFLAG) $(BIG) $(OFLAG) $(V_BIG_OP)
vector_kaddath:
	$(RUN)$(PROG) $(SFLAG) $(VECTOR) $(DFLAG) $(DICT) $(TFLAG) $(KADDATH) $(OFLAG) $(V_KAD_OP)
vector_kjv:
	$(RUN)$(PROG) $(SFLAG) $(VECTOR) $(DFLAG) $(DICT) $(TFLAG) $(KJV) $(OFLAG) $(V_KJV_OP)

#RUN SET ON EACH FILE
set_big:
	$(RUN)$(PROG) $(SFLAG) $(SET) $(DFLAG) $(DICT) $(TFLAG) $(BIG) $(OFLAG) $(S_BIG_OP)
set_kaddath:
	$(RUN)$(PROG) $(SFLAG) $(SET) $(DFLAG) $(DICT) $(TFLAG) $(KADDATH) $(OFLAG) $(S_KAD_OP)
set_kjv:
	$(RUN)$(PROG) $(SFLAG) $(SET) $(DFLAG) $(DICT) $(TFLAG) $(KJV) $(OFLAG) $(S_KJV_OP)

#RUN LIST ON EACH FILE
list_big:
	$(RUN)$(PROG) $(SFLAG) $(LIST) $(DFLAG) $(DICT) $(TFLAG) $(BIG) $(OFLAG) $(L_BIG_OP)
list_kaddath:
	$(RUN)$(PROG) $(SFLAG) $(LIST) $(DFLAG) $(DICT) $(TFLAG) $(KADDATH) $(OFLAG) $(L_KAD_OP)
list_kjv:
	$(RUN)$(PROG) $(SFLAG) $(LIST) $(DFLAG) $(DICT) $(TFLAG) $(KJV) $(OFLAG) $(L_KJV_OP)

clean:
	rm $(PROG) $(OUTPUTFILES) $(OBJECTS)
