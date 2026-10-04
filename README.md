# Godot DragonBones Plus

A Godot 4 GDExtension for DragonBones, Improved fork by TheLoneInitiate

This fork adds layered animation blending, per-clip speed, bone overrides, IK weight control, and a completion signal. Those calls are documented in [API.md](api.md).

## Setup

1. Build with `scons target=template_debug` or `scons target=template_release`.
2. Copy `bin/libgddragonbones.*` into the addon `bin` folder.
3. Enable the plugin and reload the project.
4. Add a `DragonBonesArmatureView` node and assign a `DragonBonesFactory`.

Do not instantiate or free `DragonBonesArmature` yourself. Get it from the view:

```gdscript
var arm := $DragonBonesArmatureView.get_armature()