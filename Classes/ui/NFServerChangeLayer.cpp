//
//  NFServerChangeLayer.cpp
//  demo
//
//  Created by 瑛峰 on 14/12/5.
//
//

#include "NFServerChangeLayer.h"
#include "NFServerChangeScrollLayer.h"




CNFServerChangeLayer * CNFServerChangeLayer::CreateLayer(int nCurrentServerID,int nServerTotalNum)
{
    CNFServerChangeLayer *pRet = new CNFServerChangeLayer();
    if (pRet && pRet->InitLayer(nCurrentServerID,nServerTotalNum))
    {
        pRet->autorelease();
        return pRet;
    }
    log("Fun CNFServerChangeLayer::CreateLayer Error!");
    delete pRet;
    pRet = NULL;
    return NULL;
}


bool CNFServerChangeLayer::InitLayer(int nCurrentServerID,int nServerTotalNum)
{
    do
    {
        //初始化父类
        CC_BREAK_IF(Layer::init()==false);
        
        m_nCurrentServerID = nCurrentServerID;
        
        /************************************************************************/
        /*			背景图片                                                                     */
        /************************************************************************/
        //创建背景
        Sprite * pBg = Sprite::create("ui/serverselect_bg.png");
        CC_BREAK_IF(pBg==NULL);
        pBg->setPosition(SCREEN_CENTER);
        pBg->setScaleX( (float)CCDirector::getInstance()->getWinSize().width/(float)pBg->getContentSize().width );
        addChild(pBg,enZOrderBack);
        
        //创建上次登录图片
        Sprite * pBg1 = Sprite::create("ui/serverselect_title_1.png");
        CC_BREAK_IF(pBg1==NULL);
        pBg1->setPosition(Vec2(150+_NF_SCREEN_WIDTH_DIS_,420));
        addChild(pBg1,enZOrderBack);
        
        //创建全服务器图片
        Sprite * pBg2 = Sprite::create("ui/serverselect_title_2.png");
        CC_BREAK_IF(pBg2==NULL);
        pBg2->setPosition(Vec2(160+_NF_SCREEN_WIDTH_DIS_,300));
        addChild(pBg2,enZOrderBack);
        
        /************************************************************************/
        /*			创建按钮                                                                     */
        /************************************************************************/
        Menu * pMenu = Menu::create();
        CC_BREAK_IF(pMenu==NULL);
        pMenu->setPosition(Vec2::ZERO);
        addChild(pMenu,enZOrderFront);
        
        //创建返回按钮
        //CCMenuItemSprite * pBtnBack = CCMenuItemSprite::create(
        //	CCSprite::create("ui/serverselect_btn_back_n.png"),
        //	CCSprite::create("ui/serverselect_btn_back_p.png"),
        //	this,
        //	menu_selector(CNFServerChangeLayer::OnBtnCallBack));
        //CC_BREAK_IF(pBtnBack==NULL);
        //pBtnBack->setPosition(ccp(SCREEN_WIDTH - 30,SCREEN_HEIGHT-30));
        //pMenu->addChild(pBtnBack,enZOrderFront);
        
        //创建当前服务器按钮 版本变化
//        MenuItemSprite * pBtnCurrentServer = MenuItemSprite::create(
//                                                                        Sprite::create("ui/btn_enter_n.png"),
//                                                                        Sprite::create("ui/btn_enter_p.png"),
//                                                                        this,
//                                                                        menu_selector(CNFServerChangeLayer::OnBtnCallBack));
        
        //创建当前服务器按钮
         auto pBtnCurrentServer = MenuItemSprite::create(Sprite::create("ui/btn_enter_n.png"), Sprite::create("ui/btn_enter_p.png"), Sprite::create("ui/btn_enter_n.png"), CC_CALLBACK_1(CNFServerChangeLayer::OnBtnCallBack, this) );
        CC_BREAK_IF(pBtnCurrentServer==NULL);
        pBtnCurrentServer->setPosition(Vec2(190+_NF_SCREEN_WIDTH_DIS_,380));
        pMenu->addChild(pBtnCurrentServer,enZOrderFront);
        
      
        
        //创建左侧按钮
        auto pBtnLeft = MenuItemSprite::create(Sprite::create("ui/serverselect_btn_back_n.png"), Sprite::create("ui/serverselect_btn_back_p.png"), Sprite::create("ui/serverselect_btn_back_n.png"), CC_CALLBACK_1(CNFServerChangeLayer::OnBtnLeftMove, this) );
        CC_BREAK_IF(pBtnLeft==NULL);
        pBtnLeft->setPosition(Vec2(50+_NF_SCREEN_WIDTH_DIS_,150));
        pMenu->addChild(pBtnLeft,enZOrderFront);
        

       //创建右侧按钮
        auto pBtnRight = MenuItemSprite::create(Sprite::create("ui/serverselect_btn_back_n.png"), Sprite::create("ui/serverselect_btn_back_p.png"), Sprite::create("ui/serverselect_btn_back_n.png"), CC_CALLBACK_1(CNFServerChangeLayer::OnBtnRightMove, this) );
        CC_BREAK_IF(pBtnRight==NULL);
        pBtnRight->setPosition(Vec2(SCREEN_WIDTH-_NF_SCREEN_WIDTH_DIS_-50,150));
        pMenu->addChild(pBtnRight,enZOrderFront);
        
        /************************************************************************/
        /*				创建label    
         
         */
        /************************************************************************/
//        CCDictionary *pDicLang = CCDictionary::createWithContentsOfFile("ui_xml/serverselect_xml.xml");
//        CC_BREAK_IF(pDicLang==NULL);
//        
//        //服务器名称label
//        CCString *pStrServerName = dynamic_cast<CCString*>(pDicLang->objectForKey("server_name"));
//        char szName[NAME_LEN] = {0};
//        sprintf(szName,pStrServerName->m_sString.c_str(),nCurrentServerID);
//        CCLabelTTF * pLabelServerName = CCLabelTTF::create(szName,"Arial",20);
//        CC_BREAK_IF(pLabelServerName==NULL);
//        pLabelServerName->setPosition(pBtnCurrentServer->getPosition());
//        addChild(pLabelServerName,enZOrderFront);
        
        
        ValueMap pDicLang = FileUtils::getInstance()->getValueMapFromFile("ui_xml/serverselect_xml.xml");
        std::string pStrServerName = pDicLang.at("server_name").asString();
        char szName[NAME_LEN] = {0};
        sprintf(szName,pStrServerName.c_str(),nCurrentServerID);
        
        Label * pLabelServerName = Label::createWithSystemFont(szName, "Arial", 20);
        CC_BREAK_IF(pLabelServerName==NULL);
        pLabelServerName->setPosition(pBtnCurrentServer->getPosition());
        addChild(pLabelServerName,enZOrderFront);
        
        /************************************************************************/
        /*					创建滑动层                                                                     */
        /************************************************************************/
        //创建滑动层
        CNFServerChangeScrollLayer * pLayer = CNFServerChangeScrollLayer::CreateLayer(nServerTotalNum);	//Item数组，x轴起始位置
        CC_BREAK_IF(pLayer==NULL);
        pLayer->SetMsg(this);
        addChild(pLayer,enZOrderFront,enTagScrollLayer);
        
        
        return true;
    } while (false);
    log("Fun CNFServerChangeLayer::init Error!");
    return false;
}


//消息接收
void CNFServerChangeLayer::RecMsg( int nMsgID,void* pInfo,int nSize )
{
    switch (nMsgID)
    {
        case enMsg_ServerSelect:
        {
            tagServerSelect * pCmd = (tagServerSelect *)pInfo;
            
            //发消息：更改服务器
            tagServerSelect Info;
            Info.nServerID = pCmd->nServerID;
            
            SendMsg(enMsg_ServerSelect,&Info,sizeof(Info));
            
            //移除自身
        
            removeFromParentAndCleanup(true);
            
        }break;
    }
}


//按钮回调：返回
void CNFServerChangeLayer::OnBtnCallBack( Ref* pObj )
{
    //发消息：更改服务器
    tagServerSelect Info;
    Info.nServerID = m_nCurrentServerID;
    SendMsg(enMsg_ServerSelect,&Info,sizeof(Info));
    
    //移除自身
    removeFromParentAndCleanup(true);
}

//按钮回调：向左滑动
void CNFServerChangeLayer::OnBtnLeftMove( Ref* pObj )
{
    do
    {
        //滑动层
        CNFServerChangeScrollLayer * pLayer = dynamic_cast<CNFServerChangeScrollLayer *>(getChildByTag(enTagScrollLayer));
        CC_BREAK_IF(pLayer==NULL);
        pLayer->SetRightMove();
        
        return ;
    } while (false);
    log("Fun CNFServerChangeLayer::OnBtnLeftMove Error!");
}

//按钮回调：向右滑动
void CNFServerChangeLayer::OnBtnRightMove( Ref* pObj )
{
    do
    {
        //滑动层
        CNFServerChangeScrollLayer * pLayer = dynamic_cast<CNFServerChangeScrollLayer *>(getChildByTag(enTagScrollLayer));
        CC_BREAK_IF(pLayer==NULL);
        pLayer->SetLeftMove();
        
        return ;
    } while (false);
    log("Fun CNFServerChangeLayer::OnBtnRightMove Error!");
}


