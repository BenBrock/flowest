#ifndef VECTOR_HPP
#define VECTOR_HPP

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

#endif