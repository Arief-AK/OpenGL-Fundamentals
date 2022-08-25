#version 330 core

// Get colour from vertex shader
in vec3 ourColor;

// Get positions to colour from vertex shader
in vec3 ourPosition;

// Return the fragment colour
out vec4 FragColor;

void main()
{
    FragColor = vec4(ourPosition, 1.0);
}

// Question: Why is the bottom-left side of the triangle black?
// As we assigned the fragment colour to the position of the triangle,
// the most bottom-left position (coordinate) is (-0.5f,-0.5f,0.0f).
// With this, we know that the 'x' and 'y' axes are negative. This means,
// the returned float value when constructing the vec4 'FragColor', the
// colour value is set to '0.0f'. Therefore, the colour result will be
// (0.0f,0.0f,0.0f) which is black. This continues until the axes are in
// positive space, which in turn will differ from the black colour.