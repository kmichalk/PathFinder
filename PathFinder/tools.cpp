#include "tools.h"


float veclength(QPoint const & p) {
	float x = float(p.x());
	float y = float(p.y());
	return sqrt(x*x+y*y);
}

float distance(QPoint const & p1, QPoint const & p2) {
	return veclength(p2-p1);
}
