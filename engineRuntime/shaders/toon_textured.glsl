// JE_TRANSLATE
#version 420

layout(location = 0) in vec3 vpos;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 vnorm;

layout(location = 0) out vec4 c_final;

layout(set = 0, binding = 0) uniform UBO { // JE_TRANSLATE
                                           mat4 viewMatrix;
                                           mat4 _2dProj;
                                           mat4 _3dProj;
                                           vec3 cameraPos;
                                           vec3 cameraDir;
                                           vec2 screenSize;
};

layout(set = 1, binding = 0) uniform LBO {
    vec3 sunDir;
    vec3 sunColor;
    vec3 ambience;
    vec3 clearColor;
    vec2 fogPlanes;
};

layout(set = 2, binding = 0) uniform sampler2D albedo;
layout(set = 3, binding = 0) uniform sampler2D specmissive;

void main() {
    vec3 normalDirection = normalize(vnorm);
    vec3 lightDirection = normalize(sunDir);

    vec3 albedo_color = texture(albedo, uv).rgb;
    vec2 specular_emiss = texture(specmissive, uv).rg;
    vec3 spec_highlight = (albedo_color + specular_emiss.r) * vec3(clamp((dot(normalDirection, normalize(lightDirection + cameraDir)))*specular_emiss.r, 0, 1));
    vec3 lit_color = albedo_color * max(0.2, dot(normalDirection, lightDirection)) * sunColor + ambience + spec_highlight;

    // Fog t value for interpolation
    float fog_t = max(min(((gl_FragCoord.z / gl_FragCoord.w) - fogPlanes.x)/(fogPlanes.y - fogPlanes.x), 1.0f), 0.0f);
    float emiss_fog_t = max(min(((gl_FragCoord.z / gl_FragCoord.w) - (fogPlanes.x - 10))/(fogPlanes.y + 50*specular_emiss.g - (fogPlanes.x - 10)), 1.0f), 0.0f);


    vec3 emiss = albedo_color * specular_emiss.g;
    vec3 foggy_emiss = (vec3(0) - emiss) * emiss_fog_t + emiss;

    // not lerp = (b-a)*t + a
    c_final = vec4((clearColor - lit_color)*fog_t + lit_color + foggy_emiss, 1.0f);
}