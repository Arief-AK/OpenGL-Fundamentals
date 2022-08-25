#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

// Specify a colour
out vec3 ourColor;

// Specify a position
out vec3 ourPosition;

void main()
{
    // Initialise a new position from vec3 type to vec4
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    
    // Positions to be coloured in the fragment shader
    ourPosition = aPos;
}