#include "caman.h"

#include <stdio.h>
#include <stdlib.h>
#include <wand/MagickWand.h>

/* =============== Core functions =============== */

/*
 * Creates and initializes a new Caman instance
 */
CamanInstance NewCamanFromFile(char *filename) {
	MagickBooleanType status;
	CamanInstance caman = NewCamanInstance();
	
	MagickWandGenesis();
	caman->image = NewMagickWand();
	
	status = MagickReadImage(caman->image, filename);
	if (status == MagickFalse)
		ThrowWandException(caman->image);
}

CamanInstance NewCamanInstance() {
	CamanInstance inst = (CamanInstance) malloc(sizeof(CamanInstance *));
	return inst;
}

void destroyCamanInstance(CamanInstance inst) {
	// MagickWand allocations
	DestroyPixelIterator(inst->iterator);
	DestroyMagickWand(inst->image);
	
	// The instance itself
	free(inst);
}

/* =============== Exception handling =============== */

void ThrowWandException(MagickWand wand) {
	char *description;
	ExceptionType severity;
	
	description = MagickGetException(wand, &severity);
	fprintf(stderr, "%s %s %lu %s\n", GetMagickModule(), description);
	description = (char *) MagickRelinquishMemory(description);
	exit(-1);
}