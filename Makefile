# Pilot
PILOT_NAME = Twisto

# Macros for directories
EXEC_DIR = ./bin
SRC_DIR = ./src
INC_DIR = ./include
TEST_DIR = ./test
DOC_DIR = ./doc
DRIVERS_PATH = ../drivers

# Files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC_FILES:.c=.o)

# Compilation flags
CC = gcc
CPPFLAGS = -I$(INC_DIR)
CFLAGS = -Wall -Wextra -std=c99 -pedantic -Wpedantic -g -O3
LDFLAGS = -lm -pthread

# Tools 
RM = rm -f
DOC = doxygen

# Debugging
SANITIZE = off
ifeq ($(SANITIZE),on)
CFLAGS += -fsanitize = address
endif

.PHONY: all doc clean distclean cleandoc install try test cleantest      

# --------------------------- Compilation ---------------------------

all: $(PILOT_NAME)

$(PILOT_NAME): $(SRC_FILES)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $(EXEC_DIR)/$@ $^ $(LDFLAGS)

# ------------------------- Installation ----------------------------

install: $(DRIVERS_PATH)/$(PILOT_NAME)

$(DRIVERS_PATH)/$(PILOT_NAME): $(PILOT_NAME)
	cp $(EXEC_DIR)/$^ $(DRIVERS_PATH)

# ----------------------------- Try ---------------------------------

try: install
	cd .. ; ./GrandPrix

# ---------------------------- Tests --------------------------------

test:
	cd $(TEST_DIR) && $(MAKE)

# ------------------------ Documentation ----------------------------

doc:
	$(DOC) $(DOC_DIR)/Doc_config

# -------------------------- Cleaning -------------------------------

clean:
	$(RM) $(OBJ)
	$(RM) $(SRC_DIR)/*~

cleantest:
	cd $(TEST_DIR) && $(MAKE) distclean

cleandoc:
	$(RM) -r $(DOC_DIR)/latex
	$(RM) -r $(DOC_DIR)/html

distclean: clean cleandoc cleantest
	$(RM) $(EXEC_DIR)/$(PILOT_NAME)
	