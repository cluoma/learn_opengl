//
// Created by colin on 12/1/23.
//

#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "src/shader.h"
#include "src/Mesh.h"

class Model {
public:
    Model(const char * path)
    {
        loadModel(path);
    }
    void Draw(Shader & shader);

private:
    // model data
    vector<Mesh> meshes;
    std::string directory;
    vector<Texture> textures_loaded;

    void loadModel(const string& path);
    void processNode(aiNode * node, const aiScene * scene);
    Mesh processMesh(aiMesh * mesh, const aiScene * scene);
    vector<Texture> loadMaterialTextures(aiMaterial * mat, aiTextureType type, std::string typeName);
};



#endif //MODEL_H
