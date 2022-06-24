#pragma once
enum SCENEPATH { MOON, BALLSCENE };

const static SCENEPATH ScenePath = MOON;
const static double AspectRatio = (16.0 / 9.0);
const static int ImageWidth = 1600;
const static int ImageHeight = static_cast<int> (ImageWidth / AspectRatio);
const static int SamplesPerPixel = 100;
const static int MaxDepth = 30;