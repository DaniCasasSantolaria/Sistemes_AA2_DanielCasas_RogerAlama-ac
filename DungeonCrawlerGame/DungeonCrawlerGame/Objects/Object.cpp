#include "Object.h"
#include "SpawnerObjects.h"
#include "../Nodes/INodeContent.h"
#include "../ConsoleControl/ConsoleControl.h"
#include <iostream>

void Object::Draw() {
	CC::Lock();
	CC::SetPosition(node->GetPosition().x, node->GetPosition().y);
	node->DrawContent();
	CC::Unlock();
}

void Object::SetNode(Node* node)
{
	this->node = node;
}

