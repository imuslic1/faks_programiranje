/**
 * @file AbstractInterpolator.h
 * @author Ismar Muslic, 19304 (imuslic1@etf.unsa.ba)
 * @brief 
 * @version 0.1
 * @date 21-12-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ABSTRACT_INTERPOLATOR
#define ABSTRACT_INTERPOLATOR

#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

/**
 * @brief Abstract class for other types of Interpolator classses to be derived from
 * 
 */
class AbstractInterpolator {
    mutable int lastLocated;
    /**
     * @brief Checks whether the given parameter x is in the interval (index, index+1]
     * 
     * @param x value to check for
     * @param index starting index of the interval
     * @return true if x is in the interval,
     * @return false if x is not in the interval
     */
    inline bool inInterval(double x, int index) const {
        if(index<0 || index+1 >= data.size())
            return false;
        return x > data.at(index).first && x <= data.at(index+1).first;
    }

protected: 
    std::vector<std::pair<double, double>> data;
    /**
     * @brief Locates the given parameter x and stores the interval (xi, xi+1] of indexes internally into the class object.
     * 
     * @param x value to be located
     * @return int index of located value. 0 if x <= x1 from data, n if x > xn from data.
     */
    int Locate(double x) const;
public:
    /**
     * @brief Prints the data points given to the Interpolator.
     */
    void printData() const;
    
    /**
     * @brief Construct a new Abstract Interpolator:: Abstract Interpolator object
     * 
     * @param data Points (x, y) to be added as data entries for interpolation
     */
    AbstractInterpolator(const std::vector<std::pair<double, double>> &data);
    /**
     * @brief XXX
     * 
     * @param x JE X
     * @return double NEKI BROJ
     */
    virtual double operator()(double x) const = 0;
};

inline AbstractInterpolator::AbstractInterpolator(const std::vector<std::pair<double, double>> &data) {
    lastLocated = 1;
    std::vector<std::pair<double, double>> sortedData = data;
    std::sort(sortedData.begin(), sortedData.end(), [](const std::pair<double, double> &p1, 
        const std::pair<double, double> &p2) {
            if(p1.first == p2.first)
                throw std::domain_error("Invalid data set");
        return p1.first<p2.first;
    });
    this->data = sortedData;
}

inline int AbstractInterpolator::Locate(double x) const {
    int n = data.size()-1;
    //if x is less than the first element
    if(x<=data.at(0).first) {
        lastLocated = 0;
        return 0;
    }
    //if x is greater than the last element
    if(x>data.at(n).first) {
        lastLocated = n;
        return n+1;
    }   
    //Check if x is in the last interval
    if(inInterval(x, lastLocated)) {
        return lastLocated+1;
    }   
    //Check if x is in the interval previous to the last interval
    if(inInterval(x, lastLocated-1)) {
        --lastLocated;
        return lastLocated+1;
    }
    //Check if x is in the interval following the last interval
    if(inInterval(x, lastLocated+1)) {
        ++lastLocated;
        return lastLocated+1;
    }   
    //Binary search
    auto it = std::lower_bound(data.cbegin(), data.cend(), x,
        [](const std::pair<double, double> &pair, double x) {
            return pair.first < x;
        });
    //Update the interval
    lastLocated = it-data.cbegin();
    return lastLocated;
}

inline void AbstractInterpolator::printData() const {
    for(int i=0; i<this->data.size(); ++i)
        std::cout<<"{"<<this->data.at(i).first<<", "<<this->data.at(i).second<<"} ";
}

#endif