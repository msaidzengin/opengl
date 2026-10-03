# opengl

Standalone GLUT and FreeGLUT example programs. Each `.cpp` file is its own program: 2D and 3D shapes, mouse and keyboard interaction, lighting, textures, and animation.

The examples were committed from 9 January 2020 through 14 February 2020. The commits do not name a course assignment.

## Build

Install a C++ compiler, FreeGLUT, and OpenGL. On Debian or Ubuntu:

```bash
sudo apt install g++ freeglut3-dev
```

`twoLines.cpp` also uses GLEW:

```bash
sudo apt install libglew-dev
```

Compile one source file into its own executable:

```bash
g++ -o triangle triangle.cpp -lGL -lGLU -lglut
```

`twoLines.cpp` needs GLEW on the link line as well:

```bash
g++ -o twoLines twoLines.cpp -lGL -lGLU -lglut -lGLEW
```

Use the same command for any other `.cpp` file, changing the output name and the source name.

## Run

```bash
./triangle
```

Replace `triangle` with the program you compiled. Where a program defines its own quit key, that key is listed below. Otherwise close the window.

- `triangle.cpp` draws a white triangle. Esc exits.
- `twoLines.cpp` draws two long lines. The left and right arrow keys turn the view between the z = 1 plane and the x = 1 plane.
- `cube.cpp` draws a lit red cube.
- `colorCube.cpp` flies around an RGB color cube.
- `rainbow.cpp` draws RGBA and ABGR images and textures. It exits if `GL_EXT_abgr` is missing. Pass `-sb` for a single buffer or `-db` for a double buffer. Esc exits.
- `animation3D.cpp` rotates a triangle.
- `ballAnimation.cpp` bounces one ball in 2D.
- `bouncingBalls.cpp` bounces several balls on a checkerboard. The arrow keys move the camera.
- `fish.cpp` draws fish bitmaps in random colors and positions.
- `moonRotate.cpp` orbits a camera around a lit sphere.
- `mouseSquares.cpp` draws a square where the mouse is clicked or dragged. A resize clears the squares. The middle-button menu changes their size. `q` or the right button exits.
- `mouseSquares2.cpp` does the same, and the squares stay when the window is redrawn.
- `robotArm.cpp` draws a wireframe arm. The up and down arrow keys bend the shoulder. The left and right arrow keys bend the elbow.
- `rotatingObjects.cpp` rotates a wire sphere, a wire cone, and a wire torus.
- `rotatingWireSphere.cpp` rotates a sphere drawn with lines.
- `shapes3D.cpp` draws a colored cube and a colored pyramid.
- `solarSystem.cpp` animates a sun, planets, moons, Saturn's ring, and asteroid points.
- `solidSphereRotate.cpp` rotates a solid sphere.
- `sphereAnimation.cpp` rotates a sphere drawn with lines.
- `wireSphereRotate.cpp` rotates a wire sphere.
- `sphereWireframe.cpp` draws a lit sphere. The right-button menu switches solid fill, wireframe, and backface culling. `e` exits.
- `spinningSquare.cpp` spins a square from the start. The left mouse button starts the spin and the right button stops it.
- `squareRotate.cpp` spins a square from the start. The left mouse button starts the spin and the right button stops it.
- `tetrahedron.cpp` draws a colored tetrahedron on a grid.
- `torus.cpp` draws a wire torus and the coordinate axes.
- `cometride.cpp` shows a sun and a planet from a moving viewpoint.
