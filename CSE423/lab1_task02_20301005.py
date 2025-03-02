from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *

W_Width, W_Height = 500, 500

ballx = bally = 0
speed = 0.01
ball_size = 2
create_new = False

class point:
    def __init__(self):
        self.x = 0
        self.y = 0
        self.z = 0

def convert_coordinate(x, y):
    global W_Width, W_Height
    a = x - (W_Width/2)
    b = (W_Height/2) - y 
    return a, b

def draw_points(x, y, s):
    glPointSize(15)
    glBegin(GL_POINTS)
    glColor3f(0.0, 1.0, 1.0)
    glVertex2f(x, y)
    glEnd()

freeze = False
def keyboardListener(key, x, y):
    global ball_size, freeze
    if key == b'w':
        ball_size += 1
        print("Size Increased")
    if key == b's':
        ball_size -= 1
        print("Size Decreased")
    if key == b' ':  
        freeze = not freeze  
        print("Freeze:", freeze)
    glutPostRedisplay()

def specialKeyListener(key, x, y):
    global speed
    if key == 'w':
        print(1)
    if key == GLUT_KEY_UP:
        speed *= 2
        print("Speed Increased")
    if key == GLUT_KEY_DOWN:
        speed /= 2
        print("Speed Decreased")
    glutPostRedisplay()

def mouseListener(button, state, x, y):
    global ballx, bally, create_new
    if button == GLUT_LEFT_BUTTON:
        if state == GLUT_DOWN:
            print(x, y)
            c_X, c_y = convert_coordinate(x, y)
            ballx, bally = c_X, c_y

    if button == GLUT_RIGHT_BUTTON:
        if state == GLUT_DOWN:
            create_new = convert_coordinate(x, y)

    glutPostRedisplay()

def display():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glClearColor(0, 0, 0, 0)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()

    gluLookAt(0, 0, 200, 0, 0, 0, 0, 1, 0)
    glMatrixMode(GL_MODELVIEW)

    global ballx, bally, ball_size
    draw_points(ballx, bally, ball_size)

    if create_new:
        m, n = create_new
        glBegin(GL_POINTS)
        glColor3f(0.7, 0.8, 0.6)
        glVertex2f(m, n)
        glEnd()

    glutSwapBuffers()

def animate():
    global ballx, bally, speed, freeze
    if not freeze:
        ballx = (ballx + speed) % 180
        bally = (bally + speed) % 180
    glutPostRedisplay()

def init():
    glClearColor(0, 0, 0, 0)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(104, 1, 1, 1000.0)

glutInit()
glutInitWindowSize(W_Width, W_Height)
glutInitWindowPosition(0, 0)
glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB)

wind = glutCreateWindow(b"Task_02")
init()

glutDisplayFunc(display)
glutIdleFunc(animate)

glutKeyboardFunc(keyboardListener)
glutSpecialFunc(specialKeyListener)
glutMouseFunc(mouseListener)

glutMainLoop()
