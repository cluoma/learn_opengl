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
    std::vector<float> get_vertex_attribs();
private:
    // vertex attributes
    std::vector<float> v_;
    std::vector<float> n_;
    // indices
    std::vector<unsigned int> i_;
};



#endif //SPHERE_H
