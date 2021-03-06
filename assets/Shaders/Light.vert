#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3 v_Normal;
out vec3 v_FragPos;

void main()
{
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
	v_FragPos = vec3(u_Transform * vec4(a_Position, 1.0));
	v_Normal = a_Normal;
}