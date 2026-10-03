# API

New and newly bound methods are first. Unless noted, call them on `get_armature()`.

## Added methods

### DragonBonesArmature

`fade_in_masked(animation_name, time, loop, layer, group, fade_out_mode, bones)`
Plays a clip that affects only the named bones and their children. Sets `resetToPose` and a 0.05 second auto fade-out. Also on the view.

`fade_out(animation_name, time = 0.0)`
Fades one active clip out. This is what runs the pose reset. `stop()` does not.

`set_animation_time_scale(animation_name, scale)`
Sets the speed of one active clip. `1.0` is normal. Does not change other clips.

`get_animation_states()`
Returns an array of dictionaries: `name`, `layer`, `group`, `time_scale`, `progress`.

`set_bone_rotation_override(name, rotation)`
Adds a rotation, in radians, after the animation. Does not change position.

`clear_bone_override(name)`
Clears the additive offset and sets offset mode to none.

`set_ik_enabled(name, enabled)`
Sets an IK constraint weight to `1.0` or `0.0`.

`set_ik_weight(name, weight)`
Sets an IK constraint weight from `0.0` to `1.0`.

`cache_ik_rest(name)`
Stores the IK target rest position on the first call.

`restore_ik_rest(name)`
Writes the cached IK target rest position back.

`get_current_animation_on_layer(layer)`
Returns the clip name on that layer. Already implemented; now bound. Also on the view.

`get_current_animation_in_group(group_name)`
Returns the clip name in that group. Already implemented; now bound. Also on the view.

`set_flip_x(flip_x, recursively = false)`
Flips the armature. The second argument also flips child armatures. Also on the view. The `flip_x` property still uses the one-argument setter.

### DragonBonesArmatureView

`signal animation_completed(animation_name)`
Emitted when a clip completes. The name comes from the animation state. Looping clips do not emit it at the end of every loop.

### DragonBonesSlot

`get_display_names()`
Returns the display names on that slot, in index order.

## DragonBonesArmatureView

The scene node. Most playback calls are forwarded to the armature.

Properties: `factory`, `active`, `debug`, `animation_loop_count`, `animation_time_scale`, `animation_callback_mode_process`, `instantiate_dragon_bones_data_name`, `instantiate_armature_name`, `instantiate_skin_name`, `current_animation`, `animation_progress`, `flip_x`, `flip_y`, `texture_override`.

`set_factory(factory)` / `get_factory()`
`advance(delta)`
`set_animation_loop_count(loop_count)` / `get_animation_loop_count()`
`set_time_scale(speed_scale)` / `get_time_scale()` — the `animation_time_scale` property.
`get_armature()`
`set_active(active)` / `is_active()`
`set_debug(debug)` / `is_debug()`
`set_callback_mode_process(mode)` / `get_callback_mode_process()`
`set_instantiate_dragon_bones_data_name(name)` / `get_instantiate_dragon_bones_data_name()`
`set_instantiate_armature_name(name)` / `get_instantiate_armature_name()`
`set_instantiate_skin_name(name)` / `get_instantiate_skin_name()`
`get_rect()` / `get_global_rect()`

Callback modes: `ANIMATION_CALLBACK_MODE_PROCESS_PHYSICS`, `ANIMATION_CALLBACK_MODE_PROCESS_IDLE`, `ANIMATION_CALLBACK_MODE_PROCESS_MANUAL`.

Signal: `event_dispatched(event_object)`.

## DragonBonesArmature

Do not create or free this object.

`for_each_armature(action)`
`for_each_armature_recursively(action, current_depth = 0)`
`has_animation(animation_name)` / `get_animations()`
`is_playing()`
`tell_animation(animation_name)` — progress from `0.0` to `1.0`.
`seek_animation(animation_name, progress)`
`play(animation_name, loop_count = -1)`
`play_from_time(animation_name, time, loop_count = -1)`
`play_from_progress(animation_name, progress, loop_count = -1)`
`stop(animation_name, reset = false, recursively = false)`
`stop_all_animations(reset = false, recursively = false)`
`fade_in(animation_name, time, loop, layer, group, fade_out_mode)`
`reset(recursively = false)`
`has_slot(slot_name)` / `get_slot(slot_name)` / `get_slots()`
`get_ik_constraints()`
`set_ik_constraint(constraint_name, new_position)`
`set_ik_constraint_bend_positive(constraint_name, bend_positive)`
`get_bones()` / `get_bone(bone_name)`
`advance(delta, recursively = false)`
`get_rect()`
`set_current_animation(current_animation)` / `get_current_animation()`
`set_animation_progress(progress)` / `get_animation_progress()`
`set_flip_x_(flip_x)` / `is_flipped_x()`
`set_flip_y_(flip_y)` / `is_flipped_y()`
`set_texture_override(texture)` / `get_texture_override()`

Fade-out modes: `FADE_OUT_NONE`, `FADE_OUT_SAME_LAYER`, `FADE_OUT_SAME_GROUP`, `FADE_OUT_SAME_LAYER_AND_GROUP`, `FADE_OUT_ALL`, `FADE_OUT_SINGLE`.

Signal: `event_dispatched(event_object)`.

Loop count: `-1` uses the clip default, `0` loops forever, `1` or more plays that many times.

## DragonBonesSlot

`get_slot_name()`
`get_display_count()`
`get_display_index()` / `set_display_index(index)`
`set_display_by_name(name)` — `"none"` hides the slot.
`next_display()` / `previous_display()`
`get_display_color_multiplier()` / `set_display_color_multiplier(color)`
`get_child_armature()`

## DragonBonesBone

`get_name()` / `get_parent()` / `is_valid()`
`get_position()` / `set_position(new_position)`
`get_global_position()` / `set_global_position(new_position)`
`get_rotation()` / `set_rotation(deg_in_rad)`
`get_global_rotation()` / `set_global_rotation(deg_in_rad)`
`get_scale()` / `set_scale(new_scale)`
`get_global_scale()` / `set_global_scale(new_scale)`
`get_transform()` / `set_transform(transform)`
`get_global_transform()` / `set_global_transform(global_transform)`
`get_offset_mode()` / `get_offset()` / `get_animation_pose()` / `get_origin()`

A direct bone write can be replaced on the next animation advance. Use `set_bone_rotation_override` when the rotation has to survive playback.

## DragonBonesFactory

`get_loaded_dragon_bones_data_name_list()`
`get_loaded_dragon_bones_armature_name_list(data_name)`
`get_loaded_dragon_bones_skin_name_list(data_name, armature_name)`
`set_dragon_bones_ske_file_list(files)` / `get_dragon_bones_ske_file_list()`
`set_texture_atlas_json_file_list(files)` / `get_texture_atlas_json_file_list()`

## DragonBonesEventObject

`time`, `type`, `type_text`, `name`, `armature`, `bone`, `slot`.

`name` is often empty on animation events. Use the `animation_completed` argument for the clip name.

Types: `TYPE_ANIM_START`, `TYPE_ANIM_LOOP_COMPLETE`, `TYPE_ANIM_COMPLETE`, `TYPE_ANIM_FADE_IN`, `TYPE_ANIM_FADE_IN_COMPLETE`, `TYPE_ANIM_FADE_OUT`, `TYPE_ANIM_FADE_OUT_COMPLETE`, `TYPE_FRAME_EVENT`, `TYPE_SOUND_EVENT`, `TYPE_CUSTOM`.