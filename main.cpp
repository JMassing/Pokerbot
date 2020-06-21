#include <iostream>
#include <memory>


#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <imgui.h>

#include "Capture.h"
#include "CardDetector.h"
#include "GuiContext.h"
#include "Simulation.h"
#include "ImProcSettings.h"
#include "DataPokerGui.h"
#include "DataPokerDetect.h"
#include "CameraControls.h"
#include "IObserver.h"
#include "ControlsWin.h"
#include "LiveImageWin.h"


using namespace cv;
using namespace std;
using namespace detect;
using namespace poker;
using namespace templates;
using namespace gui;
using namespace shared;

int main(int argc, char* argv[])
{
	
	//	Setup settings structs
	DefaultConfig default_settings;
    CameraControls camera_settings;
	camera_settings.setToDefault(default_settings);
	/*shared_ptr<DataPokerGui> shared_data_poker_gui = std::make_shared<DataPokerGui>();
	shared_ptr<DataPokerDetect> shared_data_poker_detect = std::make_shared<DataPokerDetect>();
	shared_ptr<LayoutConfig> layout_config = std::make_shared<LayoutConfig>();*/
	
	
	// Create Simulation, CardDetector and Gui classes
	//Simulation sim(shared_data_poker_gui, shared_data_poker_detect);
	//CardDetector detect{shared_data_detect_gui, shared_data_poker_detect, default_config};

	// set up gui context and widgets

	GuiContext gui{};
	gui.init();

	ControlsWin controls("Settings", default_settings, camera_settings);

	// Initialize live capture and attach to controls window to get user input
	shared_ptr<Capture> live = make_shared<Capture>(controls, camera_settings);
	controls.attach(live);

	shared_ptr<LiveImageWin> live_view = make_shared<LiveImageWin>("Live View", controls, live->frame_, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize);
	controls.attach(live_view);
	
	if (!live->init()) {
		cerr << "ERROR! Unable to open camera\n";
		return -2;
	}	

	while( !gui.shouldClose() )
	{
		for (;;)
		{
			

			// Grab live frame and check if it worked
			if (!live->grabLive())
			{ 
				// set gui state to should_close_ = true and exit for loop
				gui.closeWindow();
				break;
			}						

			// ************************************************ //
			//		Process live Image to extract cards			//
			// ************************************************ //

			/*detect.updateFrame(live.frame_);
			detect.detectCards();*/

			// ************************************************ //
			//					Simulation						//
			// ************************************************ //
			
			//sim.run();
					
			// ************************************************ //
			//					Draw GUI						//
			// ************************************************ //
			gui.drawGuiFrame();
			live_view->draw();
			controls.draw();
			

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
