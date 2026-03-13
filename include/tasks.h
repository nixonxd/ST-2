#ifndef INCLUDE_TASKS_H_
#define INCLUDE_TASKS_H_

#include <utility>

double calculateEarthRopeGap();

std::pair<double, double> calculatePoolCosts(double poolRadius,
                                             double pathWidth,
                                             double concretePrice,
                                             double fencePrice);

#endif // TASKS_H
