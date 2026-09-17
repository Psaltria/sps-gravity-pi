#include "cam/Camera_system.h"

#include <print>
#include <vector>

int main() {
	std::println("Hello World!");

	const auto camera { Camera_system::acquire_camera() };

	auto image { camera.capture_photo() };
}
