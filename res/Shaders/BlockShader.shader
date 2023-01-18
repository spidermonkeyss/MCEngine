#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in float blockId;
layout(location = 2) in vec3 neighborIds1;
layout(location = 3) in vec3 neighborIds2;

out float v_blockId;
out vec3 v_neighborIds1;
out vec3 v_neighborIds2;

void main()
{
	gl_Position = position;
	v_blockId = blockId;
	v_neighborIds1 = neighborIds1;
	v_neighborIds2 = neighborIds2;
};

#shader geometry
#version 330 core

layout(points) in;
layout(triangle_strip, max_vertices = 36) out;

uniform mat4 u_MVP;
uniform int u_BlockTypeAmount;

in float v_blockId[];
in vec3 v_neighborIds1[];
in vec3 v_neighborIds2[];
out vec2 g_TexCoord;

//0 = +z, 1 = +x, 5 = +y
vec4 v[8] = vec4[8](
	vec4(-0.5f, -0.5f,  0.5f, 0.0f),//bot front left
	vec4( 0.5f, -0.5f,  0.5f, 0.0f),//bot front right
	vec4( 0.5f,  0.5f,  0.5f, 0.0f),//top front right
	vec4(-0.5f,  0.5f,  0.5f, 0.0f),//top front left
	vec4( 0.5f, -0.5f, -0.5f, 0.0f),//bot back left
	vec4(-0.5f, -0.5f, -0.5f, 0.0f),//bot back right
	vec4(-0.5f,  0.5f, -0.5f, 0.0f),//top back right
	vec4( 0.5f,  0.5f, -0.5f, 0.0f)//top back left
);
//first three are indices for triangle fourth is face
int index[48] = int[48](
	0, 1, 2, 0,
	2, 3, 0, 0,
	4, 5, 6, 2,
	6, 7, 4, 2,
	5, 0, 3, 1,
	3, 6, 5, 1,
	1, 4, 7, 3,
	7, 2, 1, 3,
	3, 2, 7, 5,
	7, 6, 3, 5,
	5, 4, 1, 4,
	1, 0, 5, 4
);

void main()
{
	float numOfBlockType = u_BlockTypeAmount;
	int face;

	//Air block
	if (v_blockId[0] == 0)
		return;

	bool render = false;
	if (v_neighborIds1[0].x == 0)
		render = true;
	else if (v_neighborIds1[0].y == 0)
		render = true;		  
	else if (v_neighborIds1[0].z == 0)
		render = true;		  
	else if (v_neighborIds2[0].x == 0)
		render = true;		  
	else if (v_neighborIds2[0].y == 0)
		render = true;		  
	else if (v_neighborIds2[0].z == 0)
		render = true;
	
	if (!render)
		return;

	for (int i = 0; i < 48; i += 8)
	{
		face = index[i + 3];
		gl_Position = u_MVP * (gl_in[0].gl_Position + v[index[i + 0]]);
		g_TexCoord = vec2(0.0f, 0.0f);
		g_TexCoord.x = (g_TexCoord.x / 6.0f) + ((1.0f / 6.0f) * face);
		g_TexCoord.y = (g_TexCoord.y / numOfBlockType) + ((1.0f / numOfBlockType) * (v_blockId[0] - 1));
		EmitVertex();
		
		gl_Position = u_MVP * (gl_in[0].gl_Position + v[index[i + 1]]);
		g_TexCoord = vec2(1.0f, 0.0f);
		g_TexCoord.x = (g_TexCoord.x / 6.0f) + ((1.0f / 6.0f) * face);
		g_TexCoord.y = (g_TexCoord.y / numOfBlockType) + ((1.0f / numOfBlockType) * (v_blockId[0] - 1));
		EmitVertex();
		
		gl_Position = u_MVP * (gl_in[0].gl_Position + v[index[i + 2]]);
		g_TexCoord = vec2(1.0f, 1.0f);
		g_TexCoord.x = (g_TexCoord.x / 6.0f) + ((1.0f / 6.0f) * face);
		g_TexCoord.y = (g_TexCoord.y / numOfBlockType) + ((1.0f / numOfBlockType) * (v_blockId[0] - 1));
		EmitVertex();
		
		EndPrimitive();

		face = index[i + 7];
		gl_Position = u_MVP * (gl_in[0].gl_Position + v[index[i + 4]]);
		g_TexCoord = vec2(1.0f, 1.0f);
		g_TexCoord.x = (g_TexCoord.x / 6.0f) + ((1.0f / 6.0f) * face);
		g_TexCoord.y = (g_TexCoord.y / numOfBlockType) + ((1.0f / numOfBlockType) * (v_blockId[0] - 1));
		EmitVertex();

		gl_Position = u_MVP * (gl_in[0].gl_Position + v[index[i + 5]]);
		g_TexCoord = vec2(0.0f, 1.0f);
		g_TexCoord.x = (g_TexCoord.x / 6.0f) + ((1.0f / 6.0f) * face);
		g_TexCoord.y = (g_TexCoord.y / numOfBlockType) + ((1.0f / numOfBlockType) * (v_blockId[0] - 1));
		EmitVertex();

		gl_Position = u_MVP * (gl_in[0].gl_Position + v[index[i + 6]]);
		g_TexCoord = vec2(0.0f, 0.0f);
		g_TexCoord.x = (g_TexCoord.x / 6.0f) + ((1.0f / 6.0f) * face);
		g_TexCoord.y = (g_TexCoord.y / numOfBlockType) + ((1.0f / numOfBlockType) * (v_blockId[0] - 1));
		EmitVertex();

		EndPrimitive();
	}
}

#shader fragment
#version 330 core

//default layout location is 0
out vec4 color;
in vec2 g_TexCoord;

uniform sampler2D u_TextureAtlas;

void main()
{
	vec4 texColor = texture(u_TextureAtlas, g_TexCoord);
	color = texColor;
};