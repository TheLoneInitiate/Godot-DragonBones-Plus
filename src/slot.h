#pragma once

#include <godot_dragon_bones.h>

#include <dragonBones/armature/Slot.h>
#include <godot_cpp/classes/canvas_item_material.hpp>
#include <godot_cpp/classes/texture2d.hpp>

#include "mesh_display.h"

namespace godot {

class Slot_GD : public dragonBones::Slot {
	BIND_CLASS_TYPE_A(Slot_GD);

private:
	Ref<class DragonBonesSlot> wrapper;
	float _textureScale;

	friend class DragonBonesFactory;

public:
	CanvasItemMaterial::BlendMode blend_mode{ CanvasItemMaterial::BLEND_MODE_MIX };
	Color color;
	Ref<Texture2D> texture_override;

	Ref<Texture2D> get_texture() const;
	Display *get_display() const { return static_cast<Display *>(getDisplay()); }
	
	bool region_override_enabled = false;
	dragonBones::Rectangle region_from;
	dragonBones::Rectangle region_override;
	float region_atlas_width = 0.0f;
	float region_atlas_height = 0.0f;

	void set_region_override(const dragonBones::Rectangle &p_to);

public:
	virtual void _updateVisible() override;
	virtual void _updateBlendMode() override;
	virtual void _updateColor() override;

protected:
	virtual void _initDisplay(void *value, bool isRetain) override;
	virtual void _disposeDisplay(void *value, bool isRelease) override;
	virtual void _onUpdateDisplay() override;
	virtual void _addDisplay() override;
	virtual void _replaceDisplay(void *value, bool isArmatureDisplay) override;
	virtual void _removeDisplay() override; // 不被调用的纯虚函数
	virtual void _updateZOrder() override;

	virtual void _updateFrame() override;
	virtual void _updateMesh() override;
	virtual void _updateTransform() override;
	virtual void _identityTransform() override;

	virtual void _onClear() override;

	void __get_uv_pt(Point2 &_pt, bool _is_rot, float _u, float _v, const dragonBones::Rectangle &_reg, const dragonBones::TextureAtlasData *_p_atlas);
};

class DragonBonesSlot : public RefCounted {
	GDCLASS(DragonBonesSlot, RefCounted);

private:
	Slot_GD *slot{ nullptr }; // 生命周期由 dragonBones::Armature 管理

	friend class Slot_GD;
	friend class DragonBonesFactory;
	friend class DragonBonesArmature;

public:
	DragonBonesSlot() = default;
	DragonBonesSlot(Slot_GD *p_slot) :
			slot(p_slot) {}

public:
	/* BIND METHODS */
	static void _bind_methods();
	_DEFINE_TO_STRING()

	Color get_display_color_multiplier();
	void set_display_color_multiplier(const Color &p_color);
	void set_display_index(int index = 0);
	void set_display_by_name(const String &_name);
	int get_display_index();
	int get_display_count();
	PackedStringArray get_display_names() const;
	void next_display();
	void previous_display();
	String get_slot_name();
	int get_slot_z() const;
	void set_slot_z(int p_z);
	Rect2 get_slot_rect() const;
	PackedVector2Array get_slot_polygon() const;
	PackedInt32Array get_slot_indices() const;
	void set_texture_override(const Ref<Texture2D> &p_texture);
	Ref<Texture2D> get_texture_override() const;
	void set_display_region(const String &p_name);
	void clear_display_region();

	class DragonBonesArmature *get_child_armature();
	
};

} //namespace godot
