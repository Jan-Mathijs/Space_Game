precision mediump float;     
	attribute vec3 a_position;   
	attribute vec2 a_texCoord;   
	attribute vec3 a_normal;
	
	uniform mat4 MVP;            
	uniform vec3 LightPosition;
	uniform mat3 rotationMatrix;
	uniform mat4 MV;
	varying vec2 v_texCoord;
	varying vec3 v_Color;
	
	void main()                  
	{ 
	vec4 WorldPos = MV * vec4(a_position,1);
	vec3 lightDirection;
	vec3 transformed_normal = normalize(rotationMatrix * a_normal);
	//v_normal = normalize(a_normal);
	lightDirection = normalize(LightPosition - WorldPos.xyz);

	float diff = max(dot(transformed_normal, lightDirection), 0.1);
	v_Color = diff* vec3(1);
	v_texCoord = a_texCoord;
	gl_Position =  MVP * vec4(a_position,1);  
	}