
#include "GUI.h"

namespace visualization {

    void GUI::drawImage(const cv::Mat& frame, const std::vector<detect::Card>& cards)
    {				
            //clone original frame, as we do not want to change it
            cv::Mat shown_image = frame.clone();

            if(show_cards_ && cards.size() > 0)
            {
                this->visualize_.drawCards(cards, shown_image);
            }

            shown_image = this->visualize_.resize(shown_image, this->image_width_, this->image_height_);

            cv::cvtColor( shown_image, shown_image, cv::COLOR_BGR2RGBA );
            GLuint texture;
            glGenTextures( 1, &texture );
            glBindTexture( GL_TEXTURE_2D, texture );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
            glPixelStorei( GL_UNPACK_ROW_LENGTH, 0 );
            glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, shown_image.cols, shown_image.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, shown_image.data );
            ImGui::Image( reinterpret_cast<void*>( static_cast<intptr_t>( texture ) ), ImVec2( shown_image.cols, shown_image.rows ) );
    }

    void GUI::drawMainWindow(const std::pair<double,double>& probability)
    {
            ImGui::Text("Probability of winning = %.2f", static_cast<float>(probability.first));
            ImGui::Text("Probability of winning tie = %.2f", static_cast<float>(probability.second));
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::Text("");
            this->addButton("Quit", [this](){this->closeWindow();});
    }

    void GUI::drawGui(const cv::Mat& frame, const std::vector<detect::Card>& cards, const std::pair<double,double>& probability)
    {   
        // set up GUI
        this->setEventHandler();
	    this->drawGuiFrame();

        // Add Elements to GUI
        this->addWindow("Live Image", [this, frame, cards](){this->drawImage(frame,cards);});
        this->addWindow("Main Window", [this, probability](){this->drawMainWindow(probability);});

        //Render and Check if Close is called on GUI
        this->render();
		this->listenWindowClose();
    }

} // end namespace visualization