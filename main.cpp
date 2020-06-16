#include <iostream>
#include <memory>


#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "Capture.h"
#include "CardDetector.h"
#include "GUI.h"
#include "Simulation.h"
#include "DataDetectGui.h"
#include "DataPokerGui.h"
#include "DataPokerDetect.h"
#include "CameraControls.h"

using namespace cv;
using namespace std;
using namespace detect;
using namespace poker;
using namespace templates;
using namespace gui;
using namespace shared;

int main(int argc, char* argv[])
{
	
	//	Setup shared data structs
	shared_ptr<DefaultConfig> default_config = std::make_shared<DefaultConfig>();
	shared_ptr<DataDetectGui> shared_data_detect_gui = std::make_shared<DataDetectGui>();
	shared_ptr<DataPokerGui> shared_data_poker_gui = std::make_shared<DataPokerGui>();
	shared_ptr<DataPokerDetect> shared_data_poker_detect = std::make_shared<DataPokerDetect>();
	shared_ptr<CameraControls> camera_control = std::make_shared<CameraControls>(default_config);
	
	//// Initialize variables for live capture and image processing
	Capture live(camera_control);
	
	if (!live.init()) {
		cerr << "ERROR! Unable to open camera\n";
		return -2;
	}	

	// initialize Simulation, CardDetector and Gui classes
	Simulation sim(shared_data_poker_gui, shared_data_poker_detect);
	CardDetector detect{shared_data_detect_gui, shared_data_poker_detect, default_config};
	GUI gui{shared_data_detect_gui, shared_data_poker_gui, camera_control, default_config};
	gui.init();

	while( !gui.shouldClose() )
	{
		for (;;)
		{
			
			//set new control parameters for camera if they were changed by the user via gui
			if(gui.camControlsChanged())
			{
				live.setCameraControls();
			}

			// Grab live frame and check if it worked
			if (!live.grabLive())
			{ 
				// set gui state to should_close_ = true and exit for loop
				gui.closeWindow();
				break;
			}						

			// ************************************************ //
			//		Process live Image to extract cards			//
			// ************************************************ //

			detect.updateFrame(live.frame_);
			detect.detectCards();

			// ************************************************ //
			//					Simulation						//
			// ************************************************ //
			
			sim.run();
					
			// ************************************************ //
			//					Draw GUI						//
			// ************************************************ //
			
			gui.drawGui(live.frame_.image);
			
			if (gui.shouldClose())
			{
					break;
			}
		}

	}

	// the camera will be deinitialized automatically in VideoCapture destructor
	// the GUI will be deinitialized automatically in GUI destructor

}
