//
//  NFServerChangeScrollLayer.cpp
//  demo
//
//  Created by 瑛峰 on 14/12/5.
//
//

#include "NFServerChangeScrollLayer.h"

#define _ONE_PAGE_SERVER_NUM_	12		//每一页所拥有的服务器的个数
#define _X_START_POS_	78				//x轴初始坐标
#define _PAGE_WIDTH_	564				//页面宽度
#define _PAGE_HEIGHT_	285				//页面高度

/************************************************************************/
/*				滑动层                                                  */
/************************************************************************/
CNFServerChangeScrollLayer* CNFServerChangeScrollLayer::CreateLayer(int nItemNum)
{
    CNFServerChangeScrollLayer *pRet = new CNFServerChangeScrollLayer();
    if (pRet && pRet->InitLayer(nItemNum))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}


bool CNFServerChangeScrollLayer::InitLayer(int nItemNum)
{
    do
    {
        //初始化父类
        CC_BREAK_IF(CCLayerColor::initWithColor(Color4B(0,0,0,0))==false);
        
        
        //版本变化
        //独占触屏注册值小于-128才能屏蔽Menu(Menu默认是-128)
//        CCDirector::getInstance()->getTouchDispatcher()->addTargetedDelegate(this, -129, true);
        
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        
        listener->onTouchBegan = CC_CALLBACK_2(CNFServerChangeScrollLayer::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(CNFServerChangeScrollLayer::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(CNFServerChangeScrollLayer::onTouchEnded, this);
        listener->onTouchEnded = CC_CALLBACK_2(CNFServerChangeScrollLayer::onTouchCancelled, this);
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        
        
//        setTouchEnabled(true);
        
        
        //初始x轴坐标
        m_fStartNodePosX = _X_START_POS_ + _NF_SCREEN_WIDTH_DIS_;
        
        ;		//页面数量
        int nPageNum = nItemNum%_ONE_PAGE_SERVER_NUM_ > 0 ? nItemNum/_ONE_PAGE_SERVER_NUM_+1 : nItemNum/_ONE_PAGE_SERVER_NUM_;
        
        //每一页宽度
        m_fPageWidth = _PAGE_WIDTH_;
        
        //页面高度
        float	fPageHeight = _PAGE_HEIGHT_;
        
        //x轴最小坐标
        m_fEndLayerPos = m_fPageWidth*(1-nPageNum);
        
        //x，y轴之间的间隔
        float fItemDisX = 11;
        float fItemDisY = 20;
        
        
        /************************************************************************/
        /*			创建按钮 
         
         
         */
        /************************************************************************/
        
//        版本变化
//        CCDictionary *pDicLang = CCDictionary::createWithContentsOfFile("ui_xml/serverselect_xml.xml");
//        CC_BREAK_IF(pDicLang==NULL);
        
        ValueMap pDicLang = FileUtils::getInstance()->getValueMapFromFile("ui_xml/serverselect_xml.xml");
         
        
        
        
        
        Menu * pMenu = Menu::create();
        CC_BREAK_IF(pMenu==NULL);
        pMenu->setPosition(Vec2::ZERO);
        addChild(pMenu,enZOrderFront,enTagMenu);
        
        //创建数组
        Ref *pObj = NULL;
        for (int k=1;k<=nItemNum;k++)
        {
            int i = k%_ONE_PAGE_SERVER_NUM_ > 0 ? k%_ONE_PAGE_SERVER_NUM_ : _ONE_PAGE_SERVER_NUM_;			//页面内ITem的ID：1~12
            int j = k%_ONE_PAGE_SERVER_NUM_ > 0 ? k/_ONE_PAGE_SERVER_NUM_+1 : k/_ONE_PAGE_SERVER_NUM_;		//当前页面ID
            
            int nCrossNum = i%3 == 0 ? 3 : i%3;				//横排
            int nVerticalNum = i%3 > 0 ? i/3+1 : i/3;		//竖排
            

            
            //创建按钮
            auto pBtn = MenuItemSprite::create(Sprite::create("ui/btn_enter_n.png"), Sprite::create("ui/btn_enter_p.png"), Sprite::create("ui/btn_enter_n.png"), CC_CALLBACK_1(CNFServerChangeScrollLayer::OnBtnCallBack, this) );
            CC_BREAK_IF(pBtn==NULL);
            pBtn->setPosition(Vec2( fItemDisX+ (nCrossNum-1)*(pBtn->getContentSize().width+fItemDisX) + m_fStartNodePosX + pBtn->getContentSize().width*0.5f + (j-1)*m_fPageWidth , fPageHeight-nVerticalNum*(pBtn->getContentSize().height+fItemDisY) + fItemDisY ));
            pMenu->addChild(pBtn,enZOrderFront,enTagBtn+k);
            
            //服务器名称label
//            std::string* 注意这里没有“*” pStrServerName = pDicLang.at("server_name").asString();
            std::string pStrServerName = pDicLang.at("server_name").asString();
            
            char szName[NAME_LEN] = {0};
            sprintf(szName,pStrServerName.c_str(),k);
            
            //版本变化
//            CCLabelTTF * pLabelServerName = CCLabelTTF::create(szName,"Arial",20);
//            CC_BREAK_IF(pLabelServerName==NULL);
            
            Label * pLabelServerName = Label::createWithSystemFont(szName, "Arial", 20);
            CC_BREAK_IF(pLabelServerName==NULL);
            
            pLabelServerName->setPosition(pBtn->getPosition());
            addChild(pLabelServerName,enZOrderFront);
            
        }
        
        
        //显示区域
        m_DisPlayRect = Rect(m_fStartNodePosX ,10 ,m_fPageWidth,fPageHeight);
        
        m_bTouching = false;
        m_bIsTouchBtn = false;
        
        
//        schedule(schedule_selector(CNFServerChangeScrollLayer::OnBtnCallBack2), 1.0f, kRepeatForever, 0);
        
        return true;
    } while (false);
    log("Fun CQXPVEItemScrollLayer::initWithNodes Error!");
    
    
    return false;
    
}

//触摸：开始
bool CNFServerChangeScrollLayer::onTouchBegan(Touch *pTouch, Event *pEvent)
{
    Vec2 ptTouchPoint =pTouch->getLocation();

    //设置初始触摸点
    m_fTouchPassPosX = ptTouchPoint.x;
    m_fTouchBeginPosX = ptTouchPoint.x;

    //判断是否触摸到裁切区域内
    if(m_DisPlayRect.containsPoint(ptTouchPoint))
    {
        m_bTouching = true;

        //判断是否触摸到按钮
       
//        Menu *pMenu = dynamic_cast<Menu*>(getChildByTag(enTagMenu));
         auto pMenu = static_cast<Menu*>(getChildByTag(enTagMenu));
        
        Vector<Node*> pChildren = pMenu->getChildren();
        
        if(pMenu!=NULL)
        {
            
            int i=0;
            for(const auto &pItem : pChildren) {

                
                auto pBtn= static_cast<MenuItemSprite*>(pItem);
                if(pBtn!=NULL)
                {
                    Vec2 local = pBtn->convertToNodeSpace(pTouch->getLocation());
                    Rect r = pBtn->rect();
                    r.origin = Vec2::ZERO;
                    if (r.containsPoint(local))
                    {
                        pMenu->onTouchBegan(pTouch,pEvent);
                        m_bIsTouchBtn=true;
                    }
                }
                i++;
            }
           

        }
        
        
        return true;
    }
    
    return false;
}


//触摸：移动
void CNFServerChangeScrollLayer::onTouchMoved(Touch *pTouch, Event *pEvent)
{
    if(m_bTouching==false)return;

    Vec2 ptTouchPoint =pTouch->getLocation();
    Vec2 pNewPos=getPosition();

    //移动层
    pNewPos.x+=ptTouchPoint.x-m_fTouchPassPosX;
    this->setPosition(pNewPos);

    //重置初始点
    m_fTouchPassPosX=ptTouchPoint.x;
    
    //若触摸到按钮
    if (m_bIsTouchBtn==true)
    {
//        CCMenu *pMenu = dynamic_cast<CCMenu*>(getChildByTag(enTagMenu));
         auto pMenu = static_cast<Menu*>(getChildByTag(enTagMenu));
        if (pMenu!=NULL)
        {
            pMenu->onTouchCancelled(pTouch,pEvent);
            m_bIsTouchBtn = false;
        }
    }
}



//触摸：结束
void CNFServerChangeScrollLayer::onTouchEnded(Touch *pTouch, Event *pEvent)
{
    if(m_bTouching==false)return;

    m_bTouching = false;
    
    Vec2 ptTouchPoint =pTouch->getLocation();
    Vec2 ptMyPos = getPosition();

    
    //判断移到哪一页
    float fDisX = ptTouchPoint.x - m_fTouchBeginPosX;

    //判定滑动
    if ( _NF_ABS(fDisX)>= 20)
    {
        //向左滑动
        if (fDisX < 0)
        {
            //若未过界
            if (getPositionX() > m_fEndLayerPos)
            {
                int fLen = (int)getPositionX()%(int)m_fPageWidth;
                ptMyPos.x = (int)( getPositionX() - fLen - m_fPageWidth);
                Action *pMoveTo=MoveTo::create(0.3f,ptMyPos);
                runAction(pMoveTo);
            }
        }
        //向右滑
        if (fDisX > 0)
        {
            //若未过界
            if (getPositionX() < 0)
            {
                int fLen = (int)getPositionX()%(int)m_fPageWidth;
                ptMyPos.x = (int)( getPositionX() - fLen);
                Action *pMoveTo=MoveTo::create(0.3f,ptMyPos);
                runAction(pMoveTo);
            }
        }
    }

    //判断是否越界
    if (getPositionX()>0)
    {
        ptMyPos.x = 0;
        Action *pMoveTo=MoveTo::create(0.3f,ptMyPos);
        runAction(pMoveTo);
    }
    else if (getPositionX()<m_fEndLayerPos)
    {
        ptMyPos.x = m_fEndLayerPos<0?m_fEndLayerPos:0;
        Action *pMoveTo=MoveTo::create(0.3f,ptMyPos);
        runAction(pMoveTo);
    }

    //滑动层，当前坐标
    Vec2 LayerPos;
    LayerPos.x = getPositionX();
    LayerPos.y = getPositionY();

    //若触摸到按钮
    if (m_bIsTouchBtn==true)
    {
//        CCMenu *pMenu = dynamic_cast<CCMenu*>(getChildByTag(enTagMenu));
        auto pMenu = static_cast<Menu*>(getChildByTag(enTagMenu));
        if (pMenu!=NULL)
        {
            pMenu->onTouchEnded(pTouch,pEvent);
        }
        m_bIsTouchBtn = false;
    }
    
}

void CNFServerChangeScrollLayer::onTouchCancelled(Touch *pTouch, Event *pEvent)
{
    m_bTouching = false;
}

//裁切
void CNFServerChangeScrollLayer::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
    if (!_visible)
    {
        return;
    }
    
    uint32_t flags = processParentFlags(parentTransform, parentFlags);
    
    
    // IMPORTANT:
    // To ease the migration to v3.0, we still support the Mat4 stack,
    // but it is deprecated and your code should not rely on it
    Director* director = Director::getInstance();
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);
    
    bool visibleByCamera = isVisitableByVisitingCamera();
    
 
    
    
    glEnable(GL_SCISSOR_TEST);
    
    Size size=Director::getInstance()->getOpenGLView()->getFrameSize();
    
    float fScaleX=size.width/SCREEN_WIDTH;
    float fScaleY=size.height/SCREEN_HEIGHT;
    
    glScissor(m_DisPlayRect.origin.x*fScaleX,m_DisPlayRect.origin.y*fScaleY,m_DisPlayRect.size.width*fScaleX,m_DisPlayRect.size.height*fScaleY);
    
    
    
    int i = 0;
    
    if(!_children.empty())
    {
        sortAllChildren();
        // draw children zOrder < 0
        for( ; i < _children.size(); i++ )
        {
            auto node = _children.at(i);
            
            if ( node && node->getLocalZOrder() < 0 )
                node->visit(renderer, _modelViewTransform, flags);
            else
                break;
        }
        // self draw
        if (visibleByCamera)
            this->draw(renderer, _modelViewTransform, flags);
        
        for(auto it=_children.cbegin()+i; it != _children.cend(); ++it)
            (*it)->visit(renderer, _modelViewTransform, flags);
    }
    else if (visibleByCamera)
    {
        this->draw(renderer, _modelViewTransform, flags);
    }
    
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    
    glDisable(GL_SCISSOR_TEST);
    
   
}

void CNFServerChangeScrollLayer::OnBtnCallBack2(float df)
{
    do
    {
        int nTag = 105;
        
        //发消息：更改服务器
        tagServerSelect Info;
        Info.nServerID = nTag-100;
        
        //发消息，切换服务器
        SendMsg(enMsg_ServerSelect,&Info,sizeof(Info));
        
        //移除自身
        removeFromParentAndCleanup(true);
        
        return ;
    } while (false);
    log("Fun CNFServerSelectScrollLayer::OnBtnCallBack Error!");
}


//按钮回调
void CNFServerChangeScrollLayer::OnBtnCallBack( Ref* pObj )
{
    do
    {
        int nTag = (dynamic_cast<MenuItemSprite *>(pObj))->getTag();
        
        //发消息：更改服务器
        tagServerSelect Info;
        Info.nServerID = nTag-100;
        
        //发消息，切换服务器
        SendMsg(enMsg_ServerSelect,&Info,sizeof(Info));
        
        //移除自身
//        removeFromParentAndCleanup(true);  //这个出问题了
        
        return ;
    } while (false);
    log("Fun CNFServerSelectScrollLayer::OnBtnCallBack Error!");
}



void CNFServerChangeScrollLayer::onExit()
{
    //取消独占
//    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
//    setTouchEnabled(false);
    
    _eventDispatcher->removeEventListenersForTarget(this);
    Layer::onExit();
}

void CNFServerChangeScrollLayer::SetLeftMove()
{
    //若当前未触摸
    if (m_bTouching==false)
    {
        //若未过界
        if (getPositionX() > m_fEndLayerPos)
        {
            Vec2 ptMyPos;
            ptMyPos.x = (int)( getPositionX() - m_fPageWidth);
            Action *pMoveTo=MoveTo::create(0.3f,ptMyPos);
            runAction(pMoveTo);
        }
    }
}

void CNFServerChangeScrollLayer::SetRightMove()
{
    //若当前未触摸
    if (m_bTouching==false)
    {
        //若未过界
        if (getPositionX() < 0)
        {
            Vec2 ptMyPos;
            ptMyPos.x = (int)( getPositionX() + m_fPageWidth);
            Action *pMoveTo=MoveTo::create(0.3f,ptMyPos);
            runAction(pMoveTo);
        }
    }
}



