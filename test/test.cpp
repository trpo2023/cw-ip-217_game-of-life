
#include <gtest/gtest.h>
// Включаем заголовочные файлы с определениями функций
#include "../src/helper.hpp"


extern bool isPlaying;
extern int delay;
extern bool isInputMode;
extern const int DELAY_INC = 50;
// Тест для функции wrapValue
TEST(HelperFunctionsTest, WrapValue) {
  // Проверяем, что функция wrapValue возвращает ожидаемые значения
  EXPECT_EQ(wrapValue(-1, 10), 9);
  EXPECT_EQ(wrapValue(5, 10), 5);
  EXPECT_EQ(wrapValue(10, 10), 0);
}

TEST(HandleMouseInputTest, CellToggledInCorrectPosition) {
    const int CELL_SIZE = 30;
    const int GRID_WIDTH = 30;
    const int GRID_HEIGHT = 20;
    int grid[GRID_WIDTH * GRID_HEIGHT] = {};
    bool isInputMode = true;
    bool isPlaying = true;
    sf::Event event;
    event.type = sf::Event::MouseButtonPressed;
    event.mouseButton.button = sf::Mouse::Left;
    event.mouseButton.x = 2 * CELL_SIZE;  // Положение мыши по оси X
    event.mouseButton.y = 1 * CELL_SIZE;  // Положение мыши по оси Y

    // Вызываем функцию handleMouseInput
    handleMouseInput(event, grid, isInputMode, isPlaying, GRID_WIDTH, GRID_HEIGHT);

    // Проверяем, что клетка появилась в нужном месте на экране
    int x = event.mouseButton.x / CELL_SIZE;
    int y = event.mouseButton.y / CELL_SIZE;
    ASSERT_TRUE(grid[x + y * GRID_WIDTH]);
}

// Тест для функции handleKeyboardInput - проверка правильного нажатия кнопки
// паузы "p"
TEST(HelperFunctionsTest, HandleKeyboardInput_PauseButtonPressed) {
  sf::Event event;
  event.key.code = sf::Keyboard::P;

  // Устанавливаем isPlaying в true перед тестом
  isPlaying = true;

  // Симулируем нажатие кнопки паузы
  handleKeyboardInput(event);

  // Проверяем, что isPlaying стало false после нажатия кнопки паузы
  EXPECT_FALSE(isPlaying);
}

int mainTest(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  // Проверяем наличие аргумента командной строки "nographic" для запуска только
  // тестов без открытия графического окна
  for (int i = 1; i < argc; i++) {
    if (std::string(argv[i]) == "nographic") {
      // Запускаем тесты без открытия графического окна
      return RUN_ALL_TESTS();
    }
  }

  return 0;
}
