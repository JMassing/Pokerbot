#pragma once

#include <memory>

#include "IWindow.h"
#include "LayoutConfig.h"
#include "DefaultConfig.h"
#include "ISubject.h"
#include "Button.h"
#include "Slider.h"
#include "Input.h"
#include "CameraControls.h"

namespace gui {

	class ControlsWin: public IWindow, public interfaces::ISubject
	{
		private:
		
			bool show_ask_for_save_;
			shared::DefaultConfig& default_config_;
			Slider slider_;
			Button button_;
			Input input_;	

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
			int live_view_height_; 
        	int live_view_width_;
        	int card_image_height_percent_;
        	int card_rank_suit_height_percent_;
        	cv::Scalar card_outline_color_; 

			//Camera Controls
		 	shared::CameraControls& camera_settings_;

			//Image Processing
			int live_threshold_;            // threshold for finding cards in live image 
        	int binary_threshold_;          // threshold for binaryzing suit and rank image;
        	int identification_threshold_;  // threshold for finding the rank and suit in the card image 

			//Poker Simulation
			int nr_of_simulation_runs_;
			int nr_of_human_players_;
		
			bool draw() override;

			ControlsWin(const std::string& name, shared::DefaultConfig& default_config, shared::CameraControls& camera_settings, const int& flag = 0):
				IWindow(name, flag), default_config_(default_config), show_ask_for_save_(false),
				slider_{}, button_{}, live_view_height_(780), live_view_width_(1024),
				card_image_height_percent_(0), card_rank_suit_height_percent_(0), card_outline_color_{255, 0, 0}, camera_settings_(camera_settings), 
				live_threshold_(100), binary_threshold_(100), identification_threshold_(100), nr_of_simulation_runs_(10000), nr_of_human_players_(1) 
				{};
			virtual ~ControlsWin() {};

			// Using default copy and move constructors. 
			ControlsWin(const ControlsWin& other) = default;	
			ControlsWin& operator=(const ControlsWin& other) = default;
			ControlsWin(ControlsWin&& other) noexcept = default;
			ControlsWin& operator=(ControlsWin&& other) noexcept = default;
	};

} // namespace gui

