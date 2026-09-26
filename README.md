# Pigtail: how to use it in your own C++ projects

Pigtail is a small engine framework you can use as a base for your own game or software project. Instead of treating it like a finished engine, think of it as a starter toolkit: it gives you a runtime, a project structure, and a set of building blocks you can extend.

This README explains how to use the project for your own programming, rather than just listing the files.

## 1. What this project is for

Use Pigtail when you want to:

- build a game prototype quickly
- create your own C++ rendering or gameplay experiments
- learn how an engine is structured in practice
- modify game systems without starting from zero
- add custom scenes, entities, behaviors, and assets

In other words, this is not a locked engine. It is a foundation that you can customize.

## 2. How the project is organized

The important parts for your own work are:

- Engine/include: public engine headers you include in your own code
- Engine/src: the engine implementation
- Assets: images, audio, shaders, and other content
- Scripts: Lua and Python support files
- ThirdParty/glad: OpenGL loader support

If you are building your own program, you usually work in the engine code and the sandbox app together. The sandbox is a test project for trying features before you move them into your own game code.

## 3. Set up GLAD with Python

This project uses GLAD for OpenGL loading. Because `ThirdParty` is git-ignored for you, the usual pattern is to create the folder locally and generate GLAD there without committing it.

### Install GLAD

First install the Python package:

```bash
pip install glad2
```

If you use a virtual environment, activate it first, then run the command above.

### Create a local ThirdParty folder

From the project root:

```bash
mkdir ThirdParty
cd ThirdParty
```

### Generate the library files

Generate the GLAD loader into a local folder inside `ThirdParty`:

```bash
python -m glad --profile=core --api=gl=3.3 --generator=c --out-path=glad
```

This creates a `glad` folder inside `ThirdParty` containing the generated headers and source files.

Your folder structure should look roughly like this:

```text
PigTail/
├── ThirdParty/
│   └── glad/
│       ├── include/
│       └── src/
├── Engine/
├── Assets/
├── Scripts/
├── CMakeLists.txt
└── README.MD
```

> Since `ThirdParty` is gitignored, these files will stay local to your machine.

### Why this matters

The project expects GLAD headers and loader code to exist in the local dependency folder so the project can compile correctly.

## 4. Build the project

From the root of the repository:

```bash
cmake -S . -B build
cmake --build build
```

This creates the engine library and the sample sandbox executable.

## 5. Use the engine in your own code

The engine is designed to be extended from the outside. In practice, you would:

1. create your own app or game class
2. initialize the engine
3. create scenes and entities
4. load assets or sounds
5. run the game loop

A basic pattern looks like this:

```cpp
#include "Core/Application.hpp"
#include "Math/Vec3.hpp"
#include "Math/Mat4.hpp"

int main()
{
    Pigtail::Application app;

    if (!app.initialize())
        return -1;

    // Create your own game objects here
    // Load assets, setup scene, configure rendering

    app.run();
    return 0;
}
```

This is the general model: set up the engine, build your gameplay logic, then run the application loop.

## 5. Start with the sandbox

The default sample app in `Engine/src/main.cpp` is the best place to learn how to use the engine in practice. It shows:

- engine startup
- sound loading
- matrix transforms
- simple vector math

Use that file as your template and replace the sample logic with your own game logic.

## 6. Add your own game systems

A good way to use this project is to create your own features around the existing engine base.

### Example: add a custom scene

Use the scene and entity system to define your game world:

- create a scene object
- add entities
- assign transforms
- update behavior each frame

### Example: add a custom render feature

If you want a new visual effect:

- extend the render pipeline in the graphics modules
- add a new shader or mesh
- hook it into the engine lifecycle

### Example: add gameplay logic

You can add custom player movement, enemies, cameras, and state systems by writing code in your own app and reusing the engine math and scene infrastructure.

## 7. Add assets and content

The engine already has folders for:

- Assets/Audio
- Assets/Shaders

Use these for your own custom content. For example:

- put sound files in Assets/Audio
- put shader files in Assets/Shaders
- load them from your own app code through the resource system

## 8. Good workflow for your own programming

A simple workflow is:

1. Build the project and run the sandbox.
2. Experiment with math, transforms, and rendering.
3. Copy the sample app pattern into your own project logic.
4. Add one system at a time: input, camera, enemy, particle effect, UI, etc.
5. Keep the engine core reusable and your game logic separate.

This keeps your project easier to maintain.

## 9. Where to edit

When using this as a starter engine, these are the most useful files to modify:

- `Engine/src/main.cpp`: your startup app and test game loop
- `Engine/src/Scene/*`: world and entity behavior
- `Engine/src/Graphics/*`: rendering and camera code
- `Engine/src/Audio/*`: sound and music logic
- `Engine/src/Math/*`: custom math behavior and utilities
- `Engine/src/Core/*`: engine lifecycle and runtime behavior

## 10. Best way to use this project

Treat this repository as a base, not as final code.

The most productive approach is:

- keep the engine core stable
- add your game-specific code on top
- prototype quickly
- refactor only when the system becomes useful

That is how this project is meant to be used for your own programming.

## 11. License

This project is licensed under the terms in the LICENSE file.

## 12. Final idea

If you want to make your own game or learning project, start by editing the sandbox and then slowly move your prototypes into your own classes and scene logic. This project is meant to help you build your own engine habits, not just read someone else’s engine.
