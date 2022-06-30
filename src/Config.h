#pragma once
enum SCENEPATH { MOON, BALLSCENE };

const static SCENEPATH ScenePath = MOON;
const static double AspectRatio = (16.0 / 9.0);
const static int OutputImageWidth = 1600;
const static int OutputImageHeight = static_cast<int> (OutputImageWidth / AspectRatio);
const static int SamplesPerPixel = 100;
const static int MaxDepth = 30;