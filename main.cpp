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

	// Initialization phase
	
	// Set Up Intitalization for Data Structures and set them to default values	
	unique_ptr<DefaultConfig> default_settings = 
		make_unique<DefaultConfig>();

	unique_ptr<CameraSettings> camera_settings =
		make_unique<CameraSettings>();
	camera_settings->setToDefault(*default_settings);

	unique_ptr<ImProcSettings> proc_settings =
		make_unique<ImProcSettings>();
	proc_settings->setToDefault(*default_settings);

	unique_ptr<SimSettings> sim_settings =
		make_unique<SimSettings>();
	sim_settings->setToDefault(*default_settings);

	unique_ptr<LayoutConfig> layout_settings =
		make_unique<LayoutConfig>();
	layout_settings->setToDefault(*default_settings);


	// Set up Modules and Interfaces
	// Camera Control and Interfaces
	shared_ptr<CameraController> cam_controller = 
		make_shared<CameraController>(default_settings->device_ID);

	if (!cam_controller->initCamera(*camera_settings)) {
		cerr << "ERROR! Unable to open camera\n";
		return -2;
	}	

	// Set up capture output interface
	CaptureOutput cam_output(cam_controller->frame_);

	// Live image input to GUI for live view
	shared_ptr<GuiCaptureInput> gui_capture_input = 
		make_shared<GuiCaptureInput>(cam_output);
	cam_output.attach(gui_capture_input);
		
	// User Input from GUI to Cam Controller
	GuiCaptureOutput gui_capture_output(*camera_settings);
	shared_ptr<CaptureGuiInput> capture_gui_input =
		 make_shared<CaptureGuiInput>(gui_capture_output);
	capture_gui_input->connectCameraDevice(cam_controller);
	gui_capture_output.attach(capture_gui_input);

	
	// Detection Module and Interfaces
	// User Input from GUI to detection module
	GuiDetectionOutput gui_detection_output{*proc_settings};
	shared_ptr<DetectGuiInput> detect_gui_input =
		make_shared<DetectGuiInput>(gui_detection_output, *proc_settings);
	gui_detection_output.attach(detect_gui_input);

	// Set Up detection process and connect to capture input
	shared_ptr<CardDetector> card_detector = 
		make_shared<CardDetector> (detect_gui_input->im_proc_settings_);
	
	// Detection output to GUI giving card images
	DetectGuiOutput detect_gui_output{};
	detect_gui_output.connectCardDetector(card_detector);
	shared_ptr<GuiDetectionInput> gui_detect_input =
		make_shared<GuiDetectionInput> (detect_gui_output);
	detect_gui_output.attach(gui_detect_input);
	
	// Input from capture modlue giving live frame
	shared_ptr<DetectCaptureInput> detect_capture_input = 
		make_shared<DetectCaptureInput>(cam_output);
	cam_output.attach(detect_capture_input);
	detect_capture_input->connectCardDetector(card_detector);

	// Output to Poker Module
	DetectPokerOutput detect_poker_output(card_detector->data_);


	// Poker Module
	// User Input from GUI to poker process
	GuiPokerOutput gui_poker_output(*sim_settings);
	shared_ptr<PokerGuiInput> poker_gui_input =
		make_shared<PokerGuiInput> (gui_poker_output, *sim_settings);
	gui_poker_output.attach(poker_gui_input);

	// Input from Detection Module
	shared_ptr<PokerDetectInput> poker_detect_input = 
		make_shared<PokerDetectInput> (detect_poker_output);
	detect_poker_output.attach(poker_detect_input);

	// MonteCarlo Simulation
	Simulation sim(poker_gui_input->sim_settings_, poker_detect_input->data_);

	// Output to GUI
	PokerOutput poker_output{sim.data_};
	shared_ptr<GuiPokerInput>gui_poker_input = 
		make_shared<GuiPokerInput>(poker_output);
	poker_output.attach(gui_poker_input);


	// Set Up Gui and Widgets
	GuiContext gui{};
	gui.init();

	SettingsWin settings_window(
		"Settings", 
		*default_settings, 
		*camera_settings,
		*layout_settings,
		*proc_settings,
		*sim_settings
		);
	
	LiveImageWin live_view(
		"Live View", 
		settings_window.layout_settings_, 
		gui_capture_input->frame_, 
		gui_detect_input->cards_,
		ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize
		);	

	CardImageWin card_view(
		"Card Images", 
		settings_window.layout_settings_, 
		gui_detect_input->cards_,
		ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize
		);	
	
	RankImageWin rank_view(
		"Rank Images", 
		settings_window.layout_settings_, 
		gui_detect_input->cards_,
		ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize
		);	
	
	SuitImageWin suit_view(
		"Suit Images", 
		settings_window.layout_settings_, 
		gui_detect_input->cards_,
		ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize
		);	

	PokerWin poker_win(
		"Simulation Results", 
		gui_poker_input->data_,
		ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize
		);

	// Free Initialization Data Structures
	default_settings.release();
	camera_settings.release();
	proc_settings.release();
	sim_settings.release();
	layout_settings.release();

	// Real time Phase
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

			// Send live frame to gui and detection modules
			cam_output.notify();			

			// Detect Cards in Frame and notify other modules
			card_detector->detectCards();
			detect_gui_output.notify();
			detect_poker_output.notify();

			// run simulation
			sim.run();
			poker_output.notify();
								
			// Draw Gui
			gui.drawGuiFrame();

			live_view.draw();

			bool input = settings_window.draw();

			gui_capture_output.checkForUserInput(
				input, 
				settings_window.camera_settings_
				);	

			gui_detection_output.checkForUserInput(
				input,
				settings_window.proc_settings_
				);	

			gui_poker_output.checkForUserInput(
				input,
				settings_window.sim_settings_
				);			

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
