from conans import ConanFile, CMake

class RouteOperatorDriverLicenses(ConanFile):
    name = "route-operator-driver-licenses-post"
    version = "1.0.3"
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake", "txt"
    exports_sources = "CMakeLists.txt", "src/*", "include/*"
    options = {
        "coverage": [False, True]
    }
    default_options = {
        "coverage" : False
    }

    def build_requirements(self):
        self.build_requires("cmake-common-options/[^1.0.0, loose=False]")
        self.build_requires("boost-ext-ut/[^1.1.8, loose=False]")

    def imports(self):
        self.copy("commonoptions.cmake")
        self.copy("cpp-server", src="bin", dst="bin")

    def requirements(self):
        self.requires("service-security/[^3.0.0, loose=False]@obspher/stable")
        self.requires("mysql-obspher/[^0.0.1, loose=False]@obspher/stable")
        self.requires("api-core/[^1.0.0, loose=False]@obspher/stable")
        self.requires("api-obspher/[^0.0.1, loose=False]@obspher/stable")
        self.requires("cpp-server/[^3.0.0, loose=False]@obspher/stable")

    def build(self):
        cmake = CMake(self)
        if self.options.coverage:
            cmake.definitions["CONAN_C_FLAGS"] += " -fprofile-arcs -ftest-coverage"
            cmake.definitions["CONAN_CXX_FLAGS"] += " -fprofile-arcs -ftest-coverage"
        cmake.configure()
        cmake.build()
        cmake.test()
        if self.options.coverage:
            self.run('gcovr -r %s' % (self.source_folder))

    def package(self):
        self.copy("*.so", dst="lib", src="lib")
        self.copy("*.a", dst="lib", src="lib")
        self.copy("*.hpp", dst="include", src="include")

    def package_info(self):
        self.cpp_info.libs = ["route-operator-driver-licenses-post-static"]
