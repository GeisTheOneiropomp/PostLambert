PostLambert: A ray tracer extending the Lambertian model of Diffuse Reflection
====================================================================================================

This project implements several diffuse scattering models that are more complex than the Lambertian scattering model. For notes and the mathematical background that explains these models, see the accompanying PDF, tentatively titled "PostLambertianDraft.pdf."

## Digest

Often commonly used in computer graphics, the Lambertian model is an idealization of diffuse scattering. However, the real world almost always features objects in which diffuse scattering is much more complex than thatwhich can be approximated with the Lambertian model. Phenomena such as subsurface scattering, coherent backscattering, retroreflection, are not accounted for; there exist more suitable models that can handle diffuse reflection more accurately.

This program implements models derived from planetary astronomy that have been found to be more accurate in some circumstances. It is perhaps of interest for those seeking to make more visually-realistic materials in the realm of computer graphics.

## Usage

1. Clone this repository.
2. Compile to Release with Visual Studio. (Note well, this code project uses some Japanese characters,
3. Run from the command line. Note that the output will be a .ppm file. So for example, running 

```bash
./postlambert.exe > "test.ppm"
```
will generate a file called test.ppm that outputs the ray-traced image.
4. The project comes with two images, they can be swapped out with one's own background images, or moon textures by changing filenames in the FileResources.h file:

`FileResources.h`:
```c++
#include <string>
using namespace std;
#pragma once

const static string MOON_FILE = "extern\\img\\moon.jpg";
const static string SKYBOX_FILE = "extern\\img\\nightsky.jpg";
```

5. The default setting is to generate an image of the moon. To change the scene to balls randomly distributed throughout the scene, open the `Config.h` file, and change the variable: 

```c++
const static SCENEPATH ScenePath = MOON;
```

with 

```c++
const static SCENEPATH ScenePath = BALL_SCENE;
```

Many other parameters related to the camera controls can also be tweaked:

```c++
const static double AspectRatio = 2.0;
const static int ImageWidth = 1600;
const static int ImageHeight = static_cast<int> (ImageWidth / AspectRatio);
const static int SamplesPerPixel = 100;
const static int MaxDepth = 30;
```

To swap out the specified material with reflection models, simply swap open up `main.cpp` and switch the line

```C++
shared_ptr<Material> moonMaterial = make_shared<LommelSeeliger>(moonTexture);
```

with the desired Material:

```C++
shared_ptr<Material> moonMaterial = make_shared<Hapke>(moonTexture, 1);
```

Note that, the number of arguments into the constructor may change. Consult the PDF for explanations on how to tweak the accompanying values.

## Image Gallery

The following section compares post-Lambertian models of the Moon with the standard Lambertian model:

| ![Base Moon][basemoon]       | ![Minnaert][minnaertmoon]   | 
|:----------------------------:|:---------------------------:|
|          Base Moon           |           Minnaert          | 

| ![Base Moon][basemoon]       | ![lunar][lunarlambertmoon]  | 
|:----------------------------:|:---------------------------:|
|          Base Moon           |           Lunar Lambert     | 

| ![Base Moon][basemoon]       | ![Lommel][lommelmoon]       | 
|:----------------------------:|:---------------------------:|
|          Base Moon           |         Lommel-Seeliger     | 

| ![Base Moon][basemoon]       | ![Minnaert][minnaertmoon]   | 
|:----------------------------:|:---------------------------:|
|          Base Moon           |             Hapke           | 

Using a post-Lambertian material can give a flat-looking diffuse surface depth:

| ![Base scene][basescene]     | ![Minnaert][minnaertscene]  | 
|:----------------------------:|:---------------------------:|
|          Base Scene          |  Minnaert                   | 

It should be noted that even though post-Lambertian scattering models are often desirable, using them willy-nilly on any diffuse material may not be desirable:

| ![Base scene][basescene]     | ![Hapke Scene][hapkescene]  | 
|:----------------------------:|:---------------------------:|
|          Base Moon           |  Hapke, but radioative      | 

## In what situations are post-Lambert materials usable?
    
  * Astronomical bodies. Given that these models were derived by astronomers for the purposes of making their mathematical formulae more accurate, from a physically-based rendering point of view, this is probably the most applicable situation.
  
  * Materials with a large amount of dust, dirt, or other small particulates covering the surface. Comets, asteroids and the Moon all have thick layers of dust covering their surfaces. These models capture this behavior.
  
  * Situations in which diffuse light scattering is not uniform (heterogenous materials, or situations in which thick atmospheres surround the diffuse body).
  
  * Situations in which a "glow-effect" is desired, or other desirable effects that may not be rooted in reality.

Try and see for yourself if these Post-Lambert materials are suitable for your project!

## Should I use PostLambert in my project?

  * Compared to the standard treatment of diffuse reflection, each of the post-Lambertian models take longer to implement and run. But perhaps the benefits of capturing some aspects of subsurface scattering, and other phenomena make it desirable.

## Can you briefly summarize the technical implementation?

  * During most implementations of diffuse scattering in ray tracing, a ray is randomly picked from the unit sphere / unit circle since it is assumed that diffuse light is scattered everywhere equally. The brightness of the ray is attenuated per the Lambert cosine formula. For each post-Lambert material, the brightness of the ray is altered in accordance with the physical law being implemented (e.g., Minnaert's Law, Lommel-Seeliger's law, etc.)
  * In the case of Hapke's Law, surface roughness is taken into account, and a particle phase function is implemented, allowing for non-uniform scattering.

[basemoon]:          OutputGallery/base.png
[minnaertmoon]:          OutputGallery/minnaert.png
[lunarlambertmoon]:          OutputGallery/lunarlambert.png
[lommelmoon]:          OutputGallery/lommelseeliger.png
[hapkemoon]:          OutputGallery/hapke.png

[basescene]:          OutputGallery/scene.png
[minnaertscene]:          OutputGallery/minnaertscene.png
[hapkescene]:          OutputGallery/HapkeScene.png
