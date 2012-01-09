#ifndef __CAMAN_H
#define __CAMAN_H

#include <wand/MagickWand.h>

typedef MagickBooleanType CamanBoolean;
typedef double CamanColor;

/* Struct definitions */
struct caman {
	MagickWand *image;
};

struct camanrgba {
	CamanColor red;
	CamanColor green;
	CamanColor blue;
};

typedef struct caman *CamanInstance;
typedef struct camanrgba *CamanRGBA;

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
