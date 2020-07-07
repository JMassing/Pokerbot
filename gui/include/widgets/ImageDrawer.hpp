#pragma once

#include <imgui.h>
#include <opencv2/core.hpp>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "View.h"

namespace gui {

	class ImageDrawer
	{
		private:
		View visualize_;

		public:		

			void draw(const cv::Mat& frame, const int& image_width, const int& image_height);
			ImageDrawer(): visualize_{} {};
			virtual ~ImageDrawer() {};

			// Using default copy and move constructors. 
			ImageDrawer(const ImageDrawer& other) = default;	
			ImageDrawer& operator=(const ImageDrawer& other) = default;
			ImageDrawer(ImageDrawer&& other) noexcept = default;
			ImageDrawer& operator=(ImageDrawer&& other) noexcept = default;
	};


} // namespace gui

