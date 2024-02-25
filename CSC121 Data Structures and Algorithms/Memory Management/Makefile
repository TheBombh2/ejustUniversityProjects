CXX = g++

all: build
build:
	"mkdir" -p "bin"
	$(CXX) -Wall mem.cpp -o bin/mem
grade:
	"mkdir" -p "bin"
	$(CXX) -D GRADING -Wall grade.cpp mem.cpp grade_util.cpp -o bin/grade
	bin/grade
run: build 
	bin/mem
archive:
	git archive --format=zip -o ejust-csc121-lab3.zip lab3

.PHONY: clean
clean: rm *.o *.exe
