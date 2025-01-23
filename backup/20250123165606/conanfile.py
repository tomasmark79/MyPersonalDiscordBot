from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMake

class CompressorRecipe(ConanFile):
    name = "compressor"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"
    default_options = {
        "dpp/*:shared": False,
        "zlib/*:shared": False,
        "fmt/*:shared": False,
        "openssl/*:shared": False,
        "nlohmann_json/*:shared": False,
        "opus/*:shared": False,
        "libcurl/*:shared": False
    }

    def requirements(self):
        self.requires("dpp/10.0.35")  # Zajištění, že dpp je vyžadováno.
        self.requires("zlib/1.3.1")
        self.requires("fmt/11.1.1")
        self.requires("openssl/3.3.2")
        self.requires("nlohmann_json/3.11.2")
        self.requires("opus/1.4")
        self.requires("libcurl/8.10.1")

    def configure(self):
        # Zajistit statické sestavení.
        self.options["dpp"].shared = False
        self.options["dpp"].fPIC = True
        self.options["dpp"].BUILD_SHARED_LIBS = False

    # def layout(self):
    #     cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
