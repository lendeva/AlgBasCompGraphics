#include <iostream>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

const int NumCol = 4;
int numNowCol = 0;
struct Color {
	float Red, Blue, Black;
	Color(float x, float y, float z) :Red(x), Blue(y), Black(z) {};
};

Color arrayCol[NumCol] = {
	Color(1.0f, 1.0f, 1.0f),//white
	Color(0.0f, 1.0f, 1.0f),//blue
	Color(1.0f, 1.0f, 0.0f),//желтый
	Color(1.0f, 0.0f, 1.0f),//пурпурный
};

void nextCol() {
	numNowCol++;
	if (numNowCol == 4)
		numNowCol = 0;
}


// функция, вызываемая при изменении размеров окна
void reshape(int w, int h)
{
	// установить новую область просмотра, равную всей области окна
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};


void display(void)
{
	// отчищаем буфер цвета и буфер глубины
	glClearColor(0.22, 0.88, 0.11, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);

	// устанавливаем камеру
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5, 5, 7.5, 0, 0, 0, 0, 1, 0);

	// выводим объект - пурпурный (1,0,1 ) чайник
	glColor3f(arrayCol[numNowCol].Red, arrayCol[numNowCol].Blue, arrayCol[numNowCol].Black);
	glutWireTeapot(1.5);

	// смена переднего и заднего буферов
	glutSwapBuffers();
};
int sum = 0;
const int simulation_inter = 1000;
const int time_func = 20;
// функция вызывается каждые 20 мс
void simulation(int value)
{
//	sum += time_func;
//	if (sum == simulation_inter) {
	//	nextCol();
	//	sum = 0;
//	}
	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();
	// эта же функция будет вызвана еще раз через 20 мс
	glutTimerFunc(time_func, simulation, 0);
};

// Функция обработки нажатия клавиш
void keyboardFunc(unsigned char key, int x, int y)
{
	printf("Key code is %i\n", key);
	if (key == 32) {
		nextCol();
	}
};

void main(int argc, char** argv)
{
	setlocale(LC_ALL, "ru");

	// инициализация библиотеки GLUT и установка параметров дисплея
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	// СОЗДАНИЕ ОКНА:
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Laba_01");
	//функции обратного вызова
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(20, simulation, 0);
	glutKeyboardFunc(keyboardFunc);
	//Эта функция выполняет бесконечный цикл, в котором непрерывно
	//проверяется поступление новых сообщений от операционной системы
	glutMainLoop();
};


