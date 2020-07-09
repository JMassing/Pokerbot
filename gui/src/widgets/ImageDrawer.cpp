#include "ImageDrawer.hpp"        

namespace gui
{

    
	cv::Mat ImageDrawer::resize(const cv::Mat& frame, const int& width, const int& height)
	{
		cv::Mat live_img;
		live_img.create(cv::Size(width, height), frame.type());
		cv::resize(frame, live_img, live_img.size(), 0, 0, cv::INTER_LINEAR); 
		return live_img;
	}

    //@brief: Draw given contour into given image 
	void ImageDrawer::drawContours(
        const std::vector<std::vector<cv::Point> >& contours, 
        cv::Mat& dst, 
        const cv::Scalar& color
        )
	{
		cv::Mat drawing = cv::Mat::zeros(dst.size(), CV_8UC3);
		for (int i = 0; i < contours.size(); ++i) 
		{
			cv::drawContours(drawing, contours, i, color, 2, 8, cv::noArray(), 0, cv::Point());
		}
		drawing.copyTo(dst, drawing);
	
	}

    
	//@brief: Writes card Rank/Suit into image. Writes approx. into middle of card contour
	void ImageDrawer::writeCard(
        cv::Mat& src, 
        const std::vector<detect::Card>& cards, 
        const cv::Scalar& color
        )
	{
		
		std::string rank;
		std::string suit;
		std::string text;
		detect::Mapping mapping;

		for (int i = 0; i < cards.size(); ++i)
		{	
			if (cards[i].suit == detect::UNKNOWN || cards[i].rank == detect::UNKNOWN)
			{
				text = "Unknown";
			}
			else
			{
				rank = mapping.image_mappings.right.at(cards[i].rank);
				suit = mapping.image_mappings.right.at(cards[i].suit);
				text = rank + " of " + suit;
			}
			this->printText(src, text, cards[i].center_point-cv::Point(50,0), color);
		}

	}
    
    //@brief: Copy text to given image
	void ImageDrawer::printText(
        cv::Mat& dst, 
        std::string& text, 
        cv::Point& pos, 
        const cv::Scalar& color
        )
	{
		cv::putText(dst, text, pos, cv::FONT_HERSHEY_PLAIN, 0.75, color, 1.5);
	}

    //@brief: Load given image as texture using opengl and display it in GUI window using ImGui::Image()
    void ImageDrawer::draw(const cv::Mat& frame, const int& image_width, const int& image_height)
    {
       if(!frame.empty())
        {
            //clone original frame, as we do not want to change the underlying data as a side effect.
            cv::Mat shown_image = frame.clone();

            if(image_width != shown_image.cols || image_height != shown_image.rows )
            {
                shown_image = this->resize(shown_image, image_width, image_height);
            }

            cv::cvtColor( shown_image, shown_image, cv::COLOR_BGR2RGBA );
            GLuint texture;
            glGenTextures( 1, &texture );
            glBindTexture( GL_TEXTURE_2D, texture );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
            glPixelStorei( GL_UNPACK_ROW_LENGTH, 0 );
            
            glTexImage2D( 
                GL_TEXTURE_2D, 
                0, 
                GL_RGBA, 
                shown_image.cols, 
                shown_image.rows, 
                0, 
                GL_RGBA, 
                GL_UNSIGNED_BYTE, 
                shown_image.data 
                );

            ImGui::Image( 
                reinterpret_cast<void*>( static_cast<intptr_t>( texture ) ), 
                ImVec2( shown_image.cols, shown_image.rows ) 
                );
        }
        else
        {
            ImGui::Text("No Image to show");
        }
    }

    //@brief: Copy Card Contours and Rank/Suits as Text to image. Used to visualize Cards in given frame.
	void ImageDrawer::drawCards(
        const std::vector<detect::Card>& cards, 
        cv::Mat& dst, 
        const cv::Scalar& color
        )
	{
		std::vector<std::vector<cv::Point> > contours;
		for (const auto& card : cards)
		{
			// make sure card has a contour
			if(card.contour.size() > 0)
			{
				contours.emplace_back(card.contour);
			}
		}
		
		//
		if(contours.size() > 0)
		{
			this->drawContours(contours, dst, color);
			this->writeCard(dst, cards, color);
		}		
	}

    //@brief: Copy rectanlge to image
    void ImageDrawer::drawRectangle(
        cv::Mat& frame, 
        const cv::Rect& rect, 
        const cv::Scalar& color
        )
	{
		cv::rectangle(frame, rect, color, 1.5);
	}


} //end namespace gui