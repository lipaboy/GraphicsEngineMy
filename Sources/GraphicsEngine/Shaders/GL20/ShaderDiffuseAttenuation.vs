#version 130

// Shader parameters
uniform mat4 matrixWorldViewProjT;
uniform vec4 timeT;

// Vertex structure
attribute vec3 position;
attribute vec4 color;
attribute vec3 normal;

varying vec3 localPosition;
varying vec3 localNormal;

//layout (location = 1) in vec2 aTexCoords;
attribute vec2 aTexCoords;

varying vec2 TexCoords;


void main()
{
        TexCoords = aTexCoords;

	gl_Position		= (timeT + vec4(position, 1.0)) * matrixWorldViewProjT;
	gl_FrontColor	= color;
	localPosition	= position + timeT.xyz;
	localNormal		= normal;
}
