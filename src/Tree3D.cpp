#include "Tree3D.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Tree3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_seed"), &Tree3D::set_seed);
	ClassDB::bind_method(D_METHOD("get_seed"), &Tree3D::get_seed);
	
	ClassDB::bind_method(D_METHOD("set_branches_count", "count"), &Tree3D::set_branches_count);
	ClassDB::bind_method(D_METHOD("get_branches_count"), &Tree3D::get_branches_count);
	ClassDB::bind_method(D_METHOD("set_trunk_height", "height"), &Tree3D::set_trunk_height);
	ClassDB::bind_method(D_METHOD("get_trunk_height"), &Tree3D::get_trunk_height);
	ClassDB::bind_method(D_METHOD("set_branch_length", "length"), &Tree3D::set_branch_length);
	ClassDB::bind_method(D_METHOD("get_branch_length"), &Tree3D::get_branch_length);
	ClassDB::bind_method(D_METHOD("set_branch_length_falloff", "length"), &Tree3D::set_branch_length_falloff);
	ClassDB::bind_method(D_METHOD("get_branch_length_falloff"), &Tree3D::get_branch_length_falloff);
	ClassDB::bind_method(D_METHOD("set_branch_factor", "value"), &Tree3D::set_branch_factor);
	ClassDB::bind_method(D_METHOD("get_branch_factor"), &Tree3D::get_branch_factor);
	ClassDB::bind_method(D_METHOD("set_branch_clump_max", "max"), &Tree3D::set_branch_clump_max);
	ClassDB::bind_method(D_METHOD("get_branch_clump_max"), &Tree3D::get_branch_clump_max);
	ClassDB::bind_method(D_METHOD("set_branch_clump_min", "min"), &Tree3D::set_branch_clump_min);
	ClassDB::bind_method(D_METHOD("get_branch_clump_min"), &Tree3D::get_branch_clump_min);
	ClassDB::bind_method(D_METHOD("set_drop_amount", "amount"), &Tree3D::set_drop_amount);
	ClassDB::bind_method(D_METHOD("get_drop_amount"), &Tree3D::get_drop_amount);
	ClassDB::bind_method(D_METHOD("set_grow_amount", "amount"), &Tree3D::set_grow_amount);
	ClassDB::bind_method(D_METHOD("get_grow_amount"), &Tree3D::get_grow_amount);
	ClassDB::bind_method(D_METHOD("set_sweep_amount", "amount"), &Tree3D::set_sweep_amount);
	ClassDB::bind_method(D_METHOD("get_sweep_amount"), &Tree3D::get_sweep_amount);
	ClassDB::bind_method(D_METHOD("set_max_radius", "radius"), &Tree3D::set_max_radius);
	ClassDB::bind_method(D_METHOD("get_max_radius"), &Tree3D::get_max_radius);
	ClassDB::bind_method(D_METHOD("set_radius_falloff_rate", "radius"), &Tree3D::set_radius_falloff_rate);
	ClassDB::bind_method(D_METHOD("get_radius_falloff_rate"), &Tree3D::get_radius_falloff_rate);
	ClassDB::bind_method(D_METHOD("set_climb_rate", "rate"), &Tree3D::set_climb_rate);
	ClassDB::bind_method(D_METHOD("get_climb_rate"), &Tree3D::get_climb_rate);
	ClassDB::bind_method(D_METHOD("set_trunk_kink", "kink"), &Tree3D::set_trunk_kink);
	ClassDB::bind_method(D_METHOD("get_trunk_kink"), &Tree3D::get_trunk_kink);
	ClassDB::bind_method(D_METHOD("set_twist", "twist"), &Tree3D::set_twist);
	ClassDB::bind_method(D_METHOD("get_twist"), &Tree3D::get_twist);
	ClassDB::bind_method(D_METHOD("set_trunk_length", "length"), &Tree3D::set_trunk_length);
	ClassDB::bind_method(D_METHOD("get_trunk_length"), &Tree3D::get_trunk_length);
	
	ClassDB::bind_method(D_METHOD("set_twig_enable", "enable"), &Tree3D::set_twig_enable);
	ClassDB::bind_method(D_METHOD("get_twig_enable"), &Tree3D::get_twig_enable);
	ClassDB::bind_method(D_METHOD("set_twig_scale", "scale"), &Tree3D::set_twig_scale);
	ClassDB::bind_method(D_METHOD("get_twig_scale"), &Tree3D::get_twig_scale);
	
	ClassDB::bind_method(D_METHOD("set_material_trunk", "material"), &Tree3D::set_material_trunk);
	ClassDB::bind_method(D_METHOD("get_material_trunk"), &Tree3D::get_material_trunk);
	ClassDB::bind_method(D_METHOD("set_material_twig", "material"), &Tree3D::set_material_twig);
	ClassDB::bind_method(D_METHOD("get_material_twig"), &Tree3D::get_material_twig);
	
	
	ClassDB::add_property("Tree3D", PropertyInfo(Variant::INT, "seed", PROPERTY_HINT_RANGE, "0,100000,1"), "set_seed", "get_seed");
	
	ADD_GROUP("Trunk", "trunk_");
	ClassDB::add_property("Tree3D", PropertyInfo(Variant::INT, "trunk_branches_count", PROPERTY_HINT_RANGE, "1,13,1"), "set_branches_count", "get_branches_count");
	ClassDB::add_property("Tree3D", PropertyInfo(Variant::INT, "trunk_height", PROPERTY_HINT_RANGE, "0,100,1"), "set_trunk_height", "get_trunk_height");
	ClassDB::add_property("Tree3D", PropertyInfo(Variant::FLOAT, "trunk_branch_length", PROPERTY_HINT_RANGE, "0.1,10,0.01"), "set_branch_length", "get_branch_length");
	ClassDB::add_property("Tree3D", PropertyInfo(Variant::FLOAT, "trunk_branch_length_falloff", PROPERTY_HINT_RANGE, "0.15,1.7,0.01"), "set_branch_length_falloff", "get_branch_length_falloff");
	ClassDB::add_property("Tree3D", PropertyInfo(Variant::FLOAT, "trunk_branch_factor", PROPERTY_HINT_RANGE, "0.1,20,0.01"), "set_branch_factor", "get_branch_factor");
	ClassDB::add_property("Tree3D", PropertyInfo(Variant::FLOAT, "trunk_branch_clump_max", PROPERTY_HINT_RANGE, "0,20,0.01"), "set_branch_clump_max", "get_branch_clump_max");
	ClassDB::add_property("Tree3D", PropertyInfo(Variant::FLOAT, "trunk_branch_clump_min", PROPERTY_HINT_RANGE, "0,20,0.01"), "set_branch_clump_min", "get_branch_clump_min");
	ClassDB::add_property("Tree3D", PropertyInfo(Variant::FLOAT, "trunk_drop_amount", PROPERTY_HINT_RANGE, "-5,5,0.001"), "set_drop_amount", "get_drop_amount");
	ClassDB::add_property("Tree3D", PropertyInfo(Variant::FLOAT, "trunk_grow_amount", PROPERTY_HINT_RANGE, "-5,5,0.001"), "set_grow_amount", "get_grow_amount");
	ClassDB::add_property("Tree3D", PropertyInfo(Variant::FLOAT, "trunk_sweep_amount", PROPERTY_HINT_RANGE, "-5,5,0.01"), "set_sweep_amount", "get_sweep_amount");
	ClassDB::add_property("Tree3D", PropertyInfo(Variant::FLOAT, "trunk_max_radius", PROPERTY_HINT_RANGE, "0.01,0.6,0.01"), "set_max_radius", "get_max_radius");
	ClassDB::add_property("Tree3D", PropertyInfo(Variant::FLOAT, "trunk_radius_falloff_rate", PROPERTY_HINT_RANGE, "0.1,1,0.01"), "set_radius_falloff_rate", "get_radius_falloff_rate");
	ClassDB::add_property("Tree3D", PropertyInfo(Variant::FLOAT, "trunk_climb_rate", PROPERTY_HINT_RANGE, "0,50,0.01"), "set_climb_rate", "get_climb_rate");
	ClassDB::add_property("Tree3D", PropertyInfo(Variant::FLOAT, "trunk_kink", PROPERTY_HINT_RANGE, "-1,1,0.01"), "set_trunk_kink", "get_trunk_kink");
	ClassDB::add_property("Tree3D", PropertyInfo(Variant::FLOAT, "trunk_twist", PROPERTY_HINT_RANGE, "-5,5,0.01"), "set_twist", "get_twist");
	ClassDB::add_property("Tree3D", PropertyInfo(Variant::FLOAT, "trunk_length", PROPERTY_HINT_RANGE, "0,20,0.01"), "set_trunk_length", "get_trunk_length");
	
	ADD_GROUP("Twig", "twig_");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "twig_enable"), "set_twig_enable", "get_twig_enable");
	ClassDB::add_property("Tree3D", PropertyInfo(Variant::FLOAT, "twig_scale", PROPERTY_HINT_RANGE, "0,2,0.05"), "set_twig_scale", "get_twig_scale");
	
	ADD_GROUP("Materials", "material_");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "material_trunk", PROPERTY_HINT_RESOURCE_TYPE, "StandardMaterial3D,ORMMaterial3D,ShaderMaterial"), "set_material_trunk", "get_material_trunk");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "material_twig", PROPERTY_HINT_RESOURCE_TYPE, "StandardMaterial3D,ORMMaterial3D,ShaderMaterial"), "set_material_twig", "get_material_twig");
}

Tree3D::Tree3D() {
	
	trunk_inst = memnew(MeshInstance3D);
	twig_inst = memnew(MeshInstance3D);	
	this->add_child(trunk_inst);
	this->add_child(twig_inst);
	UpdateAllMeshes();
	//godot::UtilityFunctions::print("Tree3D Init");
	
}

Tree3D::~Tree3D() {
	
	// Add your cleanup here.
}

void Tree3D::_process(double delta) {
}


void Tree3D::set_seed(int seed) {
tree.mProperties.mSeed = seed;
UpdateAllMeshes();
}	

int Tree3D::get_seed() {
	return tree.mProperties.mSeed;
}

void Tree3D::set_branches_count(int cnt) {
tree.mProperties.mLevels = cnt;
UpdateAllMeshes();
}	

int Tree3D::get_branches_count() {
	return tree.mProperties.mLevels;
}

void Tree3D::set_trunk_height(int value) {
tree.mProperties.mTreeSteps = value;
UpdateAllMeshes();
}	

int Tree3D::get_trunk_height() {
	return tree.mProperties.mTreeSteps;
}

void Tree3D::set_twig_scale(float value) {
tree.mProperties.mTwigScale = value;
tree.generate();
UpdateMeshTwig();
}	

float Tree3D::get_twig_scale() {
	return tree.mProperties.mTwigScale;
}


void Tree3D::set_twig_enable(bool value) {
twig_inst->set_visible(value);
}	

bool Tree3D::get_twig_enable() {
	return twig_inst->is_visible();
}


void Tree3D::set_branch_length(float value) {
tree.mProperties.mInitialBranchLength = value;
UpdateAllMeshes();
}	

float Tree3D::get_branch_length() {
	return tree.mProperties.mInitialBranchLength;
}


void Tree3D::set_branch_length_falloff(float value) {
tree.mProperties.mLengthFalloffFactor = value;
UpdateAllMeshes();
}	

float Tree3D::get_branch_length_falloff() {
	return tree.mProperties.mLengthFalloffFactor;
}


void Tree3D::set_branch_clump_max(float value) {
tree.mProperties.mClumpMax = value;
UpdateAllMeshes();
}	

float Tree3D::get_branch_clump_max() {
	return tree.mProperties.mClumpMax;
}


void Tree3D::set_branch_clump_min(float value) {
tree.mProperties.mClumpMin = value;
UpdateAllMeshes();
}	

float Tree3D::get_branch_clump_min() {
	return tree.mProperties.mClumpMin;
}


void Tree3D::set_branch_factor(float value) {
tree.mProperties.mBranchFactor = value;
UpdateAllMeshes();
}	

float Tree3D::get_branch_factor() {
	return tree.mProperties.mBranchFactor;
}


void Tree3D::set_drop_amount(float value) {
tree.mProperties.mDropAmount = value;
UpdateAllMeshes();
}	

float Tree3D::get_drop_amount() {
	return tree.mProperties.mDropAmount;
}


void Tree3D::set_grow_amount(float value) {
tree.mProperties.mGrowAmount = value;
UpdateAllMeshes();
}	

float Tree3D::get_grow_amount() {
	return tree.mProperties.mGrowAmount;
}


void Tree3D::set_sweep_amount(float value) {
tree.mProperties.mSweepAmount = value;
UpdateAllMeshes();
}	

float Tree3D::get_sweep_amount() {
	return tree.mProperties.mSweepAmount;
}


void Tree3D::set_max_radius(float value) {
tree.mProperties.mMaxRadius = value;
tree.generate();
UpdateMeshTrunk();
}	

float Tree3D::get_max_radius() {
	return tree.mProperties.mMaxRadius;
}


void Tree3D::set_radius_falloff_rate(float value) {
tree.mProperties.mRadiusFalloffRate = value;
tree.generate();
UpdateMeshTrunk();
}	

float Tree3D::get_radius_falloff_rate() {
	return tree.mProperties.mRadiusFalloffRate;
}


void Tree3D::set_climb_rate(float value) {
tree.mProperties.mClimbRate = value;
UpdateAllMeshes();
}	

float Tree3D::get_climb_rate() {
	return tree.mProperties.mClimbRate;
}


void Tree3D::set_trunk_kink(float value) {
tree.mProperties.mTrunkKink = value;
UpdateAllMeshes();
}	

float Tree3D::get_trunk_kink() {
	return tree.mProperties.mTrunkKink;
}


void Tree3D::set_twist(float value) {
tree.mProperties.mTwistRate = value;
UpdateAllMeshes();
}	

float Tree3D::get_twist() {
	return tree.mProperties.mTwistRate;
}


void Tree3D::set_trunk_length(float value) {
tree.mProperties.mTrunkLength = value;
UpdateAllMeshes();
}	

float Tree3D::get_trunk_length() {
	return tree.mProperties.mTrunkLength;
}



void Tree3D::set_material_trunk(const Ref<Material> &mat) {
trunk_inst->set_surface_override_material(0,mat);
}	

Ref<Material> Tree3D::get_material_trunk() {
	return trunk_inst->get_surface_override_material(0);
}

void Tree3D::set_material_twig(const Ref<Material> &mat) {
twig_inst->set_surface_override_material(0,mat);
}	

Ref<Material> Tree3D::get_material_twig() {
	return twig_inst->get_surface_override_material(0);
}




void Tree3D::UpdateMeshTrunk()
{
	Ref<SurfaceTool> st;
	st.instantiate();
	
	st->begin(Mesh::PRIMITIVE_TRIANGLES);
    for (int i = 0; i < tree.mVertCount; i++)
	{
		st->set_uv(Vector2(tree.mUV[i].u, tree.mUV[i].v));
		st->set_normal(-Vector3(tree.mNormal[i].x, tree.mNormal[i].y, tree.mNormal[i].z));
		st->add_vertex(Vector3(tree.mVert[i].x, tree.mVert[i].y, tree.mVert[i].z));
	}
	
	for (int i = 0; i < tree.mFaceCount; i++)
	{
		st->add_index(tree.mFace[i].x);
		st->add_index(tree.mFace[i].y);
		st->add_index(tree.mFace[i].z);
	}
	st->optimize_indices_for_cache();
	trunk_inst->set_mesh(st->commit());
	
}


void Tree3D::UpdateMeshTwig()
{
	Ref<SurfaceTool> st;
	st.instantiate();
	
	st->begin(Mesh::PRIMITIVE_TRIANGLES);
    for (int i = 0; i < tree.mTwigVertCount; i++)
	{
		st->set_uv(Vector2(tree.mTwigUV[i].u, tree.mTwigUV[i].v));
		st->set_normal(-Vector3(tree.mTwigNormal[i].x, tree.mTwigNormal[i].y, tree.mTwigNormal[i].z));
		st->add_vertex(Vector3(tree.mTwigVert[i].x, tree.mTwigVert[i].y, tree.mTwigVert[i].z));
	}
	
	for (int i = 0; i < tree.mTwigFaceCount; i++)
	{
		st->add_index(tree.mTwigFace[i].x);
		st->add_index(tree.mTwigFace[i].y);
		st->add_index(tree.mTwigFace[i].z);
	}
	st->optimize_indices_for_cache();
	twig_inst->set_mesh(st->commit());
	
}

void Tree3D::UpdateAllMeshes() {
	tree.generate();
	UpdateMeshTrunk();
	UpdateMeshTwig();
}

