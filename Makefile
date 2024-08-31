cc := g++

coflags := -Isrc/include -O3  -Wall
cbflags := -lncurses -pthread

objs := $(shell find src -iname '*.cpp' | sed "s,src,obj,g; s,cpp$$,o,g" | grep -v "obj/app/main.o")

testsbin := $(shell find tests -iname '*.cpp'  | sed "s,tests/,bin/test_,g; s,\.cpp$$,,g")

.PHONY: all objects clean

all: compile_flags.txt $(objs) $(testbin) obj/app/main.o bin/game

objects: $(objs)

clean:
	rm -f $(objs) $(testbin) bin/game
	rm -f bin/bm_*
	rm -f bin/test_*
	rm -f obj/main.o
	rm -f compile_flags.txt
	rm -f dat/*.dat
	rm -rf obj
	rm -rf bin

obj/%.o: src/%.cpp
	mkdir -p $(shell dirname $< | sed 's,src,obj,g')
	$(cc) $(coflags) -c -o $@ $<

bin/game: $(objs) obj/app/main.o
	mkdir -p bin
	$(cc) -o $@ $^ $(cbflags)

bin/test_%: tests/%.cpp $(objs)
	mkdir -p bin
	$(cc) -o $@ $^ $(coflags) $(cbflags)


tests: $(testsbin)

test: tests
	for test in bin/test*; do echo -e "\033[32m[+]" running $$test "\033[00m"; $$test || echo -e "\033[31m[-] returned error: $$? \033[00m"; done

compile_flags.txt:
	for flag in $(coflags); do echo $$flag; done > compile_flags.txt
