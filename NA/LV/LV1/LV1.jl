Pkg.add("LinearAlgebra")
using LinearAlgebra

print("Z1\n")

3*(456/23) + 31.54 + 2^6 
sin(pi/7) * ℯ^0.3 * (2+0.9im)
sqrt(2) * log(10) 
(5+3im)/(1.2+4.5im) 

print("Z2\n")

a = (atan(5)+exp(5.6))/3 
b = sin(pi/3)^1/15 
c = (log(15+1)/23)
d = sin(pi/2) + cos(pi) 

(a+b)c 
acos(b)*asin(c/11)  
(a-b)^4/d 
c^1/a + b*im/(3+2im) 

print("Z3\n")
A = [1 -4im sqrt(a); log(complex(-1)) sin(pi/2) cos(pi/3); asin(0.5) acos(0.8) exp(0.8)]

transpose(A) 
At = transpose(A) 
At + A
A * At 
At * A 
det(A)
inv(A)

print("Z4\n")
nule = zeros(8, 9)
jedinice = ones(7, 5)
I(5) + zeros(5, 5)
rand(4, 9)

print("Z5\n")
a = [2 7 6; 9 5 1; 4 3 8] 
size(a) 
tr(a)    
minimum(a[1, :]) 
maximum(a[1, :]) 
minimum(a[2, :]) 
maximum(a[2, :]) 
minimum(a[3, :]) 
maximum(a[3, :]) 
minimum(diag(a)) 
maximum(diag(a)) 
sum(a) #suma svih elemenata
sum(a, dims=1) #suma po kolonama
sum(a, dims=2) #suma po redovima
tr(a) #suma po dijagonali

a = [1 2 3; 4 5 6; 7 8 9]
b = [1 1 1; 2 2 2; 3 3 3] 
a'
b'
c = sin.(a) 
c = sin.(a) * cos.(b)
c = a^1/3
c = a.^1/3 

sin(5) 