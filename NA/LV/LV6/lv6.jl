using Pkg;
Pkg.add("NLsolve")
Pkg.add("Optim")
Pkg.add("FFTW")
Pkg.add("DSP")
Pkg.add("DifferentialEquations")

using NLsolve;
using Optim;
using FFTW;
using DSP;
using DifferentialEquations;

# 1. a)
function f(x)
    return cos(x[1]) - x[1];
end

result = nlsolve(f, [0.0]);
result

# 2. b)
function sistem1!(F, x)
    F[1] = x[2] - x[1]^2 +1
    F[2] = x[1]-(2.0*x[2]-x[2].^2)/3.0;
end

x0y0 = [1.0, -3.0]
x1y1 = [0.0, 8.0]

rezultat_1 = nlsolve(sistem1!, x0y0)
rezultat_2 = nlsolve(sistem1!, x1y1)

# 2. a)

