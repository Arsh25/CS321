// sa2a.h
// Glenn G. Chappell
// 11 Feb 2015
//
// For CS 321 Spring 2015
// A Computation to Delegate
// Used in Assignment 2, Exercise A
// There is no associated source file

#ifndef FILE_SA2A_H_INCLUDED
#define FILE_SA2A_H_INCLUDED

#include <cassert>
// For: assert


// Prototypes
inline
int f1(int k, int level);


// sa2a
// Computation to delegate.
// Parameter n should be positive.
inline
int sa2a(int n)
{
    assert(n > 0);

    int nn = (n / 100) + 99-(n % 100);
    if (nn == 0)
        nn = 1;
    return f1(nn, 4);
}


// f1
// Helper function for sa2a.
// Parameter k should be postive; level should be nonnegative.
inline
int f1(int k, int level)
{
    assert(k > 0);
    assert(level >= 0);

    int count = 0;
    while (k > 1)
    {
        if (k % 2)
            k = 3*k + 1;
        else
            k /= 2;

        int up;
        if (level == 0)
            up = 1;
        else
            up = 1+f1(k, level-1);
        count += up;
    }
    return count;
}


#endif //#ifndef FILE_SA2A_H_INCLUDED

