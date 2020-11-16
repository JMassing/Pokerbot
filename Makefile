ifeq ($(OS), Windows_NT)
	RM=rm -r
	INSTALL = conan install .. -pr ../conan_configs/vs17_release 
	CONFIGURE = cmake .. -G "Visual Studio 15 2017" -T host=x86 -A x64
else
	RM=sudo rm -r
	INSTALL = conan install .. -pr ../conan_configs/gcc7_release 
	CONFIGURE = 

endif

help:
	@echo "Some available commands:"
	@echo " * prepare - Remove old build dir, create new build dir, install conan deps"
	@echo " * configure - configure cmake in build dir"
	@echo " * build_pokerbot - build target Pokerbot"
	@echo " * build_all - build all targets"

prepare:
	@$(RM) build
	@mkdir build
	@cd build && $(INSTALL) && cd ..

configure:
	@cd build && $(CONFIGURE) && cd ..

build_pokerbot:
	@cd build && cmake --build . --config Release --target Pokerbot && cd ..

build_all:
	@cd build && cmake --build . --config Release --target ALL_BUILD && cd ..