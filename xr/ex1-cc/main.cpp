#include <iostream>
#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <GLUT/glut.h>


sf::Window init() {
    sf::ContextSettings settings{
        .depthBits = 24,
        .stencilBits = 8,
        .antiAliasingLevel = 0,
        .majorVersion = 2,
        .minorVersion = 1
    };

    sf::Window window(
        sf::VideoMode({800, 600}),
        "OpenGL",
        sf::Style::Default,
        sf::State::Windowed,
        settings
    );
    return window;
}

void display(sf::Window& window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //glTranslatef(-1.5f, 0.0f, -8.0f); // Move left 1.5 Units and 7 units into the screen
    glColor3f(1.0f, 0.0f, 0.0f);      // Set the color to red

    glBegin(GL_TRIANGLES);          // Start drawing using the polygon primitive GL_TRIANGLES
    glVertex3f(0.25f, 0.25f, 0.0f);   // Top
    glVertex3f(0.75f, 0.25f, 0.0f); // Bottom left
    glVertex3f(0.75f, -.75f, 0.0f);  // Bottom right
    glEnd();
    glFlush();


    window.display();
}

struct Vertex {
    float x, y, z;
};

void makeShape(GLenum s, sf::Vector3f offset, Vertex* vertices, size_t count, Vertex color) {
    glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
    glTranslatef(offset.x, offset.y, offset.z);
    glColor3f(color.x, color.y, color.z);
    glBegin(s);
    for (int i = 0; i < count; i++) {
        glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
    }
    glEnd();
    glLoadIdentity();
}

void drawShapes(sf::Window& window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    Vertex vertices[] = {
        {0.0, 2.0, 0.0},
        {1.5, 1.5, 0.0},
        {2.0, 0.0, 0.0},
        {1.5, -1.5, 0.0},
        {0.0, -2.0, 0.0},
        {-1.5, -1.5, 0.0},
        {-2.0, 0.0, 0.0},
        {-1.5, 1.5, 0.0},
    };
    glPointSize(4.0f);

    makeShape(GL_POINTS, sf::Vector3f(0.0,0.0,0.0), vertices, 8, Vertex(1.0,1.0,0.1));
    makeShape(GL_LINES, sf::Vector3f(0.0,0.0,0.0), vertices, 8, Vertex(0.0,1.0,1.1));
    makeShape(GL_LINE_STRIP, sf::Vector3f(-4.0,-1.0,0.0), vertices, 8, Vertex(0.5,0.2,0.1));
    makeShape(GL_LINE_LOOP, sf::Vector3f(4.0,4.0,0.0), vertices, 8, Vertex(0.1,0.3,0.9));
    makeShape(GL_TRIANGLE_STRIP, sf::Vector3f(-4.0,4.0,0.0), vertices, 8, Vertex(0.2,0.2,0.4));
    makeShape(GL_TRIANGLE_FAN , sf::Vector3f(4.0,-4.0,0.0), vertices, 8, Vertex(0.7,0.2,0.3));
    makeShape(GL_QUADS, sf::Vector3f(2.0,2.0,0.0), vertices, 8, Vertex(0.5,0.7,0.3));
    makeShape(GL_QUAD_STRIP, sf::Vector3f(2.0,-2.0,0.0), vertices, 8, Vertex(0.1,0.7,0.5));
    makeShape(GL_POLYGON, sf::Vector3f(-2.0,2.0,0.0), vertices, 8, Vertex(0.7,0.1,0.3));

    glFlush();
    window.display();
}



void animation(int i, sf::Window& window) {
    auto offset = float(i)/(float(window.getSize().x)*5);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glTranslatef(offset, 0.5f, 0.0f); // Move left 1.5 Units and 7 units into the screen
    glColor3f(1.0f, 0.0f, 0.0f);      // Set the color to red

    glBegin(GL_TRIANGLES);          // Start drawing using the polygon primitive GL_TRIANGLES
    glVertex3f(0.25f, 0.25f, 0.0f);   // Top
    glVertex3f(0.75f, 0.25f, 0.0f); // Bottom left
    glVertex3f(0.75f, -.75f, 0.0f);  // Bottom right
    glEnd();
    glFlush();
    window.display();
}

void drawCubeLines(sf::Window& window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
    gluPerspective(90.0, 1.0, 0.1, 100.0);
    glColor3f(1.0f, 1.0f, 0.0f);

    glTranslatef(0, 0, -2.0f);
    //face A
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glEnd();

    //face B
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glEnd();

    //face C
    glBegin(GL_LINE_LOOP);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();

    //face D
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glEnd();

    //face E
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glEnd();

    //face F
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();

    glFlush();
    window.display();


}

void drawPrebuiltCubes(sf::Window& window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, 1.0, 0.1, 100.0);
    glTranslatef(0, 0, -2.0f);
    glColor3f(1.0f, 0.0f, 1.0f);

    glutWireCube(1.5);

    glFlush();
    window.display();
}

void drawRotatedCubes(int i, sf::Window& window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glColor3f(1.0f, 1.0f, 1.0f);
    glLoadIdentity();
    gluPerspective(90.0, 1.0, 0.1, 100.0);
    float angle = float(i);
    glRotatef(angle*0.01, 0.0f, 1.0f, 0.0f);

    glutWireCube(1.0);

    glFlush();
    window.display();
}

void drawTranslatedRotatedCubes(int i, sf::Window& window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glColor3f(1.0f, 1.0f, 1.0f);
    glLoadIdentity();
    gluPerspective(90.0, 1.0, 0.1, 100.0);
    float angle = float(i);
    glTranslatef(0, 0, -2.0f);
    glRotatef(angle*0.01, 0.0f, 1.0f, 0.0f);

    glutWireCube(1.0);

    glFlush();
    window.display();
}

void rotFirst(int i, sf::Window& window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glColor3f(1.0f, 1.0f, 1.0f);
    glLoadIdentity();
    gluPerspective(90.0, 1.0, 0.1, 100.0);
    float angle = float(i);
    glRotatef(angle*0.01, 0.0f, 1.0f, 0.0f);
    glTranslatef(0, 0, -2.0f);

    glutWireCube(1.0);

    glFlush();
    window.display();
}

void justRotateCube(int i) {
    float angle = float(i);
    glRotatef(angle*0.01, 0.0f, 1.0f, 0.0f);
    glutWireCube(1.0);
}

struct vector3 {
    float x, y, z;
};

void lookAt(sf::Window& window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    vector3 cubePos = vector3(0,0,0);

    gluPerspective(90.0, 1.0, 0.1, 100.0);

    vector3 camPos[] = {
        {4.0f, 4.0f, 4.0f},
        {0.0f, 0.0f, 2.0f},
        {0.0f, 2.0f, 2.0f},
    };

    gluLookAt(1.0f,1.35f,2.0f,0,0,0,0,1,0);

    glColor3f(1.0f, 1.0f, 1.0f);

    sf::Clock frameClock;

    for (int i = 0; i < 180; i++) {
        float dt = frameClock.restart().asSeconds();
        sf::sleep(sf::milliseconds(16));
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        justRotateCube(i);
        glFlush();
        window.display();
    }
    glLoadIdentity();
    gluPerspective(90.0, 1.0, 0.1, 100.0);
    gluLookAt(1.0f,1.35f,4.0f,0,0,0,0,1,0);

    bool hasSwapped = false;

    for (int i = 180; i < 360; i++) {
        float dt = frameClock.restart().asSeconds();
        sf::sleep(sf::milliseconds(16));
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (i >= 270 && !hasSwapped) {
            gluPerspective(90.0, 1.0, 0.1, 100.0);
            gluLookAt(2.0f,4.35f,4.0f,0,0,0,0,1,0);
            hasSwapped = true;
        }
        justRotateCube(i);
        glFlush();
        window.display();
    }
}

int main()
{
    sf::Window window = init();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Escape) {
                    window.close();
                }
            }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Num1) {
                    for (int i  = 0; i < 1000; ++i) {
                        animation(i, window);
                    }
                }
            }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Num2) {
                    display(window);
                }
            }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Num3) {
                    drawShapes(window);
                }
            }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Num4) {
                    drawCubeLines(window);
                }
            }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Num5) {
                    drawPrebuiltCubes(window);
                }
            }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Num6) {
                    for (int i  = 0; i < 18000; ++i) {
                        drawRotatedCubes(i, window);
                    }
                }
            }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Num7) {
                    for (int i  = 0; i < 18000; ++i) {
                        drawTranslatedRotatedCubes(i, window);
                    }
                }
            }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Num8) {
                    for (int i  = 0; i < 36000; ++i) {
                        rotFirst(i, window);
                    }
                }
            }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Num9) {
                    lookAt(window);
                }
            }
        }

    }
}





