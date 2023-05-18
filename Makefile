CC = g++
CFLAGS = -Wall -Wextra
SFML_INCLUDE = -I./src/SFML-2.5.1/include
SFML_LIBS = -L./src/SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
DLL_DIR = dll

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
EXECUTABLE = $(BIN_DIR)/z

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -L$(DLL_DIR) $(SFML_LIBS)
	./bin/z

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(SFML_INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXECUTABLE)

.PHONY: all clean
