CC := g++
CFLAGS := -std=c++17 -Wall -Wextra
LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system -lgtest -lpthread

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

TEST_SRC_DIR := test
TEST_OBJ_DIR := obj/test
TEST_BIN_DIR := bin/test

TEST_SRC_FILES := $(wildcard $(TEST_SRC_DIR)/*.cpp)
TEST_OBJ_FILES := $(patsubst $(TEST_SRC_DIR)/%.cpp,$(TEST_OBJ_DIR)/%.o,$(TEST_SRC_FILES))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/test/%.o: $(TEST_SRC_DIR)/%.cpp
	@mkdir -p $(TEST_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/game: $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CC) $^ -o $@ $(LDFLAGS)

$(TEST_BIN_DIR)/test: $(OBJ_FILES) $(TEST_OBJ_FILES)
	@mkdir -p $(TEST_BIN_DIR)
	$(CC) $^ -o $@ $(LDFLAGS)

.PHONY: all clean test

all: $(BIN_DIR)/game

test: $(TEST_BIN_DIR)/test
	@./$(TEST_BIN_DIR)/test

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(TEST_OBJ_DIR) $(TEST_BIN_DIR)
