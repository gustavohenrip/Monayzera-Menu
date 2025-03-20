#include "common.hpp"
#include "fiber_pool.hpp"
#include "gta/player.hpp"
#include "gta_util.hpp"
#include "gui.hpp"
#include "logger.hpp"
#include "memory/module.hpp"
#include "memory/pattern.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "renderer.hpp"
#include "script.hpp"
#include "script_global.hpp"
#include "memory_edit.hpp"
#include "script_local.hpp"
#include "fonts.hpp"

//#include "game_data.hpp"
#include <iostream>
#include <string>
#include <cstdint>
#include <sstream>
//#include "vehicle_models.cpp"
#include "gta/Weapons.h"

#include <imgui.h>
#include <iostream>
#include <Windows.h>
#include <thread>

namespace big
{
	void gui::dx_init()
	{
		ImGuiStyle* style = &ImGui::GetStyle();

		style->WindowTitleAlign = ImVec2(0.5f, 0.5f);
		style->WindowPadding = ImVec2(15, 15);
		style->WindowRounding = 5.0f;
		style->ChildRounding = 5.0f;
		style->PopupRounding = 5.0f;
		style->FramePadding = ImVec2(5, 5);
		style->FrameRounding = 4.0f;
		style->ItemSpacing = ImVec2(12, 8);
		style->ItemInnerSpacing = ImVec2(8, 6);
		style->IndentSpacing = 25.0f;
		style->ScrollbarSize = 15.0f;
		style->ScrollbarRounding = 9.0f;
		style->GrabMinSize = 5.0f;
		style->GrabRounding = 3.0f;

		style->Colors[ImGuiCol_Text] = ImVec4(0.00f, 0.50f, 0.00f, 0.70f);
		style->Colors[ImGuiCol_TextDisabled] = ImVec4(1.00f, 0.00f, 0.00f, 0.80f);
		style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_ChildBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.10f);
		style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
		style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_PopupBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_Separator] = ImVec4(0.56f, 0.56f, 0.58f, 0.20f);
		style->Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.24f, 0.23f, 0.29f, 0.20f);
		style->Colors[ImGuiCol_SeparatorActive] = ImVec4(0.56f, 0.56f, 0.58f, 0.20f);
		style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
		style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
		style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(1.00f, 0.60f, 0.00f, 0.43f);
		style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
	}

	void notification(const std::string& text)
	{
		HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
		HUD::THEFEED_SET_BACKGROUND_COLOR_FOR_NEXT_POST(184);
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(const_cast<char*>(text.c_str()));
		HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(false, false);
	}

	void notification_error(const std::string& text)
	{
		HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
		HUD::THEFEED_SET_BACKGROUND_COLOR_FOR_NEXT_POST(6);
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(const_cast<char*>(text.c_str()));
		HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(false, false);
	}

	int rp_value(int value) {
		return *script_global(GetXPValue + 1).at(value).as<int*>();
	}

	int character() {
		return *script_global(CurrentMPChar).as<int*>();
	}

	void change_session(int id) {
		*script_global(SessionUNK1).as<int*>() = 0;
		*script_global(SessionType).as<int*>() = id;
		*script_global(InitSession).at(2).as<int*>() = 0;
		*script_global(SessionSCTV).as<int*>() = 0;
		*script_global(InitSession).as<int*>() = 1;
		*script_global(SessionUNK2).as<int*>() = 0;
		*script_global(SessionUNK3).as<int*>() = -1;
	}

	bool is_context_active(char* text)
	{
		HUD::BEGIN_TEXT_COMMAND_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED(text);
		return HUD::END_TEXT_COMMAND_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED(0);
	}

	void Transaction(int address, int value) {
		*script_global(address).as<int*>() = value;
	}

	/*void Stealth(uint32_t hash, int amount) {
		Transaction(g_gui.TGC + 1, 2147483646);
		Transaction(g_gui.OVV + 7, 2147483647);
		Transaction(g_gui.LXK + 6, 0);
		Transaction(g_gui.UVE + 5, 0);
		Transaction(g_gui.KHE + 3, hash);
		Transaction(g_gui.TMW + 2, amount);
		Transaction(g_gui.TGC, g_gui.A);
	}*/

	//struct BasketTransaction {
	//	std::vector<std::pair<int, int>> transactions; // Pares de <endereço, valor>

	//	void add(int address, int value) {
	//		transactions.emplace_back(address, value); // Adiciona ao "basket"
	//	}

	//	void execute() {
	//		for (const auto& [address, value] : transactions) {
	//			*script_global(address).as<int*>() = value; // Aplica cada transação
	//		}
	//		transactions.clear(); // Limpa após execução
	//	}
	//};

	//void Stealth(uint32_t hash, int amount) {
	//	BasketTransaction basket;
	//	basket.add(g_gui.TGC + 1, 2147483646);
	//	basket.add(g_gui.OVV + 7, 2147483647);
	//	basket.add(g_gui.LXK + 6, 0);
	//	basket.add(g_gui.UVE + 5, 0);
	//	basket.add(g_gui.KHE + 3, hash);
	//	basket.add(g_gui.TMW + 2, amount);
	//	basket.add(g_gui.TGC, g_gui.A);

	//	basket.execute(); // Executa todas as transações
	//}


	struct BasketTransaction {
		// Usando um array fixo de transações para evitar overhead de alocação dinâmica
		std::pair<int, int> transactions[7];  // 7 transações fixas

		void add(int index, int address, int value) {
			transactions[index] = { address, value }; // Adiciona diretamente no índice
		}

		void execute() {
			for (int i = 0; i < 7; ++i) { // Sabemos que são 7 transações
				*script_global(transactions[i].first).as<int*>() = transactions[i].second; // Aplica cada transação
			}
		}
	};

	void Stealth(uint32_t hash, int amount) {
		BasketTransaction basket;

		// Preenche as transações com os valores desejados
		basket.add(0, g_gui.TGC + 1, 2147483646);
		basket.add(1, g_gui.OVV + 7, 2147483647);
		basket.add(2, g_gui.LXK + 6, 0);
		basket.add(3, g_gui.UVE + 5, 0);
		basket.add(4, g_gui.KHE + 3, hash);
		basket.add(5, g_gui.TMW + 2, amount);
		basket.add(6, g_gui.TGC, g_gui.A);

		basket.execute(); // Executa todas as transações
	}


	void TriggerTransaction(uint64_t hash) {
		if (NETSHOPPING::NET_GAMESERVER_BASKET_IS_ACTIVE()) {
			NETSHOPPING::NET_GAMESERVER_BASKET_END();
		}
		int id = 0;
		int value = -1135378931;
		int price = NETSHOPPING::NET_GAMESERVER_GET_PRICE(hash, 0x57DE404E, true);
		bool valid = NETSHOPPING::NET_GAMESERVER_BEGIN_SERVICE(&value, 0x57DE404E, hash, 0x562592BB, price, 2);
		if (valid) {
			NETSHOPPING::NET_GAMESERVER_CHECKOUT_START(id);
		}

	}















	void gui::dx_on_tick()
	{
		if (ImGui::Begin("Monayzera Menu", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse ))
		{

			if (ImGui::BeginMenu("Self Options")) {
				ImGui::Checkbox("GodMode", &g_gui.god);

				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Makes you invincible");

				ImGui::Separator();

				ImGui::Checkbox("Never Wanted", &g_gui.wanted);

				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Clear your wanted level everytime you got a star");

				ImGui::Separator();

				if (ImGui::Button("Get BST")) {
					*script_global(267505).at(3689).as<bool*>() = true;
					notification("Done!");
				}

				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Drop to you a BST");

				ImGui::EndMenu();
			};

				ImGui::Separator();

				if (ImGui::BeginMenu("Spawn Options")) {
					if (ImGui::BeginMenu("Spawn Vehicles")) {
						ImGui::SetNextItemWidth(75);
						ImGui::SameLine(50.0f, 50.0f);
						ImGui::InputText("Type the name of the vehicle", &g_gui.vehicle, 15);

						ImGui::Spacing();
						ImGui::Spacing();

						ImGui::SetNextItemWidth(75);
						if (ImGui::Button("Spawn!")) {
							notification("This option is not working.");
						}
						ImGui::EndMenu();
					}

					ImGui::EndMenu();
			}


				ImGui::Separator();


			if (ImGui::BeginMenu("Weapons Options")) {

				
				ImGui::Checkbox("Infinite Ammo", &g_gui.ammo);

				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Makes you dont lose ammo by shooting");

				if (ImGui::Button("Refill Ammo")) {
					for (WeaponHashes weapon : weaponHashes) {
						WEAPON::SET_PED_AMMO(PLAYER::PLAYER_PED_ID(), weapon, 9999, false);
					}
					notification("Now your weapons are filled up!");
				}

				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Must refill your current weapon ammo");

				ImGui::EndMenu();
			}


			ImGui::Separator();

			if (ImGui::BeginMenu("Recovery")) {


				ImGui::RadioButton("MP0 Char", &g_gui.numchar, 1);

				ImGui::SameLine();

				ImGui::RadioButton("MP1 Char", &g_gui.numchar, 2);

				ImGui::Spacing();
				ImGui::Spacing();




				if (g_gui.numchar == 1) {

					if (ImGui::Button("Apply all Tattos")) {
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_0"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_1"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_2"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_3"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_4"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_5"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_6"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_7"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_8"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_9"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_10"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_11"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_12"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_13"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_14"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_15"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_16"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_17"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_18"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_19"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_20"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_21"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_22"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_23"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_24"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_25"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_26"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_27"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_28"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_29"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_30"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_31"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_32"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_33"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_34"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_35"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_36"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_37"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_38"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_39"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_40"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_41"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_42"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_43"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_44"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_45"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_46"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_47"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_48"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_49"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_50"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_51"), -1, TRUE);
					}
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Must apply to your character every tattos in the game");

					ImGui::SameLine();

					if (ImGui::Button("Remove all Tattos")) {
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_0"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_1"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_2"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_3"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_4"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_5"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_6"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_7"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_8"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_9"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_10"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_11"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_12"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_13"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_14"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_15"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_16"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_17"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_18"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_19"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_20"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_21"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_22"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_23"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_24"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_25"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_26"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_27"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_28"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_29"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_30"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_31"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_32"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_33"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_34"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_35"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_36"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_37"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_38"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_39"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_40"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_41"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_42"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_43"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_44"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_45"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_46"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_47"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_48"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_49"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_50"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP0_TATTOO_FM_CURRENT_51"), 0, TRUE);
					}
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Must remove every single tattos to you character");



				}




				if (g_gui.numchar == 2) {

					if (ImGui::Button("Apply all Tattos")) {
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_0"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_1"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_2"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_3"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_4"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_5"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_6"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_7"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_8"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_9"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_10"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_11"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_12"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_13"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_14"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_15"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_16"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_17"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_18"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_19"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_20"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_21"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_22"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_23"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_24"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_25"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_26"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_27"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_28"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_29"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_30"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_31"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_32"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_33"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_34"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_35"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_36"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_37"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_38"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_39"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_40"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_41"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_42"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_43"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_44"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_45"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_46"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_47"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_48"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_49"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_50"), -1, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_51"), -1, TRUE);
					}
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Must apply to your character every tattos in the game");

					ImGui::SameLine();

					if (ImGui::Button("Remove all Tattos")) {
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_0"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_1"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_2"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_3"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_4"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_5"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_6"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_7"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_8"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_9"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_10"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_11"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_12"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_13"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_14"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_15"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_16"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_17"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_18"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_19"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_20"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_21"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_22"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_23"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_24"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_25"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_26"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_27"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_28"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_29"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_30"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_31"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_32"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_33"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_34"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_35"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_36"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_37"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_38"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_39"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_40"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_41"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_42"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_43"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_44"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_45"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_46"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_47"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_48"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_49"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_50"), 0, TRUE);
						STATS::STAT_SET_INT(RAGE_JOAAT("MP1_TATTOO_FM_CURRENT_51"), 0, TRUE);
					}
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Must remove every single tattos to you character");
				}

				ImGui::Spacing();
				
				ImGui::Separator();

				ImGui::Spacing();

				if (ImGui::Button("Max Mental State")) {
					if (g_gui.numchar == 1) {
						STATS::STAT_SET_FLOAT(RAGE_JOAAT("MP0_PLAYER_MENTAL_STATE"), 100, TRUE);
						STATS::STAT_SAVE(0, 0, 3, 0);
						notification("Mental State Maxed on Character 1!");
						
					}
					if (g_gui.numchar == 2) {
						STATS::STAT_SET_FLOAT(RAGE_JOAAT("MP1_PLAYER_MENTAL_STATE"), 100, TRUE);
						STATS::STAT_SAVE(0, 0, 3, 0);
						notification("Mental State Maxed on Character 2!");
					}

				}

				ImGui::SameLine();

				if (ImGui::Button("Min Mental State")) {
					if (g_gui.numchar == 1) {
						STATS::STAT_SET_FLOAT(RAGE_JOAAT("MP0_PLAYER_MENTAL_STATE"), 0, TRUE);
						STATS::STAT_SAVE(0, 0, 3, 0);
						notification("Mental State Minimized on Character 1!");

					}
					if (g_gui.numchar == 2) {
						STATS::STAT_SET_FLOAT(RAGE_JOAAT("MP1_PLAYER_MENTAL_STATE"), 0, TRUE);
						STATS::STAT_SAVE(0, 0, 3, 0);
						notification("Mental State Minimized on Character 2!");
					}

				}



				ImGui::EndMenu();
			}

			ImGui::Separator();


			if (ImGui::BeginMenu("Monay Options")) {

				if (ImGui::Button("Deposit Everything")) {
					int wallet = MONEY::NETWORK_GET_VC_WALLET_BALANCE(character());
					NETSHOPPING::NET_GAMESERVER_TRANSFER_WALLET_TO_BANK(character(), wallet);
				}

				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Will deposit every money you have into your wallet.");

				ImGui::SameLine();


				if (ImGui::Button("Withdraw Everything")) {
					int wallet = MONEY::NETWORK_GET_VC_BANK_BALANCE();
					NETSHOPPING::NET_GAMESERVER_TRANSFER_BANK_TO_WALLET(character(), wallet);
				}

				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Will withdraw every money you have into your wallet.");


				
				ImGui::Spacing();

				ImGui::Separator();

				if (ImGui::Checkbox("180K", &g_gui.monay180));

				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("This will automaticaly stop when you earn 200M");

				ImGui::Separator();

				if (ImGui::Checkbox("100K", &g_gui.monay100));

				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("A money loop that gives you 100K per second in your wallet.");
			
				ImGui::Separator();

				if (ImGui::Checkbox("15M", &g_gui.monay15));

				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Unlimited Money");

				ImGui::EndMenu();
			};

			ImGui::Separator();


			if (ImGui::BeginMenu("Misc Options")) {

				if (ImGui::BeginMenu("Weather Options")) {

					if (ImGui::Checkbox("Best Weather ( Freezed )", &g_gui.weather)) {
						notification("Done!");
					}

					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Freeze your weather to clear and the time to 1 PM");

					ImGui::Separator();

					if (ImGui::Button("1PM and Weather Clear")) {

						MISC::SET_OVERRIDE_WEATHER("CLEAR");
						CLOCK::SET_CLOCK_TIME(12, 10, 10);

					}

					ImGui::EndMenu();
				}
			

				ImGui::Separator();

				if (ImGui::Button("Skip Actual Cutscene")) {
					g_fiber_pool->queue_job([]
						{
							CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
						});
				}

				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Some cutscenes can't be skipped (MC/Office cutscenes).");

				ImGui::Separator();

				if (ImGui::Button("Go back to Story Mode")) {
					g_fiber_pool->queue_job([] {
						NETWORK::NETWORK_BAIL(49, 0, 0);
						notification("Done!");
					});
				}

				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Use this option to go back to Story Mode");

				ImGui::Separator();

				if (ImGui::Button("Close Game"))
				{
					exit(0);
				}

				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Close your game.");

				ImGui::Separator();

				if (ImGui::Button("Unload Menu"))
				{
					g_running = false;
					notification("Mod Unloaded.");
				}

				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Unloads the menu, you can also inject again later.");

				ImGui::EndMenu();

			}
		}
		ImGui::End();
	}

	void gui::script_init()
	{
	}

	void gui::delayed_loops()
	{
	}

	void gui::script_on_tick()
	{
		if (g_gui.m_opened)
		{			
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
		}

		if (g_gui.god) {
			g_fiber_pool->queue_job([]
				{
					if (g_gui.god == true) {
						ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), true);
					}
					else {
						ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), false);
					}
				});
		}

		if (g_gui.weather) {
			g_fiber_pool->queue_job([]
				{
					if (g_gui.weather == true) {
						MISC::SET_OVERRIDE_WEATHER("CLEAR");
						CLOCK::SET_CLOCK_TIME(12, 10, 10);
					}

					else {
						return;
					}
				});
		}

	/*----------------------------------------------------------------------------*/
		if (g_gui.monay100) {
			//g_fiber_pool->queue_job([] {
			///*static int p = 0;
			//if (p < 100000000) {*/
			//	Stealth(0x68341DC5, 100000);
			//	STATS::STAT_SAVE(0, 0, 3, 0);
			//	/*p += 100000;
			//}*/
			//});
			
				static int id = 0;
				if (id <= 1999) {
					Stealth(0x68341DC5, 100000);
					STATS::STAT_SAVE(0, 0, 3, 0);
					script::get_current()->yield(1000ms);
					id += 1;
					LOG(INFO) << id;
				}

		}

		if (g_gui.monay6) {
			g_fiber_pool->queue_job([] {




			});
		}




		if (g_gui.monay15) {
			g_fiber_pool->queue_job([] {
				Stealth(0xA174F633, 15000000);
				STATS::STAT_SAVE(0, 0, 3, 0);
				script::get_current()->yield(350000ms);
			});
		}


		if (g_gui.monay180) {
			static int id = 0;
			if (id <= 1100) {
				TriggerTransaction(0x615762F1);
				STATS::STAT_SAVE(0, 0, 3, 0);
				script::get_current()->yield(1000ms);
				id += 1;
				LOG(INFO) << id;
			}
		}





















		/*----------------------------------------------------------------------------*/



		if (g_gui.wanted) {
			g_fiber_pool->queue_job([] 
			{
					if (g_gui.wanted == true) {
						if (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) > 0)
							PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID());
					}
					else {
						return;
					}


			});
		}


		if (g_gui.ammo) {
			g_fiber_pool->queue_job([]
				{
					if (g_gui.ammo == true) {
							WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), true);
							for (WeaponHashes weapon : weaponHashes) {
								WEAPON::SET_PED_AMMO(PLAYER::PLAYER_PED_ID(), weapon, 9999, false);
							}
					}
					else {
							WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), false);
					}
				});
		}

		if (g_gui.anti_afk) {
			g_fiber_pool->queue_job([]
				{
					*script_global(Tunables).at(87).as<int*>() = INT_MAX;
					*script_global(Tunables).at(88).as<int*>() = INT_MAX;
					*script_global(Tunables).at(89).as<int*>() = INT_MAX;
					*script_global(Tunables).at(90).as<int*>() = INT_MAX;
					*script_global(Tunables).at(7785).as<int*>() = INT_MAX;
					*script_global(Tunables).at(7786).as<int*>() = INT_MAX;
					*script_global(Tunables).at(7787).as<int*>() = INT_MAX;
					*script_global(Tunables).at(7788).as<int*>() = INT_MAX;
					*script_global(IdleTimer).at(IdleTimer_Offset_1).as<int*>() = 0;
					*script_global(IdleTimer).at(IdleTimer_Offset_2).as<int*>() = 0;
					*script_global(IdleTimerUNK1).as<int*>() = 0;
					*script_global(IdleTimerUNK2).as<int*>() = 0;
				});
		}
		if (g_gui.rp_loop) {
			g_fiber_pool->queue_job([]
				{
					if (!HUD::IS_PAUSE_MENU_ACTIVE() && NETWORK::NETWORK_IS_SESSION_ACTIVE()) {
						Memory::set_value<int>({ 0x08, 0x10C8, 0x888 }, 1);
						script::get_current()->yield();
						Memory::set_value<int>({ 0x08, 0x10C8, 0x888 }, 0);
						script::get_current()->yield();
						*script_global(Tunables).at(1).as<float*>() = 500;
						STATS::STAT_SAVE(0, 0, 3, 0);
					}
				});
		}
		if (g_gui.always_jackpot) {
			g_fiber_pool->queue_job([] {

				// Basically, Always win the slots, not worth mentioning it.

				gta_util::execute_as_script(RAGE_JOAAT("CASINO_SLOTS"), [] {
					auto slots_thread = gta_util::find_script_thread(RAGE_JOAAT("CASINO_SLOTS"));
					for (int i = 1; i <= 195; i++) {
						auto local1354 = script_local(slots_thread, 1354).at(1);
						int break_value = *local1354.at(i).as<int*>();
						if (break_value != 64) {
							*local1354.at(i).as<int*>() = 6;
						}
					}
					});
				});
		}
		if (g_gui.always_jackpot_2) {
			g_fiber_pool->queue_job([] {

				// Variant #2 - This variant is a good alternative if you don't want to change the entire "Probability Table" that you can find inside the scripts.
				// How it works? The first three (local_2097.f_1, 2, 3) are related with the slots you can find in the machine.
				// The "63" value is basically the 63th position of the "Probability Table", the 63th position (or is it 64th?) will give you the "6", 6 = Best prize, Jackpot.
				// You ask, what's this probability table? That's the probability table -> https://imgur.com/a/rBidKj9
				// But, there's a "downside", if you only change the first three values, the slots icons will tell that you lost but in reality, you won but don't get fooled.
				// You will probably think "this way it will be more safer, correct?", no, incorrect. Let's not forget we're messing with locals, in this case, they're just icons.
				// Rockstar knows you're winning and it's being sent to the server.
				// So, the last three values (1082130432) are basically the "Jackpot" icons, you're not obliged to use the last three, it's just to make it look 'cool'.
				// You NEED to run this in a LOOP, always. The good part is, you don't need to leave the casino if you want to disable the Jackpot option.

				gta_util::execute_as_script(RAGE_JOAAT("CASINO_SLOTS"), [] {
					auto slots_thread = gta_util::find_script_thread(RAGE_JOAAT("CASINO_SLOTS"));
					*script_local(slots_thread, 2097).at(1).as<unsigned int*>() = 63;
					*script_local(slots_thread, 2097).at(2).as<unsigned int*>() = 63;
					*script_local(slots_thread, 2097).at(3).as<unsigned int*>() = 63;
					//////////////////////////////////////////////////////////////////
					*script_local(slots_thread, 2097).at(5).as<unsigned int*>() = 1082130432;
					*script_local(slots_thread, 2097).at(6).as<unsigned int*>() = 1082130432;
					*script_local(slots_thread, 2097).at(7).as<unsigned int*>() = 1082130432;
				});
			});
		}
		if (g_gui.bet_multiplier) {
			g_fiber_pool->queue_job([] {

				// Change all the bet multipliers to 1000x so even if you get the worst prize from the slots, you'll earn the same value as you would get with a jackpot!

				gta_util::execute_as_script(RAGE_JOAAT("CASINO_SLOTS"), [] {
					auto slots_thread = gta_util::find_script_thread(RAGE_JOAAT("CASINO_SLOTS"));
					for (int i = 1; i <= 10; i++) {
						auto local1354 = script_local(slots_thread, 1354).at(278);
						*local1354.at(i).as<int*>() = 1000;
					}
				});
			});
		}
		if (g_gui.slots_bet) {
			g_fiber_pool->queue_job([]
				{

					// Always Win 2,500,00 in ANY MACHINE, no need to use Deity or Diamond anymore.
					// Explaining a bit more about the code, the value 500 means the minimum bet
					// the 5 is the multiplier, let me explain better, when you sit in a machine, you have two options, SPACE to increase bet the and TAB to change to the max BET, the local_2134 is responsible for that.

					gta_util::execute_as_script(RAGE_JOAAT("CASINO_SLOTS"), [] {
						auto slots_thread = gta_util::find_script_thread(RAGE_JOAAT("CASINO_SLOTS"));
						auto local_219 = script_local(slots_thread, 219);
						auto local_2131 = script_local(slots_thread, 2131).as<int*>();

						*local_219.at(*local_2131, 21).at(16).as<int*>() = 500;
						*script_local(slots_thread, 2134).as<int*>() = 5;
					});
				});
		}
		if (g_gui.increase_chips_limit) {
			g_fiber_pool->queue_job([] {

				// Used to increase the chips limit, from 2B to 2.1B, not that useful but feel free to give a shot.

				*script_global(262145).at(26469).as<int*>() = INT_MAX;
			});
		}
		if (g_gui.cas_cooldown_bypass) {
			g_fiber_pool->queue_job([] {

				// Variant #1: The most popular and maybe detected (?) variant, i prefer this one, it's straight and... less buggy, but, if you're scared of using it, use the other variants.

				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CASINO_CHIPS_WON_GD"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CASINO_CHIPS_WONTIM"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CASINO_CHIPS_PUR_GD"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CASINO_CHIPS_PURTIM"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CASINO_MEM_BONUS"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_GMBLNG_0"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_GMBLNG_1"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_GMBLNG_2"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_GMBLNG_3"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_GMBLNG_4"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_GMBLNG_5"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_GMBLNG_6"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_GMBLNG_7"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_GMBLNG_8"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_GMBLNG_9"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_PLYING_0"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_PLYING_1"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_PLYING_2"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_PLYING_3"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_PLYING_4"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_PLYING_5"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_PLYING_6"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_PLYING_7"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_PLYING_8"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_PLYING_9"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CASINO_BAN_TIME"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CASINO_GMBLNG_GD"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_CUR_GMBLNG_GD"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_CUR_GMBLNG_PX"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_L24_PX"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_L24"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_TRHSLD"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_L24_1"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_L24_2"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_L24_3"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_L24_4"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_L24_5"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_L24_6"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_L24_7"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_L24_8"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_CUR_GMBLNG_HR"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_24H_GMBLNG_PX"), 0, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CHIPS_COL_TIME"), 0, TRUE);
				});
		}
		if (g_gui.cas_cooldown_bypass_2) {

			// Variant #2: this variant is interesting, i like it because that's the most simple way to bypass the cooldown, how it works? it's simple, the original value is 2880.
			// 2880 SECONDS = 48 MINUTES IRL, so, these tuneables are used as a timer to reset the WON_GD and PUR_GD stats, yes, that's exactly how it works, set them to 0 or -1 (way better and faster?)
			// then, after changing the value, you don't need to do anything, just sit and rest, the game will reset them for you!
			// but, there's a catch, if you're the type of player that like to abuse from methods, be careful, sometimes, you'll get "banned" from casino, and the only way to get "unbanned" is to use the above variant, the #1.

			*script_global(262145).at(26470).as<int*>() = 0;
			*script_global(262145).at(26471).as<int*>() = 0;
		}
		if (g_gui.cas_cooldown_bypass_3) {

			// Variant #3: this variant is... simple and i wouldn't recommend it, the default value is 5,000,000, so, how it works? well, let's say, normally you can only earn up to 5M max and then
			// you need to wait 48 minutes to play again (yes, those 2880 above will help with that), anyway, you need to set to a higher value, maybe INT_MAX or any value you want.
			// you're the boss, you decide the value, it can be useful to be used as a 'limit' if you want to prevent people from abusing it, it's really useful.
			// the downside is, let's say you set this tuneable to 2,000,000,000 and you earned 2B of chips, you'll need to wait the cooldown, so, you can use the above variant with this, up to you.

			*script_global(262145).at(26473).as<int*>() = INT_MAX;

		}
		if (g_gui.stop_anim) {
			g_fiber_pool->queue_job([] {

				// This will try to stop the character animation while playing the slot machine, it works but it can be buggy sometimes, try it.

				gta_util::execute_as_script(RAGE_JOAAT("CASINO_SLOTS"), [] {
					auto slots_thread = gta_util::find_script_thread(RAGE_JOAAT("CASINO_SLOTS"));
					*script_local(slots_thread, 1648).as<int*>() = 4;
					});
			});
		}
		if (g_gui.force_trans) {
			g_fiber_pool->queue_job([] {

				// My favorite way to earn fast chips! Run this code in a loop (fastest loop you got) then enable with Jackpot then see the magic.
				// But, there's a big problem with it, i would recommend before using it, please mute the game or... disable the slots sounds because it will get loud, really loud.

				gta_util::execute_as_script(RAGE_JOAAT("CASINO_SLOTS"), [] {
					auto slots_thread = gta_util::find_script_thread(RAGE_JOAAT("CASINO_SLOTS"));
					*script_local(slots_thread, 1644).as<int*>() = 50341673;
					});
			});
		}
		if (g_gui.fast_spin) {
			g_fiber_pool->queue_job([] {

				// You already know about it or you probably already seen it somewhere so i won't give much details about it.

				gta_util::execute_as_script(RAGE_JOAAT("CASINO_SLOTS"), [] {
					auto slots_thread = gta_util::find_script_thread(RAGE_JOAAT("CASINO_SLOTS"));
					auto local_3407 = script_local(slots_thread, 3407).at(PLAYER::PLAYER_ID(), 11).at(10).as<int*>();
					if (*local_3407 == 3) {
						*script_local(slots_thread, 3407).at(PLAYER::PLAYER_ID(), 11).at(10).as<int*>() = 6;
					}
					});
			});
		}
		if (g_gui.auto_play) {
			g_fiber_pool->queue_job([] {

				// Basically, it will Auto-Play the slot machine.

				gta_util::execute_as_script(RAGE_JOAAT("CASINO_SLOTS"), [] {
					auto slots_thread = gta_util::find_script_thread(RAGE_JOAAT("CASINO_SLOTS"));
					auto local_1644 = script_local(slots_thread, 1644).as<int*>();
					auto local_3407 = script_local(slots_thread, 3407).at(PLAYER::PLAYER_ID(), 11).at(10).as<int*>();
					if (*local_3407 == 0) {
						*script_local(slots_thread, 1644).as<int*>() = 8;
					}
					});
			});
		}
		if (g_gui.auto_play_blackjack) {
			g_fiber_pool->queue_job([] {

				// A very "complex" code to Auto-Play blackjack, quick note, use it with Anti-AFK.

				gta_util::execute_as_script(RAGE_JOAAT("BLACKJACK"), [] {
					auto blackjack_thread = gta_util::find_script_thread(RAGE_JOAAT("BLACKJACK"));
					auto current_table = script_local(blackjack_thread, 1782).at(PLAYER::PLAYER_ID(), 8).at(4).as<int*>();
					auto all_buttons_ready = script_local(blackjack_thread, 2039).at(874).at(693).as<int*>();

					if (is_context_active("BJACK_BET") && *all_buttons_ready == 5) {
						*script_local(blackjack_thread, 1782).at(PLAYER::PLAYER_ID(), 8).as<int*>() = 36864;
					}
					});
			});
		}
		if (g_gui.rig_blackjack) {
			g_fiber_pool->queue_job([] {

				// A basic rig blackjack code but, you won't need to spend any of your chips because it will make the bet FREE and you'll always win 2,500,000 chips, always.

				gta_util::execute_as_script(RAGE_JOAAT("BLACKJACK"), [] {
					auto blackjack_thread = gta_util::find_script_thread(RAGE_JOAAT("BLACKJACK"));
					auto current_table = script_local(blackjack_thread, 1782).at(PLAYER::PLAYER_ID(), 8).at(4).as<int*>();
					auto cur_card = script_local(blackjack_thread, 122).at(1).at(*current_table, 211);

					if (*current_table != -1) {
						*cur_card.at(1).as<int*>() = 1;
						*script_local(blackjack_thread, 2042).as<int*>() = 1;
						*cur_card.at(2).as<int*>() = 0;
						*script_local(blackjack_thread, 2043).as<int*>() = 0;
						*cur_card.at(3).as<int*>() = 23;
						*script_local(blackjack_thread, 2044).as<int*>() = 23;
						*cur_card.at(4).as<int*>() = 0;
						*script_local(blackjack_thread, 2045).as<int*>() = 0;
						*script_local(blackjack_thread, 2039).at(244).as<int*>() = 0;
						*script_local(blackjack_thread, 2039).at(246).as<int*>() = 0;
						*script_local(blackjack_thread, 3626).at(14).as<int*>() = 2500000;
						*script_local(blackjack_thread, 122).at(1580).at(1).as<int*>() = 0;
					}
					});
			});
		}
		if (g_gui.bypass_cooldown_err) {
			g_fiber_pool->queue_job([] {

				// A Basic message bypass, not worth mentioning it.

				int message_id = *script_global(MessageID_1).as<int*>();

				if (message_id == 20 || message_id == 4) {
					*script_global(MessageID_2).as<int*>() = 0;
				}
			});
		}
	}

	void gui::script_func()
	{
		g_gui.script_init();
		while (true)
		{
			g_gui.increase_chips_limit = true;
			g_gui.cas_cooldown_bypass = true;
			g_gui.bypass_cooldown_err = true;
			g_gui.script_on_tick();
			script::get_current()->yield();
		}
	}

	void gui::delayed_func()
	{
		g_gui.script_init();
		while (true)
		{
			g_gui.delayed_loops();
			script::get_current()->yield(6000ms);
		}
	}
}
