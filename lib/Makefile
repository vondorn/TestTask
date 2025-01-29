PROJ = infoteks
CXX = g++
CXXFLAGS = -Wall -Werror -Wextra
LIB = lib$(PROJ).so


all: check

check: $(LIB)
	$(CXX) $(CXXFLAGS) q.cc -L. -l$(PROJ) -o check
	./check
	
$(LIB): $(PROJ).o
	$(CXX) $(CXXFLAGS) -shared -o $@ $<
	export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH

$(PROJ).o:
	$(CXX) $(CXXFLAGS) -c -fPIC $(PROJ).cc -o $@

clean:
	rm *.o *.so check