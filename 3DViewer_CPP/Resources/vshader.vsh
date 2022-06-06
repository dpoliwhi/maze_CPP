attribute highp vec4 qt_Vertex;
uniform highp mat4 qt_ModelViewProjectionMatrix;
uniform vec4 color;

varying vec4 vecColor;

void main(void)
{
    vecColor = color;
    gl_Position = qt_ModelViewProjectionMatrix * qt_Vertex;
}
