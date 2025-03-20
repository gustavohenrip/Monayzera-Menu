#pragma once
#include "common.hpp"
#include "gta/fwddec.hpp"
#include "gta/natives.hpp"

namespace big::functions
{
	using run_script_threads_t = bool(*)(std::uint32_t ops_to_execute);
	using get_native_handler_t = rage::scrNativeHandler(*)(rage::scrNativeRegistrationTable*, rage::scrNativeHash);
	using fix_vectors_t = void(*)(rage::scrNativeCallContext*);
	using construct_basket_t = bool(CNetworkShoppingMgr* netshop_mgr, std::int32_t* id, std::uint32_t category, std::uint32_t action, std::uint32_t flags);
	using add_item_to_basket_t = bool(CNetworkShoppingMgr* netshop_mgr, std::int32_t* items);
	using begin_service_t = bool(CNetworkShoppingMgr* netshop_mgr, std::int32_t* id, std::uint32_t service_type, std::uint32_t category, std::uint32_t item, std::uint32_t action, std::int32_t value, std::uint32_t flags);
}
