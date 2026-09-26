# Using Pigtail for your own programming

This file is not meant to describe the engine as an academic project. It is meant to show you how to use this code as a base for your own C++ work.

If you want to build your own game, prototype, or custom engine experiment, this project gives you a starting template.

## 1. Start from the sandbox

The fastest way to use this project is to begin with the example program in `Engine/src/main.cpp`.

That file is effectively your playground. It already shows:

- engine startup
- sound loading
- math operations
- app loop execution

You can replace that sample behavior with your own game logic.

## 2. Basic app structure

Your program should follow this pattern:

```cpp
#include "Core/Application.hpp"
#include "Math/Vec3.hpp"
#include "Math/Mat4.hpp"

int main()
{
    Pigtail::Application app;

    if (!app.initialize())
        return -1;

    // setup your game world
    // load resources
    // create scene objects
    // configure camera and transforms

    app.run();
    return 0;
}
```

This is the foundation for your own program.

## 3. Add your own gameplay

Instead of trying to understand every class at once, build in layers:

### Step 1: make a simple scene

Use the scene and entity structure to represent game objects.

### Step 2: add a player object

Create your own game logic for:

- movement
- health
- animation state
- input handling

### Step 3: use the math library

The math utilities are already provided for vectors and transforms. This is useful for:

- player position
- camera movement
- object rotation
- world-to-screen calculation

Example:

```cpp
using namespace Pigtail;

Vec3 position(10.0f, 5.0f, -2.0f);
Mat4 transform = Mat4::translation(position);
```

This is a simple way to begin working with the engine as a real game runtime.

## 4. Extend the engine, do not fight it

When building your own programs, do not rewrite the whole engine. Instead, add around it.

Useful places to extend:

- `Engine/src/Core/*`: app loop and runtime behavior
- `Engine/src/Graphics/*`: rendering, shaders, cameras, and draw calls
- `Engine/src/Scene/*`: worlds, actors, and transforms
- `Engine/src/Audio/*`: music and sound behavior
- `Engine/src/Math/*`: custom transformation and math helpers

This keeps your code organized and reusable.

## 5. Add assets to your project

The project already includes folders for content:

- `Assets/Audio`
- `Assets/Shaders`

Use them for your own prototype content. You can keep game assets in these directories and load them from code as your project grows.

## 6. Use the engine as a template

This repository is best used as a starter template. A good workflow is:

1. build the project
2. run the sandbox
3. modify `main.cpp` to test your own behavior
4. add a custom scene or game object
5. add one feature at a time
6. keep your own project logic separate from engine internals

That is the practical way to use it.

## 7. Good habits when creating your own program

- keep the engine core stable
- keep gameplay code separate from rendering code
- build small test systems before large features
- use the math utilities instead of writing ad hoc calculations
- use the sample app as a scratchpad before creating your final project structure

## 8. Typical custom project flow

A real project might look like this:

- create player logic
- create enemy logic
- build a scene for each level
- attach camera and render logic
- load sounds and effects
- run the application loop

This means your project grows from the engine foundation instead of being built from nothing.

## 9. Quick starter plan

If you want to create your own program from this repository:

1. open `Engine/src/main.cpp`
2. replace the sample code with your own startup logic
3. create a player object or scene system
4. load a few assets
5. run and test the app
6. iterate on gameplay features

That is the actual use case for this project.

## 10. Final reminder

Do not treat this repository as a finished commercial engine. Treat it as a programmable base for your own experiments. The point is to help you learn and build quickly, not to lock you into a rigid architecture.

If you want a truly custom game, start by changing this sandbox and growing it into your own app.
