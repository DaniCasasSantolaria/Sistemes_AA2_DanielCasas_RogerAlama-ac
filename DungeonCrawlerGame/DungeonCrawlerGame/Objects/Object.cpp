#include "Object.h"
#include <stdlib.h>

Object::Object() {
	type = static_cast<ObjectType>(rand() % 2);
}