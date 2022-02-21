# PostLambert

This project implements several diffuse scattering models that are more complex than the Lambertian scattering model. For notes and the mathematical background that explains these models, see the accompanying PDF, tentatively titled "PostLambertianDraft.pdf."

To run the project: download the project, open the Visual Studio Solution, and compile to "Release" from Visual Studio, and then run from the command line. The format of the output will be .ppm file.  So for example, calling ./postlambert.exe > "test.ppm" will generate the ray traced image into a file named "test.ppm."

The project comes with several images, they can be swapped out with one's own background images by changing filenames in the Resources.h file. 

For the time being, the parameters of the actual image (such as the dimensions of the output, can be changed in the main.cpp file.

No copyright infringement intended.
