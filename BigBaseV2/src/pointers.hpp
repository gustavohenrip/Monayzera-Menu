#pragma once
#include "common.hpp"
#include "gta/fwddec.hpp"
#include "gta/enums.hpp"
#include "function_types.hpp"
#include "gta/player.hpp"
#include "gta/classestop.hpp"

namespace big
{
	class pointers
	{
	public:
		explicit pointers();
		~pointers();
	public:
		HWND m_hwnd{};

		eGameState* m_game_state{};
		bool* m_is_session_started{};

		CPedFactory** m_ped_factory{};
		CNetworkPlayerMgr** m_network_player_mgr{};

		rage::scrNativeRegistrationTable* m_native_registration_table{};
		functions::get_native_handler_t m_get_native_handler{};
		functions::fix_vectors_t m_fix_vectors{};

		rage::atArray<GtaThread*>* m_script_threads{};
		rage::scrProgramTable* m_script_program_table{};
		functions::run_script_threads_t m_run_script_threads{};
		std::int64_t** m_script_globals{};
		class::CNetworkShoppingMgr** m_network_shopping_mgr{};
		functions::construct_basket_t* m_construct_basket{};
		functions::add_item_to_basket_t* m_add_item_to_basket{};
		functions::begin_service_t* m_begin_service{};

		std::uint64_t m_worldptr{};

		CGameScriptHandlerMgr **m_script_handler_mgr{};

		IDXGISwapChain **m_swapchain{};
	};

	inline pointers *g_pointers{};
}
