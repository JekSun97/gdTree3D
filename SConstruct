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

# the filename "libTree3D" results from the prefix "lib*", which (somehow) gets defined from "godot-cpp"
targetLibraryFileOutput = "demo/addons/Tree3D/libTree3D{}{}".format(env["suffix"], env["SHLIBSUFFIX"])

# on MacOS we need use different filename parameters
if env["platform"] == "macos":
    targetLibraryFileOutput = "demo/addons/Tree3D/libTree3D.{}.{}.{}".format(
        env["platform"], env["target"], env["arch"]
    )

# copy addons template to demo project
# makes it usable even without Github Actions runner
# use "Install" instead of "Copy"
# https://stackoverflow.com/a/35442344/1961102
copy_static_files_to_demo_folder = env.Install("demo/", "addons")

version_replacement_dict = {}

# Godot 4.0 has a different type/interface for register_types
#
# there probably are better ways, but checking the existence of a certain file,
# which was not present "in the past", was the best clue I got.
if not os.path.isfile("godot-cpp/pyproject.toml"):
    env.Append(CPPDEFINES=['GODOT_40'])
    # the .gdextension file CAN NOT have "4.0" in it, because Godot 4.1+ would reject it
    # so change it only for Godot 4.0.x to be "4.0" instead of "4.1"
    version_replacement_dict = {'compatibility_minimum = "4.1"': 'compatibility_minimum = "4.0"'}

# always generate .gdextension file (as we need to replace stuff there)
generate_gdextension_file = env.Substfile(source = 'addons/Tree3D/Tree3D.gdextension', target = 'demo/addons/Tree3D/Tree3D.gdextension', SUBST_DICT = version_replacement_dict)

library = env.SharedLibrary(
    targetLibraryFileOutput,
    source=sources,
)

# will be executed in reverse order
Default(library, generate_gdextension_file, copy_static_files_to_demo_folder)
