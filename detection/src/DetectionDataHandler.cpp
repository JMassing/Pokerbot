#include "DetectionDataHandler.hpp"

namespace detect{

    void DetectionDataHandler::attachCaptureInterface(std::shared_ptr<IDetectCapture> interface)
	{
		this->capture_interface_ = interface;
	}

    void DetectionDataHandler::attachGuiInterface(std::shared_ptr<IDetectGui> interface)
	{
		this->gui_interface_ = interface;
	}

    bool DetectionDataHandler::getLiveFrame(Image& image) const
    {
        // get live frame from camera if connected
		if(this->capture_interface_ != nullptr)
		{
			image = this->capture_interface_->getImage();
            return true;
		}
        else
        {
            return false;
        } 
    }

    bool DetectionDataHandler::getProcessingSettings(ImProcSettings& settings) const
    {
        // get settings from GUI if a GUI is connected
		if(this->gui_interface_ != nullptr)
		{
			if(this->gui_interface_->checkUserInput())
			{
				settings = this->gui_interface_->getSettings();
                return true;
			}
		}
        return false;       
    }

    bool DetectionDataHandler::sendDetectedCards(const std::vector<Card>& cards) const 
    {
        // send cards to GUI if a GUI is connected
		if(this->gui_interface_ != nullptr)
		{
			this->gui_interface_->setCards(cards);
            return true;
		}
        else
        {
            return false;
        }
    }
} // end namespace detect