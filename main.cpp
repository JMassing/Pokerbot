#include <iostream>
#include <memory>

#include "CameraController.hpp"
#include "GuiContext.hpp"
#include "Simulation.hpp"
#include "CardDetector.hpp"
#include "SimSettings.hpp"
#include "Interfaces.hpp"
#include "DataStructures.hpp"
#include "GuiWindows.hpp"

using namespace cv;
using namespace std;
using namespace detect;
using namespace poker;
using namespace gui;
using namespace shared;
using namespace capture;


int main(int argc, char* argv[])
{

	// Read default settings from config.ini	
	unique_ptr<DefaultConfig> default_settings = 
		make_unique<DefaultConfig>();

	// ------- Set up Modules and Interfaces -----------------------------------
	
	// ------- Capture module --------------------------------------------------
	// intial camera settings
	unique_ptr<CameraSettings> camera_settings =
		make_unique<CameraSettings>();
	camera_settings->setToDefault(*default_settings);

	// Camera Control and Interfaces
	shared_ptr<CameraController> cam_controller = 
		make_shared<CameraController>(default_settings->device_ID);

	// Set up capture output interface
	shared_ptr<CaptureDetectOutput> cam_detect_in = 
		make_shared<CaptureDetectOutput>(cam_controller->frame_);

	// Initialize Camera
	if (!cam_controller->initCamera(*camera_settings)) {
		cerr << "ERROR! Unable to open camera\n";
		return -2;
	}	

	// ------ Detection Module -------------------------------------------------
	// Initial processing settings
	unique_ptr<ImProcSettings> proc_settings =
		make_unique<ImProcSettings>();
	proc_settings->setToDefault(*default_settings);

	// Set Up detection process and connect to capture input
	shared_ptr<CardDetector> card_detector = 
		make_shared<CardDetector> (*proc_settings);
	
	// Input from capture modlue giving live frame
	card_detector->attachCaptureInterface(cam_detect_in);

	// Output to Poker Module
	shared_ptr<DetectPokerOutput> detect_poker_in = 
		make_shared<DetectPokerOutput>(card_detector->data_);

	
	// ----- Poker Module ------------------------------------------------------
	// initial simulation settings
	unique_ptr<SimSettings> sim_settings =
		make_unique<SimSettings>();
	sim_settings->setToDefault(*default_settings);

	// MonteCarlo Simulation
	Simulation sim(*sim_settings);

	// Interface to Detection module
	sim.attachDetectInterface(detect_poker_in);

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
		*sim_settings
		);
	
	// SetUp GUI Interfaces to modules
	// Interface to detection module
	shared_ptr<GuiDetectionIO> gui_detection_io =
		std::make_shared<GuiDetectionIO> (
			settings_window.proc_settings_,
			settings_window.input_
			);
	card_detector->attachGuiInterface(gui_detection_io);	

	// Interface to Capture module
	shared_ptr<GuiCaptureIO> gui_capture_io =
		std::make_shared<GuiCaptureIO> (
			settings_window.camera_settings_,
			settings_window.input_
			);
	cam_controller->attachGuiInterface(gui_capture_io);	

	// Interface to Poker module
	shared_ptr<GuiPokerIO> gui_poker_io =
		std::make_shared<GuiPokerIO> (
			settings_window.sim_settings_,
			settings_window.input_
			);
	sim.attachGuiInterface(gui_poker_io);		
	
	// SetUp GUI Windows for presentation
	LiveImageWin live_view(
		"Live View", 
		main_menu.show_live_image_,
		settings_window.layout_settings_, 
		gui_capture_io->live_image_, 
		gui_detection_io->cards_,
		ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize
		);	

	CardImageWin card_view(
		"Card Images", 
		main_menu.show_card_image_,
		settings_window.layout_settings_, 
		gui_detection_io->cards_,
		ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize
		);	
	
	RankImageWin rank_view(
		"Rank Images", 
		main_menu.show_rank_image_,
		settings_window.layout_settings_, 
		gui_detection_io->cards_,
		ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize
		);	
	
	SuitImageWin suit_view(
		"Suit Images", 
		main_menu.show_suit_image_,
		settings_window.layout_settings_, 
		gui_detection_io->cards_,
		ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize
		);	

	PokerWin poker_win(
		"Simulation Results", 
		main_menu.show_poker_win_,
		gui_poker_io->data_,
		ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize
		);


	// Free Initialization Data Structures
	default_settings.release();
	camera_settings.release();
	proc_settings.release();
	sim_settings.release();
	layout_settings.release();


	// ------ Run Pokerbot ----------------------------------------------------
	while( !gui.shouldClose() )
	{
		for (;;)
		{
			// Grab live frame and check if it worked
			if (!cam_controller->grabLive())
			{ 
				// set gui state to should_close_ = true and exit for loop
				gui.closeWindow();
				break;
			}			

			// Detect Cards in Frame and notify other modules
			card_detector->detectCards();

			// run simulation
			sim.run();
								
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
