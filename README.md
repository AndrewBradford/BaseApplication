# Generating 3D Platformer Levels
## Andrew Bradford (2002702) Honours Project

## Application Overview

### Purpose

To demonstrate a method of generating levels for 3D platformer games.

### Method

 - Generates a gameplay graph using a hyperedge replacement graph grammar system
 - Generates a game space using a physics-based algorithm

### Base Tech

Uses OpenGl for graphics rendering, ImGui for user interface and GLFW for window and input functionality. Also uses ImPlot for graph rendering within ImGui.

## Code Overview

### Most Relevant Classes


#### StateBase
[.h](https://github.com/AndrewBradford/BaseApplication/blob/master/BaseApplication/BaseApplication/StateBase.h)[.cpp](https://github.com/AndrewBradford/BaseApplication/blob/master/BaseApplication/BaseApplication/StateBase.cpp)

Contains app behaviour in frame() function, called by Application each frame. Handles Rendering and ui, and triggers gameplay and game space code.

#### HyperEdgeGrammar
[.h](https://github.com/AndrewBradford/BaseApplication/blob/master/BaseApplication/BaseApplication/HyperEdgeGrammar.h)[.cpp](https://github.com/AndrewBradford/BaseApplication/blob/master/BaseApplication/BaseApplication/HyperEdgeGrammar.cpp)

Contains all data and code related to gameplay generation.

#### Physics
[.h](https://github.com/AndrewBradford/BaseApplication/blob/master/BaseApplication/BaseApplication/Physics.h)[.cpp](https://github.com/AndrewBradford/BaseApplication/blob/master/BaseApplication/BaseApplication/Physics.cpp)

Containts all data and code related to game space generation.

## Application Class Diagram



## Other Classes

#### Application
[.h](https://github.com/AndrewBradford/BaseApplication/blob/master/BaseApplication/BaseApplication/Application.h)[.cpp](https://github.com/AndrewBradford/BaseApplication/blob/master/BaseApplication/BaseApplication/Application.cpp)

Sets up OpenGL (rendering), ImGui (UI), GLFW (window and input), and StateBase.

#### Shader
[.h](https://github.com/AndrewBradford/BaseApplication/blob/master/BaseApplication/BaseApplication/Shader.h)[.cpp](https://github.com/AndrewBradford/BaseApplication/blob/master/BaseApplication/BaseApplication/Shader.cpp)

Loads and activates shaders.

#### [Shader Folder](https://github.com/AndrewBradford/BaseApplication/tree/master/BaseApplication/BaseApplication/shaders)

Location of various vertex and fragment shaders used to render objects.

#### Geometry
[.h](https://github.com/AndrewBradford/BaseApplication/blob/master/BaseApplication/BaseApplication/Geometry.h)[.cpp](https://github.com/AndrewBradford/BaseApplication/blob/master/BaseApplication/BaseApplication/Geometry.cpp)

Static class which handles setting up vertex arrays and other OpenGL objects, and draw calls.

#### Shapes
[.h](https://github.com/AndrewBradford/BaseApplication/blob/master/BaseApplication/BaseApplication/Shapes.h)

Holds vertex data for various basic shapes, used to setup vertex arrays.

#### Input
[.h](https://github.com/AndrewBradford/BaseApplication/blob/master/BaseApplication/BaseApplication/Input.h)[.cpp](https://github.com/AndrewBradford/BaseApplication/blob/master/BaseApplication/BaseApplication/Input.cpp)

Holds state of tracked inputs.

#### Camera
[.h](https://github.com/AndrewBradford/BaseApplication/blob/master/BaseApplication/BaseApplication/Camera.h)[.cpp](https://github.com/AndrewBradford/BaseApplication/blob/master/BaseApplication/BaseApplication/Camera.cpp)

Handles camera movement.

#### Renderer
[.h](https://github.com/AndrewBradford/BaseApplication/blob/master/BaseApplication/BaseApplication/Renderer.h)[.cpp](https://github.com/AndrewBradford/BaseApplication/blob/master/BaseApplication/BaseApplication/Renderer.cpp)

Holds unused rendering code.







