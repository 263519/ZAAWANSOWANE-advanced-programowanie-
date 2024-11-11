

TRGDIR=/tmp/${USER}/serwer-graficzny--klient
FILE=klient
OBJ=${TRGDIR}/obj
SRC=src
APP=${TRGDIR}/klient
COMPFLAGS= -iquote inc -W -Wall -std=c++17 -pedantic 
LINKFLAGS= -W -Wall
LIBS=-lpthread

__start__: __lines__ ${OBJ} ${APP}
	cd ${TRGDIR}; rm -f core.* core; ulimit -c unlimited; ${APP}

__lines__:
	@echo
	@echo
	@echo
	@echo
	@echo
	@echo
	@echo
	@echo

${OBJ}:
	mkdir -p "${OBJ}"

${APP}: ${OBJ}/${FILE}.o
	g++ ${LINKFLAGS} -o ${APP} ${OBJ}/${FILE}.o ${LIBS}

${OBJ}/${FILE}.o: ${SRC}/${FILE}.cpp 
	g++  ${COMPFLAGS} -c -Wall -o ${OBJ}/${FILE}.o ${SRC}/${FILE}.cpp

clean:
	rm -f "${OBJ}"/* "${APP}" core.* core

clean-copies:
	find . \( -name \*~ -o -name \*\.flc -o -name \*.BAK \) -type f -print -exec rm {} \;

cleanall: clean
	rm -r obj


help:
	#
	#   make              - tworzenie i uruchomienie aplikacji
	#   make clean        - usuniecie produktow kompilacji i konsolidacji
	#   make clean-copies - usuniecie kopii edytowanych plikow
	#
