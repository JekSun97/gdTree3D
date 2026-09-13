shader_type spatial;
render_mode depth_prepass_alpha, cull_disabled, world_vertex_coords;

uniform sampler2D texture_albedo : source_color;
uniform sampler2D texture_normal : source_color;
uniform float normal_strength : hint_range(0.0, 2.0) = 1.0;

uniform float metallic : hint_range(0.0, 1.0) = 0.0;
uniform float roughness : hint_range(0.0, 1.0) = 0.9;

uniform vec4 tint_color : source_color = vec4(1.0, 1.0, 1.0, 1.0);
uniform float tint_strength : hint_range(0.0, 1.0) = 1.0;

global uniform float tree_wind_speed : hint_range(0.0, 20.0) = 8.5;
global uniform float tree_wind_strength : hint_range(0.0, 2.0) = 0.5;
uniform float sway_phase_len : hint_range(0.0, 10.0) = 2.0;
global uniform vec3 tree_wind_direction = vec3(1.0, 0.0, 0.5);
uniform float flutter_strength : hint_range(0.0, 0.5) = 0.08;

global uniform float tree_gust_strength : hint_range(0.0, 3.0) = 1.0;
uniform float gust_speed : hint_range(0.1, 5.0) = 0.4;
uniform float gust_chaos : hint_range(0.0, 5.0) = 2.5;

global uniform bool tree_wind_use_spatial_wave = true;

uniform bool debug_vertex_colors = false;
void vertex() {
    float influence = COLOR.r;
    vec3 wind_dir = normalize(tree_wind_direction);
    float time = TIME * tree_wind_speed;
    float height_factor = VERTEX.y * 0.1; 

    float wave_factor = tree_wind_use_spatial_wave ? 1.0 : 0.0;

    float spatial_offset = ((VERTEX.x * wind_dir.x + VERTEX.z * wind_dir.z) * 0.15) * wave_factor;

    float base_sway = sin(time + height_factor * sway_phase_len + spatial_offset) * tree_wind_strength;

    float gust_envelope = sin((TIME * gust_speed) + spatial_offset) * 0.5 + 0.5;
    
    float gust_chaos_wave = sin(VERTEX.y * gust_chaos + TIME * gust_speed * 3.0) * 
                            cos(VERTEX.x * gust_chaos * 0.7 + TIME * gust_speed * 2.3);
    
    float total_sway = base_sway + (gust_envelope * gust_chaos_wave * tree_gust_strength);

    vec3 branch_movement = vec3(
        wind_dir.x * total_sway,
        sin(time * 1.3 + height_factor + spatial_offset) * total_sway * 0.1,
        wind_dir.z * total_sway
    ) * influence;

    float flutter_time = TIME * (tree_wind_speed * 2.5); 
    float flutter = sin(VERTEX.x * 6.0 + VERTEX.y * 6.0 + flutter_time) * (flutter_strength * influence);

    VERTEX += branch_movement + vec3(wind_dir.x * flutter * 0.3, flutter, wind_dir.z * flutter * 0.3);

    NORMAL.x += sin(flutter_time + VERTEX.y * 4.0 + gust_envelope * 2.0) * 0.08 * influence;
    NORMAL.z += cos(flutter_time + VERTEX.y * 4.0 + gust_envelope * 2.0) * 0.08 * influence;
}

void fragment() {
    if (debug_vertex_colors) {
        ALBEDO = mix(vec3(1.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0), COLOR.r);
        ALPHA = 1.0;
        NORMAL_MAP = vec3(0.0, 0.0, 1.0);
        NORMAL_MAP_DEPTH = 0.0;
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