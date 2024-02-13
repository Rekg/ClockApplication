#include<Windows.h>
#include<stdio.h>
#include<GL/gl.h>
#include<GL/glut.h>
#include<time.h>
#include<math.h>
#include<sys/timeb.h>
#include<string.h>
#define sign(x) ((x>0)?1:((x<0)?-1:0))
void createmenu(void);
int hour,minute,second,a,b,c,d,e,f,z=2,hourmax,minutemax,secondmax,htmr,mtmr,stmr,t,times,n,yVal=200;
static int window;
static int alarmd;
static int alarma;
static int timerd;
static int timera;
static int dmenu;
static int currentt;
static int mmenu;
static int amenu;

int value;

/* Function to plot a point */

void setPixel(GLint x, GLint y) {
  glBegin(GL_POINTS);
  glVertex2i(x,y);
  glEnd();
}

/* Generalized Bresenham's Algorithm */
void bresenham(int x1, int y1, int x2, int y2)
{
  glColor3f(0.0,1.0,0.0);
  int dx, dy, x, y, d, s1, s2, swap=0, temp;
  dx = abs(x2 - x1);
  dy = abs(y2 - y1);
  s1 = sign(x2-x1);
  s2 = sign(y2-y1);

  if(dy > dx){temp = dx; dx = dy; dy = temp; swap = 1;}

  /* Set the initial decision parameter and the initial point */
  d = 2 * dy - dx;
  x = x1;
  y = y1;

  int i;
  for(i = 1; i <= dx; i++)
  {
    setPixel(x,y);

    while(d >= 0)
    {
      if(swap) x = x + s1;
      else
      {
        y = y + s2;
        d = d - 2* dx;
      }
    }
    if(swap) y = y + s2;
    else x = x + s1;
    d = d + 2 * dy;
  }
  glFlush();
}


void drawbresenham(int num, int x, int y)
{
    switch(num)
    {
       case 1: bresenham(x+80,y,x+80,y+80);
               bresenham(x+80,y+80,x+80,y+160);
               break;

       case 2: bresenham(x,y+160,x+80,y+160);
               bresenham(x+80,y+160,x+80,y+80);
               bresenham(x+80,y+80,x,y+80);
               bresenham(x,y+80,x,y);
               bresenham(x,y,x+80,y);
               break;

       case 3: bresenham(x,y+160,x+80,y+160);
               bresenham(x+80,y+160,x+80,y+80);
               bresenham(x+80,y+80,x,y+80);
               bresenham(x+80,y+80,x+80,y);
               bresenham(x,y,x+80,y);
               break;

       case 4: bresenham(x,y+80,x,y+160);
               bresenham(x,y+80,x+80,y+80);
               bresenham(x+80,y+160,x+80,y+80);
               bresenham(x+80,y+80,x+80,y);
               break;

       case 5: bresenham(x,y+160,x+80,y+160);
               bresenham(x,y+80,x,y+160);
               bresenham(x,y+80,x+80,y+80);
               bresenham(x+80,y+80,x+80,y);
               bresenham(x,y,x+80,y);
               break;

       case 6: bresenham(x,y,x,y+80);
               bresenham(x,y+160,x+80,y+160);
               bresenham(x,y+80,x,y+160);
               bresenham(x,y+80,x+80,y+80);
               bresenham(x+80,y+80,x+80,y);
               bresenham(x,y,x+80,y);
               break;

       case 7: bresenham(x,y+160,x+80,y+160);
               bresenham(x+80,y+160,x+80,y+80);
               bresenham(x+80,y+80,x+80,y);
               break;

       case 8: bresenham(x,y,x,y+80);
               bresenham(x,y+160,x+80,y+160);
               bresenham(x,y+80,x,y+160);
               bresenham(x,y+80,x+80,y+80);
               bresenham(x+80,y+80,x+80,y);
               bresenham(x,y,x+80,y);
               bresenham(x+80,y+80,x+80,y+160);
               break;

       case 9: bresenham(x,y+160,x+80,y+160);
               bresenham(x,y+80,x,y+160);
               bresenham(x,y+80,x+80,y+80);
               bresenham(x+80,y+80,x+80,y);
               bresenham(x+80,y+80,x+80,y+160);
               break;


       case 0: bresenham(x,y,x,y+80);
               bresenham(x,y+160,x+80,y+160);
               bresenham(x,y+80,x,y+160);
               bresenham(x+80,y+80,x+80,y);
               bresenham(x,y,x+80,y);
               bresenham(x+80,y+80,x+80,y+160);
               break;
    }
}

const float clockR = 80.0f,
            clockVol  = 100.0f,

            angle1min = M_PI / 30.0f,

            minStart  = 0.9f,
            minEnd    = 1.0f,

            stepStart = 0.8f,
            stepEnd   = 1.0f;

float angleHour = 0,
      angleMin  = 0,
      angleSec  = 0;




void newLine(float rStart, float rEnd, float angle) {
  float c = cos(angle), s = sin(angle);
  glVertex2f( clockR*rStart*c, clockR*rStart*s);
  glVertex2f( clockR*rEnd*c, clockR*rEnd*s);
}

void RenderScene(void) {
  int i;

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0f, 0.0f, 0.0f);
  glLineWidth(1.0f);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_POLYGON_SMOOTH);
  glBegin(GL_LINES);
  
  for (i = 0; i < 60; i++) {
      if(i%5){ // normal minute
        if(i%5 == 1)
          glColor3f(0.0f, 1.0f, 0.0f);
        newLine(minStart, minEnd, i*angle1min);
      }else{
        glColor3f(1.0f, 0.0f, 0.0f);
        newLine(stepStart, stepEnd, i*angle1min);
      }
    }
  glEnd();

  glLineWidth(3.0f);
  glColor3f(1.0f,1.0f,0.0f);
  glBegin(GL_LINES);
    newLine(0.0f, 0.5f, -angleHour+M_PI/2);
    newLine(0.0f, 0.8f, -angleMin+M_PI/2);
  glEnd();

  glLineWidth(1.0f);
  glColor3f(1.0f, 1.0f, 0.0f);
  glBegin(GL_LINES);
    newLine(0.0f, 0.8f, -angleSec+M_PI/2);
  glEnd();

  glutSwapBuffers();
}


void Circle(int xCenter, int yCenter) {
  int r = 2;
  int x=0,y=r;
  int d = 1 - r;    // = 1 - r
  //glClear(GL_COLOR_BUFFER_BIT);
  glColor3f( 0 ,1, 0);
  while(x<=y){
    setPixel(xCenter+x,yCenter+y);
    setPixel(xCenter+y,yCenter+x);  //find other points by symmetry
    setPixel(xCenter-x,yCenter+y);
    setPixel(xCenter+y,yCenter-x);
    setPixel(xCenter-x,yCenter-y);
    setPixel(xCenter-y,yCenter-x);
    setPixel(xCenter+x,yCenter-y);
    setPixel(xCenter-y,yCenter+x);
    if (d<0)
      d += (2*x)+3;
    else {
     d += (2*(x-y))+5;
     y -= 1;
    }
    x++;
  }

  glFlush();
}
/* Function to draw a rhombus inscribed in a rectangle and roll */
/* number printed in it */
void draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  drawbresenham(a,60,200);
  drawbresenham(b,170,200);
  drawbresenham(c,310,200);
  drawbresenham(d,420,200);
  drawbresenham(e,560,200);
  drawbresenham(f,670,200);
  Circle(280,280);
  Circle(280,360);
  Circle(530,280);
  Circle(530,360);

  glFlush();
}

void TimerFunc2(int value)
{
    if(hour==0 && minute==0 && second==0)
    {

        PlaySound("C:\\Users\\redie\\oneDrive\\Desktop\\alarm.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
    }
    else
    {
        if(hour==0 && minute==0 && second==1)
            glClearColor(1,0,0,1);
        if(second==0 && minute==0)
        {
            hour--;
            second=59;
            minute=59;
        }
        else if(second==0)
        {
            minute--;
            second=59;
        }
        else
            second--;

         a=hour/10;
         b=hour%10;
         c=minute/10;
         d=minute%10;
         e=second/10;
         f=second%10;
         glutPostRedisplay();
         glutTimerFunc(1000,TimerFunc2,1);
    }

}

void Timer()
{
    char string1[]="Clock Application";
    char string2[]="By";
    char string3[]="Rediat Hailemariam";
    char string4[]="Rediet Negash";
    char string5[]="  Rekik Solomon";
    char string6[]="Ruhamma Ashenafi";
    char string7[]="Ruth Asmamaw";
    char c;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,1,0);
    glTranslatef(80,300,0);
    glScalef(0.5,0.5,0);
    for (c=0; c<strlen(string1); c++)
    {
    glutStrokeCharacter(GLUT_STROKE_ROMAN,string1[c]);
    }

    glColor3f(0.0,1.0,0.0);
    glTranslatef(-360,-150,0);
    glScalef(0.5,0.5,0);
    for (c=0; c<strlen(string2); c++)
    {
    glutStrokeCharacter(GLUT_STROKE_ROMAN,string2[c]);
    }
    
    glColor3f(0.0, 1.0, 0.0);
  glTranslatef(-400,-150,0);
  for (c=0; c<strlen(string3); c++)
  {
    glutStrokeCharacter(GLUT_STROKE_ROMAN,string3[c]);
  }
  glColor3f(0.0,1.0,0.0);
  glTranslatef(-1200,-150,0);
  for (c=0; c<strlen(string4); c++)
  {

    glutStrokeCharacter(GLUT_STROKE_ROMAN,string4[c]);
  }

    glColor3f(0.0,1.0,0.0);
    glTranslatef(-1080,-150,0);
  for (c=0; c<strlen(string5); c++)
  {

    glutStrokeCharacter(GLUT_STROKE_ROMAN,string5[c]);
  }
  glColor3f(0.0,1.0,0.0);
  glTranslatef(-920,-150,0);
  for (c=0; c<strlen(string6); c++)
  {

    glutStrokeCharacter(GLUT_STROKE_ROMAN,string6[c]);
  }
  glColor3f(0.0,1.0,0.0);
  glTranslatef(-1200,-150,0);
  for (c=0; c<strlen(string7); c++)
  {

    glutStrokeCharacter(GLUT_STROKE_ROMAN,string7[c]);
  }

    glutSwapBuffers();

}

// Update angles of hour, minute, and second hands based on current time
void TimerFunction4(int value) {
  struct timeb tb;
  time_t tim=time(0);
  struct tm* t;
  t=localtime(&tim);
  ftime(&tb);

  //angleSec = (float)(t->tm_sec+ (float)tb.millitm/1000.0f)/30.0f * M_PI;
  angleSec = (float)(t->tm_sec)/30.0f * M_PI;
  angleMin = (float)(t->tm_min)/30.0f * M_PI + angleSec/60.0f;
  angleHour = (float)(t->tm_hour > 12 ? t->tm_hour-12 : t->tm_hour)/6.0f * M_PI+angleMin/12.0f;
  glutPostRedisplay();
  glutTimerFunc(1000,TimerFunction4, 1);
}

void SetupRC(void) {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void ChangeSize(GLsizei w, GLsizei h) {
  GLfloat aspectRatio;

  // Prevent a divide by zero
  if(h == 0)
    h = 1;

  // Set viewport to window dimensions
  glViewport(0, 0, w, h);

  // Reset coordinate system
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Establish clipping volume (left, right, bottom, top, near, far)
  aspectRatio = (GLfloat)w / (GLfloat)h;
  if (w <= h)
    glOrtho (-clockVol, clockVol, -clockVol / aspectRatio, clockVol / aspectRatio, 1.0, -1.0);
  else
    glOrtho (-clockVol * aspectRatio, clockVol * aspectRatio, -clockVol, clockVol, 1.0, -1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}


void menu(int num) {
  if(num == 0){
    glutDestroyWindow(window);
    exit(0);
  }else{
    value = num;
    switch(value)
             {
                 case 1:
                 case 2:
                 case 3:
                 case 4:
                            {
           glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
           glutInitWindowPosition(0,0);
           glutInitWindowSize(840, 480);
            glutCreateWindow("Digital Clock");
            createmenu();
           glClearColor(0.0,0.0,0.0,0);
        glColor3f(1.0,1.0,1.0);
        gluOrtho2D(0,840,0,480);
                           htmr=0;
                           mtmr=0;
                           stmr=0;
                           switch(value){
                            case 1: stmr=10;
                                     break;
                            case 2: mtmr=1;
                                     break;
                            case 3: mtmr+=5;
                                     break;
                            case 4: mtmr+=10;
                                     break;
                           }
                           hour=htmr;
                           minute=mtmr;
                           second=stmr;
                           a=hour/10;
                           b=hour%10;
                           c=minute/10;
                           d=minute%10;
                           e=second/10;
                           f=second%10;

                           glutDisplayFunc(draw);
                           glutTimerFunc(1000,TimerFunc2,1);

                           glutMainLoop();
                           break;
                           }
       case 5:
                  {
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
            glutInitWindowPosition(0,0);
            glutInitWindowSize(840, 480);
            glutCreateWindow("Analog Clock");
            createmenu();
            glClearColor(0.0,0.0,0.0,0);
            glColor3f(1.0f,1.0f,1.0f);
            gluOrtho2D(0,840,0,480);
                            glutDisplayFunc(RenderScene);
                            glutReshapeFunc(ChangeSize);
                            glutTimerFunc(33, TimerFunction4, 1);
                            SetupRC();
                            glutMainLoop();
                            break;
                              }

                          }
  }
  glutPostRedisplay();
}

void createmenu(void) {
    timerd = glutCreateMenu(menu);
    glutAddMenuEntry("10 Seconds",1);
    glutAddMenuEntry("1 Minute",2);
    glutAddMenuEntry("5 Minutes",3);
    glutAddMenuEntry("10 Minutes",4);


    glutCreateMenu(menu);
    glutAddSubMenu("Set Timer", timerd);


    dmenu = glutCreateMenu(menu);
    glutAddSubMenu("Current Time",currentt);
    glutAddSubMenu("Set Timer",timerd);

    amenu = glutCreateMenu(menu);
    glutAddMenuEntry("Current Time",5);

    mmenu=glutCreateMenu(menu);
    glutAddSubMenu("Digital Clock",dmenu);
    glutAddSubMenu("Analog Clock",amenu);
    glutAddMenuEntry("Exit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    printf("Welcome to clock application\n");
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(840, 480);
    window = glutCreateWindow("Welcome to clock application");
    createmenu();
    glClearColor(0.0, 0.0, 0.0, 0);
    glColor3f(1.0f, 1.0f, 1.0f);
    gluOrtho2D(0, 840, 0, 480);
    glutDisplayFunc(Timer);
    glutMainLoop();
    return 0;
}
