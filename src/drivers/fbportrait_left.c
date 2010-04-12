/*
 * Copyright (c) 2000, 2001, 2010 Greg Haerr <greg@censoft.com>
 *
 * Left portrait mode subdriver for Microwindows
 */
#include <assert.h>
#include <string.h>
#include "device.h"
#include "fb.h"

static void
fbportrait_drawpixel(PSD psd,MWCOORD x, MWCOORD y, MWPIXELVAL c)
{
	psd->orgsubdriver->DrawPixel(psd, y, psd->xvirtres-x-1, c);
}

static MWPIXELVAL
fbportrait_readpixel(PSD psd,MWCOORD x, MWCOORD y)
{
	return psd->orgsubdriver->ReadPixel(psd, y, psd->xvirtres-x-1);
}

static void
fbportrait_drawhorzline(PSD psd,MWCOORD x1, MWCOORD x2, MWCOORD y, MWPIXELVAL c)
{
	/*x2 = psd->xvirtres-x2-1;
	while (x2 <= (psd->xvirtres-x1-1))
		fbportrait_drawpixel(psd, y, x2++, c);*/

	psd->orgsubdriver->DrawVertLine(psd, y, psd->xvirtres-x2-1, psd->xvirtres-x1-1, c);
}

static void
fbportrait_drawvertline(PSD psd,MWCOORD x, MWCOORD y1, MWCOORD y2, MWPIXELVAL c)
{
	/*while (y1 <= y2)
		fbportrait_drawpixel(psd, y1++, psd->xvirtres-x-1, c);*/

	psd->orgsubdriver->DrawHorzLine(psd, y1, y2, psd->xvirtres-x-1, c);
}

static void
fbportrait_fillrect(PSD psd,MWCOORD x1, MWCOORD y1, MWCOORD x2, MWCOORD y2, MWPIXELVAL c)
{
#if 0
	register ADDR16 addr;
        
#if DEBUG
	assert (x2 >= 0 && x2 < psd->yres);
	assert (x1 >= 0 && x1 < psd->yres);
	assert (x1 >= x2);
	assert (y1 >= 0 && y1 < psd->xres);
	assert (y2 >= 0 && y2 < psd->xres);
	assert (y2 >= y1);
	assert (c < psd->ncolors);
#endif
 	x1 = psd->xvirtres-x1-1;
	x2 = psd->xvirtres-x2-1;
	
	DRAWON;        
	if(gr_mode == MWMODE_COPY) {                  
		// bytes per RECT-line
		int len = (y2-y1+1) << 1;
		ADDR16 addr0;

		// first line
		addr = ((ADDR16)psd->addr) + x2 * psd->linelen + y1;
		addr0 = addr;
		while (y1++ <= y2)
			*addr++ = c;

		// copy first line to all  other lines...
		addr = addr0;
		while (++x2 <= x1) {
			addr += psd->linelen;
			memcpy(addr, addr0, len);
		}
	} else {
		while(x2 <= x1) {
			addr = ((ADDR16)psd->addr) + y1 + x2++ * psd->linelen;
			while(y1++ <= y2) {
				applyOp(gr_mode, c, addr, ADDR16);
				++addr;
			}
		}
	}        
	DRAWOFF;
#else
	x1 = psd->xvirtres-x1-1;
	x2 = psd->xvirtres-x2-1;
	while(x2 <= x1)
		psd->orgsubdriver->DrawHorzLine(psd, y1, y2, x2++, c);
#endif
}

static void
fbportrait_blit(PSD dstpsd,MWCOORD destx,MWCOORD desty,MWCOORD w,MWCOORD h,
	PSD srcpsd, MWCOORD srcx,MWCOORD srcy,long op)
{
	dstpsd->orgsubdriver->Blit(dstpsd, desty, dstpsd->xvirtres-destx-w,
		h, w, srcpsd, srcy, srcpsd->xvirtres-srcx-w, op);
}

static void
fbportrait_stretchblit(PSD dstpsd, MWCOORD destx, MWCOORD desty, MWCOORD dstw,
	MWCOORD dsth, PSD srcpsd, MWCOORD srcx, MWCOORD srcy, MWCOORD srcw,
	MWCOORD srch, long op)
{
	dstpsd->orgsubdriver->StretchBlit(dstpsd, desty, dstpsd->xvirtres-destx-dstw,
		dsth, dstw, srcpsd, srcy, srcpsd->xvirtres-srcx-srcw, srch, srcw, op);
}

#if MW_FEATURE_PSDOP_ALPHACOL
static void
fbportrait_drawarea_alphacol(PSD dstpsd, driver_gc_t * gc)
{
	ADDR8 alpha_in, alpha_out;
	MWCOORD	in_x, in_y, in_w, in_h;
	MWCOORD	out_x, out_y, out_w, out_h;
	driver_gc_t	l_gc;

	l_gc = *gc;
	l_gc.dstx = gc->dsty;
	l_gc.dsty = dstpsd->xvirtres - gc->dstx - gc->dstw;
	l_gc.dstw = gc->dsth;
	l_gc.dsth = gc->dstw;

	l_gc.srcx = 0;
	l_gc.srcy = 0;
	l_gc.src_linelen = l_gc.dstw;
	if (!(l_gc.misc = ALLOCA(l_gc.dstw * l_gc.dsth)))
		return;

	alpha_in = ((ADDR8)gc->misc) + gc->src_linelen * gc->srcy + gc->srcx;
	in_w = gc->dstw;
	in_h = gc->dsth;

	alpha_out = l_gc.misc;
	out_w = l_gc.dstw;
	out_h = l_gc.dsth;

	for (in_y = 0; in_y < in_h; in_y++) {
		for (in_x = 0; in_x < in_w; in_x++) {
			out_y = (out_h - 1) - in_x;
			out_x = in_y;

			alpha_out[(out_y * out_w) + out_x] = alpha_in[(in_y * in_w) + in_x];
		}
	}

	dstpsd->orgsubdriver->DrawArea(dstpsd, &l_gc, PSDOP_ALPHACOL);

	FREEA(l_gc.misc);
}
#endif

static void
fbportrait_drawarea(PSD dstpsd, driver_gc_t * gc, int op)
{
	if (!dstpsd->orgsubdriver->DrawArea)
		return;

	switch(op) {
#if MW_FEATURE_PSDOP_ALPHACOL
	case PSDOP_ALPHACOL:
		fbportrait_drawarea_alphacol(dstpsd, gc);
		break;
#endif
	}
}

SUBDRIVER fbportrait_left = {
	NULL,
	fbportrait_drawpixel,
	fbportrait_readpixel,
	fbportrait_drawhorzline,
	fbportrait_drawvertline,
	fbportrait_fillrect,
	fbportrait_blit,
	fbportrait_drawarea,
	fbportrait_stretchblit
};
