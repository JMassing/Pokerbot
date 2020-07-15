#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

// Sets up GUI Context with ImGui
namespace gui {

	class GuiContext
	{
		protected:
           
            bool should_close_;
            const int window_width_ = 1800;
            const int window_height_ = 1000;
            const char* glsl_version_ = "#version 330";
            const char* program_name_ = "Pokerbot";
            GLFWwindow* window_;

            bool setupGlfwWindow();
            void setupContext();
            void tearDown();
            void setEventHandler();             
            void listenWindowClose(); 

		public:

            bool init();
            void drawGuiFrame();            
            void render();
            bool shouldClose() { return this->should_close_; };             
            void closeWindow() { this->should_close_ = true; }; 
  					
			GuiContext(): window_(nullptr), should_close_(false) {};
			~GuiContext() 
            {
                this->tearDown();
            };

			// Using default copy and move constructors. 
			GuiContext(const GuiContext& other) = default;	
			GuiContext& operator=(const GuiContext& other) = default;
			GuiContext(GuiContext&& other) noexcept = default;
			GuiContext& operator=(GuiContext&& other) noexcept = default;
	};

} // namespace gui

