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
#ifndef TT_INCLUDE__MATRIX3D_H
#define TT_INCLUDE__MATRIX3D_H
#include "vector2.h"
#include "Vector3.h"
#include "Vector4.h"
class Matrix3;
class Matrix4;
class Quaternion;
class PlaneClass;
class SCRIPTS_API Matrix3D
{
protected:
   Vector4 Row[3];
public:
   static Matrix3D Identity;
   TT_INLINE Vector4 & operator [] (int i) { return Row[i]; }
   TT_INLINE const Vector4 & operator [] (int i) const { return Row[i]; }

	TT_INLINE explicit Matrix3D(bool init) { if (init) Make_Identity(); }
	TT_INLINE explicit Matrix3D(float m[12])
	{
		Row[0].Set(m[0],m[1],m[2],m[3]);
		Row[1].Set(m[4],m[5],m[6],m[7]);
		Row[2].Set(m[8],m[9],m[10],m[11]);
	}
	TT_INLINE explicit Matrix3D(const Vector3	&x,const Vector3	&y,const Vector3	&z,const Vector3	&pos)
	{
		Set(x,y,z,pos);
	}
	TT_INLINE explicit Matrix3D(const Vector3	&axis,float angle)
	{
		Set(axis,angle);
	}
	TT_INLINE explicit Matrix3D(const Vector3	&axis,float sine,float cosine)
	{
		Set(axis,sine,cosine);
	}
	TT_INLINE explicit Matrix3D(const Matrix3 & rotation,const Vector3 & position)
	{
		Set(rotation,position);
	}
	TT_INLINE explicit Matrix3D(const Quaternion & rotation,const Vector3 & position)
	{
		Set(rotation,position);
	}
	TT_INLINE explicit Matrix3D(const Vector3 & position)
	{
		Set(position);
	}
	TT_INLINE Matrix3D(const Matrix3D & m)
	{
		Row[0] = m.Row[0];
		Row[1] = m.Row[1];
		Row[2] = m.Row[2];
	}
	TT_INLINE Matrix3D & operator = (const Matrix3D & m)
	{
		Row[0] = m.Row[0];
		Row[1] = m.Row[1];
		Row[2] = m.Row[2];
		return *this; 
	}
   Matrix3D ();
   Matrix3D (float _11, float _12, float _13, float _14,
             float _21, float _22, float _23, float _24,
             float _31, float _32, float _33, float _34);

   void    Get_Orthogonal_Inverse (Matrix3D& target) const;
   float   Get_X_Rotation         () const;
   float   Get_Y_Rotation         () const;
   float   Get_Z_Rotation         () const;
   void    Look_At                (const Vector3&, const Vector3&, float);
   void    Obj_Look_At            (const Vector3&, const Vector3&, float unknown = 0);
   Vector3 Rotate_Vector          (const Vector3& vector) const;
   Vector3 Inverse_Rotate_Vector  (const Vector3& vector) const;
	TT_INLINE void Set(float m[12])
	{
		Row[0].Set(m[0],m[1],m[2],m[3]);
		Row[1].Set(m[4],m[5],m[6],m[7]);
		Row[2].Set(m[8],m[9],m[10],m[11]);
	}
	TT_INLINE void Set(float m11,float m12,float m13,float m14,float m21,float m22,float m23,float m24,float m31,float m32,float m33,float m34)
	{
		Row[0].Set(m11,m12,m13,m14);
		Row[1].Set(m21,m22,m23,m24);
		Row[2].Set(m31,m32,m33,m34);
	}
	TT_INLINE void Set(const Vector3	&x,const Vector3	&y,const Vector3	&z,const Vector3	&pos)
	{
		Row[0].Set(x[0],y[0],z[0],pos[0]);
		Row[1].Set(x[1],y[1],z[1],pos[1]);
		Row[2].Set(x[2],y[2],z[2],pos[2]);
	}
	TT_INLINE void Set(const Vector3 & axis,float angle)
	{
		float c = cosf(angle);
		float s = sinf(angle);
		Set(axis,s,c);
	}
	TT_INLINE void Set(const Vector3 & axis,float s,float c)
	{
		Row[0].Set(
			(float)(axis[0]*axis[0] + c*(1.0f - axis[0]*axis[0])),
			(float)(axis[0]*axis[1]*(1.0f - c) - axis[2]*s),
			(float)(axis[2]*axis[0]*(1.0f - c) + axis[1]*s),
			0.0f
		);
		Row[1].Set(
			(float)(axis[0]*axis[1]*(1.0f - c) + axis[2]*s),
			(float)(axis[1]*axis[1] + c*(1.0f - axis[1]*axis[1])),
			(float)(axis[1]*axis[2]*(1.0f - c) - axis[0]*s),
			0.0f
		);
		Row[2].Set(
			(float)(axis[2]*axis[0]*(1.0f - c) - axis[1]*s),
			(float)(axis[1]*axis[2]*(1.0f - c) + axis[0]*s),
			(float)(axis[2]*axis[2] + c*(1 - axis[2]*axis[2])),
			0.0f
		);
	}
	TT_INLINE void Set(const Vector3 & position)
	{
		Row[0].Set(1.0f,0.0f,0.0f,position[0]);
		Row[1].Set(0.0f,1.0f,0.0f,position[1]);
		Row[2].Set(0.0f,0.0f,1.0f,position[2]);
	}
   void    Set                    (const Matrix3& rotation, const Vector3& position);
   void    Set                    (const Quaternion& rotation, const Vector3& position);
   void    Set_Rotation           (const Quaternion& rotation);
	TT_INLINE Vector3 Get_Translation(void) const { return Vector3(Row[0][3],Row[1][3],Row[2][3]); }
	TT_INLINE void Get_Translation(Vector3 * set) const { set->X = Row[0][3]; set->Y = Row[1][3]; set->Z = Row[2][3]; }
	TT_INLINE void Set_Translation(const Vector3 & t)  { Row[0][3] = t[0]; Row[1][3] = t[1];Row[2][3] = t[2]; }
	void Set_Rotation(const Matrix3 & m);
	TT_INLINE float Get_X_Translation(void) const { return Row[0][3]; };
	TT_INLINE float Get_Y_Translation(void) const { return Row[1][3]; };
	TT_INLINE float Get_Z_Translation(void) const { return Row[2][3]; };
	TT_INLINE void Set_X_Translation(float x) { Row[0][3] = x; };
	TT_INLINE void Set_Y_Translation(float y) { Row[1][3] = y; };
	TT_INLINE void Set_Z_Translation(float z) { Row[2][3] = z; };
	TT_INLINE void Adjust_Translation(const Vector3 & t) { Row[0][3] += t[0]; Row[1][3] += t[1]; Row[2][3] += t[2]; };
	TT_INLINE void Adjust_X_Translation(float x) { Row[0][3] += x; };
	TT_INLINE void Adjust_Y_Translation(float y) { Row[1][3] += y; };
	TT_INLINE void Adjust_Z_Translation(float z) { Row[2][3] += z; };
	TT_INLINE void	Make_Identity(void)
	{
		Row[0].Set(1.0f,0.0f,0.0f,0.0f);
		Row[1].Set(0.0f,1.0f,0.0f,0.0f);
		Row[2].Set(0.0f,0.0f,1.0f,0.0f);
	}
	TT_INLINE void	Translate(float x,float y,float z)
	{
		Row[0][3]  += (float)(Row[0][0]*x + Row[0][1]*y + Row[0][2]*z);
		Row[1][3]  += (float)(Row[1][0]*x + Row[1][1]*y + Row[1][2]*z);
		Row[2][3]  += (float)(Row[2][0]*x + Row[2][1]*y + Row[2][2]*z);
	}
	TT_INLINE void	Translate(const Vector3 &t)
	{
		Row[0][3]  += Row[0][0]*t[0] + Row[0][1]*t[1] + Row[0][2]*t[2];
		Row[1][3]  += Row[1][0]*t[0] + Row[1][1]*t[1] + Row[1][2]*t[2];
		Row[2][3]  += Row[2][0]*t[0] + Row[2][1]*t[1] + Row[2][2]*t[2];
	}
	TT_INLINE void  Translate_X(float x)
	{
		Row[0][3]  += (float)(Row[0][0]*x);
		Row[1][3]  += (float)(Row[1][0]*x);
		Row[2][3]  += (float)(Row[2][0]*x);
	}
	TT_INLINE void  Translate_Y(float y)
	{
		Row[0][3]  += (float)(Row[0][1]*y);
		Row[1][3]  += (float)(Row[1][1]*y);
		Row[2][3]  += (float)(Row[2][1]*y);
	}
	TT_INLINE void  Translate_Z(float z)
	{
		Row[0][3]  += (float)(Row[0][2]*z);
		Row[1][3]  += (float)(Row[1][2]*z);
		Row[2][3]  += (float)(Row[2][2]*z);
	}
	TT_INLINE void	Rotate_X(float theta)
	{
		float tmp1,tmp2;
		float s,c;
		s = sinf(theta);
		c = cosf(theta);
		tmp1 = Row[0][1]; tmp2 = Row[0][2];
		Row[0][1] = (float)( c*tmp1 + s*tmp2);
		Row[0][2] = (float)(-s*tmp1 + c*tmp2);
		tmp1 = Row[1][1]; tmp2 = Row[1][2];
		Row[1][1] = (float)( c*tmp1 + s*tmp2);
		Row[1][2] = (float)(-s*tmp1 + c*tmp2);
		tmp1 = Row[2][1]; tmp2 = Row[2][2];
		Row[2][1] = (float)( c*tmp1 + s*tmp2);
		Row[2][2] = (float)(-s*tmp1 + c*tmp2);
	}
	TT_INLINE void	Rotate_Y(float theta)
	{
		float tmp1,tmp2;
		float s,c;
		s = sinf(theta);
		c = cosf(theta);
		tmp1 = Row[0][0]; tmp2 = Row[0][2];
		Row[0][0] = (float)(c*tmp1 - s*tmp2);
		Row[0][2] = (float)(s*tmp1 + c*tmp2);
		tmp1 = Row[1][0]; tmp2 = Row[1][2];
		Row[1][0] = (float)(c*tmp1 - s*tmp2);
		Row[1][2] = (float)(s*tmp1 + c*tmp2);
		tmp1 = Row[2][0]; tmp2 = Row[2][2];
		Row[2][0] = (float)(c*tmp1 - s*tmp2);
		Row[2][2] = (float)(s*tmp1 + c*tmp2);
	}
	TT_INLINE void 	Rotate_Z(float theta)
	{
		float tmp1,tmp2;
		float c,s;
		c = cosf(theta);
		s = sinf(theta);
		tmp1 = Row[0][0]; tmp2 = Row[0][1];
		Row[0][0] = (float)( c*tmp1 + s*tmp2);
		Row[0][1] = (float)(-s*tmp1 + c*tmp2);
		tmp1 = Row[1][0]; tmp2 = Row[1][1];
		Row[1][0] = (float)( c*tmp1 + s*tmp2);
		Row[1][1] = (float)(-s*tmp1 + c*tmp2);
		tmp1 = Row[2][0]; tmp2 = Row[2][1];
		Row[2][0] = (float)( c*tmp1 + s*tmp2);
		Row[2][1] = (float)(-s*tmp1 + c*tmp2);
	}
	TT_INLINE void	Rotate_X(float s,float c)
	{
		float tmp1,tmp2;
		tmp1 = Row[0][1]; tmp2 = Row[0][2];
		Row[0][1] = (float)( c*tmp1 + s*tmp2);
		Row[0][2] = (float)(-s*tmp1 + c*tmp2);
		tmp1 = Row[1][1]; tmp2 = Row[1][2];
		Row[1][1] = (float)( c*tmp1 + s*tmp2);
		Row[1][2] = (float)(-s*tmp1 + c*tmp2);
		tmp1 = Row[2][1]; tmp2 = Row[2][2];
		Row[2][1] = (float)( c*tmp1 + s*tmp2);
		Row[2][2] = (float)(-s*tmp1 + c*tmp2);
	}
	TT_INLINE void	Rotate_Y(float s,float c)
	{
		float tmp1,tmp2;
		tmp1 = Row[0][0]; tmp2 = Row[0][2];
		Row[0][0] = (float)(c*tmp1 - s*tmp2);
		Row[0][2] = (float)(s*tmp1 + c*tmp2);
		tmp1 = Row[1][0]; tmp2 = Row[1][2];
		Row[1][0] = (float)(c*tmp1 - s*tmp2);
		Row[1][2] = (float)(s*tmp1 + c*tmp2);
		tmp1 = Row[2][0]; tmp2 = Row[2][2];
		Row[2][0] = (float)(c*tmp1 - s*tmp2);
		Row[2][2] = (float)(s*tmp1 + c*tmp2);
	}
	TT_INLINE void	Rotate_Z(float s,float c)
	{
		float tmp1,tmp2;
		tmp1 = Row[0][0]; tmp2 = Row[0][1];
		Row[0][0] = (float)( c*tmp1 + s*tmp2);
		Row[0][1] = (float)(-s*tmp1 + c*tmp2);
		tmp1 = Row[1][0]; tmp2 = Row[1][1];
		Row[1][0] = (float)( c*tmp1 + s*tmp2);
		Row[1][1] = (float)(-s*tmp1 + c*tmp2);
		tmp1 = Row[2][0]; tmp2 = Row[2][1];
		Row[2][0] = (float)( c*tmp1 + s*tmp2);
		Row[2][1] = (float)(-s*tmp1 + c*tmp2);
	}
	TT_INLINE void	Scale(float scale)
	{
		Row[0][0] *= scale;
		Row[1][0] *= scale;
		Row[2][0] *= scale;
		Row[0][1] *= scale;
		Row[1][1] *= scale;
		Row[2][1] *= scale;
		Row[0][2] *= scale;
		Row[1][2] *= scale;
		Row[2][2] *= scale;
	}
	TT_INLINE void	Scale(float x, float y, float z)
	{
		Row[0][0] *= x;
		Row[1][0] *= x;
		Row[2][0] *= x;
		Row[0][1] *= y;
		Row[1][1] *= y;
		Row[2][1] *= y;
		Row[0][2] *= z;
		Row[1][2] *= z;
		Row[2][2] *= z;
	}
	TT_INLINE void	Scale(Vector3 &scale)
	{
		Scale(scale.X, scale.Y, scale.Z);
	}
	TT_INLINE void	Pre_Rotate_X(float theta)
	{
		float tmp1,tmp2;
		float c,s;
		c = cosf(theta);
		s = sinf(theta);
		tmp1 = Row[1][0]; tmp2 = Row[2][0];
		Row[1][0] = (float)(c*tmp1 - s*tmp2);
		Row[2][0] = (float)(s*tmp1 + c*tmp2);
		tmp1 = Row[1][1]; tmp2 = Row[2][1];
		Row[1][1] = (float)(c*tmp1 - s*tmp2);
		Row[2][1] = (float)(s*tmp1 + c*tmp2);
		tmp1 = Row[1][2]; tmp2 = Row[2][2];
		Row[1][2] = (float)(c*tmp1 - s*tmp2);
		Row[2][2] = (float)(s*tmp1 + c*tmp2);
		tmp1 = Row[1][3]; tmp2 = Row[2][3];
		Row[1][3] = (float)(c*tmp1 - s*tmp2);
		Row[2][3] = (float)(s*tmp1 + c*tmp2);
	}
	TT_INLINE void	Pre_Rotate_Y(float theta)
	{
		float tmp1,tmp2;
		float c,s;
		c = cosf(theta);
		s = sinf(theta);
		tmp1 = Row[0][0]; tmp2 = Row[2][0];
		Row[0][0] = (float)( c*tmp1 + s*tmp2);
		Row[2][0] = (float)(-s*tmp1 + c*tmp2);
		tmp1 = Row[0][1]; tmp2 = Row[2][1];
		Row[0][1] = (float)( c*tmp1 + s*tmp2);
		Row[2][1] = (float)(-s*tmp1 + c*tmp2);
		tmp1 = Row[0][2]; tmp2 = Row[2][2];
		Row[0][2] = (float)( c*tmp1 + s*tmp2);
		Row[2][2] = (float)(-s*tmp1 + c*tmp2);
		tmp1 = Row[0][3]; tmp2 = Row[2][3];
		Row[0][3] = (float)( c*tmp1 + s*tmp2);
		Row[2][3] = (float)(-s*tmp1 + c*tmp2);
	}
	TT_INLINE void 	Pre_Rotate_Z(float theta)
	{
		float tmp1,tmp2;
		float c,s;
		c = cosf(theta);
		s = sinf(theta);
		tmp1 = Row[0][0]; tmp2 = Row[1][0];
		Row[0][0] = (float)(c*tmp1 - s*tmp2);
		Row[1][0] = (float)(s*tmp1 + c*tmp2);
		tmp1 = Row[0][1]; tmp2 = Row[1][1];
		Row[0][1] = (float)(c*tmp1 - s*tmp2);
		Row[1][1] = (float)(s*tmp1 + c*tmp2);
		tmp1 = Row[0][2]; tmp2 = Row[1][2];
		Row[0][2] = (float)(c*tmp1 - s*tmp2);
		Row[1][2] = (float)(s*tmp1 + c*tmp2);
		tmp1 = Row[0][3]; tmp2 = Row[1][3];
		Row[0][3] = (float)(c*tmp1 - s*tmp2);
		Row[1][3] = (float)(s*tmp1 + c*tmp2);
	}
	TT_INLINE void	Pre_Rotate_X(float s,float c)
	{
		float tmp1,tmp2;
		tmp1 = Row[1][0]; tmp2 = Row[2][0];
		Row[1][0] = (float)(c*tmp1 - s*tmp2);
		Row[2][0] = (float)(s*tmp1 + c*tmp2);
		tmp1 = Row[1][1]; tmp2 = Row[2][1];
		Row[1][1] = (float)(c*tmp1 - s*tmp2);
		Row[2][1] = (float)(s*tmp1 + c*tmp2);
		tmp1 = Row[1][2]; tmp2 = Row[2][2];
		Row[1][2] = (float)(c*tmp1 - s*tmp2);
		Row[2][2] = (float)(s*tmp1 + c*tmp2);
		tmp1 = Row[1][3]; tmp2 = Row[2][3];
		Row[1][3] = (float)(c*tmp1 - s*tmp2);
		Row[2][3] = (float)(s*tmp1 + c*tmp2);
	}
	TT_INLINE void	Pre_Rotate_Y(float s,float c)
	{
		float tmp1,tmp2;
		tmp1 = Row[0][0]; tmp2 = Row[2][0];
		Row[0][0] = (float)( c*tmp1 + s*tmp2);
		Row[2][0] = (float)(-s*tmp1 + c*tmp2);
		tmp1 = Row[0][1]; tmp2 = Row[2][1];
		Row[0][1] = (float)( c*tmp1 + s*tmp2);
		Row[2][1] = (float)(-s*tmp1 + c*tmp2);
		tmp1 = Row[0][2]; tmp2 = Row[2][2];
		Row[0][2] = (float)( c*tmp1 + s*tmp2);
		Row[2][2] = (float)(-s*tmp1 + c*tmp2);
		tmp1 = Row[0][3]; tmp2 = Row[2][3];
		Row[0][3] = (float)( c*tmp1 + s*tmp2);
		Row[2][3] = (float)(-s*tmp1 + c*tmp2);
	}
	TT_INLINE void	Pre_Rotate_Z(float s,float c)
	{
		float tmp1,tmp2;
		tmp1 = Row[0][0]; tmp2 = Row[1][0];
		Row[0][0] = (float)(c*tmp1 - s*tmp2);
		Row[1][0] = (float)(s*tmp1 + c*tmp2);
		tmp1 = Row[0][1]; tmp2 = Row[1][1];
		Row[0][1] = (float)(c*tmp1 - s*tmp2);
		Row[1][1] = (float)(s*tmp1 + c*tmp2);
		tmp1 = Row[0][2]; tmp2 = Row[1][2];
		Row[0][2] = (float)(c*tmp1 - s*tmp2);
		Row[1][2] = (float)(s*tmp1 + c*tmp2);
		tmp1 = Row[0][3]; tmp2 = Row[1][3];
		Row[0][3] = (float)(c*tmp1 - s*tmp2);
		Row[1][3] = (float)(s*tmp1 + c*tmp2);
	}
	TT_INLINE void	In_Place_Pre_Rotate_X(float theta)
	{
		float tmp1,tmp2;
		float c,s;
		c = cosf(theta);
		s = sinf(theta);
		tmp1 = Row[1][0]; tmp2 = Row[2][0];
		Row[1][0] = (float)(c*tmp1 - s*tmp2);
		Row[2][0] = (float)(s*tmp1 + c*tmp2);
		tmp1 = Row[1][1]; tmp2 = Row[2][1];
		Row[1][1] = (float)(c*tmp1 - s*tmp2);
		Row[2][1] = (float)(s*tmp1 + c*tmp2);
		tmp1 = Row[1][2]; tmp2 = Row[2][2];
		Row[1][2] = (float)(c*tmp1 - s*tmp2);
		Row[2][2] = (float)(s*tmp1 + c*tmp2);
	}
	TT_INLINE void	In_Place_Pre_Rotate_Y(float theta)
	{
		float tmp1,tmp2;
		float c,s;
		c = cosf(theta);
		s = sinf(theta);
		tmp1 = Row[0][0]; tmp2 = Row[2][0];
		Row[0][0] = (float)( c*tmp1 + s*tmp2);
		Row[2][0] = (float)(-s*tmp1 + c*tmp2);
		tmp1 = Row[0][1]; tmp2 = Row[2][1];
		Row[0][1] = (float)( c*tmp1 + s*tmp2);
		Row[2][1] = (float)(-s*tmp1 + c*tmp2);
		tmp1 = Row[0][2]; tmp2 = Row[2][2];
		Row[0][2] = (float)( c*tmp1 + s*tmp2);
		Row[2][2] = (float)(-s*tmp1 + c*tmp2);
	}
	TT_INLINE void 	In_Place_Pre_Rotate_Z(float theta)
	{
		float tmp1,tmp2;
		float c,s;
		c = cosf(theta);
		s = sinf(theta);
		tmp1 = Row[0][0]; tmp2 = Row[1][0];
		Row[0][0] = (float)(c*tmp1 - s*tmp2);
		Row[1][0] = (float)(s*tmp1 + c*tmp2);
		tmp1 = Row[0][1]; tmp2 = Row[1][1];
		Row[0][1] = (float)(c*tmp1 - s*tmp2);
		Row[1][1] = (float)(s*tmp1 + c*tmp2);
		tmp1 = Row[0][2]; tmp2 = Row[1][2];
		Row[0][2] = (float)(c*tmp1 - s*tmp2);
		Row[1][2] = (float)(s*tmp1 + c*tmp2);
	}
	TT_INLINE void	In_Place_Pre_Rotate_X(float s,float c)
	{
		float tmp1,tmp2;
		tmp1 = Row[1][0]; tmp2 = Row[2][0];
		Row[1][0] = (float)(c*tmp1 - s*tmp2);
		Row[2][0] = (float)(s*tmp1 + c*tmp2);
		tmp1 = Row[1][1]; tmp2 = Row[2][1];
		Row[1][1] = (float)(c*tmp1 - s*tmp2);
		Row[2][1] = (float)(s*tmp1 + c*tmp2);
		tmp1 = Row[1][2]; tmp2 = Row[2][2];
		Row[1][2] = (float)(c*tmp1 - s*tmp2);
		Row[2][2] = (float)(s*tmp1 + c*tmp2);
	}
	TT_INLINE void	In_Place_Pre_Rotate_Y(float s,float c)
	{
		float tmp1,tmp2;
		tmp1 = Row[0][0]; tmp2 = Row[2][0];
		Row[0][0] = (float)( c*tmp1 + s*tmp2);
		Row[2][0] = (float)(-s*tmp1 + c*tmp2);
		tmp1 = Row[0][1]; tmp2 = Row[2][1];
		Row[0][1] = (float)( c*tmp1 + s*tmp2);
		Row[2][1] = (float)(-s*tmp1 + c*tmp2);
		tmp1 = Row[0][2]; tmp2 = Row[2][2];
		Row[0][2] = (float)( c*tmp1 + s*tmp2);
		Row[2][2] = (float)(-s*tmp1 + c*tmp2);
	}
	TT_INLINE void	In_Place_Pre_Rotate_Z(float s,float c)
	{
		float tmp1,tmp2;
		tmp1 = Row[0][0]; tmp2 = Row[1][0];
		Row[0][0] = (float)(c*tmp1 - s*tmp2);
		Row[1][0] = (float)(s*tmp1 + c*tmp2);
		tmp1 = Row[0][1]; tmp2 = Row[1][1];
		Row[0][1] = (float)(c*tmp1 - s*tmp2);
		Row[1][1] = (float)(s*tmp1 + c*tmp2);
		tmp1 = Row[0][2]; tmp2 = Row[1][2];
		Row[0][2] = (float)(c*tmp1 - s*tmp2);
		Row[1][2] = (float)(s*tmp1 + c*tmp2);
	}

	int	Is_Orthogonal(void) const; 
   Matrix3D& operator *= (const Matrix3D& matrix);
   Vector3 operator * (const Vector3& vector) const;
   static void Transform_Vector(const Matrix3D & A,const Vector3 & in,Vector3 * out)
   {
		Vector3 tmp;
		Vector3 * v;
		if (out == &in)
		{
			tmp = in;
			v = &tmp;
		}
		else
		{
			v = (Vector3 *)&in;
		}
		out->X = (A.Row[0][0] * v->X + A.Row[0][1] * v->Y + A.Row[0][2] * v->Z + A.Row[0][3]);
		out->Y = (A.Row[1][0] * v->X + A.Row[1][1] * v->Y + A.Row[1][2] * v->Z + A.Row[1][3]);
		out->Z = (A.Row[2][0] * v->X + A.Row[2][1] * v->Y + A.Row[2][2] * v->Z + A.Row[2][3]);
   }
	TT_INLINE Vector3 Get_X_Vector() const { return Vector3(Row[0][0], Row[1][0], Row[2][0]); }
	TT_INLINE Vector3 Get_Y_Vector() const { return Vector3(Row[0][1], Row[1][1], Row[2][1]); }
	TT_INLINE Vector3 Get_Z_Vector() const { return Vector3(Row[0][2], Row[1][2], Row[2][2]); }
	TT_INLINE void Get_X_Vector(Vector3 * set_x) const { set_x->Set(Row[0][0], Row[1][0], Row[2][0]); }
	TT_INLINE void Get_Y_Vector(Vector3 * set_y) const { set_y->Set(Row[0][1], Row[1][1], Row[2][1]); }
	TT_INLINE void Get_Z_Vector(Vector3 * set_z) const { set_z->Set(Row[0][2], Row[1][2], Row[2][2]); }
	void Get_Inverse(Matrix3D & set_inverse) const;
	void Copy_3x3_Matrix(float matrix[3][3]);
	void Transform_Min_Max_AABox(const Vector3 & min,const Vector3 & max,Vector3 * set_min,Vector3 * set_max) const;
	void Transform_Center_Extent_AABox(const Vector3 & center,const Vector3 & extent,Vector3 * set_center,Vector3 * set_extent) const;
	static void	Multiply(const Matrix3D &A,const Matrix3D &B,Matrix3D * set_result);
	static TT_INLINE void	Rotate_Vector(const Matrix3D & A,const Vector3 & in,Vector3 * out)
	{
		Vector3 tmp;
		Vector3 * v;
		if (out == &in)
		{
			tmp = in;
			v = &tmp;
		}
		else 
		{
			v = (Vector3 *)&in;
		}
		out->X = (A[0][0] * v->X + A[0][1] * v->Y + A[0][2] * v->Z);
		out->Y = (A[1][0] * v->X + A[1][1] * v->Y + A[1][2] * v->Z);
		out->Z = (A[2][0] * v->X + A[2][1] * v->Y + A[2][2] * v->Z);
	}
	static TT_INLINE void	Inverse_Transform_Vector(const Matrix3D & A,const Vector3 & in,Vector3 * out)
	{
		Vector3 tmp;
		Vector3 * v;
		if (out == &in)
		{
			tmp = in;
			v = &tmp;
		}
		else
		{
			v = (Vector3 *)&in;
		}
		Vector3 diff(v->X - A[0][3], v->Y - A[1][3], v->Z - A[2][3]);
		Matrix3D::Inverse_Rotate_Vector(A, diff, out);
	}
	static TT_INLINE void	Inverse_Rotate_Vector(const Matrix3D & A,const Vector3 & in,Vector3 * out)
	{
		Vector3 tmp;
		Vector3 * v;
		if (out == &in)
		{
			tmp = in;
			v = &tmp;
		}
		else
		{
			v = (Vector3 *)&in;
		}
		out->X = (A[0][0] * v->X + A[1][0] * v->Y + A[2][0] * v->Z);
		out->Y = (A[0][1] * v->X + A[1][1] * v->Y + A[2][1] * v->Z);
		out->Z = (A[0][2] * v->X + A[1][2] * v->Y + A[2][2] * v->Z);
	}
	static Matrix3D Reflect_Plane(const PlaneClass& _plane);
	PlaneClass Transform_Plane(const PlaneClass& _plane) const;
	static bool Solve_Linear_System(Matrix3D & system);
	void	Re_Orthogonalize(void);
}; // 48

TT_INLINE Matrix3D operator * (const Matrix3D &A,const Matrix3D &B)
{
	Matrix3D C;
	float tmp1,tmp2,tmp3;
	tmp1 = B[0][0];
	tmp2 = B[1][0];
	tmp3 = B[2][0];
	C[0][0] = (float)(A[0][0]*tmp1 + A[0][1]*tmp2 + A[0][2]*tmp3);
	C[1][0] = (float)(A[1][0]*tmp1 + A[1][1]*tmp2 + A[1][2]*tmp3);
	C[2][0] = (float)(A[2][0]*tmp1 + A[2][1]*tmp2 + A[2][2]*tmp3);
	tmp1 = B[0][1];
	tmp2 = B[1][1];
	tmp3 = B[2][1];
	C[0][1] = (float)(A[0][0]*tmp1 + A[0][1]*tmp2 + A[0][2]*tmp3);
	C[1][1] = (float)(A[1][0]*tmp1 + A[1][1]*tmp2 + A[1][2]*tmp3);
	C[2][1] = (float)(A[2][0]*tmp1 + A[2][1]*tmp2 + A[2][2]*tmp3);
	tmp1 = B[0][2];
	tmp2 = B[1][2];
	tmp3 = B[2][2];
	C[0][2] = (float)(A[0][0]*tmp1 + A[0][1]*tmp2 + A[0][2]*tmp3);
	C[1][2] = (float)(A[1][0]*tmp1 + A[1][1]*tmp2 + A[1][2]*tmp3);
	C[2][2] = (float)(A[2][0]*tmp1 + A[2][1]*tmp2 + A[2][2]*tmp3);
	tmp1 = B[0][3];
	tmp2 = B[1][3];
	tmp3 = B[2][3];
	C[0][3] = (float)(A[0][0]*tmp1 + A[0][1]*tmp2 + A[0][2]*tmp3 + A[0][3]);
	C[1][3] = (float)(A[1][0]*tmp1 + A[1][1]*tmp2 + A[1][2]*tmp3 + A[1][3]);
	C[2][3] = (float)(A[2][0]*tmp1 + A[2][1]*tmp2 + A[2][2]*tmp3 + A[2][3]);
	return C;
}
TT_INLINE bool operator == (const Matrix3D &A, const Matrix3D &B)
{
   return (A[0].X == B[0].X && A[0].Y == B[0].Y && A[0].Z == B[0].Z && A[0].W == B[0].W
        && A[1].X == B[1].X && A[1].Y == B[1].Y && A[1].Z == B[1].Z && A[1].W == B[1].W
        && A[2].X == B[2].X && A[2].Y == B[2].Y && A[2].Z == B[2].Z && A[2].W == B[2].W);
}

TT_INLINE bool operator != (const Matrix3D &A, const Matrix3D &B)
{
	return !(A == B);
}
#endif
