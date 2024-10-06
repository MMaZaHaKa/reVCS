#pragma once
#include "common.h"
#include "Camera.h"
#include "Pools.h"
#include "FerrisWheel.h"


bool CFerrisWheel::bCurrentFerrisState = false;
bool CFerrisWheel::ferris_byte_486032 = false;
eFERRIS_MODE CFerrisWheel::Mode = eFERRIS_MODE::FERRIS_MODE_START; // ?
bool CFerrisWheel::loaded_ferris_model_byte_486033 = false;
CBuilding* CFerrisWheel::pFerrisWheel = nil;
CObject* CFerrisWheel::m_aCabins[FerrisWheelCabinsCount] = { 0 };
float CFerrisWheel::fRotationSpeed = 0.0f;
float CFerrisWheel::fCurrentRotationAngle = 0.0f;
float CFerrisWheel::fTargetRotationAngle = 0.0f;

void CFerrisWheel::Init() // vcs degegate or CFerrisWheels::Init()
{
	//debug("CFerrisWheel::Init()\n");
	for(int32_t i = FerrisWheelCabinsCount - 1; i >= 0; --i) { CFerrisWheel::m_aCabins[i] = nil; }
	CFerrisWheel::pFerrisWheel = nil;

	//CPools::GetObjectPool()->GetIndex(pObj)
	int i, n; // RequestBigBuildings
	CBuilding *b;
	n = CPools::GetBuildingPool()->GetSize() - 1;

	int id = -1;
	// CBaseModelInfo *mi = CModelInfo::GetModelInfo(306); // vcs 306 wheel, 308 cabin todo mi
	// hash_ec61dff2 подставка,  nbeachw.ipl 5499,5527 LODris_wheel/ferris_wheel
	CBaseModelInfo *mi = CModelInfo::GetModelInfo("ferris_wheel", &id); // my LODris_wheel/ferris_wheel 5527, 5499

	if(n != -1) {
		for(i = n; i >= 0; i--) {
			b = CPools::GetBuildingPool()->GetSlot(i);
			//assert(b);
			// check COMMAND_GET_RANDOM_CAR_OF_TYPE_IN_AREA 502
			if(b && mi && b->GetModelIndex() == id) {
				CFerrisWheel::pFerrisWheel = b;
				debug("CFerrisWheel::pFerrisWheel FOUND !!!!!!\n");
				break;
			}
		}
	}
}

void
CFerrisWheel::Update()
{
	//debug("CFerrisWheel::Update()\n");
	if(!CFerrisWheel::pFerrisWheel) { return; }
	//float distance = (pFerrisWheel->GetPosition() - TheCamera.GetPosition()).Magnitude(); // thx COMMAND_IS_PLAYER_TARGETTING_OBJECT
	float distance = (TheCamera.GetPosition() - pFerrisWheel->GetPosition()).MagnitudeSqr(); // thx chgpt MagnitudeSqr
	// TODO VCS: fix bugs draw distance include here
	if(distance <= 90000.0) { // 90k MagnitudeSqr simplify math load
		//debug("distance: %f\n", distance);
		if(distance < 75625.0) { CFerrisWheel::UpdateCabins(); }
	} else {
		CFerrisWheel::ShutdownCabins(); // need once??
	}



	{
		CMatrix& mat = pFerrisWheel->GetMatrix();
		CVector pos;
		float speed = 1.5f; //+1.0f;
		// speed = 2.0 + m_fGasPedal;
		//int node = eCarNodes::CAR_BONNET;
		//mat.Attach(RwFrameGetMatrix(m_aCarNodes[node]));
		pos = mat.GetPosition();
		mat.SetRotateX(fCurrentRotationAngle);
		mat.Translate(pos);
		//mat.Update();
		mat.UpdateRW();

		fCurrentRotationAngle += 3.14f / speed;
		if(fCurrentRotationAngle > 6.28f) fCurrentRotationAngle -= 6.28f;

		//mat.Attach(RwFrameGetMatrix(m_aCarNodes[node]));
		//pos = mat.GetPosition();
		//mat.SetRotateX(fCurrentRotationAngle);
		//mat.Translate(pos);
		//mat.UpdateRW();
	}




	if(CFerrisWheel::Mode == eFERRIS_MODE::FERRIS_MODE_ROTATE) {
		if(CFerrisWheel::bCurrentFerrisState) {
			CFerrisWheel::bCurrentFerrisState = false;
			CFerrisWheel::Mode = eFERRIS_MODE::FERRIS_MODE_SLOW_DOWN;
		}
	} else if(CFerrisWheel::Mode >= eFERRIS_MODE::FERRIS_MODE_SLOW_DOWN) {
		if(CFerrisWheel::Mode == eFERRIS_MODE::FERRIS_MODE_SLOW_DOWN) {

		} else if(CFerrisWheel::Mode == eFERRIS_MODE::FERRIS_MODE_STOP) {

		}
	} else if(!CFerrisWheel::Mode) // eFERRIS_MODE::FERRIS_MODE_START
	{
		//if() {
		//	CFerrisWheel::Mode = eFERRIS_MODE::FERRIS_MODE_ROTATE;
		//}
	}
}

void
CFerrisWheel::Shutdown()
{
	// debug("CFerrisWheel::Shutdown()\n");

}



void
CFerrisWheel::UpdateCabins()
{
	//debug("CFerrisWheel::UpdateCabins()\n");
	// todo find cabin model index + model name
}

void
CFerrisWheel::ShutdownCabins()
{
	 //debug("CFerrisWheel::ShutdownCabins()\n");
}


void
CFerrisWheel::TurnOn()
{
	if(CFerrisWheel::Mode != eFERRIS_MODE::FERRIS_MODE_ROTATE) {
		CFerrisWheel::Mode = eFERRIS_MODE::FERRIS_MODE_START;
		CFerrisWheel::bCurrentFerrisState = false;
	}
}

void
CFerrisWheel::TurnOff()
{
	CFerrisWheel::bCurrentFerrisState = true;
}

bool
CFerrisWheel::CheckMode() { return CFerrisWheel::Mode == eFERRIS_MODE::FERRIS_MODE_STOP; }

CObject*
CFerrisWheel::GetCabineObjectPointerByIndex(uint32_t n) // COMMAND_GET_FERRIS_WHEEL_CABINE
{
	assert(n >= 0);
	assert(n < FerrisWheelCabinsCount);
	return CFerrisWheel::m_aCabins[n];
}