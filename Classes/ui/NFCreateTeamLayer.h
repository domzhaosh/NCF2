//
//  NFCreateTeamLayer.h
//  demo
//
//  Created by 瑛峰 on 14/12/7.
//
//

#ifndef _NF_TEAM_CREATE_SCENE_HEAD_
#define _NF_TEAM_CREATE_SCENE_HEAD_

#include "../publicdef/PublicDef.h"

/************************************************************************/
/*创建忍队层															*/
/************************************************************************/
class CNFTeamCreateLayer : public Layer
{
protected:
    //标签
    enum
    {
        enTagStudioMainUiLayer,
        enTagRole,
    };
    
    int				m_nRoleID;			//角色ID	1.鸣人	2.小樱	3.佐助
    
public:
//    static CNFTeamCreateLayer * CreateLayer();
    CREATE_FUNC(CNFTeamCreateLayer);
    static Scene * scene();
    
    void OnGameStartPage(Ref* pSender, TouchEventType type);				//创建人物
    
    void textFieldEvent(Ref* pSender, TextFiledEventType type);
    
    void OnBackToLoginPage(Ref* pSender, TouchEventType type);				//返回登录界面
    
    
    void OnRoleSelect(Ref* pSender, TouchEventType type);					//角色选择界面
    
protected:
    virtual bool init();     
};


#endif /* defined(_NF_TEAM_CREATE_SCENE_HEAD_) */
