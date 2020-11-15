ifeq ($(OS), Windows_NT)
	RM=rmdir /Q /S
	INSTALL = conan install .. -pr ../conan_configs/vs17_release 
else
	RM=sudo rm -r
	INSTALL = conan install .. -pr ../conan_configs/gcc7_release 

endif

help:
	@echo "Some available commands:"
	@echo " * prepare - Remove old build dir, create new build dir, install conan deps"

prepare:
	@$(RM) build
	@mkdir build
	@cd build && $(INSTALL) && cd ..
