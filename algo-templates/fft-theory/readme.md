# Note
Iterative version much more annoying to type out from scratch without mistakes. But constant is significantly lower so in practice you would always use it.

# Variations
Normal FFT - (complex roots of unity) <br>
SQRT / FFTMod - (split problem into 4 complex FFTs to improve precision) <br>
NTT - (multiplicative ring mod c\*k\^n + 1) <br>
NTT + CRT - (run NTT 2-3 times and reconstruct solution mod any prime p) 

# verification 
https://www.spoj.com/problems/POLYMUL/
