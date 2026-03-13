// Copyright 2025 UNN-CS Team
#ifndef INCLUDE_CIRCLE_H_
#define INCLUDE_CIRCLE_H_

class Circle {
 private:
  double radius;
  double ference;
  double area;

 public:
  explicit Circle(double r);
  void setRadius(double r);
  void setFerence(double f);
  void setArea(double a);
  double getRadius() const;
  double getFerence() const;
  double getArea() const;

 private:
  void updateFromRadius();
  void updateFromFerence();
  void updateFromArea();
};

#endif  // INCLUDE_CIRCLE_H_