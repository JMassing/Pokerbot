#pragma once

#include <utility>

#include <opencv2/core.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "View.h"

namespace visualization {

	class GUI
	{
		private:

            View visualize_;
            bool show_frame_;
            bool show_cards_;
            bool should_close_;
            const int window_width_ = 1600;
            const int window_height_ = 1000;
            const int image_width_ = 1248;
            const int image_height_ = 800;
            const char* glsl_version_ = "#version 330";
            GLFWwindow* window_;

            bool setupWindow();
            void setupContext();
            void tearDown();
            template<class T>
            void addButton(const char* name, T& callback)
            {
                if(ImGui::Button(name))
                {
                    callback();
                }                           
            } 

		public:

            bool init();
            void setEventHandler();
            void drawGuiFrame();
            void drawImage(const cv::Mat& frame, const std::vector<detect::Card>& cards);
            void render();
            bool shouldClose() { return this->should_close_; };
            void monitorWindowCloseCondition();   
            void closeWindow() { this->should_close_ = true; }; 
            void showProbability(const std::pair<double,double>& probability);    
  					
			GUI(): visualize_(), show_frame_(true), window_(nullptr), show_cards_(true), should_close_(false) {};
			~GUI() 
            {
                this->tearDown();
            };

			// Using default copy and move constructors. 
			GUI(const GUI& other) = default;	
			GUI& operator=(const GUI& other) = default;
			GUI(GUI&& other) noexcept = default;
			GUI& operator=(GUI&& other) noexcept = default;
	};

} // namespace visualization

