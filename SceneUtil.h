#pragma once
#include "HittableList.h"
#include "Material.h"

HittableList RandomScene();
HittableList MoonScene(shared_ptr<Material> moonMaterial);