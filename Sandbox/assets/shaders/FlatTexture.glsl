#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec2 v_TexCoord;

void main()
{
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
	v_TexCoord  = vec2(a_Position.x, a_Position.y);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;
uniform sampler2D u_Texture;
uniform vec4 u_TexParams;

in vec2 v_TexCoord;

void main()
{
	vec2 texCoords = v_TexCoord * u_TexParams.zw;
	texCoords += u_TexParams.xy;

	color  = texture(u_Texture, texCoords) * u_Color;
}