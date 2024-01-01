/**
 * @file BarycentricInterpolator.h
 * @author Ismar Muslic, 19304 (imuslic1@etf.unsa.ba)
 * @brief 
 * @version 1.0
 * @date 18-12-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef BARYCENTRIC_INTERPOLATOR
#define BARYCENTRIC_INTERPOLATOR

#include <iostream>
#include <cmath>
#include <vector>
#include <stdexcept>
#include "AbstractInterpolator.h"

/**
 * @brief Performs Barycentric Interpolation in a given point, for the data set provided in a vector.
 * 
 */
class BarycentricInterpolator : public AbstractInterpolator {
private:
    std::vector<double> tezinskiKoeficijenti;
public:
/**
 * @brief Construct a new Barycentric Interpolator object
 * 
 * @param data Data set of points to be indexed
 * @param order Order degree of Barycentric Interpolation
 */
    BarycentricInterpolator(const std::vector<std::pair<double, double>> &data, int order) : AbstractInterpolator(data) {
        if(order < 0 || order > data.size())
            throw std::domain_error("Invalid order");

        int n = this->data.size();
        
        tezinskiKoeficijenti.resize(n, 0.0);
        
        for(int i=0; i<n; i++) {
            tezinskiKoeficijenti[i] = 0.0;
            double p = 1;
            for(int k = std::max(0, i-order); k <= std::min(i, n-order); k++) {
                p=1;
                for(int j = k; j<k+order; j++) {
                    if(j!=i)
                        p /= (data.at(i).first-data.at(j).first);
                }
                if(k%2 == 1)
                    p = -p;
                
            }
            tezinskiKoeficijenti.at(i) += p;
        }
    }
    /**
     * @brief Calculates the value of y for given parameter x, using Barycentric Interpolation.
     * 
     * @param x x for y to be calculated for
     * @return double value of interpolated function for given x
     */
    double operator()(double x) const override {
        double p = 0, q = 0, n=this->data.size();
        long double epsilon = 1e-15;
        for(int i=0; i<n; i++) {
            if(std::fabs(x - data.at(i).first) < epsilon)
                return data.at(i).second;
            double u = tezinskiKoeficijenti.at(i) / (x - data.at(i).first);
            p += u*data.at(i).second;
            q += u;
        }
        return p/q;
    }
    /**
     * @brief Get the Weights vector. 
     * 
     * @return std::vector<double> Vector of weight factors for Barycentric Interpolation
     */
    std::vector<double> GetWeights() const {
        return tezinskiKoeficijenti;
    }
};

#endif