#ifndef __CAMAN_H
#define __CAMAN_H

#include <wand/MagickWand.h>

/* Struct definitions */
struct caman {
	MagickWand *image;
	PixelIterator *iterator;
	PixelWand *pixels;
};
typedef struct caman *CamanInstance;

/* Function prototypes */
CamanInstance NewCamanFromFile(char *);
CamanInstance NewCamanInstance(void);

void ThrowWandException(MagickWand *);

#endif
