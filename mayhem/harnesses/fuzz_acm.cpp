// libFuzzer harness: GemRB ACM/WAVC audio decoder (bit-stream unpacker + subband decoder).
#include "fuzz_common.h"
#include "plugins/ACMReader/ACMReader.h"

using namespace GemRB;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
	ACMReader unit;
	if (!unit.Open(FuzzStream("fuzz.acm", data, size))) return 0;
	short buf[4096];
	// read_samples returns 0 once the header's declared sample count is exhausted. The header
	// can declare up to 4G samples, so decode at most 1M per input to keep the work per input bounded.
	size_t total = 0;
	size_t got;
	while (total < (1u << 20) && (got = unit.read_samples(buf, 4096)) > 0) {
		total += got;
	}
	return 0;
}
