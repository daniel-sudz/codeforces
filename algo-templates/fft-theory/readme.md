# Note
Iterative version much more annoying to type out from scratch without mistakes. But constant is significantly lower so in practice you would always use it.

# Variations
Normal FFT - (complex roots of unity) <br>
SQRT / FFTMod - (split problem into 4 complex FFTs to improve precision) <br>
NTT - (multiplicative ring mod c\*k\^n + 1) <br>
NTT + CRT - (run NTT 2-3 times and reconstruct solution mod any prime p) 

# 2-in-one trick

Assume that you want to perform a convolution with two polynomials $f(x)$ and $g(x)$ where all coefficients belong to the reals. This trick allows you to use complex roots of unity to reduce the number of FFT calls from 3 to 2. Here's how: 

Create a polynomial $z(x)$ where each cofficient is a complex pair with the real component being the coeffient from $f(x)$ and the imaginary component being the corresponding coefficient from $g(x)$. 

Ex: 
```math
f(x) = a1 + a2*x ...
```
```math
g(x) = b1 + b2*x ...
```
```math
z(x) = (a1 + i*b1) + (a2 + i*b2)*x ...
```
```math
z(x) = f(x) + i*g(x)
```
## Lemma 1
Let $conj(x)$ be the conjugate operator. Ie. $conj(a+b\*i) = a - b\*i$.

For a polynomial with real coefficients we can show $conj(f(x)) = f(conj(x))$ using induction: 

Assume: <br>

```math
conj((a+b*i)^N) = (conj(a+b*i))^N
```
```math
(a+b*i)^N = (a1 + a2*i)
```

Then: 
```math
(a+b*i)*(a1 + a2*i) = (a*a1 - b*a2) + (a*a2 + b*a1)*i
```
```math
(a-b*i)*(a1 - a2*i) = (a*a1 - b*a2) - (a*a2 + b*a1)*i
```

Which shows:
```math
conj((a+b*i)^{N+1}) = (conj(a+b*i))^{N+1}
```

## Lemma 2
Let $w^n$ be a complex root of unity. Then $w^n = conj(w^{-n})$.

Proof: 

```math
 w^n = cos(2*pi*n / N) + i*sin(2*pi*n /N) 
```
```math
 w^{-n} = cos(-2*pi*n / N) + i*sin(-2*pi*n /N) 
```
```math
 w^{-n} = cos(2*pi*n / N) - i*sin(2*pi*n /N) 
```

## The trick (todo)




```math

```

# Resources
https://web.archive.org/web/20230115043355/http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf

# Verification 
https://www.spoj.com/problems/POLYMUL/