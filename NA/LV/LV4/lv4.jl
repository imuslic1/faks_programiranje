using Pkg
Pkg.add("Polynomials")
using Polynomials

# 1.
P1 = Polynomial(1:2:5)
P2 = fromroots(1:3:10)

roots(P1)
coeffs(P2)

# 2.
P1 + P2
P1 - P2
P1 * P2
div(P1,P2)

# 3.
P3 = Polynomial([1, 2, 3])

v = [1, 2, 3, 4, 5]

P3(5)
P3.(v)
P3(5+2im)

# 4.
CH4 = ChebyshevT([1, 0, 7, 0, 22/7])
PCH4 = convert(Polynomial, CH4)

Polynomials.domain(CH4)
x = -10:10
mapdomain(CH4, x)

# 5.
x = 1:10
y = cos.(x)

P4 = fit(x, y, 3)
Pkg.add("Plots")
using Plots

scatter(x, y, markerstrokewidth=0, label="Data")
plot!(P4, extrema(x)..., label="Interpolation")


Pkg.update("Plots")
