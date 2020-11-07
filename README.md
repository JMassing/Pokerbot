# Pokerbot
Welcome! This is an open-source project. It is intended for experimenting and testing different ideas and concepts and in general just have some fun :grinning:. If you have any questions or suggestions, you can contact me at julimassing@gmail.com. 

## Introduction
Pokerbot is a c++-project that uses OpenCV image processing methods to detect cards from a USB-camera feed and can play texas holdem poker against a human player. The decision making of the bot in this version is purely probability based using Monte Carlo Simulation. It takes the current game state into account and calculates the probability of winning with the bot's hand. The bot makes a decision based on the winning probability and the potsize and bets placed by the player. Refer to the HowTo section for instructions on how to build and use the Pokerbot. The Pokerbot currently only runs on Windows.

I am planning to implement the following in the future (in no particular order):
* Use Deep Learning for card detection
* Use Multithreading to improve runtime of Monte Carlo Simulation
* Make the bot smarter by using a more sophisticated decision making
* Game.cpp needs some refactoring

## Releases
See the Releases section

## HowTo
### Build Pokerbot
* Pokerbot uses the Conan package-manager and cmake for building the project https://conan.io/
* To use Conan you need python version > 3.5 
* See https://docs.conan.io/en/latest/installation.html on how to install conan
* Conan config files for visual studio 15 and 17 compilers are prepared in the conan_configs directory of the source directory
* To build the project download the source code and change into the source directory
* Use _conan create . -pr conan_configs/<config_file>_ to build the project, where config_file is one of the files given in the conan_config folder (e.g. vs17_release)
* Conan will download the build dependencies given in the conan-file (conanfile.py) from conan-center (https://bintray.com/conan/conan-center)
* Build files will be created in the conan-build folder, while the Pokerbot package will be created in the conan-package folder
* The build and package folders are given when the build is finished (looks something like: C:\\.conan\41e8cc\1)
* You can also find the build/package folder by using the command _conan info --paths Pokerbot/1.0.0@_.  Look for the Pokerbot/1.0.0 package-folder.
* If you get the error _ERROR: opencv/4.1.1@conan/stable: Invalid configuration: OpenCV 4.x requires Visual Studio 2015 and higher_ use _conan info --paths Pokerbot/1.0.0@ -pr conan_configs/<config_file>_, where _<config_file>_ is the conan config you used during build.

<img src="./docs/Conan-Info.png" width="500"/></img>
* The build/package folder given by the conan info command will have a .conan_link file which contains the path to the real package folder.
* Both build and package folder will have a bin/Pokerbot.exe you can use to start the pokerbot. The package folder is used to create the .zip for each release.
* Build Dependencies Windows:
    * OpenCV v4.1.1 
    * Boost v1.72
    * Gtest v1.10.0
    * ImGui v1.72b https://github.com/ocornut/imgui
    * glfw v3.3 https://github.com/glfw/glfw.git
    * Opengl
    * VS15 compiler or higher
    * Conan v1.30 or higher
    * Python v3.5 or higher
    * cmake v3.10 or higher
* Build Dependencies Linux (Ubuntu 18.04):
    * OpenCV v4.1.1 
    * Boost v1.72
    * Gtest v1.10.0
    * ImGui v1.72b https://github.com/ocornut/imgui
    * glfw v3.3 https://github.com/glfw/glfw.git
    * g++7
    * Conan v1.30 or higher
    * Python v3.5 or higher
    * build-essentials
    * cmake v3.10 or higher
    * libglu1-mesa, libglu1-mesa-dev, xorg-dev, libglew-dev, libx11-dev, libglfw3-dev
 
## Use Pokerbot
* We use OpenCV to control the camera. The OpenCV VideoCapture class uses the member device_id to determine the camera. 
    * device_id = 0 is usually the integrated webcam, whereas usb cameras are usually device_id = 1 on windows. On linux I usually got device_id = 2 for my usb camera.
    * The config.ini initially sets the device_id. The default value is 1 for windows builds and 2 for linux builds. You can change the device_id in the config.ini to the appropiate value for the camera you are using.
* The config.ini also contains initial values for camera and processing settings, which can be overwritten by using the "save as default" button. 
* Use Pokerbot.exe to start the pokerbot
* First, place a playing card within the camera view and adjust camera settings and processing settings until the card is detected
<img src="./docs/Pokerbot_Settings.png" width="700"/></img>
* To start a game press the "start game" button
* Follow the instructions in the top left corner of the live view
<img src="./docs/RobotHand_Shown.png" width="700"/></img>
* Probability of Winning shows the probability that the robot will win the current hand. Probability of Winning Tie shows the probability of a tie.
* Activate "mask robot cards" and deactivate "show probability" and "show robot hand" when playing a real game against the bot.  
<img src="./docs/RobotHand_masked.png" width="700"/></img>
* Have fun :grinning:
