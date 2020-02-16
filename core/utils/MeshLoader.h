//
// Created by svirex on 03.02.2020.
//

#ifndef SANDBOX_MESHLOADER_H
#define SANDBOX_MESHLOADER_H

#include <vector>
#include <string>

#include "GL/glew.h"

class MeshLoader {
public:
  enum FileType {
    EOBJ,
    ETEST
  };

  bool load(const std::string &filePath, std::vector<GLfloat> &vertex, std::vector<GLuint> &indices);

private:
  FileType checkFileType(const std::string &filePath);
};

#endif // SANDBOX_MESHLOADER_H
