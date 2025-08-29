// Prototypes for ido math routines.
unsigned long long __ull_rem(unsigned long long left, unsigned long long right);
unsigned long long __ull_div(unsigned long long left, unsigned long long right);
long long __ll_rem(long long left, unsigned long long right);
long long __ll_div(long long left, long long right);
long long __ll_mod(long long left, long long right);

// Translations from libgcc math routines to ido ones.
unsigned long long __umoddi3(unsigned long long a, unsigned long long b) {
    return __ull_rem(a, b);
}

unsigned long long int __udivdi3(unsigned long long int a, unsigned long long int b) {
    return __ull_div(a, b);
}

long long __moddi3(long long a, long long b) {
    return __ll_rem(a, b);
}

long long __divdi3 (long long a, long long b) {
    return __ll_div(a, b);
}
