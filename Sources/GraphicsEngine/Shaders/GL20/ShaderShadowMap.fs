#version 130

// Ouput data
//layout(location = 0) out float fragmentdepth;

varying vec4 localPosition;

void main(){
    // Not really needed, OpenGL does it anyway
    //fragmentdepth = gl_FragCoord.z;
    //gl_FragDepth = gl_FragCoord.z;

    gl_FragColor = vec4(localPosition.z / localPosition.w * 4);
}
