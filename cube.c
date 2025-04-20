// Compile with:
// gcc cube.c -o cube -lglfw -lGL -lm -ldl

#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

float angle = 0.0f;
float cube_size = 1.0f;

GLuint load_texture(const char* filename) {
    int w, h, channels;
    unsigned char* data = stbi_load(filename, &w, &h, &channels, 4);
    if (!data) {
        fprintf(stderr, "Failed to load image: %s\n", filename);
        exit(1);
    }
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(data);
    return tex;
}

void draw_cube(GLuint tex, float size) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // pastel pinkish gray, slightly transparent

    float s = size;

    glBegin(GL_QUADS);
    // Front
    glTexCoord2f(0,0); glVertex3f(-s,-s, s);
    glTexCoord2f(1,0); glVertex3f( s,-s, s);
    glTexCoord2f(1,1); glVertex3f( s, s, s);
    glTexCoord2f(0,1); glVertex3f(-s, s, s);
    // Back
    glTexCoord2f(0,0); glVertex3f(-s,-s,-s);
    glTexCoord2f(1,0); glVertex3f( s,-s,-s);
    glTexCoord2f(1,1); glVertex3f( s, s,-s);
    glTexCoord2f(0,1); glVertex3f(-s, s,-s);
    // Left
    glTexCoord2f(0,0); glVertex3f(-s,-s,-s);
    glTexCoord2f(1,0); glVertex3f(-s,-s, s);
    glTexCoord2f(1,1); glVertex3f(-s, s, s);
    glTexCoord2f(0,1); glVertex3f(-s, s,-s);
    // Right
    glTexCoord2f(0,0); glVertex3f(s,-s,-s);
    glTexCoord2f(1,0); glVertex3f(s,-s, s);
    glTexCoord2f(1,1); glVertex3f(s, s, s);
    glTexCoord2f(0,1); glVertex3f(s, s,-s);
    // Top
    glTexCoord2f(0,0); glVertex3f(-s, s,-s);
    glTexCoord2f(1,0); glVertex3f( s, s,-s);
    glTexCoord2f(1,1); glVertex3f( s, s, s);
    glTexCoord2f(0,1); glVertex3f(-s, s, s);
    // Bottom
    glTexCoord2f(0,0); glVertex3f(-s,-s,-s);
    glTexCoord2f(1,0); glVertex3f( s,-s,-s);
    glTexCoord2f(1,1); glVertex3f( s,-s, s);
    glTexCoord2f(0,1); glVertex3f(-s,-s, s);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    if (height == 0) height = 1;
    glViewport(0, 0, width, height);
    float aspect = (float)width / (float)height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float fovy = 45.0f * (3.14159265f / 180.0f);
    float f = 1.0f / tanf(fovy / 2.0f);
    float zNear = 0.1f, zFar = 100.0f;
    float proj[16] = {
        f/aspect, 0, 0, 0,
        0, f, 0, 0,
        0, 0, (zFar + zNear) / (zNear - zFar), -1,
        0, 0, (2 * zFar * zNear) / (zNear - zFar), 0
    };
    glLoadMatrixf(proj);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    const char* image_path = "res/default.png";
    const char* window_title = "sillycube.c";

    for(int i=1; i<argc-1; ++i) {
        if(strcmp(argv[i], "--image") == 0)
            image_path = argv[i+1];
        else if(strcmp(argv[i], "--title") == 0)
            window_title = argv[i+1];
        else if(strcmp(argv[i], "--size") == 0)
            cube_size = atof(argv[i+1]);
    }

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, window_title, NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    framebuffer_size_callback(window, 640, 480);

    GLuint tex = load_texture(image_path);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.2f, 0.2f, 0.2f); // pastel pink background

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();
        glTranslatef(0, 0, -5);
        glRotatef(angle, 10, 10, 0);

        draw_cube(tex, cube_size);

        angle += 1.5f;
        if (angle > 360.0f) angle -= 360.0f;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
