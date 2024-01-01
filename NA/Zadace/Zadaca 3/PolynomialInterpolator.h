/**
 * @file PolynomialInterpolator.h
 * @author Ismar Muslic, 19304 (imuslic1@etf.unsa.ba)
 * @brief 
 * @version 1.0
 * @date 18-12-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef POLYNOMIAL_INTERPOLATOR
#define POLYNOMIAL_INTERPOLATOR

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include "AbstractInterpolator.h"
/**
 * @brief Performs Polynomial Interpolation in a given point, for the data set provided in a vector.
 * 
 */
class PolynomialInterpolator : public AbstractInterpolator {
private:
    std::vector<double> newtonsCoefficients;
    std::vector<double> dodatneVrijednosti;
public:
    /**
     * @brief Construct a new Polynomial Interpolator object
     * 
     * @param data Points to be interpolated
     */
    explicit PolynomialInterpolator(const std::vector<std::pair<double, double>> &data) : AbstractInterpolator(data) {
        for (const auto &tacka : data) {
            newtonsCoefficients.push_back(tacka.second);
        }

        int n = this->data.size();

        for (int j=1; j<=n-1; j++) {
            for (int i=n; i>=j+1; i--) {
                if(i==n) 
                    dodatneVrijednosti.push_back(newtonsCoefficients.at(i-1));
                newtonsCoefficients.at(i - 1) = (newtonsCoefficients.at(i-1)
                 - newtonsCoefficients.at(i-1-1)) / (data.at(i-1).first - data.at(i-j-1).first);
            }
        }
    }
    /**
     * @brief Calculates the interpolated value of y for the given x.
     * 
     * @param x Value for y to be calculated from.
     * @return double Interpolated value of y.
     */
    double operator()(double x) const override {
        int n = data.size();
        long double f = newtonsCoefficients.at(n - 1);
        for (int i=n-1; i>=1; i--) {
            f = f * (x-data.at(i-1).first) + newtonsCoefficients.at(i-1);
        }
        return (double) f;
    }
    /**
     * @brief Adds new point std::pair<double, double>(x, y) into dataset and 
     * updates the corresponding values for interpolation to be calculated correctly.
     * 
     * @param p New point to be added. 
     */
    void AddPoint(const std::pair<double, double> &p) {
        const double epsilon = 1e-15;
        for(auto &i : data)
            if(fabs(i.first - p.first) < epsilon) 
                throw std::domain_error("Invalid point");
        
        int n = data.size();

        data.push_back(p);

        std::vector<double> y_nplus1(n);
        y_nplus1.at(0) = p.second;

        const std::vector<double> &y_n = dodatneVrijednosti;
        
        for(int j=1; j<n; j++)
            y_nplus1.at(j) = (y_nplus1.at(j-1)-y_n.at(j-1)) / (data.at(n).first-data.at(n-j).first);
        
        double newNewtonCoefficient = 
            (y_nplus1.at(n-1) - newtonsCoefficients.at(n-1)) / (data.at(n).first - data.at(0).first);
        
        newtonsCoefficients.push_back(newNewtonCoefficient);
        dodatneVrijednosti = std::vector<double>(y_nplus1);
    }
    /**
     * @brief Get the Coefficients object - vector of coefficients of the polynomial given by the interpolation.
     * Degree of x starts from 0 to n-1, for n points.
     * 
     * @return std::vector<double> Vector of coefficients.
     */
    std::vector<double> GetCoefficients() const {
        int n = data.size();
        //koeficijenti polinoma interpolacije
        std::vector<double> koeficijenti(n, 0.0);
        //koeficijenti master polinoma
        std::vector<long double> w(n+1), v(n+1);
        w.at(0) = 1;
        for(int i=1; i<=n; i++) {
            w.at(i) = w.at(i-1);
            for(int j=i-1; j>0; j--)
                w.at(j) = w.at(j-1)-data.at(i-1).first*w.at(j);
            w.at(0) = -data.at(i-1).first * w.at(0);
        }        
        //koeficijent alfa, racunanje koeficijenata polinoma
    	for(int i=0; i<n; i++) {
            long double alfa = 1.0;
            for(int j=0; j<n; j++)
                if(j!=i) 
                    alfa *= data.at(i).first - data.at(j).first;
            alfa = data.at(i).second / alfa;

            for(int j=0; j<=n; j++) v[j] = w[j];
            for(int j=n-1; j>=0; j--) {
                v.at(j) += data.at(i).first * v.at(j+1);
                koeficijenti.at(j) += alfa * v.at(j+1); 
            }     
        }
        return koeficijenti;
    }
};

#endif