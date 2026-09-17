#pragma once

#include <gphoto2/gphoto2.h>

#include <vector>

class Camera_system {
public:
	using Image = std::vector<unsigned char>;

	~Camera_system() {
		gp_camera_exit(camera_, context_);
	}

	Camera_system(const Camera_system&) = delete;
	Camera_system(const Camera_system&&) = delete;

	Camera_system& operator=(const Camera_system&) = delete;
	Camera_system& operator=(const Camera_system&&) = delete;

	static Camera_system acquire_camera();

	[[nodiscard]] Image capture_photo() const;

private:
	Camera_system(Camera* camera, GPContext* context) : camera_ { camera }, context_ { context } {}

	static void check_result(const int result);

	Camera* camera_;
	GPContext* context_;
};