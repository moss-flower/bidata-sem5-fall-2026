#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <GLUT/glut.h>

typedef struct {
    GLfloat x, y, z;
}vec3;

typedef struct {
    GLfloat r, g, b;
}col3;

const col3 red = {1.0f, 0.0f, 0.0f};
const col3 green = {0.0f, 1.0f, 0.0f};
const col3 blue = {0.0f, 0.0f, 1.0f};

struct cuboid {
    vec3 position;
    vec3 rotation;
    vec3 scale;
    vec3 vertices[24] {
        // top
        {-1.0f, 1.0f, -1.0f},
        {1.0f, 1.0f, -1.0f},
        {1.0f, 1.0f, 1.0f},
        {-1.0f, 1.0f, 1.0f},

        //back
        {-1.0f, -1.0f, -1.0f},
        {1.0f, -1.0f, -1.0f},
        {1.0f, 1.0f, -1.0f},
        {-1.0f, 1.0f, -1.0f},

        //bottom
        {-1.0f, -1.0f, -1.0f},
        {1.0f, -1.0f, -1.0f},
        {1.0f, -1.0f, 1.0f},
        {-1.0f, -1.0f, 1.0f},

        //left
        {-1.0f, -1.0f, -1.0f},
        {-1.0f, 1.0f, -1.0f},
        {-1.0f, 1.0f, 1.0f},
        {-1.0f, -1.0f, 1.0f},

        //right
        {1.0f, -1.0f, -1.0f},
        {1.0f, -1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, -1.0f},

        //front
        {-1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, -1.0f, 1.0f},
        {-1.0f, -1.0f, 1.0f},
    };
    col3 colors[24] {
        // top
        red, red, red, red,
        //back
        green, green, green, green,
        // bottom
        red, red, red, red,
        // left
        blue, blue, blue, blue,
        //right
        blue,blue, blue, blue,
        //front
        green, green, green, green,
    };
};

typedef struct {
    vec3 position;
    vec3 rotation;
}camera;

void scaleCuboid(cuboid &cuboid, float scale) {
    cuboid.scale.x = scale;
    cuboid.scale.y = scale;
    cuboid.scale.z = scale;
}

void translateCuboid(cuboid &cuboid, vec3 translation) {
    cuboid.position.x = translation.x;
    cuboid.position.y = translation.y;
    cuboid.position.z = translation.z;
}

void rotateCuboid(cuboid &cuboid, float angle, vec3 axis) {
    cuboid.rotation.x += (angle * axis.x);
    cuboid.rotation.y += (angle * axis.y);
    cuboid.rotation.z += (angle * axis.z);
    if (cuboid.rotation.x >= 360.0f) {
        cuboid.rotation.x -= 360.0f;
    }
    if (cuboid.rotation.y >= 360.0f) {
        cuboid.rotation.y -= 360.0f;
    }
    if (cuboid.rotation.z >= 360.0f) {
        cuboid.rotation.z -= 360.0f;
    }
}

cuboid createCuboid(vec3 position, float size) {
    cuboid cuboid;
    scaleCuboid(cuboid, size);
    translateCuboid(cuboid, position);
    cuboid.rotation.x = 0.0f, cuboid.rotation.y = 0.0f, cuboid.rotation.z = 0.0f;
    return cuboid;
}

void moveCamera (vec3 delta, camera &cam) {
    cam.position.x += delta.x;
    cam.position.y += delta.y;
    cam.position.z += delta.z;
}

void rotateCamera (vec3 delta, camera &cam) {
    cam.rotation.x += delta.x;
    cam.rotation.y += delta.y;
    cam.rotation.z += delta.z;
}

void setCameraPosition (vec3 delta, camera &cam) {
    cam.position.x = delta.x;
    cam.position.y = delta.y;
    cam.position.z = delta.z;
}

void updateCamera(camera &cam) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, 800.0f / 600.0f, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cam.position.x, cam.position.y, cam.position.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void renderCube(cuboid &cube) {

    glPushMatrix();

    glTranslatef(cube.position.x, cube.position.y, cube.position.z);
    glRotatef(cube.rotation.x, 1.0f, 0.0f, 0.0f);
    glRotatef(cube.rotation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(cube.rotation.z, 0.0f, 0.0f, 1.0f);
    glScalef(cube.scale.x, cube.scale.y, cube.scale.z);

    glBegin(GL_QUADS);
    for (int i = 0; i < 24; i++) {
        glColor3f(cube.colors[i].r, cube.colors[i].g, cube.colors[i].b);
        glVertex3f(cube.vertices[i].x, cube.vertices[i].y, cube.vertices[i].z);
    }
    glEnd();

    glPopMatrix();
}

void render(camera &cam, std::vector<cuboid> &cuboids, sf::Window &window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (auto &cuboid : cuboids) {
        renderCube(cuboid);
    }
    glFlush();
    window.display();
}

std::vector<cuboid> initCuboids() {
    std::vector<cuboid> cuboids;
    for (int i = -1; i < 1; i++) {
        for (int j = -1; j < 1; j++) {
            for (int k = -1; k < 1; k++) {
                cuboids.push_back(createCuboid({(GLfloat)i, (GLfloat)j, (GLfloat)k}, 1));
            }
        }
    }
}

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

int main() {
    sf::Window window = init();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearDepth(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    std::vector<cuboid> cuboids;
    cuboids.push_back(createCuboid({0,0,0.0f}, 1.0f));
    camera cam;
    setCameraPosition({0,0,-5.0f}, cam);

    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::W) {
                    rotateCuboid(cuboids[0], 15.0f, {1.0f,0.0, 0} );
                }
            }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::A) {
                    rotateCuboid(cuboids[0], 15.0f, {0.0f,-1.0, 0} );
                }
            }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::D) {
                    rotateCuboid(cuboids[0], 15.0f, {0.0f,1.0, 0} );
                }
            }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::S) {
                    rotateCuboid(cuboids[0], 15.0f, {-1.0f,0.0, 0} );
                }
            }
        }
        updateCamera(cam);
        render(cam, cuboids, window);
    }

    return 0;
}
