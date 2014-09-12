
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


${BIN}/${EXEC}: ${OBJECTS}
	${CXX} ${LINKFLAGS} -o ${BIN}/${EXEC} ${OBJECTS}

${BIN}/%.o: ${SRC}/%.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<
