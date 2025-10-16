#include "primes.hpp"
#include <cstdint>

std::vector<u32> sieve_primes(u32 limit) {
    std::vector<char> is(limit + 1, true);
    const u32 SIEVE_MAX = 50000000u;
    if (limit > SIEVE_MAX) limit = SIEVE_MAX; //clamp limit

    //0 and 1 are not prime numbers
    is[0] = false;
    if (limit >= 1) is[1] = false;
    
    for (u32 p = 2; (uint64_t)p * p <= limit; ++p) {
        if (is[p]) {
            //mark all multiples of p (starting from p^2) as non-prime
            for (u32 q = p * p; q <= limit; q += p) {
                is[q] = false;
            }
        }
    }
    
    std::vector<u32> out;
    out.reserve(limit / 10); //preallocate to reduce reallocations
    for (u32 i = 2; i <= limit; ++i) {
        if (is[i]) out.push_back(i);
    }
    return out;
}

std::vector<u32> global_primes = sieve_primes(50000000u); //global vector of all the precomputed primes up to 50000000
