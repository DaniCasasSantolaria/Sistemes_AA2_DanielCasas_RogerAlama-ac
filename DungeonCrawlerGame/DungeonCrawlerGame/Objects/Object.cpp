#include "Object.h"
#include "SpawnerObjects.h"
#include "../Nodes/INodeContent.h"
#include "../ConsoleControl/ConsoleControl.h"
#include <iostream>

void Object::PrintObject(Vector2 position)
{
	CC::Lock();
	CC::SetPosition(node->GetPosition().x, node->GetPosition().y);
	node->GetContent()->Draw(node->GetPosition());
	CC::Unlock();
}
