CC := g++
CFLAGS := -std=c++17 -Wall -Wextra -Ilib/thirdparty -Ilib/SFML-2.5.1/include -Ilib/googletest/include -Isrc/app_lib
LDFLAGS := -Llib/SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -lgtest -lpthread

SRC_DIR := src/app
CTEST_DIR := test/ctest
GTEST_DIR := test/google_test

OBJ_DIR := obj
BIN_DIR := bin

GAME_OBJ_DIR := $(OBJ_DIR)/game
CTEST_OBJ_DIR := $(OBJ_DIR)/ctest
GTEST_OBJ_DIR := $(OBJ_DIR)/google_test

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
GAME_OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(GAME_OBJ_DIR)/%.o,$(SRC_FILES))

CTEST_SRC_FILES := $(wildcard $(CTEST_DIR)/*.c)
CTEST_OBJ_FILES := $(patsubst $(CTEST_DIR)/%.c,$(CTEST_OBJ_DIR)/%.o,$(CTEST_SRC_FILES))

GTEST_SRC_FILES := $(wildcard $(GTEST_DIR)/*.cpp)
GTEST_OBJ_FILES := $(patsubst $(GTEST_DIR)/%.cpp,$(GTEST_OBJ_DIR)/%.o,$(GTEST_SRC_FILES))

$(GAME_OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(GAME_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(CTEST_OBJ_DIR)/%.o: $(CTEST_DIR)/%.c
	@mkdir -p $(CTEST_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(GTEST_OBJ_DIR)/%.o: $(GTEST_DIR)/*.cpp
	@mkdir -p $(GTEST_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/game: $(GAME_OBJ_FILES) $(GTEST_OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BIN_DIR)/ctest: $(CTEST_OBJ_FILES) $(GAME_OBJ_DIR)/lib.o
	@mkdir -p $(BIN_DIR)
	$(CC) $^ -o $@ $(LDFLAGS)

$(GAME_OBJ_DIR)/lib.o: $(SRC_DIR)/lib.cpp
	@mkdir -p $(GAME_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


all: app

app: $(BIN_DIR)/game

ctest: $(BIN_DIR)/ctest

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
