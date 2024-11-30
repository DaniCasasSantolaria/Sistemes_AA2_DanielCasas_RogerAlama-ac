#include "Object.h"
#include "SpawnerObjects.h"
#include "../Nodes/INodeContent.h"
#include "../ConsoleControl/ConsoleControl.h"
#include <iostream>

void Object::Draw() {
	node->DrawContent(node->GetPosition());
}

void Object::SetNode(Node* node)
{
	this->node = node;
}

