CXX = g++
CXXFLAGS = -Wall -Wextra
SFML_DIR = lib/SFML-2.5.1

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
DLL_DIR = dll

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

TARGET = $(BIN_DIR)/z

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ -L$(DLL_DIR) -L$(SFML_DIR)/lib -lsfml-graphics -lsfml-window -lsfml-system

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(SFML_DIR)/include

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
