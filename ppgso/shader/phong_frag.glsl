#version 330
// A texture is expected as program attribute
uniform sampler2D Texture;

// Direction of light
uniform vec3 LightDirection;

// (optional) Transparency
uniform float Transparency;

// (optional) Texture offset
uniform vec2 TextureOffset;

uniform vec3 CamPos;

// The vertex shader will feed this input
in vec2 texCoord;

// Wordspace normal passed from vertex shader
in vec3 normal3;
in vec4 normal4;

in vec3 FragPosition;
in vec3 FragPositionS;

// The final color
out vec4 FragmentColor;

void main() {

    // Point light
    vec3 LightPos = vec3(0, 5, 0);
    vec3 LightDir = normalize(LightPos - FragPosition);
    vec3 LightColor = vec3(1, 1, 1);

    vec3 GlobalColor = vec3(1, 1, 1);

    // Ambient
    vec3 AmbientColor = vec3(0.05f, 0.05f, 130f / 255f);
    float ambientStrength = 0.2f;
    vec4 ambient = vec4(ambientStrength * AmbientColor, 1);

    // Specular
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(CamPos - FragPositionS);
    vec3 reflectDir = reflect(-LightDir, normal3);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
    vec4 specular = vec4(specularStrength * spec * LightColor, 1);

    // Compute diffuse lighting
    // global
//    float diff = max(dot(normal, vec4(LightDirection, 1.0f)), 0.0f);
//    float diff = max(dot(normal, LightDirection), 0.0f);
//    vec4 diffuse = vec4(diff * GlobalColor, 1);
    // point
    float diff = max(dot(normal4, vec4(LightDir, 1.0f)), 0.0f);
//    float diff = max(dot(normal, LightDir), 0.0f);
    vec4 diffuse = vec4(diff * LightColor, 1);

    vec4 combLights = diffuse + ambient + specular;
//    vec4 combLights = specular;

    // Lookup the color in Texture on coordinates given by texCoord
    // NOTE: Texture coordinate is inverted vertically for compatibility with OBJ
    FragmentColor = texture(Texture, vec2(texCoord.x, 1.0 - texCoord.y) + TextureOffset) * combLights;
    FragmentColor.a = Transparency;
}
