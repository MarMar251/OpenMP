# Compiler and flags
CC = gcc
CFLAGS = -fopenmp -pg

# Source file and executable
SRC = mandelbrot.c
EXE = mandelbrot
# Build executable
all: $(EXE)
$(EXE): $(SRC)
	$(CC) $(CFLAGS) -o $(EXE) $(SRC)
# Run the program with the specified number of threads
# Usage: make run THREADS=<number>
run: $(EXE)
	./$(EXE) $(THREADS)
# Profile the program using gprof
# Usage: make profile THREADS=<number>
profile: $(EXE)
	./$(EXE) $(THREADS)
	gprof $(EXE) gmon.out > profile$(THREADS).txt
	cat profile$(THREADS).txt
# Clean up
clean:
	rm -f $(EXE) gmon.out profile*.txt