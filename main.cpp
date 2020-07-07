#include <iostream>
#include <memory>

#include "CameraController.hpp"
//#include "CardDetector.h"
#include "GuiContext.hpp"
//#include "Simulation.h"
//#include "ImProcSettings.h"
//#include "DataPokerGui.h"
//#include "DataPokerDetect.h"
#include "CameraSettings.hpp"
#include "SettingsWin.hpp"
#include "LiveImageWin.hpp"
#include "GuiCaptureOutput.hpp"
#include "CaptureGuiInput.hpp"
#include "CaptureOutput.hpp"
#include "GuiCaptureInput.hpp"
#include "LayoutConfig.hpp"


using namespace cv;
using namespace std;
using namespace detect;
//using namespace poker;
//using namespace templates;
using namespace gui;
using namespace shared;
using namespace capture;


int main(int argc, char* argv[])
{
	/*shared_ptr<DataPokerGui> shared_data_poker_gui = std::make_shared<DataPokerGui>();
	shared_ptr<DataPokerDetect> shared_data_poker_detect = std::make_shared<DataPokerDetect>();
	shared_ptr<LayoutConfig> layout_config = std::make_shared<LayoutConfig>();*/
	
	
	// Create Simulation, CardDetector and Gui classes
	//Simulation sim(shared_data_poker_gui, shared_data_poker_detect);
	//CardDetector detect{shared_data_detect_gui, shared_data_poker_detect, default_config};

	DefaultConfig default_settings{};

	// Set up Camera	
    CameraSettings camera_settings{};
	camera_settings.setToDefault(default_settings);

	shared_ptr<CameraController> cam_controller = make_shared<CameraController>();

	if (!cam_controller->initCamera(camera_settings)) {
		cerr << "ERROR! Unable to open camera\n";
		return -2;
	}	

	// Set up capture output interface
	CaptureOutput cam_output(cam_controller->frame_);

	// set up gui context

	GuiContext gui{};
	gui.init();

	LayoutConfig layout_settings{};
	layout_settings.setToDefault(default_settings);

	SettingsWin settings_window(
		"Settings", 
		default_settings, 
		camera_settings,
		layout_settings
		);

	// Set up Interface between camera and gui to get user input

	GuiCaptureOutput gui_capture_output(camera_settings);

	shared_ptr<CaptureGuiInput> capture_gui_input =
		 make_shared<CaptureGuiInput>(gui_capture_output);
	capture_gui_input->addCameraDevice(cam_controller);

	gui_capture_output.attach(capture_gui_input);

	// Set up Interface between gui and camera to get live frame to gui

	shared_ptr<GuiCaptureInput> gui_capture_input = 
		make_shared<GuiCaptureInput>(cam_output);

	cam_output.attach(gui_capture_input);

	// Set Up Gui Widgets
	
	LiveImageWin live_view(
		"Live View", 
		settings_window.layout_settings_, 
		gui_capture_input->frame_, 
		ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize
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


			/*detect.updateFrame(live.frame_);
			detect.detectCards();*/

			
			//sim.run();
					

			gui.drawGuiFrame();
			live_view.draw();
			gui_capture_output.checkForUserInput(
				settings_window.draw(), 
				settings_window.camera_settings_
				);			

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
