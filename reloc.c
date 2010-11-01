/*
 * This file is part of muFORTH: http://muforth.nimblemachines.com/
 *
 * Copyright (c) 2002-2010 David Frech. All rights reserved, and all wrongs
 * reversed. (See the file COPYRIGHT for details.)
 */

#include "muforth.h"

/*
 * Support for creating a relocation bitmap so that a muforth dictionary
 * can be written out ("frozen") and later quickly read in ("thawed"). This
 * is useful only for very big dictionaries where compiling from source at
 * start time is too slow.
 */

ucell reloc_bitmap[RELOC_CELLS];

/* index is a bit index into our bitmap */
#define index2mask(i)       (1 << ((i) & 31))
#define index2offset(i)     ((i) >> 5)

void mark(int index)
{
    reloc_bitmap[index2offset(index)] |= index2mask(index);
}

int marked(int index)
{
    return reloc_bitmap[index2offset(index)] & index2mask(index);
}

#define addr2index(a)       ((a) >> 2)
/* Convert a cell address -- 4-byte aligned -- to an index, and mark it */
void mu_mark()
{
    mark(addr2index(TOP));
    DROP(1);
}

/* Convert a cell address -- 4-byte aligned -- to an index, and see if it's
 * marked.
 */
void mu_marked()
{
    TOP = marked(addr2index(TOP));
}
