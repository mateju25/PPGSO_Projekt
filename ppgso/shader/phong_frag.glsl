#version 330
// A texture is expected as program attribute
uniform sampler2D Texture;

// Direction of light
uniform vec3 LightDirection;

// (optional) Transparency
uniform float Transparency;

// (optional) Texture offset
uniform vec2 TextureOffset;

// The vertex shader will feed this input
in vec2 texCoord;

// Wordspace normal passed from vertex shader
in vec4 normal;

in vec3 FragPosition;

// The final color
out vec4 FragmentColor;

void main() {

    vec3 LightDir = normalize(vec3(0, 5, 0) - FragPosition);

    vec3 GlobalColor = vec3(1, 1, 1);
//    vec3 LightColor = vec3(0.1f, 0.1f, 170f / 255f);
    vec3 LightColor = vec3(1, 0, 0);

    float ambientStrength = 0.7f;
    vec4 ambient = vec4(ambientStrength * LightColor, 1);

    // Compute diffuse lighting
    float diff = max(dot(normal, vec4(LightDirection, 1.0f)), 0.0f);
    vec4 diffuse = vec4(diff * GlobalColor, 1);

    // Lookup the color in Texture on coordinates given by texCoord
    // NOTE: Texture coordinate is inverted vertically for compatibility with OBJ
    FragmentColor = texture(Texture, vec2(texCoord.x, 1.0 - texCoord.y) + TextureOffset) * (diffuse + ambient);
    FragmentColor.a = Transparency;
}
