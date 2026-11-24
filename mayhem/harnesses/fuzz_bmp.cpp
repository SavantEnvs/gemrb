// libFuzzer harness: GemRB BMP importer (header variants, 4/8/16/24/32-bit raster decode, palette).
// GetSprite2D() is not called: it needs the engine's VideoDriver, which this harness does not boot.
#include "fuzz_common.h"
#include "plugins/BMPImporter/BMPImporter.h"

using namespace GemRB;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
	BMPImporter unit;
	if (!unit.Open(FuzzStream("fuzz.bmp", data, size))) return 0;
	Palette pal;
	(void) unit.GetPalette(16, pal);
	(void) unit.GetPalette(256, pal);
	return 0;
}
