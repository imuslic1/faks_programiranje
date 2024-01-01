using Pkg
Pkg.add("NumericalIntegration")
Pkg.add("Polynomials")
Pkg.add("Calculus")

using Polynomials
using Calculus
using NumericalIntegration

# 1.
P = Polynomial([5, 1, 2, 1])
    # P_prim
Polynomials.derivative(P)
    # P_dvoprim
Polynomials.derivative(Polynomials.derivative(P))
    # P_integral
Polynomials.integrate(P)

# 2.
    # 1. izvod
x = pi/2
Calculus.derivative(sin, x)
Calculus.derivative(cos, x)
    #2. izvod
Calculus.second_derivative(sin, x)
Calculus.second_derivative(cos, x)

# 3.

# 4.
fun(x) = sin(x) + cos(x) * exp(x)
Calculus.derivative(fun, x)
Calculus.second_derivative(fun, x)

# 5.
t = 0:0.5:pi
sinus = sin.(t)
NumericalIntegration.integrate(t, sinus)

# 6.
myfun(x) = (x * sin(30*x))/(sqrt(1-(x/2*pi)^2))



