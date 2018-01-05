#version 130

// Ouput data
//layout(location = 0) out float fragmentdepth;

uniform vec4 farPlane;
uniform vec4 nearPlane;

varying vec4 localPosition;


float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC
    return (2.0 * nearPlane.x * farPlane.x) / (farPlane.x + nearPlane.x - z * (farPlane.x - nearPlane.x));
}

void main(){
    // Not really needed, OpenGL does it anyway
    //fragmentdepth = gl_FragCoord.z;
    //gl_FragDepth = gl_FragCoord.z;

    float depthValue = localPosition.z / localPosition.w * 4;
    //gl_FragColor = vec4(vec3(LinearizeDepth(depthValue) / farPlane.x), 1.0); // perspective
    gl_FragColor = vec4(depthValue);          // orthographic
}
