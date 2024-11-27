CPPFLAGS = -Wall -g -pedantic -Iinc -I/usr/include/xercesc
LDFLAGS = -Wall -L/usr/lib/x86_64-linux-gnu
LIBS = -lxerces-c

OBJDIR = obj
OBJ = $(OBJDIR)/xmlinterp.o $(OBJDIR)/main.o $(OBJDIR)/scene.o $(OBJDIR)/programinterpreter.o $(OBJDIR)/cuboid.o
TARGET = xmlinterp4config

$(TARGET): $(OBJ)
	g++ $(LDFLAGS) -o $@ $(OBJ) $(LIBS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/xmlinterp.o: src/xmlinterp.cpp inc/xmlinterp.hh inc/AccessControl.hh inc/Port.hh inc/Sender.hh
	g++ -c $(CPPFLAGS) -o $@ src/xmlinterp.cpp

$(OBJDIR)/main.o: src/main.cpp inc/xmlinterp.hh inc/Scene.hh inc/ProgramInterpreter.hh inc/AccessControl.hh inc/Port.hh inc/Sender.hh inc/LibInterface.hh
	g++ -c $(CPPFLAGS) -o $@ src/main.cpp

$(OBJDIR)/scene.o: src/Scene.cpp inc/Scene.hh inc/AbstractScene.hh inc/AbstractMobileObj.hh inc/AccessControl.hh inc/Port.hh inc/Sender.hh
	g++ -c $(CPPFLAGS) -o $@ src/Scene.cpp

$(OBJDIR)/programinterpreter.o: src/ProgramInterpreter.cpp inc/ProgramInterpreter.hh inc/AccessControl.hh inc/Port.hh inc/Sender.hh inc/LibInterface.hh
	g++ -c $(CPPFLAGS) -o $@ src/ProgramInterpreter.cpp

$(OBJDIR)/cuboid.o: src/Cuboid.cpp inc/Cuboid.hh inc/Port.hh inc/Sender.hh
	g++ -c $(CPPFLAGS) -o $@ src/Cuboid.cpp

clean:
	rm -fr $(OBJDIR) $(TARGET) core

cleanall: clean
	find . -name '*~' -print -exec rm {} \;
