CUR_DIR=.

ALG_DIR=${CUR_DIR}/algorithm
BBS_DIR=${CUR_DIR}/algorithm/bbs04
DEV_DIR=${CUR_DIR}/devcore
MAIN_DIR=${CUR_DIR}

INC_DIR= -I${MAIN_DIR}

SRC = ${wildcard  ${ALG_DIR}/*.cpp} \
	  ${wildcard  ${BBS_DIR}/*.cpp} \
	  ${wildcard  ${DEV_DIR}/*.cpp} \
	  ${wildcard  ${MAIN_DIR}/*.cpp}

OBJ = ${patsubst %.cpp, %.o, ${SRC}}

TARGET=gsc
TARGET1 = mgs
CC=g++
CCFLAGS=-g -std=c++11 ${INC_DIR} 
LFLAGS=-lgmp -lpbc -lpbc_sig -lpthread -lboost_system -lboost_thread -lboost_filesystem -ljsoncpp

all: ${TARGET} mgs

mgs :  m_groupsig_s.o easylog.o easylogging++.o SHA3.o \
	GroupSig.o KeyLoaderDumper.o GroupSig_BBS.o GroupSig_BBS_Impl.o
	${CC} -o mgs m_groupsig_s.o m_groupsig_c.o easylog.o easylogging++.o SHA3.o \
	GroupSig.o KeyLoaderDumper.o GroupSig_BBS.o GroupSig_BBS_Impl.o ${LFLAGS} 

${TARGET} : main.o m_groupsig_c.o easylog.o easylogging++.o SHA3.o \
	GroupSig.o KeyLoaderDumper.o GroupSig_BBS.o GroupSig_BBS_Impl.o
	${CC} -o ${TARGET} main.o m_groupsig_c.o easylog.o easylogging++.o SHA3.o \
	GroupSig.o KeyLoaderDumper.o GroupSig_BBS.o GroupSig_BBS_Impl.o ${LFLAGS}

main.o: main.cpp m_groupsig_c.h
	g++ ${CCFLAGS} -c main.cpp 

m_groupsig_s.o : m_groupsig_s.cpp m_groupsig_s.h
	g++ ${CCFLAGS} -c m_groupsig_s.cpp

m_groupsig_c.o: m_groupsig_c.cpp m_groupsig_c.h 
	g++ ${CCFLAGS} -c m_groupsig_c.cpp 

easylog.o: ./devcore/easylog.cpp ./devcore/easylog.h 
	g++ ${CCFLAGS} -c ./devcore/easylog.cpp

easylogging++.o: ./devcore/easylogging++.cpp ./devcore/easylogging++.h
	g++ ${CCFLAGS} -c ./devcore/easylogging++.cpp 

SHA3.o: ./devcore/SHA3.cpp ./devcore/SHA3.h
	g++ ${CCFLAGS} -c ./devcore/SHA3.cpp 

GroupSig.o : ./algorithm/GroupSig.cpp ./algorithm/GroupSig.h \
	devcore/easylog.h devcore/CommonFunc.h
	g++ ${CCFLAGS} -c ./algorithm/GroupSig.cpp

KeyLoaderDumper.o : ./algorithm/KeyLoaderDumper.cpp algorithm/KeyLoaderDumper.h 
	g++ ${CCFLAGS} -c ./algorithm/KeyLoaderDumper.cpp 

GroupSig_BBS.o : ./algorithm/bbs04/GroupSig_BBS.cpp \
	./algorithm/bbs04/GroupSig_BBS.h devcore/CommonFunc.h \
	algorithm/KeyLoaderDumper.h algorithm/bbs04/GroupSig_BBS_Impl.h \
	algorithm/bbs04/GroupSig_BBS.h
	g++ ${CCFLAGS} -c ./algorithm/bbs04/GroupSig_BBS.cpp

GroupSig_BBS_Impl.o : ./algorithm/bbs04/GroupSig_BBS_Impl.cpp \
	./algorithm/bbs04/GroupSig_BBS_Impl.h devcore/SHA3.h devcore/CommonFunc.h \
	algorithm/KeyLoaderDumper.h algorithm/bbs04/GroupSig_BBS.h 
	g++ ${CCFLAGS} -c ./algorithm/bbs04/GroupSig_BBS_Impl.cpp 

#GroupSig_BBS_Impl.o : ./algorithm/bbs04/GroupSig_BBS_Impl.cpp \
	#./algorithm/bbs04/GroupSig_BBS_Impl.h devcore/SHA3.h devcore/CommonFunc.h \
	#algorithm/KeyLoaderDumper.h algorithm/bbs04/GroupSig_BBS.h \
	#algorithm/bbs04/GroupSig_BBS_Impl.h
	#g++ ${CCFLAGS} -c ./algorithm/bbs04/GroupSig_BBS_Impl.cpp 


clean:
	rm -f ${OBJ}
	rm -f *.o
	rm -f *~
	rm -f ${TARGET}
	rm -f ${TARGET1}
	echo "Clean done."

test :
	echo $(SRC)
	echo $(OBJ)
	echo ${CC} ${notdir ${OBJ} } "-o" $@ ${LFLAGS}
