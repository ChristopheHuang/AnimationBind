#include "MathTool.h"
#include <cmath>

#pragma region Vector3

MathTool::Vector3::Vector3()
	: x(0), y(0), z(0) {}

MathTool::Vector3::Vector3(float p_x, float p_y, float p_z)
	: x(p_x), y(p_y), z(p_z) {}

MathTool::Vector3::Vector3(const Vector3& p_other)
{
	*this = p_other;
}

MathTool::Vector3& MathTool::Vector3::operator=(const Vector3& p_other)
{
	x = p_other.x;
	y = p_other.y;
	z = p_other.z;

	return *this;
}

MathTool::Vector3& MathTool::Vector3::operator=(Vector3 && p_other)
{
	x = p_other.x;
	y = p_other.y;
	z = p_other.z;

	return *this;
}

MathTool::Vector3& MathTool::Vector3::Add(const Vector3& p_other)
{
	x += p_other.x;
	y += p_other.y;
	z += p_other.z;

	return *this;
}

MathTool::Vector3 MathTool::Vector3::operator+(const Vector3& p_other) const
{
	return Vector3(*this).Add(p_other);
}

MathTool::Vector3& MathTool::Vector3::Subtract(const Vector3& p_other)
{
	x -= p_other.x;
	y -= p_other.y;
	z -= p_other.z;

	return *this;
}

MathTool::Vector3 MathTool::Vector3::operator-(const Vector3& p_other) const
{
	return Vector3(*this).Subtract(p_other);
}

MathTool::Vector3& MathTool::Vector3::Multiply(float p_scalar)
{
	x *= p_scalar;
	y *= p_scalar;
	z *= p_scalar;

	return *this;
}

MathTool::Vector3 MathTool::Vector3::operator*(float p_scalar) const
{
	return Vector3(*this).Multiply(p_scalar);
}

MathTool::Vector3 MathTool::Vector3::Lerp(const Vector3& p_start, const Vector3& p_end,
	float p_interpolationCoefficient)
{
	if (p_interpolationCoefficient >= 0 && p_interpolationCoefficient <= 1)
		return (p_start + (p_end - p_start) * p_interpolationCoefficient);

	return p_start;
}

#pragma endregion Vector3

#pragma region Vector4

MathTool::Vector4::Vector4()
{
}

MathTool::Vector4::Vector4(float p_x, float p_y, float p_z, float p_w)
	: x(p_x), y(p_y), z(p_z), w(p_w) {}

#pragma endregion Vector4

#pragma region Matrix4
const MathTool::Matrix4 MathTool::Matrix4::Identity = Matrix4(1.f, 0.f, 0.f, 0.f,
	0.f, 1.f, 0.f, 0.f,
	0.f, 0.f, 1.f, 0.f,
	0.f, 0.f, 0.f, 1.f);


MathTool::Matrix4::Matrix4()
{
	memcpy(this->elements, Matrix4::Identity.elements, 16 * sizeof(float));
}

MathTool::Matrix4::Matrix4(float p_element1, float p_element2, float p_element3, float p_element4,
	float p_element5, float p_element6, float p_element7, float p_element8,
	float p_element9, float p_element10, float p_element11, float p_element12,
	float p_element13, float p_element14, float p_element15, float p_element16)
{
	elements[0] = p_element1;	elements[1] = p_element2;	elements[2] = p_element3;	elements[3] = p_element4;
	elements[4] = p_element5;	elements[5] = p_element6;	elements[6] = p_element7;	elements[7] = p_element8;
	elements[8] = p_element9;	elements[9] = p_element10;	elements[10] = p_element11;	elements[11] = p_element12;
	elements[12] = p_element13; elements[13] = p_element14; elements[14] = p_element15;	elements[15] = p_element16;
}

MathTool::Matrix4::Matrix4(Matrix4&& p_other)
{
	memmove(this->elements, p_other.elements, 16 * sizeof(float));
}

MathTool::Matrix4::Matrix4(const Matrix4& p_other)
{
	*this = p_other;
}

MathTool::Matrix4 MathTool::Matrix4::operator=(Matrix4&& p_other)
{
	memcpy(this->elements, p_other.elements, 16 * sizeof(float));
	return *this;
}

MathTool::Matrix4& MathTool::Matrix4::operator=(const Matrix4& p_other)
{
	memmove(this->elements, p_other.elements, 16 * sizeof(float));
	return *this;
}

MathTool::Matrix4 MathTool::Matrix4::Multiply(const Matrix4& p_left, const Matrix4& p_right)
{
	return Matrix4(
		((p_left.elements[0] * p_right.elements[0]) + (p_left.elements[1] * p_right.elements[4]) + (p_left.elements[2] * p_right.elements[8]) + (p_left.elements[3] * p_right.elements[12])),

		((p_left.elements[0] * p_right.elements[1]) + (p_left.elements[1] * p_right.elements[5]) + (p_left.elements[2] * p_right.elements[9]) + (p_left.elements[3] * p_right.elements[13])),

		((p_left.elements[0] * p_right.elements[2]) + (p_left.elements[1] * p_right.elements[6]) + (p_left.elements[2] * p_right.elements[10]) + (p_left.elements[3] * p_right.elements[14])),

		((p_left.elements[0] * p_right.elements[3]) + (p_left.elements[1] * p_right.elements[7]) + (p_left.elements[2] * p_right.elements[11]) + (p_left.elements[3] * p_right.elements[15])),

		((p_left.elements[4] * p_right.elements[0]) + (p_left.elements[5] * p_right.elements[4]) + (p_left.elements[6] * p_right.elements[8]) + (p_left.elements[7] * p_right.elements[12])),

		((p_left.elements[4] * p_right.elements[1]) + (p_left.elements[5] * p_right.elements[5]) + (p_left.elements[6] * p_right.elements[9]) + (p_left.elements[7] * p_right.elements[13])),

		((p_left.elements[4] * p_right.elements[2]) + (p_left.elements[5] * p_right.elements[6]) + (p_left.elements[6] * p_right.elements[10]) + (p_left.elements[7] * p_right.elements[14])),

		((p_left.elements[4] * p_right.elements[3]) + (p_left.elements[5] * p_right.elements[7]) + (p_left.elements[6] * p_right.elements[11]) + (p_left.elements[7] * p_right.elements[15])),

		((p_left.elements[8] * p_right.elements[0]) + (p_left.elements[9] * p_right.elements[4]) + (p_left.elements[10] * p_right.elements[8]) + (p_left.elements[11] * p_right.elements[12])),

		((p_left.elements[8] * p_right.elements[1]) + (p_left.elements[9] * p_right.elements[5]) + (p_left.elements[10] * p_right.elements[9]) + (p_left.elements[11] * p_right.elements[13])),

		((p_left.elements[8] * p_right.elements[2]) + (p_left.elements[9] * p_right.elements[6]) + (p_left.elements[10] * p_right.elements[10]) + (p_left.elements[11] * p_right.elements[14])),

		((p_left.elements[8] * p_right.elements[3]) + (p_left.elements[9] * p_right.elements[7]) + (p_left.elements[10] * p_right.elements[11]) + (p_left.elements[11] * p_right.elements[15])),

		((p_left.elements[12] * p_right.elements[0]) + (p_left.elements[13] * p_right.elements[4]) + (p_left.elements[14] * p_right.elements[8]) + (p_left.elements[15] * p_right.elements[12])),

		((p_left.elements[12] * p_right.elements[1]) + (p_left.elements[13] * p_right.elements[5]) + (p_left.elements[14] * p_right.elements[9]) + (p_left.elements[15] * p_right.elements[13])),

		((p_left.elements[12] * p_right.elements[2]) + (p_left.elements[13] * p_right.elements[6]) + (p_left.elements[14] * p_right.elements[10]) + (p_left.elements[15] * p_right.elements[14])),

		((p_left.elements[12] * p_right.elements[3]) + (p_left.elements[13] * p_right.elements[7]) + (p_left.elements[14] * p_right.elements[11]) + (p_left.elements[15] * p_right.elements[15])));
}

MathTool::Matrix4 MathTool::Matrix4::operator*(const Matrix4& p_other) const
{
	return Multiply(*this, p_other);
}

MathTool::Matrix4 MathTool::Matrix4::Translation(const Vector3& p_translation)
{
	return Matrix4(1, 0, 0, p_translation.x,
		0, 1, 0, p_translation.y,
		0, 0, 1, p_translation.z,
		0, 0, 0, 1);
}

const MathTool::Matrix4 MathTool::Matrix4::Inverse(const Matrix4& p_matrix)
{
	return p_matrix.Inverse();
}

MathTool::Matrix4 MathTool::Matrix4::Inverse() const
{
	const float cof0 = GetMinor(elements[5], elements[9], elements[13], elements[6], elements[10], elements[14], elements[7], elements[11], elements[15]);
	const float cof1 = GetMinor(elements[1], elements[9], elements[13], elements[2], elements[10], elements[14], elements[3], elements[11], elements[15]);
	const float cof2 = GetMinor(elements[1], elements[5], elements[13], elements[2], elements[6], elements[14], elements[3], elements[7], elements[15]);
	const float cof3 = GetMinor(elements[1], elements[5], elements[9], elements[2], elements[6], elements[10], elements[3], elements[7], elements[11]);

	const float det = elements[0] * cof0 - elements[4] * cof1 + elements[8] * cof2 - elements[12] * cof3;
	if (fabs(det) <= EPSILON)
		return Matrix4::Identity;
	const float cof4 = GetMinor(elements[4], elements[8], elements[12], elements[6], elements[10], elements[14], elements[7], elements[11], elements[15]);
	const float cof5 = GetMinor(elements[0], elements[8], elements[12], elements[2], elements[10], elements[14], elements[3], elements[11], elements[15]);
	const float cof6 = GetMinor(elements[0], elements[4], elements[12], elements[2], elements[6], elements[14], elements[3], elements[7], elements[15]);
	const float cof7 = GetMinor(elements[0], elements[4], elements[8], elements[2], elements[6], elements[10], elements[3], elements[7], elements[11]);

	const float cof8 = GetMinor(elements[4], elements[8], elements[12], elements[5], elements[9], elements[13], elements[7], elements[11], elements[15]);
	const float cof9 = GetMinor(elements[0], elements[8], elements[12], elements[1], elements[9], elements[13], elements[3], elements[11], elements[15]);
	const float cof10 = GetMinor(elements[0], elements[4], elements[12], elements[1], elements[5], elements[13], elements[3], elements[7], elements[15]);
	const float cof11 = GetMinor(elements[0], elements[4], elements[8], elements[1], elements[5], elements[9], elements[3], elements[7], elements[11]);

	const float cof12 = GetMinor(elements[4], elements[8], elements[12], elements[5], elements[9], elements[13], elements[6], elements[10], elements[14]);
	const float cof13 = GetMinor(elements[0], elements[8], elements[12], elements[1], elements[9], elements[13], elements[2], elements[10], elements[14]);
	const float cof14 = GetMinor(elements[0], elements[4], elements[12], elements[1], elements[5], elements[13], elements[2], elements[6], elements[14]);
	const float cof15 = GetMinor(elements[0], elements[4], elements[8], elements[1], elements[5], elements[9], elements[2], elements[6], elements[10]);

	const float detInv = 1.0f / det;
	Matrix4 inverse;

	inverse.elements[0] = detInv * cof0;     inverse.elements[1] = -detInv * cof1;   inverse.elements[2] = detInv * cof2;     inverse.elements[3] = -detInv * cof3;
	inverse.elements[4] = -detInv * cof4;    inverse.elements[5] = detInv * cof5;    inverse.elements[6] = -detInv * cof6;    inverse.elements[7] = detInv * cof7;
	inverse.elements[8] = detInv * cof8;     inverse.elements[9] = -detInv * cof9;   inverse.elements[10] = detInv * cof10;   inverse.elements[11] = -detInv * cof11;
	inverse.elements[12] = -detInv * cof12;  inverse.elements[13] = detInv * cof13;  inverse.elements[14] = -detInv * cof14;  inverse.elements[15] = detInv * cof15;

	return inverse;
}

float MathTool::Matrix4::GetMinor(float p_minor0, float p_minor1, float p_minor2, float p_minor3, float p_minor4,
	float p_minor5, float p_minor6, float p_minor7, float p_minor8)
{
	return p_minor0 * (p_minor4 * p_minor8 - p_minor5 * p_minor7)
		- p_minor1 * (p_minor3 * p_minor8 - p_minor5 * p_minor6)
		+ p_minor2 * (p_minor3 * p_minor7 - p_minor4 * p_minor6);
}

float& MathTool::Matrix4::operator()(uint8_t p_row, uint8_t p_column)
{
	if (p_row >= 4 || p_column >= 4)
		throw std::out_of_range(
			"Invalid index : " + std::to_string(p_row) + "," + std::to_string(p_column) + " is out of range");
	return elements[4 * p_row + p_column];
}

MathTool::Vector4 MathTool::Matrix4::GetColumn(uint8_t p_column)
{
	if (p_column >= 4)
		throw std::out_of_range("Invalid index : " + std::to_string(p_column) + " is out of range");

	return Vector4(elements[p_column], elements[p_column + 4], elements[p_column + 8], elements[p_column + 12]);
}

float* MathTool::Matrix4::ToArray(const Matrix4& p_matrix)
{
	return (float*)p_matrix.elements;
}

float* MathTool::Matrix4::ToArray()
{
	return elements;
}

std::ostream& MathTool::operator<<(std::ostream& p_stream, const Matrix4& p_matrix)
{
	p_stream << p_matrix.elements[0] << "\t" << p_matrix.elements[1] << "\t" << p_matrix.elements[2] << "\t" << p_matrix.elements[3] << "\n" <<
				p_matrix.elements[4] << "\t" << p_matrix.elements[5] << "\t" << p_matrix.elements[6] << "\t" << p_matrix.elements[7] << "\n" <<
				p_matrix.elements[8] << "\t" << p_matrix.elements[9] << "\t" << p_matrix.elements[10] << "\t" << p_matrix.elements[11] << "\n" <<
				p_matrix.elements[12] << "\t" << p_matrix.elements[13] << "\t" << p_matrix.elements[14] << "\t" << p_matrix.elements[15] << "\n";

	return p_stream;
}

#pragma endregion Matrix4
	
#pragma region Quaternion

MathTool::Quaternion::Quaternion() : m_x(0.0f), m_y(0.0f), m_z(0.0f), m_w(1.0f) {}

MathTool::Quaternion::Quaternion(float x, float y, float z, float w) : m_x(x), m_y(y), m_z(z), m_w(w) {}

MathTool::Quaternion::Quaternion(const Quaternion& p_other)
{
	*this = p_other;
}

bool MathTool::Quaternion::IsNormalized() const
{
	float magnitude = std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
	return std::abs(magnitude - 1.0) < std::numeric_limits<float>::epsilon();
}

MathTool::Quaternion& MathTool::Quaternion::Normalize()
{
	float magnitude = std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);

	if (magnitude > 0.0)
	{
		float invMagnitude = 1.0 / magnitude;
		m_x *= invMagnitude;
		m_y *= invMagnitude;
		m_z *= invMagnitude;
		m_w *= invMagnitude;
	}
	else
	{
		// If magnitude is zero, set to default (identity) quaternion
		m_x = 0.0;
		m_y = 0.0;
		m_z = 0.0;
		m_w = 1.0;
	}

	return *this;
}

void MathTool::Quaternion::SetXAxisValue(float p_xValue)
{
	m_x = p_xValue;
}
void MathTool::Quaternion::SetYAxisValue(float p_yValue)
{
	m_y = p_yValue;
}
void MathTool::Quaternion::SetZAxisValue(float p_zValue)
{
	m_z = p_zValue;
}
void MathTool::Quaternion::SetRealValue(float p_realValue)
{
	m_w = p_realValue;
}

MathTool::Quaternion MathTool::Quaternion::Slerp(Quaternion& p_first, Quaternion& p_second, const float p_alpha)
{
	float cosOmega = p_first.m_x * p_second.m_x + p_first.m_y * p_second.m_y +
		p_first.m_z * p_second.m_z + p_first.m_w * p_second.m_w;

	bool flip = false;

	if (cosOmega < 0.f)
	{
		flip = true;
		cosOmega = -cosOmega;
	}

	float s1, s2;

	if (cosOmega > 1.f - 1.e-06f)
	{
		s1 = 1.f - p_alpha;
		s2 = flip ? -p_alpha : p_alpha;
	}
	else
	{
		const float omega = std::acos(cosOmega);
		const float invSinOmega = 1.f / std::sin(omega);

		s1 = std::sin((1.f - p_alpha) * omega) * invSinOmega;
		s2 = flip
			? -std::sin(p_alpha * omega) * invSinOmega
			: std::sin(p_alpha * omega) * invSinOmega;
	}

	Quaternion Quat;

	Quat.m_x = s1 * p_first.m_x + s2 * p_second.m_x;
	Quat.m_y = s1 * p_first.m_y + s2 * p_second.m_y;
	Quat.m_z = s1 * p_first.m_z + s2 * p_second.m_z;
	Quat.m_w = s1 * p_first.m_w + s2 * p_second.m_w;

	return Quat;
}

MathTool::Matrix4 MathTool::Quaternion::ToMatrix4() const
{
	Matrix4 matrix;

	float xx = m_x * m_x;
	float yy = m_y * m_y;
	float zz = m_z * m_z;
	float xy = m_x * m_y;
	float xz = m_x * m_z;
	float yz = m_y * m_z;
	float wx = m_w * m_x;
	float wy = m_w * m_y;
	float wz = m_w * m_z;

	matrix(0, 0) = 1.0 - 2.0 * (yy + zz);
	matrix(0, 1) = 2.0 * (xy - wz);
	matrix(0, 2) = 2.0 * (xz + wy);
	matrix(0, 3) = 0.0;

	matrix(1, 0) = 2.0 * (xy + wz);
	matrix(1, 1) = 1.0 - 2.0 * (xx + zz);
	matrix(1, 2) = 2.0 * (yz - wx);
	matrix(1, 3) = 0.0;

	matrix(2, 0) = 2.0 * (xz - wy);
	matrix(2, 1) = 2.0 * (yz + wx);
	matrix(2, 2) = 1.0 - 2.0 * (xx + yy);
	matrix(2, 3) = 0.0;

	matrix(3, 0) = 0.0;
	matrix(3, 1) = 0.0;
	matrix(3, 2) = 0.0;
	matrix(3, 3) = 1.0;

	return matrix;
}

#pragma endregion Quaternion