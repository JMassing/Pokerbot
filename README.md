# Pokerbot
Welcome! This is an open-source project. It is intended for experimenting and testing different ideas and concepts. If you have any questions or suggestions, you can contact me at julimassing@gmail.com. 

## Introduction
Pokerbot is a c++-project that uses OpenCV image processing methods to detect cards from a USB-camera feed and can play texas holdem poker against a human player. The decision making of the bot in this version is purely probability based using Monte Carlo Simulation. It takes the current game state into account and calcualtes the probability of winning with the bot's hand. The bot makes a decision based on the winning probability and the potsize and bets placed by the player. Refer to the HowTo section for instructions on how to build an use the Pokerbot. 
Pokerbot currently only runs on Windows.

I am planning to implement the following in the future (in not particular order):
* Build and run on Linux
* Use Depp Learning for card detection
* Use Mulithreading to improve runtime of monte-carlo simulation
* Make the bot smarter by using a more sophisticated decision making

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
* Build files will be created in the conan-build folder, while the Pokerbot.exe will be created in the conan-package folder
* The build and package folders are given when the build is finished (looks something like: C:\/.conan\41e8cc\1)
* You can also find the package folder by using the command _conan info --paths Pokerbot/1.0.0@ -pr conan_configs/vs17_release_. Look for the Pokerbot/1.0.0 package-folder.
* The package folder given by the conan info command will have a .conan_link file which contains the path to the real package folder.
* Build Dependencies:
    * OpenCV >= v4.1.1 
    * Boost >= v 1.72
    * Gtest >= v1.10.0
    * ImGui >= v1.72b https://github.com/ocornut/imgui
    * glfw >= v3.3 https://github.com/glfw/glfw.git
    * Opengl