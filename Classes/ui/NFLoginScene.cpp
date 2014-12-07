//
//  NFLoginScene.cpp
//  NCF
//
//  Created by 瑛峰 on 14/11/12.
//
//

#include "NFLoginScene.h"
#include "NFLoadingLayer.h"
#include "NFServerChangeLayer.h"
#include "NFServerDataManager.h"
//#include "2d/CCActionInstant.h"

#define _LOADREC_NUM_		16
/************************************************************************/
/*			登录场景													*/
/************************************************************************/
Scene* CNFLoginScene::scene()
{
    do
    {
        Scene* pScene = Scene::create();
        CC_BREAK_IF(pScene==NULL);
        
        CNFLoginScene* pLayer = CNFLoginScene::create();
        CC_BREAK_IF(pLayer==NULL);
        
        pScene->addChild(pLayer);
        return pScene;
        
    } while (false);
    log("Fun CNFLoginScene::scene Error!");
    return NULL;
}



void CNFLoginScene::onEnter()
{
    Layer::onEnter();
    do
    {
        //创建Laoding层
        CNFLoadingLayer * pLoading = CNFLoadingLayer::create();
        CC_BREAK_IF(pLoading==NULL);
        addChild(pLoading,enZOrderFront+10000,enTagLoading);

        m_nLoadRecNum = 0;
        m_nLoadRecTotalNum = _LOADREC_NUM_;

        //预加载本层资源
        LoadRec();
        
        return ;
    } while (false);
    log("Fun CNFLoginScene::onEnter Error!");
}


//资源预加载
void CNFLoginScene::LoadRec()
{
    
    Director::getInstance()->getTextureCache()->addImageAsync("ui/serverselect_bg.png", CC_CALLBACK_1(CNFLoginScene::OnLoadRecCallBack, this));
//    CCTextureCache::sharedTextureCache()->addImageAsync("ui/serverselect_bg.png",this,callfuncO_selector(CNFLoginScene::OnLoadRecCallBack));
    
  
//    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/kulougongshou.ExportJson",this,schedule_selector(CNFLoginScene::OnLoadArmatureData));
    
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("kulougongshou.ExportJson",
                                                                 this, schedule_selector(CNFLoginScene::OnLoadArmatureData));
    
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("kulouzhanshi.ExportJson",this,schedule_selector(CNFLoginScene::OnLoadArmatureData));
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("mayi.ExportJson",this,schedule_selector(CNFLoginScene::OnLoadArmatureData));
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("bianyikunchong.ExportJson",this,schedule_selector(CNFLoginScene::OnLoadArmatureData));
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("bubing.ExportJson",this,schedule_selector(CNFLoginScene::OnLoadArmatureData));
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("xiaoyin.ExportJson",this,schedule_selector(CNFLoginScene::OnLoadArmatureData));
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("NewProject.ExportJson",this,schedule_selector(CNFLoginScene::OnLoadArmatureData));
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("minren1.ExportJson",this,schedule_selector(CNFLoginScene::OnLoadArmatureData));
    
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("kulou_arrow.ExportJson",this,schedule_selector(CNFLoginScene::OnLoadArmatureData));
    
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("naili.ExportJson",this,schedule_selector(CNFLoginScene::OnLoadArmatureData));
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("NPC_kakaxi.ExportJson",this,schedule_selector(CNFLoginScene::OnLoadArmatureData));
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("portal.ExportJson",this,schedule_selector(CNFLoginScene::OnLoadArmatureData));
    
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("hited_light.ExportJson",this,schedule_selector(CNFLoginScene::OnLoadArmatureData));
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("public_casting.ExportJson",this,schedule_selector(CNFLoginScene::OnLoadArmatureData));
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("skill_light_1.ExportJson",this,schedule_selector(CNFLoginScene::OnLoadArmatureData));
}

//资源加载回调
void CNFLoginScene::OnLoadRecCallBack( Ref *pObj )
{
    do
    {
        m_nLoadRecNum ++;
        
        //得到Laoding层
        CNFLoadingLayer * pLoading = dynamic_cast<CNFLoadingLayer *>(getChildByTag(enTagLoading));
        CC_BREAK_IF(pLoading==NULL);
        pLoading->SetPro( (float)m_nLoadRecNum/(float)m_nLoadRecTotalNum );
        
        if(m_nLoadRecNum==m_nLoadRecTotalNum){
            //延迟1秒
//            this->runAction(Sequence::create(
//                                               DelayTime::create(2.f),
//                                               CallFunc::create(this,callfunc_selector(CNFLoginScene::InitSceneUI)),
//                                               NULL));
            
            
            this->runAction(Sequence::create(DelayTime::create(2.f),
                                             CallFuncN::create(CC_CALLBACK_0(CNFLoginScene::InitSceneUI, this)),
                                             
                                             NULL));
        }
        
        return ;
    } while (false);
    log("Fun CNFLoginScene::OnLoadRecCallBack Error!");
}



void CNFLoginScene::OnLoadArmatureData( float percent )
{
    //CCLog("==================%f",percent);
    
    m_nLoadRecNum ++;
    
    //得到Laoding层
    CNFLoadingLayer * pLoading = dynamic_cast<CNFLoadingLayer *>(getChildByTag(enTagLoading));
    if(pLoading!=NULL){
        pLoading->SetPro( (float)m_nLoadRecNum/(float)m_nLoadRecTotalNum );
    }else{
        log("Fun CNFLoginScene::OnLoadArmatureData Error!");
    }
    
    if(m_nLoadRecNum==m_nLoadRecTotalNum){
        //延迟1秒
//        this->runAction(CCSequence::create(
//                                           CCDelayTime::create(2.f),
//                                           CCCallFunc::create(this,callfunc_selector(CNFLoginScene::InitSceneUI)),
//                                           NULL));
        
        
        this->runAction(Sequence::create(DelayTime::create(2.f),
                                         CallFuncN::create(CC_CALLBACK_0(CNFLoginScene::InitSceneUI, this)),
                                         
                                         NULL));
    }
    if (percent >= 1)
    {
        log("addArmatureFileInfoAsync over");
    }
}


void CNFLoginScene::RecMsg( int nMsgID,void* pInfo,int nSize )
{
    switch (nMsgID)
    {
        case enMsg_ServerSelect:
        {
            tagServerSelect * pCmd = (tagServerSelect *)pInfo;
            
            m_nCurrentServerID = pCmd->nServerID;
            
            //创建登录UI层
//            UILayer* pLoginUiLayer = dynamic_cast<UILayer*>(getChildByTag(enTagStudioLoginLayer));
//            CC_BREAK_IF(pLoginUiLayer==NULL);
            
            Layer* pLoginUiLayer = dynamic_cast<Layer*>(getChildByTag(enTagStudioLoginLayer));
            CC_BREAK_IF(pLoginUiLayer==NULL);
            
//            UILayout *pLoginWidget = dynamic_cast<UILayout*>(pLoginUiLayer->getWidgetByName("LoginLayer"));
//            CC_BREAK_IF(pLoginWidget==NULL);
            
            auto pLoginWidget = dynamic_cast<Node*>(pLoginUiLayer->getChildByName("LoginLayer"));
            CC_BREAK_IF(pLoginWidget==NULL);
            
            
            //服务器名称label
            
            /**
             ValueMap pDicLang = FileUtils::getInstance()->getValueMapFromFile("ui_xml/serverselect_xml.xml");
             std::string pStrServerName = pDicLang.at("server_name").asString();
             char szName[NAME_LEN] = {0};
             sprintf(szName,pStrServerName.c_str(),nCurrentServerID);
             
             Label * pLabelServerName = Label::createWithSystemFont(szName, "Arial", 20);
             CC_BREAK_IF(pLabelServerName==NULL);
             pLabelServerName->setPosition(pBtnCurrentServer->getPosition());
             addChild(pLabelServerName,enZOrderFront);
             */
            
            ValueMap pDicLang = FileUtils::getInstance()->getValueMapFromFile("ui_xml/serverselect_xml.xml");
            std::string pStrServerName = pDicLang.at("server_name").asString();
            char szName[NAME_LEN] = {0};
            sprintf(szName,pStrServerName.c_str(),m_nCurrentServerID);
            
            auto pServer_Name_Lable = dynamic_cast<Text*>(pLoginWidget->getChildByName("Normal_Login_panel")->getChildByName("MainUi")->getChildByName("Server_Name_Lable"));
            CC_BREAK_IF(pServer_Name_Lable==NULL);
            pServer_Name_Lable->setString(szName);
            
            
//            CCDictionary *pDicLang = CCDictionary::createWithContentsOfFile("ui_xml/serverselect_xml.xml");
//            CC_BREAK_IF(pDicLang==NULL);
//            CCString *pStrServerName = dynamic_cast<CCString*>(pDicLang->objectForKey("server_name"));
            
//            char szName[NAME_LEN] = {0};
//            sprintf(szName,pStrServerName->m_sString.c_str(),m_nCurrentServerID);
            
//            UILabel* pServer_Name_Lable = dynamic_cast<UILabel*>(pLoginWidget->getChildByName("MainUi")->getChildByName("Server_Bg")->getChildByName("Server_Name_Lable"));
//            CC_BREAK_IF(pServer_Name_Lable==NULL);
//            
//            pServer_Name_Lable->setText(szName);
            
            
            
            
            
            //显示正常登录模块
//            UILayout* pNormalLogin_Panel = dynamic_cast<UILayout*>(pLoginWidget->getChildByName("MainUi")->getChildByName("NormalLogin_Panel"));
//            CC_BREAK_IF(pNormalLogin_Panel==NULL);
//            pNormalLogin_Panel->setEnabled(true);
//            pNormalLogin_Panel->setVisible(true);
            
            //显示正常登录模块
            Widget* pNormalLogin_Panel = dynamic_cast<Widget*>(pLoginWidget->getChildByName("Normal_Login_panel")->getChildByName("MainUi")->getChildByName("NormalLogin_Panel"));
            CC_BREAK_IF(pNormalLogin_Panel==NULL);
            pNormalLogin_Panel->setEnabled(true);
            pNormalLogin_Panel->setVisible(true);
            
        }break;
    }
}





void CNFLoginScene::InitSceneUI()
{
    do
    {
        //移除Laoding层
        CNFLoadingLayer * pLoading = dynamic_cast<CNFLoadingLayer *>(getChildByTag(enTagLoading));
        if (pLoading!=NULL)
            removeChildByTag(enTagLoading,true);
        
        /************************************************************************/
        /*				2.联网：得到服务器ID                                                                     */
        /************************************************************************/
        m_nCurrentServerID = 16;
        m_nServerTotalNum = 31;
        
        
        
        //创建登录UI层   //版本变化
//        UILayer* pLoginUiLayer = UILayer::create();
//        CC_BREAK_IF(pLoginUiLayer==NULL);
        Layer* pLoginUiLayer = Layer::create();
        CC_BREAK_IF(pLoginUiLayer==NULL);
        
        
//      版本变化
//        UILayout *pLoginWidget = dynamic_cast<UILayout*>(GUIReader::shareReader()->widgetFromJsonFile("NormalLogin.json"));
//        CC_BREAK_IF(pLoginWidget==NULL);
//        pLoginUiLayer->addWidget(pLoginWidget);
//        pLoginWidget->setName("LoginLayer");
//        pLoginWidget->setSize(getContentSize());
//        
//        addChild(pLoginUiLayer,enZOrderBack,enTagStudioLoginLayer);
        
        
        
        
        Node* pLoginWidget = CSLoader::createNode("NormalLogin.csb");
        CC_BREAK_IF(pLoginWidget==NULL);
        pLoginUiLayer->addChild(pLoginWidget);
        pLoginWidget->setName("LoginLayer");
       
        addChild(pLoginUiLayer,enZOrderBack,enTagStudioLoginLayer);
        
        
        
        //设置切换服务器按钮回调
//        UIButton* pBtn_Server_Select = dynamic_cast<UIButton*>(pLoginWidget->getChildByName("MainUi")->getChildByName("Btn_Change_Server"));
//        CC_BREAK_IF(pBtn_Server_Select==NULL);
//        pBtn_Server_Select->addTouchEventListener(this,toucheventselector(CNFLoginScene::OnBtnServerSelectCallBack));
        
       
          auto pBtn_Server_Select = dynamic_cast<Button*>(pLoginWidget->getChildByName("Normal_Login_panel")->getChildByName("MainUi")->getChildByName("Btn_Change_Server"));
        CC_BREAK_IF(pBtn_Server_Select==NULL);
        pBtn_Server_Select->addTouchEventListener(CC_CALLBACK_2(CNFLoginScene::OnBtnServerSelectCallBack, this));
        
        
        /************************************************************************/
        /*			背景图片                                                                     */
        /************************************************************************/
        ////创建背景图片
        //CCSprite * pServerSelectBg = CCSprite::create("ui/serverselect_bg.png");
        //CC_BREAK_IF(pServerSelectBg==NULL);
        //pServerSelectBg->setScaleX( (float)CCDirector::sharedDirector()->getWinSize().width/(float)pServerSelectBg->getContentSize().width );
        //pServerSelectBg->setPosition(SCREEN_CENTER);
        //addChild(pServerSelectBg,enZOrderBack);
        
//        auto * pServerSelectBg = Sprite::create("ui/serverselect_bg.png");
//        CC_BREAK_IF(pServerSelectBg==NULL);
//        pServerSelectBg->setScaleX( (float)CCDirector::getInstance()->getWinSize().width/(float)pServerSelectBg->getContentSize().width );
//        pServerSelectBg->setPosition(SCREEN_CENTER);
//        addChild(pServerSelectBg,enZOrderBack);
        
        
        
        
        ////创建logo图片
        //CCSprite * pName = CCSprite::create("ui/logo_bg.png");
        //CC_BREAK_IF(pName==NULL);
        //pName->setPosition(ccp(SCREEN_WIDTH*0.5f,350));
        //addChild(pName,enZOrderBack);
        
        ////创建服务器名称背景
        //CCScale9Sprite * pServerNameBg = CCScale9Sprite::create("ui/bg_1.png");
        //CC_BREAK_IF(pServerNameBg==NULL);
        //pServerNameBg->setContentSize(CCSizeMake(173,40));
        //pServerNameBg->setPosition(ccp(SCREEN_WIDTH*0.5f,220));
        //addChild(pServerNameBg,enZOrderBack);
        
        
        /************************************************************************/
        /*			创建按钮                                                                     */
        /************************************************************************/
        //CCMenu * pMenu = CCMenu::create();
        //CC_BREAK_IF(pMenu==NULL);
        //pMenu->setPosition(CCPointZero);
        //addChild(pMenu,enZOrderMid);
        
        
        
        ////选择服务器按钮
        //CCMenuItemSprite * pBtnServerSelect = CCMenuItemSprite::create(
        //	CCSprite::create("ui/btn_enter_n.png"),
        //	CCSprite::create("ui/btn_enter_p.png"),
        //	this,
        //	menu_selector(CNFLoginScene::OnBtnServerSelectCallBack));
        //CC_BREAK_IF(pBtnServerSelect==NULL);
        //pBtnServerSelect->setScaleY(0.8f);
        //pBtnServerSelect->setScaleX(0.2f);
        //pBtnServerSelect->setPosition(ccp(pServerNameBg->getPositionX() + 63  ,pServerNameBg->getPositionY()));
        //pMenu->addChild(pBtnServerSelect,enZOrderFront);
        
        
        
        
        /************************************************************************/
        /*					label                                                                    */
        /************************************************************************/
        //CCDictionary *pDicLang = CCDictionary::createWithContentsOfFile("ui_xml/serverselect_xml.xml");
        //CC_BREAK_IF(pDicLang==NULL);
        
        ////服务器label
        //CCString *pStrServer = dynamic_cast<CCString*>(pDicLang->objectForKey("server"));
        //CCLabelTTF * pLabelServer = CCLabelTTF::create(pStrServer->m_sString.c_str(),"Arial",20);
        //CC_BREAK_IF(pLabelServer==NULL);
        //pLabelServer->setPosition(ccp(pServerNameBg->getPositionX() - 120,pServerNameBg->getPositionY()));
        //pLabelServer->setColor(ccBLACK);
        //addChild(pLabelServer,enZOrderFront);
        
        ////服务器名称label
        //CCString *pStrServerName = dynamic_cast<CCString*>(pDicLang->objectForKey("server_name"));
        //char szName[NAME_LEN] = {0};
        //sprintf(szName,pStrServerName->m_sString.c_str(),m_nCurrentServerID);
        //CCLabelTTF * pLabelServerName = CCLabelTTF::create(szName,"Arial",20);
        //CC_BREAK_IF(pLabelServerName==NULL);
        //pLabelServerName->setPosition(ccp(pServerNameBg->getPositionX() - 20,pServerNameBg->getPositionY()));
        //addChild(pLabelServerName,enZOrderFront,enTagServerNameLabel);
        
        ////切换label
        //CCString *pStrChange = dynamic_cast<CCString*>(pDicLang->objectForKey("server_change"));
        //CCLabelTTF * pLabelChange = CCLabelTTF::create(pStrChange->m_sString.c_str(),"Arial",15);
        //CC_BREAK_IF(pLabelChange==NULL);
        //pLabelChange->setPosition(pBtnServerSelect->getPosition());
        //addChild(pLabelChange,enZOrderFront);
        
        
        
#if(NF_PLATFORM == NF_PLATFORM_NORMAL)//没接SDK版

//        //隐藏SDK登录模块
//        UILayout* pSdk_Login_Panel = dynamic_cast<UILayout*>(pLoginWidget->getChildByName("MainUi")->getChildByName("Sdk_Login_Panel"));
//        CC_BREAK_IF(pSdk_Login_Panel==NULL);
//        pSdk_Login_Panel->setEnabled(false);
//        pSdk_Login_Panel->setVisible(false);
//
        
        //隐藏SDK登录模块
        Widget* pSdk_Login_Panel = dynamic_cast<Widget*>(pLoginWidget->getChildByName("Normal_Login_panel")->getChildByName("MainUi")->getChildByName("Sdk_Login_Panel"));
        CC_BREAK_IF(pSdk_Login_Panel==NULL);
        pSdk_Login_Panel->setEnabled(false);
        pSdk_Login_Panel->setVisible(false);
        
        
//        
//        //显示正常登录模块
//        UILayout* pNormalLogin_Panel = dynamic_cast<UILayout*>(pLoginWidget->getChildByName("MainUi")->getChildByName("NormalLogin_Panel"));
//        CC_BREAK_IF(pNormalLogin_Panel==NULL);
//        pNormalLogin_Panel->setEnabled(true);
//        pNormalLogin_Panel->setVisible(true);
//
        
        Widget* pNormalLogin_Panel = dynamic_cast<Widget*>(pLoginWidget->getChildByName("Normal_Login_panel")->getChildByName("MainUi")->getChildByName("NormalLogin_Panel"));
        CC_BREAK_IF(pNormalLogin_Panel==NULL);
        pNormalLogin_Panel->setEnabled(true);
        pNormalLogin_Panel->setVisible(true);
        
        
        
//        //设置注册按钮回调
//        UIButton* pBtn_Register = dynamic_cast<UIButton*>(pLoginWidget->getChildByName("MainUi")->getChildByName("NormalLogin_Panel")->getChildByName("Btn_rg"));
//        CC_BREAK_IF(pBtn_Register==NULL);
//        pBtn_Register->addTouchEventListener(this,toucheventselector(CNFLoginScene::OnBtnSwitchToRegisterCallBack));
        
         //设置注册按钮回调
        auto pBtn_Register = dynamic_cast<Button*>(pLoginWidget->getChildByName("Normal_Login_panel")->getChildByName("MainUi")->getChildByName("NormalLogin_Panel")->getChildByName("Btn_rg"));
        CC_BREAK_IF(pBtn_Register==NULL);
        pBtn_Register->addTouchEventListener(CC_CALLBACK_2(CNFLoginScene::OnBtnSwitchToRegisterCallBack, this));
        
        
//        
//        //设置登录按钮回调
//        UIButton* pBtn_Login = dynamic_cast<UIButton*>(pLoginWidget->getChildByName("MainUi")->getChildByName("NormalLogin_Panel")->getChildByName("Btn_Log"));
//        CC_BREAK_IF(pBtn_Login==NULL);
//        pBtn_Login->addTouchEventListener(this,toucheventselector(CNFLoginScene::OnBtnLoginCallBack));
//
        
         //设置登录按钮回调
        auto pBtn_Login = dynamic_cast<Button*>(pLoginWidget->getChildByName("Normal_Login_panel")->getChildByName("MainUi")->getChildByName("NormalLogin_Panel")->getChildByName("Btn_Log"));
        CC_BREAK_IF(pBtn_Login==NULL);
        pBtn_Login->addTouchEventListener(CC_CALLBACK_2(CNFLoginScene::OnBtnLoginCallBack, this));
        
        
        
//        
//        //设置注册按钮回调
//        UITextField* pAccount_TextField = dynamic_cast<UITextField*>(pLoginWidget->getChildByName("MainUi")->getChildByName("NormalLogin_Panel")->getChildByName("Account_TextField"));
//        CC_BREAK_IF(pAccount_TextField==NULL);
//        pAccount_TextField->setTouchSize(CCSizeMake(161,30));
//        pAccount_TextField->didNotSelectSelf();

        
         //设置注册按钮回调
        TextField* pAccount_TextField = dynamic_cast<TextField*>(pLoginWidget->getChildByName("Normal_Login_panel")->getChildByName("MainUi")->getChildByName("NormalLogin_Panel")->getChildByName("Account_TextField"));
        CC_BREAK_IF(pAccount_TextField==NULL);
        pAccount_TextField->setTouchSize(Size(161,30));
        pAccount_TextField->didNotSelectSelf();
        
        
#else
        
        ////进入游戏按钮
        //CCMenuItemSprite * pBtnEnter = CCMenuItemSprite::create(
        //	CCSprite::create("ui/btn_enter_n.png"),
        //	CCSprite::create("ui/btn_enter_p.png"),
        //	this,
        //	menu_selector(CNFLoginScene::OnBtnEnterCallBack));
        //CC_BREAK_IF(pBtnEnter==NULL);
        //pBtnEnter->setPosition(ccp(SCREEN_WIDTH*0.5f,140));
        //pMenu->addChild(pBtnEnter,enZOrderFront);
        
        ////进入游戏label
        //CCString *pStrStart = dynamic_cast<CCString*>(pDicLang->objectForKey("start"));
        //CCLabelTTF * pLabelStart = CCLabelTTF::create(pStrStart->m_sString.c_str(),"Arial",20);
        //CC_BREAK_IF(pLabelStart==NULL);
        //pLabelStart->setPosition(pBtnEnter->getPosition());
        //addChild(pLabelStart,enZOrderFront);
        
        //设置进入游戏按钮回调
//        UIButton* pBtn_SDK_Start = dynamic_cast<UIButton*>(pLoginWidget->getChildByName("MainUi")->getChildByName("Sdk_Login_Panel")->getChildByName("Btn_SDK_Start"));
//        CC_BREAK_IF(pBtn_SDK_Start==NULL);
//        pBtn_SDK_Start->addTouchEventListener(this,toucheventselector(CNFLoginScene::OnBtnEnterCallBack));
        
        
        //设置进入游戏按钮回调
        auto pBtn_SDK_Start = dynamic_cast<Button*>(pLoginWidget->getChildByName("Normal_Login_panel")->getChildByName("MainUi")->getChildByName("Sdk_Login_Panel")->getChildByName("Btn_SDK_Start"));
        CC_BREAK_IF(pBtn_SDK_Start==NULL);
        pBtn_SDK_Start->addTouchEventListener(CC_CALLBACK_2(CNFLoginScene::OnBtnEnterCallBack, this));

#endif
        
        
        
        
//        schedule(schedule_selector(CNFLoginScene::OnBtnServerSelectCallBack2), 1.0f, kRepeatForever, 0);
        
        
        
        
        return ;
    } while (false);
    log("Fun CNFLoginScene::InitSceneUI Error!");
}


void CNFLoginScene::OnBtnServerSelectCallBack2(float dt)
{
    do
    {
        
        //创建切换服务器层
        CNFServerChangeLayer * pLayer = CNFServerChangeLayer::CreateLayer(m_nCurrentServerID,m_nServerTotalNum);
        CC_BREAK_IF(pLayer==NULL);
        pLayer->SetMsg(this);
        addChild(pLayer,enZOrderFront+100);
        
        
        
        
        
        //创建登录UI层
        Layer* pLoginUiLayer = dynamic_cast<Layer*>(getChildByTag(enTagStudioLoginLayer));
        CC_BREAK_IF(pLoginUiLayer==NULL);
        
        
        auto pNormalLogin = dynamic_cast<Node*>(pLoginUiLayer->getChildByName("LoginLayer"));
        CC_BREAK_IF(pNormalLogin==NULL);
        
        
        
        
        
        
        
        //显示正常登录模块
        auto pNormalLogin_Panel = dynamic_cast<Widget*>(pNormalLogin->getChildByName("Normal_Login_panel")->getChildByName("MainUi")->getChildByName("NormalLogin_Panel"));
        CC_BREAK_IF(pNormalLogin_Panel==NULL);
        pNormalLogin_Panel->setEnabled(false);
        pNormalLogin_Panel->setVisible(false);
        return ;
    } while (false);
    log("Fun CNFLoginScene::OnBtnServerSelectCallBack Error!");
}

void CNFLoginScene::OnBtnServerSelectCallBack(Ref *pSender, Widget::TouchEventType type)
{
    do
    {
        
        //        switch (type)
        //        {
        //            case TOUCH_EVENT_ENDED:
        //            {
        //
        //
        //
        //            }break;
        //            default:
        //                break;
        //        }
        
        
        
        
        switch (type)
        {
            case Widget::TouchEventType::ENDED:
            {
                //                //创建切换服务器层
                //                CNFServerChangeLayer * pLayer = CNFServerChangeLayer::CreateLayer(m_nCurrentServerID,m_nServerTotalNum);
                //                CC_BREAK_IF(pLayer==NULL);
                //                pLayer->SetMsg(this);
                //                addChild(pLayer,enZOrderFront+100);
                
                //                //创建登录UI层
                //                UILayer* pLoginUiLayer = dynamic_cast<UILayer*>(getChildByTag(enTagStudioLoginLayer));
                //                CC_BREAK_IF(pLoginUiLayer==NULL);
                //
                //                UILayout *pNormalLogin = dynamic_cast<UILayout*>(pLoginUiLayer->getWidgetByName("LoginLayer"));
                //                CC_BREAK_IF(pNormalLogin==NULL);
                //
                //                //显示正常登录模块
                //                UILayout* pNormalLogin_Panel = dynamic_cast<UILayout*>(pNormalLogin->getChildByName("MainUi")->getChildByName("NormalLogin_Panel"));
                //                CC_BREAK_IF(pNormalLogin_Panel==NULL);
                //                pNormalLogin_Panel->setEnabled(false);
                //                pNormalLogin_Panel->setVisible(false);
                //
                
                
                
                
                
                //创建切换服务器层
                 CNFServerChangeLayer * pLayer = CNFServerChangeLayer::CreateLayer(m_nCurrentServerID,m_nServerTotalNum);
                 CC_BREAK_IF(pLayer==NULL);
                 pLayer->SetMsg(this);
                 addChild(pLayer,enZOrderFront+100);
                
                
                
                
                
                //创建登录UI层
                Layer* pLoginUiLayer = dynamic_cast<Layer*>(getChildByTag(enTagStudioLoginLayer));
                CC_BREAK_IF(pLoginUiLayer==NULL);
                
                
                auto pNormalLogin = dynamic_cast<Node*>(pLoginUiLayer->getChildByName("LoginLayer"));
                CC_BREAK_IF(pNormalLogin==NULL);
                
                
                
                
                
                
                
                //显示正常登录模块
                auto pNormalLogin_Panel = dynamic_cast<Widget*>(pNormalLogin->getChildByName("Normal_Login_panel")->getChildByName("MainUi")->getChildByName("NormalLogin_Panel"));
                CC_BREAK_IF(pNormalLogin_Panel==NULL);
                pNormalLogin_Panel->setEnabled(false);
                pNormalLogin_Panel->setVisible(false);
                
                
              
             
            }
                break;
                
            default:
                break;
        }
        
        return ;
    } while (false);
    log("Fun CNFLoginScene::OnBtnServerSelectCallBack Error!");
    
    
    
    
}


//注册按钮的回调
void CNFLoginScene::OnBtnSwitchToRegisterCallBack( Ref* pSender, Widget::TouchEventType type )
{
    do
    {
        //        switch (type)
        //        {
        //            case TOUCH_EVENT_ENDED:
        //            {
        
        
        switch (type)
        {
            case Widget::TouchEventType::ENDED:
            {
                //创建登录UI层
//                UILayer* pRegisterUiLayer = UILayer::create();
//                CC_BREAK_IF(pRegisterUiLayer==NULL);
//                
//                UILayout *pRegisterWidget = dynamic_cast<UILayout*>(GUIReader::shareReader()->widgetFromJsonFile("NormalRegister.json"));
//                CC_BREAK_IF(pRegisterWidget==NULL);
//                pRegisterUiLayer->addWidget(pRegisterWidget);
//                pRegisterWidget->setName("RegistLayer");
//                pRegisterWidget->setSize(getContentSize());
//                
//                
//                //设置返回登录按钮回调
//                UIButton* pBtn_Back = dynamic_cast<UIButton*>(pRegisterWidget->getChildByName("MainUi")->getChildByName("Btn_Return"));
//                CC_BREAK_IF(pBtn_Back==NULL);
//                pBtn_Back->addTouchEventListener(this,toucheventselector(CNFLoginScene::OnBackToLoginCallBack));
//                
//                //注册按钮回调
//                UIButton* pBtn_rg = dynamic_cast<UIButton*>(pRegisterWidget->getChildByName("MainUi")->getChildByName("NormalRegister_Panel")->getChildByName("Btn_rg"));
//                CC_BREAK_IF(pBtn_rg==NULL);
//                pBtn_rg->addTouchEventListener(this,toucheventselector(CNFLoginScene::OnBtnRegisterCallBack));
//                
//                addChild(pRegisterUiLayer,enZOrderBack,enTagStudioRegisterLayer);
                
                
        

                
               
                
            }break;
            default:
                break;
        }
        
        return ;
    } while (false);
    log("Fun CNFLoginScene::OnBtnRegisterCallBack Error!");
}


//登录按钮的回调
void CNFLoginScene::OnBtnLoginCallBack( Ref *pSender, Widget::TouchEventType type )
{
    do
    {
//        switch (type)
//        {
//            case TOUCH_EVENT_ENDED:
//            {
        
        switch (type)
        {
            case Widget::TouchEventType::ENDED:
            {
       
                //读取角色信息
                CNFServerRoleSelectInfoVec RoleSelectInfoVec;
                CNFServerDataManager::SharedData()->GetRoleSelectInfo(RoleSelectInfoVec);
                CNFServerRoleSelectInfoVec::iterator itRole=RoleSelectInfoVec.begin();

                
                for (;itRole!=RoleSelectInfoVec.end();itRole++)
                {
                    if (itRole->nState>=0)
                    {
//                        //人物选择场景
//                        CCScene * pScene = CNFRoleSelectLayer::scene();
//                        CC_BREAK_IF(pScene==NULL);
//                        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.f,pScene));
//                        
                        return;
                    }
                }
//
//                
//                
//                
//                
//                
//                //人物选择场景
//                CCScene * pScene = CNFTeamCreateLayer::scene();
//                CC_BREAK_IF(pScene==NULL);
//                CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.f,pScene));
                
            }break;
            default:
                break;
        }
        
        return ;
    } while (false);
    log("Fun CNFLoginScene::OnBtnLoginCallBack Error!");
}

//进入游戏按钮回调
void CNFLoginScene::OnBtnEnterCallBack( Ref* pSender, Widget::TouchEventType type)
{
    do
    {
        
//        
//        switch (type)
//        {
//            case TOUCH_EVENT_ENDED:
//            {

        switch (type)
        {
            case Widget::TouchEventType::ENDED:
            {
                
                ////人物选择场景
                //CCScene * pScene = CNFRoleSelectLayer::scene();
                //CC_BREAK_IF(pScene==NULL);
                //CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.f,pScene));
                
                //人物选择场景
//                CCScene * pScene = CNFTeamCreateLayer::scene();
//                CC_BREAK_IF(pScene==NULL);
//                CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.f,pScene));
            }break;
            default:
                break;
        }
        
        
        return ;
    } while (false);
    log("Fun CNFLoginScene::OnBtnEnterCallBack Error!");
}
