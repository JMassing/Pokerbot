#include "ImageDrawer.hpp"        

namespace gui
{
    void ImageDrawer::delete_texture()
    {
        glDeleteTextures(1, &this->texture);
    }
    void ImageDrawer::init_texture()
    {
            cv::Mat image = cv::Mat::zeros(100, 100, CV_8UC3);
            cv::cvtColor( image, image, cv::COLOR_BGR2RGBA );        
            glGenTextures( 1, &this->texture );
            glBindTexture( GL_TEXTURE_2D, this->texture );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
            glPixelStorei( GL_UNPACK_ROW_LENGTH, 0 );
            
            glTexImage2D( 
                GL_TEXTURE_2D, 
                0, 
                GL_RGBA, 
                image.cols, 
                image.rows, 
                0, 
                GL_RGBA, 
                GL_UNSIGNED_BYTE, 
                image.data 
                );            
    }
    
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
        const cv::Scalar& color,
        const bool& fill_contours
        )
	{
		cv::Mat drawing = cv::Mat::zeros(dst.size(), dst.type());
        
        // Set thickness to filled and contour color to solid white if contours should be filled
        int thickness = fill_contours ? -1 : 2;
        cv::Scalar contour_color = fill_contours ?  cv::Scalar{255, 255, 255} : color;

		for (int i = 0; i < contours.size(); ++i) 
		{
			cv::drawContours(drawing, contours, i, contour_color, thickness);
		}
		drawing.copyTo(dst, drawing);

        drawing.release();
	
	}

    
	//@brief: Writes card Rank/Suit into image. Writes approx. into middle of card contour
	void ImageDrawer::writeCard(
        cv::Mat& src, 
        const detect::Card& card, 
        const cv::Scalar& color
        )
	{
		
		std::string rank;
		std::string suit;
		std::string text;
		Mapping mapping;

	
		if (card.suit == UNKNOWN || card.rank == UNKNOWN)
		{
			text = "Unknown";
		}
		else
		{
			rank = mapping.image_mappings.right.at(card.rank);
			suit = mapping.image_mappings.right.at(card.suit);
			text = rank + " of " + suit;
		}
		this->printText(src, text, card.center_point-cv::Point(50,0), color);
		
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

    void ImageDrawer::drawPoint(
        cv::Mat& frame, 
		const cv::Point& center, 
		const cv::Scalar& color
        )
    {
        cv::circle(frame, center, 1, color);
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
                
            ImGui::Image( 
                reinterpret_cast<void*>( static_cast<intptr_t>( this->texture ) ), 
                ImVec2( shown_image.cols, shown_image.rows ) 
                );
        
            glBindTexture( GL_TEXTURE_2D, this->texture );
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

        

                //glDeleteTextures(1, &texture);
                shown_image.release();
                glBindTexture(GL_TEXTURE_2D, 0);
        }
        else
        {
            ImGui::Text("No Image to show");
        }
    }

    //@brief: Copy Card Contours and Rank/Suits as Text to image. Used to visualize Cards in given frame.
	void ImageDrawer::drawCard(
        const detect::Card& card, 
        cv::Mat& dst, 
        const cv::Scalar& color,
        const bool& mask_cards
        )
	{
		std::vector<std::vector<cv::Point> > contours;
		
		// make sure card has a contour
		if(card.contour.size() > 0)
		{
			contours.emplace_back(card.contour);
		}
		
		
		//
		if(contours.size() > 0)
		{
			this->drawContours(contours, dst, color, mask_cards);

			mask_cards ? "" : this->writeCard(dst, card, color);
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