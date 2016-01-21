class Shanu
{
public:
	Shanu();
	void glCircle(Point2D center, float radius);
	void glCircle(Point2D center, float radius, float angleStart, float angleMultiplier, float angleAdder);
	void RenderString(Point2D position, void *font, char *string, int limit, Color rgb);
	void drawCoordsLine(EnvironmentSetup myEnv);
	void drawRect(int l, int b, int w, int h);
	void drawPolyLineFile(char *fileName);
	bool checkCollision(Circle obj1, Circle obj2);
	bool checkCollision(Rect obj1, Rect obj2);

private:

};

Shanu::Shanu()
{
	// don't do anything
}

void Shanu::glCircle(Point2D center, float radius){
	glBegin(GL_POINTS);
	double x, y;
	for (float angle = 0.0f; angle<2 * 3.14159; angle += 0.05){
		x = radius*cos(angle) + center.x;
		y = radius*sin(angle) + center.y;
		glVertex2d(x, y);
	}
	glEnd();
}

void Shanu::glCircle(Point2D center, float radius, float angleStart, float angleMultiplier, float angleAdder){
	glBegin(GL_POINTS);
	double x, y;
	for (float angle = angleStart; angle<angleMultiplier * 3.14159; angle += angleAdder){
		x = radius*cos(angle) + center.x;
		y = radius*sin(angle) + center.y;
		glVertex2d(x, y);
	}
	glEnd();
}

void Shanu::RenderString(Point2D position, void *font, char *string, int limit, Color rgb)
{
	glColor3f(rgb.r, rgb.g, rgb.b);
	for (int i = 0; i < limit; i++){
		glRasterPos2f(position.x, position.y);
		glutBitmapCharacter(font, string[i]);
		position.x += 12;
	}
}

void Shanu::drawRect(int l, int b, int w, int h){
	glBegin(GL_LINES);
	glVertex2d(l, b);
	glVertex2d(l + w, b);
	glEnd();
	glBegin(GL_LINES);
	glVertex2d(l + w, b);
	glVertex2d(l + w, b + h);
	glEnd();
	glBegin(GL_LINES);
	glVertex2d(l + w, b + h);
	glVertex2d(l, b + h);
	glEnd();
	glBegin(GL_LINES);
	glVertex2d(l, b + h);
	glVertex2d(l, b);
	glEnd();
}

void Shanu::drawPolyLineFile(char *fileName){
	fstream inStream;
	inStream.open(fileName, ios::in);			// open the file
	if (inStream.fail())
		return;
	glClear(GL_COLOR_BUFFER_BIT);				// clear the screen
	GLint numpolys, numLines, x, y;
	inStream >> numpolys;						// read the number of polylines
	for (int j = 0; j < numpolys; j++){			// read each polyline
		inStream >> numLines;
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < numLines; i++){
			inStream >> x >> y;
			glVertex2i(x, y);
		}
		glEnd();
	}
	glFlush();
	inStream.close();
}

bool Shanu::checkCollision(Circle obj1, Circle obj2){
	if ((
		sqrt(pow(obj1.centerX - obj2.centerX, 2) + pow(obj1.centerY - obj2.centerY, 2)
		)) <= obj1.radius + obj2.radius)
	{
		return true;
	}
	return false;
}

bool Shanu::checkCollision(Rect obj1, Rect obj2){
	if (
		(
		((obj1.left + obj1.width) >= obj2.left && (obj1.left + obj1.width) <= (obj2.left + obj2.width)) ||
		((obj1.left) >= obj2.left && (obj1.left) <= (obj2.left + obj2.width))
		) &&
		(
		((obj1.bottom + obj1.height) >= obj2.bottom && (obj1.bottom + obj1.height) <= (obj2.bottom + obj2.height)) ||
		((obj1.bottom) >= obj2.bottom && (obj1.bottom) <= (obj2.bottom + obj2.height))
		) ||
		(
		((obj2.left + obj2.width) >= obj1.left && (obj2.left + obj2.width) <= (obj1.left + obj1.width)) ||
		((obj2.left) >= obj1.left && (obj2.left) <= (obj1.left + obj1.width))
		) &&
		(
		((obj2.bottom + obj2.height) >= obj1.bottom && (obj2.bottom + obj2.height) <= (obj1.bottom + obj1.height)) ||
		((obj2.bottom) >= obj1.bottom && (obj2.bottom) <= (obj1.bottom + obj1.height))
		)
		)
	{
		return true;
	}
	return false;
}