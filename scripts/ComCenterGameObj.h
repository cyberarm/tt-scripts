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
#ifndef TT_INCLUDE_COMCENTERGAMEOBJ_H
#define TT_INCLUDE_COMCENTERGAMEOBJ_H
#include "BuildingGameObj.h"
class ComCenterGameObjDef;
class ComCenterGameObj : public BuildingGameObj
{
public:
	ComCenterGameObj (void);
	~ComCenterGameObj (void);
	virtual	void					Init( void );
	void								Init (const ComCenterGameObjDef & definition);
	SCRIPTS_API const ComCenterGameObjDef &	Get_Definition (void) const;
	ComCenterGameObj *				As_ComCenterGameObj (void)	{ return this; }
	bool									Save (ChunkSaveClass &csave);
	bool									Load (ChunkLoadClass &cload);
	const	PersistFactoryClass &	Get_Factory (void) const;
	void					On_Destroyed (void);
	void					On_Revived (void);
private:
	void					Load_Variables (ChunkLoadClass &cload);	
};

#endif