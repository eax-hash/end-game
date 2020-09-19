#include <inc.h>
void sdk::menu::c_menu::work()
{
	ImGui_ImplDX11_NewFrame();
	//
	if (!this->was_setup)
	{
		ImGui::StyleColorsDark();
		this->was_setup = true;
	}
	if (!this->menu_active) return;
	ImGui::Begin("packet-manager", 0, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize);
	{
		static auto ibypass_trial = sys::config->gvar("packet", "ibypass_trial");
		static auto iteleport_gen2 = sys::config->gvar("packet", "iteleport_gen2");
		static auto ientity_update = sys::config->gvar("debug", "ientity_update");

		ImGui::Checkbox("Entity updates", (bool*)&ientity_update->iv);
		ImGui::Checkbox("Trial bypass", (bool*)&ibypass_trial->iv);

		ImGui::Checkbox("TGEN2", (bool*)&iteleport_gen2->iv); ImGui::SameLine();
		ImGui::Checkbox("Setup TGEN2", &sys::pack_tp->get_packet_again);
		if (iteleport_gen2->iv && !sys::pack_tp->get_packet_again) if (ImGui::Button("TGEN2 to marker")) sys::pack_tp->teleport_to_marker();

		//
		ImGui::Text(std::string("Proxies:").append(std::to_string(sdk::player::player_->actors.size())).c_str());
		ImGui::Text(std::string("DeadActors:").append(std::to_string(sdk::player::player_->corpses.size())).c_str());

		ImGui::End();
	}
	//
	ImGui::Render();
}
void sdk::menu::c_menu::sactive()
{
	this->menu_active = !this->menu_active;
}
sdk::menu::c_menu* sdk::menu::menu;