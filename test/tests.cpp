// Copyright 2025 UNN-CS
#include <gtest/gtest.h>

#include "circle.h"
#include "tasks.h"

#include <cmath>
#include <cstdint>
#include <utility>

const double PI = 3.14159265358979323846;
const double EPSILON = 1e-10;

TEST(CircleTest, ConstructorWithPositiveRadius) {
  Circle c(5.0);
  EXPECT_DOUBLE_EQ(c.getRadius(), 5.0);
  EXPECT_DOUBLE_EQ(c.getFerence(), 2 * PI * 5.0);
  EXPECT_DOUBLE_EQ(c.getArea(), PI * 25.0);
}

TEST(CircleTest, ConstructorWithZeroRadius) {
  Circle c(0.0);
  EXPECT_DOUBLE_EQ(c.getRadius(), 0.0);
  EXPECT_DOUBLE_EQ(c.getFerence(), 0.0);
  EXPECT_DOUBLE_EQ(c.getArea(), 0.0);
}

TEST(CircleTest, ConstructorWithNegativeRadiusThrows) {
  EXPECT_THROW(Circle c(-5.0), std::invalid_argument);
}

TEST(CircleTest, SetRadiusPositive) {
  Circle c(1.0);
  c.setRadius(10.0);
  EXPECT_DOUBLE_EQ(c.getRadius(), 10.0);
  EXPECT_DOUBLE_EQ(c.getFerence(), 2 * PI * 10.0);
  EXPECT_DOUBLE_EQ(c.getArea(), PI * 100.0);
}

TEST(CircleTest, SetRadiusZero) {
  Circle c(5.0);
  c.setRadius(0.0);
  EXPECT_DOUBLE_EQ(c.getRadius(), 0.0);
  EXPECT_DOUBLE_EQ(c.getFerence(), 0.0);
  EXPECT_DOUBLE_EQ(c.getArea(), 0.0);
}

TEST(CircleTest, SetRadiusNegativeThrows) {
  Circle c(1.0);
  EXPECT_THROW(c.setRadius(-5.0), std::invalid_argument);
  EXPECT_DOUBLE_EQ(c.getRadius(), 1.0);
}

TEST(CircleTest, SetFerencePositive) {
  Circle c(1.0);
  double f = 20.0;
  c.setFerence(f);
  EXPECT_DOUBLE_EQ(c.getFerence(), f);
  EXPECT_DOUBLE_EQ(c.getRadius(), f / (2 * PI));
  EXPECT_DOUBLE_EQ(c.getArea(), PI * pow(f / (2 * PI), 2));
}

TEST(CircleTest, SetFerenceZero) {
  Circle c(5.0);
  c.setFerence(0.0);
  EXPECT_DOUBLE_EQ(c.getFerence(), 0.0);
  EXPECT_DOUBLE_EQ(c.getRadius(), 0.0);
  EXPECT_DOUBLE_EQ(c.getArea(), 0.0);
}

TEST(CircleTest, SetFerenceNegativeThrows) {
  Circle c(1.0);
  EXPECT_THROW(c.setFerence(-10.0), std::invalid_argument);
  EXPECT_DOUBLE_EQ(c.getFerence(), 2 * PI * 1.0);
}

TEST(CircleTest, SetAreaPositive) {
  Circle c(1.0);
  double a = 50.0;
  c.setArea(a);
  EXPECT_DOUBLE_EQ(c.getArea(), a);
  EXPECT_NEAR(c.getRadius(), sqrt(a / PI), EPSILON);
  EXPECT_NEAR(c.getFerence(), 2 * PI * sqrt(a / PI), EPSILON);
}

TEST(CircleTest, SetAreaZero) {
  Circle c(5.0);
  c.setArea(0.0);
  EXPECT_DOUBLE_EQ(c.getArea(), 0.0);
  EXPECT_DOUBLE_EQ(c.getRadius(), 0.0);
  EXPECT_DOUBLE_EQ(c.getFerence(), 0.0);
}

TEST(CircleTest, SetAreaNegativeThrows) {
  Circle c(1.0);
  EXPECT_THROW(c.setArea(-30.0), std::invalid_argument);
  EXPECT_DOUBLE_EQ(c.getArea(), PI * 1.0);
}

TEST(CircleTest, ConsistencyAfterMultipleRadiusChanges) {
  Circle c(2.0);
  double originalArea = c.getArea();
  double originalFerence = c.getFerence();

  c.setRadius(5.0);
  c.setRadius(2.0);

  EXPECT_DOUBLE_EQ(c.getArea(), originalArea);
  EXPECT_DOUBLE_EQ(c.getFerence(), originalFerence);
}

TEST(CircleTest, ConsistencyAfterMultipleFerenceChanges) {
  Circle c(3.0);
  double originalRadius = c.getRadius();

  c.setFerence(30.0);
  c.setFerence(2 * PI * 3.0);

  EXPECT_NEAR(c.getRadius(), originalRadius, EPSILON);
}

TEST(CircleTest, LargeRadius) {
  double largeR = 1e6;
  Circle c(largeR);
  EXPECT_DOUBLE_EQ(c.getRadius(), largeR);
  EXPECT_DOUBLE_EQ(c.getFerence(), 2 * PI * largeR);
  EXPECT_DOUBLE_EQ(c.getArea(), PI * largeR * largeR);
}

TEST(CircleTest, VerySmallRadius) {
  double smallR = 1e-10;
  Circle c(smallR);
  EXPECT_DOUBLE_EQ(c.getRadius(), smallR);
  EXPECT_DOUBLE_EQ(c.getFerence(), 2 * PI * smallR);
  EXPECT_DOUBLE_EQ(c.getArea(), PI * smallR * smallR);
}

TEST(EarthRopeTaskTest, GapIsPositive) {
  double gap = calculateEarthRopeGap();
  EXPECT_GT(gap, 0.0);
}

TEST(EarthRopeTaskTest, GapIsReasonable) {
  double gap = calculateEarthRopeGap();
  EXPECT_NEAR(gap, 1.0 / (2 * PI), 1e-6);
}

TEST(EarthRopeTaskTest, GapDoesNotDependOnEarthRadius) {
  double customRadius = 1000.0;
  Circle earth(customRadius);
  double earthFerence = earth.getFerence();
  double newFerence = earthFerence + 1.0;
  Circle newCircle(0.0);
  newCircle.setFerence(newFerence);
  double customGap = newCircle.getRadius() - customRadius;

  double standardGap = calculateEarthRopeGap();
  EXPECT_NEAR(customGap, standardGap, EPSILON);
}

TEST(PoolTaskTest, PoolCostsPositive) {
  auto costs = calculatePoolCosts(3.0, 1.0, 1000.0, 2000.0);
  EXPECT_GT(costs.first, 0.0);
  EXPECT_GT(costs.second, 0.0);
}

TEST(PoolTaskTest, ConcreteCostCalculation) {
  double poolRadius = 3.0;
  double pathWidth = 1.0;
  double concretePrice = 1000.0;

  Circle pool(poolRadius);
  Circle poolWithPath(poolRadius + pathWidth);
  double expectedPathArea = poolWithPath.getArea() - pool.getArea();
  double expectedConcreteCost = expectedPathArea * concretePrice;

  auto costs = calculatePoolCosts(poolRadius, pathWidth, concretePrice, 2000.0);
  EXPECT_NEAR(costs.first, expectedConcreteCost, EPSILON);
}

TEST(PoolTaskTest, FenceCostCalculation) {
  double poolRadius = 3.0;
  double pathWidth = 1.0;
  double fencePrice = 2000.0;

  Circle poolWithPath(poolRadius + pathWidth);
  double expectedFenceLength = poolWithPath.getFerence();
  double expectedFenceCost = expectedFenceLength * fencePrice;

  auto costs = calculatePoolCosts(poolRadius, pathWidth, 1000.0, fencePrice);
  EXPECT_NEAR(costs.second, expectedFenceCost, EPSILON);
}

TEST(PoolTaskTest, ZeroPathWidth) {
  auto costs = calculatePoolCosts(3.0, 0.0, 1000.0, 2000.0);
  EXPECT_NEAR(costs.first, 0.0, EPSILON);

  Circle pool(3.0);
  EXPECT_NEAR(costs.second, pool.getFerence() * 2000.0, EPSILON);
}

TEST(PoolTaskTest, DifferentPrices) {
  auto costs1 = calculatePoolCosts(3.0, 1.0, 1000.0, 2000.0);
  auto costs2 = calculatePoolCosts(3.0, 1.0, 2000.0, 3000.0);

  EXPECT_GT(costs2.first, costs1.first);
  EXPECT_GT(costs2.second, costs1.second);
}

TEST(PoolTaskTest, ZeroPrices) {
  auto costs = calculatePoolCosts(3.0, 1.0, 0.0, 0.0);
  EXPECT_DOUBLE_EQ(costs.first, 0.0);
  EXPECT_DOUBLE_EQ(costs.second, 0.0);
}

TEST(CombinedTest, CircleAndTasksWork) {
  Circle testCircle(10.0);
  double gap = calculateEarthRopeGap();
  auto poolCosts = calculatePoolCosts(5.0, 2.0, 1500.0, 2500.0);

  EXPECT_NO_THROW(testCircle.setRadius(7.0));
  EXPECT_NO_THROW(testCircle.setFerence(50.0));
  EXPECT_NO_THROW(testCircle.setArea(200.0));

  EXPECT_GT(gap, 0.0);
  EXPECT_GT(poolCosts.first, 0.0);
  EXPECT_GT(poolCosts.second, 0.0);
}
