#include "model.h"
#include "math/vec3.h"
#include "aabb.h"

#include "spdlog/spdlog.h"


namespace hi{

Model::Model(const std::string& _path,unsigned int _primitive, bool _gammaCorrection, bool _showWire) 
    :Object(_primitive,_showWire), path(_path), gammaCorrection(_gammaCorrection),_aabb(AABB::New()) {
    loadModel();
}

void Model::loadModel() {
    // read file via ASSIMP
    Assimp::Importer importer;
    //const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);
    
    // check for errors
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        spdlog::error("ERROR::ASSIMP:: {}",importer.GetErrorString());
        return;
    }
    spdlog::info("Loading model: {}", path);
    // retrieve the directory path of the filepath
    directory = path.substr(0, path.find_last_of('/'));
    // process ASSIMP's root node recursively
    processNode(scene->mRootNode, scene);

    spdlog::debug("vertex count {}",v_count);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
    // process each mesh located at the current nodeDynamicPolytope::New
    if(!node || !scene)return;

    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene. 
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* ai_mesh = scene->mMeshes[node->mMeshes[i]];
        Mesh::Ptr polytope = processMesh(ai_mesh, scene); // may be freed?
        if(polytope.get()){
            add(polytope);
            spdlog::info("add polytope");
        }
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for(unsigned int i = 0; i < node->mNumChildren; i++) processNode(node->mChildren[i], scene);
}

Mesh::Ptr Model::processMesh(aiMesh *mesh, const aiScene *scene) {

    if(!mesh)return nullptr;
    // data to fill
    std::vector<Vec3f> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture::Ptr> textures;   

    //auto mesh_aabb = AABB::New(); 
    // walk through each of the mesh's vertices
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vec3f vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vertex.x = vector.x = mesh->mVertices[i].x;
        vertex.y = vector.y = mesh->mVertices[i].y;
        vertex.z = vector.z = mesh->mVertices[i].z;

        vertex.r = vertex.g = vertex.b = 1.0f;
        //spdlog::debug("vertex: {}, {}, {}", vertex.x, vertex.y, vertex.z);
        //mesh_aabb->expandBy(vertex);
        v_count++;
        _aabb->expandBy(vertex);// calculate model bounding box

        // // normals
        // if (mesh->HasNormals()) {
        //     vertex.nx = vector.x = mesh->mNormals[i].x;
        //     vertex.ny = vector.y = mesh->mNormals[i].y;
        //     vertex.nz = vector.z = mesh->mNormals[i].z;
        // }

        // // texture coordinates
        // if(mesh->mTextureCoords[0])  {
        //     glm::vec2 vec;
        //     // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
        //     // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
        //     vertex.tx = vec.x = mesh->mTextureCoords[0][i].x; 
        //     vertex.ty = vec.y = mesh->mTextureCoords[0][i].y;
        //     // tangent
        //     vertex.tanx = vector.x = mesh->mTangents[i].x;
        //     vertex.tany = vector.y = mesh->mTangents[i].y;
        //     vertex.tanz = vector.z = mesh->mTangents[i].z;
        //     // bitangent
        //     vertex.bitanx = vector.x = mesh->mBitangents[i].x;
        //     vertex.bitany = vector.y = mesh->mBitangents[i].y;
        //     vertex.bitanz = vector.z = mesh->mBitangents[i].z;

        //     vertex.hasTangents = true;
        // }
        // else vertex.tx = vertex.ty = 0.0f;

        
        vertices.push_back(vertex);
    }

    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        //spdlog::debug("face-{}: ", i);      
        for(unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);  
            //spdlog::debug("index: {}", face.mIndices[j]);      
        }
    }
    // process materials
    //aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];   

    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN

    // // 1. diffuse maps
    // std::vector<Texture::Ptr> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    // textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // // 2. specular maps
    // std::vector<Texture::Ptr>  specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    // textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // // 3. normal maps
    // std::vector<Texture::Ptr>  normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    // textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // // 4. height maps
    // std::vector<Texture::Ptr>  heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    // textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    // return a mesh object created from the extracted mesh data
    //Mesh::Ptr polytope = Mesh::New(vertices, indices, false);
    Mesh::Ptr polytope = Mesh::New(vertices, indices, false);
    //polytope->setFaceCulling(hi::Mesh::FaceCulling::NONE); // BACK default
    //for(auto& texture : textures) polytope->addTexture(texture);

    //polytope->setAabb(mesh_aabb);

    return polytope;
}

std::vector<Texture::Ptr> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName) {
    std::vector<Texture::Ptr> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);

        std::string texturePath = directory + "/" + str.C_Str();
        Texture::Ptr texture = Texture::New(texturePath, Texture::Type::None, false);
        if(typeName == "texture_ambient") texture->setType(Texture::Type::TextureAmbient);
        else if(typeName == "texture_diffuse") texture->setType(Texture::Type::TextureDiffuse);
        else if(typeName == "texture_specular") texture->setType(Texture::Type::TextureSpecular);
        else if(typeName == "texture_height") texture->setType(Texture::Type::TextureHeight);
        else if(typeName == "texture_normal") texture->setType(Texture::Type::TextureNormal);

        bool contained = false;
        for(auto& tex : textures) {
            if(tex->getPath() == texture->getPath()) {
                contained = true;
                break;
            }
        }
        if(!contained) textures.push_back(texture);
    }
    return textures;
}

}