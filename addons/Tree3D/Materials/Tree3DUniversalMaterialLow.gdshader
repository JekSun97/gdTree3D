shader_type spatial;
render_mode depth_prepass_alpha, cull_disabled, world_vertex_coords;

uniform sampler2D texture_albedo : source_color;
uniform sampler2D texture_normal : source_color;
uniform float normal_strength : hint_range(0.0, 2.0) = 1.0;

uniform float metallic : hint_range(0.0, 1.0) = 0.0;
uniform float roughness : hint_range(0.0, 1.0) = 0.9;

uniform vec4 tint_color : source_color = vec4(1.0, 1.0, 1.0, 1.0);
uniform float tint_strength : hint_range(0.0, 1.0) = 1.0; 
global uniform float tree_wind_speed : hint_range(0.0, 20.0) = 1.556;
global uniform float tree_wind_strength : hint_range(0.0, 2.0) = 0.194;
uniform float sway_wave_length : hint_range(0.1, 10.0) = 8.969;
global uniform vec3 tree_wind_direction = vec3(1.0, 0.0, 0.5);

uniform bool debug_vertex_colors = false;

void vertex() {
    float influence = COLOR.r;
    
    float active = step(0.01, influence); 
    
    float time = TIME * tree_wind_speed;
    
    float sway = sin(time + (VERTEX.y / sway_wave_length)) * tree_wind_strength * influence * active;
    
    VERTEX.x += tree_wind_direction.x * sway;
    VERTEX.z += tree_wind_direction.z * sway;
    VERTEX.y += sway * 0.5; 
}

void fragment() {
    if (debug_vertex_colors) {
        ALBEDO = mix(vec3(1.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0), COLOR.r);
        ALPHA = 1.0;
        NORMAL_MAP = vec3(0.0, 0.0, 1.0);
        METALLIC = 0.0;
        ROUGHNESS = 1.0;
    } else {
        vec4 albedo_tex = texture(texture_albedo, UV);
        vec3 final_albedo = mix(albedo_tex.rgb, albedo_tex.rgb * tint_color.rgb, tint_strength);
        
        ALBEDO = final_albedo;
        ALPHA = albedo_tex.a * tint_color.a;
        NORMAL_MAP = texture(texture_normal, UV).rgb;
        NORMAL_MAP_DEPTH = normal_strength;
        METALLIC = metallic;
        ROUGHNESS = roughness;
    }
}