#include "Exception.h"



Exception::Exception():
	message()
{
}


Exception::Exception(QString const & message):
	message(message)
{
}

Exception::~Exception() {
}

void Exception::display() const {
	std::cout << message.toStdString() << std::endl;
}
