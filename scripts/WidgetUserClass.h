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
#ifndef TT_INCLUDE__WIDGETUSERCLASS_H
#define TT_INCLUDE__WIDGETUSERCLASS_H


class WidgetRenderOpClass;
class WidgetUserClass
{
public:
	WidgetUserClass() {}
	~WidgetUserClass() {}
#ifdef PARAM_EDITING_ON
	virtual void	Add_Debug_Point(const Vector3 & p,const Vector3 & color);
	virtual void	Add_Debug_Vector(const Vector3 & p,const Vector3 & v,const Vector3 & color);
	virtual void	Add_Debug_AABox(const AABoxClass & box,const Vector3 & color,float opacity = 0.25f);
	virtual void	Add_Debug_OBBox(const OBBoxClass & box,const Vector3 & color,float opacity = 0.25f);
	virtual void	Add_Debug_Axes(const Matrix3D & transform,const Vector3 & color);
	WidgetRenderOpClass *			WidgetRenderOpList;
#endif
};

#endif
