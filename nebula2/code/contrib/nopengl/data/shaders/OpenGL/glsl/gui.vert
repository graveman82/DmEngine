//------------------------------------------------------------------------------
//  gui.vert
//
//  A 2d rectangle shader for GUI rendering.
//------------------------------------------------------------------------------

uniform mat4 ModelViewProjection;

void main(void)
{
    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_Position = ModelViewProjection * gl_Vertex;
}
