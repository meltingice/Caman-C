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
			pixel->red = PixelGetRed(pixels[x]) * 255;
			pixel->green = PixelGetGreen(pixels[x]) * 255;
			pixel->blue = PixelGetBlue(pixels[x]) * 255;

			printf("Before: %f %f %f\n", pixel->red, pixel->green, pixel->blue);
			filter(pixel, adjust);
			clampRGBA(pixel);
			printf("After: %f %f %f\n", pixel->red, pixel->green, pixel->blue);

			PixelSetRed(pixels[x], getCamanColorNormalized(pixel->red));
			PixelSetGreen(pixels[x], getCamanColorNormalized(pixel->green));
			PixelSetBlue(pixels[x], getCamanColorNormalized(pixel->blue));
		}
		
		PixelSyncIterator(iterator);
	}

	DestroyPixelIterator(iterator);

	free(pixel);
}

void clampRGBA(CamanRGBA pixel) {
	if (pixel->red < 0) pixel->red = 0;
	if (pixel->red > 255) pixel->red = 255;
	if (pixel->green < 0) pixel->green = 0;
	if (pixel->green > 255) pixel->green = 255;
	if (pixel->blue < 0) pixel->blue = 0;
	if (pixel->blue > 255) pixel->blue = 255;
}

double getCamanColorNormalized(CamanColor color) {
	if (color < 0) return 0;
	if (color > 255) return 1.0;

	return color / 255;
}
