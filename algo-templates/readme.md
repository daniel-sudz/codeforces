# number theory trivia 
1) Maximum number of divisors of any number grows rather slowly. Around N^(1/3) to N^(1/2). http://oeis.org/A346729
2) Any even number can be written as the sum of two primes https://en.wikipedia.org/wiki/Goldbach%27s_conjecture
3) Number of primes grows rather quickly https://web.archive.org/web/20220321222608/https://primes.utm.edu/howmany.html
4) Linear sieve to precompute min prime factor of all number in range [2,n] in O(n). Then can answer factorization queries in O(log(n)).
5) Chinese remainder theorem: given p1,p2,p3,p4... are co-prime, there is a unique solution to the equations <br> 
x = a1 (mod p1) <br>
x = a2 (mod p2) <br>
x = a3 (mod p3) ... <br> 
bounded by x < lcm(p1,p2,p3,p4...)

# Convex Hull
1) Jarvis Gift Wrapping O(N\*k), N=points, k=convex hull points
2) Graham Sweep (O(NlogN)) N=points

# Randomized 
1) Locality sensitive hashing (h-function bucketing on strings) 
2) Bloom Filter
