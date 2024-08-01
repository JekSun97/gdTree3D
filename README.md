<img src="image/tree3d.png">

# gdTree3D
Plugin for procedural generation of 3D trees of varying complexity.

## Supported Godot Engine Versions
- Godot 4.1
- Godot 4.2
- Godot 4.3

## Note
- To ensure the tree displays correctly, use Cull Mode: Front for the tree trunk material.
- To change the season, you can make one unique leaf material for all the trees and then change its color or texture to make them yellow.

## Building GDExtension

1. Place [godot-cpp](https://github.com/godotengine/godot-cpp) of the version you need in the godot-cpp folder
2. Use the SCons command:
```
scons platform=windows target= ...
```
Or use [ready-made libraries](https://github.com/JekSun97/gdTree3D/releases)

<img src="image/preview.png">