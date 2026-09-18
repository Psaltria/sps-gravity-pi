#include "cam/Camera_system.h"

#include <SpiceUsr.h>

#include <chrono>
#include <print>
#include <string>
#include <vector>

int main() {
	std::println("Hello World!");

	//const auto camera { Camera_system::acquire_camera() };
	//auto image { camera.capture_photo() };

	furnsh_c("kernels/naif0012.tls");
	furnsh_c("kernels/de442s.bsp");

	auto now { std::chrono::system_clock::now() };
	const std::string now_iso {std::format("{:%FT%T}Z", now)};

	double et {};
	str2et_c(now_iso.c_str(), &et);

	std::println("{}", now);
}
