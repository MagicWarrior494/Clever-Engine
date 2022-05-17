#version 330 core
			
layout(location = 0) out vec4 color;

in vec3 v_Normal;
in vec3 v_FragPos;
const int u_lightCount = 8;
uniform vec3 u_ObjectColor;
uniform vec3 u_lightPos[u_lightCount];
uniform vec3 u_lightColor[u_lightCount];
uniform vec3 u_viewPos;

vec3 totalDiffuse = vec3(0.0);
vec3 totalAmbient = vec3(0.0);
vec3 totalSpecular = vec3(0.0);

void main()
{
    vec3 norm = normalize(v_Normal);
    float ambientStrength = 0.1;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(u_viewPos - v_FragPos);

    for(int i = 0; i < u_lightCount; i++)
    {
        
        vec3 lightDir = normalize(u_lightPos[i] - v_FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 reflectDir = reflect(-lightDir, norm);  
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);

        totalSpecular = totalSpecular + (specularStrength * spec * u_lightColor[i]);
        totalDiffuse = totalDiffuse + (diff * u_lightColor[i]);
        totalAmbient = totalAmbient + (ambientStrength * u_lightColor[i]);
    }
    totalAmbient = min(totalAmbient, 0.01);

    vec3 result = (totalDiffuse + totalAmbient + totalSpecular) * u_ObjectColor;
    color = vec4(result, 1.0);
}