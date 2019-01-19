#pragma once
#undef min
#undef max
namespace Ti
{
	struct Vec2
	{
		union
		{
			float f[2];
			struct
			{
				float x;
				float y;
			};
		};

		Vec2();

		Vec2(float xy);
		Vec2(float x, float y);

		Vec2 operator+(const Vec2& v) const;
		Vec2 operator-(const Vec2& v) const;
		Vec2 operator*(const float value) const;

		Vec2 operator/(const float value) const;
		Vec2 operator%(const float value) const;
		Vec2 operator-() const;

		Vec2 fract() const;
		Vec2 floor() const;
		Vec2 sqrt() const;

		static Vec2 min(Vec2 a, Vec2 b);
		static Vec2 max(Vec2 a, Vec2 b);

		Vec2 operator*(const Vec2& vector) const;
		Vec2 operator/(const Vec2& vector) const;
		void operator+=(const Vec2& v);
		void operator-=(const Vec2& v);
		void operator*=(const float value);
		void operator*=(const Vec2 &value);

		bool operator==(const Vec2& other) const;
		bool operator!=(const Vec2& other) const;

		Vec2 Clamp(float min, float max);
	};

	struct Vec3
	{
		union
		{
			float f[3];
			struct
			{
				float x;
				float y;
				float z;
			};
		};

		Vec3();
		Vec3(float xyz);
		Vec3(Vec2 xy, float z);
		Vec3(float x, float y, float z);

		Vec3 operator+(const Vec3& v) const;
		Vec3 operator-(const Vec3& v) const;
		Vec3 operator*(const float value) const;

		Vec3 operator/(const float value) const;
		Vec3 operator%(const float value) const;
		Vec3 operator-() const;

		Vec3 operator*(const Vec3& vector) const;
		Vec3 operator/(const Vec3& vector) const;
		void operator+=(const Vec3& v);
		void operator-=(const Vec3& v);
		void operator*=(const float value);
		void operator*=(const Vec3 &value);

		Vec3 fract() const;
		Vec3 floor() const;
		Vec3 sqrt() const;

		static Vec3 min(Vec3 a, Vec3 b);
		static Vec3 max(Vec3 a, Vec3 b);

		Vec2 xy();
		void xy(Vec2 xy);

		Vec2 xz();
		void xz(Vec2 xz);

		Vec2 yz();
		void yz(Vec2 yz);

		Vec2 yx();
		void yx(Vec2 xy);

		Vec2 zx();
		void zx(Vec2 xz);

		Vec2 zy();
		void zy(Vec2 yz);

		Vec3 Cross(const Vec3& vector) const;
		float Dot(const Vec3& vector) const;
		float Magnitude() const;
		float SquareMagnitude() const;
		Vec3 Normalize() const;
		//Vec3 normalize() const;
		bool operator==(const Vec3& other) const;
		bool operator!=(const Vec3& other) const;

		Vec3 Clamp(float min, float max);
		Vec3 Slerp(float fact, const Vec3& r) const;
	};

	struct Vec4
	{
		union
		{
			float f[4];
			struct
			{
				float x;
				float y;
				float z;
				float w;
			};
		};

		Vec4();
		Vec4(Vec3 xyz, float w);
		Vec4(float xyzw);
		Vec4(float x, float y, float z, float w);

		Vec4 operator+(const Vec4& v) const;
		Vec4 operator-(const Vec4& v) const;
		Vec4 operator*(const float value) const;
		void operator*=(const Vec4 &value);

		Vec4 operator-() const;

		Vec4 operator*(const Vec4& vector) const;
		void operator+=(const Vec4& v);
		void operator-=(const Vec4& v);
		void operator*=(const float value);

		Vec4 fract() const;
		Vec4 floor() const;

		static Vec4 min(Vec4 a, Vec4 b);
		static Vec4 max(Vec4 a, Vec4 b);

		bool operator==(const Vec4& other) const;
		bool operator!=(const Vec4& other) const;

		Vec4 Clamp(float min, float max);
	};

}