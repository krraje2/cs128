CXX=clang++
CXX_FLAGS=-std=c++2a -g -O0 -Iincludes/ #-Wall -Wextra -Werror

exec: bin/exec
tests: bin/tests

bin/exec: src/driver.cc includes/cord.hpp src/cord.cc includes/cord-utilities.hpp src/cord-utilities.cc includes/cs128referencelist.hpp
	${CXX} ${CXX_FLAGS} src/driver.cc src/cord.cc src/cord-utilities.cc -o bin/exec

bin/tests: tests/tests.cc includes/cord.hpp src/cord.cc includes/cord-utilities.hpp src/cord-utilities.cc includes/cs128referencelist.hpp
	${CXX} ${CXX_FLAGS} tests/tests.cc src/driver.cc src/cord.cc  src/cord-utilities.cc -o bin/tests

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -rf bin/*
