SHELL = /bin/sh

# Linux, Darwin or Windows_NT
OS=$(shell uname -s)

FRONTEND_SRC = $(wildcard interface/*.c)
MAZE_SRC=$(filter-out maze.c, $(wildcard *.c))
TESTS_SRC=$(wildcard tests/*.c)

FRONTEND_OBJS = $(patsubst %.c,%.o,$(FRONTEND_SRC) $(MAZE_SRC) maze.c)
TEST_OBJS:=$(patsubst %.c,%.o,$(MAZE_SRC) $(TESTS_SRC))

DIR_BUILD=build
INSTALL_DIR=any_other_catalog
NAME_MAZE=s21_maze
NAME_TEST=test_s21_maze
OS_MAC_UX=-lsubunit
CPP_LIST=*.h *.c $(TESTS_SRC) $(FRONTEND_SRC) tests/*.h interface/*.h

CC=gcc
FLAGS=-std=c11 -Wall -Wextra -Werror 
CFLAGS:=$(FLAGS) -c
GFLAGS = -lncurses

.PHONY: all install uninstall clean tests control mk_dir launch

all: launch
	rm -f $(DIR_BUILD)/*.o

launch: install
	./$(INSTALL_DIR)/$(NAME_MAZE)
	rm -f $(DIR_BUILD)/*.o

clean:
	-rm -f $(DIR_BUILD)/*

tests: clean mk_dir $(TEST_OBJS)
ifeq ($(OS),Darwin)
	$(eval OS_MAC_UX=-I/opt/homebrew/include -L/opt/homebrew/lib)
endif
	$(CC) $(FLAGS) $(GCOV) $(DIR_BUILD)/*.o -o $(DIR_BUILD)/$(NAME_TEST) -lcheck -lm $(OS_MAC_UX) -L.
	./$(DIR_BUILD)/$(NAME_TEST)
	rm -f $(DIR_BUILD)/*.o

%.o: %.c
	$(CC) $(CFLAGS) $(GCOV) $< -o $(DIR_BUILD)/$(notdir $@)

frontend: clean mk_dir $(FRONTEND_OBJS)
	$(CC) $(FLAGS) $(DIR_BUILD)/*.o -o $(DIR_BUILD)/$(NAME_MAZE) $(GFLAGS)

install: clean frontend 
	mkdir -p $(INSTALL_DIR) 
	mkdir -p $(INSTALL_DIR)/mazes
	mkdir -p $(INSTALL_DIR)/caves
	cp $(DIR_BUILD)/$(NAME_MAZE) $(INSTALL_DIR)/
	cp mazes/* $(INSTALL_DIR)/mazes
	cp caves/* $(INSTALL_DIR)/caves
	make clean

uninstall:
	rm -Rf $(INSTALL_DIR)

mk_dir:
	mkdir -p $(DIR_BUILD)

control: tests
	-cppcheck --enable=all --suppress=missingIncludeSystem --error-exitcode=1 $(CPP_LIST)
	find . -type f \( -name "*.c" -o -name "*.h" \) -exec clang-format -n -style=Google {} \;
	-valgrind --tool=memcheck --leak-check=yes $(DIR_BUILD)/$(NAME_TEST)

clang:
	find . -type f \( -name "*.c" -o -name "*.h" \) -exec clang-format -i -style=Google {} \;

