#ifndef MATHUTILITIES_H
#define MATHUTILITIES_H

// Do not change
static const float EPSILON = 0.0001f;

// Macro definitions
#define isZero(x) ((x < EPSILON) && (x > -EPSILON))
#define isEqual(x,y) (((x >= y) ? (x-y) : (y-x)) < EPSILON)
#define PI	3.141516f

#endif