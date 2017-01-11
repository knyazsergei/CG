uniform float TWIST;

void main()
{
    // Calculate rotation angle

    float angle = gl_Vertex.y * TWIST;
    // calculate sin(angle) and cos(angle)
    float sa = sin(angle);
    float ca = cos(angle);

     //http://www.wolframalpha.com/input/?i=cannabis+curve
	float radius = ( sin(angle) + 1.5) * (0.9 * cos(8 * angle) + 1) * (0.1 * cos(24 * angle) + 1) * (0.1 * cos( 200 * angle ) + 0.9);
    
   
	vec4 twistedCoord = vec4(
        radius * ca,
        radius * sa,
        gl_Vertex.z,
        gl_Vertex.w
    );
	
    vec4 position = gl_ModelViewProjectionMatrix * twistedCoord;
    // Transform twisted coordinate
    gl_Position = position;
    gl_FrontColor = (position + vec4(1.0)) * 0.5;
}
