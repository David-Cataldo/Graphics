#ifndef COMMONVALS
#define COMMONVALS

#include "stb_image.h"

const int MAX_POINT_LIGHTS = 3;
const int MAX_SPOT_LIGHTS = 3;

using PhySimsDirection = unsigned int;
using PhySimsAxis = unsigned int;
using PhySimsAngleMode = unsigned int;

// Translation Directions
#define PS_FORWARD 0
#define PS_BACKWARD 1
#define PS_LEFT 2
#define PS_RIGHT 3
#define PS_UP 4
#define PS_DOWN 5

// Rotation/Scale axes
#define PS_X_AXIS 6
#define PS_Y_AXIS 7
#define PS_Z_AXIS 8

// Angle types
#define PS_DEGREES 9
#define PS_RADIANS 10


#endif