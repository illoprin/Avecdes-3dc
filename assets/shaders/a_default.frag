#version 430

out vec4 fragColor;

uniform float u_time;

void main(){
	fragColor = vec4(
			vec3(sin(u_time), cos(u_time), sin(u_time)), 1.0);
}