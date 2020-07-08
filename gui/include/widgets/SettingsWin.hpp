#pragma once

#include <memory>

#include "IWindow.hpp"
#include "LayoutConfig.hpp"
#include "DefaultConfig.h"
#include "Button.hpp"
#include "Slider.hpp"
#include "InputField.hpp"
#include "CameraSettings.hpp"
#include "ImProcSettings.hpp"

namespace gui {

	class SettingsWin: public IWindow
	{
		private:
		
			bool show_ask_for_save_;
			shared::DefaultConfig& default_config_;
			Slider slider_;
			Button button_;
			InputField input_;	

			// Slider Constraints
			// Layout
			const int card_image_height_ = 150;
			const int card_rank_suit_height_ = 50;
			const int min_card_image_height_percent_ = 25; 
			const int max_card_image_height_percent_ = 175; 
			const int min_rank_suit_image_height_percent_ = 25; 
			const int max_rank_suit_image_height_percent_ = 175; 
			// Camera Control
			const int max_exp_time_ = -1;
       		const int min_exp_time_ = -12;
        	const int max_focus_ = 250;
        	const int min_focus_ = 0;
        	const int max_brightness_ = 255;
        	const int min_brightness_ = 0;
			// Image Processing
			const int max_live_th_ = 255;
        	const int min_live_th_ = 0;
        	const int max_bin_th_ = 255;
        	const int min_bin_th_ = 0;
        	const int max_ident_th_ = 255;
        	const int min_ident_th_ = 0;
			// Poker Simulation
			const int min_players_ = 1;
        	const int max_players_ = 9;
			const int max_sim_runs_ = 100000;
        	const int min_sim_runs_ = 0;

			void setConfigToDefault();
			void saveConfigAsDefault();
		
		public:			
			// User Inputs
			// Layout
			LayoutConfig layout_settings_;

			//Camera Controls
		 	capture::CameraSettings camera_settings_;

			//Image Processing
			detect::ImProcSettings proc_settings_;

			//Poker Simulation
			int nr_of_simulation_runs_;
			int nr_of_human_players_;
		
			bool draw() override;

			SettingsWin(
				const std::string& name, 
				shared::DefaultConfig& default_config, 
				const capture::CameraSettings& camera_settings, 
				const LayoutConfig& layout_settings,
				const detect::ImProcSettings& proc_settings,
				const int& flag = 0
				):
				IWindow(name, flag), 
				default_config_(default_config), 
				show_ask_for_save_(false),
				slider_{}, 
				button_{}, 
				layout_settings_{layout_settings},
				camera_settings_(camera_settings), 
				proc_settings_(proc_settings),
				nr_of_simulation_runs_(10000), 
				nr_of_human_players_(1) 
			{};

			virtual ~SettingsWin() {};

			// Using default copy and move constructors. 
			SettingsWin(const SettingsWin& other) = default;	
			SettingsWin& operator=(const SettingsWin& other) = default;
			SettingsWin(SettingsWin&& other) noexcept = default;
			SettingsWin& operator=(SettingsWin&& other) noexcept = default;
	};

} // namespace gui

