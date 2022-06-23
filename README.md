<<<<<<< HEAD
<<<<<<< HEAD
PostLambert: A ray tracer extending the Lambertian model of Diffuse Reflection
====================================================================================================

This project implements a ray tracer that simulates several diffuse scattering models that are more complex than the Lambertian scattering model. For notes and the mathematical background that explains these models, see the accompanying PDF, tentatively titled "PostLambertianDraft.pdf."

| ![Base Moon][basemoon]       | ![lunar][lunarlambertmoon]  | 
|:----------------------------:|:---------------------------:|
|          Standard Lambertian Diffuse Reflection           |      The Lunar-Lambert model of Diffuse Reflection, which accurately captures the glow of the Moon due to the presence of multiple scattering centers in the material that comprises the Moon.         | 

## Digest

Often commonly used in computer graphics, the Lambertian model is an idealization of diffuse scattering. However, the real world almost always features objects in which diffuse scattering is much more complex than thatwhich can be approximated with the Lambertian model. Phenomena such as subsurface scattering, coherent backscattering, retroreflection, are not accounted for; there exist more suitable models that can handle diffuse reflection more accurately. This program implements models derived from planetary astronomy that have been found to be more accurate in some circumstances. It is perhaps of interest for those seeking to make more visually-realistic materials in the realm of computer graphics.
=======
=======
PostLambert: A ray tracer extending the Lambertian model of Diffuse Reflection
====================================================================================================

>>>>>>> b1524f5... Minnaert plus read me.
This project implements several diffuse scattering models that are more complex than the Lambertian scattering model. For notes and the mathematical background that explains these models, see the accompanying PDF, tentatively titled "PostLambertianDraft.pdf."

## Digest

Often commonly used in computer graphics, the Lambertian model is an idealization of diffuse scattering. However, the real world almost always features objects in which diffuse scattering is much more complex than thatwhich can be approximated with the Lambertian model. Phenomena such as subsurface scattering, coherent backscattering, retroreflection, are not accounted for; there exist more suitable models that can handle diffuse reflection more accurately.

This program implements models derived from planetary astronomy that have been found to be more accurate in some circumstances. It is perhaps of interest for those seeking to make more visually-realistic materials in the realm of computer graphics.

## Usage

1. Clone this repository
2. Compile to Release with Visual Studio. (All results here are compiled with MSVC++ 14.21 (Visual Studio 2019 version 16.1))
3. Run from the command line. Note that the output will be a .ppm file. So for example, running 

```bash
./postlambert.exe > "test.ppm"
```

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
    
  -Astronomical bodies. Given that these models were derived by astronomers for the purposes of making their mathematical formulae more accurate, from a physically-based rendering point of view, this is probably the most applicable situation.
  -Materials with a large amount of dust, dirt, or other small particulates covering the surface. Comets, asteroids and the Moon all have thick layers of dust covering their surfaces. These models capture this behavior.
  -Situations in which diffuse light scattering is not uniform (heterogenous materials, or situations in which thick atmospheres surround the diffuse body)
  -Situations in which a "glow-effect" is desired, or other desirable effects that may not be rooted in reality.

Try and see for yourself if these Post-Lambert materials are suitable for your project!

## Should I use PostLambert in my project?

  -Compared to the standard treatment of diffuse reflection, each of the post-Lambertian models take longer to implement and run. But perhaps the benefits of capturing some aspects of subsurface scattering, and other phenomena make it desirable.
>>>>>>> f7512d0... Resource files changes, and Readme.

## Can you briefly summarize the technical implementation?

<<<<<<< HEAD
## Usage

1. Clone this repository.

2. Compile to Release with Visual Studio. (Note well, this code project uses some Japanese characters. That may cause some compilation errors. If you encounter compilations, ensure that the file is encoded in UTF-8 and retry.)

3. The project comes with two images, they can be swapped out with one's own background images, or moon textures by changing filenames in the FileResources.h file:

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

`Config.h`:
```c++
const static SCENEPATH ScenePath = MOON;
```

with 

`Config.h`:
```c++
const static SCENEPATH ScenePath = BALL_SCENE;
```

Many other parameters related to the camera controls can also be tweaked:

`Config.h`:
```c++
const static double AspectRatio = 2.0;
const static int ImageWidth = 1600;
const static int ImageHeight = static_cast<int> (ImageWidth / AspectRatio);
const static int SamplesPerPixel = 100;
const static int MaxDepth = 30;
```

To swap out the specified material with reflection models, simply swap open up `main.cpp` and switch the line

`main.cpp`:
```C++
shared_ptr<Material> moonMaterial = make_shared<LommelSeeliger>(moonTexture);
```

with the desired Material:

`main.cpp`:
```C++
shared_ptr<Material> moonMaterial = make_shared<Hapke>(moonTexture, 1);
```

Note that, the number of arguments into the constructor may change. Consult the PDF for explanations on how to tweak the accompanying values.

5. Run from either the command line or by just running with Visual Studio. There are no command line arguments to pass in.

The default output location is "postlambert.bmp". It can be changed here:
`FileResources.h`:
```c++
const static string OUTPUT = "postlambert.bmp";
```

## Image Gallery

The following section compares post-Lambertian models of the Moon with the standard Lambertian model:

| ![Base Moon][basemoon]       | ![Lommel][lommelmoon]       | 
|:----------------------------:|:---------------------------:|
|          Base Moon           |         Lommel-Seeliger model. It assumes that scattering is isotropic.      | 

| ![Base Moon][basemoon]       | ![Minnaert][minnaertmoon]   | 
|:----------------------------:|:---------------------------:|
|          Base Moon           |           Minnaert model. It takes a single parameter n in a generalization of Lambert's Law. By setting n = 1, it reduces to Lambertian scattering.          | 

| ![Base Moon][basemoon]       | ![lunar][lunarlambertmoon]  | 
|:----------------------------:|:---------------------------:|
|          Base Moon           |       Lunar Lambert model. It takes two parameters A and B, which alters the strength of the overall affect.         | 

| ![Base Moon][basemoon]       | ![Minnaert][hapkemoon]   | 
|:----------------------------:|:---------------------------:|
|          Base Moon           |             Hapke model. It takes a single parameter theta, which models the roughness of the surface. | 

Using a post-Lambertian material can give a flat-looking diffuse surface depth:

| ![Base scene][basescene]     | ![Minnaert][minnaertscene]  | 
|:----------------------------:|:---------------------------:|
|          Base Scene          |  Minnaert -- applied only to the diffuse (non-glass, non-metallic) balls.                   | 

It should be noted that even though post-Lambertian scattering models are often desirable, using them willy-nilly on any diffuse material may not be desirable:

| ![Base scene][basescene]     | ![Hapke Scene][hapkescene]  | 
|:----------------------------:|:---------------------------:|
|          Base Moon           |  Hapke, but the balls appear radioactive      | 

PostLambertian models can be used to create a variety of looks. Though not rooted in reality, here are some examples:

| ![Planet 1][planet1]         | ![Planet 3][planet3]        | 
|:----------------------------:|:---------------------------:|
| ![Planet 2][planet2]         | ![Planet 4][planet4]        | 

## In what situations are post-Lambert materials usable?
      
  * Materials with a large amount of dust, dirt, or other small particulates covering the surface. Comets, asteroids and the Moon all have thick layers of dust covering their surfaces. These models capture this behavior.
  
  * Situations in which diffuse light scattering is not uniform (heterogenous materials, or situations in which thick atmospheres surround the diffuse body).
  
  * Situations in which a "glow-effect" is desired, or other desirable effects that may not be rooted in reality.

  * It is worth noting that given that these models were derived by astronomers for the purposes of making their mathematical formulae more accurate, from a physically-based rendering point of view, astronomical bodies are probably the most applicable situation.

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

[planet1]:          OutputGallery/postlambert_output.bmp
[planet2]:          OutputGallery/postlambert_output2.bmp
[planet3]:          OutputGallery/postlambert_output3.bmp
[planet4]:          OutputGallery/daymoon.png

## Disclaimers:

No copyright infringement is intended. A full list of sources is provided in the accompanying PDF. 
Original code was based on "Ray Tracing Weekend" series.
Makes use of the EasyBMP library to output BMPs.
=======
  -During most implementations of diffuse scattering in ray tracing, a ray is randomly picked from the unit sphere / unit circle since it is assumed that diffuse light is scattered everywhere equally. The brightness of the ray is attenuated per the Lambert cosine formula. For each post-Lambert material, the brightness of the ray is altered in accordance with the physical law being implemented (e.g., Minnaert's Law, Lommel-Seeliger's law, etc.)
  -In the case of Hapke's Law, surface roughness is taken into account, and a particle phase function is implemented, allowing for non-uniform scattering.
<<<<<<< HEAD
>>>>>>> f7512d0... Resource files changes, and Readme.
=======

[basemoon]:          OutputGallery/base.png
[minnaertmoon]:          OutputGallery/minnaert.png
[lunarlambertmoon]:          OutputGallery/lunarlambert.png
[lommelmoon]:          OutputGallery/lommelseeliger.png
[hapkemoon]:          OutputGallery/hapke.png

[basescene]:          OutputGallery/scene.png
[minnaertscene]:          OutputGallery/minnaertscene.png
[hapkescene]:          OutputGallery/HapkeScene.png
>>>>>>> b1524f5... Minnaert plus read me.
