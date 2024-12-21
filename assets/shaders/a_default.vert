#version 430 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_texcoord;
layout (location = 2) in vec3 in_normal;

uniform mat4 u_view;
uniform mat4 u_projection;
uniform mat4 u_model = mat4(1.0);

out vec3 out_position;
out vec3 out_normal;

void main(){
	out_position = in_position;
	out_normal = in_normal;
	gl_Position = u_projection * u_view * u_model * vec4(in_position, 1.0);
}