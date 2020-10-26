#pragma once
#include <inc.h>
namespace sdk
{
	namespace dialog
	{
		struct s_thread_p
		{
			std::string npc = "";
			std::vector<int> items = {};
		};
		class str_btn
		{
		public:
			wchar_t str_btn_[64]; //0x0000 
		};
		typedef const char* (__fastcall* t_gettext)(uint64_t);
		typedef uint64_t(__fastcall* t_getdialog)(uint64_t, int);
		class c_dialog
		{
		private:
			t_gettext	gettext = (t_gettext)core::offsets::fn::dialog_gettext;
			t_getdialog getdialog = (t_getdialog)core::offsets::fn::dialog_getbutton;
		public:
			bool thread_running = false, completed_sales = false;
			ULONGLONG last_execution = 0, last_click_time = 0; bool	needs_numberpad = 0; int item_id = 0; bool did_click = false; bool did_select_max = false; bool did_select_confirm = false;

			int			sell_state = 0;
			std::unordered_map<std::string, std::string>	core_dialogs =
			{
				{"NPC_Interaction",	"Panel_Npc_Dialog_All"},
				{"Repair",			"Panel_Dialog_Repair_Function_All"},
				{"Shop",			"Panel_Dialog_NPCShop_All"},
				{"Storage",			"Panel_Window_Warehouse"},
				{"MessageBox",		"Panel_Window_MessageBox_All"},
				{"NumberPad",		"Panel_Window_NumberPad_All"}
			};
			/*
			notes:

			store/sell routine:

			> interaction selection:
				> user slects NPC name
					> bot checks for NPC_Interaction presence in root panels
			> dialog selection:
				> user selects button by it's displayed name in the menu
					> menu translates it to RadioButton_Func.... (internal name) and saves that for the script action
						> bot looks up RadioButton_Func.... from the core_buttons list and executes the button by given ID
			> in dialog selection:
				> for selling & storage:
					> user selects the action wanted to be performed such as: SellStore()
						> pre-defined bot function: SellStore() requires a item list to be present, processes all items owned by player
			> end of interaction:
				> menu will detect the selection of dialog option, automatically add the Exit button parameter (find exit button from a list of known buttons)
					> saves changes made to path and reloads
			*/
			std::unordered_map<int, std::string>			buttons_map = {};
			std::unordered_map<std::string, bool>			panels_map = {};
			std::unordered_map<std::string, std::string>	children_by_panel = {};
			bool gbuttons();
			bool gpanels();
			bool gchildren(std::string panel); 
			//
			std::string find_button(std::string display_name, std::string panel);
			bool		find_panel(std::string panel);
			//
			void		sell_reset()
			{
				this->did_click = false;
				this->did_select_confirm = false;
				this->did_select_max = false;
				this->needs_numberpad = false;
				this->sell_state = 0; 
			};
			bool		sell_test(int id);
		};
		extern c_dialog* dialog;
		extern void __stdcall do_sell(void* p);

	}
}