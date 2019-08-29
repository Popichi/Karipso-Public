// bv.h — Bit Vector interface
// Author: Prof. Darrell Long + Modified by Anil Celik Maral
// Note: size is changed to uint64_t and reallocVec is added.

# ifndef _BVector
# define _BVector
# include <stdint.h>
# include "stack.h"
# include "statistics.h"

typedef struct bitV {
	uint8_t *v;
	uint64_t l;
} bitV;

bitV *newVec(uint64_t);

void delVec(bitV *);

void one(bitV *);

void setBit(bitV *, uint64_t);

void clrBit(bitV *, uint64_t);

uint8_t valBit(bitV *, uint64_t);

uint64_t lenVec(bitV *);

bitV *reallocVec(bitV *);
# endif