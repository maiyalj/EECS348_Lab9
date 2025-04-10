CXX := g++

all: matrix.exe

matrix.exe: main.cpp
	@$(CXX) main.cpp -o matrix.exe
	@./matrix.exe
	@rm -f matrix.exe
