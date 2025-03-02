from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
import random 


def draw_box():
    glBegin(GL_QUADS) 
    glColor3f(1.0, 1.0, 0.0)  
    glVertex2f(120, 55)
    glVertex2f(120, 290)
    glVertex2f(381, 290)
    glVertex2f(381, 55)
    glEnd()



def draw_triangle():
    glPointSize(5) 
    glBegin(GL_TRIANGLES)
    glColor3f(0.86, 0.08, 0.24)  
    glVertex2f(120, 290) 
    glVertex2f(251, 458) 
    glVertex2f(381, 290) 
    glEnd()

def draw_door(): 
    glBegin(GL_QUADS)
    glColor3f(0.6, 0.4, 0.2)
    glVertex2f(225, 55) 
    glVertex2f(225, 143) 
    glVertex2f(276, 143)
    glVertex2f(276, 55) 
    glEnd()

def draw_points(x, y):
    glPointSize(6) 
    glBegin(GL_POINTS)
    glColor3f(0.0, 0.0, 0.0) 
    glVertex2f(x,y) 
    glEnd()


def draw_window(): 
    glPointSize(5) 
    glBegin(GL_QUADS)
    glColor3f(0.53, 0.81, 0.98) 
    glVertex2f(294, 193) 
    glVertex2f(365, 193) 
    glVertex2f(365, 256) 
    glVertex2f(294, 256) 
    glEnd()


def draw_raindrop(x, y):
    glLineWidth(1)
    glBegin(GL_LINES)
    glVertex2f(x, y)
    glVertex2f(x, y-15)
    glEnd()



def iterate():
    glViewport(0, 0, 500, 500)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glOrtho(0.0, 500, 0.0, 500, 0.0, 1.0)
    glMatrixMode (GL_MODELVIEW)
    glLoadIdentity()

def showScreen():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()
    iterate()
    glColor3f(1.0, 1.0, 1.0)
    
    
    for i in range(200):  
        x = random.randint(0, 500)  
        y = random.randint(300, 500)  
        draw_raindrop(x, y)

    draw_box()
    draw_triangle()
    draw_door()
    draw_points(270,100)
    draw_window()
    glutSwapBuffers()


glutInit()
glutInitDisplayMode(GLUT_RGBA)
glutInitWindowSize(650, 650)
glutInitWindowPosition(0, 0)
wind = glutCreateWindow(b"Task_01") 
glutDisplayFunc(showScreen)

glutMainLoop()