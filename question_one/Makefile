# Compiler
CC = gcc
CFLAGS = -fopenmp -pg

# Source and executable
SRC = integral.c
EXE = integral

# Thread counts for profiling
THREAD_COUNTS = 1 2 4 8

# Build executable
all: $(EXE)

$(EXE): $(SRC)
	$(CC) $(CFLAGS) -o $(EXE) $(SRC) -lm

# Run the program with profiling for each thread count
profile: $(EXE)
	@for threads in $(THREAD_COUNTS); do \
		echo "Profiling with $$threads threads..."; \
		OMP_NUM_THREADS=$$threads ./$(EXE); \
		gprof $(EXE) gmon.out > profile_$$threads.txt; \
		cat profile_$$threads.txt; \
	done

# Clean up
clean:
	rm -f $(EXE) gmon.out profile*.txt
