#include<GL/glut.h>
#include <math.h>
#include<GL/glu.h>
#include<GL/glext.h>
#include<GL/gl.h>
#define PI 3.1415926535897932384626433832795
static int mercuryRadius = 200;
static int venusRadius = mercuryRadius + 150;


static float  mercury = 360.0 / 87.97;
static float  venus = 360.0 / 224.70;


static float  mercuryAngle = 0.0f;
static float  venusAngle    = 0.0f;



float eyeX = 0.0f;
float eyeY = 800.0f;
float eyeZ = 1700.0f;


GLfloat mat_ambient [] = {0.7 , 0.7 , 0.7 , 1.0} ;
GLfloat mat_specular [] = {0.0 , 0.0 , 0.0 , 0.0} ;
GLfloat mat_shininess [] = {50.0};
GLfloat light_position [] = {1.0 , 1.0 ,1.0 , 1.0} ;
GLfloat model_ambient [] = {1.0, 1.0 , 1.0 ,1.0} ;


void setupMaterials()
{
  glMaterialfv (GL_FRONT, GL_AMBIENT , mat_ambient)  ;
  glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular) ;
  glMaterialfv  (GL_FRONT, GL_SHININESS, mat_shininess) ;
  glLightfv (GL_LIGHT0, GL_POSITION, light_position) ;
  glLightModelfv (GL_LIGHT_MODEL_AMBIENT, model_ambient) ;
}

void changeColour(GLfloat r, GLfloat g , GLfloat b , GLfloat A) {
 model_ambient [0] = r;
 model_ambient [1] = g;
 model_ambient [2] = b;
 model_ambient [3] = A;
 glLightModelfv(GL_LIGHT_MODEL_AMBIENT , model_ambient) ;
}


void changeSize(int w, int h)
{
  if (h == 0)   h = 1;
  float ratio = 1.0 * w / h ;

  glMatrixMode(GL_PROJECTION)  ;
  glLoadIdentity() ;

  glViewport( 0 , 0 , w , h) ;
  gluPerspective (45, ratio , 1 , 5000 ) ;

 glMatrixMode(GL_MODELVIEW) ;
}

float angle = 0.0f;
float j = 0.0f;


void renderScence(void){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt( 0.0f, eyeY, eyeZ,
               0.0f, 0.0f, 0.0f,
               0.0f, 1.0f, 0.0f);

    changeColour(1.0, 1.0, 1.0, 1.0);

glBegin(GL_POINTS);
for(double i = 0; i< 2 * PI; i += PI / mercuryRadius) // change this value
    glVertex3f(cos(i) * mercuryRadius, 1.0, sin(i) * mercuryRadius);
glEnd();

glBegin(GL_POINTS);
for(double i = 0; i < 2 * PI; i += PI /venusRadius) // change this value
    glVertex3f(cos(i) *  venusRadius, 1.0, sin(i) * venusRadius);
glEnd();


//Mercury
glPushMatrix();
glRotatef(mercuryAngle, 0.0f,1.0f, 0.0f);
glTranslatef(mercuryRadius, 0.0, 0.0);
changeColour(66/255.0, 61/255.0, 57/255.0, 0.0);
GLUquadric *Mercury;
Mercury = gluNewQuadric();
gluSphere(Mercury, 10, 100, 100);
glPopMatrix();


//Venus
glPushMatrix();
glRotatef(venusAngle, 0.0f,1.0f, 0.0f);
glTranslatef(venusRadius, 0.0, 0.0);
changeColour(140.0/255.0, 70.0/255.0, 0.0, 0.0);
GLUquadric *Venus;
Venus = gluNewQuadric();
gluSphere(Venus, 25.8, 100, 100);
glPopMatrix();


angle+= 0.2f;
mercuryAngle += mercury / 10;
venusAngle += venus/ 10;

//if (angle == 360) angle =0;
glutSwapBuffers();
}

void mouse (int button, int state, int x, int y)
{
switch (button) {
    case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
          glutIdleFunc(renderScence);
          break;
    case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN)
            glutIdleFunc(NULL);
         break;
    }
}

void keyboard(unsigned char key, int xx, int yy) {
     switch(key){
     case 27:
         exit(0);
         break;

    }
}

void keyboardSpecial(int key, int xx, int yy)
{
    switch(key){
    case GLUT_KEY_UP:
         eyeY -= 10.0f;
         eyeZ -= 10.0f;
         break;
     case GLUT_KEY_DOWN:
        eyeY += 10.0f;
        eyeZ += 10.0f;
        break;
    }
}


void init (void){
     glClearColor(0.0, 0.0, 0.0, 1.0);
     setupMaterials();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glEnable(GL_DEPTH_TEST);
     glEnable(GL_CULL_FACE);
     glFrontFace(GL_CCW);
     glShadeModel(GL_SMOOTH);
}

int main (int argc, char * argv[]){

    //init GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1000, 500);
    //glOrtho(-1000, 1000, -1000, 1000, -1000, 1000);
    glutCreateWindow("Solar 3D Model");
    init();

    // register callback
    glutDisplayFunc(renderScence);
    glutReshapeFunc(changeSize);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboardSpecial);

    //enter GLUT event processing cycle
    glutMainLoop();
    return 0;
     }
