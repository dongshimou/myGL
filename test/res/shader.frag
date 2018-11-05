#version 330 core
#ifdef GL_ES
precision mediump float
#endif

vec3 c1=vec3(0.1,0.2,0.3);
vec3 c2=vec3(0.2,0.3,0.4);

in vec3 outColor;
in vec2 outTexture;
out vec4 FragColor;
uniform sampler2D ourTexture;

void main(){
    
    vec3 color=vec3(0.0);
    color=mix(c1,c2,0.5);

    FragColor = texture(ourTexture, outTexture)*vec4(color,1.0);
}