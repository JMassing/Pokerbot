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

namespace gui {

	class ImageDrawer
	{
		private:

			cv::Mat resize(const cv::Mat& frame, const int& width, const int& height);

			void writeCard(
				cv::Mat& src, 
				const std::vector<detect::Card>& cards, 
				const cv::Scalar& color
				);
			
			void drawContours(
				const std::vector<std::vector<cv::Point> >& contours, 
				cv::Mat& dst,
				const cv::Scalar& color
				);	

			void printText(
				cv::Mat& dst, 
				std::string& text, 
				cv::Point& pos, 
				const cv::Scalar& color
				);

		public:		

			void draw(const cv::Mat& frame, const int& image_width, const int& image_height);

			void drawCards(
				const std::vector<detect::Card>& cards, 
				cv::Mat& dst, 
				const cv::Scalar& color
				);

			void drawRectangle(
					cv::Mat& frame, 
					const cv::Rect& rect, 
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

