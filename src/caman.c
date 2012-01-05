#include "caman.h"

/* =============== Core API =============== */

/*
 * Creates and initializes a new CamanInstance.
 */
CamanInstance NewCamanFromFile(char *filename) {
	CamanBoolean status;
	CamanInstance caman = NewCamanInstance();
	
	caman->image = NewMagickWand();
	
	status = MagickReadImage(caman->image, filename);
	if (status == MagickFalse)
		ThrowWandException(caman->image);
	
	return caman;
}

/*
 * Creates a new bare CamanInstance and allocates the memory for you.
 */
CamanInstance NewCamanInstance() {
	CamanInstance inst = (CamanInstance) malloc(sizeof(CamanInstance *));
	return inst;
}

/*
 * Fully destroys a CamanInstance and frees the memory again.
 * Handles freeing the MagickWand allocations as well.
 */
void destroyCamanInstance(CamanInstance inst) {
	// MagickWand allocations
	DestroyPixelIterator(inst->iterator);
	DestroyMagickWand(inst->image);
	
	// The struct itself
	free(inst);
}

/*
 * Writes the given CamanInstance image to file.
 */
CamanBoolean writeCamanToFile(CamanInstance caman, char *filename) {
	CamanBoolean status;
	
	status = MagickWriteImages(caman->image, filename, MagickTrue);
	return status;
}

void CamanInitialize() {
	MagickWandGenesis();
}

void CamanFinish() {
	MagickWandTerminus();
}

/* =============== Internal functions =============== */

void loadCamanPixelIterator(CamanInstance caman) {
	caman->iterator = NewPixelIterator(caman->image);
	if (caman->iterator == (PixelIterator *) NULL)
		ThrowWandException(caman->image);
}

/* =============== Exception handling =============== */

void ThrowWandException(MagickWand *wand) {
	char *description;
	ExceptionType severity;
	
	description = MagickGetException(wand, &severity);
	fprintf(stderr, "%s %s %lu %s\n", GetMagickModule(), description);
	description = (char *) MagickRelinquishMemory(description);
	exit(-1);
}