#include "Object.h"
#include "SpawnerObjects.h"
#include "../Nodes/INodeContent.h"
#include "../ConsoleControl/ConsoleControl.h"
#include <iostream>

void Object::PrintObject()
{
	CC::Lock();
	CC::SetPosition(node->GetPosition().x, node->GetPosition().y);
	node->GetContent()->Draw();
	CC::Unlock();
}
