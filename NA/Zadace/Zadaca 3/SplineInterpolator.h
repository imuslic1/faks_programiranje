/**
 * @file SplineInterpolator.h
 * @author Ismar Muslic, 19304 (imuslic1@etf.unsa.ba)
 * @brief 
 * @version 1.0
 * @date 18-12-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SPLINE_INTERPOLATOR
#define SPLINE_INTERPOLATOR

#include <iostream>
#include <vector>
#include <stdexcept>
#include "AbstractInterpolator.h"
/**
 * @brief Performs interpolation using a cubic spline, in a given point, for the data set provided in a vector.
 * 
 */
class SplineInterpolator : public AbstractInterpolator {
private: 
    std::vector<double> r, s, q;
public:
    /**
     * @brief Construct a new Spline Interpolator object, calculating the coefficients of the cubic spline.
     * 
     * @param data Points to be interpolated
     */
    explicit SplineInterpolator(
        const std::vector<std::pair<double, double>> &data) 
        : AbstractInterpolator(data) {
    r.resize(this->data.size());
    r[0] = 0;
    r[this->data.size() -1] = 0;

    std::vector<double> alpha (r.size() - 2);

    for (int i=1; i<r.size()-1; i++) {
            alpha[i-1] = 2 * (this->data[i+1].first - this->data[i-1].first);
            r[i] = 3 * ((this->data[i+1].second - this->data[i].second) / (this->data[i+1].first - this->data[i].first)
                    - (this->data[i].second - this->data[i-1].second) 
                    / (this->data[i].first - this->data[i-1].first));
        }

        for (int i=1; i<r.size()-2; i++) {
            double mi = (this->data[i+1].first - this->data[i].first) / alpha[i-1];
            alpha[i] = alpha[i] - mi * (this->data[i+1].first - this->data[i].first);
            r[i+1] = r[i+1] - mi*r[i];
        }

        r[r.size()-2] = r[r.size()-2] / alpha[r.size()-3];

        for (int i=r.size()-3; i>=1; i--)
            r[i] = (r[i] - (this->data[i+1].first - this->data[i].first) * r[i+1]) / alpha[i-1];

        for (int i=0; i<r.size()-1; i++) {
            double delta = this->data[i+1].first - this->data[i].first;
            s.push_back((r[i+1] - r[i]) / (3*delta));
            q.push_back((this->data[i+1].second - this->data[i].second) / delta-delta*(r[i+1] + 2*r[i]) / 3);
        }
    }
    /**
     * @brief Calculates the interpolated value of y, for the given x.
     * 
     * @param x Value of x for y to be calculated from.
     * @return double Interpolated value of y.
     */
    double operator()(double x) const override {
        int index = Locate(x);
        if(index==0) ++index;
        else if(index==data.size()) --index;
        long double t = x - data.at(index-1).first;
        double Px = data.at(index-1).second + t*(q.at(index-1) + t*(r.at(index-1)+ t*s.at(index-1)));
        return Px;
    }
};

#endif