//
//  NFServerDataManager.cpp
//  demo
//
//  Created by 瑛峰 on 14/12/7.
//
//

#include "NFServerDataManager.h"


/************************************************************************/
/*					服务器数据管理类                                                                     */
/************************************************************************/
static CNFServerDataManager * g_pServerDataManager = NULL;
CNFServerDataManager * CNFServerDataManager::SharedData()
{
    if(g_pServerDataManager==NULL)
    {
        g_pServerDataManager = new CNFServerDataManager();
        
        //临时：初始化技能信息
        for (int i=1;i<=3;i++)
        {
            CNFServerSkillInfoVec PosInfo;
            for (int j=1;j<=8;j++)
            {
                tagServerSkillInfo Info;
                if (j==1)		Info.nSkillID = 11;
                if (j==2)		Info.nSkillID = 12;
                if (j==3)		Info.nSkillID = 13;
                if (j==4)		Info.nSkillID = 101;
                if (j==5)		Info.nSkillID = 102;
                
                Info.nSkillLevel = j;
                Info.nPos = j;
                
                if (j==6)
                {
                    Info.nSkillID = 14;
                    Info.nSkillLevel = 11;
                    Info.nPos = 0;
                }
                if (j==7)
                {
                    Info.nSkillID = 15;
                    Info.nSkillLevel = 11;
                    Info.nPos = 0;
                }
                
                if (j==8)
                {
                    Info.nSkillID = 103;
                    Info.nSkillLevel = 11;
                    Info.nPos = 0;
                }
                
                
                PosInfo.push_back(Info);
            }
            g_pServerDataManager->m_SkillInfoMap[i] = PosInfo;
        }
        
        //临时：初始化角色选择信息
        for (int i=0;i<3;i++)
        {
            tagServerRoleSelectInfo Info;
            Info.nRoleID = i+1;
            Info.fExp = 1;
            Info.fStrength = 1;
            Info.nRoleLevel = 1;
            Info.strRoleName = "naruto";
            if (i==0)		Info.nState = -1;
            if (i==1)		Info.nState = -1;
            if (i==2)		Info.nState = -1;
            
            g_pServerDataManager->m_RoleSelectInfoVec.push_back(Info);
        }
        
    }
    return g_pServerDataManager;
}

//服务器分区列表信息
void CNFServerDataManager::SetServerListInfo( tagServerListInfo ServerListInfo )
{
    m_ServerListInfo = ServerListInfo;
}
void CNFServerDataManager::GetServerListInfo( tagServerListInfo &ServerListInfo )
{
    ServerListInfo = m_ServerListInfo;
}

//角色选择信息
void CNFServerDataManager::SetRoleSelectInfo( CNFServerRoleSelectInfoVec RoleSelectInfoVec )
{
    m_RoleSelectInfoVec = RoleSelectInfoVec;
}
void CNFServerDataManager::GetRoleSelectInfo( CNFServerRoleSelectInfoVec &RoleSelectInfoVec )
{
    RoleSelectInfoVec = m_RoleSelectInfoVec;
}