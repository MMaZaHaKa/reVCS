#pragma once
#include "common.h"
#include "Object.h"


enum eFERRIS_MODE
{
    FERRIS_MODE_START = 0,    // Запуск (начало вращения)
    FERRIS_MODE_ROTATE = 1,   // Вращение (колесо вращается)
    FERRIS_MODE_SLOW_DOWN = 2, // Замедление (уменьшение скорости)
    FERRIS_MODE_STOP = 3       // Остановка (колесо остановлено)
};

#define FerrisWheelCabinsCount 12
class CFerrisWheel // todo maybe CFerrisWheels.process -> CFerrisWheel.Update
{
	static bool bCurrentFerrisState;
	static bool ferris_byte_486032; // todo
	static eFERRIS_MODE Mode;
	static bool loaded_ferris_model_byte_486033; // todo
	static CBuilding* pFerrisWheel;
	static CObject* m_aCabins[FerrisWheelCabinsCount]; // ObjectPool Indicies by comm 1226
	static float fRotationSpeed;
	static float fCurrentRotationAngle;
	static float fTargetRotationAngle;
public:
	static void Init(); // 1755E0 delegate check todo if need
	static void Update();
	static void Shutdown();
	static void UpdateCabins();
	static void ShutdownCabins();
	static void TurnOff(); // op 1223
	static void TurnOn(); // op 1224
	static bool CheckMode(); // op 1225 todo normal RE name
	static CObject *GetCabineObjectPointerByIndex(uint32_t n); // op 1226 04CA: unknown_get_object_command_4814 index 39@ store_to 25@ :FERRIS_1160
	// ops 1223 1224 1225 1226
};