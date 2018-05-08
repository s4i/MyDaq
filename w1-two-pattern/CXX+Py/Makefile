PYLIB = -I/usr/include/python3.5m -L/usr/lib/python3.5/config -lpython3.5m
all: w1
w1: w1_reader.cpp
	g++ -o $@ $^ $(PYLIB)
