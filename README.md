## Freeman40  branch ##
This is the "Freeman40" branch of my fork of TheCherno/Hazel.  It contains experimental code, some changes to make Hazel easier to use in other projects, small bug fixes and other random hacks.  Other Hazel projects of mine will generally use this branch.

Notable features in the Freeman40 branch:
- Spritesheets
  - sub textures stuff from yt episodes 67-70 (that Cherno is not planning to commit any time soon)
  - bug fix for texture bleeding at edges
  - sub textures can be flipped in one or both axes by setting size to negative values
- ~~Experimental ECS (not the one that Cherno is planning to use)~~
- "modular" premake (to make it easier to use Hazel as a submodule of external project)
- Profiling is done with the "Tracy Profiler" rather than the Hazel instrumentor
	

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

You can clone the repository to a local destination using git:

`git clone --recursive https://github.com/TheCherno/Hazel`

Make sure that you do a `--recursive` clone to fetch all of the submodules!

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
