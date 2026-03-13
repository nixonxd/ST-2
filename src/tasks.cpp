// Copyright 2022 UNN-CS
#include "tasks.h"

#include <cmath>
#include <utility>

#include "circle.h"

const double EARTH_RADIUS_KM = 6378.1;
const double METER_TO_KM = 0.001;
const double KM_TO_METER = 1000.0;

double calculateEarthRopeGap() {
  double earthRadiusM = EARTH_RADIUS_KM * KM_TO_METER;

  Circle earth(earthRadiusM);

  double earthFerence = earth.getFerence();

  double newFerence = earthFerence + 1.0;

  Circle newCircle(0.0);
  newCircle.setFerence(newFerence);

  double gap = newCircle.getRadius() - earthRadiusM;

  return gap;
}

std::pair<double, double> calculatePoolCosts(double poolRadius,
                                             double pathWidth,
                                             double concretePrice,
                                             double fencePrice) {
  Circle pool(poolRadius);

  Circle poolWithPath(poolRadius + pathWidth);

  double pathArea = poolWithPath.getArea() - pool.getArea();

  double concreteCost = pathArea * concretePrice;

  double fenceLength = poolWithPath.getFerence();

  double fenceCost = fenceLength * fencePrice;

  return std::make_pair(concreteCost, fenceCost);
}
