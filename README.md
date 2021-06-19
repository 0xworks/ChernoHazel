## Freeman40  branch ##
This is the "Freeman40" branch of my fork of TheCherno/Hazel.  It contains experimental code, some changes to make Hazel easier to use in other projects, small bug fixes and other random hacks.  Other Hazel projects of mine will generally use this branch.

Notable changes between this Freeman40 branch and the master branch (tracking origin TheCherno/Hazel:master) are:
- Premake5 is updated to alpha16 (needed for C++20 support)
- Uses C++20 (needed to take advantage of newest EnTT features)
- Spritesheets:
  - sub-textures stuff from yt episodes 67-70 (that Cherno is not planning to commit any time soon)
  - bug fix for texture bleeding at edges of sub-textures
  - sub-textures can be flipped in one or both axes by setting size to negative values
- EnTT
  - EnTT is added as a submodule, and updated to 0b3e3fd (which is latest as at today, 19June2021)
  - HACK: Scene EnTT registry is exposed to clients to faciliate iteration over view etc.  (temporary until Hazel provides mechanism for this)
- Updates to premake files:
  - make it easier to use Hazel as a submodule of an external project
  - turn off MSVC permissive mode (to catch C++ compliance issues that may cause problems for other compilers)
  - turn on MSVC synchronous PDB writes (allows for better build parallelism)
  - post build steps to copy debug VulkanSDK libs to executable bin folders
- Profiling is done with the "Tracy Profiler" rather than the Hazel instrumentor
- imgui.ini removed from version control
	

This branch should not be used to create PRs for upstream TheCherno/Hazel.

The "master" branch is intended to be kept in synch with upstream TheCherno/Hazel (and when convienient or necessary those changes can be merged into this Freeman40 branch.

For PRs to upstream TheCherno/Hazel, follow this workflow:
1) Get "master" in synch with upstream/master  (this will just be a fast-forward, since I do not do any other changes to master)
2) Branch from master
3) Checkout the branch and do the changes that you want to submit in the PR
4) Create PR from branch --> TheCherno/Hazel:master
5) (later, if/when the PR is accepted) do step 1 again (which should fast-forward to TheCherno/Hazel:master which now contains the changes from the PR, and then delete the PR branch (it's no longer needed)


# Hazel

![Hazel](/Resources/Branding/Hazel_Logo_Text_Light_Square.png?raw=true "Hazel")

Hazel is primarily an early-stage interactive application and rendering engine for Windows. Currently not much is implemented, however (almost) everything inside this repository is being created within YouTube videos, found at [thecherno.com/engine](https://thecherno.com/engine). 

## Getting Started
Visual Studio 2017 or 2019 is recommended, Hazel is officially untested on other development environments whilst we focus on a Windows build.

Start by cloning the repository with `git clone --recursive https://github.com/TheCherno/Hazel`.

If the repository was cloned non-recursively previously, use `git submodule update --init` to clone the necessary submodules.

## The Plan
The plan for Hazel is two-fold: to create a powerful 3D engine, but also to serve as an education tool for teaching game engine design and architecture. Because of this the development inside this repository is rather slow, since everything has to be taught and implemented on-camera. There is a much more advanced version of the engine in a private repository called `Hazel-dev`, accessible to supporters on [Patreon](https://patreon.com/thecherno). The plan for this project is to mostly take already implemented code from the `Hazel-dev` repository and integrate it into this one, done within videos and supported by explanations.

### Main features to come:
- Fast 2D rendering (UI, particles, sprites, etc.)
- High-fidelity Physically-Based 3D rendering (this will be expanded later, 2D to come first)
- Support for Mac, Linux, Android and iOS
    - Native rendering API support (DirectX, Vulkan, Metal)
- Fully featured viewer and editor applications
- Fully scripted interaction and behavior
- Integrated 3rd party 2D and 3D physics engine
- Procedural terrain and world generation
- Artificial Intelligence
- Audio system


## Short term goals :
*Note: this is subject to change at any time! Follow the roadmap over at [hazelengine.com/roadmap](http://hazelengine.com/roadmap).*

By the end 2021, we want to make a game using the Hazel game engine. Not like the time I made a game in one hour using the engine, but this time by using the proper tools that would be required to make a game with Hazel. This means we need to add a full 2D workflow:

- Design the game scene by using Hazelnut, the Hazel editor,
- Test the game inside Hazelnut, including the ability to save/load the created game,
- Load and play the game inside Sandbox.

We want everyone to be able to play the game on all desktop platforms (Windows, Mac and Linux). When this is implemented, another attempt at the "Creating a game in one hour using Hazel" will be made to see how far the engine has become.

[![Twitter](https://img.shields.io/badge/%40thecherno--blue.svg?style=social&logo=Twitter)](https://twitter.com/thecherno)
[![Instagram](https://img.shields.io/badge/thecherno--red.svg?style=social&logo=Instagram)](https://www.instagram.com/thecherno)
[![Youtube](https://img.shields.io/badge/TheChernoProject--red.svg?style=social&logo=youtube)](https://www.youtube.com/user/TheChernoProject)
[![Discord](https://img.shields.io/badge/TheCherno%20Server--blue.svg?style=social&logo=Discord)](https://discord.gg/K2eSyQA)
[![Patreon](https://img.shields.io/badge/%40thecherno--green.svg?style=social&logo=Patreon)](https://patreon.com/thecherno)
