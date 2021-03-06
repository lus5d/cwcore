#include "precompiled.h"
#include "oculus.h"

#define MAX_ENCOUNTER 4

/* The Occulus encounters:
0 - Drakos the Interrogator
1 - Varos Cloudstrider
2 - Mage-Lord Urom
3 - Ley-Guardian Eregos */

struct CW_DLL_DECL instance_oculus : public ScriptedInstance
{
    instance_oculus(Map* pMap) : ScriptedInstance(pMap) {Initialize();};
    
    uint64 uiDrakos;
    uint64 uiVaros;
    uint64 uiUrom;
    uint64 uiEregos;
    
    uint8 m_auiEncounter[MAX_ENCOUNTER];
    std::string str_data;
    
    void OnCreatureCreate(Creature* pCreature, bool add)
    {
        switch(pCreature->GetEntry())
        {
            case CREATURE_DRAKOS:
                uiDrakos = pCreature->GetGUID();
                break;
            case CREATURE_VAROS:
                uiVaros = pCreature->GetGUID();
                break;
            case CREATURE_UROM:
                uiUrom = pCreature->GetGUID();
                break;
            case CREATURE_EREGOS:
                uiEregos = pCreature->GetGUID();
                break;
        }
    }
    
    void SetData(uint32 type, uint32 data)
    {
        switch(type)
        {
            case DATA_DRAKOS_EVENT:
                m_auiEncounter[0] = data;
                break;
            case DATA_VAROS_EVENT:
                m_auiEncounter[1] = data;
                break;
            case DATA_UROM_EVENT:
                m_auiEncounter[2] = data;
                break;
            case DATA_EREGOS_EVENT:
                m_auiEncounter[3] = data;
                break;
        }

        if (data == DONE)
            SaveToDB();
    }
    
    uint32 GetData(uint32 type)
    {
        switch(type)
        {
            case DATA_DRAKOS_EVENT:                return m_auiEncounter[0];
            case DATA_VAROS_EVENT:                 return m_auiEncounter[1];
            case DATA_UROM_EVENT:                  return m_auiEncounter[2];
            case DATA_EREGOS_EVENT:                return m_auiEncounter[3];
        }

        return 0;
    }
    
    uint64 GetData64(uint32 identifier)
    {
        switch(identifier)
        {
            case DATA_DRAKOS:                 return uiDrakos;
            case DATA_VAROS:                  return uiVaros;
            case DATA_UROM:                   return uiUrom;
            case DATA_EREGOS:                 return uiEregos;
        }

        return 0;
    }

    
    std::string GetSaveData()
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;
        saveStream << "T O " << m_auiEncounter[0] << " " << m_auiEncounter[1] << " " << m_auiEncounter[2] << " " << m_auiEncounter[3];

        str_data = saveStream.str();

        OUT_SAVE_INST_DATA_COMPLETE;
        return str_data;
    }

    void Load(const char* in)
    {
        if (!in)
        {
            OUT_LOAD_INST_DATA_FAIL;
            return;
        }

        OUT_LOAD_INST_DATA(in);

        char dataHead1, dataHead2;
        uint16 data0, data1, data2, data3;

        std::istringstream loadStream(in);
        loadStream >> dataHead1 >> dataHead2 >> data0 >> data1 >> data2 >> data3;

        if (dataHead1 == 'T' && dataHead2 == 'O')
        {
            m_auiEncounter[0] = data0;
            m_auiEncounter[1] = data1;
            m_auiEncounter[2] = data2;
            m_auiEncounter[3] = data3;

            for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                if (m_auiEncounter[i] == IN_PROGRESS)
                    m_auiEncounter[i] = NOT_STARTED;

        } else OUT_LOAD_INST_DATA_FAIL;

        OUT_LOAD_INST_DATA_COMPLETE;
    }
};

InstanceData* GetInstanceData_instance_oculus(Map* pMap)
{
    return new instance_oculus(pMap);
}

void AddSC_instance_oculus()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "instance_oculus";
    newscript->GetInstanceData = &GetInstanceData_instance_oculus;
    newscript->RegisterSelf();
}
