#version 330 core

// Inputs
in vec3 ourColor;
in vec2 texCoord;

// Outputs
out vec4 FragColor;

// Initialise a 2D sampler for our texture
uniform sampler2D texture_0;
uniform sampler2D texture_1;
uniform float display_value;

void main()
{
    // Attempt to colour the fragment with the texture
    FragColor = mix(texture(texture_0, texCoord), texture(texture_1, texCoord), display_value);
}