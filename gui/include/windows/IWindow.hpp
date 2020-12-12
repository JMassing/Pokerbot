#pragma once

#include <string>
#include <imgui.h>

namespace gui {

	/**  \ingroup gui
	 * @class IWindow
	 * @author Julian Massing (julimassing@gmail.com)
	 * @brief Interface which defines minimum required functionality for Gui windows. 
	 *		
	 * @version 1.0
	 * @date 2020-11-21
	 * 
	 * @copyright Copyright (c) 2020
	 * 
	 */	
	class IWindow
	{
		protected:

		std::string name_;
		int flag_;
		bool& show_;
		/**
		 * @brief add a helpMarker to sliders, etc 
		 * 
		 * @param desc Description displayed in the help marker
		 */
		void helpMarker(const char* desc);

		// Protected constructor to signal this is abstract
		IWindow(
			const std::string& name, 
			bool& show,
			const int& flag = 0
			): 
			name_(name), 
			flag_(flag), 
			show_(show) 
		{};

		public:
			
			/**
			 * @brief Defines window content
			 * 
			 */
			virtual void draw() = 0;			
			virtual ~IWindow() {};
	};

} // namespace gui

