#include <math.h>

#include "caman.h"
#include "render.h"

void camanProcessFilter(CamanInstance caman, double adjust, 
	void (*filter)(CamanRGBA, CamanColor)) {
	
	PixelIterator *iterator;
	PixelWand **pixels;

	long y;
	register long x;
	unsigned long width;
	CamanRGBA pixel;

	pixel = (CamanRGBA) malloc(sizeof(CamanRGBA *));

	iterator = NewPixelIterator(caman->image);

	for (y = 0; y < (long) MagickGetImageHeight(caman->image); y++) {
		pixels = PixelGetNextIteratorRow(iterator, &width);

		if (pixels == (PixelWand **) NULL)
			break;

		for (x = 0; x < (long) width; x++) {
			pixel->red = (CamanColor)(PixelGetRedQuantum(pixels[x]) / (CamanColor) QuantumRange);
			pixel->green =  (CamanColor)(PixelGetGreenQuantum(pixels[x]) / (CamanColor)QuantumRange);
			pixel->blue = (CamanColor)(PixelGetBlueQuantum(pixels[x]) / (CamanColor) QuantumRange);

			pixel->red *= 255.0;
			pixel->green *= 255.0;
			pixel->blue *= 255.0;

			printf("Before: %f %f %f\n", pixel->red, pixel->green, pixel->blue);
			filter(pixel, adjust);
			clampRGBA(pixel);
			//printf("After: %f %f %f\n", pixel->red, pixel->green, pixel->blue);
			printf("After: %d %d %d\n", getCamanColorQuantum(pixel->red), getCamanColorQuantum(pixel->green), getCamanColorQuantum(pixel->blue));

			PixelSetRedQuantum(pixels[x], getCamanColorQuantum(pixel->red));
			PixelSetGreenQuantum(pixels[x], getCamanColorQuantum(pixel->green));
			PixelSetBlueQuantum(pixels[x], getCamanColorQuantum(pixel->blue));
		}

		PixelSyncIterator(iterator);
	}

	DestroyPixelIterator(iterator);

	//free(pixel);
}

void clampRGBA(CamanRGBA pixel) {
	if (pixel->red < 0) pixel->red = 0;
	if (pixel->red > 255) pixel->red = 255;
	if (pixel->green < 0) pixel->green = 0;
	if (pixel->green > 255) pixel->green = 255;
	if (pixel->blue < 0) pixel->blue = 0;
	if (pixel->blue > 255) pixel->blue = 255;
}

Quantum getCamanColorQuantum(CamanColor color) {
	if (color < 0) return 0;
	if (color > 255) return QuantumRange;

	return (Quantum)((color / 255) * (CamanColor) QuantumRange);
}
