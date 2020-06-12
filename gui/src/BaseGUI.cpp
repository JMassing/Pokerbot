
#include "BaseGUI.h"

namespace gui {

    bool BaseGUI::init()
    {
        if(!this->setupGlfwWindow())
        {
            return false;
        }
        this->setupContext();
        return true;
    }

    bool BaseGUI::setupGlfwWindow()
    {
        // Setup window
        if( !glfwInit() )
        {
            return false;
        }

        // Create window with graphics context
        this->window_ = glfwCreateWindow( this->window_width_, this->window_height_, this->program_name_, nullptr, nullptr );
        glfwMakeContextCurrent( this->window_ );
        glfwSwapInterval( 1 );
        gl3wInit();

        return true;
    }

    void BaseGUI::setupContext()
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

    void BaseGUI::setEventHandler()
    {
        // Poll and handle events (inputs, window resize, etc.)
        glfwPollEvents();
    }

    void BaseGUI::drawGuiFrame()
    {
		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
    }

    void BaseGUI::render()
    {        
        ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );
		glfwSwapBuffers( this->window_ );
    }

    void BaseGUI::listenWindowClose()
    {
        if(glfwWindowShouldClose(this->window_))
        {
            this->should_close_ = true;
        }
    }

    void BaseGUI::tearDown()
    {
        ImGui_ImplGlfw_Shutdown();
	    ImGui_ImplOpenGL3_Shutdown();
	    glfwTerminate();
	    ImGui::DestroyContext();	
    }

    // Helper to display a little (?) mark which shows a tooltip when hovered.
    // In your own code you may want to display an actual icon if you are using a merged icon fonts (see misc/fonts/README.txt)
    void BaseGUI::helpMarker(const char* desc)
    {
        ImGui::TextDisabled("(?)");
        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted(desc);
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
    }
} // end namespace gui