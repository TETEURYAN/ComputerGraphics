//  Transformacoes Geométricas
//
//  Auth Matheus Ryan
//  Copyright (c) 2024 Universidade Federal de Alagoas - UFAL. All rights reserved.

#include <GL/freeglut.h>
#include <GL/glut.h>

float angle = 0.0f;
float rotationSpeed = 1.0f;
float initx = 250.0f;
float inity = 250.0f;
bool isrotate = true;

void init (void){
    /* selecionar cor de fundo (preto) */
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glMatrixMode (GL_PROJECTION); //Projecao 2D
    gluOrtho2D (0.0, 600.0, 0.0, 400.0); //Definindo os limites da Porta de Visao (ViewPort)
        
}

/*Checa a situação do Ângulo*/
void checkAngle(){
    if(isrotate){// Caso esteja disponível para girar, gire
        angle += rotationSpeed + 3.14f;
    }
    if(angle > 360){//VOlta para a origem quando ultrapassa o valor de giro
        angle -= 360;
    }
}

void turnRotate(){
    isrotate = (isrotate) ? false : true;
}

void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); 
}

/*Método para pegar a entrada do teclado*/
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'l':  /*Aumenta a velocidade*/
            rotationSpeed += 1.0f;
        break;

        case 'j': /*Diminui a velocidade*/
            if (rotationSpeed > 0.0f) rotationSpeed -= 1.0f;
        break;

        case 13: /*Paralisa ou continua o giro*/
            turnRotate();
        break;  
    }
}

void display(void)
{
    /* Limpar todos os pixels  */
    glClear (GL_COLOR_BUFFER_BIT);

    /*Armazenar as coordenadas atuais na matriz*/
    glPushMatrix();

    /*Desenha o palito*/
    glColor3f (1.0, 1.0, .0);
    glBegin(GL_POLYGON);
        glVertex3f (249.0f, 250.0f, -1.0f);
        glVertex3f (251.0f, 250.0f, -1.0f);
        glVertex3f (249.0f, 100.0f, -1.0f);
        glVertex3f (251.0f, 100.0f, -1.0f);
    glEnd();
        
    glTranslatef(initx, inity, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-initx, -inity, 0.0f);

    /* Desenhar um polígono branco  */
    glColor3f (1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);
        glVertex2f (250.0f, 250.0f);
        glVertex2f (230.0f, 200.0f);
        glVertex2f (270.0f, 200.0f);
    glEnd();
        
    /* Desenhar um polígono vermelho */
    glColor3f (1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f (250.0f, 250.0f);
        glVertex2f (300.0f, 230.0f);
        glVertex2f (300.0f, 270.0f);
    glEnd();
        
    /* Desenhar um polígono verde */
    glColor3f (0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f (250.0f, 250.0f);
        glVertex2f (230.0f, 300.0f);
        glVertex2f (270.0f, 300.0f);
    glEnd();
        
    /* Desenhar um polígono vermelho */
    glColor3f (0.0, 0.0, 1.0);
    glBegin(GL_TRIANGLES);
        glVertex2f (250.0f, 250.0f);
        glVertex2f (200.0f, 270.0f);
        glVertex2f (200.0f, 230.0f);
    glEnd();

    /*Função para atualizar o Ângulo conforme gira*/
    checkAngle();

    /* Não esperar! */
    glFlush ();
    glPopMatrix();
    
    // Trocar os buffers
    glutSwapBuffers();
}



int main(int argc, char** argv) {
        
    glutInit(&argc, argv);
        
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (500, 400);
    glutInitWindowPosition (200, 200);
    glutCreateWindow ("Flor de Abril");
    glutKeyboardFunc(keyboard);
        
    init();
    
    glutDisplayFunc(display);
    glutTimerFunc(16, timer, 0);
    glutMainLoop();
        
    return 0;
        
}
