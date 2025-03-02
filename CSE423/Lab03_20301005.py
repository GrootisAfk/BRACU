from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import math

WINDOW_WIDTH = 500
WINDOW_HEIGHT = 500

circles = []
is_paused = False
max_radius = 800
growth_speed = 1
min_growth_speed = 1


def mid_circle(cx, cy, radius):
    d = 1 - radius
    x = 0
    y = radius

    draw_circle_dots(x, y, cx, cy)

    while x < y:
        if d < 0:
            d = d + 2 * x + 3
        else:
            d = d + 2 * x - 2 * y + 5
            y = y - 1
        x = x + 1
        draw_circle_dots(x, y, cx, cy)


def draw_circle_dots(x, y, cx, cy):
    glVertex2f(x + cx, y + cy)
    glVertex2f(y + cx, x + cy)
    glVertex2f(y + cx, -x + cy)
    glVertex2f(x + cx, -y + cy)
    glVertex2f(-x + cx, -y + cy)
    glVertex2f(-y + cx, -x + cy)
    glVertex2f(-y + cx, x + cy)
    glVertex2f(-x + cx, y + cy)


def initialize():
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glOrtho(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT, 0.0, 1.0)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()


def show_screen():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glColor3f(1.0, 0.0, 0.0)
    glPointSize(2)
    glBegin(GL_POINTS)

    for x, y, radius in circles:
        mid_circle(x, y, radius)

    glEnd()

    glutSwapBuffers()


def keyboard_ordinary_keys(key, x, y):
    global is_paused, growth_speed, min_growth_speed
    if key == b' ':
        is_paused = not is_paused
    elif key == b'\r':
        is_paused = not is_paused
    elif key == b's':
        growth_speed += 1
    elif key == b'd':
        growth_speed -= 1 if growth_speed > min_growth_speed else 0

    glutPostRedisplay()


def mouse_click(button, state, x, y):
    global circles
    if button == GLUT_LEFT_BUTTON and state == GLUT_DOWN:
        world_x, world_y = x, WINDOW_HEIGHT - y
        circles.append((world_x, world_y, 10))


def update_animation():
    if not is_paused:
        global circles
        new_circles = []  # List to store circles within display boundary

        for circle in circles:
            x, y, radius = circle
            new_radius = radius + growth_speed

            # Check if circle exceeds display boundary
            if (x + new_radius) <= WINDOW_WIDTH and (x - new_radius) >= 0 and (y + new_radius) <= WINDOW_HEIGHT and (y - new_radius) >= 0:
                new_circles.append((x, y, new_radius))

        circles = new_circles  # Update circles with new list

    glutPostRedisplay()

glutInit()
glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH)
glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT)
glutInitWindowPosition(0, 0)
window = glutCreateWindow(b"LAB TASK 03")
glutDisplayFunc(show_screen)
glutIdleFunc(update_animation)
glutKeyboardFunc(keyboard_ordinary_keys)
glutMouseFunc(mouse_click)
glEnable(GL_DEPTH_TEST)
initialize()
glutMainLoop()