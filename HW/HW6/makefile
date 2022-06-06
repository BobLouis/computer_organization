FILE = cache.c
CC = gcc
exe = cache
INPUTPATH = ./src/
EXAMPLE = ./EXAMPLE_output/

all: trace1 trace2 trace3

	
trace1: cache
	./$(exe) < $(INPUTPATH)trace1.txt > ./trace1.out
	diff trace1.out $(EXAMPLE)trace1.out && echo "trace1 pass"
trace2: cache
	./$(exe) < $(INPUTPATH)trace2.txt > ./trace2.out
	diff trace2.out $(EXAMPLE)trace2.out && echo "trace2 pass"
trace3: cache
	./$(exe) < $(INPUTPATH)trace3.txt > ./out3
	diff trace3.out $(EXAMPLE)trace3.out && echo "trace3 pass"
trace4: cache
	./$(exe) < $(INPUTPATH)trace4.txt > ./trace4.out
	diff trace4.out $(EXAMPLE)trace4.out && echo "trace4 pass"
cache: 
	rm $(exe) | $(CC) $(FILE) -o $(exe) -lm
clean:
	rm $(exe) *.out