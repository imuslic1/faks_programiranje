/**
 * @file LinearInterpolator.h
 * @author Ismar Muslic, 19304 (imuslic1@etf.unsa.ba)
 * @brief Class used to perform Linear Interpolation on a dataset
 * @version 1.0
 * @date 16-12-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef LINEAR_INTERPOLATOR
#define LINEAR_INTERPOLATOR

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <vector>
#include "AbstractInterpolator.h"
/**
 * @brief Performs Linear Interpolation in a given point, for the data set provided in a vector.
 * 
 */
class LinearInterpolator : public AbstractInterpolator {
public:
    /**
     * @brief Construct a new Linear Interpolator object
     * 
     * @param data Points to be interpolated.
     */
    LinearInterpolator(const std::vector<std::pair<double,double>> &data)
        : AbstractInterpolator(data){}

    /**
     * @brief Calculates the interpolated value of the function in the point x.
     * 
     * @param x Value for y to be calculated for
     * @return double Interpolated value of y
     */
    double operator()(double x) const override {
        int interval = Locate(x);

        std::pair<long double, long double> point_i;
        std::pair<long double, long double> point_iplus1;

        if(interval == 0) {
            point_i = data.at(0);
            point_iplus1 = data.at(1);
        }

        else if(interval == data.size()) {
            point_i = data.at(data.size()-2);
            point_iplus1 = data.at(data.size()-1);
        }
        else {
            point_i = data.at(interval-1);
            point_iplus1 = data.at(interval);
        }

        long double x1 = point_i.first;
        long double x2 = point_iplus1.first;
        long double y1 = point_i.second;
        long double y2 = point_iplus1.second;

        double result = (x2-x) / (x2-x1) * y1 + (x-x1) / (x2-x1) * y2;

        return result;
    }
};

#endif