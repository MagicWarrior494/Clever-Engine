#version 330 core
			
layout(location = 0) out vec4 color;

in vec3 v_Normal;
in vec3 v_FragPos;

uniform vec3 u_lightColor;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * u_lightColor;			

    vec3 result = ambient * u_lightColor;
    color = vec4(u_lightColor, 1.0);
}