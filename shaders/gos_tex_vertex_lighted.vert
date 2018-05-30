//#version 300 es
// using this because it is required if we want to use "binding" qualifier in layout (can be set in cpp code but it is easier to do in shader, so procedd like this and maybe change later)
#version 420

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec4 aRGBLight;
layout(location = 3) in vec2 texcoord;


layout (binding = 1, std140) uniform mesh_data
{ 
  vec4 ambient;
  vec4 diffuse;
};

// should be in sync with C++ code
#define     LIGHT_DATA_ATTACHMENT_SLOT      0

#define 	TG_LIGHT_AMBIENT				0
#define		TG_LIGHT_INFINITE				1
#define		TG_LIGHT_INFINITEWITHFALLOFF	2
#define 	TG_LIGHT_POINT					3
#define		TG_LIGHT_SPOT					4
#define		TG_LIGHT_TERRAIN				5
#define MAX_LIGHTS_IN_WORLD 16

layout (binding = 0, std140) uniform LightsDataArrays
{
    mat4 light_to_shape[MAX_LIGHTS_IN_WORLD];
    vec4 light_dir[MAX_LIGHTS_IN_WORLD]; // w - light type
    vec4 root_light_dir[MAX_LIGHTS_IN_WORLD];
    vec4 spot_light_dir[MAX_LIGHTS_IN_WORLD];
}lights_data_arrays;

layout (binding = LIGHT_DATA_ATTACHMENT_SLOT, std140) uniform LightsData
{
    mat4 light_to_world[MAX_LIGHTS_IN_WORLD];
    vec4 light_dir[MAX_LIGHTS_IN_WORLD]; // w - light type
    vec4 light_color[MAX_LIGHTS_IN_WORLD];
} lights_data;


uniform mat4 mvp_; // TODO: remove, use wvp_ instead

uniform mat4 world_;
uniform mat4 view_;
uniform mat4 wvp_;

// common parameters
uniform mat4 projection_;
uniform vec4 vp; //viewport

uniform float forceZ; // baked in a wvp matrix

out vec3 Normal;
out float FogValue;
out vec2 Texcoord;
out vec4 Light;


void main(void)
{
    vec4 p = wvp_ * vec4(pos.xyz, 1);
    float rhw = 1 / p.w;

    p.x = (p.x * rhw) * vp.z + vp.x + 100.0;
    p.y = (p.y * rhw) * vp.w + vp.y;
    p.z = p.z * rhw;
    p.w = abs(rhw);


    vec4 p2 = projection_ * vec4(p.xyz,1);

    //mat4 norm_view_mat = inverse(view_);

    gl_Position = p2 / p.w;
    //Normal = ((world_ * view_) * vec4(normal, 0)).xyz;
    Normal = (world_ * vec4(normal, 0)).xyz;
    //FogValue = fog.w;
    Texcoord = texcoord;
    Light = aRGBLight;
}

