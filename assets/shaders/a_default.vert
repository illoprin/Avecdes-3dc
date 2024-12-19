#version 430 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_texcoord;
layout (location = 2) in vec3 in_normal;

uniform mat4 u_view;
uniform mat4 u_projection;

void main(){
	gl_Position = u_projection * u_view * vec4(in_position, 1.0);
}