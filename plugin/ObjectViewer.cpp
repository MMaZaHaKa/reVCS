// MIT лицензия By MaZaHaKa
#pragma once
#include "../core/common.h"
#include "../audio/AudioManager.h"
#include "../audio/DMAudio.h"
#include "../audio/MusicManager.h"
#include "../audio/sampman.h"
#include "../core/Camera.h"
#include "../core/Clock.h"
#include "../core/FileLoader.h"
#include "../core/FileMgr.h"
#include "../core/Frontend.h"
#include "../core/Pad.h"
#include "../core/PlayerInfo.h"
#include "../core/World.h"
#include "../entities/Entity.h"
#include "../extras/custompipes.h"
#include "../peds/CivilianPed.h"
#include "../peds/Ped.h"
#include "../peds/PlayerPed.h"
#include "../renderer/Font.h"
#include "../rw/TxdStore.h"
#include "../utils/Utils.h"
#include "../vehicles/CarGen.h"
#include "../vehicles/Vehicle.h"
#include "../weapons/WeaponInfo.h"
#include "../core/Streaming.h"
#include "Object.h"

//#include "../utils/Utils.h"
#include "../utils/ConsoleTools.h"

#include "ObjectViewer.h"
#include "Windows.h"
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <conio.h>

namespace PLG_ObjectViewer
{

CObject *
CreateObject(int mi, CVector pos, float scale = 1.0f)
{
	CStreaming::RequestModel(mi, STREAMFLAGS_DONT_REMOVE); // StreamFlags::STREAMFLAGS_DONT_REMOVE
	CStreaming::LoadAllRequestedModels(false); // false
	if(!CStreaming::HasModelLoaded(mi)) { return nil; }

	CObject *pObj = new CObject(mi, true); // false
	pObj->ObjectCreatedBy = MISSION_OBJECT;
	if(pos.z <= MAP_Z_LOW_LIMIT) pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
	pos.z += pObj->GetDistanceFromCentreOfMassToBaseOfModel();

	// if(scale != 1.0f) { pObj->GetMatrix().SetScale(scale); }
	/*pObj->m_objectMatrix.Scale(scale);
	pObj->UpdateRwFrame();
	pObj->GetMatrix().Update();
	pObj->GetMatrix().UpdateRW();
	RwV3d scalemat;
	scalemat.x = scale;
	scalemat.y = scale;
	scalemat.z = scale;*/
	// pObj->GetMatrix().SetScale(1.0f);
	// RwMatrixScale(pObj->m_objectMatrix.Scale(scale), &scalemat, rwCOMBINEPRECONCAT);

	pObj->m_objectMatrix.Scale(2.0);
	pObj->GetMatrix().Update();
	// pObj->GetMatrix().SetScale(2.0f);
	pObj->SetPosition(pos);
	pObj->SetOrientation(0.0f, 0.0f, 0.0f);
	pObj->GetMatrix().UpdateRW();
	pObj->UpdateRwFrame();
	// pObj->UpdateRwFrame();
	pObj->SetStatus(STATUS_PHYSICS);
	CWorld::Add(pObj);
	// int index = CPools::GetObjectPool()->GetIndex(pObj);
	return pObj;
}


void Printstr(std::string astr, int x, int y, CRGBA col)
{

	char str[200];
	wchar ustr[200];

	//sprintf(str, "X:%5.1f, Y:%5.1f, Z:%5.1f, F-%d, %s", pos.x, pos.y, pos.z, (int32)FramesPerSecond, ZonePrint[ZoneId].name);
	strcpy(str, astr.c_str());
	AsciiToUnicode(str, ustr);

	CFont::SetPropOff();
	CFont::SetBackgroundOff();
	CFont::SetCentreOff();
	CFont::SetRightJustifyOff();
	CFont::SetJustifyOff();
	CFont::SetBackGroundOnlyTextOff();
	//CFont::SetWrapx(SCREEN_STRETCH_X(DEFAULT_SCREEN_WIDTH));
	CFont::SetFontStyle(FONT_STANDARD);
	CFont::SetColor(col);
	CFont::PrintString(x, y, ustr);
}

int curr_pos = MI_BANSHEE;
int spawned_id = -1;
CObject *obj = nil;
bool mode = false;
bool bf = false;
void
OV_PROCESS()
{
	// CStreaming::LoadCdDirectory(const char *dirname, int n) models
	//ms_aInfoForModel
	//std::cout << getch() << "\n";
	int slms = 120;
	int max_id = MODELINFOSIZE - 1;
	CRGBA col = CRGBA(255, 108, 0, 255);
	bool sh = (GetAsyncKeyState(VK_SHIFT) & 0x8000);
	if((GetAsyncKeyState(VK_F4) & 0x8000)) { mode = !mode; /*CWorld::Players[0].MakePlayerSafe(mode);*/ Sleep(slms); }
	//if(!mode) { spawned_id = -1; curr_pos = 0; }
	if(!mode) { return; }
	CBaseModelInfo* mi = CModelInfo::GetModelInfo(curr_pos);
	if (!mi) {
		while(true) {
			mi = CModelInfo::GetModelInfo(bf ? --curr_pos: ++curr_pos);
			if(mi || (curr_pos >= max_id)) { break; }
		}
	}
	std::string obj_name = (mi && mi->GetModelName() && (std::string(mi->GetModelName()) != "")) ? mi->GetModelName() : "--";
	Printstr("Object Viewer Mode. CURR ID: " + std::to_string(curr_pos) + " NAME: " + obj_name, SCREEN_SCALE_X(10.0f), 1080 / 2, col);

	if((GetAsyncKeyState(VK_F6) & 0x8000)) { if(curr_pos > 0){ if(sh){curr_pos-=10;} else{ --curr_pos; } bf = true; Sleep(slms);} } // todo +10 check bounds
	if((GetAsyncKeyState(VK_F7) & 0x8000)) { if(curr_pos < max_id){ if(sh){curr_pos+=10;} else{ ++curr_pos; } bf = false; Sleep(slms);} }
	if(curr_pos > max_id) { curr_pos = max_id; }
	if(curr_pos < 0) { curr_pos = 0; }

	mi = CModelInfo::GetModelInfo(curr_pos);
	if(mi && mi->GetModelName() && (std::string(mi->GetModelName()) != "")) {
		CStreaming::RequestModel(curr_pos, 0); // StreamFlags::STREAMFLAGS_DONT_REMOVE
		CStreaming::LoadAllRequestedModels(false);             // false

		//if(curr_pos != spawned_id)
		if(GetAsyncKeyState(VK_F8) & 0x8000)
		{
			//Sleep(slms);
			// EX_MISC gtafw
			CVector spos = (FindPlayerPed()->GetPosition() + CVector(0.0f, 0.0f, 2.5f) + FindPlayerPed()->GetForward() * 5.0f);
			CVector leftVector = -FindPlayerPed()->GetRight();
			CVector orie = CVector(0.0f, 0.0f, leftVector.Heading());
			spos.z = FindPlayerPed()->GetPosition().z;

			//COMMAND_DELETE_OBJECT
			if(obj) {
				CWorld::Remove(obj);
				CWorld::RemoveReferencesToDeletedObject(obj);
				delete obj;
			}

			obj = CreateObject(curr_pos, spos); // palette
			obj->SetOrientation(orie.x, orie.y, orie.z);

			//obj
			spawned_id = curr_pos;
		}
	}
}


//-------------------------
void
PLG_OnStart()
{

}

void
PLG_OnInit()
{

}

void
PLG_OnDraw()
{
	OV_PROCESS();
}

void
PLG_OnShutdown()
{

}

} // namespace PLG_ObjectViewer