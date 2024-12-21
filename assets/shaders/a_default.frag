#version 430 core

out vec4 fragColor;

uniform float u_time;
// in vec3 out_position;
in vec3 out_normal;

void main(){
	// vec3 pos_multed = out_position * 2; 
	// fragColor = vec4(
	// 		pos_multed.x * sin(u_time),
	// 		pos_multed.y * cos(u_time),
	// 		(pos_multed.z + 1.0) * (-sin(u_time)), 1.0);

	fragColor = vec4(
			abs(out_normal) * abs(sin(u_time)), 1.0);
}