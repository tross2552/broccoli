#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
uniform vec4 u_Color;

out vec3 v_Position;
out vec4 v_Color;
out vec2 v_TexCoord;

void main()
{
	v_Position = a_Position * 0.5 + 0.5;
	v_Color = a_Color;
	v_Color *= u_Color;
	v_TexCoord = a_TexCoord;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform sampler2D u_Texture;


in vec3 v_Position;
in vec4 v_Color;
in vec2 v_TexCoord;

void main()
{
	//color   = vec4( v_Position , 1.0 );
	color = texture(u_Texture, v_TexCoord);
	//color   = vec4( v_TexCoord , 0.0 , 1.0 );
	//color  *= v_Color;
}