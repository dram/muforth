/*
 * This file is part of muFORTH: http://muforth.nimblemachines.com/
 *
 * Copyright (c) 2002-2010 David Frech. All rights reserved, and all wrongs
 * reversed. (See the file COPYRIGHT for details.)
 */

#include "muforth.h"

#include <stdlib.h>     /* exit(3) */

/*
 * Support for "thawing" previously "frozen" dictionary images.
 */

struct freeze_header
{
    cell id;            /* "mu4z"; or the value 0x7A34756D (little endian) */
    cell version;       /* must be 1 */
    cell image_cells;   /* size of image, in cells */
    cell prim_cells;    /* "primitive" part of dictionary */
    cell reloc_cells;   /* size of reloc bitmap, in cells */
    cell dot_forth;     /* relative ptr to last .forth. word */
    cell dot_compiler;  /* relative ptr to last .compiler. word */
};

/* NOTE: by simply comparing the primitive prefix part of the frozen
 * reloc_bitmap to the just inited reloc_bitmap we can quickly tell if the
 * two have the same shape. This may be enough to check compatibility. */

void muforth_thaw_image()
{
}

void mu_bye()
{
    exit(0);
}

/*
 * This is its own main. It runs instead of the normal muforth one.
 */
int main(int argc, char *argv[])
{
    muforth_init();
    muforth_thaw_image();
    muforth_interpret_warm();
    return 0;
}
