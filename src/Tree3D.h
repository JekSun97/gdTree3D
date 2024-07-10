//Author: Artyom Bozhko (JekSun)
//Repo: https://github.com/JekSun97/gdTree3D

#ifndef TREE3D_H
#define TREE3D_H

#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/surface_tool.hpp>
#include <godot_cpp/classes/material.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/classes/orm_material3d.hpp>
#include <godot_cpp/classes/shader_material.hpp>
#include <proctree.h>

namespace godot {

class Tree3D : public Node3D {
	GDCLASS(Tree3D, Node3D)

private:
	Proctree::Tree tree;
	MeshInstance3D *trunk_inst = nullptr;
	MeshInstance3D *twig_inst = nullptr;
	
	void UpdateMeshTrunk();
	void UpdateMeshTwig();
	void UpdateAllMeshes();

protected:
	static void _bind_methods();

public:
	Tree3D();
	~Tree3D();

	void _process(double delta) override;

	void set_seed(int seed);
	int get_seed();
	
	void set_segments(int sg);
	int get_segments();
	
	void set_material_trunk(const Ref<Material> &mat);
	Ref<Material> get_material_trunk();
	void set_material_twig(const Ref<Material> &mat);
	Ref<Material> get_material_twig();
	
	void set_branches_count(int cnt);
	int get_branches_count();
	void set_trunk_height(int value);
	int get_trunk_height();
	void set_branch_length(float value);
	float get_branch_length();
	void set_branch_length_falloff(float value);
	float get_branch_length_falloff();
	void set_branch_clump_max(float value);
	float get_branch_clump_max();
	void set_branch_clump_min(float value);
	float get_branch_clump_min();
	void set_branch_factor(float value);
	float get_branch_factor();
	void set_drop_amount(float value);
	float get_drop_amount();
	void set_grow_amount(float value);
	float get_grow_amount();
	void set_sweep_amount(float value);
	float get_sweep_amount();
	void set_max_radius(float value);
	float get_max_radius();
	void set_radius_falloff_rate(float value);
	float get_radius_falloff_rate();
	void set_climb_rate(float value);
	float get_climb_rate();
	void set_trunk_kink(float value);
	float get_trunk_kink();
	void set_twist(float value);
	float get_twist();
	void set_trunk_length(float value);
	float get_trunk_length();
	void set_uv_multiplier(float value);
	float get_uv_multiplier();
	
	void set_twig_enable(bool value);
	bool get_twig_enable();
	void set_twig_scale(float value);
	float get_twig_scale();

};
}



#endif