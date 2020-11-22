#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

namespace gui {
    
    /**
    * \defgroup gui
    * The Gui module uses the Dear ImGui framework to create the Pokerbot GUI.
 	* @{
	* @class GuiContext
	* @author Julian Massing (julimassing@gmail.com)
	* @brief Wrapper around Dear ImGui with glfw and OpenGl3 backend. Sets up GUI context, event handlers,
    *        platform bindings and renders GUI.
	*
	* @version 1.0
	* @date 2020-11-21
	* 
	* @copyright Copyright (c) 2020
	* 
	*/
    /**@}*/
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

            /**
             * @brief Initialize Gui Context and main Gui frame with graphics context
             * 
             * @return true on successfull init
             * @return false on failed init
             */
            bool init();
            /**
             * @brief Draw main Gui frame
             * 
             */
            void drawGuiFrame();    
            /**
             * @brief Renders all gui windows 
             * 
             */
            void render();
            /**
             * @brief Checks if User closes Gui
             * 
             * @return true if close
             * @return false if not close
             */
            bool shouldClose() { return this->should_close_; }; 
            /**
             * @brief Forces Gui closure.
             * 
             */
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

