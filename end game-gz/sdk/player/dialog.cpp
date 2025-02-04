#include <inc.h>
bool sdk::dialog::c_dialog::disable_all()
{
	auto uimgr = *(uint64_t*)(core::offsets::cl::ui_manager);
	if (!uimgr) return false;
	auto p_s = *(uint64_t*)(uimgr + 0x3c0);
	auto p_e = *(uint64_t*)(uimgr + 0x3c8);
	if (!p_s || !p_e) return false;
	auto delta = ((p_e - p_s) / 8);
	for (auto a = 0; a < delta * 8; a += 8)
	{
		auto panel = *(uint64_t*)(p_s + a);
		if (!panel) continue;
		auto panel_state = *(BYTE*)(panel + 0x239);
		if (panel_state == 0xC) continue;
		auto panel_name = sdk::player::player_->gstring(panel + 0xD0, 64);
		if (panel_name.empty()) continue;
		*(BYTE*)(panel + 0x239) = 0xC;
		this->disabled_panels.push_back(panel);
	}
	return 1;
}
bool sdk::dialog::c_dialog::enable_all()
{
	for (auto a : this->disabled_panels) *(BYTE*)(a + 0x239) = 0x8;
	this->disabled_panels.clear();
	return 1;
}
bool sdk::dialog::c_dialog::gbuttons()
{
	this->buttons_map.clear();
	auto act = *(uint64_t*)(core::offsets::cl::dialog_base + 0x30);
	if (!act) return false;
	auto p_s = *(uint64_t*)(core::offsets::cl::dialog_base + 0x70);
	auto p_e = *(uint64_t*)(core::offsets::cl::dialog_base + 0x78);
	if (!p_s || !p_e) return false;
	auto delta = ((p_e - p_s) / 0x68);
	for (auto a = 0; a < delta; a++)
	{
		auto btn = getdialog(core::offsets::cl::dialog_base, a);
		if (!btn) continue;
		auto txt = gettext(btn);
		this->buttons_map[a] = txt;
	}
	if (this->buttons_map.size()) return true;
	else return false;
}
bool sdk::dialog::c_dialog::gpanels()
{
	this->panels_map.clear();
	auto uimgr = *(uint64_t*)(core::offsets::cl::ui_manager);
	if (!uimgr) return false;
	auto p_s = *(uint64_t*)(uimgr + 0x3c0);
	auto p_e = *(uint64_t*)(uimgr + 0x3c8);
	if (!p_s || !p_e) return false;
	auto delta = ((p_e - p_s) / 8);
	for (auto a = 0; a < delta * 8; a += 8)
	{
		auto panel = *(uint64_t*)(p_s + a);
		if (!panel) continue;
		auto panel_state = *(BYTE*)(panel + 0x239);
		if (panel_state == 0xC) continue;
		auto panel_name = sdk::player::player_->gstring(panel + 0xD0, 64);
		if (panel_name.empty()) continue;
		if (!strstr(panel_name.c_str(), "Panel"))
		{
			panel_name.clear();
			auto start_asptr = *(uint64_t*)(panel + 0xD0);
			if (!start_asptr) continue;
			for (auto c = start_asptr; c < start_asptr + 64; c++)
			{
				char read = *(char*)(c);
				if (read == '\0' || read == '?') break;
				panel_name.push_back(read);
			}
		}
		this->panels_map[panel_name] = 1;
	}
	if (this->panels_map.size()) return true;
	else return false;
}
bool sdk::dialog::c_dialog::gchildren(std::string t)
{
	this->children_by_panel.clear();
	auto uimgr = *(uint64_t*)(core::offsets::cl::ui_manager);
	if (!uimgr) return false;
	auto p_s = *(uint64_t*)(uimgr + 0x3c0);
	auto p_e = *(uint64_t*)(uimgr + 0x3c8);
	if (!p_s || !p_e) return false;
	auto delta = ((p_e - p_s) / 8);
	for (auto a = 0; a < delta * 8; a += 8)
	{
		auto panel = *(uint64_t*)(p_s + a);
		if (!panel) continue;
		auto panel_state = *(BYTE*)(panel + 0x239);
		if (panel_state == 0xC) continue;
		auto panel_name = sdk::player::player_->gstring(panel + 0xD0, 64);
		if (panel_name.empty()) continue;
		if (!strstr(panel_name.c_str(), t.c_str())) continue;
		auto c_s = *(uint64_t*)(panel + 0xF0);
		auto c_e = *(uint64_t*)(panel + 0xF8);
		if (!c_s || !c_e) continue;
		auto c_delta = ((c_e - c_s) / 8);
		if (!c_delta) continue;
		for (auto b = 0; b < c_delta * 8; b += 8)
		{
			auto child = *(uint64_t*)(c_s + b);
			if (!child) continue;
			auto child_state = *(BYTE*)(child + 0x239);
			if (child_state == 0xC) continue;
			auto child_name = sdk::player::player_->gstring(child + 0xD0, 64);
			if (child_name.empty()) continue;
			auto has_txt = *(BYTE*)(child + 0x298);
			if (has_txt)
			{
				if (!has_txt || !*(uint64_t*)(child + 0x298)) continue;
				auto txt = *(sdk::dialog::str_btn*)(*(uint64_t*)(child + 0x298));
				if (!txt.str_btn_) continue;
				auto s = std::wstring(txt.str_btn_); if (!s.size()) continue;
				auto e = std::string(s.begin(), s.end()); if (!e.size() || e.size() < 3) continue;
				this->children_by_panel[e] = child_name;
			}
			this->children_by_panel[child_name] = "=>";
			//+0x120 -> +0x98 = lua for buttons
		}
	}
	return true;
}
std::string sdk::dialog::c_dialog::find_button(std::string display_name, std::string t)
{
	auto uimgr = *(uint64_t*)(core::offsets::cl::ui_manager);
	if (!uimgr) return "";
	auto p_s = *(uint64_t*)(uimgr + 0x3c0);
	auto p_e = *(uint64_t*)(uimgr + 0x3c8);
	if (!p_s || !p_e) return "";
	auto delta = ((p_e - p_s) / 8);
	for (auto a = 0; a < delta * 8; a += 8)
	{
		auto panel = *(uint64_t*)(p_s + a);
		if (!panel) continue;
		auto panel_state = *(BYTE*)(panel + 0x239);
		if (panel_state == 0xC) continue;
		auto panel_name = sdk::player::player_->gstring(panel + 0xD0, 64);
		if (panel_name.empty()) continue;
		if (!strstr(panel_name.c_str(), "Panel"))
		{
			panel_name.clear();
			auto start_asptr = *(uint64_t*)(panel + 0xD0);
			if (!start_asptr) continue;
			for (auto c = start_asptr; c < start_asptr + 64; c++)
			{
				char read = *(char*)(c);
				if (read == '\0' || read == '?') break;
				panel_name.push_back(read);
			}
		}
		if (!strstr(panel_name.c_str(), t.c_str())) continue;
		auto c_s = *(uint64_t*)(panel + 0xF0);
		auto c_e = *(uint64_t*)(panel + 0xF8);
		if (!c_s || !c_e) continue;
		auto c_delta = ((c_e - c_s) / 8);
		if (!c_delta) continue;
		for (auto b = 0; b < c_delta * 8; b += 8)
		{
			auto child = *(uint64_t*)(c_s + b);
			if (!child) continue;
			auto child_name = sdk::player::player_->gstring(child + 0xD0, 64);
			if (child_name.empty()) continue;
			auto has_txt = *(BYTE*)(child + 0x298);
			if (!has_txt || !*(uint64_t*)(child + 0x298)) continue;
			auto txt = *(sdk::dialog::str_btn*)(*(uint64_t*)(child + 0x298));
			if (!txt.str_btn_) continue;
			auto s = std::wstring(txt.str_btn_); if (!s.size()) continue;
			auto e = std::string(s.begin(), s.end()); if (!e.size() || e.size() < 3) continue;
			//sdk::util::log->a("panel: %s button: %s > %s", panel_name.c_str(), child_name.c_str(), e.c_str());
			if (!strstr(e.c_str(), display_name.c_str())) continue;
			auto idx = std::string(); idx.push_back(child_name.back());
			return idx;
		}
	}
	return "";
}
int sdk::dialog::c_dialog::find_button_ex(std::string display_name, std::string t)
{
	auto uimgr = *(uint64_t*)(core::offsets::cl::ui_manager);
	if (!uimgr) return -1;
	auto p_s = *(uint64_t*)(uimgr + 0x3c0);
	auto p_e = *(uint64_t*)(uimgr + 0x3c8);
	if (!p_s || !p_e) return -1;
	auto delta = ((p_e - p_s) / 8);
	for (auto a = 0; a < delta * 8; a += 8)
	{
		auto panel = *(uint64_t*)(p_s + a);
		if (!panel) continue;
		auto panel_state = *(BYTE*)(panel + 0x239);
		if (panel_state == 0xC) continue;
		auto panel_name = sdk::player::player_->gstring(panel + 0xD0, 64);
		if (panel_name.empty()) continue;
		if (!strstr(panel_name.c_str(), t.c_str())) continue;
		auto c_s = *(uint64_t*)(panel + 0xF0);
		auto c_e = *(uint64_t*)(panel + 0xF8);
		if (!c_s || !c_e) continue;
		auto c_delta = ((c_e - c_s) / 8);
		if (!c_delta) continue;
		for (auto b = 0; b < c_delta * 8; b += 8)
		{
			auto child = *(uint64_t*)(c_s + b);
			if (!child) continue;
			auto child_name = sdk::player::player_->gstring(child + 0xD0, 64);
			if (child_name.empty()) continue;

			if (!strstr(child_name.c_str(), "Radio")) continue;
			if (!strstr(child_name.c_str(), "_Func_")) continue;

			auto vt = this->icon_idents[display_name];

			auto _x6C = *(int*)(child + 0x6C);
			auto _x70 = *(int*)(child + 0x70);
			auto _x74 = *(int*)(child + 0x74);
			auto _x78 = *(int*)(child + 0x78);
			auto _x80 = *(int*)(child + 0x80);
			auto _x84 = *(int*)(child + 0x84);
			auto _x88 = *(int*)(child + 0x88);
			auto _x8C = *(int*)(child + 0x8C);

			/*sdk::util::log->b("%s", child_name.c_str());
			sdk::util::log->b("0x%04x", _x6C);
			sdk::util::log->b("0x%04x", _x70);
			sdk::util::log->b("0x%04x", _x74);
			sdk::util::log->b("0x%04x", _x78);
			sdk::util::log->b("0x%04x", _x80);
			sdk::util::log->b("0x%04x", _x84);
			sdk::util::log->b("0x%04x", _x88);
			sdk::util::log->b("0x%04x", _x8C);
			sdk::util::log->b(" --- ");*/

			if (vt[0x6C] == _x6C &&
				vt[0x70] == _x70 &&
				vt[0x74] == _x74 &&
				vt[0x78] == _x78 &&
				vt[0x80] == _x80 &&
				vt[0x84] == _x84 &&
				vt[0x88] == _x88 &&
				vt[0x8C] == _x8C)
			{
				sdk::util::log->b("match for %s -> %s", display_name.c_str(), child_name.c_str());
				auto idx = std::string(); idx.push_back(child_name.back());
				return std::stoi(idx);
			}
		}
	}
	return -1;
}
bool sdk::dialog::c_dialog::find_panel(std::string panel)
{
	this->gpanels();
	for (auto a : this->panels_map) if (strstr(a.first.c_str(), panel.c_str())) return true;
	return false;
}
void sdk::dialog::c_dialog::disable_by_name(std::string fef)
{
	auto uimgr = *(uint64_t*)(core::offsets::cl::ui_manager);
	if (!uimgr) return;
	auto p_s = *(uint64_t*)(uimgr + 0x3c0);
	auto p_e = *(uint64_t*)(uimgr + 0x3c8);
	if (!p_s || !p_e) return;
	auto delta = ((p_e - p_s) / 8);
	for (auto a = 0; a < delta * 8; a += 8)
	{
		auto panel = *(uint64_t*)(p_s + a);
		if (!panel) continue;
		auto panel_state = *(BYTE*)(panel + 0x239);
		if (panel_state == 0xC) continue;
		auto panel_name = sdk::player::player_->gstring(panel + 0xD0, 64);
		if (panel_name.empty()) continue;
		if (panel_name == fef)
		{
			*(BYTE*)(panel + 0x239) = 0xC;
			this->disabled_panels.push_back(panel);
			return;
		}
	}
}
bool sdk::dialog::c_dialog::sell_test(int id)
{
	return false;
}

void __stdcall sdk::dialog::repair_eq(void* a)
{
	auto data = (sdk::dialog::s_thread_p*)(a);
	sdk::dialog::dialog->thread_running = true;
	sdk::dialog::dialog->last_click_time = 0;
	while (1)
	{
		if (sdk::dialog::dialog->last_execution + 300 > GetTickCount64()) continue;
		sdk::dialog::dialog->last_execution = GetTickCount64();
		if (!sdk::dialog::dialog->did_enter_repair)
		{
			auto interaction = sdk::dialog::dialog->find_panel("Panel_Npc_Dialog_All");
			if (!interaction)
			{
				uint64_t npc_wanted_ptr = 0;
				for (auto b : sdk::player::player_->npcs) if (strstr(b.name.c_str(), data->npc.c_str())) { npc_wanted_ptr = b.ptr; break; }

				if (!npc_wanted_ptr)
				{
					sdk::util::log->b("npc cannot be found");
					continue;
				}

				auto cinteract = *(uint64_t*)(core::offsets::actor::interaction_current);
				if (!cinteract || cinteract != npc_wanted_ptr)
				{
					sys::roar_bot->f_npc_interaction(npc_wanted_ptr);
				}
				continue;
			}
			else sdk::dialog::dialog->did_enter_repair = true;
			continue;
		}
		if (!sdk::dialog::dialog->did_enter_menu)
		{
			auto repair_window = sdk::dialog::dialog->find_panel(sdk::dialog::dialog->core_dialogs["Repair"]);
			if (!repair_window)
			{
				auto rep_btn = sdk::dialog::dialog->find_button_ex("Repair", "Panel_Npc_Dialog_All");
				if (rep_btn == -1) continue;
				auto str = std::string("HandleEventLUp_DialogMain_All_FuncButton(").append(std::to_string(rep_btn)).append(")");
				sys::lua_q->add(str);
				continue;
			}
			else sdk::dialog::dialog->did_enter_menu = true;
			continue;
		}
		auto message_box = sdk::dialog::dialog->find_panel(sdk::dialog::dialog->core_dialogs["MessageBox"]);
		if (!message_box)
		{
			if (!sdk::dialog::dialog->did_click_repair)
			{
				if (!sdk::dialog::dialog->last_click_time)
				{
					sys::lua_q->add("HandleEventLUp_RepairFunc_All_Equipment()");
					sdk::dialog::dialog->last_click_time = GetTickCount64();
					sdk::dialog::dialog->did_click_repair = true;
					continue;
				}
			}
			else
			{
				if (sdk::dialog::dialog->did_click_confirm)
				{
					switch (sdk::dialog::dialog->exit_stage)
					{
					case 0:
					{
						auto repair_window = sdk::dialog::dialog->find_panel(sdk::dialog::dialog->core_dialogs["Repair"]);
						if (repair_window)
						{
							sys::lua_q->add("PaGlobalFunc_RepairFunc_All_Close()");
							break;
						}
						else sdk::dialog::dialog->exit_stage++;
						//sdk::util::log->b("exit repair complete");
						continue;
						break;
					}
					case 1:
					{
						auto interaction = sdk::dialog::dialog->find_panel("Panel_Npc_Dialog_All");
						if (interaction)
						{
							sys::lua_q->add("HandleEventLUp_DialogMain_All_ExitClick()");
							break;
						}
						else sdk::dialog::dialog->exit_stage++;
						//sdk::util::log->b("exit complete");
						continue;
						break;
					}
					default: break;
					}

					if (sdk::dialog::dialog->exit_stage >= 2)
					{
						//sdk::util::log->b("done repair");
						sdk::dialog::dialog->did_click = false;
						sdk::dialog::dialog->did_click_confirm = false;
						sdk::dialog::dialog->did_click_repair = false;
						sdk::dialog::dialog->did_select_confirm = false;
						sdk::dialog::dialog->did_enter_repair = false;
						sdk::dialog::dialog->did_finish_reapir = false;
						sdk::dialog::dialog->last_click_time = 0;
						sdk::dialog::dialog->exit_stage = 0;
						sdk::dialog::dialog->did_enter_menu = 0;
						sdk::dialog::dialog->thread_running = false;
						sdk::dialog::dialog->completed_repair = true;
						delete a;
						ExitThread(0);
						return;
					}
					continue;
				}
				if (GetTickCount64() > sdk::dialog::dialog->last_click_time + 1000)
				{
					sdk::dialog::dialog->last_click_time = 0;
					sdk::dialog::dialog->did_click_repair = false;
					continue;
				}
			}
		}
		else
		{
			if (!sdk::dialog::dialog->last_click_time)
			{
				//sdk::util::log->b("clicked messageBox");
				sys::lua_q->add("messageBox_YesButtonUp()");
				sdk::dialog::dialog->last_click_time = GetTickCount64();
				sdk::dialog::dialog->did_click_confirm = true;
				sdk::dialog::dialog->did_finish_reapir = true;
				continue;
			}
			else if (GetTickCount64() > sdk::dialog::dialog->last_click_time + 250)
			{
				sdk::dialog::dialog->last_click_time = 0;
				sdk::dialog::dialog->did_finish_reapir = false;
				sdk::dialog::dialog->did_click_confirm = false;
				continue;
			}
		}
	}
}
// item exist for too long with no change reset
void __stdcall sdk::dialog::do_store(void* a)
{
	auto data = (sdk::dialog::s_thread_p*)(a);
	sdk::dialog::dialog->thread_running = true;
	while (1)
	{
		if (sdk::dialog::dialog->last_execution + 250 > GetTickCount64()) continue;
		sdk::dialog::dialog->last_execution = GetTickCount64();
		if (!data->items.empty())
		{
			auto interacting = sdk::dialog::dialog->find_panel("Panel_Npc_Dialog_All");
			if (!interacting)
			{
				uint64_t npc_wanted_ptr = 0;
				for (auto b : sdk::player::player_->npcs) if (strstr(b.name.c_str(), data->npc.c_str())) { npc_wanted_ptr = b.ptr; break; }

				if (!npc_wanted_ptr)
				{
					sdk::util::log->b("npc cannot be found");
					continue;
				}

				sys::roar_bot->f_npc_interaction(npc_wanted_ptr);
				auto cinteract = *(uint64_t*)(core::offsets::actor::interaction_current);
				if (!cinteract || cinteract != npc_wanted_ptr) continue;

				sdk::util::log->b("interacted with %s", data->npc.c_str());
				continue;
			}
			auto shop_panel = sdk::dialog::dialog->find_panel("Panel_Window_Warehouse");
			if (!shop_panel)
			{
				auto btn = sdk::dialog::dialog->find_button_ex("Store", "Panel_Npc_Dialog_All");
				if (btn == -1) continue;
				auto str = std::string("HandleEventLUp_DialogMain_All_FuncButton(").append(std::to_string(btn)).append(")");
				sys::lua_q->add(str);
				sdk::util::log->b("store button > %s", str.c_str());
				continue;
			}
		}
		if (data->items.empty())//to exit dialog
		{
			auto interacting = sdk::dialog::dialog->find_panel("Panel_Npc_Dialog_All");
			if (interacting)
			{
				if (sdk::dialog::dialog->last_click_time != 0)
				{
					if (GetTickCount64() > sdk::dialog::dialog->last_click_time + 500)//max timeout to try again if failed
					{
						sdk::dialog::dialog->last_click_time = 0;
						sys::lua_q->add("HandleEventLUp_DialogMain_All_ExitClick()");
						continue;
					}
				}
				else
				{
					sys::lua_q->add("HandleEventLUp_DialogMain_All_ExitClick()");
					sdk::dialog::dialog->last_click_time = GetTickCount64();
					continue;
				}
			}
			else
			{
				sdk::dialog::dialog->completed_sales = true;
				sdk::dialog::dialog->needs_numberpad = false;
				sdk::dialog::dialog->last_click_time = 0;
				sdk::dialog::dialog->did_click = false;
				sdk::dialog::dialog->did_select_confirm = false;
				sdk::dialog::dialog->did_select_max = false;
				sdk::dialog::dialog->thread_running = false;
				delete a;
				ExitThread(0);
				return;
			}
			continue;
		}
		auto i = data->items.back();
		if (i != -1)
		{
			if (sdk::dialog::dialog->last_click_time != 0)
			{
				if (GetTickCount64() > sdk::dialog::dialog->last_click_time + 150)//max timeout to try again if failed
				{
					sdk::dialog::dialog->last_click_time = 0;
					goto do_it;
				}
			}
			else
			{
			do_it:
				auto has_item = false; int slot = -1;
				for (auto a : sdk::player::player_->inventory_items)
				{
					if (a.item_index == i)
					{
						has_item = true;
						slot = a.item_slot;
						if (a.count > 1) sdk::dialog::dialog->needs_numberpad = true;
						else sdk::dialog::dialog->needs_numberpad = false;
						break;
					}
				}
				auto delta = GetTickCount64() - sdk::dialog::dialog->last_click_time;
				if (delta > 2500)
				{
					sdk::dialog::dialog->did_click = false;
					sdk::util::log->b("sale stuck, retrying");
				}
				if (has_item)
				{
					if (!sdk::dialog::dialog->did_click)
					{
						sdk::dialog::dialog->last_click_time = GetTickCount64();
						auto s = std::string("HandleEventRUp_Inventory_All_SlotRClick(").append(std::to_string(slot)).append(")");
						sys::lua_q->add(s);
						sdk::dialog::dialog->did_click = true;
						continue;
					}
					else if (GetTickCount64() > sdk::dialog::dialog->last_click_time + 500)
					{
						if (sdk::dialog::dialog->needs_numberpad)
						{
							if (!sdk::dialog::dialog->did_select_max)
							{
								auto r = sdk::dialog::dialog->find_panel(sdk::dialog::dialog->core_dialogs["NumberPad"]);
								if (r)
								{
									sys::lua_q->add("HandleEventLUp_NumberPad_All_AllButton_Click(0)");
									sdk::dialog::dialog->did_select_max = true;
									sdk::dialog::dialog->last_click_time = GetTickCount64();
									continue;
								}
							}
							if (!sdk::dialog::dialog->did_select_confirm)
							{
								auto r = sdk::dialog::dialog->find_panel(sdk::dialog::dialog->core_dialogs["NumberPad"]);
								if (r)
								{
									sys::lua_q->add("HandleEventLUp_NumberPad_All_ConfirmButton_Click()");
									sdk::dialog::dialog->did_select_confirm = true;
									sdk::dialog::dialog->last_click_time = GetTickCount64();
									continue;
								}
							}
							else
							{
								sdk::dialog::dialog->did_select_confirm = false;
								sdk::dialog::dialog->did_select_max = false;
								continue;
							}
						}
					}
				}
				else
				{
					sdk::dialog::dialog->needs_numberpad = false;
					sdk::dialog::dialog->last_click_time = 0;
					sdk::dialog::dialog->did_click = false;
					sdk::dialog::dialog->did_select_confirm = false;
					sdk::dialog::dialog->did_select_max = false;
					data->items.pop_back();
				}
			}
		}
	}
}

void __stdcall sdk::dialog::do_sell(void* a)
{
	auto data = (sdk::dialog::s_thread_p*)(a);
	sdk::dialog::dialog->thread_running = true;
	while (1)
	{
		if (sdk::dialog::dialog->last_execution + 250 > GetTickCount64()) continue;
		sdk::dialog::dialog->last_execution = GetTickCount64();
		if (!data->items.empty())
		{
			auto interacting = sdk::dialog::dialog->find_panel("Panel_Npc_Dialog_All");
			if (!interacting)
			{
				sdk::dialog::dialog->sell_reset();
				uint64_t npc_wanted_ptr = 0;
				for (auto b : sdk::player::player_->npcs) if (strstr(b.name.c_str(), data->npc.c_str())) { npc_wanted_ptr = b.ptr; break; }

				if (!npc_wanted_ptr)
				{
					sdk::util::log->b("npc cannot be found");
					continue;
				}

				sys::roar_bot->f_npc_interaction(npc_wanted_ptr);
				auto cinteract = *(uint64_t*)(core::offsets::actor::interaction_current);
				if (!cinteract || cinteract != npc_wanted_ptr) continue;

				sdk::util::log->b("interacted with %s", data->npc.c_str());
				sdk::dialog::dialog->last_execution = GetTickCount64() + 1000;
				continue;
			}
			auto shop_panel = sdk::dialog::dialog->find_panel("Panel_Dialog_NPCShop_All");
			if (!shop_panel)
			{
				auto btn = sdk::dialog::dialog->find_button_ex("Shop", "Panel_Npc_Dialog_All");
				if (btn == -1) continue;
				auto str = std::string("HandleEventLUp_DialogMain_All_FuncButton(").append(std::to_string(btn)).append(")");
				sys::lua_q->add(str);
				sdk::util::log->b("shop button > %s", str.c_str());
				continue;
			}
		}
		if (data->items.empty())//to exit dialog
		{
			auto interacting = sdk::dialog::dialog->find_panel("Panel_Npc_Dialog_All");
			if (interacting)
			{
				if (sdk::dialog::dialog->last_click_time != 0)
				{
					if (GetTickCount64() > sdk::dialog::dialog->last_click_time + 500)//max timeout to try again if failed
					{
						sdk::dialog::dialog->last_click_time = 0;
						sys::lua_q->add("HandleEventLUp_DialogMain_All_ExitClick()");
						sdk::util::log->b("exiting interaction");
						continue;
					}
				}
				else
				{
					sys::lua_q->add("HandleEventLUp_DialogMain_All_ExitClick()");
					sdk::dialog::dialog->last_click_time = GetTickCount64();
					sdk::util::log->b("exiting interaction");
					continue;
				}
			}
			else
			{
				sdk::util::log->b("exit confirmed");
				sdk::dialog::dialog->completed_sales = true;
				sdk::dialog::dialog->needs_numberpad = false;
				sdk::dialog::dialog->last_click_time = 0;
				sdk::dialog::dialog->did_click = false;
				sdk::dialog::dialog->did_select_confirm = false;
				sdk::dialog::dialog->did_select_max = false;
				sdk::dialog::dialog->thread_running = false;
				delete a;
				ExitThread(0);
				return;
			}
			continue;
		}
		auto i = data->items.back();
		if (i != -1)
		{
			if (sdk::dialog::dialog->last_click_time != 0)
			{
				if (GetTickCount64() > sdk::dialog::dialog->last_click_time + 150)//max timeout to try again if failed
				{
					sdk::dialog::dialog->last_click_time = 0;
					goto do_it;
				}
			}
			else
			{
			do_it:
				auto has_item = false; int slot = -1;
				for (auto a : sdk::player::player_->inventory_items)
				{
					if (a.item_index == i)
					{
						has_item = true;
						slot = a.item_slot;
						if (a.count > 1) sdk::dialog::dialog->needs_numberpad = true;
						else sdk::dialog::dialog->needs_numberpad = false;
						break;
					}
				}
				sdk::util::log->b("item: %i exists: %i slot: %i", i, has_item, slot);
				if (has_item && slot != -1)
				{
					auto delta = GetTickCount64() - sdk::dialog::dialog->last_click_time;
					if (delta > 2500 && sdk::dialog::dialog->last_click_time != 0)
					{
						sdk::dialog::dialog->last_click_time = GetTickCount64();
						sdk::dialog::dialog->did_click = false;
						sdk::util::log->b("sale stuck, retrying");
					}
					if (!sdk::dialog::dialog->did_click)
					{
						sdk::dialog::dialog->last_click_time = GetTickCount64();
						auto s = std::string("HandleEventRUp_Inventory_All_SlotRClick(").append(std::to_string(slot)).append(")");
						sys::lua_q->add(s);
						sdk::dialog::dialog->did_click = true;
						sdk::util::log->b("clicking item");
						continue;
					}
					else if (GetTickCount64() > sdk::dialog::dialog->last_click_time + 150)
					{
						if (sdk::dialog::dialog->needs_numberpad)
						{
							if (!sdk::dialog::dialog->did_select_max)
							{
								auto r = sdk::dialog::dialog->find_panel(sdk::dialog::dialog->core_dialogs["NumberPad"]);
								if (r)
								{
									sdk::util::log->b("select max quant");
									sys::lua_q->add("HandleEventLUp_NumberPad_All_AllButton_Click(0)");
									sdk::dialog::dialog->did_select_max = true;
									sdk::dialog::dialog->last_click_time = GetTickCount64();
									continue;
								}
							}
							else
							{
								sdk::dialog::dialog->did_select_max = false;
								sdk::dialog::dialog->did_click = false;
							}
							if (!sdk::dialog::dialog->did_select_confirm)
							{
								auto r = sdk::dialog::dialog->find_panel(sdk::dialog::dialog->core_dialogs["NumberPad"]);
								if (r)
								{
									sdk::util::log->b("select confirm sell");
									sys::lua_q->add("HandleEventLUp_NumberPad_All_ConfirmButton_Click()");
									sdk::dialog::dialog->did_select_confirm = true;
									sdk::dialog::dialog->last_click_time = GetTickCount64();
									continue;
								}
							}
							else
							{
								sdk::dialog::dialog->did_select_confirm = false;
								sdk::dialog::dialog->did_select_max = false;
								continue;
							}
						}
					}
				}
				else
				{
					sdk::util::log->b("item processed %i", i);
					sdk::dialog::dialog->needs_numberpad = false;
					sdk::dialog::dialog->last_click_time = 0;
					sdk::dialog::dialog->did_click = false;
					sdk::dialog::dialog->did_select_confirm = false;
					sdk::dialog::dialog->did_select_max = false;
					data->items.pop_back();
				}
			}
		}
	}
}
sdk::dialog::c_dialog* sdk::dialog::dialog;