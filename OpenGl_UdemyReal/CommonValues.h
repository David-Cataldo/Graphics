#ifndef COMMONVALS
#define COMMONVALS

#include "stb_image.h"

struct TexCoords
{
	unsigned int u;
	unsigned int v;
};

#define COBBLESTONE TexCoords{1,0}
#define SAND TexCoords{1,2}

#endif