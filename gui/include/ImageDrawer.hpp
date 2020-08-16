#pragma once

#include <vector>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "Card.hpp"
#include "Mapping.hpp"

// Loads cv::Mat image to OpenGL texture and draws it in ImGui
namespace gui {

	class ImageDrawer
	{
		private:

			cv::Mat resize(const cv::Mat& frame, const int& width, const int& height);

			void writeCard(
				cv::Mat& src, 
				const detect::Card& card, 
				const cv::Scalar& color
				);
			
			void drawContours(
				const std::vector<std::vector<cv::Point> >& contours, 
				cv::Mat& dst,
				const cv::Scalar& color,
				const bool& fill_contours = false
				);	

		public:		

			
			void printText(
				cv::Mat& dst, 
				std::string& text, 
				cv::Point& pos, 
				const cv::Scalar& color
				);

			void draw(const cv::Mat& frame, const int& image_width, const int& image_height);

			void drawCard(
				const detect::Card& card, 
				cv::Mat& dst, 
				const cv::Scalar& color,
				const bool& mask_cards = false
				);

			void drawRectangle(
					cv::Mat& frame, 
					const cv::Rect& rect, 
					const cv::Scalar& color
					);
			
			void drawPoint(
					cv::Mat& frame, 
					const cv::Point& center, 
					const cv::Scalar& color
					);

			ImageDrawer() {};
			~ImageDrawer() {};

			// Using default copy and move constructors. 
			ImageDrawer(const ImageDrawer& other) = default;	
			ImageDrawer& operator=(const ImageDrawer& other) = default;
			ImageDrawer(ImageDrawer&& other) noexcept = default;
			ImageDrawer& operator=(ImageDrawer&& other) noexcept = default;
	};


} // namespace gui

