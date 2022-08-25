#version 330 core

// Inputs
in vec3 ourColor;
in vec2 texCoord;

// Outputs
out vec4 FragColor;

// Initialise a 2D sampler for our texture
uniform sampler2D ourTexture;

void main()
{
    // Attempt to colour the fragment with the texture
    FragColor = texture(ourTexture, texCoord);
}