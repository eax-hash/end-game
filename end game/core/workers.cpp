#include <inc.h>
void core::core_cheat_worker()
{
	while (1337)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		auto self = *(uint64_t*)(core::offsets::actor::actor_self);
		if (!self) { sdk::player::player_->thread_working = 0; return; }
		auto playable = *(BYTE*)(self + core::offsets::actor::actor_can_play);
		if (!playable) { sdk::player::player_->thread_working = 0; return; }
		sdk::player::player_->update_actors(self);
	}
}
std::string core::get_vtable_name(uint64_t address)
{
	uint64_t base = 0x140000000;
	auto negated = address -= 0x8;

	if (negated == NULL) return "";
	negated = *(uint64_t*)(negated);

	if (!negated || negated >= 0x14fffffff) return "";

	auto step_int2 = *(int*)(negated + 0x10);
	if (!step_int2 || step_int2 >= 0x14fffffff) return "";

	auto tmp = base + step_int2;

	auto step_int3 = *(int*)(tmp + 0xC);
	if (!step_int3 || step_int3 >= 0x14fffffff) return "";

	tmp = base + step_int3;
	auto step_int4 = *(int*)(tmp + 0x0);
	if (!step_int4 || step_int4 >= 0x14fffffff) return "";

	tmp = base + step_int4;
	auto step_int5 = *(int*)(tmp + 0x0);
	if (!step_int5 || step_int5 >= 0x14fffffff) return "";

	tmp = base + step_int5;
	auto string = *(N00001055*)(tmp);

	auto tmp2 = std::string(string.N00001058);

	auto pos = tmp2.find("AV");
	tmp2.erase(0, pos + 2);

	pos = tmp2.find("@");
	tmp2.erase(pos, tmp2.size());

	return tmp2;
}
