/*	Renegade Scripts.dll
	Copyright 2013 Tiberian Technologies

	This file is part of the Renegade scripts.dll
	The Renegade scripts.dll is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	In addition, an exemption is given to allow Run Time Dynamic Linking of this code with any closed source module that does not contain code covered by this licence.
	Only the source code to the module(s) containing the licenced code has to be released.
*/
#ifndef TT_INCLUDE__MATRIX4_H
#define TT_INCLUDE__MATRIX4_H
#include "Vector4.h"
#include "Vector3.h"
#include "Matrix3D.h"
#include "Matrix3.h"
#include "plane.h"
class SCRIPTS_API Matrix4 {
public:
	static const Matrix4 IDENTITY;
	TT_INLINE Matrix4(void)
	{
	}
	TT_INLINE Matrix4(const Matrix4 & m)
	{
		Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2]; Row[3] = m.Row[3];
	}
	TT_INLINE explicit Matrix4(bool identity)
	{
		if (identity)
		{
			Make_Identity();
		}
	}
	TT_INLINE explicit Matrix4(const Matrix3D & m)
	{
		Init(m);
	}
	TT_INLINE explicit Matrix4(const Vector4 & v0, const Vector4 & v1, const Vector4 & v2, const Vector4 & v3)	{
		Init(v0,v1,v2,v3);
	}
	TT_INLINE void Make_Identity(void)
	{
		Row[0].Set(1.0,0.0,0.0,0.0);
		Row[1].Set(0.0,1.0,0.0,0.0);
		Row[2].Set(0.0,0.0,1.0,0.0);
		Row[3].Set(0.0,0.0,0.0,1.0);
	}
	TT_INLINE void Init(const Matrix3D & m)
	{
		Row[0] = m[0]; Row[1] = m[1]; Row[2] = m[2]; Row[3] = Vector4(0.0,0.0,0.0,1.0); 
	}
	TT_INLINE void Init(const Vector4 & v0, const Vector4 & v1, const Vector4 & v2, const Vector4 & v3)
	{
		Row[0] = v0; Row[1] = v1; Row[2] = v2; Row[3] = v3;
	}
	TT_INLINE void Init_Ortho_OGL(float left,float right,float bottom,float top,float znear,float zfar)
	{
		Make_Identity();
		Row[0][0] = 2.0f / (right - left);
		Row[0][3] = -(right + left) / (right - left);
		Row[1][1] = 2.0f / (top - bottom);
		Row[1][3] = -(top + bottom) / (top - bottom);
		Row[2][2] = -2.0f / (zfar - znear);
		Row[2][3] = -(zfar + znear) / (zfar - znear);

	}
	TT_INLINE void Init_Perspective_OGL(float hfov,float vfov,float znear,float zfar)
	{
		Make_Identity();
		Row[0][0] = static_cast<float>(1.0 / tan(hfov*0.5));
		Row[1][1] = static_cast<float>(1.0 / tan(vfov*0.5));
		Row[2][2] = -(zfar + znear) / (zfar - znear);
		Row[2][3] = static_cast<float>(-(2.0*zfar*znear) / (zfar - znear));
		Row[3][2] = -1.0f;
		Row[3][3] = 0.0f;
	}
	TT_INLINE void Init_Perspective_OGL(float left,float right,float bottom,float top,float znear,float zfar)
	{
		Make_Identity();
		Row[0][0] = static_cast<float>(2.0*znear / (right - left));
		Row[0][2] = (right + left) / (right - left);
		Row[1][1] = static_cast<float>(2.0*znear / (top - bottom));
		Row[1][2] = (top + bottom) / (top - bottom);
		Row[2][2] = -(zfar + znear) / (zfar - znear);
		Row[2][3] = static_cast<float>(-(2.0*zfar*znear) / (zfar - znear));
		Row[3][2] = -1.0f;
		Row[3][3] = 0.0f;
	}
	TT_INLINE void Init_Ortho(float left,float right,float bottom,float top,float znear,float zfar)
	{
		Make_Identity();
		Row[0][0] = 2.0f / (right - left);
		Row[0][3] = (left + right) / (left - right);
		Row[1][1] = 2.0f / (top - bottom);
		Row[1][3] = (top + bottom) / (bottom - top);
		Row[2][2] = 1.0f / (znear - zfar);
		Row[2][3] = znear / (znear - zfar);

	}
	TT_INLINE void Init_Perspective(float left,float right,float bottom,float top,float znear,float zfar)
	{
		Make_Identity();
		Row[0][0] = static_cast<float>(2.0*znear / (right - left));
		Row[0][2] = (right + left) / (right - left);
		Row[1][1] = static_cast<float>(2.0*znear / (top - bottom));
		Row[1][2] = (top + bottom) / (top - bottom);
		Row[2][2] = zfar / (znear - zfar);
		Row[2][3] = (znear * zfar) / (znear - zfar);
		Row[3][2] = -1.0f;
		Row[3][3] = 0.0f;
	}

	TT_INLINE Vector4 & operator [] (int i) { return Row[i]; }
	TT_INLINE const Vector4 & operator [] (int i) const { return Row[i]; }
	TT_INLINE Matrix4 Transpose(void) const
	{
		return Matrix4(Vector4(Row[0][0], Row[1][0], Row[2][0], Row[3][0]),Vector4(Row[0][1], Row[1][1], Row[2][1], Row[3][1]),Vector4(Row[0][2], Row[1][2], Row[2][2], Row[3][2]),Vector4(Row[0][3], Row[1][3], Row[2][3], Row[3][3]));
	}
	TT_INLINE float Determinant() const
	{
		float det;
		det =	(Row[0].X * Row[1].Y - Row[0].Y * Row[1].X) * (Row[2].Z * Row[3].W - Row[2].W * Row[3].Z);
		det -=	(Row[0].X * Row[1].Z - Row[0].Z * Row[1].X) * (Row[2].Y * Row[3].W - Row[2].W * Row[3].Y);
		det +=	(Row[0].X * Row[1].W - Row[0].W * Row[1].X) * (Row[2].Y * Row[3].Z - Row[2].Z * Row[3].Y);
		det +=	(Row[0].Y * Row[1].Z - Row[0].Z * Row[1].Y) * (Row[2].X * Row[3].W - Row[2].W * Row[3].X);
		det -=	(Row[0].Y * Row[1].W - Row[0].W * Row[1].Y) * (Row[2].X * Row[3].Z - Row[2].Z * Row[3].X);
		det +=	(Row[0].Z * Row[1].W - Row[0].W * Row[1].Z) * (Row[2].X * Row[3].Y - Row[2].Y * Row[3].X);		
		return det;	
	};	
	TT_INLINE Matrix4 Inverse(void) const
	{
		float s = Determinant();
		if (s == 0.0) return Matrix4();
		s = 1/s;
		Matrix4 t;
		t.Row[0].X = s*(Row[1].Y*(Row[2].Z*Row[3].W - Row[2].W*Row[3].Z) + Row[1].Z*(Row[2].W*Row[3].Y - Row[2].Y*Row[3].W) + Row[1].W*(Row[2].Y*Row[3].Z - Row[2].Z*Row[3].Y));
		t.Row[0].Y = s*(Row[2].Y*(Row[0].Z*Row[3].W - Row[0].W*Row[3].Z) + Row[2].Z*(Row[0].W*Row[3].Y - Row[0].Y*Row[3].W) + Row[2].W*(Row[0].Y*Row[3].Z - Row[0].Z*Row[3].Y));
		t.Row[0].Z = s*(Row[3].Y*(Row[0].Z*Row[1].W - Row[0].W*Row[1].Z) + Row[3].Z*(Row[0].W*Row[1].Y - Row[0].Y*Row[1].W) + Row[3].W*(Row[0].Y*Row[1].Z - Row[0].Z*Row[1].Y));
		t.Row[0].W = s*(Row[0].Y*(Row[1].W*Row[2].Z - Row[1].Z*Row[2].W) + Row[0].Z*(Row[1].Y*Row[2].W - Row[1].W*Row[2].Y) + Row[0].W*(Row[1].Z*Row[2].Y - Row[1].Y*Row[2].Z));
		t.Row[1].X = s*(Row[1].Z*(Row[2].X*Row[3].W - Row[2].W*Row[3].X) + Row[1].W*(Row[2].Z*Row[3].X - Row[2].X*Row[3].Z) + Row[1].X*(Row[2].W*Row[3].Z - Row[2].Z*Row[3].W));
		t.Row[1].Y = s*(Row[2].Z*(Row[0].X*Row[3].W - Row[0].W*Row[3].X) + Row[2].W*(Row[0].Z*Row[3].X - Row[0].X*Row[3].Z) + Row[2].X*(Row[0].W*Row[3].Z - Row[0].Z*Row[3].W));
		t.Row[1].Z = s*(Row[3].Z*(Row[0].X*Row[1].W - Row[0].W*Row[1].X) + Row[3].W*(Row[0].Z*Row[1].X - Row[0].X*Row[1].Z) + Row[3].X*(Row[0].W*Row[1].Z - Row[0].Z*Row[1].W));
		t.Row[1].W = s*(Row[0].Z*(Row[1].W*Row[2].X - Row[1].X*Row[2].W) + Row[0].W*(Row[1].X*Row[2].Z - Row[1].Z*Row[2].X) + Row[0].X*(Row[1].Z*Row[2].W - Row[1].W*Row[2].Z));
		t.Row[2].X = s*(Row[1].W*(Row[2].X*Row[3].Y - Row[2].Y*Row[3].X) + Row[1].X*(Row[2].Y*Row[3].W - Row[2].W*Row[3].Y) + Row[1].Y*(Row[2].W*Row[3].X - Row[2].X*Row[3].W));
		t.Row[2].Y = s*(Row[2].W*(Row[0].X*Row[3].Y - Row[0].Y*Row[3].X) + Row[2].X*(Row[0].Y*Row[3].W - Row[0].W*Row[3].Y) + Row[2].Y*(Row[0].W*Row[3].X - Row[0].X*Row[3].W));
		t.Row[2].Z = s*(Row[3].W*(Row[0].X*Row[1].Y - Row[0].Y*Row[1].X) + Row[3].X*(Row[0].Y*Row[1].W - Row[0].W*Row[1].Y) + Row[3].Y*(Row[0].W*Row[1].X - Row[0].X*Row[1].W));
		t.Row[2].W = s*(Row[0].W*(Row[1].Y*Row[2].X - Row[1].X*Row[2].Y) + Row[0].X*(Row[1].W*Row[2].Y - Row[1].Y*Row[2].W) + Row[0].Y*(Row[1].X*Row[2].W - Row[1].W*Row[2].X));
		t.Row[3].X = s*(Row[1].X*(Row[2].Z*Row[3].Y - Row[2].Y*Row[3].Z) + Row[1].Y*(Row[2].X*Row[3].Z - Row[2].Z*Row[3].X) + Row[1].Z*(Row[2].Y*Row[3].X - Row[2].X*Row[3].Y));
		t.Row[3].Y = s*(Row[2].X*(Row[0].Z*Row[3].Y - Row[0].Y*Row[3].Z) + Row[2].Y*(Row[0].X*Row[3].Z - Row[0].Z*Row[3].X) + Row[2].Z*(Row[0].Y*Row[3].X - Row[0].X*Row[3].Y));
		t.Row[3].Z = s*(Row[3].X*(Row[0].Z*Row[1].Y - Row[0].Y*Row[1].Z) + Row[3].Y*(Row[0].X*Row[1].Z - Row[0].Z*Row[1].X) + Row[3].Z*(Row[0].Y*Row[1].X - Row[0].X*Row[1].Y));
		t.Row[3].W = s*(Row[0].X*(Row[1].Y*Row[2].Z - Row[1].Z*Row[2].Y) + Row[0].Y*(Row[1].Z*Row[2].X - Row[1].X*Row[2].Z) + Row[0].Z*(Row[1].X*Row[2].Y - Row[1].Y*Row[2].X));
		return t;
	}
	TT_INLINE Matrix4 & operator = (const Matrix4 & m)
	{
		Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2]; Row[3] = m.Row[3];
		return *this; 
	}
	TT_INLINE Matrix4 & operator += (const Matrix4 & m)
	{
		Row[0] += m.Row[0]; Row[1] += m.Row[1]; Row[2] += m.Row[2]; Row[3] += m.Row[3];
		return *this; 
	}
	TT_INLINE Matrix4 & operator -= (const Matrix4 & m)
	{
		Row[0] -= m.Row[0]; Row[1] -= m.Row[1]; Row[2] -= m.Row[2]; Row[3] -= m.Row[3];
		return *this; 
	}
	TT_INLINE Matrix4 & operator *= (float d)
	{
		Row[0] *= d; Row[1] *= d; Row[2] *= d; Row[3] *= d;
		return *this;
	}
	TT_INLINE Matrix4 & operator /= (float d)
	{
		float ood = d;
		Row[0] *= ood; Row[1] *= ood; Row[2] *= ood; Row[3] *= ood;
		return *this;
	}
	friend Matrix4 operator - (const Matrix4& a);
	friend Matrix4 operator * (const Matrix4& a,float d);
	friend Matrix4 operator * (float d,const Matrix4& a);
	friend Matrix4 operator / (const Matrix4& a,float d);
	friend Matrix4 operator + (const Matrix4& a, const Matrix4& b);
	friend Matrix4 Add(const Matrix4& a);
	friend Matrix4 operator - (const Matrix4 & a, const Matrix4 & b);
	friend Matrix4 Subtract(const Matrix4 & a, const Matrix4 & b);
	friend Matrix4 operator * (const Matrix4 & a, const Matrix4 & b);
	friend Matrix4 Multiply(const Matrix4 & a, const Matrix4 & b);
	friend Matrix4 operator * (const Matrix4 & a, const Matrix3D & b);
	friend Matrix4 operator * (const Matrix3D & a, const Matrix4 & b);
	friend int operator == (const Matrix4 & a, const Matrix4 & b);
	friend int operator != (const Matrix4 & a, const Matrix4 & b);
	friend void Swap(Matrix4 & a,Matrix4 & b);
	friend Vector4 operator * (const Matrix4 & a, const Vector4 & v);
	friend Vector4 operator * (const Matrix4 & a, const Vector3 & v);
	static void Multiply(const Matrix4 &A,const Matrix4 &B,Matrix4 * set_result);
	static void Multiply(const Matrix3D &A,const Matrix4 &B,Matrix4 * set_result);
	static void Multiply(const Matrix4 &A,const Matrix3D &B,Matrix4 * set_result);
	TT_INLINE static void Transform_Vector(const Matrix4 &A,const Vector3 & in,Vector3 * out)
	{
		Vector3 tmp;
		Vector3 *v;
		if (out == &in)
		{
			tmp = in;
			v = &tmp;
		}
		else
		{
			v = (Vector3 *)&in;
		}
		out->X = (A[0][0] * v->X + A[0][1] * v->Y + A[0][2] * v->Z + A[0][3]);
		out->Y = (A[1][0] * v->X + A[1][1] * v->Y + A[1][2] * v->Z + A[1][3]);
		out->Z = (A[2][0] * v->X + A[2][1] * v->Y + A[2][2] * v->Z + A[2][3]);
	}
	TT_INLINE static void Transform_Vector(const Matrix4 &A,const Vector3 & in,Vector4 * out)
	{
		out->X = (A[0][0] * in.X + A[0][1] * in.Y + A[0][2] * in.Z + A[0][3]);
		out->Y = (A[1][0] * in.X + A[1][1] * in.Y + A[1][2] * in.Z + A[1][3]);
		out->Z = (A[2][0] * in.X + A[2][1] * in.Y + A[2][2] * in.Z + A[2][3]);
		out->W = 1.0f;
	}
	TT_INLINE static void Transform_Vector(const Matrix4 &A,const Vector4 & in,Vector4 * out)
	{
		Vector4 tmp;
		Vector4 * v;
		if (out == &in)
		{
			tmp = in;
			v = &tmp;
		}
		else
		{
			v = (Vector4 *)&in;
		}
		out->X = (A[0][0] * v->X + A[0][1] * v->Y + A[0][2] * v->Z + A[0][3] * v->W);
		out->Y = (A[1][0] * v->X + A[1][1] * v->Y + A[1][2] * v->Z + A[1][3] * v->W);
		out->Z = (A[2][0] * v->X + A[2][1] * v->Y + A[2][2] * v->Z + A[2][3] * v->W);
		out->W = (A[3][0] * v->X + A[3][1] * v->Y + A[3][2] * v->Z + A[3][3] * v->W);
	}
	static Matrix4 ReflectPlane(const PlaneClass& plane); // Expects Ax + By + Cz + D = 0, not WW convention
protected:
	Vector4 Row[4];
};
TT_INLINE Matrix4 operator - (const Matrix4 & a)
{
	return Matrix4(-a.Row[0], -a.Row[1], -a.Row[2], -a.Row[3]); 
}

TT_INLINE Matrix4 operator * (const Matrix4 & a, float d)
{ 
	return Matrix4(a.Row[0] * d, a.Row[1] * d, a.Row[2] * d, a.Row[3] * d); 
}

TT_INLINE Matrix4 operator * (float d, const Matrix4 & a)
{ 
	return a*d; 
}

TT_INLINE Matrix4 operator / (const Matrix4 & a, float d)
{ 
	float ood = 1.0f / d;
	return Matrix4(a.Row[0] * ood, a.Row[1] * ood, a.Row[2] * ood, a.Row[3] * ood); 
}
TT_INLINE Matrix4 operator + (const Matrix4 & a, const Matrix4 & b)
{
	return Matrix4(a.Row[0] + b.Row[0],a.Row[1] + b.Row[1],a.Row[2] + b.Row[2],a.Row[3] + b.Row[3]);
}
TT_INLINE Matrix4 Add(const Matrix4 & a, const Matrix4 & b)
{
	return a+b;
}
TT_INLINE Matrix4 operator - (const Matrix4 & a, const Matrix4 & b)
{
	return Matrix4(a.Row[0] - b.Row[0],a.Row[1] - b.Row[1],a.Row[2] - b.Row[2],a.Row[3] - b.Row[3]);
}
TT_INLINE Matrix4 Subtract(const Matrix4 & a, const Matrix4 & b)
{
	return a-b;
}
TT_INLINE Matrix4 operator * (const Matrix4 & a, const Matrix4 & b)
{
	#define ROWCOL(i, j) a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j] + a[i][3]*b[3][j]
	return Matrix4(Vector4(ROWCOL(0,0), ROWCOL(0,1), ROWCOL(0,2), ROWCOL(0,3)),Vector4(ROWCOL(1,0), ROWCOL(1,1), ROWCOL(1,2), ROWCOL(1,3)),Vector4(ROWCOL(2,0), ROWCOL(2,1), ROWCOL(2,2), ROWCOL(2,3)),Vector4(ROWCOL(3,0), ROWCOL(3,1), ROWCOL(3,2), ROWCOL(3,3)));
	#undef ROWCOL
}
TT_INLINE Matrix4 Multiply(const Matrix4 & a, const Matrix4 & b)
{
	return a*b;
}
TT_INLINE Matrix4 operator * (const Matrix4 & a, const Matrix3D & b)
{
	#define ROWCOL(i,j) a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j]
	#define ROWCOL_LAST(i,j) a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j] + a[i][3]
	return Matrix4(Vector4(ROWCOL(0,0), ROWCOL(0,1), ROWCOL(0,2), ROWCOL_LAST(0,3)),Vector4(ROWCOL(1,0), ROWCOL(1,1), ROWCOL(1,2), ROWCOL_LAST(1,3)),Vector4(ROWCOL(2,0), ROWCOL(2,1), ROWCOL(2,2), ROWCOL_LAST(2,3)),Vector4(ROWCOL(3,0), ROWCOL(3,1), ROWCOL(3,2), ROWCOL_LAST(3,3)));
	#undef ROWCOL
	#undef ROWCOL_LAST
}
TT_INLINE Matrix4 operator * (const Matrix3D & a, const Matrix4 & b)
{
	#define ROWCOL(i,j) a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j] + a[i][3]*b[3][j]
	return Matrix4(Vector4(ROWCOL(0,0), ROWCOL(0,1), ROWCOL(0,2), ROWCOL(0,3)),Vector4(ROWCOL(1,0), ROWCOL(1,1), ROWCOL(1,2), ROWCOL(1,3)),Vector4(ROWCOL(2,0), ROWCOL(2,1), ROWCOL(2,2), ROWCOL(2,3)),Vector4(b[3][0], b[3][1], b[3][2], b[3][3]));
	#undef ROWCOL
}
TT_INLINE Vector4 operator * (const Matrix4 & a, const Vector3 & v)
{
	return Vector4(a[0][0] * v[0] + a[0][1] * v[1] + a[0][2] * v[2] + a[0][3] * 1.0f,a[1][0] * v[0] + a[1][1] * v[1] + a[1][2] * v[2] + a[1][3] * 1.0f,a[2][0] * v[0] + a[2][1] * v[1] + a[2][2] * v[2] + a[2][3] * 1.0f,a[3][0] * v[0] + a[3][1] * v[1] + a[3][2] * v[2] + a[3][3] * 1.0f);
}
TT_INLINE Vector4 operator * (const Matrix4 & a, const Vector4 & v)
{
	return Vector4(a[0][0] * v[0] + a[0][1] * v[1] + a[0][2] * v[2] + a[0][3] * v[3],a[1][0] * v[0] + a[1][1] * v[1] + a[1][2] * v[2] + a[1][3] * v[3],a[2][0] * v[0] + a[2][1] * v[1] + a[2][2] * v[2] + a[2][3] * v[3],a[3][0] * v[0] + a[3][1] * v[1] + a[3][2] * v[2] + a[3][3] * v[3]);
}
#endif
