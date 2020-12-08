#include <iostream>
#include <memory>

#include "CameraController.hpp"
#include "GuiContext.hpp"
#include "Game.hpp"
#include "CardDetector.hpp"
#include "GameSettings.hpp"
#include "Interfaces.hpp"
#include "DataStructures.hpp"
#include "GuiWindows.hpp"

using namespace cv;
using namespace std;
using namespace detect;
using namespace poker;
using namespace gui;
using namespace capture;


int main(int argc, char* argv[])
{

	// Read intial settings from config.ini	
	unique_ptr<DefaultConfig> default_settings = 
		make_unique<DefaultConfig>();

	// ------- Set up Modules and Interfaces -----------------------------------
	
	// ------- Capture module --------------------------------------------------
	// intial camera settings
	unique_ptr<CameraSettings> camera_settings =
		make_unique<CameraSettings>();
	camera_settings->setToDefault(*default_settings);

	// Camera Control and Interfaces
	CameraController cam_controller(default_settings->device_ID);

	// Set up capture detection interface
	shared_ptr<CaptureDetectInterface> cam_detect_interface = 
		make_shared<CaptureDetectInterface>(cam_controller.frame_);

	// Initialize Camera
	if (!cam_controller.initCamera(*camera_settings)) {
		cerr << "ERROR! Unable to open camera\n";
		return -2;
	}	

	// ------ Detection Module -------------------------------------------------
	// Initial processing settings
	unique_ptr<ImProcSettings> proc_settings =
		make_unique<ImProcSettings>();
	proc_settings->setToDefault(*default_settings);

	// Set Up detection process and connect to capture input
	CardDetector card_detector(*proc_settings);

	// Interface to Poker Module
	shared_ptr<DetectPokerInterface> detect_poker_interface = 
		make_shared<DetectPokerInterface>(card_detector.data_);

	
	// ----- Poker Module ------------------------------------------------------
	// initial simulation settings
	unique_ptr<GameSettings> sim_settings =
		make_unique<GameSettings>();
	sim_settings->setToDefault(*default_settings);

	// MonteCarlo Simulation
	Game game(*sim_settings);

	// Interface to Detection module
	game.attachDetectInterface(detect_poker_interface);

	// ----- GUI Module --------------------------------------------------------
	// Initial GUI layout
	unique_ptr<LayoutConfig> layout_settings =
		make_unique<LayoutConfig>();
	layout_settings->setToDefault(*default_settings);

	// Set Up Gui and Widget
	GuiContext gui{};
	gui.init();

	MainMenuBar main_menu{};

	// Set Up Window for User Input
	SettingsWin settings_window(
		"Settings", 
		main_menu.show_settings_win_,
		*default_settings, 
		*camera_settings,
		*layout_settings,
		*proc_settings,
		*sim_settings,
		cam_controller.getBackend()
		);
	
	// SetUp GUI Interfaces to modules
	// Interface to detection module
	shared_ptr<GuiDetectionInterface> gui_detection_interface =
		std::make_shared<GuiDetectionInterface> (
			settings_window.proc_settings_,
			settings_window.input_
			);

	// Interface to Capture module
	shared_ptr<GuiCaptureInterface> gui_capture_interface =
		std::make_shared<GuiCaptureInterface> (
			settings_window.camera_settings_,
			settings_window.input_
			);
	cam_controller.attachGuiInterface(gui_capture_interface);	

	// Interface to Poker module
	shared_ptr<GuiPokerInterface> gui_poker_interface =
		std::make_shared<GuiPokerInterface> (
			settings_window.game_settings_,
			settings_window.input_
			);
	game.attachGuiInterface(gui_poker_interface);		
	
	// SetUp GUI Windows for presentation
	LiveImageWin live_view(
		"Live View", 
		main_menu.show_live_image_,
		settings_window.layout_settings_, 
		gui_capture_interface->live_image_, 
		gui_detection_interface->cards_,
		gui_poker_interface,
		ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize
		);	

	CardImageWin card_view(
		"Card Images", 
		main_menu.show_card_image_,
		settings_window.layout_settings_, 
		gui_detection_interface->cards_,
		gui_poker_interface,
		ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize
		);	
	
	RankImageWin rank_view(
		"Rank Images", 
		main_menu.show_rank_image_,
		settings_window.layout_settings_, 
		gui_detection_interface->cards_,
		gui_poker_interface,
		ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize
		);	
	
	SuitImageWin suit_view(
		"Suit Images", 
		main_menu.show_suit_image_,
		settings_window.layout_settings_, 
		gui_detection_interface->cards_,
		gui_poker_interface,
		ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize
		);	

	PokerWin poker_win(
		"Game Win", 
		main_menu.show_poker_win_,
		settings_window.layout_settings_, 
		gui_poker_interface,
		ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize
		);

	// Free Initialization Data Structures
	default_settings.release();
	camera_settings.release();
	proc_settings.release();
	sim_settings.release();
	layout_settings.release();

	// ------ Data Handlers --------------------------------------------------
	// Detection
	unique_ptr<DetectionDataHandler> detection_data_handler = 
		make_unique<DetectionDataHandler>();
	// Input from capture modlue giving live frame
	detection_data_handler->attachCaptureInterface(cam_detect_interface);
	detection_data_handler->attachGuiInterface(gui_detection_interface);	
	card_detector.attachDataHandler(std::move(detection_data_handler));


	// ------ Run Pokerbot ----------------------------------------------------
	while( !gui.shouldClose() )
	{
		for (;;)
		{
			// Grab live frame and check if it worked
			if (!cam_controller.grabLive())
			{ 
				// set gui state to should_close_ = true and exit for loop
				gui.closeWindow();
				break;
			}		
						
			// Detect Cards in Frame and notify other modules
			card_detector.detectCards();

			// run simulation
			game.play();
								
			// Draw Gui Frame
			gui.drawGuiFrame();

			//draw Windows
			settings_window.draw();
			main_menu.draw();
			live_view.draw();
			card_view.draw();
			rank_view.draw();
			suit_view.draw();
			poker_win.draw();

			gui.render();
	
			if (gui.shouldClose())
			{
					break;
			}
		}
	}

// the camera will be deinitialized automatically in VideoCapture destructor
// the GUI will be deinitialized automatically in GUI destructor
}
