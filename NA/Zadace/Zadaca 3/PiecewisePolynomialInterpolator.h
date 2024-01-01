/**
 * @file PiecewisePolynomialInterpolator.h
 * @author Ismar Muslic, 19304 (imuslic1@etf.unsa.ba)
 * @brief 
 * @version 1.0
 * @date 18-12-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef PIECEWISE_INTERPOLATOR
#define PIECEWISE_INTERPOLATOR

#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include "AbstractInterpolator.h"
/**
 * @brief Performs Piecewise Polynomial Interpolation in a given point, for the data set provided in a vector.
 * 
 */
class PiecewisePolynomialInterpolator : public AbstractInterpolator {
private: 
    int order;
public:
/**
 * @brief Construct a new Piecewise Polynomial Interpolator object
 * 
 * @param data Points to be interpolated.
 * @param order Degree of piece-wise polynomials to be used for intepolation between two xi and xi+1.
 */
    explicit PiecewisePolynomialInterpolator(const std::vector<std::pair<double, double>> &data, int order) 
            : AbstractInterpolator(data) {
        if(order<1||order>=data.size())
            throw std::domain_error("Invalid order");
        this->order = order;
    }
    /**
     * @brief Caluclates the interpolated value of y for the given x.
     * 
     * @param x Value for y to be calculated for.
     * @return double Interpolated value of y.
     */
    double operator() (double x) const override {
        int subinterval = Locate(x);
        int lower = 0, upper = 0;

        if(order%2 == 0) {
            lower = subinterval-order/2;
            upper = subinterval+order/2;
        } else {
            lower = subinterval - (order-1)/2;
            upper = subinterval + (order+1)/2;
        }

        if(lower <= 0) {
            lower = 1;
            upper = order+1;
        }
        if(upper>data.size()) {
            upper = data.size();
            lower = upper - order;
        }

        long double sum = 0;

        for(int i= lower-1; i<upper; i++) {
            long double proizvod = data.at(i).second;
            for(int j = lower-1; j<upper; j++) 
                if(j!=i)
                    proizvod*=(x-data.at(j).first) / (data.at(i).first - data.at(j).first);
            sum += proizvod;
        }
        return (double) sum;
    }
};

#endif