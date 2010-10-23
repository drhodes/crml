#include "test-macros.cc"

namespace scm {
	bool TestPoint(Scene* s) {
		std::string modulename = "Point";

		Point p1 = Point();		
		pass("Point default constructor");
		
		Point p2 = Point(1,2);
		pass("Point constructor, two ints");			

		ok( p2.X() == 1, "Point constructor, set x" )
		ok( p2.Y() == 2, "Point constructor, set y" )

		p2.X(0);
		ok( p2.X() == 0, "Point::x set mutation, set x")

		p2.Y(0);
		ok( p2.Y() == 0, "Point::y set mutation, set y")
		
		return true;
	}
}
