_GUI = $(if $(NOGUI),,-D GUI -Werror)
_DEBUG = $(if $(DEBUG),-D DEBUG,)
_OPT = $(if $(OPT),-O3 -flto,)
CC = gcc
CFLAGS = -g -std=c99 -Wall $(_OPT) $(_GUI) $(_DEBUG) -I./include
LDFLAGS = -lSDL2

.PHONY: clean doc check-syntax compile-all launch-tests

# rule to generate the doxygen documentation
doc:
	doxygen conf/doxygen.conf

# rule to remove all .o files and all executables
clean:
	- rm -f *.o
	- find . -maxdepth 1 -executable -type f \( ! -name "Makefile" \) -delete

# compile rules
%.o: ./src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

%.o: ./tests/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

# you should put all the .o files corresponding to your .c files as prerequisites of
# this rule (see examples)
# \ allows to go on the next line
check-syntax: sokoban.o loader.o test-loader.o test-move.o test-replay.o\
	replay.o play.o linked_list_map.o test-linked-list-map.o gui.o \
	queue_map.o test-queue-map.o test-solver


# all the rules to build the tests
test-loader: test-loader.o loader.o sokoban.o
	$(CC) $(CFLAGS) -o test-loader test-loader.o loader.o sokoban.o

test-move: test-move.o loader.o sokoban.o
	$(CC) $(CFLAGS) -o test-move test-move.o loader.o sokoban.o

test-replay: test-replay.o loader.o sokoban.o
	$(CC) $(CFLAGS) -o test-replay test-replay.o loader.o sokoban.o

test-linked-list-map: test-linked-list-map.o loader.o sokoban.o linked_list_map.o
	$(CC) $(CFLAGS) -o test-linked-list-map test-linked-list-map.o loader.o sokoban.o linked_list_map.o

test-queue-map: test-queue-map.o loader.o sokoban.o linked_list_map.o queue_map.o
	$(CC) $(CFLAGS) -o test-queue-map test-queue-map.o loader.o sokoban.o linked_list_map.o queue_map.o

test-solver: test-solver.o loader.o sokoban.o linked_list_map.o queue_map.o solver.o
	$(CC) $(CFLAGS) -o test-solver test-solver.o loader.o sokoban.o linked_list_map.o queue_map.o solver.o

# all the rules to build the other applications
replay: replay.o loader.o sokoban.o
	$(CC) $(CFLAGS) -o replay replay.o loader.o sokoban.o

play: play.o loader.o sokoban.o gui.o
	$(CC) $(CFLAGS) -o play play.o loader.o sokoban.o gui.o $(LDFLAGS)


# put all your applications and tests executables as prerequisite of this rule
# \ allows to go to the next line
compile-all: test-loader test-move test-replay replay play \
	test-linked-list-map test-queue-map test-solver
	 
compile-all-macOS: test-loader test-move test-replay \
	replay test-linked-list-map test-queue-map test-solver

# add all your test executables in the following variable. You should respect
# the order given in the project text
# \ allows to go to the next line
ALL_TESTS = test-loader test-move test-replay test-linked-list-map test-queue-map test-solver

ALL_TESTS_DEBUG = test-solver

launch-tests: $(ALL_TESTS)
	for x in $(ALL_TESTS); do ./$$x --all; done

launch-tests-debug: $(ALL_TESTS_DEBUG)
	for x in $(ALL_TESTS_DEBUG); do ./$$x --all; done

# add all .c, .h and .txt files in repository
svn-add-all-files:
	svn add --force src/*.c include/*.h tests/*.c data/*.txt --auto-props --parents --depth infinity -q

