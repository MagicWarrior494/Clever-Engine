#version 330 core
			
in layout(location = 0) vec3 a_Position;
in layout(location = 1) vec3 a_Normal;
in layout(location = 2) mat4 a_Transform;
in layout(location = 6) vec3 a_Color;

uniform mat4 u_ViewProjection;
out vec3 v_Normal;
out vec3 v_FragPos;
out vec3 v_Color;

void main()
{
	vec3 changedPosition = a_Position;
	v_FragPos = vec3(a_Transform * vec4(changedPosition, 1.0));
	gl_Position = u_ViewProjection * a_Transform * vec4(changedPosition, 1.0f);
	v_Normal = a_Normal;
	v_Color = a_Color;
}