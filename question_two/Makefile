# Compiler
CC = gcc
CFLAGS = -fopenmp -pg

# Source file and executable
SRC = mandelbrot.c
EXE = mandelbrot

# Number of threads to test
THREAD_COUNTS = 1 2 4 8

# Default rule
all: $(EXE)

# Build executable from source file
$(EXE): $(SRC)
	$(CC) $(CFLAGS) -o $(EXE) $(SRC)

# Run the program
run: $(EXE)
	./$(EXE)

# Profile the program using gprof for each thread count
profile: $(EXE)
	@for threads in $(THREAD_COUNTS); do \
		echo "Profiling with $$threads threads..."; \
		OMP_NUM_THREADS=$$threads ./$(EXE); \
		gprof $(EXE) gmon.out > profile_$$threads.txt; \
		echo "Profile for $$threads threads:"; \
		cat profile_$$threads.txt; \
		echo ""; \
	done

# Clean up
clean:
	rm -f $(EXE) gmon.out profile*.txt
