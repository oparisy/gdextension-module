#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")

# For the reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["extension/src/", "extension/libxmp-lite/include/"])
sources = Glob("extension/src/*.cpp")

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "game/bin/libgdaudiostreammodule.{}.{}.framework/libgdaudiostreammodule.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "game/bin/libgdaudiostreammodule{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

# Adapted from https://github.com/allan-simon/gdextension-vosk-speech-to-text#interesting-part
env.Append(LIBPATH=["extension/libxmp-lite/bin/"])
env.Append(LIBS=["libxmp-lite"])

Default(library)
