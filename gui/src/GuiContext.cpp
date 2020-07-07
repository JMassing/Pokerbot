#include "GuiContext.hpp"

namespace gui {

    bool GuiContext::init()
    {
        if(!this->setupGlfwWindow())
        {
            return false;
        }
        this->setupContext();

        return true;
    }

    bool GuiContext::setupGlfwWindow()
    {
        // Setup window
        if( !glfwInit() )
        {
            return false;
        }

        // Create window with graphics context
        this->window_ = 
            glfwCreateWindow( 
                this->window_width_, 
                this->window_height_, 
                this->program_name_, 
                nullptr, 
                nullptr 
                );

        glfwMakeContextCurrent( this->window_ );
        glfwSwapInterval( 1 );
        gl3wInit();

        return true;
    }

    void GuiContext::setupContext()
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

    void GuiContext::setEventHandler()
    {
        // Poll and handle events (inputs, window resize, etc.)
        glfwPollEvents();
    }

    void GuiContext::drawGuiFrame()
    {
		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
        this->setEventHandler();
        this->listenWindowClose();
    }

    void GuiContext::render()
    {        
        ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );
		glfwSwapBuffers( this->window_ );
    }

    void GuiContext::listenWindowClose()
    {
        if(glfwWindowShouldClose(this->window_))
        {
            this->should_close_ = true;
        }
    }

    void GuiContext::tearDown()
    {
        ImGui_ImplGlfw_Shutdown();
	    ImGui_ImplOpenGL3_Shutdown();
	    glfwTerminate();
	    ImGui::DestroyContext();	
    }

} // end namespace gui