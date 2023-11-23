//
// Created by colin on 11/19/23.
//

#include "sphere.h"

#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/normal.hpp>

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
    // for (unsigned int i = 1; i < (v_.size() - (3*lonSegs + 6))/3; i++)
    // {
    //     // first tri
    //     i_.push_back(i);
    //     i_.push_back(i + lonSegs);
    //     i_.push_back(i + lonSegs + 1);
    //     // second tri
    //     i_.push_back(i);
    //     i_.push_back(i + 1);
    //     i_.push_back(i + lonSegs + 1);
    // }

    int s1, s2, k1, k2;
    for(int i = 0; i < latSegs-2; i++)
    {
        // beginning of current stack
        s1 = i * (lonSegs) + 1;
        k1 = s1;
        // beginning of next stack
        s2 = k1 + lonSegs;
        k2 = s2;
        printf("k1: %d, k2: %d\n", k1, k2);

        for(int j = 0; j < lonSegs; j++, k1++, k2++)
        {
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            int k1_next = k1 + 1;
            int k2_next = k2 + 1;
            if (j == lonSegs - 1)
            {
                k1_next = s1;
                k2_next = s2;
            }
                i_.push_back(k1);
                i_.push_back(k2);
                i_.push_back(k2_next);

            // k1+1 => k2 => k2+1
                i_.push_back(k1);
                i_.push_back(k1_next);
                i_.push_back(k2_next);
        }
    }

    std::cout << "Indices" << std::endl;
    for (unsigned int i : i_)
    {
        std::cout << i << std::endl;
    }

    std::cout << i_.size() << std::endl;
}

const std::vector<float> & Sphere::get_vertices()
{
    return v_;
}

const std::vector<unsigned int> & Sphere::get_indices()
{
    return i_;
}

std::vector<float> Sphere::get_vertex_attribs()
{
    std::vector<float> a_;
    for (int i = 0; i < i_.size(); i+=3)
    {
        printf("i: %u\n", i);
        // normals
        glm::vec3 norm = glm::triangleNormal(
            glm::vec3(v_.at(i_.at(i)*3), v_.at(i_.at(i)*3+1), v_.at(i_.at(i)*3+2)),
            glm::vec3(v_.at(i_.at((i+1))*3), v_.at(i_.at(i+1)*3+1), v_.at(i_.at(i+1)*3+2)),
            glm::vec3(v_.at(i_.at((i+2))*3), v_.at(i_.at(i+2)*3+1), v_.at(i_.at(i+2)*3+2))
            );
        if (i % 2 == 0)
        {
            norm = (-1.0f) * norm;
        }
        for (int j = 0; j < 3; j++)
        {
            // position
            a_.push_back(v_.at(i_.at(i+j)*3));
            a_.push_back(v_.at(i_.at(i+j)*3+1));
            a_.push_back(v_.at(i_.at(i+j)*3+2));
            // normal
            a_.push_back(norm.x);
            a_.push_back(norm.y);
            a_.push_back(norm.z);
        }
    }
    return a_;
}