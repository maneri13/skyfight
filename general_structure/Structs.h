/*
no header required included in Includes.h file
*/
/*
create all your structs here
*/
/*************** for setup and project use ****************/
typedef struct{
	float x;
	float y;
} Point2D;

typedef struct{
	float r;
	float g;
	float b;
	float a;
} Color;

typedef struct {
	int left;
	int bottom;
	int width;
	int height;
} Rect;

typedef struct {
	int centerX;
	int centerY;
	int radius;
} Circle;

typedef struct {
	int pixWidth, pixHeight;	// width/height in pixels
	float z;					// distance from the origin in world units (future purpose)
} Screen;

typedef struct {
	int left;
	int right;
	int bottom;
	int top;
} CartesianSystem;

typedef struct {
	Screen windowSR;						// window screen resolution
	Screen windowSP;						// window screen position
	char *title;							// window title
	Color backgroundColor;					// world background color
	float pointSize;						// world point size
	float lineWidth;						// world line width
	CartesianSystem ortho2D;				// world cartesion system
} EnvironmentSetup;

/**************** define extra structures here *****************/