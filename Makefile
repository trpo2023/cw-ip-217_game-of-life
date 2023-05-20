CXX = g++
CXXFLAGS = -Wall -Wextra -Ilib/googletest/include
SFML_DIR = lib/SFML-2.5.1
GTEST_DIR = lib/googletest

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = test
DLL_DIR = dll

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(TEST_SRCS))

TARGET = $(BIN_DIR)/z
TEST_TARGET = $(BIN_DIR)/test

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ -L$(DLL_DIR) -L$(SFML_DIR)/lib -lsfml-graphics -lsfml-window -lsfml-system

$(TEST_TARGET): $(TEST_OBJS) $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ -L$(DLL_DIR) -L$(SFML_DIR)/lib -lsfml-graphics -lsfml-window -lsfml-system -L$(GTEST_DIR)/lib -lgtest -lpthread

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(SFML_DIR)/include

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(SFML_DIR)/include -I$(GTEST_DIR)/include

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
