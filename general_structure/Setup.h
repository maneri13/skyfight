class _Setup {

private:

	const int default_PointSize = 2;
	const int default_LineWidth = 1;
	const Color default_Color = Color{ 0.2, 0.5, 0.8, 1 };

	EnvironmentSetup myEnv;

	void setTitle(char *title);
	void setWindowSize(Screen windowSize);
	void setWindowPosition(Screen windowPosition);
	void setCartesianSystem(CartesianSystem cartesinSystem);


public:

	// Constructor
	_Setup();

	// Setter's
	void setLineWidth(float width);
	void setPointSize(float size);
	void setBackgroundColor(Color backColor);
	void setupEnvironment(char *title, Screen windowSize, Screen windowPos, CartesianSystem cartesianSystem);

	// Getter's
	float getLineWidth();
	float getPointSize();
	Color getBackgroundColor();
	char* getTitle();
	Screen getWindowSize();
	Screen getWindowPosition();

	void showCoordsLine();

};
/*
empty contstructor, call setupEnvironment() to setup your project environment
*/
_Setup::_Setup(){
	myEnv = {};
}
/*
setup environmnet with minimal req, and with some default values
*/
void _Setup::setupEnvironment(char *title, Screen windowSize, Screen windowPos, CartesianSystem cartesianSystem){
	// Initialize Window
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	this->setWindowSize(windowSize);
	this->setWindowPosition(windowPos);
	this->setTitle(title);
	// InitGL
	//this->setBackgroundColor(default_Color);
	this->setPointSize(default_PointSize);
	this->setLineWidth(default_LineWidth);


	/*glClearColor(1.0f, 1.0f, 1.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	this->setCartesianSystem(cartesianSystem);
	*/
}

void _Setup::setTitle(char *title){
	glutCreateWindow(title);
	myEnv.title = title;
}

char* _Setup::getTitle(){
	return myEnv.title;
}

void _Setup::setLineWidth(float width){
	glLineWidth(width);
	myEnv.lineWidth = width;
}

float _Setup::getLineWidth(){
	return myEnv.lineWidth;
}

void _Setup::setPointSize(float size){
	glPointSize(size);
	myEnv.pointSize = size;
}

float _Setup::getPointSize(){
	return myEnv.pointSize;
}

void _Setup::setBackgroundColor(Color backColor){
	glClearColor(backColor.r, backColor.g, backColor.b, backColor.a);
	myEnv.backgroundColor = backColor;
}

Color _Setup::getBackgroundColor(){
	return myEnv.backgroundColor;
}

void _Setup::setCartesianSystem(CartesianSystem cartesianSystem){
	gluOrtho2D(cartesianSystem.left, cartesianSystem.right, cartesianSystem.bottom, cartesianSystem.top);
	myEnv.ortho2D = cartesianSystem;
}

void _Setup::setWindowSize(Screen windowSize){
	glutInitWindowSize(windowSize.pixWidth, windowSize.pixHeight);
	myEnv.windowSR = windowSize;
}

Screen _Setup::getWindowSize(){
	return myEnv.windowSR;
}

void _Setup::setWindowPosition(Screen windowPos){
	glutInitWindowPosition(windowPos.pixWidth, windowPos.pixHeight);
	myEnv.windowSP = windowPos;
}

Screen _Setup::getWindowPosition(){
	return myEnv.windowSP;
}

void _Setup::showCoordsLine(){
	glBegin(GL_LINES);
	glVertex2d(this->myEnv.ortho2D.right, this->myEnv.ortho2D.top + this->myEnv.ortho2D.bottom);
	glVertex2d(this->myEnv.ortho2D.left, this->myEnv.ortho2D.top + this->myEnv.ortho2D.bottom);
	glEnd();
	glBegin(GL_LINES);
	glVertex2d(this->myEnv.ortho2D.left + this->myEnv.ortho2D.right, this->myEnv.ortho2D.bottom);
	glVertex2d(this->myEnv.ortho2D.left + this->myEnv.ortho2D.right, this->myEnv.ortho2D.top);
	glEnd();
}