#type vertex
#version 330 core

layout(location = 0) in vec3  a_Position;
layout(location = 1) in vec4  a_Color;
layout(location = 2) in vec2  a_TexCoord;
layout(location = 3) in float a_TexSlot;

uniform mat4 u_ViewProjection;

out vec4 v_Color;
out vec2 v_TexCoord;
out float  v_TexSlot;

void main()
{
	v_Color = a_Color;
	v_TexSlot = a_TexSlot;
	v_TexCoord  = a_TexCoord;
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;
uniform sampler2D u_Textures[32];
uniform vec4 u_TexParams;

in vec4 v_Color;
in vec2 v_TexCoord;
in float  v_TexSlot;
in vec4 v_TexOffset;

void main()
{
	//color = vec4(2-v_TexSlot, v_TexSlot-1, v_TexSlot-32, 1);
	//color = vec4(v_TexCoord,0,1) * v_Color;
	color = texture(u_Textures[int(v_TexSlot)], v_TexCoord) * v_Color;
	//color  = texture(u_Textures[v_TexSlot], v_TexCoord);
	//color = v_Color;
}