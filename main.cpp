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
#include "Card.h"
#include "Simulation.h"
#include "CardBuffer.h"
#include "AssignCards.h"
#include "RectangleCorners.h"


using namespace cv;
using namespace std;
using namespace detect;
using namespace poker;
using namespace templates;

int main(int argc, char* argv[])
{
	
	//// Initialize variables for live capture and image processing
	Capture live("C:\\Users\\julim\\Desktop\\Projects\\DealingCards.mp4");
	//
	/*if (!live.init()) {
		cerr << "ERROR! Unable to open camera\n";
		return -2;
	}*/
	//	
	//

	////--- GRAB AND WRITE LOOP
	cout << "Start grabbing" << endl
		<< "Press any key to terminate" << endl;

	array<BaseCard,2> robot_cards;

	Simulation sim(5,10000);
	int nr_of_sim_runs=0;

	for (;;)
	{
		// Grab live frame and check if it worked
		if (!live.grabLive()) { break; }		
		
		// ************************************************ //
		//		Process live Image to extract cards			//
		// ************************************************ //

		CardDetector detect{ live.frame_ };
		detect.detectCards();

		vector<Card> known_cards=detect.getCards();
		vector<BaseCard> public_cards;
		RectangleCorners<cv::Point> robot_area;
		robot_area.upper_left= cv::Point{0,3600};
		robot_area.upper_right= cv::Point{1500,3600};
		robot_area.lower_right= cv::Point{1500,800};
		robot_area.lower_left= cv::Point{0,800};
		RectangleCorners<cv::Point> public_area;
		public_area.upper_left= cv::Point{0,800};
		public_area.upper_right= cv::Point{1500,800};
		public_area.lower_right= cv::Point{1500,0};
		public_area.lower_left= cv::Point{0,0};

		AssignCards assign_cards(robot_area, public_area);
		
		assign_cards.assign(known_cards);
		robot_cards=assign_cards.getRobotCards();
		public_cards=assign_cards.getPublicCards();		

		// ************************************************ //
		//				Simulation						//
		// ************************************************ //
				
		pair<double,double> prob=sim.run(public_cards, robot_cards);
		++nr_of_sim_runs;
				
		// ************************************************ //
		//				Visualization						//
		// ************************************************ //
		
		View visualize;
		visualize.drawCards(detect.getCards(), live.frame_, Scalar(0, 255, 0));
		visualize.printProbability(live.frame_, prob);

		imshow("live",live.frame_);


	if (waitKey(5) >= 0)
			break;
	}
	
	// the camera will be deinitialized automatically in VideoCapture destructor
	
}
