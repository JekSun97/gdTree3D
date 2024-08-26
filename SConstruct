#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/"])
sources = Glob("src/*.cpp")

targetLibraryFileOutput = "demo/addons/tree3d/libtree3d{}{}".format(env["suffix"], env["SHLIBSUFFIX"])

# on MacOS we need use different filename parameters
if env["platform"] == "macos":
    targetLibraryFileOutput = "demo/addons/tree3d/libtree3d.{}.{}.{}".format(
        env["platform"], env["target"], env["arch"]
    )

library = env.SharedLibrary(
    targetLibraryFileOutput,
    source=sources,
)

Default(library)
