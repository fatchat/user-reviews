INCLUDES = -I.

# set up compiler and options
CXX = g++
CXXFLAGS = -g $(INCLUDES) -Wall -pg -std=c++0x
EXES = filereader filereader_test input_test

all : input_test

filereader : obj/filereader.o obj/beevolve.o obj/input.o
	g++ -o $@ $^ -lboost_regex

filereader_test: obj/filereader.o obj/filereader_test.o
	g++ -o $@ $^

input_test : obj/input_test.o obj/input_boost.o
	g++ -o $@ $^ -lboost_regex

obj/%.o : src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

depend:
	makedepend $(CXXFLAGS) -Y $(SRC)

clean:
	rm -f obj/* $(EXES)

