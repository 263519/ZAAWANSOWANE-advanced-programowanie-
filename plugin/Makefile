__start__: obj __lines_for_space__ ../libs/libInterp4Move.so ../libs/libInterp4Rotate.so ../libs/libInterp4Set.so ../libs/libInterp4Pause.so
	@echo "  Tworzenie wtyczek zakonczone."
	@echo

obj:
	mkdir -p obj

CPPFLAGS=-Wall -fPIC -pedantic -std=c++17 -Iinc -I../inc
LDFLAGS=-Wall -shared

__lines_for_space__:
	@echo
	@echo
	@echo
	@echo
	@echo

../libs/libInterp4Move.so: obj/Interp4Move.o
	g++ ${LDFLAGS} -o ../libs/libInterp4Move.so obj/Interp4Move.o
	@echo "  Wtyczka dla polecenia 'Move' zostala utworzona."
	@echo

../libs/libInterp4Rotate.so: obj/Interp4Rotate.o
	g++ ${LDFLAGS} -o ../libs/libInterp4Rotate.so obj/Interp4Rotate.o
	@echo "  Wtyczka dla polecenia 'Rotate' zostala utworzona."
	@echo


../libs/libInterp4Set.so: obj/Interp4Set.o
	g++ ${LDFLAGS} -o ../libs/libInterp4Set.so obj/Interp4Set.o
	@echo "  Wtyczka dla polecenia 'Set' zostala utworzona."
	@echo

../libs/libInterp4Pause.so: obj/Interp4Pause.o
	g++ ${LDFLAGS} -o ../libs/libInterp4Pause.so obj/Interp4Pause.o
	@echo "  Wtyczka dla polecenia 'Pause' zostala utworzona."
	@echo

obj/Interp4Move.o: src/Interp4Move.cpp inc/Interp4Move.hh \
                   ../inc/AbstractInterp4Command.hh \
                   ../inc/AbstractScene.hh \
                   ../inc/AbstractComChannel.hh
	g++ -c ${CPPFLAGS} -o obj/Interp4Move.o src/Interp4Move.cpp

obj/Interp4Rotate.o: src/Interp4Rotate.cpp inc/Interp4Rotate.hh \
                     ../inc/AbstractInterp4Command.hh \
                     ../inc/AbstractScene.hh \
                     ../inc/AbstractComChannel.hh
	g++ -c ${CPPFLAGS} -o obj/Interp4Rotate.o src/Interp4Rotate.cpp

obj/Interp4Set.o: src/Interp4Set.cpp inc/Interp4Set.hh \
                  ../inc/AbstractInterp4Command.hh \
                  ../inc/AbstractScene.hh \
                  ../inc/AbstractComChannel.hh
	g++ -c ${CPPFLAGS} -o obj/Interp4Set.o src/Interp4Set.cpp

obj/Interp4Pause.o: src/Interp4Pause.cpp inc/Interp4Pause.hh \
                    ../inc/AbstractInterp4Command.hh \
                    ../inc/AbstractScene.hh \
                    ../inc/AbstractComChannel.hh
	g++ -c ${CPPFLAGS} -o obj/Interp4Pause.o src/Interp4Pause.cpp


clean:
	rm -f obj/*

cleanall: clean
	find . -name \*~ -print -exec rm {} \;
