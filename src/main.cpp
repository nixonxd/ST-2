// Copyright 2022 UNN-CS
#include <iostream>
#include "circle.h"
#include "tasks.h"

int main() {
  std::cout << "=== Демонстрация работы класса Circle ===\n";

  Circle circle1(5.0);
  std::cout << "Радиус: " << circle1.getRadius() << std::endl;
  std::cout << "Длина окружности: " << circle1.getFerence() << std::endl;
  std::cout << "Площадь: " << circle1.getArea() << std::endl;

  std::cout << "\n=== Изменение длины окружности ===\n";
  circle1.setFerence(40.0);
  std::cout << "Новый радиус: " << circle1.getRadius() << std::endl;
  std::cout << "Новая площадь: " << circle1.getArea() << std::endl;

  std::cout << "\n=== Изменение площади ===\n";
  circle1.setArea(200.0);
  std::cout << "Новый радиус: " << circle1.getRadius() << std::endl;
  std::cout << "Новая длина окружности: " << circle1.getFerence() << std::endl;

  std::cout << "\n=== Задача 'Земля и веревка' ===\n";
  double gap = calculateEarthRopeGap();
  std::cout << "Зазор после добавления 1 м веревки: " << gap << " м\n";
  std::cout << "Это примерно " << gap * 100 << " см\n";

  std::cout << "\n=== Задача 'Бассейн' ===\n";
  auto costs = calculatePoolCosts(3.0, 1.0, 1000.0, 2000.0);
  std::cout << "Стоимость бетонной дорожки: " << costs.first << " руб.\n";
  std::cout << "Стоимость ограды: " << costs.second << " руб.\n";
  std::cout << "Общая стоимость: " << costs.first + costs.second << " руб.\n";

  return 0;
}
