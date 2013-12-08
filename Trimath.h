#include <math.h>

// Maths
#define PI 3.14152965358 // Standard PI
double absolute(double A) {return (sqrt(A*A));} // The absolute value of a
double distance(double AX, double AY,double BX,double BY) {return (sqrt((BX-AX)*(BX-AX)+(BY-AY)*(BY-AY)));} // The distance between a and b
double direction(double AX, double AY,double BX,double BY) {return (atan2(BY-AY,BX-AX)*180.0/PI);} // The angle of vector a

// Loops
#define loopi(LOOP,MAX) for (LOOP=0;LOOP<MAX;LOOP++)