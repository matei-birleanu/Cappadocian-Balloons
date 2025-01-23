#version 330

// Input
in vec2 texcoord;

// Uniform properties
uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform int mixer;

uniform int u_deformBalon;

// Output
layout(location = 0) out vec4 out_color;

void main()
{
    vec4 colour1 = texture(texture_1, texcoord);
    vec4 colour2 = texture(texture_2, texcoord);

    vec4 colour;
    if (mixer == 1)
    {
    colour = mix(colour1, colour2, 0.5);
    }
    else
    {
        colour = colour1;
    }

    if (colour.a < 0.5f)
    {
        discard;
    }

    out_color = colour;
}
