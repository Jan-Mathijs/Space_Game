attribute vec4 a_position;

varying vec3 vTexCoordinates;

uniform mat4 MVP; 

//code form https://www.haroldserrano.com/blog/how-to-apply-a-skybox-in-opengl
void main()
{

//4. Generate the UV coordinates

vTexCoordinates = normalize(a_position.xyz);

//5. transform every position vertex by the model-view-projection matrix

gl_Position = MVP * a_position;

//6. Trick to place the skybox behind any other 3D model

gl_Position = gl_Position.xyww;
}