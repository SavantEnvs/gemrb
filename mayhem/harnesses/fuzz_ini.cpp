// libFuzzer harness: GemRB INI parser, iterating every group and key through the typed getters.
#include "fuzz_common.h"
#include "plugins/INIImporter/INIImporter.h"

using namespace GemRB;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
	INIImporter unit;
	if (!unit.Open(std::unique_ptr<DataStream>(FuzzStream("fuzz.ini", data, size)))) return 0;

	(void) unit.GetTagsCount();
	for (const auto& group : unit) {
		const std::string& tag = group.GetName();
		for (const auto& kv : group) {
			StringView key(kv.first);
			(void) unit.GetKeyAsString(StringView(tag), key);
			(void) unit.GetKeyAsInt(StringView(tag), key, 0);
			(void) unit.GetKeyAsFloat(StringView(tag), key, 0.0f);
			(void) unit.GetKeyAsBool(StringView(tag), key, false);
		}
	}
	return 0;
}
