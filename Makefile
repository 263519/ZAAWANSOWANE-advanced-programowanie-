__start__: obj xmlinterp4config
	./xmlinterp4config

obj:
	mkdir -p obj

CPPFLAGS=-Wall -g -pedantic -Iinc
LDFLAGS=-Wall

xmlinterp4config: obj/xmlinterp.o obj/main.o obj/scene.o obj/programinterpreter.o
	g++ ${LDFLAGS} -o xmlinterp4config obj/xmlinterp.o \
                                     obj/main.o obj/scene.o obj/programinterpreter.o -lxerces-c

obj/xmlinterp.o: src/xmlinterp.cpp inc/xmlinterp.hh inc/AccessControl.hh inc/Port.hh inc/Sender.hh
	g++ -c ${CPPFLAGS} -o obj/xmlinterp.o src/xmlinterp.cpp

obj/main.o: src/main.cpp inc/xmlinterp.hh inc/Scene.hh inc/ProgramInterpreter.hh inc/AccessControl.hh inc/Port.hh inc/Sender.hh
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp

obj/scene.o: src/Scene.cpp inc/Scene.hh inc/AbstractScene.hh inc/AbstractMobileObj.hh inc/AccessControl.hh inc/Port.hh inc/Sender.hh
	g++ -c ${CPPFLAGS} -o obj/scene.o src/Scene.cpp

obj/programinterpreter.o: src/ProgramInterpreter.cpp inc/ProgramInterpreter.hh inc/AccessControl.hh inc/Port.hh inc/Sender.hh
	g++ -c ${CPPFLAGS} -o obj/programinterpreter.o src/ProgramInterpreter.cpp

clean:
	rm -fr obj xmlinterp4config core

cleanall: clean
	find . -name \*~ -print -exec rm {} \;
