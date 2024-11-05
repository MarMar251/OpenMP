# Compiler
CC = gcc
CFLAGS = -fopenmp -pg

# Source file and executable
SRC = mandelbrot.c
EXE = mandelbrot

# Default rule
all: $(EXE)

# Build executable from source file
$(EXE): $(SRC)
	$(CC) $(CFLAGS) -o $(EXE) $(SRC)

# Run the program
run: $(EXE)
	./$(EXE)

# Profile the program using gprof
profile: $(EXE)
	./$(EXE)
	gprof $(EXE) gmon.out > profile.txt
	cat profile.txt

# Clean up
clean:
	rm -f $(EXE) gmon.out profile.txt