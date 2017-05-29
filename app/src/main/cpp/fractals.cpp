#include "fractals.h"

vertex triangle[3] = {
        {-1.0f, 1.0f},
        {1.0f,  1.0f},
        {0.0f,  -1.0f},
};

int half_way(GLfloat point[], GLfloat a[], GLfloat new_point[]) {
    if (point != NULL) {
        new_point[0] = (point[0] + a[0]) / 2;
        new_point[1] = (point[1] + a[1]) / 2;
        return 1;
    }
    return 0;
}

int
recurse_triangles(GLfloat point[], GLfloat a[], GLfloat b[], GLfloat c[],
                  int iteration, int size_of_points, vertex points_to_draw[]) {
    int x = rand() % 3 + 1; //returns 1 to 3
    if (iteration == size_of_points) {
        std::cout << iteration << std::endl;
        return iteration;
    }
    if (x == 1) {
        half_way(point, a, points_to_draw[iteration].pos);
    }
    if (x == 2) {
        half_way(point, b, points_to_draw[iteration].pos);
    }
    if (x == 3) {
        half_way(point, c, points_to_draw[iteration].pos);
    }
    return recurse_triangles(points_to_draw[iteration].pos, a, b, c, ++iteration, size_of_points,
                             points_to_draw);
}


//not going to use dynamic allocation because
// the heap space is already being used a lot by the gl
void drawTriangle(vertex points_to_draw[], int size_of_points) {
    recurse_triangles(triangle[0].pos, triangle[0].pos, triangle[1].pos,
                      triangle[2].pos, 0, size_of_points, points_to_draw);
}




