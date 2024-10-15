__start__: obj __lines_for_space__ ../libs/libInterp4Move.so ../libs/libInterp4Rotate.so
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

clean:
	rm -f obj/*

cleanall: clean
	find . -name \*~ -print -exec rm {} \;
