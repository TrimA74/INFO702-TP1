LD=g++
CXX=g++ -g -c
NAME=egalise
EXEC_SRC=\
	${NAME}.cpp

MODULE_SRC=\
	GrayLevelImage2D.cpp
MODULE_SRCB =\
	Histogramme.cpp
MODULE_OBJ=${MODULE_SRC:.cpp=.o}
MODULE_OBJB=${MODULE_SRCB:.cpp=.o}
EXEC_OBJ=${EXEC_SRC:.cpp=.o}

EXEC_PRG=${EXEC_SRC:.cpp=}

all: ${EXEC_PRG} ${MODULE_OBJ} ${MODULE_OBJB} ${EXEC_OBJ}

${NAME}: ${NAME}.o ${MODULE_OBJ} ${MODULE_OBJB}
	${LD} ${MODULE_OBJ} ${MODULE_OBJB} $< -o $@

.cpp.o: %.cpp %.hpp
	${CXX} $<

clean:
	rm -f ${EXEC_PRG} ${MODULE_OBJ} ${MODULE_OBJB} ${EXEC_OBJ}

