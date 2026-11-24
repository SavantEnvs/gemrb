// libFuzzer harness: GemRB WAV (RIFF/PCM) sound importer — WavPCMReader::Import + read_samples.
#include "fuzz_common.h"
#include "plugins/WAVReader/WAVReader.h"

using namespace GemRB;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
	WavPCMReader unit;
	if (!unit.Open(FuzzStream("fuzz.wav", data, size))) return 0;
	short buf[4096];
	// read_samples returns 0 once the data chunk's declared length is exhausted. That length is a
	// 32-bit header field, so decode at most 1M samples per input to keep the work per input bounded.
	size_t total = 0;
	size_t got;
	while (total < (1u << 20) && (got = unit.read_samples(buf, 4096)) > 0) {
		total += got;
	}
	return 0;
}
