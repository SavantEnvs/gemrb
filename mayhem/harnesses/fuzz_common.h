// Shared helpers for the GemRB fuzz harnesses (Mayhem integration).
#ifndef GEMRB_FUZZ_COMMON_H
#define GEMRB_FUZZ_COMMON_H

#include "Streams/MemoryStream.h"

#include <cstdlib>
#include <cstring>

namespace GemRB {
// MemoryStream takes ownership of `data` and free()s it, so hand it a malloc'd copy.
inline MemoryStream* FuzzStream(const char* name, const uint8_t* data, size_t size)
{
	void* copy = malloc(size ? size : 1);
	if (size) memcpy(copy, data, size);
	return new MemoryStream(name, copy, size);
}
}

#endif
