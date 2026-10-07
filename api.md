# API

New and newly bound methods are first. Unless noted, call them on `get_armature()`.

## Added methods

### DragonBonesArmature

`fade_in_masked(animation_name, time, loop, layer, group, fade_out_mode, bones)`

Plays a clip that affects only the named bones and their children. Sets `resetToPose` and a 0.05 second auto fade-out. Also on the view.

```gdscript
arm.fade_in_masked(
    "Swing", 0.0, 1, 1, "arms",
    DragonBonesArmature.FADE_OUT_NONE,
    PackedStringArray(["ArmLeftUpper", "ArmRightUpper"])
)
```

`fade_out(animation_name, time = 0.0)`

Fades one active clip out. This is what runs the pose reset. `stop()` does not.

```gdscript
arm.fade_out("Swing", 0.1)
```

`fade_out_group(group, time = 0.0)`

Fades out every playing animation that was started with that group. Other groups keep playing. The group is the string passed to `fade_in`, not a value from the DragonBones editor.

```gdscript
arm.fade_in_masked("Flinch", -1.0, 1, 1, "hit", DragonBonesArmature.FADE_OUT_NONE, PackedStringArray(["Hip"]))
arm.fade_out_group("hit", 0.1)



`set_animation_weight(animation_name, weight)`

Sets how much one playing animation mixes in, from `0.0` to `1.0`. `1.0` is the full animation. This mixes animations that move the same bones. It does not start or loop an animation. Use `fade_in_masked` when the animations should move different bones.
The call does nothing if that animation is not already playing. A second `fade_in` while it is still playing stacks another mix on top.

```gdscript
arm.fade_in_masked(
    "Flinch", -1.0, 1, 1, "hit",
    DragonBonesArmature.FADE_OUT_NONE,
    PackedStringArray(["Hip"])
)
arm.set_animation_weight("Flinch", 0.3)

`set_animation_time_scale(animation_name, scale)`

Sets the speed of one active clip. `1.0` is normal. Does not change other clips.

```gdscript
arm.set_animation_time_scale("Walk", 1.5)
arm.set_animation_time_scale("Swing", 2.0)
```

`get_animation_states()`

Returns an array of dictionaries: `name`, `layer`, `group`, `time_scale`, `progress`.

```gdscript
print(arm.get_animation_states())
```

`set_bone_rotation_override(name, rotation)`

Adds a rotation, in radians, after the animation. Does not change position.

```gdscript
arm.set_bone_rotation_override("ArmRightUpper", aim)
```

`clear_bone_override(name)`

Clears the additive offset and sets offset mode to none.

```gdscript
arm.clear_bone_override("ArmRightUpper")
```

`get_bone_global_pos(name)`

Returns the bone position after the armature advances. Same value as `get_bone(name).get_global_position()`.

```gdscript
sprite.global_position = arm.get_bone_global_pos("HandRight")


`get_bone_global_rotation(name)`

Returns the bone rotation in radians. Same value as get_bone(name).get_global_rotation().

```gdscript
print(arm.get_bone_global_rotation("ArmLeftUpper"))


`set_ik_enabled(name, enabled)`

Sets an IK constraint weight to `1.0` or `0.0`.

```gdscript
arm.set_ik_enabled("bone_ik2", false)
```

`set_ik_weight(name, weight)`

Sets an IK constraint weight from `0.0` to `1.0`.

```gdscript
arm.set_ik_weight("bone_ik2", 0.5)
```

`cache_ik_rest(name)`

Stores the IK target rest position on the first call.

```gdscript
arm.cache_ik_rest("bone_ik2")
```

`restore_ik_rest(name)`

Writes the cached IK target rest position back.

```gdscript
arm.restore_ik_rest("bone_ik2")
```

`get_current_animation_on_layer(layer)`

Returns the clip name on that layer. Already implemented; now bound. Also on the view.

```gdscript
print(arm.get_current_animation_on_layer(0))
```

`get_current_animation_in_group(group_name)`

Returns the clip name in that group. Already implemented; now bound. Also on the view.

```gdscript
print(arm.get_current_animation_in_group("body"))
```

`set_flip_x(flip_x, recursively = false)`

Flips the armature. The second argument also flips child armatures. Also on the view. The `flip_x` property still uses the one-argument setter.

```gdscript
view.set_flip_x(true, true)
```

### DragonBonesArmatureView

`signal animation_completed(animation_name)`

Emitted when a clip completes. The name comes from the animation state. Looping clips do not emit it at the end of every loop.

```gdscript
func _ready() -> void:
    $View.animation_completed.connect(_on_animation_completed)

func _on_animation_completed(animation_name: String) -> void:
    if animation_name == "Swing":
        attacking = false
```

`signal frame_event(animation_name, event_name)`

Emitted when playback reaches a frame event on a clip. `event_name` is the label set on the Event row in DragonBones.

```gdscript
func _on_frame_event(_clip: String, event_name: String) -> void:
    if event_name == "LeftFootTouched":
        print("left foot")

### DragonBonesSlot

`get_display_names()`

Returns the display names on that slot, in index order.

```gdscript
var slot := arm.get_slot("torso")
print(slot.get_display_names())
slot.set_display_by_name("torso2")
```

`get_slot_z()`

Returns the slot draw order. Higher values draw in front.

```gdscript
var slot := arm.get_slot("torso")
print(slot.get_slot_z())

`set_slot_z()`

Sets the slot draw order. The change shows on the next redraw. A slot with a z-order keyframe can be overwritten by the animation.

```gdscript
var slot := arm.get_slot("torso")
var saved := slot.get_slot_z()
slot.set_slot_z(saved + 100)
slot.set_slot_z(saved)

## DragonBonesArmatureView

The scene node. Most playback calls are forwarded to the armature.

Properties: `factory`, `active`, `debug`, `animation_loop_count`, `animation_time_scale`, `animation_callback_mode_process`, `instantiate_dragon_bones_data_name`, `instantiate_armature_name`, `instantiate_skin_name`, `current_animation`, `animation_progress`, `flip_x`, `flip_y`, `texture_override`.

```gdscript
view.animation_time_scale = 1.0
view.play("Walk", 0)
var arm := view.get_armature()
```

- `set_factory(factory)` / `get_factory()`
- `advance(delta)`
- `set_animation_loop_count(loop_count)` / `get_animation_loop_count()`
- `set_time_scale(speed_scale)` / `get_time_scale()` — the `animation_time_scale` property.
- `get_armature()`
- `set_active(active)` / `is_active()`
- `set_debug(debug)` / `is_debug()`
- `set_callback_mode_process(mode)` / `get_callback_mode_process()`
- `set_instantiate_dragon_bones_data_name(name)` / `get_instantiate_dragon_bones_data_name()`
- `set_instantiate_armature_name(name)` / `get_instantiate_armature_name()`
- `set_instantiate_skin_name(name)` / `get_instantiate_skin_name()`
- `get_rect()` / `get_global_rect()`

Callback modes: `ANIMATION_CALLBACK_MODE_PROCESS_PHYSICS`, `ANIMATION_CALLBACK_MODE_PROCESS_IDLE`, `ANIMATION_CALLBACK_MODE_PROCESS_MANUAL`.

Signal: `event_dispatched(event_object)`.
Signal: `frame_event(animation_name, event_name)`

## DragonBonesArmature

Do not create or free this object.

```gdscript
arm.fade_in("Walk", -1.0, 0, 0, "body", DragonBonesArmature.FADE_OUT_SAME_LAYER)
arm.play("Idle", -1)
print(arm.get_animations())
```

- `for_each_armature(action)`
- `for_each_armature_recursively(action, current_depth = 0)`
- `has_animation(animation_name)` / `get_animations()`
- `is_playing()`
- `tell_animation(animation_name)` — progress from `0.0` to `1.0`.
- `seek_animation(animation_name, progress)`
- `play(animation_name, loop_count = -1)`
- `play_from_time(animation_name, time, loop_count = -1)`
- `play_from_progress(animation_name, progress, loop_count = -1)`
- `stop(animation_name, reset = false, recursively = false)`
- `stop_all_animations(reset = false, recursively = false)`
- `fade_in(animation_name, time, loop, layer, group, fade_out_mode)`
- `reset(recursively = false)`
- `has_slot(slot_name)` / `get_slot(slot_name)` / `get_slots()`
- `get_ik_constraints()`
- `set_ik_constraint(constraint_name, new_position)`
- `set_ik_constraint_bend_positive(constraint_name, bend_positive)`
- `get_bones()` / `get_bone(bone_name)`
- `advance(delta, recursively = false)`
- `get_rect()`
- `set_current_animation(current_animation)` / `get_current_animation()`
- `set_animation_progress(progress)` / `get_animation_progress()`
- `set_flip_x_(flip_x)` / `is_flipped_x()`
- `set_flip_y_(flip_y)` / `is_flipped_y()`
- `set_texture_override(texture)` / `get_texture_override()`

Fade-out modes: `FADE_OUT_NONE`, `FADE_OUT_SAME_LAYER`, `FADE_OUT_SAME_GROUP`, `FADE_OUT_SAME_LAYER_AND_GROUP`, `FADE_OUT_ALL`, `FADE_OUT_SINGLE`.

Signal: `event_dispatched(event_object)`.

Loop count: `-1` uses the clip default, `0` loops forever, `1` or more plays that many times.

## DragonBonesSlot

```gdscript
var slot := arm.get_slot("torso")
slot.set_display_index(1)
slot.set_display_by_name("none")
```

- `get_slot_name()`
- `get_display_count()`
- `get_display_index()` / `set_display_index(index)`
- `set_display_by_name(name)` — `"none"` hides the slot.
- `next_display()` / `previous_display()`
- `get_display_color_multiplier()` / `set_display_color_multiplier(color)`
- `get_child_armature()`

## DragonBonesBone

```gdscript
var bone := arm.get_bone("ArmRightUpper")
bone.rotation = 0.5
print(bone.get_global_position())
```

- `get_name()` / `get_parent()` / `is_valid()`
- `get_position()` / `set_position(new_position)`
- `get_global_position()` / `set_global_position(new_position)`
- `get_rotation()` / `set_rotation(deg_in_rad)`
- `get_global_rotation()` / `set_global_rotation(deg_in_rad)`
- `get_scale()` / `set_scale(new_scale)`
- `get_global_scale()` / `set_global_scale(new_scale)`
- `get_transform()` / `set_transform(transform)`
- `get_global_transform()` / `set_global_transform(global_transform)`
- `get_offset_mode()` / `get_offset()` / `get_animation_pose()` / `get_origin()`

A direct bone write can be replaced on the next animation advance. Use `set_bone_rotation_override` when the rotation has to survive playback.

## DragonBonesFactory

```gdscript
print(factory.get_loaded_dragon_bones_data_name_list())
print(factory.get_loaded_dragon_bones_armature_name_list("Player"))
```

- `get_loaded_dragon_bones_data_name_list()`
- `get_loaded_dragon_bones_armature_name_list(data_name)`
- `get_loaded_dragon_bones_skin_name_list(data_name, armature_name)`
- `set_dragon_bones_ske_file_list(files)` / `get_dragon_bones_ske_file_list()`
- `set_texture_atlas_json_file_list(files)` / `get_texture_atlas_json_file_list()`

## DragonBonesEventObject

```gdscript
func _on_event(ev: DragonBonesEventObject) -> void:
    print(ev.get_type(), " ", ev.get_type_text())
    var data := ev.get_data()
    if data:
        print(data.get_strings())
```

- `get_time()` / `set_time(time)`
- `get_type()` / `set_type(type)`
- `get_type_text()` / `set_type_text(type_text)`
- `get_name()` / `set_name(name)`
- `get_armature()` / `set_armature(armature)`
- `get_bone()` / `set_bone(bone)`
- `get_slot()` / `set_slot(slot)`
- `get_data()` / `set_data(data)`

`name` is often empty on animation events. Use the `animation_completed` argument for the clip name.

Types: `TYPE_ANIM_START`, `TYPE_ANIM_LOOP_COMPLETE`, `TYPE_ANIM_COMPLETE`, `TYPE_ANIM_FADE_IN`, `TYPE_ANIM_FADE_IN_COMPLETE`, `TYPE_ANIM_FADE_OUT`, `TYPE_ANIM_FADE_OUT_COMPLETE`, `TYPE_FRAME_EVENT`, `TYPE_SOUND_EVENT`, `TYPE_CUSTOM`, `TYPE_MAX`.

## DragonBonesUserData

Reached through `event_object.get_data()`. These are the custom values stored on a frame event.

```gdscript
var data := ev.get_data()
if data:
    print(data.get_ints())
    print(data.get_floats())
    print(data.get_strings())
```

- `get_ints()`
- `get_floats()`
- `get_strings()`