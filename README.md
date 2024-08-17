# GDExtension Module Player

This repository provides an example of real-time Godot 4.3 sound generation by integrating the [libxmp-lite](https://github.com/libxmp/libxmp/tree/master/lite) module-decoding library in a custom `AudioStream` with the GDExtension system.

It is mostly a proof of concept, but I'm open to PRs if this proves useful to someone. Note that a pure GDScript module player exists ([Godot Mod Player](https://godotengine.org/asset-library/asset/841)).

Code is based on [gdextension-custom-audiostream](https://github.com/oparisy/gdextension-custom-audiostream). Have a look at that project for more details about GDExtension, debugger usage...

## Credits & Distribution

This repository includes [libxmp](https://github.com/libxmp/libxmp) as a submodule, 
in conformance with [its MIT license](https://github.com/libxmp/libxmp/blob/master/README).
Scons will include it to the GDExtension library during build.

Public Domain module files are included with this module for testing purpose; see `game/CREDITS` for details.

## Using the Extension
After cloning and building the extension (see below), open `game/project.godot` in Godot Project Manager, and run it. You'll hear a module being played.

If you test this in the editor, by setting the `Playing` property to `true` there, you may get audio glitches. This is due to the fact that editor windows are running with default priority.
This will not happen with a script/game, since those are run with a higher priority ([as can be seen here](https://github.com/godotengine/godot/blob/9b522ac1a85cab1a7a867b7a9f3bb102d9376ac2/platform/windows/display_server_windows.cpp#L4800-L4815)).

## Cloning the Extension
Since this project includes `godot-cpp` and `libxmp` as submodules, you'll have to clone it with `git clone --recurse-submodules`.

## Building the Extension

### Manual Compilation

To compile the extension you need to follow these steps:

1. Make sure you cloned the extension recursively as described above

2. Go to the top level of the project
```sh
cd gdextension-module
```

3. Compile the extension
```sh
scons # this will use the default values such as target=template_debug
```

### VSCode Compilation
For the initial build you can run the vscode task `initial-build-extension`. This compiles both `godot-cpp` and the extension. For all subsequent builds, you only need to run the task `build-extension`.

## Previous Versions
Check out the [`godot-4.2.1-stable`](https://github.com/oparisy/gdextension-module/releases/tag/godot-4.2.1-stable) tag for a Godot 4.2 compatible version.
