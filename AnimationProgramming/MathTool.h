#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <type_traits>

#define EPSILON 0.00001f

namespace MathTool
{
#pragma region Tools

	static const float Pi = 3.1415926535f;
	static const float E = 2.7182818284f;

#pragma endregion Tools	

#pragma region Utils

	class Utils
	{
	public:
		Utils() = delete;

		template <typename T>
		static T Square(T value);

		template <typename T>
		static T SquareRoot(T value);

		static float SquareRootF(float value);

		template <typename T>
		static T Abs(T value);
	};

	template<typename T>
	inline T Utils::Square(T value)
	{
		return value * value;
	}

	template<typename T>
	inline T Utils::SquareRoot(T value)
	{
		return sqrt(value);
	}

	inline float Utils::SquareRootF(float value)
	{
		return sqrtf(value);
	}

	template<typename T>
	inline T Utils::Abs(T value)
	{
		return (value < 0) ? -value : value;
	}

#pragma endregion Utils

#pragma region Vector3

	struct Vector3
	{
		float x;
		float y;
		float z;

		Vector3();

		Vector3(float p_x, float p_y, float p_z);

		Vector3(const Vector3& p_other);

		Vector3& operator=(const Vector3& p_other);

		Vector3& operator=(Vector3&& p_other);

		Vector3& Add(const Vector3& p_other);

		Vector3 operator+(const Vector3& p_other) const;

		Vector3& Subtract(const Vector3& p_other);

		Vector3 operator-(const Vector3& p_other) const;

		Vector3& Multiply(float p_scalar);

		Vector3 operator*(float p_scalar) const;

		static Vector3 Lerp(const Vector3& p_start, const Vector3& p_end, float p_interpolationCoefficient);
	};


#pragma endregion Vector3

#pragma region Vector4

	struct Vector4
	{
		float x;
		float y;
		float z;
		float w;

		Vector4();

		Vector4(float p_x, float p_y, float p_z, float p_w = 1.0f);
	};

#pragma endregion Vector4

#pragma region Matrix4

	class Matrix4
	{
	public:
		float elements[16];

		Matrix4();

		Matrix4(float p_element1, float p_element2, float p_element3, float p_element4,
			float p_element5, float p_element6, float p_element7, float p_element8,
			float p_element9, float p_element10, float p_element11, float p_element12,
			float p_element13, float p_element14, float p_element15, float p_element16);

		static const Matrix4 Identity;

		Matrix4(const Matrix4& p_other);

		Matrix4(Matrix4&& p_other);

		Matrix4& operator=(const Matrix4& p_other);

		Matrix4 operator=(Matrix4&& p_other);

		static Matrix4 Multiply(const Matrix4& p_left, const Matrix4& p_right);

		Matrix4 operator*(const Matrix4& p_other) const;

		static float GetMinor(float p_minor0, float p_minor1, float p_minor2, float p_minor3, float p_minor4, float p_minor5,
			float p_minor6, float p_minor7, float p_minor8);

		Matrix4 Inverse() const;

		static const Matrix4 Inverse(const Matrix4& p_matrix);

		static Matrix4 Translation(const Vector3& p_translation);

		float& operator()(uint8_t p_row, uint8_t p_column);

		float* ToArray();

		static float* ToArray(const Matrix4& p_matrix);

		Vector4 GetColumn(uint8_t p_column);
	};

	std::ostream& operator<<(std::ostream& p_stream, const Matrix4& p_matrix);

#pragma endregion Matrix4

#pragma region Quaternion

	class Quaternion
	{
	private:
		float m_x;
		float m_y;
		float m_z;
		float m_w;

	public:
		Quaternion();

		Quaternion(float x, float y, float z, float w);

		Quaternion(const Quaternion& p_other);

		bool IsNormalized() const;

		Quaternion& Normalize();

		void SetXAxisValue(float p_xValue);

		void SetYAxisValue(float p_yValue);

		void SetZAxisValue(float p_zValue);

		void SetRealValue(float p_realValue);

		static Quaternion Slerp(Quaternion& p_first, Quaternion& p_second, const float p_alpha);

		Matrix4 ToMatrix4() const;

	};

#pragma endregion Quaternion

}
