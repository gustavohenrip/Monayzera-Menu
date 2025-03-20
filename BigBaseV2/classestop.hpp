#pragma pack(push, 1)
#include <gta/node_list.hpp>
#include <nlohmann/json.hpp>
using JSONSerialiser = nlohmann::json;



class CNetShopTransaction
{
public:
	std::uint32_t m_id; //0x0000
	std::uint32_t m_variation; //0x0004
	std::uint32_t m_price; //0x0008
	std::uint32_t m_multiplier; //0x000C
	std::uint32_t m_value; //0x0010
}; //Size: 0x0014
static_assert(sizeof(CNetShopTransaction) == 0x14);

class CNetShopTransactionBasket
{
public:
	virtual ~CNetShopTransactionBasket() = default;

	std::uint32_t m_transaction_id; //0x0008
	char pad_000C[12]; //0x000C
	std::uint32_t m_category; //0x0018
	char pad_001C[8]; //0x001C
	std::uint32_t m_action; //0x0020
	std::uint32_t m_target; //0x0024
	char pad_0002C[180]; //0x0002C
	class CNetShopTransaction m_transactions[71]; //0x00E0
	std::uint32_t m_transaction_count; //0x066C
}; //Size: 0x0670
static_assert(sizeof(CNetShopTransactionBasket) == 0x670);
#pragma pack(pop)

class CNetworkShoppingMgr
{
public:
	virtual ~CNetworkShoppingMgr() = default;

	char pad_0008[24]; //0x0008
	rage::atDList<rage::atDNode<CNetShopTransactionBasket*>> m_transaction_nodes; //0x0020
	char pad_0030[9]; //0x0030
	bool m_is_busy1; //0x0039
	char pad_003A[14]; //0x003A
	bool m_is_busy2; //0x0048
	char pad_0049[7]; //0x0049
	bool m_is_busy3; //0x0050
	char pad_0051[79]; //0x0051
	void* m_inventory_items; //0x00A0
	char pad_00A8[24]; //0x00A8
	char m_gs_token[36]; //0x00C0
	char pad_00E4[28]; //0x00E4
	std::uint32_t m_transaction_noce_seed; //0x0100
	char pad_0104[44]; //0x0104
	std::uint32_t m_transaction_count; //0x0130
	char pad_0134[396]; //0x0134
	char* m_balance; //0x02C0

	std::uint32_t get_transaction_nonce() {
		return m_transaction_noce_seed + m_transaction_count;
	}
}; //Size: 0x02C8
static_assert(sizeof(CNetworkShoppingMgr) == 0x2C8);
class rlMetric
{
public:
	virtual ~rlMetric() = default; //Deconstructor
	virtual int metric_b() { return 0; }; //Returns a constant integer like 4, 5, 6
	virtual int metric_a() { return 0; }; //Returns a constant integer like 0
	virtual int unk_0018() { return 0; };
	virtual char const* get_name() { return ""; }; //Short name of the metric
	virtual bool to_json(JSONSerialiser* jsonStream) { return false; }; //Prints the metric out to a JSON stream
	virtual int get_size() { return 0; }; //Size in bytes of derived object (for copying)
	virtual std::uint32_t get_name_hash() { return 0; }; //Joaat of short name
public:
	bool using_a() {
		return metric_a() == 6;
	}
	bool using_b() {
		return metric_b() == 5;
	}
	bool using_c() {
		return !using_a() && !using_b();
	}
	bool crc_flag() {
		return !(*(std::int8_t*)(*(std::uint64_t*)__readgsqword(0x58) + 0xB4) & 1);
	}
};

class CHeaders
{
public:
	char m_header_data[465]; //0x0000
}; //Size: 0x01D1
static_assert(sizeof(CHeaders) == 0x1D1);

class CHTTPRequest
{
public:
	char pad_0000[112]; //0x0000
	rage::sysMemAllocator* m_allocator; //0x0070
	char pad_0078[16]; //0x0078
	CHeaders* m_http_headers; //0x0088
	char pad_0090[1144]; //0x0090
	char* m_protocol; //0x0508
	char* m_base_url; //0x0510
	char* m_endpoint_data; //0x0518
}; //Size: 0x0520
static_assert(sizeof(CHTTPRequest) == 0x520);
