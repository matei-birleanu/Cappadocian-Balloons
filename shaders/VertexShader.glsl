#version 330

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform int u_deformBalon;

out vec2 texcoord;

void main()
{
    vec3 pos = v_position;

    if (u_deformBalon == 1)
    {
        float factorMax = 2.4; 
        float factorMin = 2.0;

        float t = (pos.y + 1.0) / 2.0; // 0 la y=-1; 1 la y=+1

        float factorFinal = mix(factorMax, factorMin, t);

        pos.y *= factorFinal;
    }

    texcoord = v_texture_coord;

    gl_Position = Projection * View * Model * vec4(pos, 1.0);
}
