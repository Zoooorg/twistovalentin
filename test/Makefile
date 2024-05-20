#Executable
EXEC = test

# Macros for directories
EXEC_DIR = ./bin
TEST_SRC_DIR = ./src
SRC_DIR = ../src
TEST_INC_DIR = ./include
INC_DIR = ../include

# Files
SRC_FILES = $(filter-out $(SRC_DIR)/Twisto.c, $(wildcard $(SRC_DIR)/*.c))
TEST_SRC_FILES = $(wildcard $(TEST_SRC_DIR)/*.c)
OBJ = $(SRC_FILES:.c=.o) 
TEST_OBJ = $(TEST_SRC_FILES:.c=.o)

# Compilation flags
CC = gcc
CPPFLAGS = -I$(INC_DIR) -I$(TEST_INC_DIR)
CFLAGS = -Wall -Wextra -std=c99 -pedantic -Wpedantic -g -O3
LDFLAGS = -lm

# Tools 
RM = rm -f

.PHONY: all clean distclean           

# --------------------------- Compilation ---------------------------

all: $(EXEC)

$(EXEC): $(SRC_FILES) $(TEST_SRC_FILES)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $(EXEC_DIR)/$@ $^ $(LDFLAGS)

# -------------------------- Cleaning -------------------------------

clean:
	$(RM) $(OBJ)
	$(RM) $(TEST_OBJ)
	$(RM) $(SRC_DIR)/*~
	$(RM) $(TEST_SRC_DIR)/*~

distclean: clean
	$(RM) $(EXEC_DIR)/$(EXEC)

