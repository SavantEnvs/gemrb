// libFuzzer harness: GemRB IDS symbol-table parser (plain and encrypted), plus lookups.
#include "fuzz_common.h"
#include "plugins/IDSImporter/IDSImporter.h"

using namespace GemRB;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
	IDSImporter unit;
	if (!unit.Open(std::unique_ptr<DataStream>(FuzzStream("fuzz.ids", data, size)))) return 0;

	const size_t n = unit.GetSize();
	(void) unit.GetHighestValue();
	for (size_t i = 0; i < n; ++i) {
		const std::string& s = unit.GetStringIndex(i);
		const int v = unit.GetValueIndex(i);
		(void) unit.GetValue(StringView(s));
		(void) unit.GetValue(v);
		(void) unit.FindString(StringView(s));
		(void) unit.FindValue(v);
	}
	return 0;
}
