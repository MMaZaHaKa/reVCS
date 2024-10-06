#include "common.h"

#include "Script.h"
#include "ScriptCommands.h"

#include "CarCtrl.h"
#include "ColStore.h"
#include "Coronas.h"
#include "CutsceneMgr.h"
#include "DMAudio.h"
#include "Explosion.h"
#include "GameLogic.h"
#include "General.h"
#include "Glass.h"
#include "Fluff.h"
#include "KeyGen.h"
#include "Hud.h"
#include "MBlur.h"
#include "Pad.h"
#include "Pickups.h"
#include "Pools.h"
#include "Population.h"
#include "Radar.h"
#include "RoadBlocks.h"
#include "Ropes.h"
#include "SetPieces.h"
#include "SpecialFX.h"
#include "Stats.h"
#include "Streaming.h"
#include "Timecycle.h"
#include "User.h"
#include "World.h"
#include "Zones.h"
// new
#include "FerrisWheel.h"


// LCS: file done except TODOs

int8 CRunningScript::ProcessCommands1200To1299(int32 command)
{
	switch (command) {
	case todo__comm_1200: // 04B0=2,get_char_colour_set %1d% store_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1200");
		return 0;
	}
	case todo__comm_1201: // 04B1=2,get_char_script_colour_set %1d% store_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1201");
		return 0;
	}
	case todo__comm_1202: // 04B2=2,get_number_of_char_colour_sets_2 %1d% store_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1202");
		return 0;
	}
	case todo__comm_1203: // 04B3=2,get_number_of_char_script_colour_sets %1d% store_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1203");
		return 0;
	}
	case todo__comm_1204: // 04B4=4,  unknown_char_animation_6727 %1d% values %2d% %3d% %4d%
	{
		CollectParameters(&m_nIp, 4);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1204");
		return 0;
	}
	case todo__comm_1205: // 04B5=2,unknown_char_set_command_47e1 %1d% flag %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1205");
		return 0;
	}
	case todo__comm_1206: // 04B6=2,unknown_char_set_command_87c3 %1d% flag %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1206");
		return 0;
	}
	case todo__comm_1207: // 04B7=2,unknown_char_set_command_3120 %1d% flag %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1207");
		return 0;
	}
	case todo__comm_1208: // 04B8=2,  has_object_collided_with_car %1d% car %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1208");
		return 0;
	}
	case todo__comm_1209: // 04B9=4,unknown_char_command_4384 %1d% values %2d% %3d% %4d%
	{
		CollectParameters(&m_nIp, 4);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1209");
		return 0;
	}
	case todo__comm_1210: // 04BA=1,reset_car_num_collided_entities %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1210");
		return 0;
	}
	case todo__comm_1211: // 04BB=0,unknown_radar_command_0628
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1211");
		return 0;
	}
	case todo__comm_1212: // 04BC=11,create_flying_projectile_shot_by_car weapon_type %1d% start_coords %2d% %3d% %4d% target_coords %5d% %6d% %7d% power %8d% shooting_car_handle %9d% flag %10d% store_to %11d%
	{
		CollectParameters(&m_nIp, 11);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1212");
		return 0;
	}
	case todo__comm_1213: // 04BD=1,unknown_radar_command_0628 %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1213");
		return 0;
	}
	case todo__comm_1214: // 04BE=3,unknown_car_set_command_2872 %1d% values %2d% %3d%
	{
		CollectParameters(&m_nIp, 3);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1214");
		return 0;
	}
	case todo__comm_1215: // 04BF=10,draw_checkpoint_with_alpha coords %1d% %2d% %3d% coords %4d% %5d% %6d% colour %7d% %8d% %9d% radius %10d%
	{
		CollectParameters(&m_nIp, 10);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1215");
		return 0;
	}
	case todo__comm_1216: // 04C0=6,attach_object_to_char %1d% car %2d% unk_int %3d% offset %4d% %5d% %6d%
	{
		CollectParameters(&m_nIp, 6);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1216");
		return 0;
	}
	case todo__comm_1217: // 04C1=1,detach_object_from_char %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1217");
		return 0;
	}
	case todo__comm_1218: // 04C2=2,unknown_char_set_command_7283 %1d% flag %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1218");
		return 0;
	}
	case todo__comm_1219: // 04C3=1,clear_all_threats_for_ped_type %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1219");
		return 0;
	}
	case todo__comm_1220: // 04C4=6,get_closest_water_node %1d% %2d% %3d% store_to %4d% %5d% %6d%
	{
		CollectParameters(&m_nIp, 6);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1220");
		return 0;
	}
	case todo__comm_1221: // 04C5=1,unknown_command_6717 %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1221");
		return 0;
	}
	case todo__comm_1222: // 04C6=1,unknown_generate_cars_set_command_7421 %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1222");
		return 0;
	}
	case COMMAND_FERRIS_WHEEL_TURN_ON: //04C7=0,unknown_command_4981
	{
		CFerrisWheel::TurnOn();
		return 0;
	}
	case COMMAND_FERRIS_WHEEL_TURN_OFF: //04C8=0,unknown_command_6282
	{
		CFerrisWheel::TurnOff();
		return 0;
	}
	case COMMAND_FERRIS_WHEEL_IS_STOPPED: //04C9=0,  unknown_check_command_7451
	{
		UpdateCompareFlag(CFerrisWheel::CheckMode());
		return 0;
	}
	case COMMAND_FERRIS_WHEEL_GET_CABINE: //04CA=2,unknown_get_object_command_4814 index %1d% store_to %2d%
	{
		CollectParameters(&m_nIp, 1);
		CObject *pCabine = CFerrisWheel::GetCabineObjectPointerByIndex(GET_INTEGER_PARAM(0));
		SET_INTEGER_PARAM(0, pCabine ? CPools::GetObjectPool()->GetIndex(pCabine) : -1);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case todo__comm_1227: // 04CB=2,add_sprite_blip_for_empire_building_2 empire_index %1d% store_to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1227");
		return 0;
	}
	case todo__comm_1228: // 04CC=0,unknown_command_2739
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1228");
		return 0;
	}
	case todo__comm_1229: // 04CD=2,set_area_name %1g% unk_int %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1229");
		return 0;
	}
	case todo__comm_1230: // 04CE=2,unknown_command_6745 %1d% %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1230");
		return 0;
	}
	case todo__comm_1231: // 04CF=2,unknown_attached_player_set_angle_command_b516 %1d% angle %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1231");
		return 0;
	}
	case todo__comm_1232: // 04D0=2,unknown_attached_player_set_angle_command_1969 %1d% angle %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1232");
		return 0;
	}
	case todo__comm_1233: // 04D1=1,trigger_car_alarm %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1233");
		return 0;
	}
	case todo__comm_1234: // 04D2=2,unknown_car_set_command_9338 %1d% flag %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1234");
		return 0;
	}
	case todo__comm_1235: // 04D3=1,clear_char_leadership %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1235");
		return 0;
	}
	case todo__comm_1236: // 04D4=1,make_player_fire_proof %1b%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1236");
		return 0;
	}
	case todo__comm_1237: // 04D5=5,unknown_command_5721 %1d% %2d% %3d% %4d% %5d%
	{
		CollectParameters(&m_nIp, 5);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1237");
		return 0;
	}
	case todo__comm_1238: // 04D6=2,unknown_player_command_4832 %1d% flag %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1238");
		return 0;
	}
	case todo__comm_1239: // 04D7=3,camera_look_at_entity char %1d% or_car %2d% enable_look_at %3d%
	{
		CollectParameters(&m_nIp, 3);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1239");
		return 0;
	}
	case todo__comm_1240: // 04D8=1,  is_object_still_alive %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1240");
		return 0;
	}
	case todo__comm_1241: // 04D9=1,get_number_of_ballons_burst %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1241");
		return 0;
	}
	case todo__comm_1242: // 04DA=1,set_total_balloons_to %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1242");
		return 0;
	}
	case todo__comm_1243: // 04DB=1,unknown_command_8219 %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1243");
		return 0;
	}
	case todo__comm_1244: // 04DC=0,  unknown_check_command_371f
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1244");
		return 0;
	}
	case todo__comm_1245: // 04DD=1,make_vehicle_invisible %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1245");
		return 0;
	}
	case todo__comm_1246: // 04DE=1,freeze_time %1b:freeze/unfreeze%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1246");
		return 0;
	}
	case todo__comm_1247: // 04DF=1,  is_char_holding_sniper %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1247");
		return 0;
	}
	case todo__comm_1248: // 04E0=0,clear_pager
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1248");
		return 0;
	}
	case todo__comm_1249: // 04E1=0,  does_game_want_to_draw_hud
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1249");
		return 0;
	}
	case todo__comm_1250: // 04E2=1,unknown_audio_command_7659 %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1250");
		return 0;
	}
	case todo__comm_1251: // 04E3=11,create_flying_projectile_shot_by_char weapon_type %1d% start_coords %2d% %3d% %4d% target_coords %5d% %6d% %7d% power %8d% shooting_car_handle %9d% flag %10d% store_to %11d%
	{
		CollectParameters(&m_nIp, 11);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1251");
		return 0;
	}
	case todo__comm_1252: // 04E4=2,unknown_char_set_command_8248 %1d% flag %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1252");
		return 0;
	}
	case todo__comm_1253: // 04E5=2,set_number_of_empire_business_sites_owned_by_player business_type %1d% number %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1253");
		return 0;
	}
	case todo__comm_1254: // 04E6=2,unknown_char_set_command_c728 %1d% flag %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1254");
		return 0;
	}
	case todo__comm_1255: // 04E7=3,  is_3d_coord_in_current_level %1d% %2d% %3d%
	{
		CollectParameters(&m_nIp, 3);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1255");
		return 0;
	}
	case todo__comm_1256: // 04E8=1,  is_vehicle_performing_wheelie %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1256");
		return 0;
	}
	case todo__comm_1257: // 04E9=1,  is_vehicle_performing_stoppie %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1257");
		return 0;
	}
	case todo__comm_1258: // 04EA=0,register_shoplifter_apprended
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1258");
		return 0;
	}
	case todo__comm_1259: // 04EB=1,unknown_audio_command_4817 %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1259");
		return 0;
	}
	case todo__comm_1260: // 04EC=5,extinguish_fire_at_point %1d% %2d% %3d% radius %4d% use_water %5b%
	{
		CollectParameters(&m_nIp, 5);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1260");
		return 0;
	}
	case todo__comm_1261: // 04ED=8,add_fight_ring_static_shadow at_coords %1d% %2d% %3d% rgb %4d% %5d% %6d% intensity %7d% radius %8d%
	{
		CollectParameters(&m_nIp, 8);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1261");
		return 0;
	}
	case todo__comm_1262: // 04EE=1,make_char_invisible %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1262");
		return 0;
	}
	case todo__comm_1263: // 04EF=1,unknown_command_8850 %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1263");
		return 0;
	}
	case todo__comm_1264: // 04F0=2,unknown_char_set_command_7528 %1d% flag %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1264");
		return 0;
	}
	case todo__comm_1265: // 04F1=8,  unknown_slide_object_5128 %1d% to %2d% %3d% %4d% speed %5d% %6d% %7d% collision_check %8d%
	{
		CollectParameters(&m_nIp, 8);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1265");
		return 0;
	}
	case todo__comm_1266: // 04F2=0,  is_current_script_a_mission
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1266");
		return 0;
	}
	case todo__comm_1267: // 04F3=1,lock_the_costume %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1267");
		return 0;
	}
	case todo__comm_1268: // 04F4=2,register_driving_range_stat best_score %1d% furthest_drive %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1268");
		return 0;
	}
	case todo__comm_1269: // 04F5=1,set_radar_zoom %1h%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1269");
		return 0;
	}
	case todo__comm_1270: // 04F6=1,enable_empire_stats %1b%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1270");
		return 0;
	}
	case todo__comm_1271: // 04F7=3,display_text_without_highlighting %1d% %2d% gxt %3g%
	{
		CollectParameters(&m_nIp, 3);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1271");
		return 0;
	}
	case todo__comm_1272: // 04F8=1,unknown_char_check_command_7892 %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1272");
		return 0;
	}
	case todo__comm_1273: // 04F9=1,unknown_char_check_command_2017 %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1273");
		return 0;
	}
	case todo__comm_1274: // 04FA=2,unknown_char_set_command_9817 %1d% flag %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1274");
		return 0;
	}
	case todo__comm_1275: // 04FB=1,unknown_audio_get_command_7219 %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1275");
		return 0;
	}
	case todo__comm_1276: // 04FC=2,unknown_gang_set_command_2891 %1d% to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1276");
		return 0;
	}
	case todo__comm_1277: // 04FD=0,unknown_coll_set_command_5171
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1277");
		return 0;
	}
	case todo__comm_1278: // 04FE=3,unknown_command_8278 %1d% %2d% %3d%
	{
		CollectParameters(&m_nIp, 3);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1278");
		return 0;
	}
	case todo__comm_1279: // 04FF=3,unknown_gang_set_command_6393 %1d% values %2d% %3d%
	{
		CollectParameters(&m_nIp, 3);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1279");
		return 0;
	}
	case todo__comm_1280: // 0500=2,unknown_char_set_command_1736 %1d% bit_num %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1280");
		return 0;
	}
	case todo__comm_1281: // 0501=2,unknown_char_unset_command_1736 %1d% bit_num %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1281");
		return 0;
	}
	case todo__comm_1282: // 0502=1,unknown_char_clear_command_1736 %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1282");
		return 0;
	}
	case todo__comm_1283: // 0503=2,unknown_char_set_command_4828 %1d% flag %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1283");
		return 0;
	}
	case todo__comm_1284: // 0504=4,nop_char_vcs_0504 %1d% coords %2d% %3d% %4d%
	{
		CollectParameters(&m_nIp, 4);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1284");
		return 0;
	}
	case todo__comm_1285: // 0505=4,unknown_command_1693 char %1d% handle_type_of_next_param %2b:vehicle/ped% handle %3d% flag %4d%
	{
		CollectParameters(&m_nIp, 4);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1285");
		return 0;
	}
	case todo__comm_1286: // 0506=2,unknown_char_set_command_9621 %1d% flag %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1286");
		return 0;
	}
	case todo__comm_1287: // 0507=2,unknown_char_audio_command_8157 char %1d% value %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1287");
		return 0;
	}
	case todo__comm_1288: // 0508=2,unknown_char_set_command_5817 %1d% flag %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1288");
		return 0;
	}
	case todo__comm_1289: // 0509=3,unknown_radar_set_coords_command_0472 %1d% %2d% %3d%
	{
		CollectParameters(&m_nIp, 3);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1289");
		return 0;
	}
	case todo__comm_1290: // 050A=0,register_empire_attack_successful
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1290");
		return 0;
	}
	case todo__comm_1291: // 050B=0,register_empire_attack_unsuccessful
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1291");
		return 0;
	}
	case todo__comm_1292: // 050C=0,register_site_was_defended_successfully
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1292");
		return 0;
	}
	case todo__comm_1293: // 050D=0,register_site_was_not_defended_successfully
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1293");
		return 0;
	}
	case todo__comm_1294: // 050E=1,register_most_damage_caused_on_crash_mission %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1294");
		return 0;
	}
	case todo__comm_1295: // 050F=1,register_fastest_time_on_mashing_up_the_mall %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1295");
		return 0;
	}
	case todo__comm_1296: // 0510=1,register_fastest_time_on_harbor_hover_race %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1296");
		return 0;
	}
	case todo__comm_1297: // 0511=1,register_fastest_time_on_haiti_hover_race %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1297");
		return 0;
	}
	case todo__comm_1298: // 0512=1,register_crimewave_value_of_goods_saved %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1298");
		return 0;
	}
	case todo__comm_1299: // 0513=1,register_crimewave_level %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1299");
		return 0;
	}
	default:
		script_assert(0);
	}
	return -1;
}

int8 CRunningScript::ProcessCommands1300To1399(int32 command)
{
	switch (command) {
	case todo__comm_1300: // 0514=1,register_air_ambulance_level %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1300");
		return 0;
	}
	case todo__comm_1301: // 0515=1,register_vice_sights_level %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1301");
		return 0;
	}
	case todo__comm_1302: // 0516=1,register_vice_sights_number_of_sights_viewed %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1302");
		return 0;
	}
	case todo__comm_1303: // 0517=1,register_fire_copter_level %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1303");
		return 0;
	}
	case todo__comm_1304: // 0518=1,register_beach_patrol_level %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1304");
		return 0;
	}
	case todo__comm_1305: // 0519=1,register_crims_on_wings_time %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1305");
		return 0;
	}
	case todo__comm_1306: // 051A=1,register_pcjplay_town_time %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1306");
		return 0;
	}
	case todo__comm_1307: // 051B=1,register_pcjplay_point_time %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1307");
		return 0;
	}
	case todo__comm_1308: // 051C=2,register_watersports_time course %1d% time %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1308");
		return 0;
	}
	case todo__comm_1309: // 051D=2,register_watersports_best_lap course %1d% time %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1309");
		return 0;
	}
	case todo__comm_1310: // 051E=2,register_dtrial_time course %1d% time %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1310");
		return 0;
	}
	case todo__comm_1311: // 051F=2,register_dtrial_best_lap course %1d% time %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1311");
		return 0;
	}
	case todo__comm_1312: // 0520=2,register_turismo_time course %1d% time %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1312");
		return 0;
	}
	case todo__comm_1313: // 0521=2,register_turismo_best_lap course %1d% time %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1313");
		return 0;
	}
	case todo__comm_1314: // 0522=2,register_turismo_best_position course %1d% time %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1314");
		return 0;
	}
	case todo__comm_1315: // 0523=3,unknown_char_anim_command_5618 %1d% values %2d% %3d%
	{
		CollectParameters(&m_nIp, 3);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1315");
		return 0;
	}
	case todo__comm_1316: // 0524=1,get_camera_vehicle_zoom_base %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1316");
		return 0;
	}
	case todo__comm_1317: // 0525=1,set_camera_vehicle_zoom_base %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1317");
		return 0;
	}
	case todo__comm_1318: // 0526=2,unknown_char_command_7812 %1d% value %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1318");
		return 0;
	}
	case todo__comm_1319: // 0527=1,  is_char_on_fire %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1319");
		return 0;
	}
	case todo__comm_1320: // 0528=3,unknown_command_6825 %1d% values %2d% %3d%
	{
		CollectParameters(&m_nIp, 3);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1320");
		return 0;
	}
	case todo__comm_1321: // 0529=3,unknown_char_command_8377 %1d% value %2d% store_to %3d%
	{
		CollectParameters(&m_nIp, 3);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1321");
		return 0;
	}
	case todo__comm_1322: // 052A=3,unknown_char_anim_command_7281 %1d% values %2d% %3d%
	{
		CollectParameters(&m_nIp, 3);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1322");
		return 0;
	}
	case todo__comm_1323: // 052B=1,register_mvrace_time %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1323");
		return 0;
	}
	case todo__comm_1324: // 052C=1,register_skywolf_time %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1324");
		return 0;
	}
	case todo__comm_1325: // 052D=9,add_ped_static_shadow cornerA %1d% %2d% %3d% cornerB %4d% %5d% %6d% intensity %7d% radius %8d% unused %9d%
	{
		CollectParameters(&m_nIp, 9);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1325");
		return 0;
	}
	case todo__comm_1326: // 052E=2,get_radio_channel_all_values %1d% %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1326");
		return 0;
	}
	case todo__comm_1327: // 052F=0,return_player_weapons
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1327");
		return 0;
	}
	case todo__comm_1328: // 0530=1,disable_splash_screen_when_moving_between_levels %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1328");
		return 0;
	}
	case todo__comm_1329: // 0531=2,unknown_char_set_command_8319 %1d% flag %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1329");
		return 0;
	}
	case todo__comm_1330: // 0532=2,unknown_player_set_command_7236 %1d% flag %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1330");
		return 0;
	}
	case todo__comm_1331: // 0533=2,unknown_car_door_command_2714 %1d% door %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1331");
		return 0;
	}
	case todo__comm_1332: // 0534=1,allow_planes_to_move %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1332");
		return 0;
	}
	case todo__comm_1333: // 0535=1,register_dtrial_furthest_hoop %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1333");
		return 0;
	}
	case todo__comm_1334: // 0536=1,register_btrial_furthest_hoop %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1334");
		return 0;
	}
	case todo__comm_1335: // 0537=2,register_btrial_time course %1d% time %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1335");
		return 0;
	}
	case todo__comm_1336: // 0538=2,register_btrial_best_lap course %1d% time %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1336");
		return 0;
	}
	case todo__comm_1337: // 0539=1,register_qttrial_furthest_hoop %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1337");
		return 0;
	}
	case todo__comm_1338: // 053A=2,register_qttrial_time course %1d% time %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1338");
		return 0;
	}
	case todo__comm_1339: // 053B=2,register_qttrial_best_lap course %1d% time %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1339");
		return 0;
	}
	case todo__comm_1340: // 053C=1,register_shrange_time %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1340");
		return 0;
	}
	case todo__comm_1341: // 053D=1,register_shrange_accuracy %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1341");
		return 0;
	}
	case todo__comm_1342: // 053E=1,register_shrange_score %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1342");
		return 0;
	}
	case todo__comm_1343: // 053F=1,unknown_char_audio_command_5171 %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1343");
		return 0;
	}
	case todo__comm_1344: // 0540=2,unknown_audio_command_2762 values %1d% %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1344");
		return 0;
	}
	case todo__comm_1345: // 0541=5,unknown_car_path_coord_command_6291 %1d% unused %2d% store_coords %3d% %4d% %5d%
	{
		CollectParameters(&m_nIp, 5);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1345");
		return 0;
	}
	case todo__comm_1346: // 0542=2,unknown_char_set_command_6416 %1d% flag %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1346");
		return 0;
	}
	case todo__comm_1347: // 0543=2,unknown_char_set_command_2782 %1d% flag %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1347");
		return 0;
	}
	case todo__comm_1348: // 0544=1,unknown_world_bullet_command_7281 %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1348");
		return 0;
	}
	case todo__comm_1349: // 0545=1,unknown_camera_command_5782 %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1349");
		return 0;
	}
	case todo__comm_1350: // 0546=1,register_empire_job_completed %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1350");
		return 0;
	}
	case todo__comm_1351: // 0547=2,unknown_gang_set_command_9365 %1d% to %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1351");
		return 0;
	}
	case todo__comm_1352: // 0548=3,unknown_radar_set_coords_command_6295 %1d% %2d% %3d%
	{
		CollectParameters(&m_nIp, 3);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1352");
		return 0;
	}
	case todo__comm_1353: // 0549=1,unknown_radar_command_1835 %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1353");
		return 0;
	}
	case todo__comm_1354: // 054A=1,unknown_command_6181 %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1354");
		return 0;
	}
	case todo__comm_1355: // 054B=3,unknown_char_command_7359 char %1d% vehicle %2d% flag %3d%
	{
		CollectParameters(&m_nIp, 3);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1355");
		return 0;
	}
	case todo__comm_1356: // 054C=2,unknown_command_8258 %1d% %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1356");
		return 0;
	}
	case todo__comm_1357: // 054D=2,unknown_command_6817 %1d% flag %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1357");
		return 0;
	}
	case todo__comm_1358: // 054E=1,get_number_of_weapons_to_return_to_player %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1358");
		return 0;
	}
	case todo__comm_1359: // 054F=0,set_photograph_has_not_been_taken
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1359");
		return 0;
	}
	case todo__comm_1360: // 0550=1,add_money_spent_on_empire_development %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1360");
		return 0;
	}
	case todo__comm_1361: // 0551=1,add_money_spent_on_empire_repair %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1361");
		return 0;
	}
	case todo__comm_1362: // 0552=1,set_largest_earning_from_empire_building %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1362");
		return 0;
	}
	case todo__comm_1363: // 0553=1,add_money_earnt_from_empire_building %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1363");
		return 0;
	}
	case todo__comm_1364: // 0554=4,set_amounts_empire_sites_owned vance %1d% cholo %2d% sharks %3d% bikers %4d%
	{
		CollectParameters(&m_nIp, 4);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1364");
		return 0;
	}
	case todo__comm_1365: // 0555=12,  is_line_of_sight_clear %1d% %2d% %3d% to %4d% %5d% %6d% buildings %7h% cars %8h% chars %9h% objects %10h% particles %11h% unk12 %12h%
	{
		CollectParameters(&m_nIp, 12);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1365");
		return 0;
	}
	case todo__comm_1366: // 0556=1,unknown_command_1382 %1b%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1366");
		return 0;
	}
	case todo__comm_1367: // 0557=2,unknown_command_4681 %1d% flag %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1367");
		return 0;
	}
	case todo__comm_1368: // 0558=2,unknown_command_7441 %1d% value %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1368");
		return 0;
	}
	case todo__comm_1369: // 0559=1,unknown_object_command_0167 %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1369");
		return 0;
	}
	case todo__comm_1370: // 055A=0,  unknown_world_streaming_check_command_6292
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1370");
		return 0;
	}
	case todo__comm_1371: // 055B=1,register_rush_damage_value %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1371");
		return 0;
	}
	case todo__comm_1372: // 055C=1,register_airrace2_time %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1372");
		return 0;
	}
	case todo__comm_1373: // 055D=1,register_dock_pcjplay_time %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1373");
		return 0;
	}
	case todo__comm_1374: // 055E=1,register_park_pcjplay_time %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1374");
		return 0;
	}
	case todo__comm_1375: // 055F=1,register_mvrace2_time %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1375");
		return 0;
	}
	case todo__comm_1376: // 0560=1,register_gtrial_best_lap %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1376");
		return 0;
	}
	case todo__comm_1377: // 0561=1,register_gtrial_furthest_hoop %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1377");
		return 0;
	}
	case todo__comm_1378: // 0562=1,register_gtrial_time %1d%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1378");
		return 0;
	}
	case todo__comm_1379: // 0563=2,unknown_command_2951 %1d% flag %2d%
	{
		CollectParameters(&m_nIp, 2);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1379");
		return 0;
	}
	case todo__comm_1380: // 0564=1,allow_pause_in_widescreen %1h%
	{
		CollectParameters(&m_nIp, 1);
		script_assert(false && "TODO_OR_CHECK_todo__comm_1380");
		return 0;
	}
	default:
		script_assert(0);
	}
	return -1;
}
