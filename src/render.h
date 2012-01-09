#ifndef __RENDER_H
#define __RENDER_H

/* Function prototypes */
void camanProcessFilter(CamanInstance, double, void (*filter)(CamanRGBA, CamanColor));
void clampRGBA(CamanRGBA);
double getCamanColorNormalized(CamanColor);

#endif