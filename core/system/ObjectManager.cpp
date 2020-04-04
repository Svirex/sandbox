//
// Created by svirex on 04.04.2020.
//

#include "ObjectManager.h"

#ifdef OBJECT_MANAGER

#include <iostream>
#include <sstream>

void OBJECT_MANAGER_CLASS::created() { ++mCreated; }
void OBJECT_MANAGER_CLASS::deleted() { ++mDeleted; }

void OBJECT_MANAGER_CLASS::getStatus() {
  std::ostringstream str;
  str << "CREATED: " << mCreated << " objects, \n"
      << "DELETED: " << mDeleted << " objects";
  std::cout << str.str();
}

OBJECT_MANAGER_CLASS OBJECT_MANAGER_OBJ;

#endif
