precision mediump float;  

varying vec2 v_texCoord;                            
uniform sampler2D s_texture;                        
uniform vec4  Ambient;
void main()                                         
{                                                   
  gl_FragColor = texture2D( s_texture, v_texCoord )*Ambient;
} 