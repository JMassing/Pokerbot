#pragma once

#include <string>
#include <imgui.h>

namespace gui {

	class IWindow
	{
		protected:

		std::string name_;
		int flag_;
		bool show_;
		void helpMarker(const char* desc);

		// Protected constructor to signal this is abstract
		IWindow(const std::string& name, const int& flag = 0): name_(name), flag_(flag), show_(true) {};

		public:
			
			virtual bool draw() = 0;			
			virtual ~IWindow() {};
	};

} // namespace gui

