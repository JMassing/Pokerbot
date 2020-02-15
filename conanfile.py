from conans import ConanFile, CMake, tools


class PokerbotConan(ConanFile):
    name = "Pokerbot"
    version = "0.1.0"
    license = "Open Source"
    author = "Julian Massing julimassing@gmail.com"
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"
    requires = [("opencv/4.1.1@conan/stable"), ("boost/1.72.0")]
    default_options = {"opencv:shared": False, "boost:shared": False}

    #def source(self):
        # This small hack might be useful to guarantee proper /MT /MD linkage
        # in MSVC if the packaged project doesn't have variables to set it
        # properly
       # tools.replace_in_file("hello/CMakeLists.txt", "PROJECT(HelloWorld)",
       #                       '''PROJECT(HelloWorld)
#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#conan_basic_setup()''')
    def imports(self):
        self.copy("*.dll", dst="bin", src="bin") # From bin to bin
        self.copy("*.dylib*", dst="bin", src="lib") # From lib to bin

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    #def package(self):
    #   self.copy("*.h", dst="include", src="src")
    #   self.copy("*Pokerbot.lib", dst="lib", keep_path=False)
    #    self.copy("*.dll", dst="bin", keep_path=False)
    #    self.copy("*.so", dst="lib", keep_path=False)
    #    self.copy("*.dylib", dst="lib", keep_path=False)
    #    self.copy("*.a", dst="lib", keep_path=False)

    #def package_info(self):
    #    self.cpp_info.libs = ["opencv", "boost"]

