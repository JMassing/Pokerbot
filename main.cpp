#include <iostream>
#include <vector>
#include <array>
#include <memory>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include "Capture.h"
#include "CardDetector.h"
#include "GUI.h"
#include "Simulation.h"
#include "DataDetectGui.h"
#include "DataPokerGui.h"
#include "DataPokerDetect.h"


using namespace cv;
using namespace std;
using namespace detect;
using namespace poker;
using namespace templates;
using namespace visualization;
using namespace data;


int main(int argc, char* argv[])
{
	
	//// Initialize variables for live capture and image processing
	Capture live("C:\\Users\\julim\\Desktop\\Projects\\DealingCards.mp4");
	//
	/*/if (!live.init()) {
		cerr << "ERROR! Unable to open camera\n";
		return -2;
	}*/
	
	//	Setup shared data structs
	shared_ptr<DataDetectGui> shared_data_detect_gui = std::make_shared<DataDetectGui>();
	shared_ptr<DataPokerGui> shared_data_poker_gui = std::make_shared<DataPokerGui>();
	shared_ptr<DataPokerDetect> shared_data_poker_detect = std::make_shared<DataPokerDetect>();


	// initialize Simulation, CardDetector and Gui classes
	Simulation sim(shared_data_poker_gui, shared_data_poker_detect);
	CardDetector detect{shared_data_detect_gui, shared_data_poker_detect};
	GUI gui{shared_data_detect_gui, shared_data_poker_gui};
	gui.init();
	
	
	while( !gui.shouldClose() )
	{
		for (;;)
		{
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
