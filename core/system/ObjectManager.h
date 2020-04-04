//
// Created by svirex on 04.04.2020.
//

#ifndef SANDBOX_OBJECTMANAGER_H
#define SANDBOX_OBJECTMANAGER_H

#ifdef OBJECT_MANAGER

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

#define OBJECT_MANAGER_CLASS ObjectManager
#define OBJECT_MANAGER_OBJ objectManager

class OBJECT_MANAGER_CLASS {
public:
  //  OBJECT_MANAGER_CLASS() { std::cout << "OBJECT_MANAGER_NAME" << std::endl;
  //  }

  void created();

  void deleted();

  void getStatus();

private:
  int mCreated = 0;

  int mDeleted = 0;

  std::vector<std::string> mCreatedNames;

  std::vector<std::string> mDeletedNames;
};

extern OBJECT_MANAGER_CLASS OBJECT_MANAGER_OBJ;

#define MANAGE(CLASS)                                                          \
public:                                                                        \
  void *operator new(size_t s) {                                               \
    OBJECT_MANAGER_OBJ.created();                                              \
    void *obj = std::malloc(s);                                                \
    return obj;                                                                \
  }                                                                            \
                                                                               \
  void operator delete(void *obj) {                                            \
    OBJECT_MANAGER_OBJ.deleted();                                              \
    std::free(obj);                                                            \
  }

#define OBJECT_MANAGER_STAT OBJECT_MANAGER_OBJ.getStatus()

#else

#define OBJECT_MANAGER_CLASS
#define OBJECT_MANAGER_OBJ

#define MANAGE(CLASS)

#define OBJECT_MANAGER_STAT

#endif

#endif // SANDBOX_OBJECTMANAGER_H
