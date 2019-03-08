#pragma once

#include <qline.h>
#include "tools.h"

class Node;

class ConnectHandler
{
	Node* src;

public:
	void grab(Node* src);
	Node* getSource() const;
	void release(Node* dest);
	ConnectHandler();
	
};

