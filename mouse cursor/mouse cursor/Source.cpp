
#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"
#include<time.h>

const int width = 680;
const int height = 500;

float* pixels = new float[width*height * 3];

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue);
void drawcircle(const int&i0, const int& j0, int r);

class Line
{
public:
	int start_x, start_y, end_x, end_y;
	void draw()
	{
		drawLine(start_x, start_y, end_x, end_y, 0.0f, 0.5f, 1.0f);
	}
};

class Circle 
{
public:
	int x_c, y_c, r;
	void draw()
	{
		drawcircle(x_c, y_c, r);
	}
};
const int num_lines = 5;
Line *my_lines = new Line[num_lines];


double pos_x, pos_y;
GLFWwindow* window;

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

bool isinside(double pos_x, double pos_y, int x_c, int y_c, int r)
{
	if (r < 40) return false;   //안의 원까지 색깔이 변하는 것을 방지.
	double TF = (pos_x - x_c)*(pos_x - x_c) + (pos_y - y_c)*(pos_y - y_c) - r*r;
	if (TF > 0)return false;
	else return true;
}
//원안에 있는지 판별

// scratched from https://courses.engr.illinois.edu/ece390/archive/archive-f2000/mp/mp4/anti.html
// see 'Rasterization' part.
void drawcircle(const int&i0, const int& j0, int r)
{

	int x = r;
	int y = 0;
	int err = 0;
	float red, green, blue;

	red = 1.0f, green = 0.0f, blue = 0.0f; //평소엔 빨간색

	if (isinside(pos_x, height-pos_y,i0,j0,r)==true) {
		red = 0.0f; green = 0.0f; blue = 1.0f;
	}
	//마우스커서가 원안에 있을 떄는 파란색

	while (x >= y)
	{
		drawPixel(i0 + x, j0 + y, red, green, blue);
		drawPixel(i0 + y, j0 + x, red, green, blue);
		drawPixel(i0 - y, j0 + x, red, green, blue);
		drawPixel(i0 - x, j0 + y, red, green, blue);
		drawPixel(i0 - x, j0 - y, red, green, blue);
		drawPixel(i0 - y, j0 - x, red, green, blue);
		drawPixel(i0 + y, j0 - x, red, green, blue);
		drawPixel(i0 + x, j0 - y, red, green, blue);

		y += 1;
		err += 1 + 2 * y;
		if (2 * (err - x) + 1 > 0)
		{
			x -= 1;
			err += 1 - 2 * x;
		}
	}
}


void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	if (i0 == i1) 
	{
		for (int y = j0; y < j1; y++) 
		{
			drawPixel(i0, y, 1.0f, 0.0f, 0.0f);
		}
	}

	else for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
	
}
void drawOnPixelBuffer()
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background

													//for (int i = 0; i<width*height; i++) {
													//	pixels[i * 3 + 0] = 1.0f; // red 
													//	pixels[i * 3 + 1] = 1.0f; // green
													//	pixels[i * 3 + 2] = 1.0f; // blue
													//}

}

int main(void)
{	
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background
						  /* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		glfwGetCursorPos(window, &pos_x, &pos_y);
		drawOnPixelBuffer();

		int i1 = 80, i2 = 210, i3 = 340, i4 = 470, i5 = 600, j1 = 100, j2 = 400;
		int r = 50;
		for (int y = 0; y < 2; y++)
			for (int x = 0; x < 5; x++)
			{
				drawcircle(80 + 130 * x, 100 + 300 * y, r);
			}

		/*for (int i = 0; i < 5; i++)
		{
			my_lines[i].start_x = 0 + 50 * i;
			my_lines[i].start_y = 0;
			my_lines[i].end_x = 50 + 50 * i;
			my_lines[i].end_y = 50;

			my_lines[i].draw();
		}*/

		//circle-1
		drawLine(i1 - 30, j2 - 30, i1 + 30, j2 + 30, 1.0f, 0.0f, 0.0f);
		drawLine(i1 - 30, j2 - 31, i1 + 30, j2 + 30, 1.0f, 0.0f, 0.0f);
		drawLine(i1 - 30, j2 - 29, i1 + 30, j2 + 30, 1.0f, 0.0f, 0.0f);

		//circle-2
		drawcircle(i2, j2, r - 30);
		//circle-3
		drawLine(i3 - 27, j2 - 27, i3 - 27, j2 + 27, 1.0f, 0.0f, 0.0f);
		drawLine(i3 + 27, j2 - 27, i3 + 27, j2 + 27, 1.0f, 0.0f, 0.0f);

		drawLine(i3 - 27, j2 - 27, i3 + 27, j2 - 27, 1.0f, 0.0f, 0.0f);
		drawLine(i3 - 27, j2 + 27, i3 + 27, j2 + 27, 1.0f, 0.0f, 0.0f);
		//circle-4
		drawLine(i4 - 30, j2 - 30, i4 + 30, j2 + 30, 1.0f, 0.0f, 0.0f);
		drawLine(i4 - 30, j2 + 30, i4 + 30, j2 - 30, 1.0f, 0.0f, 0.0f);
		//circle-5
		drawLine(i5, j2 - 25, i5, j2 + 25, 1.0f, 0.0f, 0.0f);

		drawLine(i5, j2 - 25, i5 + 10, j2 - 15, 1.0f, 0.0f, 0.0f);
		drawLine(i5 - 10, j2 - 15, i5, j2 - 25, 1.0f, 0.0f, 0.0f);
		// circle-6
		drawLine(i1 - 25, j1, i1 + 25, j1, 1.0f, 0.0f, 0.0f);
		drawLine(i1 + 15, j1 + 10, i1 + 25, j1, 1.0f, 0.0f, 0.0f);
		drawLine(i1 + 15, j1 - 10, i1 + 25, j1, 1.0f, 0.0f, 0.0f);
		//circle-7
		drawLine(i2 - 20, j1 - 20, i2, j1 + 20, 1.0f, 0.0f, 0.0f);
		drawLine(i2 - 20, j1 - 21, i2, j1 + 19, 1.0f, 0.0f, 0.0f);

		drawLine(i2, j1 + 20, i2 + 20, j1 - 20, 1.0f, 0.0f, 0.0f);
		drawLine(i2, j1 + 19, i2 + 20, j1 - 21, 1.0f, 0.0f, 0.0f);

		drawLine(i2 - 10, j1, i2 + 10, j1, 1.0f, 0.0f, 0.0f);
		//circle-8
		drawLine(i3, j1 - 30, i3, j1 + 30, 1.0f, 0.0f, 0.0f);
		drawLine(i3 - 30, j1, i3 + 30, j1, 1.0f, 0.0f, 0.0f);
		//circle-9
		drawLine(i4 - 25, j1, i4 + 25, j1, 1.0f, 0.0f, 0.0f);
		drawLine(i4 - 25, j1, i4 - 15, j1 + 10, 1.0f, 0.0f, 0.0f);
		drawLine(i4 - 25, j1, i4 - 15, j1 - 10, 1.0f, 0.0f, 0.0f);
		//circle-10
		drawLine(i5, j1 - 25, i5, j1 + 25, 1.0f, 0.0f, 0.0f);
		
		drawLine(i5 - 10, j1 + 15, i5, j1 + 25, 1.0f, 0.0f, 0.0f);
		drawLine(i5, j1 + 25, i5 + 10, j1 + 15, 1.0f, 0.0f, 0.0f);


		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}