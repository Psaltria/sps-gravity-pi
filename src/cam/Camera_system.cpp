#include "cam/Camera_system.h"

#include <gphoto2/gphoto2.h>
#include <gphoto2/gphoto2-port-result.h>

#include <cassert>
#include <print>
#include <stdexcept>
#include <vector>

Camera_system Camera_system::acquire_camera() {
	GPContext* context { gp_context_new() };
	assert(context);

	Camera* camera { nullptr };

	auto result = gp_camera_new(&camera);
	check_result(result);

	result = gp_camera_init(camera, context);
	check_result(result);

	return { camera, context };
}

Camera_system::Image Camera_system::capture_photo() const {
	CameraFilePath path {};
	auto result = gp_camera_capture(camera_, GP_CAPTURE_IMAGE, &path, context_);
	check_result(result);

	std::println("Image path: {}/{}", path.folder, path.name);

	CameraFile* file { nullptr };
	result = gp_file_new(&file);
	check_result(result);

	result = gp_camera_file_get(camera_, path.folder, path.name, GP_FILE_TYPE_NORMAL, file, context_);
	check_result(result);

	const char* data { nullptr };
	std::uint64_t size { 0 };

	result = gp_file_get_data_and_size(file, &data, &size);
	check_result(result);

	Image image(reinterpret_cast<const unsigned char*>(data), reinterpret_cast<const unsigned char*>(data) + size);
	gp_file_free(file);

	return image;
}

void Camera_system::check_result(const int result) {
	if (result < GP_OK) {
		throw std::runtime_error(gp_result_as_string(result));
	}
}
