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
#pragma once
class NH_Spawn_Object_On_Poke : public ScriptImpClass {
	int spawn;
	void Created(GameObject *obj);
	void Damaged(GameObject *obj,GameObject *damager,float amount);
	void Custom(GameObject *obj,int type,int param,GameObject *sender);
	void Timer_Expired(GameObject *obj,int number);
};

class NH_SetTeam_OnLeave : public ScriptImpClass {
	void Custom(GameObject *obj,int type,int param,GameObject *sender);
};

class NH_Deploy_Building_On_Poke : public ScriptImpClass {
	void Death(GameObject *obj,GameObject *killer);
};

class NH_Create_Buy_Panels : public ScriptImpClass {
	int panel1;
	int panel2;
	int panel3;
	int panel4;
	void Created(GameObject *obj);
	void Death(GameObject *obj,GameObject *killer);
	public: void Register_Auto_Save_Variables();
};
