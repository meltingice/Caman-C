#ifndef __CAMAN_H
#define __CAMAN_H

#include <wand/MagickWand.h>

typedef MagickBooleanType CamanBoolean;
typedef MagickPixelPacket CamanPixel;

/* Struct definitions */
struct caman {
	MagickWand *image;
	PixelIterator *iterator;
};
typedef struct caman *CamanInstance;

#include "filters.h"
#include "render.h"

/* Function prototypes */
CamanInstance NewCamanFromFile(char *);
CamanInstance NewCamanInstance(void);
void destroyCamanInstance(CamanInstance);
CamanBoolean writeCamanToFile(CamanInstance, char *);
void CamanInitialize(void);
void CamanFinish(void);

void loadCamanPixelIterator(CamanInstance);

/* Exception handlers */
void ThrowWandException(MagickWand *);

#endif
