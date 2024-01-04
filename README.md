# GDExtension Module Player

This repository provides an example of real-time Godot 4.2 sound generation by integrating the [libxmp-lite](https://github.com/libxmp/libxmp/tree/master/lite) module-decoding library in a custom `AudioStream` with the GDExtension system.

It is based on [gdextension-custom-audiostream](https://github.com/oparisy/gdextension-custom-audiostream). Have a look at that project for more details about GDExtension, debugger usage...

This is mostly a proof of concept, but I'm open to PRs if this proves useful to someone. Note that a pure GDScript module player exists ([Godot Mod Player](https://godotengine.org/asset-library/asset/841)).

## Credits & Distribution
For simplicity this repository distributes a compiled version of [libxmp-lite](https://github.com/libxmp/libxmp/tree/master/lite) for Windows, in conformance with [its MIT license](https://github.com/libxmp/libxmp/blob/master/README). I'm open to PRs automating its compilation from Scons.

Module files are included with this module for testing purpose; see `game/CREDITS` for details.

## Cloning the Extension
Since this project includes `godot-cpp` as a submodule, you'll have to clone it with `git clone --recurse-submodules`.

## Using the Extension
After building the extension successfully (see below), open `game/project.godot` in Godot Project Manager, and run it. You'll hear a module being played.

## Building the Extension

### VSCode Compilation (only applicable if you are using VSCode as your code editor)
For the initial build you can run the vscode task `initial-build-extension`. This compiles both `godot-cpp` and the extension. For all subsequent builds, you only need to run the task `build-extension`.

### Manual Compilation

To compile the extension you need to follow these steps:

1. Make sure you cloned the extension recursively as described above

2. Go to the top level of the project
```bash
cd gdextension-custom-audiostream
```

3. Compile the extension
```bash
scons # this will use the default values such as target=template_debug
```
