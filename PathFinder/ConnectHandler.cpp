#include "ConnectHandler.h"
#include "Node.h"
#include "qcursor.h"
#include <iostream>

void ConnectHandler::grab(Node * n) {
	src = n;
}

Node * ConnectHandler::getSource() const {
	return src;
}

void ConnectHandler::release(Node * dest) {
	if (dest && src && (dest != src)) {
		float distance = ::distance(dest->pos(), src->pos());
		src->connect(dest, distance);
		dest->connect(src, distance);
		std::cout << "connected\n";
	}	
	src = nullptr;
}



ConnectHandler::ConnectHandler():
	src(nullptr)
{
}
