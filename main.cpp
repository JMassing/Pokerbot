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


using namespace cv;
using namespace std;
using namespace detect;
using namespace poker;

template<class T>
bool contains(Card input_card, T cards)
{
	for(const auto& card: cards)
	{
		if(card.rank==input_card.rank && card.suit==input_card.suit)
		{
			return true;
		}
	} 
	
	return false;
}

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

		// ************************************************ //
		//				Simulation						//
		// ************************************************ //
		vector<Card> known_cards=detect.getCards();
		vector<BaseCard> public_cards;
		
		for(const auto& card: known_cards)
		{	
			for(auto&robot_card : robot_cards)
			{
				if(card.rank != UNKNOWN && card.suit != UNKNOWN && robot_card.rank == UNKNOWN && card.center_point.x < 1500 && card.center_point.y > 800 && !contains(card,robot_cards))
				{
					robot_card=card;
				}
				else if(card.rank != UNKNOWN && card.suit != UNKNOWN && card.center_point.x < 1500 && card.center_point.y < 800 && !contains(card,public_cards))
				{
					public_cards.emplace_back(card);
				}
			}	
		}		
				
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
