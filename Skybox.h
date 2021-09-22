#pragma once
#include "Vec3.h"
#include "ImageTexture.h"
using std::string;
class Skybox
{
public:
	Skybox();
	Skybox(string filename);
	std::vector<std::shared_ptr<ImageTexture>> texturePointers;
	Color getValue(const Vec3 point) const;

};

