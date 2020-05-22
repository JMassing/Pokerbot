
#include "GUI.h"

namespace visualization {

    bool GUI::init()
    {
        if(!this->setupWindow())
        {
            return false;
        }
        this->setupContext();
        return true;
    }

    bool GUI::setupWindow()
    {
        // Setup window
        if( !glfwInit() )
        {
            return false;
        }

        // Create window with graphics context
        this->window_ = glfwCreateWindow( this->window_width_, this->window_height_, "Pokerbot", nullptr, nullptr );
        glfwMakeContextCurrent( this->window_ );
        glfwSwapInterval( 1 );
        gl3wInit();

        return true;
    }

    void GUI::setupContext()
    {
        // Setup Dear ImGui context	
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // Setup Platform/Renderer bindings     
        ImGui_ImplGlfw_InitForOpenGL( this->window_, true );
        ImGui_ImplOpenGL3_Init( this->glsl_version_ );

    }

    void GUI::setEventHandler()
    {
        // Poll and handle events (inputs, window resize, etc.)
        glfwPollEvents();
    }

    void GUI::drawGuiFrame()
    {
		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
    }

    void GUI::drawImage(const cv::Mat& frame, const std::vector<detect::Card>& cards)
    {				
        if(this->show_frame_)
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
            
            ImGui::Begin( "Live Image", &this->show_frame_ );
            ImGui::Image( reinterpret_cast<void*>( static_cast<intptr_t>( texture ) ), ImVec2( shown_image.cols, shown_image.rows ) );
            ImGui::End();
        }
    }

    void GUI::showProbability(const std::pair<double,double>& probability)
    {
        bool show_window=true;
        if(show_window)
        {
            ImGui::Begin("", &show_window );
            ImGui::Text("Probability of winning = %.2f", static_cast<float>(probability.first));
            ImGui::Text("Probability of winning tie = %.2f", static_cast<float>(probability.second));
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::Text("");
            this->addButton("Stop Program", [this](){this->closeWindow();});

            ImGui::End();
        }

    }

    void GUI::render()
    {        
        ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );
		glfwSwapBuffers( this->window_ );
    }

    void GUI::monitorWindowCloseCondition()
    {
        if(glfwWindowShouldClose(this->window_))
        {
            this->should_close_ = true;
        }
    }

    void GUI::tearDown()
    {
        ImGui_ImplGlfw_Shutdown();
	    ImGui_ImplOpenGL3_Shutdown();
	    glfwTerminate();
	    ImGui::DestroyContext();	
    }
} // end namespace visualization