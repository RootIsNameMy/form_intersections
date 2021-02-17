#type vertex
#version 330 core

in vec3 a_position;
in vec2 a_tex_coord;

out vec2 uv;

void main()
{
    gl_Position = vec4(a_position,1);
    uv = a_tex_coord;
}




#type fragment
#version 330 core

out vec4 color;

in vec2 uv;
uniform sampler2D tex;

void main()
{
  color = texture(tex,uv);
}
