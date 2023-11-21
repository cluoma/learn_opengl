//
// Created by colin on 11/19/23.
//

#include "sphere.h"

#include <iostream>
#include <glm/gtx/string_cast.hpp>

#define PI 3.1415962f

Sphere::Sphere(int latSegs, int lonSegs)
{
    float yInc = 2.0f / (float)(latSegs);
    float rotInc = (2.0f * PI) / (float)lonSegs;

    // bottom vertex
    glm::vec3 curVec = glm::vec3(0.0f, -1.0f, 0.0f);
    v_.push_back(curVec.x);
    v_.push_back(curVec.y);
    v_.push_back(curVec.z);

    float curRadius = curVec.z;
    for (int i = 1; i < latSegs; i++)
    {
        // increment latitude segment
        curVec.y += yInc;
        curVec.z = sqrt(1 - pow(curVec.y, 2.0f));
        curVec.x = 0.0f;
        curRadius = curVec.z;
        v_.push_back(curVec.x);
        v_.push_back(curVec.y);
        v_.push_back(curVec.z);

        printf("Starting layer %d:\n", i);
        std::cout << glm::to_string(curVec) << std::endl;

        float curTheta = 0.0f;
        for (int j = 0; j < lonSegs-1; j++)
        {
            curTheta += rotInc;
            curVec.x = sin(curTheta) * curRadius;
            curVec.z = cos(curTheta) * curRadius;
            v_.push_back(curVec.x);
            v_.push_back(curVec.y);
            v_.push_back(curVec.z);

            std::cout << glm::to_string(curVec) << std::endl;
            //std::cout << "Radius: " << pow(curVec.x, 2.0f) + pow(curVec.y, 2.0f) + pow(curVec.z, 2.0f) << std::endl;
        }
    }

    // top vertex
    curVec = glm::vec3(0.0f, 1.0f, 0.0f);
    v_.push_back(curVec.x);
    v_.push_back(curVec.y);
    v_.push_back(curVec.z);

    std::cout << v_.size() << std::endl;

    // build indices vector
    for (int i = 1; i < (v_.size() - (3*lonSegs + 6))/3; i++)
    {
        // first tri
        i_.push_back(i);
        i_.push_back(i + lonSegs);
        i_.push_back(i + lonSegs + 1);
        // second tri
        i_.push_back(i);
        i_.push_back(i + 1);
        i_.push_back(i + lonSegs + 1);
    }

    std::cout << "Indices" << std::endl;
    for (int i = 0; i < i_.size(); i++)
    {
        std::cout << i_.at(i) << std::endl;
    }

    std::cout << i_.size() << std::endl;
}

std::vector<float> & Sphere::get_vertices()
{
    return v_;
}

std::vector<int> & Sphere::get_indices()
{
    return i_;
}


