
SRC := ./src
INC := ./inc
BIN := ./bin
EXEC := mksrc

CXX := g++
CXXFLAGS := -Wall --std=c++11 -I${INC}
LINKFLAGS := 

OBJECTS := $(patsubst ${SRC}/%.cpp, ${BIN}/%.o, $(wildcard ${SRC}/*.cpp))

.PHONEY: all clean install

all: ${BIN}/${EXEC}

clean:
	rm -f ${BIN}/*
	rm -f ${SRC}/*.cc
	rm -f ${INC}/*.hh

${BIN}/${EXEC}: ${BIN}/language-parser.o ${BIN}/language-lexer.o ${OBJECTS}
	${CXX} ${LINKFLAGS} -o ${BIN}/${EXEC} ${OBJECTS} ${BIN}/language-lexer.o ${BIN}/language-parser.o

${SRC}/language-parser.tab.cc: ${SRC}/language-parser.yy
	bison --defines=${INC}/language-parser.tab.hh -o ${SRC}/language-parser.tab.cc ${SRC}/language-parser.yy
	mv ${SRC}/*.hh ${INC}/

${SRC}/language-lexer.tab.cc: ${SRC}/language-lexer.ll
	flex -o ${SRC}/language-lexer.tab.cc ${SRC}/language-lexer.ll

${BIN}/language-parser.o: ${SRC}/language-parser.tab.cc
	${CXX} -Wno-deprecated-register --std=c++11 -I${INC} -c -o $@ $<

${BIN}/language-lexer.o: ${SRC}/language-lexer.tab.cc
	${CXX} -Wno-deprecated-register --std=c++11 -I${INC} -c -o $@ $<

${BIN}/%.o: ${SRC}/%.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<
