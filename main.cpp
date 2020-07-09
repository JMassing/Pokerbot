#include <iostream>
#include <memory>

#include "CameraController.hpp"
#include "GuiContext.hpp"
#include "Simulation.hpp"
#include "ImProcSettings.hpp"
#include "DataPoker.hpp"
#include "DataDetect.hpp"
#include "CameraSettings.hpp"
#include "SettingsWin.hpp"
#include "LiveImageWin.hpp"
#include "CardImageWin.hpp"
#include "RankImageWin.hpp"
#include "SuitImageWin.hpp"
#include "GuiCaptureOutput.hpp"
#include "CaptureGuiInput.hpp"
#include "CaptureOutput.hpp"
#include "GuiCaptureInput.hpp"
#include "LayoutConfig.hpp"
#include "DetectCaptureInput.hpp"
#include "DetectGuiInput.hpp"
#include "GuiDetectionOutput.hpp"
#include "CardDetector.hpp"
#include "DetectGuiOutput.hpp"
#include "GuiDetectionInput.hpp"
#include "PokerDetectInput.hpp"
#include "DetectPokerOutput.hpp"
#include "SimSettings.hpp"
#include "PokerOutput.hpp"
#include "GuiPokerInput.hpp"
#include "PokerWind.hpp"

using namespace cv;
using namespace std;
using namespace detect;
using namespace poker;
using namespace gui;
using namespace shared;
using namespace capture;


int main(int argc, char* argv[])
{
	
	DefaultConfig default_settings{};

	// Set up Camera	

    CameraSettings camera_settings{};
	camera_settings.setToDefault(default_settings);

	shared_ptr<CameraController> cam_controller = make_shared<CameraController>(1);

	if (!cam_controller->initCamera(camera_settings)) {
		cerr << "ERROR! Unable to open camera\n";
		return -2;
	}	

	// Set up capture output interface
	CaptureOutput cam_output(cam_controller->frame_);

	// Set Up Detecion interfaces
	ImProcSettings proc_settings{};
	proc_settings.setToDefault(default_settings);

	GuiDetectionOutput gui_detection_output{proc_settings};

	shared_ptr<DetectCaptureInput> detect_capture_input = 
		make_shared<DetectCaptureInput>(cam_output);
	cam_output.attach(detect_capture_input);

	shared_ptr<DetectGuiInput> detect_gui_input =
		make_shared<DetectGuiInput>(gui_detection_output, proc_settings);
	gui_detection_output.attach(detect_gui_input);

	// Set Up detection process and connect to capture input
	shared_ptr<CardDetector> card_detector = 
		make_shared<CardDetector> (detect_gui_input->im_proc_settings_);
	detect_capture_input->connectCardDetector(card_detector);

	// Set Up detection output to gui
	DetectGuiOutput detect_gui_output{};
	detect_gui_output.connectCardDetector(card_detector);


	// SetUp Connection between detection and poker module
	DetectPokerOutput detect_poker_output(card_detector->data_);

	shared_ptr<PokerDetectInput> poker_detect_input = 
		make_shared<PokerDetectInput> (detect_poker_output);
	detect_poker_output.attach(poker_detect_input);

	//Setup simulation
	SimSettings mock_settings{};
	Simulation sim(mock_settings, poker_detect_input->data_);

	// Set Up Interface poker/gui
	PokerOutput poker_output{sim.data_};
	shared_ptr<GuiPokerInput>gui_poker_input = 
		make_shared<GuiPokerInput>(poker_output);
	poker_output.attach(gui_poker_input);

	// Set up gui context
	GuiContext gui{};
	gui.init();

	LayoutConfig layout_settings{};
	layout_settings.setToDefault(default_settings);

	// Set up Interface between camera and gui to get user input

	GuiCaptureOutput gui_capture_output(camera_settings);

	shared_ptr<CaptureGuiInput> capture_gui_input =
		 make_shared<CaptureGuiInput>(gui_capture_output);
	capture_gui_input->connectCameraDevice(cam_controller);

	gui_capture_output.attach(capture_gui_input);

	// Set up Interface between gui and detection module to get card images
	shared_ptr<GuiDetectionInput> gui_detect_input =
		make_shared<GuiDetectionInput> (detect_gui_output);
	detect_gui_output.attach(gui_detect_input);

	// Set up Interface between gui and camera to get live frame to gui

	shared_ptr<GuiCaptureInput> gui_capture_input = 
		make_shared<GuiCaptureInput>(cam_output);

	cam_output.attach(gui_capture_input);

	// Set Up Gui Widgets

	SettingsWin settings_window(
		"Settings", 
		default_settings, 
		camera_settings,
		layout_settings,
		proc_settings
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
		gui_poker_input->data_
		);

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
			cout << sim.data_.probability.first << endl;
					
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
