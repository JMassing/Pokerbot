from conans import ConanFile, CMake, tools

class PokerbotConan(ConanFile):
    name = "Pokerbot"
    version = "1.1.2"
    license = "Open Source"
    author = "Julian Massing julimassing@gmail.com"
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"
    requires = [
    ("opencv/4.1.1@conan/stable"), 
    ("boost/1.72.0"), 
    ("gtest/1.10.0"),
    ]
    default_options = {"opencv:shared": False, "boost:shared": False, "gtest:shared": False}
    exports_sources = "*"
    short_paths = True

    def source(self):
        pass

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin", keep_path=False)
        self.copy("app/imgui.ini", dst="bin") 

    def build(self, keep_imports=True):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.test()

    def package(self):
        if self.settings.os == "Windows":
            tools.rename("app/config_windows.ini", "app/config.ini")
        else:
            tools.rename("app/config_linux.ini", "app/config.ini")

        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)
        self.copy("Pokerbot.exe", dst="bin", src="bin", keep_path=False)
        self.copy("Pokerbot", dst="bin", src="bin", keep_path=False)
        self.copy("Card_Imgs/*", dst="", keep_path=True)
        self.copy("app/config.ini", dst="", keep_path=False)
        self.copy("app/imgui.ini", dst="bin", keep_path=False) 
 
    def package_info(self):
        self.cpp_info.libs = ["opencv", "boost", "gtest"]

