using Pkg
Pkg.add("LinearAlgebra")
Pkg.add(url="https://github.com/JuliaMatrices/SpecialMatrices.jl")
Pkg.add("RowEchelon")
Pkg.add("Images")
Pkg.add("TestImages")
Pkg.add("ImageMagick")
using LinearAlgebra
using SpecialMatrices
using RowEchelon
using Images
using TestImages
using ImageMagick

# 1. zadatak: lijevo dijeljenje 
A = [2 1 3; 2 6 8; 6 8 18]
B = [1; 3; 5]

X = A\B
(A.'*A)\(B.'*B)
inv(A) * B
pinv(A) * B

# 2. zadatak: AX = B
A = [2 1; -3 1; -1 1]
B = [-1; -2; 1]

X = (A'*B)\(A'*A)

# 3. zadatak: desno dijeljenje 
A = [2 4 6 8; 3 5 7 9]
B = [10 10 10 10; 10 10 10 10]

X = A/B
# X = A * inv(B)
X = A * pinv(B)

A = [1 2 3; 4 5 6; 7 8 9]
B = [7 5 6; 2 0 8; 5 7 1]

X = A/B
X = A * inv(B)
X = A * pinv(B)

# 4. zadatak: Riemannova i Hilbertova
C = Riemann(3)
D = Hilbert(3)

det(C)
det(D)

rank(C)
rank(D)

cond(C)
cond(D)

# 5. zadatak: LU i Choleski
A = [1 -2 -2 -3 
     3 -9  0 -9 
    -1  2  4  7
    -3 -6  26 2]

B = [2 -1 0; -1 2 -1; 0 -1 2]

L, U, p = lu(A)
A[p, :]
p
(L*U)
factorize(A)  #implementirano je vise algoritama faktorizacije, 
              #bira se najpogodniji za proslijeđenu matricu
cholesky(B)
 
# 6. zadatak: rref
M = 
[3  4  18  34  0  2  31
 1 -3  -7  -6  2  4  26
 2  1   7  16  3 -1  27
 5 11  43  74  2  0  56
 3 -3  -3   6 -1  14 55
-2  0  -4 -12  1  5   6
 1 -6 -16 -18  4  4  33]
 
rref(M)
