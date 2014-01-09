#ifndef MATHS_HPP
#define MATHS_HPP

#include <math.h>


// No sense in encapsulating this stuff right now


/* Vectors */

struct Vec2f {
	float x, y;
	
	Vec2f(float x=0, float y=0)
	: x(x), y(y) {}
	
	inline Vec2f operator+(const Vec2f &other) const {
		return Vec2f(x + other.x, y + other.y);
	}
	
	inline float norm() {
		return hypot(x, y);
	}
};


struct Vec3i {
	int x;
	int y;
	int z;
	
	Vec3i(int x=0, int y=0, int z=0)
	: x(x), y(y), z(z) {}
	
	inline Vec3i operator+(const Vec3i &other) const {
		return Vec3i(x + other.x, y + other.y, z + other.z);
	}
	
	inline Vec3i operator-(const Vec3i &other) const {
		return Vec3i(x - other.x, y - other.y, z - other.z);
	}
};


/* Fields */

template <typename T>
struct Field {
	T *values;
	int w, h;
	
	inline Field(int w, int h)
	: w(w), h(h) {
		values = new T[w * h];
	}
	
	inline ~Field() {
		delete values;
	}
	
	inline float &at(int x, int y) {
		return values[x + w * y];
	}
	
	inline float &atSafe(int x, int y) {
		// x86 sucks
		// Fix non-Euclidean integer division
		if (x < 0) {
			x += w;
		}
		if (y < 0) {
			y += h;
		}
		
		return at(x % w, y % h);
	}
	
	inline void clear(T value=T()) {
		for (int i = 0; i < w * h; i++) {
			values[i] = value;
		}
	}
};


struct Field2f : public Field<Vec2f> {
	// Inherit Field constructor
	using Field<Vec2f>::Field;
};


struct FieldF : public Field<float> {
	// Inherit Field constructor
	using Field<float>::Field;
	
	void print();
};


#endif