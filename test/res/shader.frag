#version 330 core
#ifdef GL_ES
precision mediump float
#endif

uniform float myvalue;

vec3 c1=vec3(0.1,0.2,0.8);
vec3 c2=vec3(1.0,0.5,0.2);
out vec4 FragColor;

void main(){
    
    vec3 color=vec3(0.0);
    float pct=abs(sin(myvalue));
    color=mix(c1,c2,pct);

    FragColor=vec4(color,1.0);
}