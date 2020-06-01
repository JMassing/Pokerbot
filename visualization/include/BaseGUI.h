#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

namespace visualization {

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

		public:

            template<class T>
            void addButton(const char* name, T& callback);
            template<class T>
            void addWindow(const char* name, bool& show_window, T& content);
            bool init();
            void setEventHandler();
            void drawGuiFrame();
            void render();
            bool shouldClose() { return this->should_close_; };
            void listenWindowClose();   
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

    //template functions
    template<class T>
    void BaseGUI::addButton(const char* name, T& callback)
    {
        if(ImGui::Button(name))
        {
            callback();
        }                           
    };

    template<class T>
    void BaseGUI::addWindow(const char* name, bool& show_window, T& content)
    {
        if(show_window)
        {
            ImGui::Begin(name, &show_window );
            content();
            ImGui::End();
        }
    };
} // namespace visualization
