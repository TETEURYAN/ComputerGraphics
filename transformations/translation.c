
//  Transformação de Translação
//
//  Auth Matheus Ryan
//  Copyright (c) 2024 Universidade Federal de Alagoas - UFAL. All rights reserved.

#include <GL/freeglut.h>
#include <GL/glut.h>

float speed = 0.5f;
float initx = 0.0f;
float inity = 0.0f;
bool isrotate = true;

void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); 
}

/*Método para pegar a entrada do teclado*/
void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            inity += speed;
            break;
        case GLUT_KEY_DOWN:
            inity -= speed;
            break;
        case GLUT_KEY_LEFT:
            initx -= speed;
            break;
        case GLUT_KEY_RIGHT:
            initx += speed;
            break;
    }
    glutPostRedisplay(); // Solicita um redesenho da tela
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Limpa a tela

    glPushMatrix();
    // Desenhando um quadrado vermelho
    glColor3f(1.0, 0.0, 0.0); // Define a cor como vermelho
    glBegin(GL_QUADS);
        glVertex2f(initx-0.5f, inity-0.5f); // Canto inferior esquerdo
        glVertex2f(initx+0.5f, inity-0.5f);  // Canto inferior direito
        glVertex2f(initx+0.5f, inity+0.5f);   // Canto superior direito
        glVertex2f(initx-0.5f, inity+0.5f);  // Canto superior esquerdo
    glEnd();
    
    
    glFlush(); // Força a renderização
    
    glPopMatrix();
    
    // Trocar os buffers
    glutSwapBuffers();
}



int main(int argc, char** argv) {
        
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(1080, 720);
    glutCreateWindow("Translação");
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutTimerFunc(16, timer, 0);
    glutMainLoop();
        
    return 0;
        
}