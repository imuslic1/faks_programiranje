/**
 * Univerzitet u Sarajevu 
 * Elektrotehnicki fakultet Sarajevo
 * Odsjek za Racunarstvo i informatiku
 * 
 * Numerički Algoritmi
 * Ismar Muslic, 19304
 * 
 * Implementacija raznih funkcija 
 * za rjesavanje problema linearne algebre
 * 
*/

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <cmath>

#include "Matrix.h"
#include "Vector.h"
#include "LUDecomposer.h"
#include "QRDecomposer.h"

/**
 * @brief Aplikativni testovi
 *
 * @return int 
 */

int main() {

    try {
        // Test Matrix creation and basic operations
        Matrix A = {{1, 2, 3},
                    {4, 5, 6},
                    {7, 8, 9}};

        std::cout << "Matrix A:\n"; A.Print();

        Matrix B = A; // Test copy constructor
        std::cout << "Matrix B (copy of A):\n"; B.Print();

        // Test matrix inversion
        try {
            Matrix A_inv = Inverse(A);
            std::cout << "Inverse of Matrix A:\n"; A_inv.Print();
        } catch (const std::domain_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        // Test matrix rank
        try {
            int rank_A = Rank(A);
            std::cout << "Rank of Matrix A: " << rank_A << std::endl;
        } catch (const std::domain_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        // Test matrix division
        try {
            Matrix C = A / 2.0;
            std::cout << "Matrix A divided by 2:\n"; C.Print();
        } catch (const std::domain_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        // Test matrix equality
        Matrix D = {{1, 2, 3},
                    {4, 5, 6},
                    {7, 8, 9}};

        try {
            bool equal = A.EqualTo(D);
            std::cout << "Matrix A is " << (equal ? "equal" : "not equal") << " to Matrix D\n";
        } catch (const std::domain_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        // Test matrix determinant
        try {
            double det_A = A.Det();
            std::cout << "Determinant of Matrix A: " << det_A << std::endl;
        } catch (const std::domain_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        // Test matrix reduction to RREF
        try {
            Matrix RREF_A = RREF(A);
            std::cout << "Reduced Row Echelon Form of Matrix A:\n"; RREF_A.Print();
        } catch (const std::domain_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }

    //Test LUDecomposer

    try {
        // Test LUDecomposer
        Matrix A = {{2, -1, 0},
                    {-1, 2, -1},
                    {0, -1, 2}};

        std::cout << "Matrix A:\n";
        A.Print();

        LUDecomposer luDecomposer(A);

        // Test Solve with Vector
        try {
            Vector bVec = {1, 0, 1};
            Vector xVec = luDecomposer.Solve(bVec);

            std::cout << "Solution x for Ax=b (Vector form):\n";
            xVec.Print();
        } catch (const std::domain_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid argument: " << e.what() << std::endl;
        }

        // Test Solve with Matrix
        try {
            Matrix B = {{1, 0, 1},
                        {0, 1, 0},
                        {1, 0, 1}};
            Matrix X = luDecomposer.Solve(B);

            std::cout << "Solution X for AX=B (Matrix form):\n";
            X.Print();
        } catch (const std::domain_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid argument: " << e.what() << std::endl;
        }

        // Test GetCompactLU
        try {
            Matrix compactLU = luDecomposer.GetCompactLU();
            std::cout << "Compact LU Decomposition:\n";
            compactLU.Print();
        } catch (const std::domain_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        // Test GetL
        try {
            Matrix L = luDecomposer.GetL();
            std::cout << "Lower Triangular Matrix L:\n";
            L.Print();
        } catch (const std::domain_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        // Test GetU
        try {
            Matrix U = luDecomposer.GetU();
            std::cout << "Upper Triangular Matrix U:\n";
            U.Print();
        } catch (const std::domain_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        // Test GetPermuation
        try {
            Vector permutation = luDecomposer.GetPermuation();
            std::cout << "Permutation Vector P:\n";
            permutation.Print();
        } catch (const std::domain_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }

    //QRDecomposer

    try {
        // Test QRDecomposer
        Matrix A = {{2, -1, 0},
                    {-1, 2, -1},
                    {0, -1, 2}};

        std::cout << "Matrix A:\n";
        A.Print();

        QRDecomposer qrDecomposer(A);

        // Test Solve with Vector
        try {
            Vector bVec = {1, 0, 1};
            Vector xVec = qrDecomposer.Solve(bVec);

            std::cout << "Solution x for Ax=b (Vector form):\n";
            xVec.Print();
        } catch (const std::domain_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid argument: " << e.what() << std::endl;
        }

        // Test Solve with Matrix
        try {
            Matrix B = {{1, 0, 1},
                        {0, 1, 0},
                        {1, 0, 1}};
            Matrix X = qrDecomposer.Solve(B);

            std::cout << "Solution X for AX=B (Matrix form):\n";
            X.Print();
        } catch (const std::domain_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid argument: " << e.what() << std::endl;
        }

        // Test MulQWith
        try {
            Vector v = {1, 2, 3};
            Vector result = qrDecomposer.MulQWith(v);

            std::cout << "Result of Q*v:\n";
            result.Print();
        } catch (const std::domain_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        // Test MulQTWith
        try {
            Vector v = {1, 2, 3};
            Vector result = qrDecomposer.MulQTWith(v);

            std::cout << "Result of Q^T*v:\n";
            result.Print();
        } catch (const std::domain_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        // Test GetQ
        try {
            Matrix Q = qrDecomposer.GetQ();
            std::cout << "Matrix Q:\n";
            Q.Print();
        } catch (const std::domain_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        // Test GetR
        try {
            Matrix R = qrDecomposer.GetR();
            std::cout << "Upper Triangular Matrix R:\n";
            R.Print();
        } catch (const std::domain_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }

    return 0;
}
