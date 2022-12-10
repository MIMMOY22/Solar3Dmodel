
#include<GL/glut.h>
#include <math.h>
#include<GL/glu.h>
#include<GL/glext.h>
#include<GL/gl.h>
#define PI 3.1415926535897932384626433832795

static int mercuryRadius = 200;
static int venusRadius = mercuryRadius + 150;
static int earthRadius = venusRadius + 150;
static int marsRadius =  earthRadius  + 150;
static int jupiterRadius  = marsRadius  + 200;
static int saturnRadius  = jupiterRadius + 200;
static int uranusRadius =saturnRadius + 150;
static int neptuneRadius  = uranusRadius  + 150;

static float  uranus = 360.0 / 306871.5;
static float   neptune = 360.0 / 601900.3;

static float   uranusAngle   = 0.0f;
static float   neptuneAngle  = 0.0f;


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
for(double i = 0; i < 2 * PI; i += PI /uranusRadius) // change this value
    glVertex3f(cos(i) *  uranusRadius, 1.0, sin(i) * uranusRadius);
glEnd();

glBegin(GL_POINTS);
for(double i = 0; i < 2 * PI; i += PI /neptuneRadius) // change this value
    glVertex3f(cos(i) *  neptuneRadius, 1.0, sin(i) * neptuneRadius);
glEnd();

// Uranus
glPushMatrix();
glRotatef(uranusAngle, 0.0f, 1.0f, 0.0f);
glTranslatef(uranusRadius,0.0, 0.0);
changeColour(53/255.0, 195/255.0, 198/255.0, 0.0);
GLUquadric *Uranus;
Uranus = gluNewQuadric();
gluSphere(Uranus,22.5,100,100);
glPopMatrix();

//Neptune
glPushMatrix();
glRotatef(neptuneAngle, 0.0f, 1.0f, 0.0f);
glTranslatef(neptuneRadius,0.0, 0.0);
changeColour(5/255.0, 5/255.0, 186/255.0, 0.0);
GLUquadric *Neptune;
Neptune = gluNewQuadric();
gluSphere(Neptune,24,100,100);
glPopMatrix();

angle+= 0.2f;
uranusAngle += uranus  * 10;
neptuneAngle += neptune * 10;


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
