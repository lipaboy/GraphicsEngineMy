#version 130

// Shader parameters
uniform mat4 matrixWorldViewProjT;
uniform vec4 timeT;
uniform mat4 lightSpaceMatrix;

// Vertex structure
attribute vec3 position;
attribute vec4 color;
attribute vec3 normal;

// local variables (between shaders)
varying vec3 localPosition;
varying vec3 localNormal;

//layout (location = 1) in vec2 aTexCoords;
attribute vec2 aTexCoords;

varying vec2 TexCoords;
varying vec4 FragPosLightSpace;


void main()
{
        gl_Position		=   (timeT + vec4(position, 1.0)) * matrixWorldViewProjT;
	gl_FrontColor	= color;
	localPosition	= position + timeT.xyz;
	localNormal		= normal;

        TexCoords = aTexCoords;
        FragPosLightSpace =  vec4(localPosition, 1.0) * lightSpaceMatrix;
}
