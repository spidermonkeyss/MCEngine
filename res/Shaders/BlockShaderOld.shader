#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 texCoord;

out vec3 v_TexCoord;
uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * (position * vec4 (1.0, 1.0, -1.0, 1.0));
	v_TexCoord = texCoord;
};

#shader geometry
#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3 v_TexCoord[];
out vec2 g_TexCoord;

//0 = +z, 1 = +x, 5 = +y
int GetFace(vec3 v1, vec3 v2, vec3 v3)
{
	vec3 faceNormal = cross(
		normalize(vec3(v1) - vec3(v2)),
		normalize(vec3(v3) - vec3(v2))
	);

	if (faceNormal == vec3(0, 0, 1))
		return 0;
	if (faceNormal == vec3(1, 0, 0))
		return 1;
	if (faceNormal == vec3(0, 0, -1))
		return 2;
	if (faceNormal == vec3(-1, 0, 0))
		return 3;
	if (faceNormal == vec3(0, -1, 0))
		return 4;
	if (faceNormal == vec3(0, 1, 0))
		return 5;

	return 0;
}

mat4 GetRotMat4(int face)
{
	if (face == 0)
		return mat4(1.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000);
	if (face == 1)
		return mat4(-0.000000, 0.000000, -1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, -0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000);
	if (face == 2)
		return mat4(-1.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, -0.000000, 0.000000, -1.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000);
	if (face == 3)
		return mat4(-0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, -1.000000, 0.000000, -0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000);
	if (face == 4)
		return mat4(1.000000, 0.000000, 0.000000, 0.000000, 0.000000, -0.000000, -1.000000, 0.000000, 0.000000, 1.000000, -0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000);
	if (face == 5)
		return mat4(1.000000, 0.000000, 0.000000, 0.000000, 0.000000, -0.000000, 1.000000, 0.000000, 0.000000, -1.000000, -0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000);

	return mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}

void main()
{
	int face = GetFace(normalize(v_TexCoord[0]), normalize(v_TexCoord[1]), normalize(v_TexCoord[2]));

	gl_Position = gl_in[0].gl_Position;
	g_TexCoord = (GetRotMat4(face) * vec4(v_TexCoord[0], 1.0)).xy + 0.5;
	EmitVertex();

	gl_Position = gl_in[1].gl_Position;
	g_TexCoord = (GetRotMat4(face) * vec4(v_TexCoord[1], 1.0)).xy + 0.5;
	EmitVertex();

	gl_Position = gl_in[2].gl_Position;
	g_TexCoord = (GetRotMat4(face) * vec4(v_TexCoord[2], 1.0)).xy + 0.5;
	EmitVertex();

	EndPrimitive();
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