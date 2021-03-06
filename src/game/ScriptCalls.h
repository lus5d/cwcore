/*
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 *
 * Copyright (C) 2009 CWCore <http://www.wow-extrem.de/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef __SCRIPT_CALLS_H
#define __SCRIPT_CALLS_H

#include "Common.h"
#include "ObjectMgr.h"

class Creature;
class CreatureAI;
class GameObject;
class Item;
class Player;
class Quest;
class SpellCastTargets;
class Map;
class InstanceData;

bool LoadScriptingModule(char const* libName = "");
void UnloadScriptingModule();
//Hawthorne - On Events
typedef void(CW_IMPORT * scriptCallOnLogin) (Player *player);
typedef void(CW_IMPORT * scriptCallOnLogout) (Player *player);
typedef void(CW_IMPORT * scriptCallOnPVPKill) (Player *killer, Player *killed );
typedef bool(CW_IMPORT * scriptCallOnSpellCast)(Unit *pUnitTarget, Item *pItemTarget, GameObject *pGoTarget, uint32 i, SpellEntry const *spell);
typedef uint32(CW_IMPORT * scriptCallOnGetXP) (Player *pPlayer, uint32 amount);
typedef int32(CW_IMPORT * scriptCallOnGetMoney) (Player *pPlayer, int32 amount);
typedef bool(CW_IMPORT * scriptCallOnPlayerChat) (Player *pPlayer, const char *text);
typedef void(CW_IMPORT * scriptCallOnServerStartup) ();
typedef void(CW_IMPORT * scriptCallOnServerShutdown) ();
typedef void(CW_IMPORT * scriptCallOnAreaChange) (Player *pPlayer, AreaTableEntry const *pArea);
typedef bool(CW_IMPORT * scriptCallOnItemClick) (Player *pPlayer, Item *pItem);
typedef bool(CW_IMPORT * scriptCallOnItemOpen) (Player *pPlayer, Item *pItem);
typedef bool(CW_IMPORT * scriptCallOnGoClick) (Player *pPlayer, GameObject *pGameObject);
typedef void(CW_IMPORT * scriptCallOnCreatureKill) (Player *pPlayer, Creature *pCreature);

typedef void(CW_IMPORT * scriptCallScriptsInit) (char const*);
typedef void(CW_IMPORT * scriptCallScriptsFree) ();
typedef char const* (CW_IMPORT * scriptCallScriptsVersion) ();

typedef bool(CW_IMPORT * scriptCallGossipHello) (Player *player, Creature *_Creature );
typedef bool(CW_IMPORT * scriptCallQuestAccept) (Player *player, Creature *_Creature, Quest const *);
typedef bool(CW_IMPORT * scriptCallGossipSelect)(Player *player, Creature *_Creature, uint32 sender, uint32 action);
typedef bool(CW_IMPORT * scriptCallGossipSelectWithCode)( Player *player, Creature *_Creature, uint32 sender, uint32 action, const char* sCode );
typedef bool(CW_IMPORT * scriptCallGOSelect)(Player *player, GameObject *_GO, uint32 sender, uint32 action);
typedef bool(CW_IMPORT * scriptCallGOSelectWithCode)( Player *player, GameObject *_GO, uint32 sender, uint32 action, const char* sCode );
typedef bool(CW_IMPORT * scriptCallQuestSelect)( Player *player, Creature *_Creature, Quest const* );
typedef bool(CW_IMPORT * scriptCallQuestComplete)(Player *player, Creature *_Creature, Quest const*);
typedef uint32(CW_IMPORT * scriptCallNPCDialogStatus)( Player *player, Creature *_Creature);
typedef uint32(CW_IMPORT * scriptCallGODialogStatus)( Player *player, GameObject * _GO);
typedef bool(CW_IMPORT * scriptCallChooseReward)( Player *player, Creature *_Creature, Quest const*, uint32 opt );
typedef bool(CW_IMPORT * scriptCallItemHello)( Player *player, Item *, Quest const*);
typedef bool(CW_IMPORT * scriptCallGOHello)( Player *player, GameObject * );
typedef bool(CW_IMPORT * scriptCallAreaTrigger)( Player *player, AreaTriggerEntry const* );
typedef bool(CW_IMPORT * scriptCallItemQuestAccept)(Player *player, Item *, Quest const*);
typedef bool(CW_IMPORT * scriptCallGOQuestAccept)(Player *player, GameObject *, Quest const*);
typedef bool(CW_IMPORT * scriptCallGOChooseReward)(Player *player, GameObject *, Quest const*, uint32 opt );
typedef bool(CW_IMPORT * scriptCallItemUse) (Player *player, Item *_Item, SpellCastTargets const& targets);
typedef bool(CW_IMPORT * scriptCallItemExpire) (Player *player, ItemPrototype const *_ItemProto);
typedef bool(CW_IMPORT * scriptCallEffectDummyGameObj) (Unit *caster, uint32 spellId, uint32 effIndex, GameObject *gameObjTarget);
typedef bool(CW_IMPORT * scriptCallEffectDummyCreature) (Unit *caster, uint32 spellId, uint32 effIndex, Creature *crTarget);
typedef bool(CW_IMPORT * scriptCallEffectDummyItem) (Unit *caster, uint32 spellId, uint32 effIndex, Item *itemTarget);
typedef CreatureAI* (CW_IMPORT * scriptCallGetAI) ( Creature *_Creature );
typedef InstanceData* (CW_IMPORT * scriptCallCreateInstanceData) (Map *map);

typedef struct
{
    scriptCallScriptsInit ScriptsInit;
    scriptCallScriptsFree ScriptsFree;
    scriptCallScriptsVersion ScriptsVersion;

    scriptCallOnLogin OnLogin;
    scriptCallOnLogout OnLogout;
    scriptCallOnPVPKill OnPVPKill;
    scriptCallOnSpellCast OnSpellCast;
    scriptCallOnGetXP OnGetXP;
    scriptCallOnGetMoney OnGetMoney;
    scriptCallOnPlayerChat OnPlayerChat;
    scriptCallOnServerStartup OnServerStartup;
    scriptCallOnServerShutdown OnServerShutdown;
    scriptCallOnAreaChange OnAreaChange;
    scriptCallOnItemClick OnItemClick;
    scriptCallOnItemOpen OnItemOpen;
    scriptCallOnGoClick OnGoClick;
    scriptCallOnCreatureKill OnCreatureKill;
    scriptCallGossipHello GossipHello;
    scriptCallGOChooseReward GOChooseReward;
    scriptCallQuestAccept QuestAccept;
    scriptCallGossipSelect GossipSelect;
    scriptCallGossipSelectWithCode GossipSelectWithCode;
    scriptCallGOSelect GOSelect;
    scriptCallGOSelectWithCode GOSelectWithCode;
    scriptCallQuestSelect QuestSelect;
    scriptCallQuestComplete QuestComplete;
    scriptCallNPCDialogStatus NPCDialogStatus;
    scriptCallGODialogStatus GODialogStatus;
    scriptCallChooseReward ChooseReward;
    scriptCallItemHello ItemHello;
    scriptCallGOHello GOHello;
    scriptCallAreaTrigger scriptAreaTrigger;
    scriptCallItemQuestAccept ItemQuestAccept;
    scriptCallGOQuestAccept GOQuestAccept;
    scriptCallItemUse ItemUse;
    scriptCallItemExpire ItemExpire;
    scriptCallEffectDummyGameObj  EffectDummyGameObj;
    scriptCallEffectDummyCreature EffectDummyCreature;
    scriptCallEffectDummyItem     EffectDummyItem;
    scriptCallGetAI GetAI;
    scriptCallCreateInstanceData CreateInstanceData;

    CW_LIBRARY_HANDLE hScriptsLib;
}_ScriptSet,*ScriptsSet;

extern ScriptsSet Script;
#endif

