CUR_DIR=.

ALG_DIR=${CUR_DIR}/algorithm
BBS_DIR=${CUR_DIR}/algorithm/bbs04
DEV_DIR=${CUR_DIR}/devcore
MAIN_DIR=${CUR_DIR}

INC_DIR= -I${MAIN_DIR}  -I${ALG_DIR}

G_SRC = ${wildcard  ${ALG_DIR}/*.cpp} \
	  ${wildcard  ${BBS_DIR}/*.cpp} \
	  ${wildcard  ${DEV_DIR}/*.cpp} 

G_OBJ = ${wildcard ${MAIN_DIR}/groupsiglib/*.o}

SRC = ${wildcard  ${MAIN_DIR}/*.cpp}

OBJ = ${patsubst %.cpp, %.o, ${SRC}}

TARGET=main
CC=g++
CCFLAGS=-g -std=c++11 ${INC_DIR} 
LFLAGS=-lgmp -lpbc -lpbc_sig -lpthread -lboost_system -lboost_thread -lboost_filesystem

${TARGET}: ${OBJ}
	${CC} ${notdir ${OBJ} } ${G_OBJ} -o $@ ${LFLAGS} 
	mv ${TARGET} gsc
	echo "Compile done."
${OBJ}:${SRC}
	$(CC) ${CCFLAGS} -c $? ${LFLAGS}  

groupsig:


clean:
	rm -f ${OBJ}
	rm -f *.o
	rm -f *~
	rm -f ${TARGET}
	echo "Clean done."

test :
	echo $(SRC)
	echo $(OBJ)
	echo ${CC} ${notdir ${OBJ} } "-o" $@ ${LFLAGS}
