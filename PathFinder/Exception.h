#pragma once

#include <qstring.h>
#include <iostream>

class Exception
{
public:
	QString const message;

	Exception();
	Exception(QString const& message);
	virtual ~Exception();
	void display() const;
};

