#include <math.h>

#include "caman.h"
#include "filters.h"

void brightness(CamanInstance caman, CamanColor adjust) {
	adjust = 255 * (adjust / 100);
	camanProcessFilter(caman, adjust, brightnessFilter);
}

void brightnessFilter(CamanRGBA pixel, CamanColor adjust) {
	pixel->red += adjust;
	pixel->blue += adjust;
	pixel->green += adjust;
}