#pragma once


class Values
{
public :
	const static float PI;
	const static float PI_TIMES_TWO;
	const static Vector3 ZeroVec3;
	const static Vector3 OneVec3; 
	const static Vector3 LeftVec;
	const static Vector3 RightVec;
	const static Vector3 DownVec;
	const static Vector3 UpVec;
	const static Vector3 FwdVec;
	const static Vector3 ScreenSize;

	const static Vector2 ZeroVec2;
	const static Vector2 OneVec2;
	const static Vector2 UVLT; // left top
	const static Vector2 UVLB; // left bottom
	const static Vector2 UVRB; // right bottom
	const static Vector2 UVRT; // right top

	const static Color Red;
	const static Color Blue;
	const static Color Green;
	const static Color Magenta;
	const static Color Black;
	const static Color White;
	const static Color ClearColor;
	
	const static Matrix Identity;
};

class DxMath
{
public :
	// example : Matrix m = DxMath::Translation(position)
	static Matrix Translation(const Vector3& position)
	{
		Matrix m;
		D3DXMatrixTranslation(&m, position.x, position.y, position.z);
		return m;
	}

	static Matrix Translation(const float& x, const float& y, const float& z)
	{
		return Translation(Vector3(x, y, z));
	}
	static Matrix TranslationX(const float& x)
	{
		return Translation(x, 0, 0);
	}
	static Matrix TranslationY(const float& y)
	{
		return Translation(0, y, 0);
	}
	static Matrix TranslationZ(const float& z)
	{
		return Translation(0, 0, z);
	}

	static Matrix Scaling(const Vector3& size)
	{
		Matrix m;
		D3DXMatrixScaling(&m, size.x, size.y, size.z);
		return m;
	}
	static Matrix Scaling(const float& x, const float& y, const float& z)
	{
		return Scaling(Vector3(x, y, z));
	}
	static Matrix ScalingX(const float& x)
	{
		return Scaling(x, 0, 0);
	}
	static Matrix ScalingY(const float& y)
	{
		return Scaling(0, y, 0);
	}
	static Matrix ScalingZ(const float& z)
	{
		return Scaling(0, 0, z);
	}


	static Matrix RotationInDegree(const float& rotation)
	{
		Matrix m;
		D3DXMatrixRotationZ(&m, (float)D3DXToRadian(rotation));
		return m;
	}

	static Matrix RotationInRadian(const float& rotation)
	{
		Matrix m;
		D3DXMatrixRotationZ(&m, rotation);
		return m;
	}

	// 결과값 : -180 ~ 180
	static float GetAngle(const D3DXVECTOR3& a, const D3DXVECTOR3& b)
	{
		float cosAngle = acosf(D3DXVec3Dot(&a, &b) / (D3DXVec3Length(&a) * D3DXVec3Length(&b)));
		cosAngle = D3DXToDegree(cosAngle);

		// 외적의 z성분으로 방향이 결정된다.
		float angle = (a.x * b.y - a.y * b.x > 0.0f) ? cosAngle : -cosAngle;
		return angle;
	}


	// Dot product of two vector2's
	static float DotProduct(const Vector2 &a, const Vector2 &b)
	{
		return a.x*b.x + a.y*b.y;
	}

	// Dot product of two vector3's
	static float DotProduct(const Vector3 &a, const Vector3 &b)
	{
		return a.x*b.x + a.y*b.y + a.z*b.z;
	}


	// Swap two vector2's
	static void SwapVec(Vector2 &a, Vector2 &b)
	{
		Vector2 tmp(a);

		a = b;
		b = tmp;
	}

	// Swap two vector3's
	static void SwapVec(Vector3 &a, Vector3 &b)
	{
		Vector3 tmp(a);

		a = b;
		b = tmp;
	}

	// Cross product of two vector3's
	static Vector3 CrossProduct(const Vector3 &a, const Vector3 &b)
	{
		return Vector3(a.y*b.z - a.z*b.y,
			a.z*b.x - a.x*b.z,
			a.x*b.y - a.y*b.x);
	}

	// Are these two vector2's nearly equal?
	static  bool NearlyEquals(const Vector2& a, const Vector2& b, float r)
	{
		Vector2 diff = a - b; // difference

		return (DotProduct(diff, diff) < r*r); // radius
	}

	// Are these two vector3's nearly equal?
	static  bool NearlyEquals(const Vector3& a, const Vector3& b, float r)
	{
		Vector3 diff = a - b; // difference

		return (DotProduct(diff, diff) < r*r); // radius
	}

	static float Length(Vector3 vec)
	{
		return (float)sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	}
	static float SqrMagnitude(Vector3 vec)
	{
		return Length(vec) * Length(vec);
	}
	static Vector3 Normalize(Vector3 vec)
	{
		float m = Length(vec);

		if (m > 0.0f)
			m = 1.0f / m;
		else
			m = 0.0f;
		vec.x *= m;
		vec.y *= m;
		vec.z *= m;

		return vec;
	}
	static Vector3 SetMagnitudeOfVector(Vector3 vec, float velocity)
	{

		Vector3 norm = Normalize(vec);
		norm.x *= velocity;
		norm.y *= velocity;
		norm.z *= velocity;

		return norm;
	}
	// get angle between two vectors
	static float GetAngleBetween(Vector3 vec1, Vector3 vec2)
	{
		float mag1 = Length(vec1);
		float mag2 = Length(vec2);
		float dotProduct = DotProduct(vec1, vec2);

		return (float)(acos(dotProduct / (mag1 * mag2)));
	}

	static float GetDist(Vector3 pos1, Vector3 pos2)
	{
		Vector3 temp = pos1 - pos2;
		return std::abs(Length(temp));
	}
	static  Vector3 GetDirection(Vector3 vec)
	{
		return Normalize(vec);
	}

	// old
	/*static float Lerp(float value1, float value2, float amount)
	{
		return float(value1 + ((float)(value2 - value1) * amount));
	}*/
	static float Lerp(float a, float b, float lerpFactor)
	{
		float result = ((1.f - lerpFactor) * a) + (lerpFactor * b);
		return result;
	}
	static float LerpDegrees(float a, float b, float lerpFactor) // Lerps from angle a to b (both between 0.f and 360.f), taking the shortest path
	{
		float result;
		float diff = b - a;
		if (diff < -180.f)
		{
			// lerp upwards past 360
			b += 360.f;
			result = Lerp(a, b, lerpFactor);
			if (result >= 360.f)
			{
				result -= 360.f;
			}
		}
		else if (diff > 180.f)
		{
			// lerp downwards past 0
			b -= 360.f;
			result = Lerp(a, b, lerpFactor);
			if (result < 0.f)
			{
				result += 360.f;
			}
		}
		else
		{
			// straight lerp
			result = Lerp(a, b, lerpFactor);
		}

		return result;
	}

	static float LerpRadians(float a, float b, float lerpFactor) // Lerps from angle a to b (both between 0.f and PI_TIMES_TWO), taking the shortest path
	{
		float result;
		float diff = b - a;
		if (diff < -Values::PI)
		{
			// lerp upwards past PI_TIMES_TWO
			b += Values::PI_TIMES_TWO;
			result = Lerp(a, b, lerpFactor);
			if (result >= Values::PI_TIMES_TWO)
			{
				result -= Values::PI_TIMES_TWO;
			}
		}
		else if (diff > Values::PI)
		{
			// lerp downwards past 0
			b -= Values::PI_TIMES_TWO;
			result = Lerp(a, b, lerpFactor);
			if (result < 0.f)
			{
				result += Values::PI_TIMES_TWO;
			}
		}
		else
		{
			// straight lerp
			result = Lerp(a, b, lerpFactor);
		}

		return result;
	}
	static float ReliableRandom(float min, float max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> distr(min, max);
		return distr(gen);
	}
};

