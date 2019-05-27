#version 430 core

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 emission;
    float shininess;
};

struct dirLight{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 pos;
in vec4 vColor;
in vec2 textureCoord;
in vec3 vnormal;

out vec4 color;

uniform dirLight myDirectionalLight;
uniform sampler2D myTexture;
uniform float useTexture;
uniform Material myMaterial;
uniform vec3 eyePos;

vec3 CalcDirLight(dirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    vec3 reflectDir = reflect(-lightDir, normal);

	vec3 ambient = light.ambient * myMaterial.ambient;
	vec3 diffuse = light.diffuse * myMaterial.diffuse * max(dot(normal, lightDir), 0.0);
	vec3 specular = light.specular * myMaterial.specular * pow(max(dot(viewDir, reflectDir), 0.0), myMaterial.shininess);

    return (ambient + diffuse + specular);
} 

void main(){
    vec3 normal = normalize(vnormal);
    vec3 viewDir = normalize(eyePos - pos);
    
    vec3 result = CalcDirLight(myDirectionalLight, normal, viewDir);
    color = vec4(result + myMaterial.emission, 1.f) * mix(vColor, texture(myTexture, textureCoord), useTexture);
}
