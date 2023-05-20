CXX = g++
CXXFLAGS = -Wall -Wextra
LDFLAGS = -Llib/SFML-2.5.1/lib
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
INCLUDES = -Ilib/SFML-2.5.1/include

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

TARGET = $(BIN_DIR)/z

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@ $(SFML_LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)
