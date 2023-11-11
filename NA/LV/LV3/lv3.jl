using Pkg
Pkg.add("LinearAlgebra")
Pkg.add("Plots")
Pkg.add(url="https://github.com/SciML/DataInterpolations.jl")
using LinearAlgebra
using Plots
using DataInterpolations

# z1
import Pkg; 
Pkg.add("Plots")
using Plots
x=range(0, 2pi, length=100)
y=sin.(x)
Plots.plot(x,y,title = "Sinus", label = "sin(x)")

#z2









using Pkg;
pkg"instantiate"

using Pkg
Pkg.activate(; temp = true)
Pkg.add("GR_jll")
import GR_jll

Pkg.add("GR")
Base.compilecache(Base.identify_package("GR"))
using GR
GR.plot(rand(10))

