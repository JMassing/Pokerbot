#pragma once

#include <string>
#include <imgui.h>

namespace gui {

	class MainMenuBar
	{
				
		public:
			
            bool show_settings_win_;
            bool show_live_image_;
            bool show_card_image_;
            bool show_rank_image_;
            bool show_suit_image_;
            bool show_poker_win_;

			void draw();

			MainMenuBar(): 
                show_settings_win_(true),
                show_live_image_(true),
                show_rank_image_(true),
                show_suit_image_(true),
                show_poker_win_(true),
                show_card_image_(true)
            {};
			virtual ~MainMenuBar() {};

			// Using default copy and move constructors. 
			MainMenuBar(const MainMenuBar& other) = default;	
			MainMenuBar& operator=(const MainMenuBar& other) = default;
			MainMenuBar(MainMenuBar&& other) noexcept = default;
			MainMenuBar& operator=(MainMenuBar&& other) noexcept = default;
	};
} // namespace gui


