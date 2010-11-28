uniform mat4 worldMatrix;
attribute vec3 g_Position;
attribute vec2 g_TexCoord0;
varying vec2 texCoord;
void main()
{
  gl_Position = worldMatrix * vec4(g_Position.x, g_Position.y, g_Position.z, 1.0);
  texCoord = g_TexCoord0;
}



   
