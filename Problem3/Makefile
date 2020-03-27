CC=g++

OPENGLLIB= -framework OpenGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include -I./

BIN1=Bin/Ring
BIN2=Bin/Disc
BIN3=Bin/Crescent
BIN4=Bin/Chess

SRCS1= Ring.cpp Utility/Shader.cpp Utility/Textures.cpp
SRCS2= Disc.cpp Utility/Shader.cpp Utility/Textures.cpp
SRCS3= Crescent.cpp Utility/Shader.cpp Utility/Textures.cpp
SRCS4= Chess.cpp Utility/Shader.cpp Utility/Textures.cpp

INCLUDES=Utility/Shader.hpp Utility/Textures.hpp

all: $(BIN1) $(BIN2) $(BIN3) $(BIN4)
$(BIN1): $(SRCS1) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS1) -o $(BIN1) $(LDFLAGS) $(LIBS)

$(BIN2): $(SRCS2) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS2) -o $(BIN2) $(LDFLAGS) $(LIBS)

$(BIN3): $(SRCS3) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS3) -o $(BIN3) $(LDFLAGS) $(LIBS)

$(BIN4): $(SRCS4) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS4) -o $(BIN4) $(LDFLAGS) $(LIBS)




