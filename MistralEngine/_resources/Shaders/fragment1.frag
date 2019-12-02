#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform float intensity;
uniform int specularintensity;
uniform sampler2D texture_diffuse1;
uniform vec3 viewPos;

void main()
{    
	
	
	vec3 ambient = intensity * lightColor;
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir),0.0), specularintensity);
	vec3 result = (ambient + diffuse + spec);
    FragColor = texture(texture_diffuse1, TexCoords) * vec4(result,1.0);
}