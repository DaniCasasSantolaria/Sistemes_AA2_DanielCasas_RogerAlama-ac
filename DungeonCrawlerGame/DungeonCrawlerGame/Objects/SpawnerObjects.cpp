#include "SpawnerObjects.h"

void SpawnerObjects::SpawnObject(Node* node)
{
	node = object->GetNode();
	objectType = object->GetType();
	object = new Object(objectType, node);
}
