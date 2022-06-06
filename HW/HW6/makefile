FILE = cache.c
CC = gcc
exe = cache
obj = 
INPUTPATH = ./src/
EXAMPLE = ./EXAMPLE_output/

all: trace1 trace2 trace3 trace4
	@diff trace1.out $(EXAMPLE)trace1.out && echo "trace1 pass"
	@diff trace2.out $(EXAMPLE)trace2.out && echo "trace2 pass"
	@diff trace3.out $(EXAMPLE)trace3.out && echo "trace3 pass"
	@diff trace4.out $(EXAMPLE)trace4.out && echo "trace4 pass"
	
trace1: cache
	./$(exe) $(INPUTPATH)trace1.txt ./trace1.out
trace2: cache
	./$(exe) $(INPUTPATH)trace2.txt ./trace2.out
trace3: cache
	./$(exe) $(INPUTPATH)trace3.txt ./trace3.out
trace4: cache
	./$(exe) $(INPUTPATH)trace4.txt ./trace4.out
cache: 
	rm $(exe) | $(CC) $(FILE) -o $(exe)
clean:
	rm $(exe) *.out