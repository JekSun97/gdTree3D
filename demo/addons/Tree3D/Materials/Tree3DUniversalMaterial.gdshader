shader_type spatial;
render_mode depth_prepass_alpha, cull_disabled, world_vertex_coords;

uniform sampler2D texture_albedo : source_color;
uniform sampler2D texture_normal : source_color;
uniform float normal_strength : hint_range(0.0, 2.0) = 1.0;

uniform float metallic : hint_range(0.0, 1.0) = 0.0;
uniform float roughness : hint_range(0.0, 1.0) = 0.9;

uniform vec4 tint_color : source_color = vec4(1.0, 1.0, 1.0, 1.0);
uniform float tint_strength : hint_range(0.0, 1.0) = 1.0;

uniform float sway_speed : hint_range(0.0, 20.0) = 8.5;
uniform float sway_strength : hint_range(0.0, 2.0) = 0.5;
uniform float sway_phase_len : hint_range(0.0, 10.0) = 2.0;
uniform vec3 wind_direction = vec3(1.0, 0.0, 0.5);

uniform float flutter_strength : hint_range(0.0, 0.5) = 0.08;

uniform bool debug_vertex_colors = false;

void vertex() {
    float influence = COLOR.r;
    
    vec3 wind_dir = normalize(wind_direction);
    float time = TIME * sway_speed;
    float height_factor = VERTEX.y * 0.1; 

    float base_sway = sin(time + height_factor * sway_phase_len) * sway_strength;
    float base_sway_y = sin(time * 1.3 + height_factor) * sway_strength * 0.05;

    vec3 branch_movement = vec3(
        wind_dir.x * base_sway,
        base_sway_y,
        wind_dir.z * base_sway
    ) * influence;

    float flutter_time = TIME * (sway_speed * 2.5); 
    float flutter = sin(VERTEX.x * 6.0 + VERTEX.y * 6.0 + flutter_time) * (flutter_strength * influence);

    VERTEX += branch_movement + vec3(wind_dir.x * flutter * 0.3, flutter, wind_dir.z * flutter * 0.3);

    NORMAL.x += sin(flutter_time + VERTEX.y * 4.0) * 0.05 * influence;
    NORMAL.z += cos(flutter_time + VERTEX.y * 4.0) * 0.05 * influence;
}

void fragment() {
    if (debug_vertex_colors) {
        float influence = COLOR.r;
        
        vec3 debug_color = mix(vec3(1.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0), influence);
        
        ALBEDO = debug_color;
        ALPHA = 1.0;
        
        NORMAL_MAP = vec3(0.0, 0.0, 1.0);
        NORMAL_MAP_DEPTH = 0.0;
        
        METALLIC = 0.0;
        ROUGHNESS = 1.0;
        
    } else {
        vec4 albedo_tex = texture(texture_albedo, UV);
        
        // === НОВОЕ: Применяем тонирование ===
        // Умножаем цвет текстуры на tint_color
        vec3 final_albedo = albedo_tex.rgb * tint_color.rgb;
        
        // tint_strength контролирует, насколько сильно применять tint
        // 0.0 = оригинальный цвет текстуры, 1.0 = полное тонирование
        final_albedo = mix(albedo_tex.rgb, final_albedo, tint_strength);
        
        ALBEDO = final_albedo;
        ALPHA = albedo_tex.a * tint_color.a; // Прозрачность тоже умножается

        NORMAL_MAP = texture(texture_normal, UV).rgb;
        NORMAL_MAP_DEPTH = normal_strength;

        METALLIC = metallic;
        ROUGHNESS = roughness;
    }
}