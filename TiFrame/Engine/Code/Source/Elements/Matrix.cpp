#include <Elements/Matrix.h>
#include <Static/Math.h>
using namespace Ti;

// COLUMN MAJOR MATRIX
// m00 , m10 , m20 , m30
// m01 , m11 , m21 , m31
// m02 , m12 , m22 , m32
// m03 , m13 , m23 , m33

// f00 , f04 , f08 , f12
// f01 , f05 , f09 , f13
// f02 , f06 , f10 , f14
// f03 , f07 , f11 , f15

// m00 - m02 , f00 - f02 = xAxis
// m10 - m12 , f04 - f06 = yAxis
// m20 - m22 , f08 - f10 = zAxis
// m30 - m32 , f12 - f14 = translation

Mat4::Mat4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33) {
	m[0][0] = m00;	 m[1][0] = m10;	 m[2][0] = m20;	 m[3][0] = m30;
	m[0][1] = m01;	 m[1][1] = m11;	 m[2][1] = m21;	 m[3][1] = m31;
	m[0][2] = m02;	 m[1][2] = m12;	 m[2][2] = m22;	 m[3][2] = m32;
	m[0][3] = m03;	 m[1][3] = m13;	 m[2][3] = m23;	 m[3][3] = m33;
}

Mat4::Mat4() {
	m[0][0] = 1.f;	 m[1][0] = 0.f;	 m[2][0] = 0.f;	 m[3][0] = 0.f;
	m[0][1] = 0.f;	 m[1][1] = 1.f;	 m[2][1] = 0.f;	 m[3][1] = 0.f;
	m[0][2] = 0.f;	 m[1][2] = 0.f;	 m[2][2] = 1.f;	 m[3][2] = 0.f;
	m[0][3] = 0.f;	 m[1][3] = 0.f;	 m[2][3] = 0.f;	 m[3][3] = 1.f;
}

Vec3 Mat4::operator*(const Vec3 & vec) const {
	return Vec3(
		vec.x * m[0][0] + vec.y * m[1][0] + vec.z * m[2][0] + m[3][0],
		vec.x * m[0][1] + vec.y * m[1][1] + vec.z * m[2][1] + m[3][1],
		vec.x * m[0][2] + vec.y * m[1][2] + vec.z * m[2][2] + m[3][2]
	);
}

Vec4 Mat4::operator*(const Vec4 & vec) const {
	return Vec4(
		(vec.x * m[0][0]) + (vec.y * m[1][0]) + (vec.z * m[2][0]) + (vec.w * m[3][0]),
		(vec.x * m[0][1]) + (vec.y * m[1][1]) + (vec.z * m[2][1]) + (vec.w * m[3][1]),
		(vec.x * m[0][2]) + (vec.y * m[1][2]) + (vec.z * m[2][2]) + (vec.w * m[3][2]),
		(vec.x * m[0][3]) + (vec.y * m[1][3]) + (vec.z * m[2][3]) + (vec.w * m[3][3]));
}

Mat4 Mat4::operator+(const Mat4 & mat) const {
	return Mat4(
		m[0][0] + mat.m[0][0], m[0][1] + mat.m[0][1], m[0][2] + mat.m[0][2], m[0][3] + mat.m[0][3],
		m[1][0] + mat.m[1][0], m[1][1] + mat.m[1][1], m[1][2] + mat.m[1][2], m[1][3] + mat.m[1][3],
		m[2][0] + mat.m[2][0], m[2][1] + mat.m[2][1], m[2][2] + mat.m[2][2], m[2][3] + mat.m[2][3],
		m[3][0] + mat.m[3][0], m[3][1] + mat.m[3][1], m[3][2] + mat.m[3][2], m[3][3] + mat.m[3][3]
	);
}

Mat4 Mat4::operator-(const Mat4 & mat) const {
	return Mat4(
		m[0][0] - mat.m[0][0], m[0][1] - mat.m[0][1], m[0][2] - mat.m[0][2], m[0][3] - mat.m[0][3],
		m[1][0] - mat.m[1][0], m[1][1] - mat.m[1][1], m[1][2] - mat.m[1][2], m[1][3] - mat.m[1][3],
		m[2][0] - mat.m[2][0], m[2][1] - mat.m[2][1], m[2][2] - mat.m[2][2], m[2][3] - mat.m[2][3],
		m[3][0] - mat.m[3][0], m[3][1] - mat.m[3][1], m[3][2] - mat.m[3][2], m[3][3] - mat.m[3][3]
	);
}

Mat4 Mat4::operator*(const Mat4 & mat) const
{
	Mat4 tempMat(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int x = 0; x < 4; x++)
				tempMat.m[i][j] += mat.m[i][x] * m[x][j];
		}
	}
	return tempMat;
}



Vec3 Mat4::GetTranslation() const {
	return translation;
}

void Mat4::SetTranslation(const Vec3 & vec) {
	translation = vec;
}

Vec3 Mat4::GetXAxis() const {
	return xAxis;
}

Vec3 Mat4::GetYAxis() const {
	return yAxis;
}

Vec3 Mat4::GetZAxis() const {
	return zAxis;
}

float Mat4::Determinant() const {
	float d01 = (m[2][0] * m[3][1] - m[3][0] * m[2][1]);
	float d02 = (m[2][0] * m[3][2] - m[3][0] * m[2][2]);
	float d12 = (m[2][1] * m[3][2] - m[3][1] * m[2][2]);
	float d13 = (m[2][1] * m[3][3] - m[3][1] * m[2][3]);
	float d23 = (m[2][2] * m[3][3] - m[3][2] * m[2][3]);
	float d30 = (m[2][3] * m[3][0] - m[3][3] * m[2][0]);

	float tmp0 = (m[1][1] * d23 - m[1][2] * d13 + m[1][3] * d12);
	float tmp1 = -(m[1][0] * d23 + m[1][2] * d30 + m[1][3] * d02);
	float tmp2 = (m[1][0] * d13 + m[1][1] * d30 + m[1][3] * d01);
	float tmp3 = -(m[1][0] * d12 - m[1][1] * d02 + m[1][2] * d01);

	return  m[0][0] * tmp0 + m[0][1] * tmp1 + m[0][2] * tmp2 + m[0][3] * tmp3;

}


// https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
bool Mat4::Invert() {
	Mat4 m = *this;
	float inv[16], det;
	int i;

	inv[0] = m.f[5] * m.f[10] * m.f[15] -
		m.f[5] * m.f[11] * m.f[14] -
		m.f[9] * m.f[6] * m.f[15] +
		m.f[9] * m.f[7] * m.f[14] +
		m.f[13] * m.f[6] * m.f[11] -
		m.f[13] * m.f[7] * m.f[10];

	inv[4] = -m.f[4] * m.f[10] * m.f[15] +
		m.f[4] * m.f[11] * m.f[14] +
		m.f[8] * m.f[6] * m.f[15] -
		m.f[8] * m.f[7] * m.f[14] -
		m.f[12] * m.f[6] * m.f[11] +
		m.f[12] * m.f[7] * m.f[10];

	inv[8] = m.f[4] * m.f[9] * m.f[15] -
		m.f[4] * m.f[11] * m.f[13] -
		m.f[8] * m.f[5] * m.f[15] +
		m.f[8] * m.f[7] * m.f[13] +
		m.f[12] * m.f[5] * m.f[11] -
		m.f[12] * m.f[7] * m.f[9];

	inv[12] = -m.f[4] * m.f[9] * m.f[14] +
		m.f[4] * m.f[10] * m.f[13] +
		m.f[8] * m.f[5] * m.f[14] -
		m.f[8] * m.f[6] * m.f[13] -
		m.f[12] * m.f[5] * m.f[10] +
		m.f[12] * m.f[6] * m.f[9];

	inv[1] = -m.f[1] * m.f[10] * m.f[15] +
		m.f[1] * m.f[11] * m.f[14] +
		m.f[9] * m.f[2] * m.f[15] -
		m.f[9] * m.f[3] * m.f[14] -
		m.f[13] * m.f[2] * m.f[11] +
		m.f[13] * m.f[3] * m.f[10];

	inv[5] = m.f[0] * m.f[10] * m.f[15] -
		m.f[0] * m.f[11] * m.f[14] -
		m.f[8] * m.f[2] * m.f[15] +
		m.f[8] * m.f[3] * m.f[14] +
		m.f[12] * m.f[2] * m.f[11] -
		m.f[12] * m.f[3] * m.f[10];

	inv[9] = -m.f[0] * m.f[9] * m.f[15] +
		m.f[0] * m.f[11] * m.f[13] +
		m.f[8] * m.f[1] * m.f[15] -
		m.f[8] * m.f[3] * m.f[13] -
		m.f[12] * m.f[1] * m.f[11] +
		m.f[12] * m.f[3] * m.f[9];

	inv[13] = m.f[0] * m.f[9] * m.f[14] -
		m.f[0] * m.f[10] * m.f[13] -
		m.f[8] * m.f[1] * m.f[14] +
		m.f[8] * m.f[2] * m.f[13] +
		m.f[12] * m.f[1] * m.f[10] -
		m.f[12] * m.f[2] * m.f[9];

	inv[2] = m.f[1] * m.f[6] * m.f[15] -
		m.f[1] * m.f[7] * m.f[14] -
		m.f[5] * m.f[2] * m.f[15] +
		m.f[5] * m.f[3] * m.f[14] +
		m.f[13] * m.f[2] * m.f[7] -
		m.f[13] * m.f[3] * m.f[6];

	inv[6] = -m.f[0] * m.f[6] * m.f[15] +
		m.f[0] * m.f[7] * m.f[14] +
		m.f[4] * m.f[2] * m.f[15] -
		m.f[4] * m.f[3] * m.f[14] -
		m.f[12] * m.f[2] * m.f[7] +
		m.f[12] * m.f[3] * m.f[6];

	inv[10] = m.f[0] * m.f[5] * m.f[15] -
		m.f[0] * m.f[7] * m.f[13] -
		m.f[4] * m.f[1] * m.f[15] +
		m.f[4] * m.f[3] * m.f[13] +
		m.f[12] * m.f[1] * m.f[7] -
		m.f[12] * m.f[3] * m.f[5];

	inv[14] = -m.f[0] * m.f[5] * m.f[14] +
		m.f[0] * m.f[6] * m.f[13] +
		m.f[4] * m.f[1] * m.f[14] -
		m.f[4] * m.f[2] * m.f[13] -
		m.f[12] * m.f[1] * m.f[6] +
		m.f[12] * m.f[2] * m.f[5];

	inv[3] = -m.f[1] * m.f[6] * m.f[11] +
		m.f[1] * m.f[7] * m.f[10] +
		m.f[5] * m.f[2] * m.f[11] -
		m.f[5] * m.f[3] * m.f[10] -
		m.f[9] * m.f[2] * m.f[7] +
		m.f[9] * m.f[3] * m.f[6];

	inv[7] = m.f[0] * m.f[6] * m.f[11] -
		m.f[0] * m.f[7] * m.f[10] -
		m.f[4] * m.f[2] * m.f[11] +
		m.f[4] * m.f[3] * m.f[10] +
		m.f[8] * m.f[2] * m.f[7] -
		m.f[8] * m.f[3] * m.f[6];

	inv[11] = -m.f[0] * m.f[5] * m.f[11] +
		m.f[0] * m.f[7] * m.f[9] +
		m.f[4] * m.f[1] * m.f[11] -
		m.f[4] * m.f[3] * m.f[9] -
		m.f[8] * m.f[1] * m.f[7] +
		m.f[8] * m.f[3] * m.f[5];

	inv[15] = m.f[0] * m.f[5] * m.f[10] -
		m.f[0] * m.f[6] * m.f[9] -
		m.f[4] * m.f[1] * m.f[10] +
		m.f[4] * m.f[2] * m.f[9] +
		m.f[8] * m.f[1] * m.f[6] -
		m.f[8] * m.f[2] * m.f[5];

	det = m.f[0] * inv[0] + m.f[1] * inv[4] + m.f[2] * inv[8] + m.f[3] * inv[12];

	if (det == 0)
		return false;

	det = 1.f / det;

	for (i = 0; i < 16; i++)
		f[i] = inv[i] * det;

	return true;
}


void Mat4::Transpose() {
	Mat4 mat = *this;

	for (int row = 0; row < 4; ++row) {
		for (int col = 0; col < 4; ++col) {
			mat.m[row][col] = this->m[col][row];
		}
	}

	*this = mat;
}

void Mat4::SetOrientation(const Vec3 & x, const Vec3 & y, const Vec3 & z) {
	xAxis = x;
	yAxis = y;
	zAxis = z;
}


Mat4 Mat4::CreateIdentity() {
	return Mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}

Mat4 Mat4::CreateMatrix(Vec3 pos, Vec3 rot, Vec3 scale)
{
	Mat4 m = CreateTranslation(pos) * CreateEulerAxis(rot.x, rot.y, rot.z) * CreateScale(scale);
	return m;
}

Mat4 Mat4::CreateMatrixDeg(Vec3 pos, Vec3 rot, Vec3 scale)
{
	rot = rot / 180 * (float) 3.14159265359;
	Mat4 m = CreateTranslation(pos) * CreateEulerAxis(rot.x, rot.y, rot.z) * CreateScale(scale);
	return m;
}

Mat4 Mat4::CreateTranslation(Vec3 pos) {
	return Mat4(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		pos.x, pos.y, pos.z, 1);
}

Mat4 Mat4::CreateScale(Vec3 scale) {
	return Mat4(
		scale.x, 0, 0, 0,
		0, scale.y, 0, 0,
		0, 0, scale.z, 0,
		0, 0, 0, 1);
}

Mat4 Mat4::CreateEulerAxis(float yaw, float pitch, float roll) {
	Mat4 m;
	m = m.CreateRotateY(yaw) * m.CreateRotateZ(roll) * m.CreateRotateX(pitch);
	return m;
}

// Lotte provided this.
Mat4 Mat4::CreateRotate(float angle, const Vec3 & axis) {
	return Mat4(
		axis.x * axis.x * (1 - cos(angle)) + cos(angle), axis.x * axis.y * (1 - cos(angle)) + axis.z * sin(angle), axis.x * axis.z * (1 - cos(angle)) - axis.y * sin(angle), 0,
		axis.x * axis.y * (1 - cos(angle)) - axis.z * sin(angle), axis.y * axis.y * (1 - cos(angle)) + cos(angle), axis.y * axis.z * (1 - cos(angle)) + axis.x * sin(angle), 0,
		axis.x * axis.z * (1 - cos(angle)) + axis.y * sin(angle), axis.y * axis.z * (1 - cos(angle)) - axis.x * sin(angle), axis.z * axis.z * (1 - cos(angle)) + cos(angle), 0,
		0, 0, 0, 1);
}

Mat4 Mat4::CreateRotateX(float angle) {
	Mat4 m;
	m.f[5] = cos(angle);		m.f[9] = -sin(angle);
	m.f[6] = sin(angle);		m.f[10] = cos(angle);
	return m;
}

Mat4 Mat4::CreateRotateY(float angle) {
	Mat4 m;
	m.f[0] = cos(angle);		m.f[8] = sin(angle);
	m.f[2] = -sin(angle);		m.f[10] = cos(angle);
	return m;
}

Mat4 Mat4::CreateRotateZ(float angle) {
	Mat4 m;
	m.f[0] = cos(angle);		m.f[4] = -sin(angle);
	m.f[1] = sin(angle);		m.f[5] = cos(angle);
	return m;
}

Mat4 Mat4::CreateOrtho(float left, float right, float bottom, float top, float nearZ, float farZ) {
	return Mat4(
		2.f / (right - left), 0, 0, 0,
		0, 2.f / (top - bottom), 0, 0,
		0, 0, (-2.f) / (farZ - nearZ), 0,
		-((right + left) / (right - left)), -((top + bottom) / (top - bottom)), -((farZ + nearZ) / (farZ - nearZ)), 1.f
	);
}

Mat4 Mat4::CreateFrustum(float left, float right, float bottom, float top, float nearZ, float farZ) {
	return Mat4(2 * nearZ / (right - left), 0.0f, 0.0f, 0.0f,   //X column
		0.0f, 2 * nearZ / (top - bottom), 0.0f, 0.0f,   //Y column
		(right + left) / (right - left), (top + bottom) / (top - bottom), (nearZ + farZ) / (nearZ - farZ), -1.0f,  //Z column
		0.0f, 0.0f, 2 * nearZ * farZ / (nearZ - farZ), 0.0f    //Z column
	);
}

Mat4 Mat4::CreatePerspective(float fovy, float aspect, float nearZ, float farZ) {	
	Mat4 result;

	float scale = 1 / tan(fovy * 0.5f / 180 * (float) 3.14159265359);
	result.m[0][0] = scale / aspect;
	result.m[1][1] = scale;
	result.m[2][2] = -((farZ + nearZ) / (farZ - nearZ));
	//m.m[2][2] = -1;
	result.m[3][3] = 0;
	result.m[2][3] = -1;
	result.m[3][2] = -(2 * farZ * nearZ / (farZ - nearZ));
	//m.m[3][2] = -2 * nearZ;
	return result;
}

Mat4 Mat4::CreateLookAt(const Vec3 & eye, const Vec3 & center, const Vec3 & up) {

	Vec3 zaxis = (eye - center).Normalize();    // The "forward" vector.
	Vec3 xaxis = up.Cross(zaxis).Normalize();// The "right" vector.
	Vec3 yaxis = zaxis.Cross(xaxis);     // The "up" vector.

										  // Create a 4x4 view matrix from the right, up, forward and eye position vectors
	Mat4 viewMatrix(
		xaxis.x, yaxis.x, zaxis.x, 0,
		xaxis.y, yaxis.y, zaxis.y, 0,
		xaxis.z, yaxis.z, zaxis.z, 0,
		-xaxis.Dot(eye), -yaxis.Dot(eye), -zaxis.Dot(eye), 1);

	return viewMatrix;

}

Vec3 Mat4::TransformDirectionVector(const Vec3 & direction) {
	return Vec3();
}

std::string Mat4::Print()
{
	std::string s;
	for (int i = 0; i < 16; i++)
	{
		//s += std::to_string(f[i]);
		s += ", ";
		if ((i + 1) % 4 == 0) s += "\n";
	}

	return s;
}
