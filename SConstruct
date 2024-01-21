#!/usr/bin/env python
import os
import sys

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# Explicitly name godot-cpp environment to avoid tampering with it below
godot_cpp_env = SConscript("godot-cpp/SConstruct")

# Extracted from libxmp/lite/src/Makefile
LIBXMP_LITE_SRC = [ "virtual.c", "format.c", "period.c", "player.c", "read_event.c",  "misc.c",
                   "dataio.c", "lfo.c", "scan.c", "control.c", "filter.c",  "effects.c",
                   "mixer.c", "mix_all.c", "load_helpers.c", "load.c", "filetype.c", "hio.c",
                   "smix.c", "memio.c", "win32.c", "md5.c" ]

# Extracted from libxmp/lite/src/loaders/Makefile
LIBXMP_LITE_LOADER_SRC = [ "xm_load.c", "mod_load.c", "s3m_load.c", "it_load.c",
                          "common.c", "itsex.c", "sample.c" ]

libxmp_source = []
libxmp_source.append(["libxmp/src/{}".format(f) for f in LIBXMP_LITE_SRC])
libxmp_source.append(["libxmp/src/loaders/{}".format(f) for f in LIBXMP_LITE_LOADER_SRC])

# Use a dedicated environment for libxmp-lite build
# Not cloned from godot-cpp Environment since libxmp does not depend on it
libxmp_env = Environment(CPPPATH=["libxmp/include/"])
libxmp_env.Append(CCFLAGS=["-DLIBXMP_CORE_PLAYER", "-DLIBXMP_STATIC"])
libxmp_obj = [libxmp_env.SharedObject(f) for f in libxmp_source] # Make sure -fPIC is added under Linux
libxmp_lib = libxmp_env.StaticLibrary('libxmp-lite', libxmp_obj)

# GDExtension environment is cloned to avoid altering godot-cpp CPPPATH
env = godot_cpp_env.Clone()
env.Append(CPPPATH=["extension/src/", "libxmp/include/"])
env.Append(CCFLAGS=["-DLIBXMP_STATIC"]) # Avoids a LNK2019 under Windows
env.Append(LIBS=libxmp_lib)
sources = Glob("extension/src/*.cpp")

# Boilerplate
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

Default(library)
