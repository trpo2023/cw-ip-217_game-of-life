CC := g++
CFLAGS := -std=c++17 -Wall -Wextra
LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system -lgtest -lpthread

SRC_DIR := src/app
TEST_DIR := test

OBJ_DIR := obj
BIN_DIR := bin

GAME_OBJ_DIR := $(OBJ_DIR)/game
TEST_OBJ_DIR := $(OBJ_DIR)/test

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
GAME_OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(GAME_OBJ_DIR)/%.o,$(SRC_FILES))

TEST_SRC_FILES := $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJ_FILES := $(patsubst $(TEST_DIR)/%.cpp,$(TEST_OBJ_DIR)/%.o,$(TEST_SRC_FILES))

$(GAME_OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(GAME_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(TEST_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/game: $(GAME_OBJ_FILES) $(TEST_OBJ_DIR)/test.o
	@mkdir -p $(BIN_DIR)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BIN_DIR)/test: $(TEST_OBJ_FILES) $(GAME_OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CC) $^ -o $@ $(LDFLAGS)

.PHONY: all clean test app

all: app

app: $(BIN_DIR)/game

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)