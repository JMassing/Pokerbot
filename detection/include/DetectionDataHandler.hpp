#pragma once

#include <memory>

#include "IDetectionDataHandler.hpp"
#include "IDetectGui.hpp"
#include "IDetectCapture.hpp"


namespace detect
{
	/** 
	 * \ingroup detection
	 * @class DetectionDataHandler
	 * @author Julian Massing (julimassing@gmail.com)
	 * @brief Handles communication to gui and capture modules
	 *
	 * @version 1.0
	 * @date 2020-11-18
	 * 
	 * @copyright Copyright (c) 2020
	 * 
	 */
	class DetectionDataHandler: public IDetectionDataHandler
	{

		private:
			// Interfaces
			std::shared_ptr<IDetectGui> gui_interface_;
			std::shared_ptr<IDetectCapture> capture_interface_;

		public:
			/**
			 * @brief Attach communication interface to GUI
			 * 
			 * @param interface GUI interface
			 */
			void attachGuiInterface(std::shared_ptr<IDetectGui> interface);

			/**
			 * @brief Attach communication interface to capture module
			 * 
			 * @param interface Capture interface
			 */
			void attachCaptureInterface(std::shared_ptr<IDetectCapture> interface);

			/**
			 * @brief Get live frame from capture module
			 * 
			 * @param image Destination image
			 * @return true if image was grabbed
			 * @return false if no image was grabbed
			 */
			bool getLiveFrame(Image& image) const override;

			/**
			 * @brief Get processing settings from gui module
			 * 
			 * @param settings Image processing settings
			 * @return true if settings were changed
			 * @return false if settings were not changed
			 */
			bool getProcessingSettings(ImProcSettings& settings) override;
			
			/**
			 * @brief Send detected cards to Capture gui
			 * 
			 * @return true if data was send
			 * @return false if no data was send
			 */
			bool sendDetectedCards(const std::vector<Card>& cards) const override;


			DetectionDataHandler():gui_interface_{nullptr}, capture_interface_{nullptr} {};
			~DetectionDataHandler(){};

			// Using default copy and move constructors. 
			DetectionDataHandler(const DetectionDataHandler& other) = default;	
			DetectionDataHandler& operator=(const DetectionDataHandler& other) = default;
			DetectionDataHandler(DetectionDataHandler&& other) noexcept = default;
			DetectionDataHandler& operator=(DetectionDataHandler&& other) noexcept = default;
	};
}// end namespace signals