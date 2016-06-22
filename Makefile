CC = gcc

# use gdb, all warnings, link pthreads
FLAGS = -g -Wall -Wpedantic -Wextra -pthread
SOURCE = src/*.c
OUTPUT = myhttpd

all: $(SOURCE)
	$(CC) $(FLAGS) -o $(OUTPUT) $(SOURCE)

clean:
	@# remove build target, including .dSYM files on mac
	@rm -rf $(OUTPUT)*

