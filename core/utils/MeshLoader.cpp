//
// Created by svirex on 03.02.2020.
//

#include <algorithm>
#include <unordered_map>
#include <utility>

#define TINYOBJLOADER_IMPLEMENTATION
#include <SDL2/SDL.h>
#include <tiny_obj_loader.h>

#include "MeshLoader.h"

struct pair_hash
{
  template <class T1, class T2>
  std::size_t operator() (const std::pair<T1, T2> &pair) const
  {
    return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
  }
};

bool MeshLoader::load(const std::string &filePath, std::vector<GLfloat> &vertex,
                      std::vector<GLuint> &indices) {
  auto fileType = checkFileType(filePath);
  if (fileType == EOBJ) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    bool result = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err,
                                   filePath.c_str());
    if (!result) {
      SDL_Log("Couldnt open mesh file %s", filePath.c_str());
      return false;
    }

    std::unordered_map<std::pair<int, int>, GLuint, pair_hash> vertNormToIndex;
    GLuint index = 0;

    for (auto &shape : shapes) {
      // Loop over faces(polygon)
      size_t index_offset = 0;
      for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); ++f) {
        int fv = shape.mesh.num_face_vertices[f];

        // Loop over vertices in the face.
        for (size_t v = 0; v < fv; v++) {
          tinyobj::index_t idx = shape.mesh.indices[index_offset + v];
          auto vertNormPair = std::make_pair(idx.vertex_index, idx.normal_index);
          auto iter = vertNormToIndex.find(vertNormPair);
          if (iter != vertNormToIndex.end()) {
            indices.emplace_back(iter->second);
          } else {
            vertex.emplace_back(attrib.vertices[3 * idx.vertex_index + 0]);
            vertex.emplace_back(attrib.vertices[3 * idx.vertex_index + 1]);
            vertex.emplace_back(attrib.vertices[3 * idx.vertex_index + 2]);

            vertex.emplace_back(attrib.normals[3 * idx.normal_index + 0]);
            vertex.emplace_back(attrib.normals[3 * idx.normal_index + 1]);
            vertex.emplace_back(attrib.normals[3 * idx.normal_index + 2]);
            indices.emplace_back(index);

            vertNormToIndex[vertNormPair] = index;
            ++index;
          }
        }
        index_offset += fv;
      }
    }
  } else if (fileType == ETEST) {
    vertex = std::vector<GLfloat>({
//      -0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
//      0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f,
//      0.5f, 1.0f, 0.5f, 0.0f, 1.0f, 0.0f,
//      -0.5f, 1.0f, 0.5f, 1.0f, 0.0f, 0.0f,
//      -0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 0.0f,
//      0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 0.0f,
//      0.5f, 1.0f, -0.5f, 0.0f, 0.0f, 0.0f,
//      -0.5f, 1.0f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
    });

    indices = std::vector<GLuint>({
        0,2,1,
//        0,3,2,
//        5,1,2,
//        5,6,2,
//        5,4,7,
//        5,6,7,
//        0,4,7,
//        0,3,7,
//        3,2,6,
//        3,7,6,
//        0,1,5,
//        0,4,5
    });
  }

  return true;
}

MeshLoader::FileType MeshLoader::checkFileType(const std::string &filePath) {
  return EOBJ;
}
