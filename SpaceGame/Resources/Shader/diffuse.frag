precision mediump float;    

varying vec2 v_texCoord;    
//varying vec3 v_diffuse;
uniform sampler2D s_texture;                        
uniform vec4  Ambient;
varying vec3 v_Color;

void main()                                         
{             
	
	//vec4 localColor = vec4(v_Color,1) * Ambient;
	gl_FragColor = vec4(v_Color,1) * texture2D( s_texture, v_texCoord) * Ambient;//* v_Color;
	//gl_FragColor.a = 1.0;
} 