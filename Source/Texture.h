#pragma once
#include <glm/vec3.hpp>
#include <vector>
#include <string>

class Texture
{
	enum class ImageFormat {
		PNG = 0,
		JPG = 1,
	};

	static unsigned LoadTexture(const char* image, ImageFormat fmt);
	static unsigned LoadCubemap(const std::vector<std::string>& faces);
};