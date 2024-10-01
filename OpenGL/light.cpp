#include <GL/glew.h>
#include <GL/freeglut.h>

float angle = 0.0;

// Definindo a luz
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 }; // Posição da luz
GLfloat diffuse_light[] = { 1.0, 1.0, 1.0, 1.0 };  // Cor da luz difusa
GLfloat ambient_light[] = { 0.2, 0.2, 0.2, 1.0 };   // Cor da luz ambiente

void init() {
    glEnable(GL_LIGHTING);          // Habilita a iluminação
    glEnable(GL_LIGHT0);           // Habilita a luz 0
    glLightfv(GL_LIGHT0, GL_POSITION, light_position); // Define a posição da luz
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);   // Define a cor da luz difusa
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);    // Define a cor da luz ambiente
    
    glEnable(GL_DEPTH_TEST);       // Habilita o teste de profundidade
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Movendo a câmera
    gluLookAt(0.0, 0.0, 5.0,   // Posição da câmera
              0.0, 0.0, 0.0,   // Para onde a câmera olha
              0.0, 1.0, 0.0);  // Para cima

    glRotatef(angle, 1.0, 1.0, 0.0); // Rotaciona o cubo

    // Desenha um cubo
    glutSolidCube(1.0);
    
    glutSwapBuffers();
}

void timer(int) {
    angle += 0.5; // Incrementa o ângulo de rotação
    if (angle > 360) angle -= 360;
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // Aproximadamente 60 FPS
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Iluminação com OpenGL");
    
    glewInit(); // Inicializa o GLEW
    init();
    
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    
    return 0;
}
