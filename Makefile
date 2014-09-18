
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

${BIN}/${EXEC}: ${OBJECTS} ${BIN}/parser.o ${BIN}/lexer.o
	${CXX} ${LINKFLAGS} -o ${BIN}/${EXEC} ${OBJECTS} ${BIN}/lexer.o ${BIN}/parser.o

${SRC}/parser.tab.c: ${SRC}/parser.y
	bison --defines=${INC}/parser.tab.h -o ${SRC}/parser.tab.c ${SRC}/parser.y

${SRC}/lexer.tab.c: ${SRC}/lexer.lex
	flex -o ${SRC}/lexer.tab.c ${SRC}/lexer.lex

${BIN}/parser.o: ${SRC}/parser.tab.c
	${CXX} ${CXXFLAGS} -Wno-write-strings -c -o $@ $<

${BIN}/lexer.o: ${SRC}/lexer.tab.c
	${CXX} ${CXXFLAGS} -c -o $@ $<

${BIN}/%.o: ${SRC}/%.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<
