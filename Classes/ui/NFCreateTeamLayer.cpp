//
//  NFCreateTeamLayer.cpp
//  demo
//
//  Created by 瑛峰 on 14/12/7.
//
//

#include "NFCreateTeamLayer.h"

/************************************************************************/
/*创建忍队层															*/
/************************************************************************/

Scene * CNFTeamCreateLayer::scene()
{
    do
    {
        Scene* pScene = Scene::create();
        CC_BREAK_IF(pScene==NULL);
        
        CNFTeamCreateLayer* pLayer = CNFTeamCreateLayer::create();
        CC_BREAK_IF(pLayer==NULL);
        
        pScene->addChild(pLayer);
        return pScene;
        
    } while (false);
    CCLog("Fun CNFTeamCreateLayer::scene Error!");
    return NULL;
}

//CNFTeamCreateLayer * CNFTeamCreateLayer::CreateLayer()
//{
//    CNFTeamCreateLayer *pRet = new CNFTeamCreateLayer();
//    if (pRet && pRet->init())
//    {
//        pRet->autorelease();
//        return pRet;
//    }
//    CCLog("Fun CNFTeamCreateLayer::CreateLayer Error!");
//    delete pRet;
//    pRet = NULL;
//    return NULL;
//}

bool CNFTeamCreateLayer::init()
{
    do
    {
        //初始化父类
        CC_BREAK_IF(Layer::init()==false);
        
        m_nRoleID = 1;
        
        //创建主场景UI层
        Layer* pUiLayer = Layer::create();
        CC_BREAK_IF(pUiLayer==NULL);
        
        //-------------------加入主场景UI----------------------------
//        UILayout *pCreateNinja = dynamic_cast<UILayout*>	(GUIReader::shareReader()->widgetFromJsonFile("CreateNinja.json"));
//        CC_BREAK_IF(pCreateNinja==NULL);
//        pUiLayer->addWidget(pCreateNinja);
//        pCreateNinja->setName("CreateNinjaLayer");
//        pCreateNinja->setSize(getContentSize());
//        
//        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("armature/xiaoyin.ExportJson");
//        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("armature/NewProject.ExportJson");
//        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("armature/minren1.ExportJson");
//        
//        
//        //获取返回按钮
//        UIButton *pBtn_Back=dynamic_cast<UIButton*>(pCreateNinja->getChildByName("MainUi")->getChildByName("Btn_Return"));
//        CC_BREAK_IF(pBtn_Back==NULL);
//        pBtn_Back->addTouchEventListener(this,toucheventselector(CNFTeamCreateLayer::OnBackToLoginPage));
//        
//        //获取开始按钮
//        UIButton *pBtn_Create_Team=dynamic_cast<UIButton*>(pCreateNinja->getChildByName("MainUi")->getChildByName("Btn_Create_Team"));
//        CC_BREAK_IF(pBtn_Create_Team==NULL);
//        pBtn_Create_Team->addTouchEventListener(this,toucheventselector(CNFTeamCreateLayer::OnGameStartPage));
//        
//        //获取输入框
//        UITextField* pTextField = dynamic_cast<UITextField*>(pCreateNinja->getChildByName("MainUi")->getChildByName("Team_Name_TextField"));
//        CC_BREAK_IF(pTextField==NULL);
//        pTextField->setTouchEnabled(true);
//        pTextField->addEventListenerTextField(this, textfieldeventselector(CNFTeamCreateLayer::textFieldEvent));
//        pTextField->setText("");
//        
//        
//        for (int i=0;i<3;i++)
//        {
//            //获取人物按钮
//            UIButton *pBtn_Role=dynamic_cast<UIButton*>(pCreateNinja->getChildByName("MainUi")->getChildByName(CCString::createWithFormat("Btn_Char_%d",i+1)->getCString()));
//            CC_BREAK_IF(pBtn_Role==NULL);
//            pBtn_Role->addTouchEventListener(this,toucheventselector(CNFTeamCreateLayer::OnRoleSelect));
//            
//            if (i==0)
//            {
//                //获取按下图片
//                UIImageView *pSelect_Img=dynamic_cast<UIImageView*>(pBtn_Role->getChildByName("Select_Img"));
//                CC_BREAK_IF(pSelect_Img==NULL);
//                pSelect_Img->setVisible(true);
//            }
//        }
//        
//        
//        
//        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("armature/xiaoyin.ExportJson");
//        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("armature/NewProject.ExportJson");
//        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("armature/minren1.ExportJson");
//        
//        char cName[3][256]={"minren1","xiaoyin","NewProject"};
//        
//        
//        
//        CCArmature *pRole = CCArmature::create(cName[0]);
//        CC_BREAK_IF(pRole==NULL);
//        pRole->setPosition(ccp(SCREEN_WIDTH/2,210));
//        pRole->setAnchorPoint(ccp(pRole->getAnchorPoint().x,0));
//        pRole->getAnimation()->play("hold",-1,-1,-1,10000);
//        addChild(pRole,enZOrderMid,enTagRole);
//        
//        
//        
//        
//        
//        addChild(pUiLayer,enZOrderBack,enTagStudioMainUiLayer);
        return true;
    } while (false);
    log("Fun CNFTeamCreateLayer::init Error!");
    return false;
}

