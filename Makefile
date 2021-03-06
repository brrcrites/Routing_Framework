SRC=$(filter-out %main.cc, Source/*)
OBJ=claim.o edge.o grid.o netlist.o node.o path.o pathsegment.o problem_object.o segmentgroup.o 

vpath %.cc Source/

all: $(OBJ) main.cc
	g++ -std=c++11 -o grid_router $^

test: all
	./grid_router Tests/test_sample.json
	
%.o: %.cc
	g++ -std=c++11 -c $^

cleanup:
	rm -f *.o

clean: cleanup
	rm -f grid_router

