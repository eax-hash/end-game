#include <inc.h>
std::vector<int> sys::v_keys_i =
{
	-1,
	VK_LBUTTON,
	VK_RBUTTON,
	VK_SPACE,
	VK_TAB,
	VK_SHIFT,
	0x57,
	0x41,
	0x53,
	0x44,
	0x45,
	0x46,
	0x51,
	0x43,
	9000,
	9001,
	9002,
	9003,
	9004,
	9005,
	9006,
	9007,
	9008,
	9009
};
std::vector<std::string> sys::v_keys_s =
{
	{"None       "},
	{"Left  mouse"},
	{"Right mouse"},
	{"Space key  "},
	{"TAB   key  "},
	{"Shift key  "},
	{"W key"},
	{"A key"},
	{"S key"},
	{"D key"},
	{"E key"},
	{"F key"},
	{"Q key"},
	{"C key"},
	{"1 slot"},
	{"2 slot"},
	{"3 slot"},
	{"4 slot"},
	{"5 slot"},
	{"6 slot"},
	{"7 slot"},
	{"8 slot"},
	{"9 slot"},
	{"10 slot"}
};
std::unordered_map<int, int> sys::v_quickslot =
{
	{9000, 0},
	{9001, 1},
	{9002, 2},
	{9003, 3},
	{9004, 4},
	{9005, 5},
	{9006, 6},
	{9007, 7},
	{9008, 8},
	{9009, 9}
};
std::unordered_map<int, std::string> sys::v_keys =
{
	{-1        , "None"		  },
	{VK_LBUTTON, "Left  mouse"},
	{VK_RBUTTON, "Right mouse"},
	{VK_SPACE  , "Space key  "},
	{VK_TAB    , "TAB   key  "},
	{VK_SHIFT  , "Shift key  "},
	{0x57      , "W key"},
	{0x41	   , "A key"},
	{0x53	   , "S key"},
	{0x44	   , "D key"},
	{0x45	   , "E key"},
	{0x46	   , "F key"},
	{0x51	   , "Q key"},
	{0x43	   , "C key"},
	{9000      , "1 slot"},
	{9001      , "2 slot"},
	{9002      , "3 slot"},
	{9003      , "4 slot"},
	{9004      , "5 slot"},
	{9005      , "6 slot"},
	{9006      , "7 slot"},
	{9007      , "8 slot"},
	{9008      , "9 slot"},
	{9009      , "10 slot"}
};
std::unordered_map<int, int> sys::v_keys_flags =
{
	{VK_LBUTTON, 0x40000},
	{VK_RBUTTON, 0x80000},
	{VK_SPACE  , 0x20000},
	{VK_TAB    , 0x4000 },
	{VK_SHIFT  , 0x8000 },
	{0x57      , 0x2    },
	{0x41	   , 0x20   },
	{0x53	   , 0x40   },
	{0x44	   , 0x80   },
	{0x45	   , 0x4    },
	{0x46	   , 0x100  },
	{0x51	   , 0x1    },
	{0x43	   , 0x800  }
};
bool sys::c_legit_bot::mobs_near(sdk::util::c_vector3 p, sdk::util::c_vector3 s)
{
	//auto self_key = *(int*)(this->self + core::offsets::actor::actor_proxy_key);
	for (auto a : sdk::player::player_->actors)
	{
		if (a.type != 1
			|| a.hp <= 0
			|| !a.ptr
			|| !a.pos.valid()
			|| a.state == 1
			|| a.ptr == this->self) continue;
		auto d = sdk::util::math->gdst_2d(p, a.pos);
		if (d > 800) continue;
		if (!sdk::player::player_->trace(s, a.pos, this->self, 200).success) continue;
		return true;
	}
	return false;
}
sdk::player::s_blank_proxy sys::c_legit_bot::nearest(sdk::util::c_vector3 from, sdk::util::c_vector3 s, float max)
{
	auto n = sdk::player::s_blank_proxy(); auto l = float(max);
	for (auto a : sdk::player::player_->actors)
	{
		if (a.type != 1
			|| a.hp <= 0
			|| !a.ptr
			|| !a.pos.valid()
			|| a.state == 1
			|| a.ptr == this->self) continue;
		auto d = sdk::util::math->gdst_2d(from, a.pos);
		if (d > max) continue;
		if (!sdk::player::player_->trace(s, a.pos, this->self, 200).success) continue;
		if (a.rlt_dst < l)
		{
			l = d;
			n = a;
		}
	}
	return n;
}
bool sys::c_legit_bot::update_target()
{
	for (auto a : sdk::player::player_->actors)
	{
		if (a.ptr == this->target_actor.ptr && a.key == this->target_actor.key)
		{
			if (a.hp <= 0 || a.state == 1)
			{
				this->target_actor = {};
				return false;
			}
			this->target_actor = a;
			return true;
		}
	}
	this->target_actor = {};
	return false;
}
bool sys::c_legit_bot::add_skill(int key, int key2, int key3, int interval, int cd, int mp, int awakening, int condition)
{
	for (auto obj : this->skills)
	{
		if (key2 != -1)
		{
			if (obj->input->k[0] == key &&
				obj->input->k[1] == key2 &&
				obj->input->k[2] == key3 &&
				obj->mp == mp &&
				obj->cd == cd)
				return 0;
		}
		else
		{
			if (obj->input->k[0] == key &&
				obj->mp == mp &&
				obj->cd == cd)
				return 0;
		}
	}
	auto t = new sys::s_skill();
	t->input = new sys::s_key_input({ key, key2, key3 }, interval);
	t->cd = cd; t->mp = mp;
	if (condition > 0) t->condition = condition;
	else t->condition = -1;
	if (t->mp == 0) t->mp = 5;
	if (t->cd == 0) t->cd = 5;
	if (t->condition == 0) t->condition = -1;
	t->awakening = awakening;
	this->skills.push_back(t);
	sdk::util::log->add("skill was added to list");
	return 1;
}
bool sys::c_legit_bot::save_skill_profile()
{
	/*skill profile example line:
	[s](  1)(  2)(  3)( 10)(100)(500)(  1)
		key1 key2 key3 cd   mp   press  condition
	*/
	std::ofstream r(combo_name);
	for (auto&& obj : this->skills)
	{
		r << "[s](" << obj->input->k[0] << ")(" << obj->input->k[1] << ")(" << obj->input->k[2] << ")(" << obj->cd << ")(" << obj->mp << ")(" << obj->input->d << ")(" << obj->awakening << ")(" << obj->condition << ")" << "\n";
	}
	r.close();
	//utils::cfg->cheat_log.push_back("(save-profile) saved profile!");
	return 1;
}
bool sys::c_legit_bot::load_skill_profile()
{
	/*skill profile example line:
	[s](  1)(  2)(  3)( 10)(100)(500)(  1)
		key1 key2 key3 cd   mp   press  awakening
	*/
	this->skills.clear();

	std::ifstream in(combo_name); std::string tmp;
	auto parse_skill = [&](std::string l) -> bool
	{
		auto line = l;
		auto res = new sys::s_skill();

		int key1 = 0, key2 = 0, key3 = 0, mp = 0, cd = 0, interval = 0, awakening = 0, condition = 0;

		while (line.size() > 0)
		{
			if (condition == -1 || condition >= 1) break; /*finish*/
			/*parse all 6 parts*/
			auto pos = line.find("(");
			if (!pos) break;
			line.erase(0, pos + 1);
			pos = line.find(")");

			auto cpy = line;
			cpy.erase(pos, cpy.size()); /*cpy only contains the seperated string now*/

			line.erase(0, pos); /*line now has the seperated part removed from it*/

			auto flt = std::stoi(cpy);

			if (key1 == 0) key1 = flt;
			else if (key2 == 0) key2 = flt;
			else if (key3 == 0) key3 = flt;
			else if (cd == 0) cd = flt;
			else if (mp == 0) mp = flt;
			else if (interval == 0) interval = flt;
			else if (awakening == 0) awakening = flt;
			else if (condition == 0) condition = flt;
		}

		res->input = new sys::s_key_input({ key1,key2,key3 }, interval);

		res->cd = cd;
		res->mp = mp;
		res->awakening = awakening;
		res->condition = condition;

		if (awakening == 0) res->awakening = 1;
		if (awakening == -1) res->awakening = -1;

		std::stringstream k;
		k << "key1:" << key1 << " key2:" << key2 << " key3:" << key3 << " cd:" << cd << " mp:" << mp << " iv:" << interval << " aw:" << awakening << " cn:" << condition;
		sdk::util::log->add(k.str(), sdk::util::e_info, true);

		this->skills.push_back(res);

		return 1;
	};

	while (std::getline(in, tmp))
	{
		if (tmp.empty()) continue;
		auto skill = parse_skill(tmp);
		if (!skill) sdk::util::log->add("failed to load skill from file");
	}
	sdk::util::log->add("profile was loaded");
	return 1;
}
void sys::c_legit_bot::aim_pos(sdk::util::c_vector3 t, sdk::util::c_vector3 s)
{
#define PI		3.14159265358979323846
	auto norm = [](float& fl)
	{
		while (fl > PI) fl = -PI + (fl - PI);
		while (fl < (-PI)) fl = PI + (fl + PI);
	};

	auto enemy_dir_x = s.x - t.x;
	auto enemy_dir_y = s.z - t.z;
	auto player_rotation = atan2(-enemy_dir_y, enemy_dir_x);
	auto rot = player_rotation;
	rot -= (2 * PI);
	rot += PI / 2;
	norm(rot);

	auto controller = *(uint64_t*)(this->self + core::offsets::actor::actor_char_ctrl);
	auto c_base = *(uint64_t*)(controller + 0x10);

	this->spitch(-0.8f);
	this->syaw(rot);
	*(float*)(c_base + 0x43C) = rot;

}
void sys::c_legit_bot::spitch(float f)
{
	auto scene_base = *(uint64_t*)(core::offsets::cl::client_base);
	if (!scene_base) return;
	auto camera_base = *(uint64_t*)(scene_base + 0x30);
	if (!camera_base) return;
	*(float*)(camera_base + 0x60) = f;
	*(float*)(camera_base + 0x64) = f;
	*(float*)(camera_base + 0x5C) = f;
}
void sys::c_legit_bot::syaw(float f)
{
	auto scene_base = *(uint64_t*)(core::offsets::cl::client_base);
	if (!scene_base) return;
	auto camera_base = *(uint64_t*)(scene_base + 0x30);
	if (!camera_base) return;
	*(float*)(camera_base + 0x68) = f;
}
bool sys::c_legit_bot::ssp(s_path_script s)
{
	if (this->force_store) return true;
	auto in_m = *(int*)(this->self + core::offsets::actor::actor_inv_max_weight) / 10000;
	auto in_w = (*(int*)(this->self + core::offsets::actor::actor_inv_raw_weight) + *(int*)(this->self + core::offsets::actor::actor_inv_gear_weight)) / 10000;
	if (in_w >= in_m) return true;
	//
	auto in_l = *(int*)(this->self + core::offsets::actor::actor_inv_left);
	if (in_l <= 2) return true;
	//
	return false;
}
void sys::c_legit_bot::repath(int a, int b)
{
	if (a == 0) { this->cur_route.clear(); for (auto c : this->grind) this->cur_route.emplace_back(c, "NONE", "NONE", c.pause); }
	if (a == 1)
	{
		this->cur_route.clear();
		if (b) this->cur_route = this->store;
		else
		{
			this->cur_route = this->store;
			std::reverse(this->cur_route.begin(), this->cur_route.end());
		}
		this->reversed = b;
	}
}
bool sys::c_legit_bot::pause(uint64_t s, float p)
{
	if (p == 0.1f || p == 1.f) return true;
	if (this->p_mode == 0)
	{
		auto mobs = [&]() -> bool
		{
			auto sk = *(int*)(s + core::offsets::actor::actor_proxy_key);
			for (auto a : sdk::player::player_->actors)
			{
				if (a.ptr == s) continue;
				if (a.type != 1) continue;
				if (a.hp <= 0) continue;
				if (a.state == 1) continue;
				if (a.rlt_dst >= 800) continue;
				auto ak = *(int*)(a.ptr + core::offsets::actor::actor_attack_target);
				if (ak != sk) return true;
				return false;
			}
			return true;
		};
		if (mobs()) return true;
		else
		{
			if (!this->max_cooltime) this->max_cooltime = GetTickCount64() + 30000;
			else if (GetTickCount64() > this->max_cooltime) { this->max_cooltime = 0; return true; }
			return false;
		}
	}

	auto tick = GetTickCount64();
	if (!pause_ending_tick) { pause_ending_tick = tick + (p * 1000.f); return 0; }
	else { if (tick > pause_ending_tick) { pause_ending_tick = 0; return 1; } }

	return false;
}
bool sys::c_legit_bot::has_lootables(sdk::util::c_vector3 spp)
{
	if (sys::loot->loot_proxys.empty()) return 0;
	auto l = 9999.f; auto rr = uint64_t(0);
	auto selfpos = sdk::player::player_->gpos(this->self);
	for (auto b = 0; b < sys::loot->loot_proxys.size(); b++)
	{
		auto a = sys::loot->loot_proxys[b];
		if (*(BYTE*)(a + core::offsets::actor::actor_was_looted))
		{
			sys::loot->loot_proxys.erase(sys::loot->loot_proxys.begin() + b);
			continue;
		}
		auto ap = sdk::player::player_->gpos(a);
		auto rd = sdk::util::math->gdst_3d(ap, spp);
		if (rd <= l && rd <= 800)
		{
			if (!sdk::player::player_->trace(selfpos, ap, this->self, 200, 34, false).success) continue;
			l = rd;
			rr = a;
			continue;
		}
	}
	return rr;
}
bool sys::c_legit_bot::loot_near(sdk::util::c_vector3 o)
{
	//if (!ibot_lootrange) ibot_lootrange = sys::config->gvar("roar_bot", "ibot_lootrange");

	auto has = this->has_lootables(o);
	if (!has) { sys::cursor_tp->set_pos(this->self, sdk::util::c_vector3(o.x / 100, o.y / 100, o.z / 100)); return true; }

	auto selfpos = sdk::player::player_->gpos(this->self);

	auto l = 9999.f; auto rr = uint64_t(0);
	for (auto b = 0; b < sys::loot->loot_proxys.size(); b++)
	{
		auto a = sys::loot->loot_proxys[b];
		if (*(BYTE*)(a + core::offsets::actor::actor_was_looted))
		{
			sys::loot->loot_proxys.erase(sys::loot->loot_proxys.begin() + b);
			continue;
		}
		auto ap = sdk::player::player_->gpos(a);
		auto rd = sdk::util::math->gdst_3d(ap, o);
		if (rd <= l && rd <= 800)
		{
			if (!sdk::player::player_->trace(selfpos, ap, this->self, 200, 34, false).success) continue;
			l = rd;
			rr = a;
			continue;
		}
	}
	if (rr)
	{
		auto lpos = sdk::player::player_->gpos(rr);
		sys::cursor_tp->set_pos(this->self, sdk::util::c_vector3((int)lpos.x / 100, lpos.y / 100, (int)lpos.z / 100));
		this->loot_act_k = *(int*)(rr + core::offsets::actor::actor_proxy_key);
		sys::loot->act_id_cur = 0;
	}

	return false;
}
bool sys::c_legit_bot::has_aggro()
{
	auto sk = *(int*)(this->self + core::offsets::actor::actor_proxy_key);
	for (auto a : sdk::player::player_->actors)
	{
		if (a.type != 1 || a.hp <= 0 || a.state == 1 || a.rlt_dst >= 2000) continue;
		auto ag = *(int*)(a.ptr + core::offsets::actor::actor_attack_target);
		if (sk == ag) return true;
	}
	return false;
}
bool sys::c_legit_bot::stance()
{
	auto a = sdk::player::player_->ganim(this->self);
	if (strstr(a.c_str(), "BT_skill_AggroShout_Ing_UP")) return true;//autoskip
	if (strstr(a.c_str(), "BT_WAIT")) return true;//autoskip
	if (GetTickCount64() > this->sct) this->sct = GetTickCount64() + 5000;
	else return false;
	if (strstr(a.c_str(), "WAIT"))
	{
		sys::key_q->add(new sys::s_key_input({ VK_TAB }, 500));
		return false;
	}
	return true;
}
void sys::c_legit_bot::rskill()
{
	if (GetTickCount64() > this->skill_delay) this->skill_delay = 25;
	else return;

	if (sys::key_q->thread_working) return;

	uint64_t& input_adr = *((uint64_t*)(*((uint64_t*)(core::offsets::cl::client_base)) + 0x08));
	*((uint64_t*)((input_adr + 0x840) + (0x57 * 4))) = 0;

	auto msp = sdk::player::player_->gsp(this->self);
	auto stance = *(BYTE*)(this->self + core::offsets::actor::actor_combat_stance);

	auto cur_anim = sdk::player::player_->ganim(this->self);
	auto loc = std::locale();
	for (std::string::size_type i = 0; i < cur_anim.length(); ++i) std::cout << std::tolower(cur_anim[i], loc);
	auto cur_anim_lower = loc.c_str();

	for (auto&& a : this->skills)
	{
		if (strstr(cur_anim_lower, "stop") || strstr(cur_anim_lower, "end")) continue;
		if (GetTickCount64() < a->next_possible_use) continue;
		if (msp < a->mp) continue;
		if (sys::key_q->gq().size() || sys::key_q->thread_working) return;

		//if ((stance != 2 && a->awakening == 1) ||
		//	(stance != 1 && a->awakening == -1))
		//{
		//	//need to swap
		//	if (stance == 0) sys::key_q->add(new sys::s_key_input({ VK_TAB }, 500));
		//	else sys::key_q->add(new sys::s_key_input({ 0x43 }, 500));
		//	return;
		//}

		a->next_possible_use = GetTickCount64() + (a->cd * 1000);
		a->last_use = GetTickCount64();

		sys::key_q->add(a->input);
		a->total_uses++;

		return;
	}
	if (!sys::key_q->thread_working) sys::key_q->add(new sys::s_key_input({ VK_LBUTTON }, 100));
}
bool sys::c_legit_bot::snear()
{
	if (this->p_mode == 1) return false;
	this->self = *(uint64_t*)(core::offsets::actor::actor_self);
	if (!this->self) return false;
	auto p = sdk::player::player_->gpos(this->self); auto ldst = 9999.f; sdk::util::c_vector3 lv;
	this->cur_route.clear();
	this->repath(0, 0);
	for (auto a : this->cur_route)
	{
		auto d = sdk::util::math->gdst_3d(p, a.pos);
		if (d < ldst)
		{
			ldst = d;
			lv = a.pos;
		}
	}
	for (auto a : this->cur_route)
	{
		if (!a.pos.cmp(lv)) this->cur_route.pop_front();
		else
		{
			sdk::util::log->add("set start to nearest pos");
			break;
		}
	}
	return true;
}
void sys::c_legit_bot::reset()
{
	this->cur_route.clear(); this->grind.clear(); this->store.clear(); this->allowed_sell_items.clear(); this->items_left_sell.clear();
	this->p_mode = 0;
	this->reversed = 0;
	this->s_npc = "NONE";
	this->s_scr = "NONE";
	this->lp.clear();
}
void sys::c_legit_bot::sgpos(sdk::util::c_vector3 to_replace, sdk::util::c_vector3 new_pos)
{
	for (auto&& a : this->grind)
	{
		if (!a.cmp(to_replace)) continue;
		a = new_pos;
		break;
	}
}
std::vector<std::string> sys::c_legit_bot::gnpcs()
{
	auto r = std::vector<std::string>();
	for (auto a : sdk::player::player_->npcs)
	{
		r.push_back(a.name);
	}
	return r;
}
void sys::c_legit_bot::gpoint()
{
	auto p = sdk::player::player_->gpos(this->self);
	std::ofstream f(this->pathname, std::ios::app);
	if (!f.is_open()) return;
	f << "[gp](" << p.x << ")(" << p.y << ")(" << p.z << ")(0.1)\n";
	f.close();
	this->grind.push_back(p);
	sdk::util::log->add("gpoint add", sdk::util::e_info, true);
}
void sys::c_legit_bot::spoint()
{
	auto p = sdk::player::player_->gpos(this->self);
	std::ofstream f(this->pathname, std::ios::app);
	if (!f.is_open()) return;
	f << "(sp){" << p.x << "}{" << p.y << "}{" << p.z << "}{" << "NONE" << "}{" << "NONE" << "}" << "\n";
	f.close();
	sdk::util::log->add("spoint add", sdk::util::e_info, true);
	this->store.emplace_back(p, "NONE", "NONE", false);
}
void sys::c_legit_bot::sepoint()
{
	auto p = sdk::player::player_->gpos(this->self);
	std::ofstream f(this->pathname, std::ios::app);
	if (!f.is_open()) return;
	f << "(sp){" << p.x << "}{" << p.y << "}{" << p.z << "}{" << this->s_npc << "}{" << this->s_scr << "}\n";
	f.close();
	this->s_npc = "NONE"; this->s_scr = "NONE"; this->glua_actions = false; this->last_lua_actions.clear();
	this->store.emplace_back(p, this->s_npc, this->s_scr, true);
	sdk::util::log->add("sepoint add", sdk::util::e_info, true);
}
void sys::c_legit_bot::sitem(int i)
{
	for (auto a : this->allowed_sell_items) if (a == i) return;
	std::ofstream f(this->pathname, std::ios::app);
	if (!f.is_open()) return;
	f << "[item](" << i << ")\n";
	this->allowed_sell_items.push_back(i);
	sdk::util::log->add("sitem add", sdk::util::e_info, true);
}
std::vector<std::string> sys::c_legit_bot::gitm()
{
	auto r = std::vector<std::string>();
	//
	for (auto a : sdk::player::player_->inventory_items) r.push_back(a.name);
	//
	return r;
}
std::vector<int> sys::c_legit_bot::gitm_left()
{
	return this->items_left_sell;
}
int sys::c_legit_bot::gitem_bn(std::string s)
{
	for (auto a : sdk::player::player_->inventory_items) if (a.name == s) return a.item_index;
	return {};
}
void sys::c_legit_bot::autopot()
{
	if (!ipot || !ihp_pct || !isp_pct)
	{
		ipot = sys::config->gvar("legit_bot", "ipot");
		ihp_pct = sys::config->gvar("legit_bot", "ihp_pot_pct");
		isp_pct = sys::config->gvar("legit_bot", "isp_pot_pct");
	}
	if (!ipot->iv) return;
	auto hp = sdk::player::player_->ghp(self);
	auto max_hp = sdk::player::player_->gmhp(self);
	auto sp = sdk::player::player_->gsp(self);
	auto max_sp = sdk::player::player_->gmsp(self);
	//				
	auto hp_pct_cur = (hp / max_hp) * 100.f;
	auto sp_pct_cur = (float)((float)sp / (float)max_sp) * 100.f;
	//
	if (hp_pct_cur <= ihp_pct->iv)
	{
		for (auto a : this->hp_pots)
		{
			if (!sys::rebuff->hitem(a)) continue;
			sys::lua_q->useitem_id(a);
			break;
		}
	}
	if (sp_pct_cur <= isp_pct->iv)
	{
		for (auto a : this->mp_pots)
		{
			if (!sys::rebuff->hitem(a)) continue;
			sys::lua_q->useitem_id(a);
			break;
		}
		for (auto a : this->wp_items)
		{
			if (!sys::rebuff->hitem(a)) continue;
			sys::lua_q->useitem_id(a);
			break;
		}
	}
}
void sys::c_legit_bot::gppoint(float t)
{
	auto p = sdk::player::player_->gpos(this->self); p.pause = t;
	std::ofstream f(this->pathname, std::ios::app);
	if (!f.is_open()) return;
	f << "[gp](" << p.x << ")(" << p.y << ")(" << p.z << ")(" << t << ")\n";
	f.close();
	this->grind.push_back(p);
	sdk::util::log->add("gppoint add", sdk::util::e_info, true);
}
void sys::c_legit_bot::record()
{
	this->self = *(uint64_t*)(core::offsets::actor::actor_self);
	auto p = sdk::player::player_->gpos(this->self);
	if (!this->store_can_path && this->recording_s) return;
	if (!lp.valid())
	{
		this->grind.clear(); this->allowed_sell_items.clear(); this->store.clear();
		lp = p;
		if (this->recording_g) this->grind.push_back(p);
		if (this->recording_s) this->store.emplace_back(p, "NONE", "NONE", false);
		return;
	}
	auto d = sdk::util::math->gdst_3d(p, lp);
	if (d >= 300)
	{
		lp = p;
		if (this->recording_g) this->gpoint();
		if (this->recording_s) this->spoint();
	}
}
void sys::c_legit_bot::load()
{
	this->reset(); this->grind.clear(); this->store.clear();
	auto parse_position = [&](std::string l) -> sdk::util::c_vector3
	{
		auto line = l;
		sdk::util::c_vector3 res; res.clear(); res.pause = 0;

		while (line.size() > 0)
		{
			if (res.pause != 0) break; /*finish*/
			/*parse all 4 vector parts*/
			auto pos = line.find("(");

			if (!pos) break;
			line.erase(0, pos + 1);
			pos = line.find(")");

			auto cpy = line;
			cpy.erase(pos, cpy.size()); /*cpy only contains the seperated string now*/

			line.erase(0, pos); /*line now has the seperated part removed from it*/

			auto flt = std::stof(cpy);

			//sdk::util::log->add(std::string(">f:").append(std::to_string(flt)).append(" s:").append(std::to_string(line.size())), sdk::util::e_info, true);

			if (res.x == 0) res.x = flt;
			else if (res.y == 0) res.y = flt;
			else if (res.z == 0) res.z = flt;
			else if (res.pause == 0) res.pause = flt;
		}

		return res;
	};
	auto parse_storage = [&](std::string l) -> s_path_script
	{
		auto line = l;
		s_path_script res;
		//"(sp){" << obj.pos.x << "}{" << obj.pos.y << "}{" << obj.pos.z << "}{" << obj.npc_name << "}{" << obj.script << "}"
		while (line.size() > 0)
		{
			if (res.script.size() > 0) break;/*done parsing*/

			if (res.pos.hasZero()) /*parse pos vec3*/
			{
				auto pos = line.find("{");
				line.erase(0, pos + 1); /*delete header and first {*/

				pos = line.find("}");

				auto cpy = line;
				cpy.erase(pos, cpy.size());/*only leaves var behind*/

				line.erase(0, pos); /*erase current vec entry*/

				auto var = std::stof(cpy);

				if (res.pos.x == 0) res.pos.x = var;
				else if (res.pos.y == 0) res.pos.y = var;
				else if (res.pos.z == 0) res.pos.z = var;
			}
			else if (res.npc_name.empty()) /*parse npc name from script*/
			{
				/* "NONE" = no npc*/
				auto pos = line.find("{");
				line.erase(0, pos + 1);

				pos = line.find("}");

				auto cpy = line;
				cpy.erase(pos, cpy.size()); /*erase all after npc name*/

				line.erase(0, pos); /*delete npc name from line*/

				res.npc_name = cpy;
			}
			else if (res.script.empty()) /*parse lua script line*/
			{
				/* "NONE" = no scr*/
				auto pos = line.find("{");
				line.erase(0, pos + 1);

				pos = line.find("}");

				auto cpy = line;
				cpy.erase(pos, cpy.size()); /*erase all after scr*/

				line.erase(0, pos); /*delete scr from line*/

				res.script = cpy;
			}
		}
		res.pause = 0.1f;
		res.pos.pause = 0.1f;
		return res;
	};
	auto parse_item = [&](std::string l) -> int
	{
		auto line = l;
		auto pos = line.find("(");

		line.erase(0, pos + 1);

		pos = line.find(")");
		line.erase(pos, line.size());

		return std::stoi(line);
	};
	this->grind.clear();
	std::ifstream v(this->pathname); std::string s;
	if (!v.is_open()) return;
	while (std::getline(v, s))
	{
		if (s.empty()) continue;
		if (strstr(s.c_str(), "(sp)"))
		{
			auto res = parse_storage(s);
			if (res.script != "NONE") { res.special_event = 1; res.pause = 1.2f; }
			if (res.npc_name != "NONE") { res.special_event = 1; res.pause = 8.0f; }
			if (res.pos.valid() && res.script.size() > 0) { this->store.push_back(res); continue; }
		}
		if (strstr(s.c_str(), "[gp]"))
		{
			/*grinding path line would look like __gp__1234_12__1234_12__28973007_dec */
			/*                                    head   x         y        z     pause  */
			auto res = parse_position(s);
			if (res.valid()) { this->grind.push_back(res); continue; }
			else { v.close(); return; }
			continue;
		}
		if (strstr(s.c_str(), "[item]"))
		{
			/*item whitelist line would look like __item__1234_1643616536_dec */
			/*                                      head  item idx*/
			auto res = parse_item(s);
			if (res != 0) { this->allowed_sell_items.push_back(res); continue; }
			else v.close(); return;
			continue;
		}
	}
	v.close();
	this->items_left_sell = this->allowed_sell_items;
	sdk::util::log->add(std::string("done load"), sdk::util::e_info, true);
}
void sys::c_legit_bot::save()
{
	std::ofstream p(this->pathname);
	if (!p.is_open()) return;
	for (auto a : this->grind)
	{
		if (a.pause > 0.1f && a.pause != 0.f) p << "[gp](" << a.x << ")(" << a.y << ")(" << a.z << ")(" << a.pause << ")\n";
		else p << "[gp](" << a.x << ")(" << a.y << ")(" << a.z << ")(" << 0.1f << ")\n";
	}
	for (auto a : this->store) p << "(sp){" << a.pos.x << "}{" << a.pos.y << "}{" << a.pos.z << "}{" << a.npc_name << "}{" << a.script << "}\n";
	for (auto a : this->allowed_sell_items)	p << "[item](" << a << ")\n";
	sdk::util::log->add("resaved path");
}
void sys::c_legit_bot::nav_to(const sdk::util::c_vector3& spos, sys::s_path_script& cur_point)
{
	//pot. per point trace validated nav (?)
	auto dst_to = sdk::util::math->gdst_2d(spos, cur_point.pos);
	if (dst_to > 150)
	{
		this->aim_pos(cur_point.pos, spos);
		uint64_t& input_adr = *((uint64_t*)(*((uint64_t*)(core::offsets::cl::client_base)) + 0x08));
		*((uint64_t*)((input_adr + 0x840) + (0x57 * 4))) = 1;
		return;
	}
	else
	{
		this->cur_route.pop_front();
	}
}
void sys::c_legit_bot::work(uint64_t s)
{
	this->self = s;
	if (this->recording_g || this->recording_s) { this->record(); return; }
	if (!this->dwork) return;
	if (!this->execution) this->execution = GetTickCount64() + 75;
	if (GetTickCount64() > this->execution) this->execution = GetTickCount64() + 75;
	else return;
	if (!sdk::player::player_->ghp(s)) return;
	if (this->gssize() && this->cur_route.empty() && this->ssp({}) && this->p_mode == 0)
	{
		this->repath(1, 1);
		this->p_mode = 1;
		this->force_store = false;
		sdk::util::log->add("should SP NOW", sdk::util::e_info, true);
	}
	if (!this->cur_route.size() && this->p_mode == 0) this->repath(0, 0);
	if (!this->cur_route.size() && this->p_mode == 1 && this->reversed)
	{
		//remove events
		this->repath(1, 0);
		for (auto a = 0; a < this->cur_route.size(); a++)
		{
			auto obj = this->cur_route[a];
			if (obj.special_event) this->cur_route.erase(this->cur_route.begin() + a);
		}
		sdk::util::log->add("repathed SP conform", sdk::util::e_info, true);
	}
	auto& input_adr = *((uint64_t*)(*((uint64_t*)(core::offsets::cl::client_base)) + 0x08));
	if (!input_adr) return;
	//
	this->autopot();
	sys::key_q->bypass();
	//
	auto spos = sdk::player::player_->gpos(s);
	auto cur_point = this->cur_route.front();
	if (this->p_mode == 1)
	{
		if (this->sp_delay > GetTickCount64()) return; else sp_delay = 0;
		if (this->reversed)//path to
		{
			if (cur_point.special_event)
			{
				if (cur_point.npc_name != "NONE")//npc
				{
					if (this->has_aggro()) return;
					sp_delay = GetTickCount64() + 2400;
					sdk::util::log->add(cur_point.npc_name, sdk::util::e_info, true);

					std::string npc_wanted = ""; uint64_t npc_wanted_ptr = 0;
					for (auto b : this->store) if (b.npc_name != "NONE") { npc_wanted = b.npc_name; break; }
					for (auto b : sdk::player::player_->npcs) if (strstr(b.name.c_str(), npc_wanted.c_str())) { npc_wanted_ptr = b.ptr; break; }

					this->f_npc_interaction(npc_wanted_ptr);
					auto cinteract = *(uint64_t*)(core::offsets::actor::interaction_current);
					if (!cinteract || cinteract != npc_wanted_ptr) return;

					sys::cursor_tp->set_pos(s, sdk::util::c_vector3(cur_point.pos.x / 100, cur_point.pos.y / 100, cur_point.pos.z / 100));
					this->cur_route.pop_front();
					return;
				}
				else if (cur_point.script != "NONE")//scr
				{
					if (this->npc_interacted)
					{
						if (!sdk::player::player_->npcs.size())
						{
							sdk::util::log->add("no npc near, after interaction - stopping bot (???)", sdk::util::e_critical, true);
							this->dwork = false;
							return;
						}
						std::string npc_wanted = ""; uint64_t npc_wanted_ptr = 0;
						for (auto b : this->store) if (b.npc_name != "NONE") { npc_wanted = b.npc_name; break; }
						for (auto b : sdk::player::player_->npcs) if (strstr(b.name.c_str(), npc_wanted.c_str())) { npc_wanted_ptr = b.ptr; break; }
						auto cinteract = *(uint64_t*)(core::offsets::actor::interaction_current);
						if (cinteract != npc_wanted_ptr)
						{
							//aborted sp due to something (?)
							sp_delay = GetTickCount64() + 8000;
							this->npc_interacted = false;
							//allow for roar and repath for only scripts
							this->cur_route.clear();
							this->cur_route = this->store;
							while (true)
							{
								if (this->cur_route.front().special_event) break;
								this->cur_route.pop_front();
							}
							this->i_sell_state = 0;
							this->items_left_sell = this->allowed_sell_items;
							sdk::util::log->add("sp interaction was aborted (?)");
							return;
						}
					}
					this->npc_interacted = true;
					sp_delay = GetTickCount64() + 2000;
					if (cur_point.script == "sell_routine()")
					{
						auto ctrl = *(uint64_t*)(this->self + core::offsets::actor::actor_char_ctrl);
						if (!ctrl) return;
						auto scene = *(uint64_t*)(ctrl + core::offsets::actor::actor_char_scene);
						if (!scene) return;
						auto speed = *(float*)(scene + core::offsets::actor::actor_animation_speed);
						if (speed >= 8000.f) *(float*)(scene + core::offsets::actor::actor_animation_speed) = 1.f;

						if (this->i_sell_state == 3 && !this->items_left_sell.empty())
						{
							for (auto a : sdk::player::player_->inventory_items)
							{
								if (a.item_index == this->items_left_sell.back())
								{
									this->i_sell_state = 0; //wasnt sold
									sdk::util::log->add("failed last sell", sdk::util::e_info, true);
									return;
								}
							}
							this->items_left_sell.pop_back();
							this->i_sell_state = 0;
							sdk::util::log->add("next item", sdk::util::e_info, true);
						}
						if (this->i_sell_state == 3 && this->items_left_sell.empty())//end state
						{
							this->items_left_sell = this->allowed_sell_items;

							sdk::util::log->add(cur_point.script, sdk::util::e_info, true);
							this->cur_route.pop_front();
							sdk::util::log->add("items sold", sdk::util::e_info, true);

							return;
						}
						auto t = this->items_left_sell.back();
						switch (this->i_sell_state)
						{
						case 0:
						{
							for (auto a : sdk::player::player_->inventory_items)
							{
								if (a.item_index == t)
								{
									auto _t = std::string("HandleEventRUp_Inventory_All_SlotRClick(").append(std::to_string(a.item_slot)).append(")");
									sys::lua_q->add(_t);
									this->i_sell_state++;
									return;
								}
							}
							sdk::util::log->add(std::string("item not found: ").append(std::to_string(t)), sdk::util::e_info, true);
							this->i_sell_state = 3;
							return;
						}
						case 1:
						{
							sys::lua_q->add("HandleEventLUp_NumberPad_All_AllButton_Click(0)");
							this->i_sell_state++;
							return;
						}
						case 2:
						{
							sys::lua_q->add("HandleEventLUp_NumberPad_All_ConfirmButton_Click()");
							this->i_sell_state++;
							return;
						}
						}
					}
					sdk::util::log->add(cur_point.script, sdk::util::e_info, true);
					sys::lua_q->add(cur_point.script);
					this->cur_route.pop_front();
					return;
				}
			}
			else
			{
				auto dst_to = sdk::util::math->gdst_2d(spos, cur_point.pos);
				if (dst_to > 100)
				{
					this->aim_pos(cur_point.pos, spos);
					if (!sys::key_q->thread_working) sys::key_q->add(new sys::s_key_input({ 0x57 }, 500));
					return;
				}
				//sys::cursor_tp->set_pos(s, sdk::util::c_vector3(cur_point.pos.x / 100, cur_point.pos.y / 100, cur_point.pos.z / 100));
				this->cur_route.pop_front();
				return;
			}
		}
		else//path back
		{
			auto dst_to = sdk::util::math->gdst_2d(spos, cur_point.pos);
			if (dst_to > 100)
			{
				this->aim_pos(cur_point.pos, spos);
				if (!sys::key_q->thread_working) sys::key_q->add(new sys::s_key_input({ 0x57 }, 500));
				return;
			}
			this->npc_interacted = false;
			this->cur_route.pop_front();
			if (this->cur_route.empty())
			{
				this->p_mode = 0;
				this->repath(0, 0);
				sdk::util::log->add("completed SP", sdk::util::e_info, true);
				this->npc_interacted = false;
			}
		}
		return;
	}
	if (this->p_mode == 0 && cur_point.pos.pause > 1.1f)
	{
		auto has_mobs = this->mobs_near(cur_point.pos, spos);
		if (!has_mobs)
		{
			this->cur_route.front().pos.pause = 0.1f;
			this->target_actor = {};
			this->execution = GetTickCount64() + 1000;
			return;
		}
		if (this->target_actor.ptr == NULL)
		{
			auto n = this->nearest(cur_point.pos, spos, 800);
			if (n.ptr == NULL)
			{
				*((uint64_t*)((input_adr + 0x840) + (0x57 * 4))) = 0;
				this->cur_route.front().pos.pause = 0.1f;
				this->target_actor = {};
				this->execution = GetTickCount64() + 1000;
				return;
			}
			this->target_actor = n;
			return;
		}
		else
		{
			auto u = this->update_target();
			if (u)
			{
				if (this->target_actor.rlt_dst > 300)
				{
					this->aim_pos(this->target_actor.pos, spos);
					*((uint64_t*)((input_adr + 0x840) + (0x57 * 4))) = 1;
					return;
				}
				else
				{
					*((uint64_t*)((input_adr + 0x840) + (0x57 * 4))) = 0;
					this->aim_pos(this->target_actor.pos, spos);
					this->rskill();
					return;
				}
			}
			else
			{
				*((uint64_t*)((input_adr + 0x840) + (0x57 * 4))) = 0;
				this->target_actor = {};
				this->execution = GetTickCount64() + 1000;
				return;
			}
		}
	}
	nav_to(spos, cur_point);
}
sys::c_legit_bot* sys::legit_bot;