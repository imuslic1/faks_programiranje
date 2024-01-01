/**
 * @file TrigonometricInterpolator.h
 * @author Ismar Muslic, 19304 (imuslic1@etf.unsa.ba)
 * @brief 
 * @version 1.0
 * @date 18-12-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef TRIGONOMETRIC_INTERPOLATOR
#define TRIGONOMETRIC_INTERPOLATOR

#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include "AbstractInterpolator.h"
/**
 * @brief Performs Trigonometric Interpolation in a given point, for the data set provided in a vector.
 * 
 */
class TrigonometricInterpolator : public AbstractInterpolator {
private:
    double omega, T;
public:
    /**
     * @brief Construct a new Trigonometric Interpolator object
     * 
     * @param data Points to be interpolated.
     */
    inline explicit TrigonometricInterpolator(const std::vector<std::pair<double, double>> &data) : AbstractInterpolator(data) {
        const double epsilon = 1e-15;
        if(std::fabs(data.at(0).second - data.at(data.size()-1).second) < epsilon)
            throw std::domain_error("Function is not periodic");
    }
    /**
     * @brief Calculates the interpolated value of y for the given x, using Trigonometric interpolation.
     * 
     * @param x Value of x for y to be calculated from.
     * @return double Interpolated value of y.
     */
    double operator()(double x) const override {
        double sum = 0.0;

        for (size_t k = 0; k < data.size(); ++k) {
            double ak = data.at(k).second;

            double factor = 1.0;
            for (size_t j = 0; j < data.size(); ++j) {
                if (j != k) {
                    double numerator = sin((x - data.at(j).first) * omega / 2);
                    double denominator = sin((data.at(k).first - data.at(j).first) * omega / 2);
                    factor *= numerator / denominator;
                }
            }

            sum += ak * factor;
        }

        return sum;
    }
};

#endif