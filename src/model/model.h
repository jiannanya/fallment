#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "glad/glad.h"

#include "texture/texture.h"
#include "material/material.h"
#include "mesh.h"
#include "object.h"
#include "aabb.h"



namespace hi{

class Model: public Object{
    MAKE_PTR(Model)
private:
    std::string directory, path;
    std::vector<Texture::Ptr> texturesLoaded;
    bool gammaCorrection;

    AABB::Ptr _aabb;

public:
    Model(const std::string& _path,unsigned int _primitive, bool _gammaCorrection = false, bool _showWire = false);
    Model() = default;

public:
    AABB::Ptr& getAabb(){return _aabb;}
    void setAabb(AABB::Ptr ab){_aabb = ab;}

private:
    long long v_count = 0;
    void loadModel();
    void processNode(aiNode *node, const aiScene *scene);
    Mesh::Ptr processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture::Ptr> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName);
};

}