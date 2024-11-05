# Compiler
CC = gcc
CFLAGS = -fopenmp -pg

# Source and executable
SRC = integral.c
EXE = integral

# Build executable
all: $(EXE)

$(EXE): $(SRC)
	$(CC) $(CFLAGS) -o $(EXE) $(SRC) -lm

# Run the program 
run: $(EXE)
	./$(EXE)


# Profile the program using gprof
profile: $(EXE)
	./$(EXE) $(THREADS)
	gprof $(EXE) gmon.out > profile.txt
	cat profile.txt

# Clean up
clean:
	rm -f $(EXE) gmon.out profile.txt