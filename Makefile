CXX  = clang++

SRCS = main gpst_lib
OBJS = $(addprefix src/, $(addsuffix .o, $(SRCS)))

INC=include
INCS = $(wildcard include/*.h)

.PHONY: all clean $(INC)/gpst_leaps.h

all: gpst

$(INC)/gpst_leaps.h:
	./update_gpst.sh

src/%.o: src/%.cpp $(INCS)
	@echo Making $@
	$(CXX) -I$(INC) -c -O3 $< -o $@

gpst: $(OBJS)
	$(CXX) -o $@ $^

clean:
	-rm src/*.o
