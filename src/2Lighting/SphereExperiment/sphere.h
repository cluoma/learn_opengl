//
// Created by colin on 11/19/23.
//

#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include <glm/glm.hpp>

class Sphere {
public:
    Sphere(int latSegs, int lonSegs);
    const std::vector<float> & get_vertices();
    const std::vector<unsigned int> & get_indices();

    // build a dense array of position and normals
    // p1.x, p1.y, p1.z, n1.x, n1.y, n1.z,
    // p2.x, ...
    std::vector<float> get_vertex_attribs(bool smoothNormals);

private:
    int latSegs_;
    int lonSegs_;
    // vertex attributes
    std::vector<float> v_;
    std::vector<float> n_;
    // indices
    std::vector<unsigned int> i_;
};



#endif //SPHERE_H
