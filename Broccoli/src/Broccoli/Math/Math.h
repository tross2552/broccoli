#pragma once

#include <blaze/Blaze.h>

namespace brcl
{
	
	typedef blaze::StaticVector<float, 2> Vector2;
	typedef blaze::StaticVector<float, 3> Vector3;
	typedef blaze::StaticVector<float, 4> Vector4;

	typedef blaze::StaticMatrix<float, 2, 2> Matrix2x2;
	typedef blaze::StaticMatrix<float, 3, 3> Matrix3x3;
	typedef blaze::StaticMatrix<float, 4, 4> Matrix4x4;

	//TODO: make explicit that these functions use homogenous coordinates
	
	inline Matrix4x4 Ortho(float left, float right, float bottom, float top) {

		//assume near = -1f and far = 1f;
		
		auto ret = static_cast<Matrix4x4>(blaze::IdentityMatrix<float>(4));

		ret(0,0) = 2.0f / (right - left);
		ret(1,1) = 2.0f / (top - bottom);
		ret(2,2) = -1.0f;
		ret(3,0) = -(right + left) / (right - left);
		ret(3,1) = -(top + bottom) / (top - bottom);
		
		return ret;
	}

	inline Matrix4x4 Translate(const Matrix4x4& m, const Vector3& v)
	{
		auto ret = m;
		
		ret(0, 3) = v[0];
		ret(1, 3) = v[1];
		ret(2, 3) = v[2];

		return ret;
	}

	inline Matrix4x4 Scale(const Matrix4x4& m, const Vector3& v)
	{
		auto ret = m;

		ret(0, 0) *= v[0];
		ret(1, 1) *= v[1];
		ret(2, 2) *= v[2];

		return ret;
	}

	//TODO: implement
	inline Matrix4x4 Rotate(const Matrix4x4& m, float angle, const Vector3& v)
	{
		
		Matrix4x4 ret;

		Vector3 axis = blaze::normalize(v);

		auto&[x, y, z] = axis;

		ret(0,0) = cos(angle) + (1.0f - cos(angle)) * x * x;
		ret(1,0) = (1.0f - cos(angle)) * x * y + sin(angle) * z;
		ret(2,0) = (1.0f - cos(angle)) * x * z - sin(angle) * y;
		ret(3,0) = 0.0f;

		ret(0,1) = (1.0f - cos(angle)) * y * x - sin(angle) * z;
		ret(1,1) = cos(angle) + (1.0f - cos(angle)) * y * y;
		ret(2,1) = (1.0f - cos(angle)) * y * z + sin(angle) * x;
		ret(3,1) = 0.0f;

		ret(0,2) = (1.0f - cos(angle)) * z * x + sin(angle) * y;
		ret(1,2) = (1.0f - cos(angle)) * z * y - sin(angle) * x;
		ret(2,2) = cos(angle) + (1.0f - cos(angle)) * z * z;
		ret(3,2) = 0.0f;

		ret(0,3) = 0.0f;
		ret(1,3) = 0.0f;
		ret(2,3) = 0.0f;
		ret(3,3) = 1.0f;

		
		return m * ret;
	}

	inline Matrix2x2 Identity2x2()
	{
		return Matrix2x2({ {1,0}, {0,1} });
	}
	
	inline Matrix3x3 Identity3x3()
	{
		return Matrix3x3({ {1,0,0}, {0,1,0}, {0,0,1} });
	}
	
	inline Matrix4x4 Identity4x4()
	{
		return Matrix4x4({ {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} });
	}
	
	
}