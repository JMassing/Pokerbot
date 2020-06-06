#include <iostream>
#include <memory>

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
using namespace visualization;
using namespace data;


int main(int argc, char* argv[])
{
	
	//	Setup shared data structs
	shared_ptr<DataDetectGui> shared_data_detect_gui = std::make_shared<DataDetectGui>();
	shared_ptr<DataPokerGui> shared_data_poker_gui = std::make_shared<DataPokerGui>();
	shared_ptr<DataPokerDetect> shared_data_poker_detect = std::make_shared<DataPokerDetect>();
	shared_ptr<CameraControls> camera_control = std::make_shared<CameraControls>();
	CameraControls save_camera_state{}; 
	//// Initialize variables for live capture and image processing
	Capture live("C:\\Users\\julim\\Desktop\\Projects\\DealingCards.mp4", camera_control);

	
	if (!live.init()) {
		cerr << "ERROR! Unable to open camera\n";
		return -2;
	}
	

	// initialize Simulation, CardDetector and Gui classes
	Simulation sim(shared_data_poker_gui, shared_data_poker_detect);
	CardDetector detect{shared_data_detect_gui, shared_data_poker_detect};
	GUI gui{shared_data_detect_gui, shared_data_poker_gui, camera_control};
	gui.init();
	
	save_camera_state = *camera_control;

	while( !gui.shouldClose() )
	{
		for (;;)
		{
			shared_data_detect_gui->known_cards.clear();
			//set new control parameters for camera if they were changed by the user via gui
			if(save_camera_state != *camera_control)
			{
				live.setCameraControls();
				save_camera_state = *camera_control;
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
			shared_data_detect_gui->known_cards = detect.getCards(); 

			// ************************************************ //
			//					Simulation						//
			// ************************************************ //
			
			sim.run();
					
			// ************************************************ //
			//					Draw GUI						//
			// ************************************************ //
			

			// draw Gui
			gui.drawGui(live.frame_);
			
			if (gui.shouldClose())
			{
					break;
			}
		}

	}

	// the camera will be deinitialized automatically in VideoCapture destructor
	// the GUI will be deinitialized automatically in GUI destructor	
}
