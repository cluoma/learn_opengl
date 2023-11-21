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
    std::vector<float> & get_vertices();
    std::vector<int> & get_indices();
private:
    std::vector<float> v_;
    std::vector<int> i_;
    std::vector<glm::vec3> n_;
};



#endif //SPHERE_H
