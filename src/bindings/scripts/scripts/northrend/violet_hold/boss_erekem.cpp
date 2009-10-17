/* Script Data Start
SDName: Boss erekem
SDAuthor: LordVanMartin
SD%Complete:
SDComment:
SDCategory:
Script Data End */

/*** SQL START ***
update creature_template set scriptname = '' where entry = '';
*** SQL END ***/
#include "precompiled.h"

//Spells
#define SPELL_BLOODLUST                                54516
#define SPELL_BREAK_BONDS                              59463
#define SPELL_CHAIN_HEAL                               54481
#define SPELL_EARTH_SHIELD                             54479
#define SPELL_EARTH_SHOCK                              54511
#define SPELL_LIGHTNING_BOLT                           53044
#define SPELL_STORMSTRIKE                              51876

//not in db
//Yells
#define SAY_AGGRO                                   -1608010
#define SAY_SLAY_1                                  -1608011
#define SAY_SLAY_2                                  -1608012
#define SAY_SLAY_3                                  -1608013
#define SAY_DEATH                                   -1608014
#define SAY_SPAWN                                   -1608015
#define SAY_ADD_KILED                               -1608016
#define SAY_BOTH_ADDS_KILED                         -1608017

struct CW_DLL_DECL boss_erekemAI : public ScriptedAI
{
    boss_erekemAI(Creature *c) : ScriptedAI(c) {}

    void Reset() {}
    void EnterCombat(Unit* who)
    {
        DoScriptText(SAY_AGGRO, m_creature);
    }
    void AttackStart(Unit* who) {}
    void MoveInLineOfSight(Unit* who) {}
    void UpdateAI(const uint32 diff)
    {
        //Return since we have no target
        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }
    void JustDied(Unit* killer)
    {
        DoScriptText(SAY_DEATH, m_creature);
    }
    void KilledUnit(Unit *victim)
    {
        if (victim == m_creature)
            return;
        switch(rand()%3)
        {
            case 0: DoScriptText(SAY_SLAY_1, m_creature);break;
            case 1: DoScriptText(SAY_SLAY_2, m_creature);break;
            case 2: DoScriptText(SAY_SLAY_3, m_creature);break;
        }
    }
};

CreatureAI* GetAI_boss_erekem(Creature* pCreature)
{
    return new boss_erekemAI (pCreature);
}

struct CW_DLL_DECL mob_erekem_guardAI : public ScriptedAI
{
    mob_erekem_guardAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = c->GetInstanceData();
    }
    
    uint32 uiEarthShieldTimer;
    uint32 uiLightningBoltTimer;
    uint32 uiBloodlustTimer;
    
    ScriptedInstance* pInstance;
    
    void Reset()
    {
        uiEarthShieldTimer = 20000;
        uiLightningBoltTimer = urand(0,5000);
        uiBloodlustTimer = urand(8000,18000);
    }
    
    void EnterCombat(Unit* who)
    {
        DoCast(m_creature, H_SPELL_EARTH_SHIELD);
    }
    
    void MoveInLineOfSight(Unit* who) {}
        
    void UpdateAI(const uint32 diff)
    {
        if (uiEarthShieldTimer < diff)
        {
            DoCast(m_creature, H_SPELL_EARTH_SHIELD);
            uiEarthShieldTimer = 20000;
        } else uiEarthShieldTimer -= diff;
        
        if (uiLightningBoltTimer < diff)
        {
            if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                DoCast(pTarget, SPELL_LIGHTNING_BOLT);
            uiLightningBoltTimer = urand(18000,24000);
        } else uiLightningBoltTimer -= diff;
        
        if (uiBloodlustTimer < diff)
        {
            DoCast(m_creature,SPELL_BLOODLUST);
            uiBloodlustTimer = urand(35000,45000);
        } else uiBloodlustTimer -= diff;
    }
};

CreatureAI* GetAI_mob_erekem_guard(Creature* pCreature)
{
    return new mob_erekem_guardAI (pCreature);
}


void AddSC_boss_erekem()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name="boss_erekem";
    newscript->GetAI = &GetAI_boss_erekem;
    newscript->RegisterSelf();
    
    newscript->Name="mob_erekem_guard";
    newscript->GetAI = &GetAI_mob_erekem_guard;
    newscript->RegisterSelf();
}
