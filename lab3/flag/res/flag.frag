const vec4 WHITE = vec4(1.0, 1.0, 1.0, 0);
const vec4 RED = vec4(1.0, 0, 0, 0);
const vec4 BLUE = vec4(0, 0, 1.0, 0);
const vec4 GREEN = vec4(0, 1.0, 0, 0);
const vec4 BLACK = vec4(0, 0, 0, 0);
const vec2 CENTER = vec2(2, 2);
const float PI =  3.14159265359;


bool PointIsOnTheLeft(vec2 p0, vec2 p1, vec2 p)
{
    vec2 p0p1 = p1 - p0;
    // find the orthogonal vector to p0p1
    vec2 n = vec2(-p0p1.y, p0p1.x);
    // Find the dot product between n and (p - p0)
    return dot(p - p0, n) > 0.0;
}

bool PointIsInsideTriangle(vec2 p0, vec2 p1, vec2 p2, vec2 p)
{
    return PointIsOnTheLeft(p0, p1, p) &&
           PointIsOnTheLeft(p1, p2, p) &&
           PointIsOnTheLeft(p2, p0, p);
}

bool PointIsInsideStar(vec2 starsVert[5], vec2 point)
{
	bool isInT1 = PointIsInsideTriangle(starsVert[0], starsVert[2], starsVert[3], point);
	bool isInT2 = PointIsInsideTriangle(starsVert[1], starsVert[3], starsVert[4], point);
	bool isInT3 = PointIsInsideTriangle(starsVert[2], starsVert[4], starsVert[0], point);
	bool isInT4 = PointIsInsideTriangle(starsVert[3], starsVert[0], starsVert[1], point);

	int sum = int(isInT1) + int(isInT2) + int(isInT3) + int(isInT4);
	return (sum >= 2);
}

//check in circle
bool inCircle(vec2 center, float radius, vec2 point)
{
	return pow((point.x - center.x), 2) + pow((point.y - center.y), 2) < radius * radius;
}

//check in cross
bool inCross(vec2 center, vec2 radius, vec2 point)
{
	if((point.x >= center.x - radius.x * 0.5) && (point.x <= center.x + radius.x * 0.5)&&
	   (point.y >= center.y - radius.y * 0.5) && (point.y <= center.y + radius.y * 0.5))
	{
		return true;
	}
	else if((point.x >= center.x - radius.y * 0.5) && (point.x <= center.x + radius.y * 0.5)&&
	   		(point.y >= center.y - radius.x * 0.5) && (point.y <= center.y + radius.x * 0.5))
	{
		return true;
	}

	return false;
}


//chekc in ring
bool inRing(vec2 center, vec2 point, float radius1, float radius2)
{
	return pow((point.x - center.x), 2) + pow((point.y - center.y), 2) < radius1 * radius1 && pow((point.x - center.x), 2) + pow((point.y - center.y), 2) > radius2 * radius2;
}

//creat star
vec2[5] CreateStarVertexes(vec2 center, float radius)
{
	vec2 starsVert[5];

	int i;
	int count = 5;
	float x = center.x;
	float y = center.y;

	float angle;
  	for (int i = 0; i < count; i++)
  	{
   		angle = 2 * PI / count * i + 0.5 * PI;
   		starsVert[i] = vec2( radius * cos(angle) + x, radius * sin(angle) + y);
  	}

	return starsVert;
}



void main()
{
	vec2 position = gl_TexCoord[0].xy;
    vec4 color = WHITE;

    vec2 star[5] = CreateStarVertexes(vec2(2, 2),0.5);
    if(inCross(vec2(3.2, 3.2), vec2(0.5, 0.2), position))
    {
    	color = RED;
    }else if(inCircle(vec2(1,3.2), 0.5, position))
    {
    	color = RED;
    }
    if(PointIsInsideStar(star, position))
    {
    	color = WHITE;
    }
    else if(inRing(CENTER, position, 1, 0.8))//big circle
	{
		color = BLACK;
	}
	else
	{	
    	if( 1.33  > position.y ) {
    	    color = RED;
    	}
    	else if( 2.66  > position.y )
    	{
    		color = BLUE;
    	}
    }
	gl_FragColor = color;
}