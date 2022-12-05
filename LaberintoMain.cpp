

#include <glad.h>
#include <glfw3.h>
#include <stdio.h>
#include <math.h> 

#include "esfera.h"

//Para las transformaciones
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);



// settings
unsigned int SCR_WIDTH = 1200;
unsigned int SCR_HEIGHT = 800;

float Escala = 2;

typedef struct {
	float px, py, pz;
	float angulo_trans;
	float angulo_trans2;
	float sx, sy, sz;
	glm::vec3 color;
	int listarender;
	int num_vertex;
	const char* fichero_textura;
	int textura;
} objeto;

//Personaje
objeto tronco = { 13/Escala, -11/Escala, 0.33, 0.0, -45.0, .2, .1, .27, glm::vec3(1.0f, 1.0f, 1.0f), 0 ,0, "cuerpo.jpg", 0};
objeto piernaI = { -.0467, .0, -0.21, 0.0, 0.0, .083, .093, .25, glm::vec3(1.0f, 1.0f, 1.0f), 0,0, "pierna.jpg", 0 };
objeto piernaD = { .0467, .0, -0.21, 0.0, 0.0, .083, .093, .25, glm::vec3(1.0f, 1.0f, 1.0f), 0,0, "pierna.jpg", 0 };
objeto brazoI = { -.127, .0, 0.0, 0.0, 0.0, .0533, .0533, .23, glm::vec3(1.0f, 1.0f, 1.0f), 0,0, "brazo.jpg" };
objeto brazoD = { .127, .067, 0.067, 90.0, .0, .0533, .0533, .23, glm::vec3(1.0f, 1.0f, 1.0f), 0,0, "brazo.jpg", 0 };
objeto linterna = { .127, .215, 0.067, 0.0, 0.0, .02, .067, .02, glm::vec3(1.0f, 1.0f, 1.0f), 0,0 , "linterna.bmp", 0};
objeto cabeza = { .0, .0, 0.202, -90.0, 0.0, .067, .067, .067, glm::vec3(1.0f, 1.0f, 1.0f), 0,0, "cabeza.jpg", 0};

//Monstruo 1
objeto troncoM1 = { -2.5/Escala, -13.5/Escala, 0.4, .0, 0.0, .2, .2, .4, glm::vec3(1.0f, 1.0f, 1.0f), 0,0, "cuerpoM1.jpg", 0};
objeto brazoIM1 = { -.15, .1, 0.1, 0.0, 0, .1, .3, .1, glm::vec3(1.0f, 1.0f, 1.0f), 0,0, "cuerpoM1.jpg", 0 };
objeto brazoDM1 = { 0.15, .1, 0.1, 0.0, 0, .1, .3, .1, glm::vec3(1.0f, 1.0f, 1.0f), 0,0, "cuerpoM1.jpg", 0 };
objeto cabezaM1 = { .0, .1, 0.42, -90.0, 0.0, .12, .12, .12, glm::vec3(1.0f, 1.0f, 1.0f), 0,0, "cabezaM1.jpg", 0 };

//Monstruo2
objeto troncoM2 = { 10.5/ Escala, 1.0 / Escala, 0.4, .0, 0.0, .2, .2, .4, glm::vec3(1.0f, 1.0f, 1.0f), 0,0, "cuerpoM2.jpg", 0 };
objeto brazoIM2 = { -.15, .1, 0.1, 0.0, 0, .1, .3, .1, glm::vec3(1.0f, 1.0f, 1.0f), 0,0, "cuerpoM2.jpg", 0 };
objeto brazoDM2 = { 0.15, .1, 0.1, 0.0, 0, .1, .3, .1, glm::vec3(1.0f, 1.0f, 1.0f), 0,0, "cuerpoM2.jpg", 0 };
objeto cabezaM2 = { .0, .1, 0.42, -90.0, 0.0, .12, .12, .12, glm::vec3(1.0f, 1.0f, 1.0f), 0,0, "cabezaM2.jpg", 0 };

unsigned const int numCubos = 267;
objeto cubos[numCubos];

unsigned const int numeroPartes = 7;
objeto *partes[numeroPartes];
unsigned const int numeroPartesM = 4;
objeto* partesM1[numeroPartesM];
objeto* partesM2[numeroPartesM];

int coordenadasCubos[numCubos][2] = { {-12,-15}, {-11,-15}, {-10,-15}, {-9,-15}, {-8,-15}, {-7,-15}, {-6,-15}, {-5,-15}, {-4,-15}, {-3,-15}, {-2,-15}, {-1,-15}, {0,-15}, {1,-15}, {2,-15}, {3,-15}, {4,-15}, {5,-15}, {6,-15}, {7,-15}, {8,-15}, {9,-15}, {10,-15}, {11,-15}, {12,-15}, {13,-15}, {14,-15}, {15,-15},
	{-12,-14}, {0,-14}, {12,-14}, {15, -14},
	{-12,-13}, {0,-13}, {12,-13}, {15, -13},
	{-12,-12}, {-9,-12}, {-8,-12}, {-7,-12}, {-6,-12}, {-5,-12}, {-4,-12}, {-3,-12}, {-2,-12}, {-1,-12}, {0,-12}, {1,-12}, {2,-12}, {3,-12}, {4,-12}, {5,-12}, {8,-12}, {9,-12}, {10,-12}, {11,-12}, {12,-12}, {13,-12}, {14,-12}, {15,-12},
	{-12,-11}, {12,-11}, {15,-11},
	{-12,-10}, {12,-10}, {15,-10},
	{-12,-9}, {-9,-9}, {-8,-9}, {-7,-9}, {-6,-9}, {-3,-9}, {-2,-9}, {-1,-9}, {0,-9}, {1,-9}, {2,-9}, {3,-9}, {4,-9}, {5,-9}, {6,-9}, {7,-9}, {8,-9}, {9,-9}, {12,-9}, {13,-9}, {14,-9}, {15,-9},
	{-12,-8}, {-9,-8}, {9,-8}, {12,-8},
	{-12,-7}, {-9,-7}, {9,-7}, {12,-7},
	{-12,-6}, {-9,-6}, {-6,-6}, {-5,-6}, {-4,-6}, {-3,-6}, {-2,-6}, {-1,-6}, {2,-6}, {3,-6}, {4,-6}, {5,-6}, {6,-6}, {9,-6}, {12,-6},
	{-12,-5}, {-9,-5}, {-6,-5}, {-1,-5}, {6,-5}, {9,-5}, {12,-5},
	{-12,-4}, {-9,-4}, {-6,-4}, {-1,-4}, {6,-4}, {9,-4}, {12,-4},
	{-12,-3}, {-9,-3}, {-6,-3}, {-3,-3}, {-2,-3}, {-1,-3}, {0,-3}, {1,-3}, {2,-3}, {3,-3}, {6,-3}, {9,-3}, {12,-3},
	{-12,-2}, {-9,-2}, {-6,-2}, {-3,-2}, {3,-2}, {6,-2}, {9,-2}, {12,-2},
	{-12,-1}, {-9,-1}, {-6,-1}, {-3,-1}, {3,-1}, {6,-1}, {9,-1}, {10,-1}, {11,-1}, {12,-1},
	{-12, 0}, {-9, 0}, {-6, 0}, {-3, 0}, {3, 0}, {6, 0}, {9, 0}, {12, 0},
	{-12, 1}, {-9, 1}, {-6, 1}, {-3, 1}, {3, 1}, {6, 1}, {9, 1}, {12, 1},
	{-12, 2}, {-9, 2}, {-6, 2}, {-3, 2}, {3, 2}, {6, 2}, {9, 2}, {12, 2},
	{-12, 3}, {-9, 3}, {-6, 3}, {6, 3}, {12, 3},
	{-12, 4}, {-9, 4}, {-6, 4}, {6, 4}, {12, 4},
	{-12, 5}, {-9, 5}, {-8, 5}, {-7, 5}, {-6, 5}, {-5, 5}, {-4, 5}, {-3, 5}, {-2, 5}, {-1, 5}, {0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {6, 5}, {7, 5}, {8, 5}, {9, 5}, {10, 5}, {11, 5}, {12, 5},
	{-12, 6}, {-5, 6}, {-2, 6}, {12, 6},
	{-12, 7}, {-5, 7}, {-2, 7}, {12, 7},
	{-12, 8}, {-11, 8}, {-10, 8}, {-9, 8}, {-8, 8}, {-5, 8}, {-2, 8}, {-1, 8}, {0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {9, 8}, {12, 8},
	{-12, 9}, {9, 9},
	{-12, 10}, {9, 10},
	{-12, 11}, {-11, 11}, {-10, 11}, {-9, 11}, {-8, 11}, {-7, 11}, {-6, 11}, {-5, 11}, {-4, 11}, {-3, 11}, {-2, 11}, {-1, 11}, {0, 11}, {1, 11}, {2, 11}, {3, 11}, {4, 11}, {5, 11}, {6, 11}, {7, 11}, {8, 11}, {9, 11}, {10, 11}, {11, 11}, {12, 11}
	};
int posiciones[numCubos][2];
int texturaSuelo;
const char* ficheroSuelo = "suelo.jpg";
int texturaPared;
const char* ficheroParedes = "pared.jpg";

extern GLuint setShaders(const char *nVertx, const char *nFrag);
GLuint shaderProgram;
GLuint shaderProgramB;

unsigned int VAO;
unsigned int VAO_esfera;
unsigned int VAO_cubo;
unsigned int VAO_cuadrado;

unsigned int VAO_vertex = 6;
unsigned int VAO_esfera_vertex = 1080;
unsigned int VAO_cubo_vertex = 36;
unsigned int VAO_cuadrado_vertex = 6;

int texturaIntro;
const char* ficheroIntro = "intro.png";

int texturaVictoria;
const char* ficheroVictoria = "win.png";

int texturaDerrota;
const char* ficheroDerrota = "muerto.png";

int texturaControles;
const char* ficheroControles = "controles.png";

float velocidad = 0.0f;

#define GL_PI 3.14f
#define RADIO 1.0f
#define GradosToRadianes 0.0175

void my_cuadrado(void) {
	unsigned int VBO, EBO;


	float vertices[] = {
		-0.5f, -0.5f,  0.0f,  .0f, .0f, 1.0f,	.0f, .0f,
		 0.5f, -0.5f,  0.0f,  .0f, .0f,1.0f,	1.0f, .0f,
		 0.5f,  0.5f,  0.0f,  .0f,.0f,1.0f,		1.0f, 1.0f,

		 0.5f,  0.5f,  0.0f,  .0f, .0f, 1.0f,	1.0f, 1.0f,
		 -0.5f, 0.5f,  0.0f,  .0f, .0f, 1.0f,	.0f, 1.0f,
		 -0.5f, -0.5f,  0.0f,  .0f, .0f, 1.0f,	.0f, .0f,
	};

	glGenVertexArrays(1, &VAO_cuadrado);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first.
	glBindVertexArray(VAO_cuadrado);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// position Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Texturas
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
void my_esfera() {
	unsigned int VBO;

	glGenVertexArrays(1, &VAO_esfera);
	glGenBuffers(1, &VBO);

	// bind the Vertex Array Object first.
	glBindVertexArray(VAO_esfera);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_esfera), vertices_esfera, GL_STATIC_DRAW);

	// Normales
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	// texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	// vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteBuffers(1, &VBO);

}
void my_cubo() {
	unsigned int VBO, EBO;


	float vertices[] = {
		//Cara frente
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f, .0f, .0f,
		 0.5f, -0.5f,  0.5f,  .0f, 0.0f,1.0f,	1.0f, .0f,
		 0.5f,  0.5f,  0.5f,  .0f, .0f,1.0f,	1.0f, 1.0f,

		 0.5f,  0.5f,  0.5f,  .0f, .0f,1.0f,	1.0f, 1.0f,
		 -0.5f, 0.5f,  0.5f,  .0f, 0.0f,1.0f,	.0f, 1.0f, 
		 -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f,	.0f, .0f,

		 //cara derecha
		 0.5f,  0.5f,  0.5f,  1.0f, .0f,0.0f,	1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,0.0f,	.0f, 1.0f,
		 0.5f, 0.5f,  -0.5f,  1.0f, 0.0f,0.0f,	1.0f, .0f,

		 0.5f,  -0.5f,  0.5f,  1.0f, .0f,0.0f,	.0f, 1.0f,
		 0.5f, -0.5f,  -0.5f,  1.0f, 0.0f,0.0f,	.0f, .0f,
		 0.5f, 0.5f,  -0.5f,  1.0f, 0.0f,0.0f,	1.0f, .0f,

		 //cara izquierda 
		 -0.5f, -0.5f, 0.5f,  -1.0f, 0.0f,0.0f,	1.0f, 1.0f,
		 -0.5f,  0.5f, 0.5f,  -1.0f, .0f,0.0f,	.0f, 1.0f,
		 -0.5f, -0.5f, -0.5f,  -1.0f, 0.0f,0.0f,1.0f, .0f,

		 -0.5f,  0.5f, 0.5f,  -1.0f, .0f,0.0f,	.0f, 1.0f,
		 -0.5f, 0.5f, -0.5f,  -1.0f, 0.0f,0.0f,	.0f, .0f,
		 -0.5f, -0.5f, -0.5f,  -1.0f, 0.0f,0.0f,1.0f, .0f,

		 //cara atras
		 -0.5f, -0.5f, -0.5f,  .0f, 0.0f,-1.0f,	1.0f, .0f,
		 -0.5f,  0.5f, -0.5f,  .0f, .0f,-1.0f,	1.0f, 1.0f,
		 0.5f, 0.5f, -0.5f,  .0f, 0.0f,-1.0f,	.0f, 1.0f,

		 -0.5f,  -0.5f, -0.5f,  .0f, .0f,-1.0f,	1.0f, .0f,
		 0.5f, 0.5f, -0.5f,  .0f, 0.0f,-1.0f,	.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f,-1.0f,	.0f, .0f,

		 //cara abajo
		 -0.5f, -0.5f, 0.5f,  .0f, -1.0f,0.0f,	.0f, 1.0f,
		 -0.5f,  -0.5f, -0.5f,  .0f, -1.0f,0.0f,.0f, .0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,0.0f,	1.0f, .0f,

		 -0.5f, -0.5f, 0.5f,  .0f, -1.0f,0.0f,	.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  .0f, -1.0f,0.0f,	1.0f, .0f,
		 0.5f, -0.5f, 0.5f,  0.0f, -1.0f,0.0f,	1.0f, 1.0f,

		 ////cara arriba
		 0.5f, 0.5f, 0.5f,  .0f, 1.0f,0.0f,		.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  .0f, 1.0f,0.0f,	.0f, .0f,
		 -0.5f, 0.5f, 0.5f,  0.0f, 1.0f,0.0f,	1.0f, 1.0f,

		 -0.5f, 0.5f, 0.5f,  .0f, 1.0f,0.0f,	1.0f, 1.0f,
		 0.5f, 0.5f, -0.5f,  .0f, 1.0f,0.0f,	.0f, .0f,
		 -0.5f, 0.5f, -0.5f,  0.0f, 1.0f,0.0f,	1.0f, .0f,

	};

	glGenVertexArrays(1, &VAO_cubo);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first.
	glBindVertexArray(VAO_cubo);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// position Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Texturas
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

}

void openGlInit() {
	//Habilito aqui el depth en vez de arriba para los usuarios de linux y mac mejor arriba
	//Incializaciones varias
	glClearDepth(1.0f); //Valor z-buffer
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // valor limpieza buffer color
	glEnable(GL_DEPTH_TEST); // z-buffer
	glEnable(GL_CULL_FACE); //ocultacion caras back
	glCullFace(GL_BACK);
}

float alpha = 0;
float beta = 0;
float omega = 10.0f;
int flagCamara = 1;

void camaraExterna(void){
	glm::mat4 view;
	glm::mat4 projection;
	unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
	unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");

	unsigned int viewPosLoc = glGetUniformLocation(shaderProgram, "viewPos");

	glm::vec3 posicionView = glm::vec3((*partes[0]).px+(float)omega * (float)sin(alpha) * cos(beta), (*partes[0]).py+(float)omega * (float)sin(beta), (float)omega * cos(alpha) * cos(beta));

	view = glm::mat4();
	view = glm::lookAt(posicionView, glm::vec3((*partes[0]).px, (*partes[0]).py, (*partes[0]).pz), glm::vec3(0, 1, 0));

	projection = glm::mat4();
	projection = glm::perspective(glm::radians(60.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, .1f, 1000.0f);

	glUniform3f(viewPosLoc, posicionView.x, posicionView.y, posicionView.z);
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
}
void camaraTerceraP(void) {
	glm::mat4 view;
	glm::mat4 projection;
	unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
	unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");

	unsigned int viewPosLoc = glGetUniformLocation(shaderProgram, "viewPos");
	 
	glm::vec3 posicionView = glm::vec3((*partes[0]).px + (-3.0 * (*partes[0]).sx * -sin((*partes[0]).angulo_trans2 * GradosToRadianes)), (*partes[0]).py + (-3.0 * (*partes[0]).sx * cos((*partes[0]).angulo_trans2 * GradosToRadianes)), 2.5 * (*partes[0]).sz);

	view = glm::mat4();
	view = glm::lookAt(posicionView,
					   glm::vec3((*partes[0]).px + (2.0*(*partes[0]).sx * -sin((*partes[0]).angulo_trans2 * GradosToRadianes)), (*partes[0]).py + (2.0* (*partes[0]).sx * cos((*partes[0]).angulo_trans2 * GradosToRadianes)), (*partes[0]).pz),
					   glm::vec3(0, 0, 1));

	projection = glm::mat4();
	projection = glm::perspective(glm::radians(60.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, .1f, 1000.0f);

	glUniform3f(viewPosLoc, posicionView.x, posicionView.y, posicionView.z);
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}
void camaraPrimeraP(void) {
	glm::mat4 view;
	glm::mat4 projection;
	unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
	unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");

	unsigned int viewPosLoc = glGetUniformLocation(shaderProgram, "viewPos");

	glm::vec3 posicionView = glm::vec3(tronco.px + (cabeza.sx * -sin(tronco.angulo_trans2 * GradosToRadianes)), tronco.py + ( cabeza.sy * cos(tronco.angulo_trans2 * GradosToRadianes)), tronco.pz+cabeza.pz);

	view = glm::mat4();
	view = glm::lookAt(posicionView,
						glm::vec3(tronco.px + (2.0 * tronco.sx * -sin(tronco.angulo_trans2 * GradosToRadianes)), tronco.py + (2.0 * tronco.sx * cos(tronco.angulo_trans2 * GradosToRadianes)), tronco.pz + cabeza.pz),
						glm::vec3(0, 0, 1));

	projection = glm::mat4();
	projection = glm::perspective(glm::radians(80.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, .1f, 1000.0f);

	glUniform3f(viewPosLoc, posicionView.x, posicionView.y, posicionView.z);
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

}

void Display();

void cargaCubos() {
	for (int i = 0; i < numCubos; i++) {
		objeto cubo = { coordenadasCubos[i][0] / Escala, coordenadasCubos[i][1] / Escala, 1.0f / Escala, 0.0f, 0.0f, 1.0f / Escala, 1.0f / Escala, 2.0f / Escala, glm::vec3(1.0f, 1.0f, 1.0f), VAO_cubo, VAO_cubo_vertex};
		cubos[i] = cubo;
	}
}

void inicializarObjetos() {

	tronco.listarender = VAO_cubo;
	tronco.num_vertex = VAO_cubo_vertex;
	partes[0] = &tronco;

	piernaI.listarender = VAO_cubo;
	piernaI.num_vertex = VAO_cubo_vertex;
	partes[1] = &piernaI;

	piernaD.listarender = VAO_cubo;
	piernaD.num_vertex = VAO_cubo_vertex;
	partes[2] = &piernaD;

	brazoI.listarender = VAO_cubo;
	brazoI.num_vertex = VAO_cubo_vertex;
	partes[3] = &brazoI;

	brazoD.listarender = VAO_cubo;
	brazoD.num_vertex = VAO_cubo_vertex;
	partes[4] = &brazoD;

	linterna.listarender = VAO_cubo;
	linterna.num_vertex = VAO_cubo_vertex;
	partes[5] = &linterna;

	cabeza.listarender = VAO_esfera;
	cabeza.num_vertex = VAO_esfera_vertex;
	partes[6] = &cabeza;

	troncoM1.listarender = VAO_esfera;
	troncoM1.num_vertex = VAO_esfera_vertex;
	partesM1[0] = &troncoM1;

	brazoIM1.listarender = VAO_cubo;
	brazoIM1.num_vertex = VAO_cubo_vertex;
	partesM1[1] = &brazoIM1;

	brazoDM1.listarender = VAO_cubo;
	brazoDM1.num_vertex = VAO_cubo_vertex;
	partesM1[2] = &brazoDM1;

	cabezaM1.listarender = VAO_esfera;
	cabezaM1.num_vertex = VAO_esfera_vertex;
	partesM1[3] = &cabezaM1;

	troncoM2.listarender = VAO_esfera;
	troncoM2.num_vertex = VAO_esfera_vertex;
	partesM2[0] = &troncoM2;

	brazoIM2.listarender = VAO_cubo;
	brazoIM2.num_vertex = VAO_cubo_vertex;
	partesM2[1] = &brazoIM2;

	brazoDM2.listarender = VAO_cubo;
	brazoDM2.num_vertex = VAO_cubo_vertex;
	partesM2[2] = &brazoDM2;

	cabezaM2.listarender = VAO_esfera;
	cabezaM2.num_vertex = VAO_esfera_vertex;
	partesM2[3] = &cabezaM2;

	cargaCubos();
}

int carga_textura(char* fichero) {
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(fichero, &width, &height, &nrChannels, 0);

	if (data) {
		if (nrChannels == 3)	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	return texture;
}
void carga_texturas() {

	texturaSuelo = carga_textura((char*)ficheroSuelo);
	texturaPared = carga_textura((char*)ficheroParedes);
	for (int i = 0; i < numeroPartes; i++) {
		(*partes[i]).textura = carga_textura((char*)(*partes[i]).fichero_textura);
	}
	for (int i = 0; i < numeroPartesM; i++) {
		(*partesM1[i]).textura = carga_textura((char*)(*partesM1[i]).fichero_textura);
	}
	for (int i = 0; i < numeroPartesM; i++) {
		(*partesM2[i]).textura = carga_textura((char*)(*partesM2[i]).fichero_textura);
	}
	texturaVictoria = carga_textura((char*)ficheroVictoria);
	texturaDerrota = carga_textura((char*)ficheroDerrota);
	texturaIntro = carga_textura((char*)ficheroIntro);
	texturaControles = carga_textura((char*)ficheroControles);

}

double lasatTime = glfwGetTime();
double currentTime;
double lapsoTime;
int nbFrames = 0;

void tiempo() {
	static float unSegundo = 0;
	static float tiempoM = 0;
	currentTime = glfwGetTime();
	nbFrames++;
	lapsoTime = currentTime - lasatTime;
	unSegundo = unSegundo + (float)lapsoTime;

	if (unSegundo >= 1.0) {
		printf("%f frame/s\n", double(nbFrames));
		nbFrames = 0;
		unSegundo = 0;
	}
	lasatTime = currentTime;
}

void movimiento_P() {
	int disponible = 0;


	float sigPosx = (*partes[0]).px + velocidad * -sin((*partes[0]).angulo_trans2 * GradosToRadianes) * (float)lapsoTime;
	float sigPosy = (*partes[0]).py + velocidad * cos((*partes[0]).angulo_trans2 * GradosToRadianes) * (float)lapsoTime;

	for (int i = 0; i < numCubos; i++) {

		if ((cubos[i].px - cubos[i].sx / 2.0 < sigPosx + (*partes[0]).sx*1.5) && (sigPosx - (*partes[0]).sx*1.5 < cubos[i].px + cubos[i].sx / 2.0) &&
			(cubos[i].py - cubos[i].sy / 2.0 < sigPosy + (*partes[0]).sx * 1.5) && (sigPosy - (*partes[0]).sx * 1.5 < cubos[i].py + cubos[i].sy / 2.0)) {
	
			disponible = 1;

			if ((*partes[0]).px < (cubos[i].px - cubos[i].sx / 2.0f)) {

				(*partes[0]).px -= 0.0035;
			}
			else if ((*partes[0]).px > (cubos[i].px + cubos[i].sx / 2.0f)) {

				(*partes[0]).px += 0.0035;
			}
			else (*partes[0]).px += velocidad * -sin((*partes[0]).angulo_trans2 * GradosToRadianes) * (float)lapsoTime;

			if ((*partes[0]).py > (cubos[i].py + cubos[i].sy / 2.0f)) {
			
				(*partes[0]).py += 0.0035;
			}
			else if ((*partes[0]).py < (cubos[i].py - cubos[i].sy / 2.0f)) {
				(*partes[0]).py -= 0.0035;
			}
			else (*partes[0]).py += velocidad * cos((*partes[0]).angulo_trans2 * GradosToRadianes) * (float)lapsoTime;

			if (((cubos[i].px - cubos[i].sx / 2.0f) >= (*partes[0]).px) &&
				((cubos[i].py - cubos[i].sy / 2.0f) >= (*partes[0]).py)) {
				(*partes[0]).px -= 0.0035;
				(*partes[0]).py -= 0.0035;
			}
			else if (((cubos[i].px + cubos[i].sx / 2.0f) <= (*partes[0]).px) &&
				((cubos[i].py - cubos[i].sy / 2.0f) >= (*partes[0]).py)) {

				(*partes[0]).px += 0.0035;
				(*partes[0]).py -= 0.0035;
			}
			else if (((cubos[i].px + cubos[i].sx / 2.0f) <= (*partes[0]).px) &&
				((cubos[i].py + cubos[i].sy / 2.0f) <= (*partes[0]).py)) {
				(*partes[0]).px += 0.0035;
				(*partes[0]).py += 0.0035;

			}
			else if (((cubos[i].px - cubos[i].sx / 2.0f) >= (*partes[0]).px) &&
				((cubos[i].py + cubos[i].sy / 2.0f) <= (*partes[0]).py)) {

				(*partes[0]).px -= 0.0035;
				(*partes[0]).py += 0.0035;
			}
			else {
				sigPosx = (*partes[0]).px + velocidad * -sin((*partes[0]).angulo_trans2 * GradosToRadianes) *(float) lapsoTime;
				sigPosy = (*partes[0]).py + velocidad * cos((*partes[0]).angulo_trans2 * GradosToRadianes) * (float)lapsoTime;
			}

			if ((*partes[0]).angulo_trans2 >= 180.0)	(*partes[0]).angulo_trans2 = -180;
			if ((*partes[0]).angulo_trans2 < -180.0)	(*partes[0]).angulo_trans2 = 180;
			
		}
	}

	if (disponible == 0) {

		(*partes[0]).px = (*partes[0]).px + velocidad * -sin((*partes[0]).angulo_trans2 * GradosToRadianes) * (float)lapsoTime;
		(*partes[0]).py = (*partes[0]).py + velocidad * cos((*partes[0]).angulo_trans2 * GradosToRadianes) * (float)lapsoTime;
		if (((*partesM1[0]).px - (*partesM1[0]).sx / 2.0 < (*partes[0]).px + (*partes[0]).sx * 1.5) && ((*partes[0]).px - (*partes[0]).sx * 1.5 < (*partesM1[0]).px + (*partesM1[0]).sx / 2.0) &&
			((*partesM1[0]).py - (*partesM1[0]).sy / 2.0 < sigPosy + (*partes[0]).sx * 1.5) && (sigPosy - (*partes[0]).sx * 1.5 < (*partesM1[0]).py + (*partesM1[0]).sy / 2.0)||
			((*partesM2[0]).px - (*partesM2[0]).sx / 2.0 < (*partes[0]).px + (*partes[0]).sx * 1.5) && ((*partes[0]).px - (*partes[0]).sx * 1.5 < (*partesM2[0]).px + (*partesM2[0]).sx / 2.0) &&
			((*partesM2[0]).py - (*partesM2[0]).sy / 2.0 < sigPosy + (*partes[0]).sx * 1.5) && (sigPosy - (*partes[0]).sx * 1.5 < (*partesM2[0]).py + (*partesM2[0]).sy / 2.0)) {

			(*partes[0]).px = 13.5/Escala;
			(*partes[0]).py = -13.75/Escala;
			(*partes[0]).angulo_trans2 = 0.0;
			velocidad = 0;
		}
	}
}
void movimiento_M(objeto *m) {
	int disponible = 0;
	int giroM = 0;
	int cambio = 0;
	float velocidadM = 1.1;
	float sigPosx = m[0].px + velocidadM * -sin(m[0].angulo_trans2 * GradosToRadianes) * (float)lapsoTime;
	float sigPosy = m[0].py + velocidadM * cos(m[0].angulo_trans2 * GradosToRadianes) * (float)lapsoTime;
	
	for (int i = 0; i < numCubos; i++) {

		if ((cubos[i].px - cubos[i].sx / 2.0 < (sigPosx + 0.1)) && ((sigPosx - 0.1) < cubos[i].px + cubos[i].sx / 2.0) &&
			(cubos[i].py - cubos[i].sy / 2.0 < (sigPosy + 0.1)) && ((sigPosy - 0.1) < cubos[i].py + cubos[i].sy / 2.0)) {
			if (giroM == 0) {
				giroM = 1;
			}
			disponible = 1;

			if ((m[0].py >= (cubos[i].py - cubos[i].sy / 2.0f)) && (m[0].py <= (cubos[i].py + cubos[i].sy / 2.0f))) {

				if (m[0].px <= (cubos[i].px - (cubos[i].sx / 2.0f))) {
					m[0].px -= 0.03;
				}
				else if (m[0].px >= (cubos[i].px + (cubos[i].sx / 2.0f))) {
					m[0].px += 0.03;
				}
			}
			if ((m[0].px >= (cubos[i].px - (cubos[i].sx / 2.0f))) && (m[0].px <= (cubos[i].px + (cubos[i].sx / 2.0f)))) {

				if (m[0].py >= (cubos[i].py + (cubos[i].sy / 2.0f))) {
					m[0].py += 0.03;
				}
				else {
					m[0].py -= 0.03;
				}
			}

			if (rand() % 2 == 1) {
				cambio = 1;
				if (m[0].angulo_trans2 == 180.0f) {
					m[0].angulo_trans2 = 90.0f;
				}
				else if (m[0].angulo_trans2 == 0.0f) {
					m[0].angulo_trans2 = -90.0f;
				}
				else if (m[0].angulo_trans2 == 90.0f) {
					m[0].angulo_trans2 = 0.0f;
				}
				else if (m[0].angulo_trans2 == -90.0f) {
					m[0].angulo_trans2 = 180.0f;
				}
			}
			else {
				cambio = 0;
				if (m[0].angulo_trans2 == 180.0f) {
					m[0].angulo_trans2 = -90.0f;
				}
				else if (m[0].angulo_trans2 == 0.0f) {
					m[0].angulo_trans2 = 90.0f;
				}
				else if (m[0].angulo_trans2 == 90.0f) {
					m[0].angulo_trans2 = 180.0f;
				}
				else if (m[0].angulo_trans2 == -90.0f) {
					m[0].angulo_trans2 = 0.0f;
				}
			}

			break;


		}
	}

	if (disponible == 0) {
		if ((12.0f/Escala - cubos[0].sx / 2.0 <= (sigPosx + 0.4)) &&
			(11.0f/Escala - cubos[0].sy / 2.0 > (sigPosy - 0.4)) && ((sigPosy + 0.4) > 8.0f/Escala + cubos[0].sy / 2.0)){
			m[0].angulo_trans2 = 90.0f;
		}
		m[0].px = m[0].px + velocidadM * -sin(m[0].angulo_trans2 * GradosToRadianes) * (float)lapsoTime;
		m[0].py = m[0].py + velocidadM * cos(m[0].angulo_trans2 * GradosToRadianes) * (float)lapsoTime;

		if (giroM == 1) {
			int giro = 0;
			float anguloNuevo;
			if (rand() % 2 == 0) {
				if (m[0].angulo_trans2 == 180) anguloNuevo = -90.0f;
				else anguloNuevo = m[0].angulo_trans2 + 90.0f;
			}
			else {
				if (m[0].angulo_trans2 == 180) anguloNuevo = 90.0f;
				else anguloNuevo = m[0].angulo_trans2 - 90.0f;
				if (anguloNuevo == -180.0f) anguloNuevo = 180.0f;
			}
			
			sigPosx = m[0].px + velocidadM * -sin(anguloNuevo * GradosToRadianes) * (float)lapsoTime;
			sigPosy = m[0].py + velocidadM * cos(anguloNuevo * GradosToRadianes) * (float)lapsoTime;

			for (int i = 0; i < numCubos; i++) {

				if ((cubos[i].px - cubos[i].sx / 2.0 <= (sigPosx +0.4)) && ((sigPosx -0.4) <= cubos[i].px + cubos[i].sx / 2.0) &&
					(cubos[i].py - cubos[i].sy / 2.0 <= (sigPosy +0.4)) && ((sigPosy - 0.4) <= cubos[i].py + cubos[i].sy / 2.0)) {
					giro = 1;
				}
			}
			if (giro == 0) {
				m[0].angulo_trans2 = anguloNuevo;
				giroM = 0;
			}
		}
	}
}
void movimiento() {

	movimiento_P();
	movimiento_M(*partesM1);
	movimiento_M(*partesM2);

	if ((*partes[0]).angulo_trans2 > 180.0)	(*partes[0]).angulo_trans2 = -180;
	if ((*partes[0]).angulo_trans2 < -180.0)	(*partes[0]).angulo_trans2 = 180;
}
int sentidoPiernas = 1;
void movimientoPiernas(){
	
	if (piernaD.angulo_trans >= 20) sentidoPiernas = -1;
	if (piernaD.angulo_trans <= -20) sentidoPiernas = 1;

	piernaD.angulo_trans += 1.0f*sentidoPiernas* abs(velocidad) /2.0f;
	piernaD.py += 0.002f*sentidoPiernas* abs(velocidad) /2.0f;

	brazoI.angulo_trans += 1.0f * sentidoPiernas * abs(velocidad) / 2.0f;
	brazoI.py += 0.003f * sentidoPiernas * abs(velocidad) / 2.0f;

	piernaI.angulo_trans -= 1.0f * sentidoPiernas * abs(velocidad) / 2.0f;
	piernaI.py -= 0.002f * sentidoPiernas * abs(velocidad) / 2.0f;

}


void Idle(void) {
	/*fAngulo += 0.005f;
	if (fAngulo > 6.28) fAngulo = 0.0f;
	fAngulo2 += 0.007f;
	if (fAngulo > 6.28) fAngulo = 0.0f;
	Display();*/
}


void ilumina(glm::mat4 transform) {
	//Declaracion de la variable uniforme para la luz ambiente
	unsigned int lightColorLoc = glGetUniformLocation(shaderProgram, "lightColor");
	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);

	//Declaracion de la variable uniforme para la posicion de la luz
	glm::vec4 posicionLuz = transform * glm::vec4(linterna.px, linterna.py + linterna.sy / 2.0, linterna.pz, 1.0f);
	unsigned int lightPosLoc = glGetUniformLocation(shaderProgram, "lightPos");
	glUniform3f(lightPosLoc, posicionLuz.x, posicionLuz.y, posicionLuz.z);

	//Declaracion de una variable uniforme para la direccion hacia donde se dirige la luz
	glm::vec4 finalLuz = transform * glm::vec4(0.0, 3.0, 0.0, 1.0f);
	unsigned int lightEndLoc = glGetUniformLocation(shaderProgram, "lightEnd");
	glUniform3f(lightEndLoc, finalLuz.x, finalLuz.y, finalLuz.z);
}

void dibuja_mensaje(int textura, float i, float j) {
	glm::mat4 transform;
	glm::mat4 stack;
	float EscalaM = 1;
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	unsigned int transformLoc = glGetUniformLocation(shaderProgram, "model");
	unsigned int colorLoc = glGetUniformLocation(shaderProgram, "objectColor");

	transform = glm::mat4();
	
	transform = glm::translate(transform, glm::vec3(i / Escala, j / Escala, 1/(EscalaM *2)));
	if(textura == texturaIntro || textura == texturaDerrota) transform = glm::rotate(transform, (float)(90.0 * GradosToRadianes), glm::vec3(1.0f, .0f, .0f));
	else transform = glm::rotate(transform, (float)(-90.0 * GradosToRadianes), glm::vec3(.0f, 1.0f, .0f));
	transform = glm::scale(transform, glm::vec3((1.0f / EscalaM), (1.0f / EscalaM), (1.0f / EscalaM)));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glUniform3f(colorLoc, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, textura);

	glBindVertexArray(VAO_cuadrado);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	
}
void dibuja_mensajes() {
	dibuja_mensaje(texturaVictoria, 14.0, 9.5);
	dibuja_mensaje(texturaDerrota, 13.5, -12.52);
	dibuja_mensaje(texturaIntro, 13.5, -9.52);
	dibuja_mensaje(texturaControles, 14.48, -10.5);
}

void dibuja_suelo() {

	glm::mat4 transform;
	glm::mat4 stack;
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	unsigned int transformLoc = glGetUniformLocation(shaderProgram, "model");
	unsigned int colorLoc = glGetUniformLocation(shaderProgram, "objectColor");
	
	for (float i = -12.0f; i <= 37.0f; i ++)
		for (float j = -15.0f; j <= 11.0f; j ++) {
			transform = glm::mat4();
			transform = glm::translate(transform, glm::vec3(i/Escala, j/Escala, -0.0001));
			transform = glm::scale(transform, glm::vec3((1.0f / Escala), (1.0f / Escala), (1.0f / Escala)));

			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glUniform3f(colorLoc, 1.0f, 1.0f, 1.0f);
			glBindTexture(GL_TEXTURE_2D, texturaSuelo);
		
			glBindVertexArray(VAO_cuadrado);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
}

void dibujaCubo(objeto o) {
	glm::mat4 transform;
	transform = glm::mat4();
	unsigned int transformLoc = glGetUniformLocation(shaderProgram, "model");
	unsigned int colorLoc = glGetUniformLocation(shaderProgram, "objectColor");

	transform = glm::translate(transform, glm::vec3(o.px, o.py, o.pz));
	transform = glm::scale(transform, glm::vec3(o.sx, o.sy, o.sz));

	glUniform3f(colorLoc, o.color.x, o.color.y, o.color.z);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindTexture(GL_TEXTURE_2D, texturaPared);
	glBindVertexArray(o.listarender);
	glDrawArrays(GL_TRIANGLES, 0, o.num_vertex);

}
void dibujaCubos() {
	for (int i = 0; i < numCubos; i++) {
		dibujaCubo(cubos[i]);
	}
}


glm::mat4 dibujaParte(glm::mat4 stack, objeto* o) {
	glm::mat4 resultante;

	unsigned int transformLoc = glGetUniformLocation(shaderProgram, "model");
	unsigned int colorLoc = glGetUniformLocation(shaderProgram, "objectColor");

	stack = glm::translate(stack, glm::vec3((*o).px, (*o).py, (*o).pz));
	
	stack = glm::rotate(stack, (float)((*o).angulo_trans2 * GradosToRadianes), glm::vec3(.0f, .0f, 1.0f));
	stack = glm::rotate(stack, (float)((*o).angulo_trans * GradosToRadianes), glm::vec3(1.0f, .0f, .0f));

	resultante = stack;
	stack = glm::scale(stack, glm::vec3((*o).sx, (*o).sy, (*o).sz));
	if (o == partesM2[0] || o == partesM1[0]) {
		stack = glm::rotate(stack, (float)(90.0 * GradosToRadianes), glm::vec3(1.0f, .0f, .0f));
	}

	glUniform3f(colorLoc, (*o).color.x, (*o).color.y, (*o).color.z);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(stack));
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindTexture(GL_TEXTURE_2D, (*o).textura);
	glBindVertexArray((*o).listarender);
	glDrawArrays(GL_TRIANGLES, 0, (*o).num_vertex);
	
	return resultante;

}
void dibuja_P() {
	glm::mat4 transform, aux;

	transform = glm::mat4();
	transform = dibujaParte(transform, partes[0]);
	for (int i = 1; i < numeroPartes; i++) {
		dibujaParte(transform, partes[i]);
	}
	ilumina(transform);

}
void dibuja_M() {
	glm::mat4 transform, aux;

	transform = glm::mat4();
	transform = dibujaParte(transform, partesM1[0]);
	for (int i = 1; i < numeroPartesM; i++) {
		dibujaParte(transform, partesM1[i]);
	}
	transform = glm::mat4();
	transform = dibujaParte(transform, partesM2[0]);
	for (int i = 1; i < numeroPartesM; i++) {
		dibujaParte(transform, partesM2[i]);
	}
}

void Display() {
	
	glClearColor(.0f, .0f, .0f, 1.0f); //Borro el Buffer the la ventana
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	switch (flagCamara) {
	case 2: camaraExterna();
		break;
	case 3: camaraTerceraP();
		break;
	case 1: camaraPrimeraP();
		break;
	}

	dibuja_suelo();
	dibujaCubos();
	dibuja_P();
	dibuja_M();
	
	dibuja_mensajes();

	glBindVertexArray(0); // unbind 
}

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//Creo la ventana

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "El laberinto del Minotauro", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Fallo Crear Ventana" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: 
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	openGlInit();

	shaderProgram = setShaders("shaderPres.vert", "shaderPres.frag");

	my_cuadrado();
	my_esfera();
	my_cubo();
	
	inicializarObjetos();
	
	
	carga_texturas();
	glUseProgram(shaderProgram); // lo muevo para aqui por no 
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		
		processInput(window);
		Display();
		Idle();
		tiempo();
		movimiento();
		movimientoPiernas();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
			}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);


	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) flagCamara = 1;
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) flagCamara = 2;
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) flagCamara = 3;
	if (flagCamara == 2) {
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			beta += .001f;
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			beta -= .001f;
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			alpha += .001f;
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			alpha -= .001f;

		if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS && omega < 100)
			omega += .1f;
		if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS && omega > 1)
			omega -= .1f;
	}


	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) velocidad = 1.0f;
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) velocidad = -1.0f;
	else velocidad = .0f;
	
	
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)	(*partes[0]).angulo_trans2 += .55f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)	(*partes[0]).angulo_trans2 -= .55f;
	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS){
		(*partes[0]).px = 0.0f;
		(*partes[0]).py = 0.0f;
		(*partes[0]).angulo_trans2 = 0.0f;
	}
		

	

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
	SCR_HEIGHT = height;
	SCR_WIDTH = width;
}
