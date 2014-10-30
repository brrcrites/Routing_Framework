
SRC=$(filter-out %main.cc, Source/*)
OBJ=$(SRC:.cc=.o) 

vpath %.cc Source/

all: $(OBJ) main.cc
	echo $(SRC)
	g++ -o grid_test $^

test: all
	./grid_test 100 100 10
	
%.o:%.cc
	g++ -c $^

cleanup:
	rm -f *.o

clean: cleanup
	rm -f grid_test

