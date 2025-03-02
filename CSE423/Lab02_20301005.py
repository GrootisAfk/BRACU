from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
import random

catcherX = 200
catcherY = 30
diamondX = random.randint(50, 350)
diamondY = 500
diamondStop = False
BackButtonChk = False
PlayButtonChk = False
CrossButtonChk = False
gameScore = 0
fallingSpeed = 1
paused = False


def MidPointLine(zone, x1, y1, x2, y2):
    dx = (x2 - x1)
    dy = (y2 - y1)
    x = x1
    y = y1
    dInitial = 2 * dy - dx
    Del_E = 2 * dy
    Del_NE = 2 * (dy - dx)

    while x <= x2:
        a, b = ConvertToOriginal(zone, x, y)
        drawpoints(a, b)
        if dInitial <= 0:
            x = x + 1
            dInitial = dInitial + Del_E
        else:
            x = x + 1
            y = y + 1
            dInitial = dInitial + Del_NE


def FindZone(x1, y1, x2, y2):
    dx = (x2 - x1)
    dy = (y2 - y1)
    if abs(dx) > abs(dy):
        if dx > 0 and dy > 0:
            return 0
        elif dx < 0 < dy:
            return 3
        elif dx < 0 and dy < 0:
            return 4
        else:
            return 7
    else:
        if dx > 0 and dy > 0:
            return 1
        elif dx < 0 < dy:
            return 2
        elif dx < 0 and dy < 0:
            return 5
        else:
            return 6


def ConvertToZoneZero(zone, x, y):
    if zone == 0:
        return x, y
    elif zone == 1:
        return y, x
    elif zone == 2:
        return -y, x
    elif zone == 3:
        return -x, y
    elif zone == 4:
        return -x, -y
    elif zone == 5:
        return -y, -x
    elif zone == 6:
        return -y, x
    elif zone == 7:
        return x, -y


def ConvertToOriginal(zone, x, y):
    if zone == 0:
        return x, y
    if zone == 1:
        return y, x
    if zone == 2:
        return -y, -x
    if zone == 3:
        return -x, y
    if zone == 4:
        return -x, -y
    if zone == 5:
        return -y, -x
    if zone == 6:
        return y, -x
    if zone == 7:
        return x, -y


def Line(x1, y1, x2, y2):
    zone = FindZone(x1, y1, x2, y2)
    x1, y1 = ConvertToZoneZero(zone, x1, y1)
    x2, y2 = ConvertToZoneZero(zone, x2, y2)
    MidPointLine(zone, x1, y1, x2, y2)


def catcher():
    glColor3f(1, 1, 1)
    catcherWidth = 80
    catcherHeight = 20

    Line(catcherX - catcherWidth / 2, catcherY, catcherX + catcherWidth / 2, catcherY)
    Line(catcherX - catcherWidth / 2, catcherY, catcherX - catcherWidth / 2 + 10, catcherY - catcherHeight)
    Line(catcherX + catcherWidth / 2, catcherY, catcherX + catcherWidth / 2 - 10, catcherY - catcherHeight)
    Line(catcherX - catcherWidth / 2 + 10, catcherY - catcherHeight, catcherX + catcherWidth / 2 - 10, catcherY - catcherHeight)


def diamond():
    glColor3f(1, 0, 1)
    global diamondX, diamondY, catcherX, catcherY
    global fallingSpeed, gameScore, diamondStop

    Line(diamondX, diamondY, diamondX + 5, diamondY - 10)
    Line(diamondX, diamondY, diamondX - 5, diamondY - 10)
    Line(diamondX - 5, diamondY - 10, diamondX, diamondY - 20)
    Line(diamondX, diamondY - 20, diamondX + 5, diamondY - 10)
    diamondY = (diamondY - fallingSpeed)

    if diamondY - 20 < catcherY and catcherX - 50 <= diamondX <= catcherX + 50:
        diamondX = random.randint(100, 350)
        diamondY = 600
        gameScore = gameScore + 1
        fallingSpeed = fallingSpeed + 1
        print("Game Score: ", gameScore)
    elif diamondY - 20 < 0:
        fallingSpeed = 0
        diamondY = 20
        totalScore = gameScore
        gameScore = 0
        diamondStop = True
        print('======================')
        print("Game Over!")
        print("Total Score: ", totalScore)


def play_button():
    glColor3f(0, 1, 0)
    Line(200, 580, 220, 570)
    Line(200, 560, 220, 570)


def back_button():
    Line(10, 570, 30, 570)
    Line(10, 570, 20, 580)
    Line(10, 570, 20, 560)


def cross_button():
    Line(390, 580, 370, 560)
    Line(370, 580, 390, 560)


def pause_resume_button():
    glColor3f(1, 1, 1)
    Line(190, 580, 190, 560)
    Line(210, 580, 210, 560)


def specialKeyboardListener(key, x, y):
    global catcherX
    if key == GLUT_KEY_LEFT:
        catcherX = max(45, catcherX - 10)
    elif key == GLUT_KEY_RIGHT:
        catcherX = min(360, catcherX + 10)
    glutPostRedisplay()


def mouseListener(button, state, x, y):
    global BackButtonChk, CrossButtonChk, PlayButtonChk, diamondStop, gameScore, paused
    converted_y = 600 - y
    if button == GLUT_LEFT_BUTTON and state == GLUT_DOWN:
        if 10 <= x <= 30 and 560 <= converted_y <= 580:
            BackButtonChk = True
            reset_game()
        elif 370 <= x <= 390 and 560 <= converted_y <= 580:
            CrossButtonChk = True
        elif 200 - 10 <= x <= 220 + 10 and 560 <= converted_y <= 580:
            PlayButtonChk = not PlayButtonChk
            paused = not paused
        glutPostRedisplay()


def reset_game():
    global diamondStop, gameScore, diamondY, catcherX
    diamondStop = False
    gameScore = 0
    diamondY = 500
    catcherX = 350


def timer(value):
    if not paused:
        glutPostRedisplay()
    glutTimerFunc(16, timer, 0)


def drawpoints(x, y):
    glPointSize(1)
    glBegin(GL_POINTS)
    glVertex2f(x, y)
    glEnd()


def iterate():
    glViewport(0, 0, 400, 600)
    glOrtho(0.0, 400, 0.0, 600, 0.0, 1.0)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glLoadIdentity()
    glMatrixMode(GL_MODELVIEW)


def display():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()
    iterate()

    glColor3f(1, 1, 1)
    catcher()

    global diamondStop
    if diamondStop:
        glColor3f(1, 0, 0)
        diamond()
    else:
        glColor3f(1, 1, 0)
        diamond()

    global diamondY, gameScore
    if BackButtonChk:
        glColor3f(0, 0, 1)
        back_button()
        diamondY = 600
        gameScore = 0
    else:
        glColor3f(0, 0, 1)
        back_button()

    if CrossButtonChk:
        cross_button()
        glutLeaveMainLoop()
    else:
        glColor3f(1, 0, 0)
        cross_button()

    if PlayButtonChk:
        play_button()

    if not paused:
        pause_resume_button()

    glutSwapBuffers()


glutInit()
glutInitDisplayMode(GLUT_RGBA)
glutInitWindowSize(400, 600)
glutInitWindowPosition(1000, 250)
wind = glutCreateWindow(b"Diamond Catcher Game")
glutTimerFunc(0, timer, 0)
glutMouseFunc(mouseListener)
glutSpecialFunc(specialKeyboardListener)
glutDisplayFunc(display)
glutMainLoop()
