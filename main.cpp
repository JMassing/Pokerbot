#include <iostream>
#include <vector>
#include <array>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>


#include "Capture.h"
#include "CardDetector.h"
#include "View.h"
#include "Hand.h"
#include "Deck.h"


using namespace cv;
using namespace std;
using namespace detect;
using namespace poker;


int main(int argc, char* argv[])
{
	
	//// Initialize variables for live capture and image processing
	Capture live("C:\\Users\\julim\\Desktop\\Projects\\MultipleCards.mp4");
	//
	if (!live.init()) {
		cerr << "ERROR! Unable to open camera\n";
		return -2;
	}
	//	
	//

	////--- GRAB AND WRITE LOOP
	cout << "Start grabbing" << endl
		<< "Press any key to terminate" << endl;


	for (;;)
	{
		// Grab live frame and check if it worked
		if (!live.grabLive()) { break; }		
		
		// ************************************************ //
		//		Process live Image to extract cards			//
		// ************************************************ //

		CardDetector detect{ live.frame_ };
		detect.detectCards();

		// ************************************************ //
		//				Visualization						//
		// ************************************************ //
		
		View visualize;
		visualize.drawCards(detect.getCards(), live.frame_, Scalar(0, 255, 0));

		imshow("live",live.frame_);


	if (waitKey(5) >= 0)
			break;
	}
	
	// the camera will be deinitialized automatically in VideoCapture destructor
	
}
