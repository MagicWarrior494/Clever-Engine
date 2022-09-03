#version 330 core
			
layout(location = 0) out vec4 color;

in vec3 v_Normal;
in vec3 v_FragPos;
in vec3 v_Color;

uniform vec3 u_LightColor;
uniform vec3 u_ViewPos;
uniform vec3 u_LightPos;

vec3 totalDiffuse = vec3(0.0);
vec3 totalAmbient = vec3(0.0);
vec3 totalSpecular = vec3(0.0);

void main()
{
    vec3 norm = normalize(v_Normal);
    float ambientStrength = 0.1;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(u_ViewPos - v_FragPos);

    vec3 lightDir = normalize(u_LightPos - v_FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);

    totalSpecular = (specularStrength * spec * u_LightColor);
    totalDiffuse = (diff * u_LightColor);
    totalAmbient = (ambientStrength * u_LightColor);

    totalAmbient = min(totalAmbient, 0.01);

    vec3 result = (totalDiffuse + totalAmbient + totalSpecular) * v_Color;
    color = vec4(result, 1.0);
}