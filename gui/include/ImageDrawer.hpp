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
	/** \ingroup gui
	 * @class ImageDrawer
	 * @author Julian Massing (julimassing@gmail.com)
	 * @brief Adds contour outlines, text, rectangles and points to camera image and 
	 * 		 draws live frame into live image window
	 *
	 * @version 1.0
	 * @date 2020-11-21
	 * 
	 * @copyright Copyright (c) 2020
	 * 
	 */
	class ImageDrawer
	{
		private:

			GLuint texture;

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

			/**
			 * @brief Inits OpenGl texture for drawing live image
			 * 
			 */
			void initTexture();
			/**
			 * @brief Deletes texture
			 * 
			 */
			void deleteTexture();
			/**
			 * @brief Print text to given frame
			 * 
			 * @param dst destination frame
			 * @param text text to print
			 * @param pos Text position
			 * @param color Text color
			 */
			void printText(
				cv::Mat& dst, 
				std::string& text, 
				const cv::Point& pos, 
				const cv::Scalar& color
				);
			/**
			 * @brief Load given image as texture using OpenGl and display it in GUI window using ImGui::Image()
			 * 
			 * @param frame Frame to draw
			 * @param image_width Width in pixel
			 * @param image_height Height in Pixel
			 */
			void draw(const cv::Mat& frame, const int& image_width, const int& image_height);
			/**
			 * @brief Print Card Contours and Rank/Suits as Text to image. Used to visualize Cards in given frame.
			 * 
			 * @param card Card to draw
			 * @param dst Destination frame
			 * @param color Contour and Text color
			 * @param mask_cards True if cards should be masked. 
			 */
			void drawCard(
				const detect::Card& card, 
				cv::Mat& dst, 
				const cv::Scalar& color,
				const bool& mask_cards = false
				);
			/**
			 * @brief Draw rectangle in given frame
			 * 
			 * @param frame Destination frame
			 * @param rect Rectangle object
			 * @param color Linecolor
			 */
			void drawRectangle(
					cv::Mat& frame, 
					const cv::Rect& rect, 
					const cv::Scalar& color
					);
			/**
			 * @brief Draw point in given frame
			 * 
			 * @param frame Destination frame
			 * @param center Point object
			 * @param color 
			 */
			void drawPoint(
					cv::Mat& frame, 
					const cv::Point& center, 
					const cv::Scalar& color
					);

			ImageDrawer() 
			{ 
				this->initTexture(); 
			};
			~ImageDrawer() {};

			// Using default copy and move constructors. 
			ImageDrawer(const ImageDrawer& other) = default;	
			ImageDrawer& operator=(const ImageDrawer& other) = default;
			ImageDrawer(ImageDrawer&& other) noexcept = default;
			ImageDrawer& operator=(ImageDrawer&& other) noexcept = default;
	};

} // namespace gui

