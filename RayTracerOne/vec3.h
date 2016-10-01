#pragma once

#include <iostream>
#include <cmath>

inline float frand() { return float(std::rand() % 10000) / 10000.0f; }

class vec3 {
public:
	vec3() {}
	vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }

	inline float x() const { return e[0]; }
	inline float y() const { return e[1]; }
	inline float z() const { return e[2]; }

	inline float r() const { return e[0]; }
	inline float g() const { return e[1]; }
	inline float b() const { return e[2]; }

	inline const vec3& operator+() const { return *this; }
	inline vec3 operator-() const { return vec3{ -x(), -y(), -z() }; }
	inline float operator[](int i) const { return e[i]; }
	inline float& operator[](int i) { return e[i]; }

	inline float length() const { return std::sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
	inline float squared_length() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }

	float e[3];
	void make_unit_vector();
	vec3 & operator+=(const vec3 & other);
	vec3 & operator-=(const vec3 & other);
	vec3 & operator*=(const vec3 & other);
	vec3 & operator/=(const vec3 & other);
	vec3 & operator*=(float other);
	vec3 & operator/=(float other);

	static vec3 random_unit_vector() {
		vec3 res;
		do {
			res = vec3(
				2.0f * frand() - 1.0f,
				2.0f * frand() - 1.0f,
				2.0f * frand() - 1.0f
			);
		} while (res.length() >= 1.0f);
		return res;
	}
};

inline std::istream& operator >> (std::istream &is, vec3 &v) {
	is >> v.e[0] >> v.e[1] >> v.e[2];
	return is;
}

inline std::ostream& operator << (std::ostream &os, const vec3 &v) {
	os << "(" << v.e[0] << "," << v.e[1] << "," << v.e[2] << ")";
	return os;
}

inline void vec3::make_unit_vector() {
	float k = 1.0f / std::sqrtf(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	e[0] *= k; e[1] *= k; e[2] *= k;
}

inline vec3 operator + (const vec3 &left, const vec3 &right) {
	return vec3(left.e[0] + right.e[0], left.e[1] + right.e[1], left.e[2] + right.e[2]);
}

inline vec3 operator - (const vec3 &left, const vec3 &right) {
	return vec3(left.e[0] - right.e[0], left.e[1] - right.e[1], left.e[2] - right.e[2]);
}

inline vec3 operator * (const vec3 &left, const vec3 &right) {
	return vec3(left.e[0] * right.e[0], left.e[1] * right.e[1], left.e[2] * right.e[2]);
}

inline vec3 operator / (const vec3 &left, const vec3 &right) {
	return vec3(left.e[0] / right.e[0], left.e[1] / right.e[1], left.e[2] / right.e[2]);
}

inline vec3 operator*(float left, const vec3 &right) {
	return vec3(left * right.e[0], left * right.e[1], left * right.e[2]);
}

inline vec3 operator * (const vec3 &left, float right) {
	return vec3(left.e[0] * right, left.e[1] * right, left.e[2] * right);
}

inline vec3 operator / (const vec3 &left, const float &right) {
	return vec3(left.e[0] / right, left.e[1] / right, left.e[2] / right);
}

inline float dot(const vec3 &left, const vec3 &right) {
	return left.e[0] * right.e[0] + left.e[1] * right.e[1] + left.e[2] * right.e[2];
}

inline vec3 cross(const vec3 &left, const vec3 &right) {
	return vec3(
		left.e[1] * right.e[2] - left.e[2] * right.e[1],
		left.e[2] * right.e[0] - left.e[0] * right.e[2],
		left.e[0] * right.e[1] - left.e[1] * right.e[0]
	);
}

inline vec3& vec3::operator += (const vec3 &other) {
	e[0] += other.e[0];
	e[1] += other.e[1];
	e[2] += other.e[2];
	return *this;
}

inline vec3& vec3::operator -= (const vec3 &other) {
	e[0] -= other.e[0];
	e[1] -= other.e[1];
	e[2] -= other.e[2];
	return *this;
}

inline vec3& vec3::operator *= (const vec3 &other) {
	e[0] *= other.e[0];
	e[1] *= other.e[1];
	e[2] *= other.e[2];
	return *this;
}

inline vec3& vec3::operator /= (const vec3 &other) {
	e[0] /= other.e[0];
	e[1] /= other.e[1];
	e[2] /= other.e[2];
	return *this;
}

inline vec3& vec3::operator *= (float other) {
	e[0] *= other;
	e[1] *= other;
	e[2] *= other;
	return *this;
}

inline vec3& vec3::operator /= (float other) {
	e[0] /= other;
	e[1] /= other;
	e[2] /= other;
	return *this;
}

inline vec3 unit_vector(const vec3 &v) {
	return v / v.length();
}
