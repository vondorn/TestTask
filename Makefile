PROJ = infoteks
CXX = g++
CXXFLAGS = -Wall -Werror -Wextra
LIB = lib$(PROJ).so
PR1 = program1
PR2 = program2

all: clean mama

mama: $(LIB)
	$(CXX) $(CXXFLAGS) $(PR1)/$(PR1).cc -L. -l$(PROJ) -o cl
	$(CXX) $(CXXFLAGS) $(PR2)/$(PR2).cc -L. -l$(PROJ) -o se
	

$(LIB): $(PROJ).o
	$(CXX) $(CXXFLAGS) -shared -o $@ $<
	export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH

$(PROJ).o:
	$(CXX) $(CXXFLAGS) -c -fPIC lib/$(PROJ).cc -o $@

clean:
	rm -f *.o cl se