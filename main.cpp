//
//  main.cpp
//  MandelbrotOpenGL
//
//  Created by Mark Tselikov on 05.02.17.
//  Copyright © 2017 Mark Tselikov. All rights reserved.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

const double HEIGHT = 3000.0;
const double WIDTH = 3000.0;
const int ITERATIONS = 150; //100 default
const int RES_HEIGHT = 800;
const int RES_WIDTH = 800;


void render(double xCoordStart, double yCoordStart, double zoomScale) {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    for(int i = 0; i < WIDTH; i++) {
        for(int j = 0; j < HEIGHT; j++) {
    
            double x = (i * 1.0 / WIDTH * 4.0 - 2.0) / zoomScale + xCoordStart;
            double y = (j * 1.0 / HEIGHT * 4.0 - 2.0) / zoomScale + yCoordStart;
            const double X_INIT = x;
            const double Y_INIT = y;
            int n = 0;
            bool check = true;
            double scale = 0.0;
                        
            while(n < ITERATIONS) {
                
                double xTemp =  X_INIT + (x * x - y * y);
                double yTemp = Y_INIT + (2 * x * y);
                x = xTemp;
                y = yTemp;
                
                //if a point is not in the pure mandelbrot set, we can still color it in a shade
                if(fabs(x * x + y * y) > 4.0) {
                    check = false;
                    scale = (double)n / (double)ITERATIONS;
                    glBegin(GL_POINTS);
                    {
                        double x_coord = i / HEIGHT * 2.0 - 1.0;
                        double y_coord = j / WIDTH * 2.0 - 1.0;
                        glColor3d(scale, scale / 4, scale / 3);
                        glVertex2d(x_coord, y_coord);
                    }
                    glEnd();
                    break;
                }
                n++;
            } //while
            
            //if a point is in the set, it is colored white
            if(check) {
                glBegin(GL_POINTS);
                {
                    glColor3d(1.0, 1.0, 1.0);
                    double x_coord = i / HEIGHT * 2.0 - 1.0;
                    double y_coord = j / WIDTH * 2.0 - 1.0;
                    glVertex2d(x_coord, y_coord);
                }
            } //if
        }
    } //for end
} //render


int main(int argc, const char * argv[]) {
    
    GLFWwindow* win;
    if(!glfwInit()) { return -1; }
    
    win = glfwCreateWindow(RES_WIDTH, RES_HEIGHT, "Mandelbrot Set", NULL, NULL);
    if(!win) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    if(!glewInit()) { return -1; }
    glfwMakeContextCurrent(win);
    
    while(!glfwWindowShouldClose(win)) {
        
        //render(-0.83, 0.23, 1000.0);
        //render(-0.832, 0.23, 200000.0);
        //render(-0.101, 0.955, 5000.0);
        render(0.3, 0.018, 5000.0);
        //render(-1.12153, 0.30053, 10000.0);
        //render(-0.59, 0.0, 4.0); //NOT WORKING FOR SOME REASON
        //render(-1.411, 0.01, 50.0);
        //render(-1.40275, 0.02945, 200000.0);
        //render(0.0, 0.0, 1.0);
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
    
    glfwTerminate();
    exit(EXIT_SUCCESS);
    
    return 0;
}
