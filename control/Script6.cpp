#include "common.h"

#include "Script.h"
#include "ScriptCommands.h"

#include "Bike.h"
#include "CarCtrl.h"
#include "Cranes.h"
#include "Credits.h"
#include "CutsceneMgr.h"
#include "DMAudio.h"
#include "FileMgr.h"
#include "Fire.h"
#include "Frontend.h"
#include "Garages.h"
#include "General.h"
#ifdef MISSION_REPLAY
#include "GenericGameStorage.h"
#endif
#include "Hud.h"
#include "Messages.h"
#include "Pad.h"
#include "Particle.h"
#include "Phones.h"
#include "Population.h"
#include "Pools.h"
#include "Record.h"
#include "Remote.h"
#include "Restart.h"
#include "SpecialFX.h"
#include "Stats.h"
#include "Streaming.h"
#include "Weather.h"
#include "Zones.h"
#include "main.h"
#include "GameLogic.h"
#include "Sprite.h"
#include "CarAI.h"
#include "Pickups.h"
#include "Fluff.h"
#include "CustomSoundTrack.h"
//new
#include "User.h"
#pragma optimize("", off) // tmp 4 dbg

// LCS: file done except TODOs

#ifdef USE_DEBUG_SCRIPT_LOADER
extern const char* scriptfile;
#endif

bool CRunningScript::ThisIsAValidRandomCop(uint32 mi, int cop, int swat, int fbi, int army, int miami)
{
	switch (mi)
	{
	case MI_COP: if (cop) return true; break;
	case MI_SWAT: if (swat) return true; break;
	case MI_FBI: if (fbi) return true; break;
	case MI_ARMY: if (army) return true; break;
	default: if (mi >= MI_VICE1 && mi <= MI_VICE8 && miami) return true; break;
	}
	return false;
}

bool CRunningScript::ThisIsAValidRandomPed(uint32 pedtype, int civ, int gang, int criminal)
{
    switch (pedtype) {
    case PEDTYPE_CIVMALE:
    case PEDTYPE_CIVFEMALE:
        return civ;
    case PEDTYPE_GANG1:
    case PEDTYPE_GANG2:
    case PEDTYPE_GANG3:
    case PEDTYPE_GANG4:
    case PEDTYPE_GANG5:
    case PEDTYPE_GANG6:
    case PEDTYPE_GANG7:
    case PEDTYPE_GANG8:
    case PEDTYPE_GANG9:
        return gang;
    case PEDTYPE_CRIMINAL:
    case PEDTYPE_PROSTITUTE:
        return criminal;
    default:
        return false;
    }
}

int8 CRunningScript::ProcessCommands1000To1099(int32 command)
{
	switch (command) {
	case COMMAND_DETACH_OBJECT_FROM_CAR:
	{
		CollectParameters(&m_nIp, 1);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		// if (pObject && pObject->m_pAttachedTo)
		//	pObject->DettachObjectFromEntity();
		return 0;
	}
	case COMMAND_SET_PAD_STICKS_MULTIPLIER:
	{
		CollectParameters(&m_nIp, 2);
		CPad::GetPad(0)->unk_B4 = GET_FLOAT_PARAM(0);
		CPad::GetPad(0)->unk_B8 = GET_FLOAT_PARAM(1);
		return 0;
	}
	case COMMAND_PRINT_SUBTITLE_NOW:
	{
		wchar* key = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 2);
		if (FrontEndMenuManager.m_PrefsShowSubtitles)
			CMessages::AddMessageJumpQ(key, GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1)); // false, true
		else
			CMessages::AddToPreviousBriefArray(key, -1, -1, -1, -1, -1, -1, nil);
		return 0;
	}
	case COMMAND_PRINT_SUBTITLE_NOW_OVERRIDE_FADE:
	{
		wchar* key = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 2);
		if (FrontEndMenuManager.m_PrefsShowSubtitles)
			CMessages::AddMessageJumpQ(key, GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1)); // true, true
		else
			CMessages::AddToPreviousBriefArray(key, -1, -1, -1, -1, -1, -1, nil);
		return 0;
	}
	case COMMAND_PRINT_SUBTITLE_NOW_NO_BRIEF:
	{
		wchar* key = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 2);
		//if (FrontEndMenuManager.m_PrefsShowSubtitles) // vcs no if else
			CMessages::AddMessageJumpQ(key, GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1)); // false, false
		//else
		//	CMessages::AddToPreviousBriefArray(key, -1, -1, -1, -1, -1, -1, nil);
		return 0;
	}
	case COMMAND_PRINT_WITH_NUMBER_NOW_NO_BRIEF:
	{
		wchar* key = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 3);
		CMessages::AddMessageJumpQWithNumber(key, GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(0), -1, -1, -1, -1, -1); // 0
		return 0;
	}
	case COMMAND_GET_ANGLE_BETWEEN_POINTS:
	{
		CollectParameters(&m_nIp, 4);
		SET_FLOAT_PARAM(0, CGeneral::GetAngleBetweenPoints(GET_FLOAT_PARAM(0), GET_FLOAT_PARAM(1), GET_FLOAT_PARAM(2), GET_FLOAT_PARAM(3)));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_OVERRIDE_CHAR_MOVE_ANIM:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bOverrideMoveAnim = true;
		return 0;
	}
	case EMPTY_COMMAND_1008:
	{
		/* Something must have been here */
		// something related to debug menu, not implemented // lcs 1627
		return 0;
	}
	case COMMAND_ENABLE_EMERGENCY_VEHICLES:
	{
		CollectParameters(&m_nIp, 1);
		gbEmergencyVehiclesEnabled = GET_INTEGER_PARAM(0) != 0;
		return 0;
	}
	case COMMAND_ADD_UNLOCKED_COSTUME:
		CollectParameters(&m_nIp, 1);
		// CStats::AddUnlockedCostume(GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_CLEAR_MULTIPLAYER_SPLASH_SCREEN:
		// ClearMultiplayerSplashScreen();
		return 0;
	case COMMAND_PRINT_WITH_2_NUMBERS_NOW_NO_BRIEF:
	{
		wchar* key = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 4);
		CMessages::AddMessageJumpQWithNumber(key, GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(3), GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), -1, -1, -1, -1); // 0
		return 0;
	}
	case COMMAND_GET_OBJECT_ORIENTATION:
	{
		CollectParameters(&m_nIp, 1);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		SET_FLOAT_PARAM(1, LimitAngleOnCircle(RADTODEG(Asin(pObject->GetForward().z))));
		SET_FLOAT_PARAM(2, LimitAngleOnCircle(RADTODEG(Atan2(-pObject->GetForward().x, pObject->GetForward().y))));
		SET_FLOAT_PARAM(0, LimitAngleOnCircle(RADTODEG(Atan2(-pObject->GetRight().z, pObject->GetUp().z))));
		StoreParameters(&m_nIp, 3);
		return 0;
	}
	case COMMAND_SET_OBJECT_ORIENTATION:
	{
		CollectParameters(&m_nIp, 4);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		pObject->SetOrientation(DEGTORAD(GET_FLOAT_PARAM(2)), DEGTORAD(GET_FLOAT_PARAM(1)), DEGTORAD(GET_FLOAT_PARAM(3)));
		return 0;
	}
	case COMMAND_CHANGE_ONSCREEN_COUNTER_PREFIX:
	{
		uint16 offset = (uint8*)GetPointerToScriptVariable(&m_nIp) - CTheScripts::ScriptSpace;
		CollectParameters(&m_nIp, 1);
		CUserDisplay::OnscnTimer.ChangeCounterPrefix(offset, GET_INTEGER_PARAM(0) != 0);
		return 0;
	}
	case COMMAND_STORE_PLAYER_OUTFIT:
	{
		//char tmp[12]; // lcs
		//CTheScripts::ReadTextLabelFromScript(&m_nIp, tmp);
		//int32 *ptr = GetPointerToScriptVariable(&m_nIp);
		//debug("%p\n", ptr);
		const char *key = GetKeyFromScript(&m_nIp);
		script_assert(key);
		for (int i = 0; i < KEY_LENGTH_IN_SCRIPT; i++)
			CGameLogic::mStoredPlayerOutfit[i] = key[i];
		printf("STORED PLAYOUR OUTFIT : %s\n", CGameLogic::mStoredPlayerOutfit);
		//m_nIp += KEY_LENGTH_IN_SCRIPT;
		return 0;
	}
	case COMMAND_DISPLAY_ONSCREEN_TIMER_WITH_NUMBER_AND_STRING:
	{
		//char onscreen_str1[12];
		uint16 var = (uint8*)GetPointerToScriptVariable(&m_nIp) - CTheScripts::ScriptSpace;
		CollectParameters(&m_nIp, 2); // max number, total
		uint32 type = GET_INTEGER_PARAM(1);
		int32 total = GET_INTEGER_PARAM(0);
		//wchar* text = TheText.Get((char*)&CTheScripts::ScriptSpace[m_nIp]); // ??
		//strncpy(onscreen_str1, (char*)&CTheScripts::ScriptSpace[m_nIp], KEY_LENGTH_IN_SCRIPT);
		//m_nIp += KEY_LENGTH_IN_SCRIPT;

		const char *label = GetKeyFromScript(&m_nIp);
		CUserDisplay::OnscnTimer.AddCounter(var, type, (char *)label, 0, total, nil, 0);
		return 0;
	}
	case COMMAND_SET_PLAYER_CURRENT_WEAPON_AMMO_IN_CLIP:
	{
		CollectParameters(&m_nIp, 1);
		CWeapon* pWeapon = FindPlayerPed()->GetWeapon();
		if (pWeapon && GET_INTEGER_PARAM(0))
			pWeapon->m_nAmmoInClip = GET_INTEGER_PARAM(0);
		return 0;
	}
	case COMMAND_SET_CHAR_WAIT_STATE_REPEAT:
	{
		CollectParameters(&m_nIp, 3);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		if (pPed)
			pPed->SetWaitState((eWaitState)GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2) >= 0 ? &GET_INTEGER_PARAM(2) : nil, true);
		return 0;
	}
	case COMMAND_LOCK_GARAGE:
		CollectParameters(&m_nIp, 2);
		CGarages::LockGarage(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1));
		return 0;
	case COMMAND_IS_FINAL_GAME:
#ifdef FINAL
		UpdateCompareFlag(true);
#else
		UpdateCompareFlag(false);
#endif
		return 0;
	case COMMAND_SET_ALLOWED_COLLISION:
	{
		CollectParameters(&m_nIp, 2);
		CTheScripts::AllowedCollision[0] = GET_INTEGER_PARAM(0);
		CTheScripts::AllowedCollision[1] = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_DISPLAY_ONSCREEN_TIMER_WITH_NUMBER_AND_2_STRINGS:
	{
		//char onscreen_str1[12];
		//char onscreen_str2[12];
		uint16 var = (uint8*)GetPointerToScriptVariable(&m_nIp) - CTheScripts::ScriptSpace;
		CollectParameters(&m_nIp, 3);
		uint32 type = GET_INTEGER_PARAM(1);
		int32 total = GET_INTEGER_PARAM(0);
		uint32 totalType = GET_INTEGER_PARAM(2);
		//wchar* text = TheText.Get((char*)&CTheScripts::ScriptSpace[m_nIp]); // ??
		//strncpy(onscreen_str1, (char*)&CTheScripts::ScriptSpace[m_nIp], KEY_LENGTH_IN_SCRIPT);
		//m_nIp += KEY_LENGTH_IN_SCRIPT;
		//wchar* text2 = TheText.Get((char*)&CTheScripts::ScriptSpace[m_nIp]); // ??
		//strncpy(onscreen_str2, (char*)&CTheScripts::ScriptSpace[m_nIp], KEY_LENGTH_IN_SCRIPT);
		//m_nIp += KEY_LENGTH_IN_SCRIPT;
		const char *label1 = GetKeyFromScript(&m_nIp);
		const char *label2 = GetKeyFromScript(&m_nIp);
		script_assert(false && "VCS TODO: comm 1023 CHECK labelspos"); // its like lcs but maybe bug label1 as text2 todo recheck
		CUserDisplay::OnscnTimer.AddCounter(var, type, (char*)label2, 0, total, (char *)label1, totalType); // recheck mb switch labels
		return 0;
	}
	case COMMAND_GET_PLAYER_STORED_WEAPON:
	{
		CollectParameters(&m_nIp, 1);
		//CPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed; // lcs
		// vcs (ida style)
		GetPlayerInfoByPoolHandler(pPlayerInfo, GET_INTEGER_PARAM(0));
		CPed *pPed = pPlayerInfo->m_pPed;
		// or
		//CPed *pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		SET_INTEGER_PARAM(0, pPed->m_storedWeapon);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_DISABLE_PAUSE_MENU:
		CollectParameters(&m_nIp, 1);
		// FrontEndMenuManager.mDisablePauseMenu = GET_INTEGER_PARAM(0) != 0; // TODO: static + member
		return 0;
	case COMMAND_IS_CHANNEL_PLAYING:
		CollectParameters(&m_nIp, 1);
		//UpdateCompareFlag(DMAudio.IsChannelPlaying(GET_INTEGER_PARAM(0));
		UpdateCompareFlag(false);
		return 0;
	case COMMAND_SET_CLOCK_EVENT_WARNING:
	{
		CollectParameters(&m_nIp, 3);
		/*
		if (CHud::m_ClockEventWarningMinutes || GET_INTEGER_PARAMS(2)){
			CHud::m_ClockEventWarningMinutes = GET_INTEGER_PARAMS(2);
			CHud::m_ClockEventMinutes = GET_INTEGER_PARAMS(1);
			CHud::m_ClockEventHours = GET_INTEGER_PARAMS(0);
			CHud::m_ClockEventFlashTimer = 0;
		}
		*/
		return 0;
	}
	case COMMAND_SET_EXTRA_COLOUR_LIGHT_DIRECTION:
	{
		CollectParameters(&m_nIp, 3);
		// CWeather::ExtraColourLightDir = GET_VECTOR_PARAM(0);
		// CWeather::ExtraColourLightDir.Normalise();
		return 0;
	}
	case COMMAND_SET_CHAR_CAN_BE_TARGETTED_BY_LEADER:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bCanBeTargettedByLeader = GET_INTEGER_PARAM(1) != 0;
		return 0;
	}
	case COMMAND_PRINT_HELP_NO_BRIEF:
	{
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CHud::SetHelpMessage(text, false); // + false, false
		return 0;
	}
	case COMMAND_PRINT_HELP_FOREVER_NO_BRIEF:
	{
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CHud::SetHelpMessage(text, false, true); // + false
		return 0;
	}
	case COMMAND_PRINT_HELP_ALWAYS_NO_BRIEF:
	{
		// CHud::mAlwaysAllowHelpText = true;
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CHud::SetHelpMessage(text, false); // + false, false
		return 0;
	}
	case COMMAND_PRINT_HELP_FOREVER_ALWAYS_NO_BRIEF:
	{
		// CHud::mAlwaysAllowHelpText = true;
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CHud::SetHelpMessage(text, false, true); // + false
		return 0;
	}
	case COMMAND_SET_CAR_IS_REWARD:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->bRewardVehicle = (GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	case todo__comm_1035: // 040B=2,unknown_char_command_8565 %1d% flag %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1035");
		return 0;
	}
	case todo__comm_1036: //040C=5,calc_screen_coords %1d% %2d% %3d% returned_screen_coords %4d% %5d%
	{
		CollectParameters(&m_nIp, 3);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1036");
		return 0;
	}
	case todo__comm_1037: //040D=4,get_integer_number_in_string result_var %1d% num %2d% num_length %3d% start_index %4d%
	{
		const char *label = GetKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 3);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1037");
		return 0;
	}
	case COMMAND_COPY_STRING:
	{
		const char *dst = GetKeyFromScript(&m_nIp);
		script_assert(dst)
		const char *src = GetKeyFromScript(&m_nIp);
		script_assert(src)
		strcpy((char*)dst, src);
		return 0;
	}
	case todo__comm_1039: // 040F=2,get_length_of_text_entry %1g% store_to %2d%
	{
		const char *label = GetKeyFromScript(&m_nIp);
		// get wide len?
		script_assert(false && "TODO_OR_CHECK_todo__comm_1039");
		return 0;
	}
	case todo__comm_1040: // 0410=1,get_free_mission_audio_slot %1d%
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1040");
		return 0;
	}
	case todo__comm_1041: //0411=1,get_mission_audio_slot_unknown_5634 %1d%
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1041");
		return 0;
	}
	case todo__comm_1042: //0412=1,unknown_mission_audio_slot_command_751f %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1042");
		return 0;
	}
	case todo__comm_1043: //0413=4,unknown_audio_command_6363 str %1d% str2 %2d% slot %3d% unk %4d%
	{
		const char *str1 = GetKeyFromScript(&m_nIp);
		const char *str2 = GetKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1043");
		return 0;
	}
	case todo__comm_1044: //0414=3,  unknown_char_animation_command_18f3 %1d% value1 %2d% value2 %3d%
	{
		CollectParameters(&m_nIp, 3);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1044");
		return 0;
	}
	case EMPTY_COMMAND_1045: // 0415=10,unknown_char_command_2621 %1d% flags %2d% %3d% %4d% %5d% %6d% %7d% %8d% %9d% %10d%
	{
		CollectParameters(&m_nIp, 10);
		/* Something must have been here */
		return 0;
	}
	case EMPTY_COMMAND_1046: // 0416=6,unknown_car_command_8533 %1d% flags %2d% %3d% %4d% %5d% %6d%
	{
		CollectParameters(&m_nIp, 6);
		/* Something must have been here */
		return 0;
	}
	case todo__comm_1047: // 0417=5,unknown_audio_command_7532 point %1d% %2d% %3d% values %4d% %5d%
	{
		CollectParameters(&m_nIp, 5);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1047");
		return 0;
	}
	case todo__comm_1048: // 0418=3,unknown_audio_command_8451 point %1d% %2d% %3d%
	{
		CollectParameters(&m_nIp, 3);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1048");
		return 0;
	}
	case todo__comm_1049: // 0419=5,get_random_char_in_area_7472 from %1d% %2d% to %3d% %4d% store_to %5d%
	{
		CollectParameters(&m_nIp, 5);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1049");
		return 0;
	}
	case todo__comm_1050: // 041A=2,request_model_name %1d% store_model_id %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1050");
		return 0;
	}
	case todo__comm_1051: // 041B=2,unknown_char_set_command_2463 %1d% value %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1051");
		return 0;
	}
	case todo__comm_1052: // 041C=2,unknown_char_get_command_7452 %1d% store_value %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1052");
		return 0;
	}
	case todo__comm_1053: // 041D=4,  is_3d_coord_in_zone %1d% %2d% %3d% zone %4z%
	{
		CollectParameters(&m_nIp, 4);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1053");
		return 0;
	}
	case todo__comm_1054: // 041E=1,nop_car_vcs_041e %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1054");
		return 0;
	}
	case todo__comm_1055: // 041F=1,nop_char_vcs_041f %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1055");
		return 0;
	}
	case todo__comm_1056: // 0420=1,nop_object_vcs_041f %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1056");
		return 0;
	}
	case todo__comm_1057: // 0421=5,get_random_object_in_area_no_save from %1d% %2d% to %3d% %4d% store_to %5d%
	{
		CollectParameters(&m_nIp, 5);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1057");
		return 0;
	}
	case todo__comm_1058: // 0422=4,set_car_coordinates_no_offset %1d% to %2d% %3d% %4d%
	{
		CollectParameters(&m_nIp, 4);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1058");
		return 0;
	}
	case todo__comm_1059: // 0423=4,set_char_coordinates_no_offset %1d% to %2d% %3d% %4d%
	{
		CollectParameters(&m_nIp, 4);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1059");
		return 0;
	}
	case todo__comm_1060: // 0424=1,  unknown_car_check_f721 %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1060");
		return 0;
	}
	case todo__comm_1061: // 0425=9,get_random_char_of_specified_model_in_area_3d %1d% %2d% %3d% to %4d% %5d% %6d% model %7d% or %8d% store_to %9d%
	{
		CollectParameters(&m_nIp, 9);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1061");
		return 0;
	}
	case todo__comm_1062: // 0426=4,get_name_of_info_zone %1d% %2d% %3d% store_to %4d%
	{
		CollectParameters(&m_nIp, 4);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1062");
		return 0;
	}
	case todo__comm_1063: // 0427=4,get_name_of_zone %1d% %2d% %3d% store_to %4d%
	{
		CollectParameters(&m_nIp, 4);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1063");
		return 0;
	}
	case todo__comm_1064: // 0428=13,get_zone_ped_info %1s% time_of_day %2b:day/night% store_info_to %3h% %4h% %5h% %6h% %7h% %8h% %9h% %10h% %11h% %12h% %13d%
	{
		CollectParameters(&m_nIp, 13);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1064");
		return 0;
	}
	case todo__comm_1065: // 0429=2,get_char_char_is_targetting %1d% store_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1065");
		return 0;
	}
	case todo__comm_1066: // 042A=2,remove_char_weapon_in_slot %1d% slot %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1066");
		return 0;
	}
	case todo__comm_1067: // 042B=2,get_anim_group_from_char %1d% store_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1067");
		return 0;
	}
	case todo__comm_1068: // 042C=2,  is_armour_health_greater %1d% than %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1068");
		return 0;
	}
	case todo__comm_1069: // 042D=2,  is_char_ped_type %1d% ped_type %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1069");
		return 0;
	}
	case todo__comm_1070: // 042E=1,  is_player_in_this_level %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1070");
		return 0;
	}
	case todo__comm_1071: // 042F=2,set_car_max_health %1d% to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1071");
		return 0;
	}
	case todo__comm_1072: // 0430=2,get_car_max_health %1d% store_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1072");
		return 0;
	}
	case todo__comm_1073: // 0431=2,get_object_heading_vector_inverse_squared_x %1d% store_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1073");
		return 0;
	}
	case todo__comm_1074: // 0432=2,get_object_heading_vector_inverse_squared_y %1d% store_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1074");
		return 0;
	}
	case todo__comm_1075: // 0433=6,unknown_char_area_command_15f2 %1d% cornerA %2d% %3d% cornerB %4d% %5d% flag %6d%
	{
		CollectParameters(&m_nIp, 6);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1075");
		return 0;
	}
	case todo__comm_1076: // 0434=2,unknown_char_set_command_3747 %1d% flag %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1076");
		return 0;
	}
	case todo__comm_1077: // 0435=2,unknown_char_command_18e6 %1d% another_char %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1077");
		return 0;
	}
	case todo__comm_1078: // 0436=1,  is_char_fighting %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1078");
		return 0;
	}
	case todo__comm_1079: // 0437=1,  unknown_is_char_in_specified_area %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1079");
		return 0;
	}
	case todo__comm_1080: // 0438=1,  unknown_is_specified_area_for_char_set_up %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1080");
		return 0;
	}
	case todo__comm_1081: // 0439=1,  unknown_char_check_command_8517 %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1081");
		return 0;
	}
	case todo__comm_1082: // 043A=2,unknown_car_set_command_6481 %1d% flag %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1082");
		return 0;
	}
	case todo__comm_1083: // 043B=1,  unknown_coll_check_command_2827 %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1083");
		return 0;
	}
	case todo__comm_1084: // 043C=3,unknown_coll_set_command_4627 %1d% %2d% %3d%
	{
		CollectParameters(&m_nIp, 3);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1084");
		return 0;
	}
	case todo__comm_1085: // 043D=3,unknown_coll_set_command_b471 %1d% %2d% %3d%
	{
		CollectParameters(&m_nIp, 3);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1085");
		return 0;
	}
	case todo__comm_1086: // 043E=8,create_projectile weapon_type %1d% coords %2d% %3d% %4d% power %5d% ped_handle %6d% flag %7d% store_to %8d%
	{
		CollectParameters(&m_nIp, 8);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1086");
		return 0;
	}
	case todo__comm_1087: // 043F=2,remove_projectile %1d% do_explosion %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1087");
		return 0;
	}
	case todo__comm_1088: // 0440=2,  is_projectile_of_type %1d% weapon_type %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1088");
		return 0;
	}
	case todo__comm_1089: // 0441=1,  is_projectile_destroyed %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1089");
		return 0;
	}
	case todo__comm_1090: // 0442=2,unknown_char_set_command_2691 %1d% flag %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1090");
		return 0;
	}
	case todo__comm_1091: // 0443=1,request_anims %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1091");
		return 0;
	}
	case todo__comm_1092: // 0444=1,remove_anims %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1092");
		return 0;
	}
	case todo__comm_1093: // 0445=1,have_anims_loaded %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1093");
		return 0;
	}
	case todo__comm_1094: // 0446=1, is_char_surrendering %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1094");
		return 0;
	}
	case todo__comm_1095: // 0447=2,apply_visible_damage_to_car %1d% amount_of_damage %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1095");
		return 0;
	}
	case todo__comm_1096: // 0448=4,get_dead_char_coordinates %1d% store_to %2d% %3d% %4d%
	{
		CollectParameters(&m_nIp, 4);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1096");
		return 0;
	}
	case todo__comm_1097: // 0449=2,get_number_of_char_colour_sets %1d% store_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1097");
		return 0;
	}
	case todo__comm_1098: // 044A=2,change_char_colour_set_dont_updated_saved_one %1d% set_id %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1098");
		return 0;
	}
	case todo__comm_1099: // 044B=0,unknown_nop_command_1847
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1099");
		return 0;
	}
	default:
		script_assert(0);
	}
	return -1;
}

int8 CRunningScript::ProcessCommands1100To1199(int32 command)
{
	//char tmp[48];
	switch (command) {
	case todo__comm_1100: // 044C=1,  unknown_char_check_command_3553 %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1100");
		return 0;
	}
	case todo__comm_1101: // 044D=4,add_toggleable_blip_for_coord %1d% coords %2d% %3d% %4d%
	{
		CollectParameters(&m_nIp, 4);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1101");
		return 0;
	}
	case todo__comm_1102: // 044E=2,unknown_empire_display_command_7317 %1d% %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1102");
		return 0;
	}
	case todo__comm_1103: // 044F=0,unknown_empire_display_command_8542
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1103");
		return 0;
	}
	case todo__comm_1104: // 0450=3,unknown_empire_display_command_91e4 %1d% %2d% %3d%
	{
		CollectParameters(&m_nIp, 3);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1104");
		return 0;
	}
	case todo__comm_1105: // 0451=3,unknown_empire_display_command_6b43 %1d% %2d% %3d%
	{
		CollectParameters(&m_nIp, 3);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1105");
		return 0;
	}
	case todo__comm_1106: // 0452=5,unknown_empire_display_command_3866 %1d% %2d% %3d% %4d% %5d%
	{
		CollectParameters(&m_nIp, 5);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1106");
		return 0;
	}
	case todo__comm_1107: // 0453=5,unknown_empire_display_command_7217 %1d% %2d% %3d% %4d% %5d%
	{
		CollectParameters(&m_nIp, 5);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1107");
		return 0;
	}
	case todo__comm_1108: // 0454=5,unknown_empire_display_command_8527 %1g% %2d% %3d% %4d% store_to %5d%
	{
		CollectParameters(&m_nIp, 5);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1108");
		return 0;
	}
	case todo__comm_1109: // 0455=12,unknown_empire_display_command_0471 %1g% %2d% %3d% %4d% %5d% %6d% %7d% %8d% %9d% %10d% %11d% store_to %12d%
	{
		CollectParameters(&m_nIp, 12);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1109");
		return 0;
	}
	case todo__comm_1110: // 0456=1,unknown_empire_display_command_6438 %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1110");
		return 0;
	}
	case todo__comm_1111: // 0457=5,unknown_empire_display_command_5372 %1d% %2d% %3d% %4d% %5d%
	{
		CollectParameters(&m_nIp, 5);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1111");
		return 0;
	}
	case todo__comm_1112: // 0458=2,unknown_empire_display_command_7492 %1d% %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1112");
		return 0;
	}
	case todo__comm_1113: // 0459=2,unknown_empire_display_command_9274 %1d% %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1113");
		return 0;
	}
	case todo__comm_1114: // 045A=2,unknown_empire_display_command_8917 %1d% %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1114");
		return 0;
	}
	case todo__comm_1115: // 045B=3,unknown_empire_display_command_4877 %1d% %2d% %3d%
	{
		CollectParameters(&m_nIp, 3);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1115");
		return 0;
	}
	case todo__comm_1116: // 045C=1,unknown_empire_display_command_8467 %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1116");
		return 0;
	}
	case todo__comm_1117: // 045D=6,unknown_empire_display_command_5737 %1d% %2d% %3d% %4d% %5d% %6d%
	{
		CollectParameters(&m_nIp, 6);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1117");
		return 0;
	}
	case todo__comm_1118: // 045E=4,unknown_empire_system_command_2858 %1d% %2d% %3d% store_to %4d%
	{
		CollectParameters(&m_nIp, 4);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1118");
		return 0;
	}
	case todo__comm_1119: // 045F=2,set_empire_ownership %1d% value %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1119");
		return 0;
	}
	case todo__comm_1120: // 0460=2,set_empire_type %1d% type %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1120");
		return 0;
	}
	case todo__comm_1121: // 0461=2,set_empire_scale %1d% scale %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1121");
		return 0;
	}
	case todo__comm_1122: // 0462=2,set_empire_condition %1d% condition %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1122");
		return 0;
	}
	case todo__comm_1123: // 0463=2,set_empire_visual_damage %1d% flag %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1123");
		return 0;
	}
	case todo__comm_1124: // 0464=2,set_empire_state %1d% state %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1124");
		return 0;
	}
	case todo__comm_1125: // 0465=4,get_empire_coords %1d% store_to %2d% %3d% %4d%
	{
		CollectParameters(&m_nIp, 4);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1125");
		return 0;
	}
	case todo__comm_1126: // 0466=2,get_empire_ownership %1d% store_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1126");
		return 0;
	}
	case todo__comm_1127: // 0467=2,get_empire_type %1d% store_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1127");
		return 0;
	}
	case todo__comm_1128: // 0468=2,get_empire_scale %1d% store_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1128");
		return 0;
	}
	case todo__comm_1129: // 0469=2,get_empire_condition %1d% store_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1129");
		return 0;
	}
	case todo__comm_1130: // 046A=2,get_empire_visual_damage %1d% store_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1130");
		return 0;
	}
	case todo__comm_1131: // 046B=2,get_empire_state %1d% store_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1131");
		return 0;
	}
	case todo__comm_1132: // 046C=2,get_empire_heading %1d% store_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1132");
		return 0;
	}
	case todo__comm_1133: // 046D=5,unknown_char_get_command_7389 %1d% store_values_to %2d% %3d% %4d% %5d%
	{
		CollectParameters(&m_nIp, 5);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1133");
		return 0;
	}
	case todo__comm_1134: // 046E=1,  unknown_command_0514 %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1134");
		return 0;
	}
	case todo__comm_1135: // 046F=5,unknown_car_get_command_8218 %1d% store_values_to %2d% %3d% %4d% %5d%
	{
		CollectParameters(&m_nIp, 5);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1135");
		return 0;
	}
	case todo__comm_1136: // 0470=3,get_active_camera_coordinates %1d% %2d% %3d%
	{
		CollectParameters(&m_nIp, 3);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1136");
		return 0;
	}
	case todo__comm_1137: // 0471=3,get_active_camera_point_at %1d% %2d% %3d%
	{
		CollectParameters(&m_nIp, 3);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1137");
		return 0;
	}
	case todo__comm_1138: // 0472=4,add_pager_message %1g% %2d% %3d% %4d%
	{
		CollectParameters(&m_nIp, 4);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1138");
		return 0;
	}
	case todo__comm_1139: // 0473=5,add_pager_message_with_number %1s% num %2d% time_to_move_characters %3d% priority %4d% unk5 %5d%
	{
		CollectParameters(&m_nIp, 5);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1139");
		return 0;
	}
	case todo__comm_1140: // 0474=0,  is_help_message_being_displayed
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1140");
		return 0;
	}
	case todo__comm_1141: // 0475=3,unknown_object_set_command_7418 %1d% %2d% %3d%
	{
		CollectParameters(&m_nIp, 3);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1141");
		return 0;
	}
	case todo__comm_1142: // 0476=10,unknown_command_8858 %1d% cornerA %2d% %3d% %4d% cornerB %5d% %6d% %7d% unk_float %8d% unk_float %9d% unk %10d%
	{
		CollectParameters(&m_nIp, 10);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1142");
		return 0;
	}
	case todo__comm_1143: // 0477=1,get_mission_script_name %1s%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1143");
		return 0;
	}
	case todo__comm_1144: // 0478=13,draw_corona_with_explosion point %1d% %2d% %3d% point %4d% %5d% %6d% colour %7d% %8d% %9d% %10d% unk_float_values %11d% %12d% unk_int %13d%
	{
		CollectParameters(&m_nIp, 13);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1144");
		return 0;
	}
	case todo__comm_1145: // 0479=5,add_sphere_0172 %1d% %2d% %3d% radius %4d% store_to %5d%
	{
		CollectParameters(&m_nIp, 5);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1145");
		return 0;
	}
	case todo__comm_1146: // 047A=1,remove_sphere_0172 %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1146");
		return 0;
	}
	case todo__comm_1147: // 047B=2,unknown_empire_get_command_7418 %1d% store_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1147");
		return 0;
	}
	case todo__comm_1148: // 047C=6,get_random_object_of_specified_model_in_area_2d model %1o% cornerA %2d% %3d% cornerB %4d% %5d% store_to %6d%
	{
		CollectParameters(&m_nIp, 6);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1148");
		return 0;
	}
	case todo__comm_1149: // 047D=3,unknown_empire_command_6726 %1d% %2d% store_to %3d%
	{
		CollectParameters(&m_nIp, 3);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1149");
		return 0;
	}
	case todo__comm_1150: // 047E=7,unknown_empire_command_8382 %1d% %2d% %3d% store_to %4d% %5d% %6d% %7d%
	{
		CollectParameters(&m_nIp, 7);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1150");
		return 0;
	}
	case todo__comm_1151: // 047F=5,unknown_empire_command_9726 %1d% str %2d% unk %3d% %4d% store_to %5d%
	{
		CollectParameters(&m_nIp, 5);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1151");
		return 0;
	}
	case todo__comm_1152: // 0480=9,unknown_empire_command_83f8 %1d% %2d% %3d% str %4d% store_to %5d% %6d% %7d% %8d% %9d%
	{
		CollectParameters(&m_nIp, 9);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1152");
		return 0;
	}
	case todo__comm_1153: // 0481=2,unknown_player_set_command_1631 %1d% flag %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1153");
		return 0;
	}
	case todo__comm_1154: // 0482=2,unknown_enable_building_swap_for_model hash %1d% enable %2d% 
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1154");
		return 0;
	}
	case todo__comm_1155: // 0483=2,get_empire_from_building model_hash %1d% store_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1155");
		return 0;
	}
	case todo__comm_1156: // 0484=2,get_hash_key hash %1d% store_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1156");
		return 0;
	}
	case todo__comm_1157: // 0485=2,  unknown_char_check_command_5936 %1d% id %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1157");
		return 0;
	}
	case todo__comm_1158: // 0486=5,set_gang_empire_building_colour gangID %1d% colour %2d% %3d% %4d% unk_gangID %5d%
	{
		CollectParameters(&m_nIp, 5);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1158");
		return 0;
	}
	case todo__comm_1159: // 0487=3,unknown_player_command_6421 %1d% values %2d% %3d%
	{
		CollectParameters(&m_nIp, 3);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1159");
		return 0;
	}
	case todo__comm_1160: // 0488=1,unknown_player_set_drunk_delay %1b%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1160");
		return 0;
	}
	case todo__comm_1161: // 0489=0,load_empire_hud
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1161");
		return 0;
	}
	case todo__comm_1162: // 048A=0,unknown_disable_empire_display
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1162");
		return 0;
	}
	case todo__comm_1163: // 048B=7,draw_empire_box_with_text %1s% %2d% %3d% %4d% %5d% %6d% %7d%
	{
		CollectParameters(&m_nIp, 7);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1163");
		return 0;
	}
	case todo__comm_1164: // 048C=3,unknown_empire_display_set_coords_7543 %1d% %2d% %3d%
	{
		CollectParameters(&m_nIp, 3);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1164");
		return 0;
	}
	case todo__comm_1165: // 048D=3,bitwise_or %1d% or %2d% store_to %3d%
	{
		CollectParameters(&m_nIp, 3);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1165");
		return 0;
	}
	case todo__comm_1166: // 048E=3,bitwise_and %1d% and %2d% store_to %3d%
	{
		CollectParameters(&m_nIp, 3);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1166");
		return 0;
	}
	case todo__comm_1167: // 048F=2,  is_bitwise_and_not_equal_to_zero %1d% and %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1167");
		return 0;
	}
	case todo__comm_1168: // 0490=2,set_object_health %1d% to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1168");
		return 0;
	}
	case todo__comm_1169: // 0491=2,get_object_health %1d% store_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1169");
		return 0;
	}
	case todo__comm_1170: // 0492=1,set_radar_display_mode %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1170");
		return 0;
	}
	case todo__comm_1171: // 0493=2,unknown_command_7395 %1d% store_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1171");
		return 0;
	}
	case todo__comm_1172: // 0494=4,unknown_get_coords_command_8316 %1d% store_to %2d% %3d% %4d%
	{
		CollectParameters(&m_nIp, 4);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1172");
		return 0;
	}
	case todo__comm_1173: // 0495=2,change_car_colour_set %1d% set_id %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1173");
		return 0;
	}
	case todo__comm_1174: // 0496=2,change_car_script_colour_set %1d% set_id %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1174");
		return 0;
	}
	case todo__comm_1175: // 0497=2,get_car_colour_set %1d% store_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1175");
		return 0;
	}
	case todo__comm_1176: // 0498=2,get_car_script_colour_set %1d% store_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1176");
		return 0;
	}
	case todo__comm_1177: // 0499=2,get_number_of_car_colour_sets %1d% store_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1177");
		return 0;
	}
	case todo__comm_1178: // 049A=2,get_number_of_car_script_colour_sets %1d% store_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1178");
		return 0;
	}
	case todo__comm_1179: // 049B=1,get_number_of_days_passed %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1179");
		return 0;
	}
	case todo__comm_1180: // 049C=2,unknown_command_7264 %1d% unused %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1180");
		return 0;
	}
	case todo__comm_1181: // 049D=1,unknown_command_83e5 %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1181");
		return 0;
	}
	case todo__comm_1182: // 049E=2,add_sprite_blip_for_empire_building empire_index %1d% store_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1182");
		return 0;
	}
	case todo__comm_1183: // 049F=1,switch_dollar_particle %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1183");
		return 0;
	}
	case todo__comm_1184: // 04A0=8,unknown_command_3842 %1d% %2d% %3d% %4d% %5d% %6d% %7d% %8d%
	{
		CollectParameters(&m_nIp, 8);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1184");
		return 0;
	}
	case todo__comm_1185: // 04A1=2,unknown_audio_command_0648 %1d% store_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1185");
		return 0;
	}
	case todo__comm_1186: // 04A2=9,unknown_char_coord_check_command_6382 %1d% coords %2d% %3d% %4d% %5d% %6d% %7d% %8d% %9d%
	{
		CollectParameters(&m_nIp, 9);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1186");
		return 0;
	}
	case todo__comm_1187: // 04A3=2,unknown_char_command_8375 %1d% char %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1187");
		return 0;
	}
	case todo__comm_1188: // 04A4=2,unknown_char_command_7845 %1d% char %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1188");
		return 0;
	}
	case todo__comm_1189: // 04A5=1,pop_car_bonnet %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1189");
		return 0;
	}
	case todo__comm_1190: // 04A6=2,create_rope_for_car %1d% rope_type %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1190");
		return 0;
	}
	case todo__comm_1191: // 04A7=1,delete_rope_from_car %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1191");
		return 0;
	}
	case todo__comm_1192: // 04A8=2,unknown_get_object_from_car_command_8457 %1d% store_object_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1192");
		return 0;
	}
	case todo__comm_1193: // 04A9=2,unknown_get_car_from_car_command_7457 %1d% store_car_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1193");
		return 0;
	}
	case todo__comm_1194: // 04AA=2,unknown_object_set_command_5758 %1d% flag %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1194");
		return 0;
	}
	case todo__comm_1195: // 04AB=2,unknown_car_set_command_5758 %1d% flag %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1195");
		return 0;
	}
	case todo__comm_1196: // 04AC=4,set_car_rope_start_position %1d% coords %2d% %3d% %4d%
	{
		CollectParameters(&m_nIp, 4);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1196");
		return 0;
	}
	case todo__comm_1197: // 04AD=2,unknown_get_object_from_car_command_7393 %1d% store_object_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1197");
		return 0;
	}
	case todo__comm_1198: // 04AE=2,change_char_colour_set %1d% set_id %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1198");
		return 0;
	}
	case todo__comm_1199: // 04AF=2,change_char_script_colour_set %1d% set_id %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1199");
		return 0;
	}
	default:
		script_assert(0);
	}
	return -1;
}
