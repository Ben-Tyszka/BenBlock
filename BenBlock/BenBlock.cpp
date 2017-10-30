#include "stdafx.h"

#include "Cube.h"
#include "File.h"

void error_callback(int error, const char* description);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

bool move_x_pos, move_x_neg, move_y_neg, move_y_pos, move_z_pos, move_z_neg;
float speed = 0.04f;
double xpos_mouse, ypos_mouse;
int main()
{
	printf("Log: BenBlock Version %s\n", B_VERSION);

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow* window;

	window = glfwCreateWindow(1280, 720, "BenBlock Version " B_VERSION, NULL, NULL);

	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		return -1;
	}

	glClearColor(26/255, 209/255, 255/255, 0.0f);

	printf("Log: %s\n", glGetString(GL_VERSION));
	printf("Log: %s\n", glGetString(GL_VENDOR));

#pragma region FPS COUNTER SETUP
	int frames = 0;
	double t, t0, fps;
	t0 = glfwGetTime();
#pragma endregion

	glfwSetKeyCallback(window, key_callback);
	Camera cam;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
	glfwPollEvents();
	glfwSetCursorPos(window, 1280 / 2, 720 / 2);
	const int iter = 2, WIDTH = 5, HEIGHT = 3, DEPTH = 2;
	Cube* cub_m[WIDTH * HEIGHT * DEPTH];

	int counter = 0;

	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			for (int z = 0; z < DEPTH; z++) {
				cub_m[counter] = new Cube(cam, "dirt.bmp", glm::vec3(x * iter, y * iter, z * iter));
				counter++;
			}
		}
	}
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#pragma region Camera Translation
		if (move_y_pos) {
			cam.MoveRight();
		}
		if (move_y_neg) {
			cam.MoveLeft();
		}
		if (move_z_neg) {
			cam.TranslateCamera(glm::vec3(cam.x, cam.y -= speed, cam.z));
		}
		if (move_z_pos) {
			cam.TranslateCamera(glm::vec3(cam.x, cam.y += speed, cam.z));
		}
		if (move_x_pos) {
			cam.MoveForward();
		}
		if (move_x_neg) {
			cam.MoveBackwards();
		}
#pragma endregion
#pragma region Camera LookAt
		glfwGetCursorPos(window, &xpos_mouse, &ypos_mouse);
		cam.LookAt(xpos_mouse, ypos_mouse);
#pragma endregion
#pragma region FPS COUNTER


		t = glfwGetTime();

		if ((t - t0) > 1.0 || frames == 0)
		{
			fps = (double)frames / (t - t0);

			std::stringstream ss;
			ss << "BenBlock" << " " << B_VERSION << " [" << fps << " FPS] (" << cam.lx << "," << cam.ly << "," << cam.z << ")";

			glfwSetWindowTitle(window, ss.str().c_str());
			t0 = t;
			frames = 0;
		}

		frames++;
#pragma endregion

		for (int i = 0; i < sizeof(cub_m) / sizeof(cub_m[0]); i++) {
			cub_m[i]->cam = cam;
			cub_m[i]->Render();
		}
		glfwSwapBuffers(window);
		glfwPollEvents();

	};
	for (int i = 0; i < sizeof(cub_m) / sizeof(cub_m[0]); i++) {
		delete cub_m[i];
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
	return 0;
}
void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		exit(EXIT_SUCCESS);
	}

	if (key == GLFW_KEY_W) {
		if (action == GLFW_PRESS) {
			move_x_pos = true;
		}
		else if (action == GLFW_RELEASE) {
			move_x_pos = false;
		}
	}

	if (key == GLFW_KEY_S) {
		if (action == GLFW_PRESS) {
			move_x_neg = true;
		}
		else if (action == GLFW_RELEASE) {
			move_x_neg = false;
		}
	}

	if (key == GLFW_KEY_A) {
		if (action == GLFW_PRESS) {
			move_y_neg = true;
		}
		else if (action == GLFW_RELEASE) {
			move_y_neg = false;
		}
	}
	if (key == GLFW_KEY_D) {
		if (action == GLFW_PRESS) {
			move_y_pos = true;
		}
		else if (action == GLFW_RELEASE) {
			move_y_pos = false;
		}
	}
	if (key == GLFW_KEY_LEFT_SHIFT) {
		if (action == GLFW_PRESS) {
			move_z_pos = true;
		}
		else if (action == GLFW_RELEASE) {
			move_z_pos = false;
		}
	}
	if (key == GLFW_KEY_LEFT_CONTROL) {
		if (action == GLFW_PRESS) {
			move_z_neg = true;
		}
		else if (action == GLFW_RELEASE) {
			move_z_neg = false;
		}
	}
}