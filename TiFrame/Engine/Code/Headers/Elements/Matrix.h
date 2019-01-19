#pragma once
#include <string>
#include <Elements/Vector.h>
namespace Ti
{
	struct Transform
	{
		Transform()
		{
			position = Vec3(0,0,0);
			rotation = Vec3(0,0,0);
			scale	 = Vec3(0,0,0);
		}
		Transform(Vec3 _pos, Vec3 _rot, Vec3 _scale)
		{
			position = _pos; 
			rotation = _rot; 
			scale = _scale;
		}
		Vec3 position;
		Vec3 rotation;
		Vec3 scale;

		std::string GetTransformAsText()
		{
			return std::string(
				"Position: " + std::to_string(position.x) + ",  " + std::to_string(position.y) + ",  " + std::to_string(position.z) + "\n" +
				"Rotation: " + std::to_string(rotation.x) + ",  " + std::to_string(rotation.y) + ",  " + std::to_string(rotation.z) + "\n" +
				"Scale   : " + std::to_string(scale.x)    + ",  " + std::to_string(scale.y) + ",  "    + std::to_string(scale.z)    );
		};
	};
	//! Column major matrix 4 x 4
	/** 
	* m00 , m10 , m20 , m30
	* m01 , m11 , m21 , m31
	* m02 , m12 , m22 , m32
	* m03 , m13 , m23 , m33
	* f00 , f04 , f08 , f12
	* f01 , f05 , f09 , f13
	* f02 , f06 , f10 , f14
	* f03 , f07 , f11 , f15
	* m00 - m02 , f00 - f02 = xAxis
	* m10 - m12 , f04 - f06 = yAxis
	* m20 - m22 , f08 - f10 = zAxis
	* m30 - m32 , f12 - f14 = translation 
	*/
	struct Mat4
	{
		union
		{
			float m[4][4];
			float f[16];
			struct
			{
				Vec3 xAxis;
				float wx;
				Vec3 yAxis;
				float wy;
				Vec3 zAxis;
				float wz;
				Vec3 translation;
				float one;
			};
		};

		//! Construct a new matrix from explicit values
		Mat4(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33);

		//! Construct a new identity matrix
		Mat4();

		//! Transform the given vector by this matrix.
		Vec3 operator*(const Vec3& vec) const;
		Vec4 operator*(const Vec4& vec) const;
		Mat4 operator+(const Mat4& mat) const;
		Mat4 operator-(const Mat4& mat) const;
		Mat4 operator*(const Mat4& mat) const;

		//! Translation bit of the matrix
		Vec3 GetTranslation() const;
		//! Set the transltion of the matrix
		void SetTranslation(const Vec3& vec);
		//! Get the x orientation axis 
		Vec3 GetXAxis() const;
		//! Get the y orientation axis 
		Vec3 GetYAxis() const;
		//! Get the z orientation axis 
		Vec3 GetZAxis() const;
		//! Get the determinant of this matrix
		float Determinant() const;
		//! Inverts this matrix
		bool Invert();
		//! Transposes this matrix
		void Transpose();


		//! Sets the orientation of the matrix to the orthogonal basis vector
		//! It perfoms no checks on the orthogonality!
		void SetOrientation(const Vec3& x, const Vec3& y, const Vec3& z);

		//! Set orientation using Euler angles. Broken at current!
		static Mat4 CreateEulerAxis(float yaw, float pitch, float roll);

		//! Creates an identity matrix
		static Mat4 CreateIdentity();

		//! Creates an matrix based on a position, scale and rotation.
		static Mat4 CreateMatrix(Vec3 pos, Vec3 rot, Vec3 scale);

		//! Creates an matrix based on a position, scale and rotation (in degrees).
		static Mat4 CreateMatrixDeg(Vec3 pos, Vec3 drot, Vec3 scale);

		//! Creates a transation matrix
		static Mat4 CreateTranslation(Vec3 pos);

		//! Creates a scale matrix
		static Mat4 CreateScale(Vec3 scale);

		//! Creates a rotation matrix around an arbitrary axis
		static Mat4 CreateRotate(float angle, const Vec3& axis);

		//! Angle in radians
		static Mat4 CreateRotateX(float angle);

		//! Angle in radians
		static Mat4 CreateRotateY(float angle);

		//! Angle in radians
		static Mat4 CreateRotateZ(float angle);

		//! Creates an orthographic projection matrix
		static Mat4 CreateOrtho(float left, float right, float bottom, float top, float nearZ, float farZ);

		//! Creates a frustum projection matrix
		static Mat4 CreateFrustum(float left, float right, float bottom, float top, float nearZ, float farZ);

		//! Creates a perspective projection matrix from camera settings
		static Mat4 CreatePerspective(float fovy, float aspect, float nearZ, float farZ);

		//! Creates a look at matrix, usualy a view matrix  
		static Mat4 CreateLookAt(const Vec3& eye, const Vec3& center, const Vec3& up);

		//! Prints the whole matrix.
		static std::string Print();

		//! Transfrom just the direction
		Vec3 TransformDirectionVector(const Vec3& direction);
	};
}