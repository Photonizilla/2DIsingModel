#include <GL/glut.h>
#include <cstdio>

#define n 80
float T, m[102];

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_LINES);
	glVertex2f(-0.9f, -0.9f);
	glVertex2f(0.9f, -0.9f);
	glVertex2f(0.9f, -0.9f);
	glVertex2f(0.9f, 0.9f);
	glVertex2f(0.9f, 0.9f);
	glVertex2f(-0.9f, 0.9f);
	glVertex2f(-0.9f, 0.9f);
	glVertex2f(-0.9f, -0.9f);
	glEnd();
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_LINE_STRIP);
	for(int i=1;i<=n;i++) {
		glVertex2f(GLfloat(-0.9 + 1.8 * i / n), GLfloat(-0.9 + 1.8 * m[i]));
	}
	glEnd();
    glFlush();
}

int main(int argc, char** argv) {

	freopen("sample.txt", "r", stdin);

	for(int i=1;i<=n;i++) {
		scanf("%f%f", &T, &m[i]);
	}

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(400, 250);
    glutInitWindowSize(800, 400);
    glutCreateWindow("Ising Monte Carlo");
    glutDisplayFunc(&myDisplay);
    glutMainLoop();

    return 0;
}

