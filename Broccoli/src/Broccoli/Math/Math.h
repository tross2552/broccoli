#pragma once

#include <blaze/Blaze.h>

//simple wrapper around blaze library, to be extended over time

namespace brcl
{
	
	typedef blaze::StaticVector<float, 2> Vector2;
	typedef blaze::StaticVector<float, 3> Vector3;
	typedef blaze::StaticVector<float, 4> Vector4;

	typedef blaze::StaticMatrix<float, 2, 2> Matrix2x2;
	typedef blaze::StaticMatrix<float, 3, 3> Matrix3x3;
	typedef blaze::StaticMatrix<float, 4, 4> Matrix4x4;

	inline float Distance(Vector2 a, Vector2 b)
	{
		return blaze::l2Norm(b - a);
	}

	inline float Distance(Vector3 a, Vector3 b)
	{
		return blaze::l2Norm(b - a);
	}

	inline float Dot(Vector2 a, Vector2 b)
	{
		return blaze::dot(a, b);
	}

	inline float Dot(Vector3 a, Vector3 b)
	{
		return blaze::dot(a, b);
	}

	inline Matrix2x2 Identity2x2()
	{
		return blaze::IdentityMatrix<float>(2);
		//return Matrix2x2({ {1,0}, {0,1} });
	}

	inline Matrix3x3 Identity3x3()
	{
		return blaze::IdentityMatrix<float>(3);
		//return Matrix3x3({ {1,0,0}, {0,1,0}, {0,0,1} });
	}

	inline Matrix4x4 Identity4x4()
	{
		return blaze::IdentityMatrix<float>(4);
		//return Matrix4x4({ {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} });
	}
	
	inline Matrix4x4 Ortho(float left, float right, float bottom, float top) {

		//assume near = -1f and far = 1f;
		
		Matrix4x4 ret = Identity4x4();

		ret(0,0) = 2.0f / (right - left);
		ret(1,1) = 2.0f / (top - bottom);
		ret(2,2) = 1.0f / 2.0f;
		
		ret(3,0) = -(right + left) / (right - left);
		ret(3,1) = -(top + bottom) / (top - bottom);
		ret(3, 2) = 1.0f / 2.0f;
		
		return ret;
	}
	
	inline Matrix4x4 Translate(const Matrix4x4& m, const Vector3& v)
	{
		auto ret = m;
		
		ret(0, 3) = blaze::sum(blaze::column(m,0)* v[0]);
		ret(1, 3) = blaze::sum(blaze::column(m, 1) * v[1]);
		ret(2, 3) = blaze::sum(blaze::column(m, 2) * v[2]);

		return ret;
	}

	inline Matrix4x4 Scale(const Matrix4x4& m, const float scale)
	{
		auto ret = m;

		blaze::row(ret, 0) *= scale;
		blaze::row(ret, 1) *= scale;
		blaze::row(ret, 2) *= scale;

		return ret;
	}

	inline Matrix4x4 Scale(const Matrix4x4& m, const Vector2& v)
	{
		auto ret = m;

		blaze::column(ret, 0) *= v[0];
		blaze::column(ret, 1) *= v[1];

		return ret;
	}

	inline Matrix4x4 Scale(const Matrix4x4& m, const Vector3& v)
	{
		auto ret = m;

		blaze::column(ret, 0) *= v[0];
		blaze::column(ret, 1) *= v[1];
		blaze::column(ret, 2) *= v[2];

		return ret;
	}

	//TODO: quaternions
	inline Matrix4x4 Rotate(const Matrix4x4& m, const Vector3& euler)
	{
		Matrix4x4 rotate = Identity4x4();
		

		//TODO: this math needs fixed
		
		auto& [x, y, z] = euler;

		rotate(0,0) =  cos(z) * cos(y);
		rotate(1,0) =  sin(z) * cos(y);
		rotate(2,0) = -sin(y);

		rotate(0, 1) = cos(z) * sin(y) * sin(x) - sin(z) * cos(x);
		rotate(1, 1) = sin(z) * sin(y) * sin(x) + cos(z) * cos(x);
		rotate(2, 1) = cos(y) * sin(x);

		rotate(0, 2) = cos(z) * sin(y) * cos(x) + sin(z) * sin(x);
		rotate(1, 2) = sin(z) * sin(y) * cos(x) - cos(z) * sin(x);
		rotate(2, 2) = cos(y) * cos(x);

		return rotate * m;
	}


	inline Matrix4x4 Rotate(const Matrix4x4& m, float angle, const Vector3& v)
	{
		
		Matrix4x4 rotate;

		Vector3 axis = blaze::normalize(v);

		auto&[x, y, z] = axis;

		//TODO: check this math

		rotate(0,0) = cos(angle) + (1.0f - cos(angle)) * x * x;
		rotate(1,0) = (1.0f - cos(angle)) * x * y + sin(angle) * z;
		rotate(2,0) = (1.0f - cos(angle)) * x * z - sin(angle) * y;
		rotate(3,0) = 0.0f;

		rotate(0,1) = (1.0f - cos(angle)) * y * x - sin(angle) * z;
		rotate(1,1) = cos(angle) + (1.0f - cos(angle)) * y * y;
		rotate(2,1) = (1.0f - cos(angle)) * y * z + sin(angle) * x;
		rotate(3,1) = 0.0f;

		rotate(0,2) = (1.0f - cos(angle)) * z * x + sin(angle) * y;
		rotate(1,2) = (1.0f - cos(angle)) * z * y - sin(angle) * x;
		rotate(2,2) = cos(angle) + (1.0f - cos(angle)) * z * z;
		rotate(3,2) = 0.0f;

		rotate(0,3) = 0.0f;
		rotate(1,3) = 0.0f;
		rotate(2,3) = 0.0f;
		rotate(3,3) = 1.0f;

		
		return rotate * m;
	}
	
	inline Matrix2x2 Invert(const Matrix2x2& mat)
	{
		return blaze::inv(mat);
	}

	inline Matrix3x3 Invert(const Matrix3x3& mat)
	{
		return blaze::inv(mat);
	}

	inline Matrix4x4 Invert(const Matrix4x4& mat)
	{
		return blaze::inv(mat);
	}
	
	
}