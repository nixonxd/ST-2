// Copyright 2022 UNN-CS
#include <cmath>
#include <stdexcept>
#include "circle.h"

static const double PI = 3.14159265358979323846;

Circle::Circle(double r) {
  if (r < 0) {
    throw std::invalid_argument("Radius cannot be negative");
  }
  setRadius(r);
}

void Circle::setRadius(double r) {
  if (r < 0) {
    throw std::invalid_argument("Radius cannot be negative");
  }
  radius = r;
  updateFromRadius();
}

void Circle::setFerence(double f) {
  if (f < 0) {
    throw std::invalid_argument("Ference cannot be negative");
  }
  ference = f;
  updateFromFerence();
}

void Circle::setArea(double a) {
  if (a < 0) {
    throw std::invalid_argument("Area cannot be negative");
  }
  area = a;
  updateFromArea();
}

double Circle::getRadius() const { return radius; }

double Circle::getFerence() const { return ference; }

double Circle::getArea() const { return area; }

void Circle::updateFromRadius() {
  ference = 2 * PI * radius;
  area = PI * radius * radius;
}

void Circle::updateFromFerence() {
  radius = ference / (2 * PI);
  area = PI * radius * radius;
}

void Circle::updateFromArea() {
  radius = sqrt(area / PI);
  ference = 2 * PI * radius;
}
