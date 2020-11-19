ifeq ($(OS), Windows_NT)
	RM = rm -r
	PROFILE = vs17
	CONFIGURE = cmake .. -G "Visual Studio 15 2017" -T host=x86 -A x64
else
	RM = sudo rm -r
	PROFILE = gcc7
	CONFIGURE = 
endif

help:
	@echo "Some available commands:"
	@echo " * prepare_release - Remove old build dir if exists, create new build dir, install conan deps as release"
	@echo " * prepare_debug - Remove old build dir if exists, create new build dir, install conan deps as debug"
	@echo " * configure - configure cmake in build dir"
	@echo " * build_release - build Pokerbot in release mode"
	@echo " * build_debug - build Pokerbot in unit test mode"
	@echo " * documentation - create doxygen documentation in docs folder"

prepare_release:
	@if [ -d "./build" ]; then $(RM) build; fi 
	@mkdir build
	@cd build && conan install .. -pr ../conan_configs/$(PROFILE)_release && cd ..

prepare_debug:
	@if [ -d "./build" ]; then $(RM) build; fi 
	@mkdir build
	@cd build && conan install .. -pr ../conan_configs/$(PROFILE)_debug && cd ..

configure:
	@cd build && $(CONFIGURE) && cd ..

build_release:
	@cd build && cmake --build . --config Release --target ALL_BUILD && cd ..

build_debug:
	@cd build && cmake --build . --config Debug --target ALL_BUILD && cd ..

documentation:
	@cd build && cmake --build . --target Pokerbot_docs && cd ..