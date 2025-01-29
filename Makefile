PROJ = infoteks
CXX = g++
CXXFLAGS = -Wall -Werror -Wextra
LIB = lib$(PROJ).so
PR1 = program1

all: mama

mama: $(LIB)
	$(CXX) $(CXXFLAGS) main.cc $(PR1)/$(PR1).cc -L. -l$(PROJ) -o check

$(LIB): $(PROJ).o
	$(CXX) $(CXXFLAGS) -shared -o $@ $<
	export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH

$(PROJ).o:
	$(CXX) $(CXXFLAGS) -c -fPIC lib/$(PROJ).cc -o $@

clean:
	rm *.o *.so check