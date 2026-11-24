// libFuzzer harness: GemRB 2DA table parser (plain and XOR-encrypted), plus every query.
#include "fuzz_common.h"
#include "plugins/2DAImporter/2DAImporter.h"

using namespace GemRB;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
	p2DAImporter unit;
	if (!unit.Open(std::unique_ptr<DataStream>(FuzzStream("fuzz.2da", data, size)))) return 0;

	const auto rows = unit.GetRowCount();
	const auto cols = unit.GetColNamesCount();
	(void) unit.QueryDefault();
	for (TableMgr::index_t c = 0; c < cols; ++c) {
		const std::string& name = unit.GetColumnName(c);
		(void) unit.GetColumnIndex(name);
	}
	for (TableMgr::index_t r = 0; r < rows; ++r) {
		const std::string& rname = unit.GetRowName(r);
		(void) unit.GetRowIndex(rname);
		const auto n = unit.GetColumnCount(r);
		for (TableMgr::index_t c = 0; c < n; ++c) {
			const std::string& f = unit.QueryField(r, c);
			(void) unit.FindTableValue(c, f, 0);
			(void) unit.FindTableValue(c, strtol(f.c_str(), nullptr, 0), 0);
		}
	}
	return 0;
}
