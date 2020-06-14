#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

namespace gui {

	class BaseGUI
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
            void helpMarker(const char* desc);
            void setEventHandler();
            void render();
            void listenWindowClose();  

		public:

            bool init();            
            void drawGuiFrame();            
            bool shouldClose() { return this->should_close_; };             
            void closeWindow() { this->should_close_ = true; }; 
  					
			BaseGUI(): window_(nullptr), should_close_(false) {};
			~BaseGUI() 
            {
                this->tearDown();
            };

			// Using default copy and move constructors. 
			BaseGUI(const BaseGUI& other) = default;	
			BaseGUI& operator=(const BaseGUI& other) = default;
			BaseGUI(BaseGUI&& other) noexcept = default;
			BaseGUI& operator=(BaseGUI&& other) noexcept = default;
	};

} // namespace gui

