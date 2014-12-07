//
//  NFLoadingLayer.cpp
//  NCF
//
//  Created by 瑛峰 on 14/11/12.
//
//

#include "NFLoadingLayer.h"


bool CNFLoadingLayer::init()
{
    do
    {
        
        //版本修改的
        //初始化父类
//        CC_BREAK_IF(LayerColor::initWithColor(ccc4(0,0,0,255))==false);
        
        //这个一定要由，否则允许有问题
        CC_BREAK_IF(LayerColor::initWithColor(Color4B(0,0,0,255))==false);
        
        
        
        
        
        //版本修改的
        
        
        //独占触屏
//        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -10000, true);

//         Register Touch Event
        
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        
        listener->onTouchBegan = CC_CALLBACK_2(CNFLoadingLayer::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(CNFLoadingLayer::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(CNFLoadingLayer::onTouchEnded, this);
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        
//        setTouchEnabled(true);

        
        
        
        
        /************************************************************************/
        /*				背景图片                                                                     */
        /************************************************************************/
        //创建人物图片
        Sprite * pPersonBg = Sprite::create("ui/loading_bg.png");
        CC_BREAK_IF(pPersonBg==NULL);
        pPersonBg->setPosition(SCREEN_CENTER);
        addChild(pPersonBg,enZOrderBack);

        //创建logo图片
        Sprite * pLogo = Sprite::create("ui/logo_bg.png");
        CC_BREAK_IF(pLogo==NULL);
        pLogo->setScale(0.95f);
        pLogo->setPosition(Vec2(SCREEN_WIDTH*0.5f,410));
        addChild(pLogo,enZOrderBack);
        
        
        /************************************************************************/
        /*				进度条                                                                     */
        /************************************************************************/
        //创建加载进度条背景
        Sprite * pProBg = Sprite::create("ui/loading_progress_bg.png");
        CC_BREAK_IF(pProBg==NULL);
        pProBg->setPosition(Vec2(SCREEN_WIDTH*0.5f,100));
        addChild(pProBg,enZOrderMid);
        
        //创建加载进度条
        ProgressTimer *pProLoadRec = ProgressTimer::create(Sprite::create("ui/loading_progress_bar.png"));
        CC_BREAK_IF(pProLoadRec==NULL);
        pProLoadRec->setPosition(pProBg->getPosition());
//        pProLoadRec->setType(kCCProgressTimerTypeBar);	//设置进度条类型
        
        pProLoadRec->setType(ProgressTimer::Type::BAR);
        pProLoadRec->setMidpoint(Vec2(0,0));				//靠左
        pProLoadRec->setBarChangeRate(Vec2(1, 0));		//Y轴不缩放
        pProLoadRec->setPercentage(0.f);
        addChild(pProLoadRec,enZOrderMid+1,enTagPro);
        
        //创建光点
        Sprite * pLight = Sprite::create("ui/loading_progress_light.png");
        CC_BREAK_IF(pLight==NULL);
        addChild(pLight,enZOrderFront,enTagLight);
        pLight->setPosition( Vec2( pProLoadRec->getPositionX()-pProLoadRec->getContentSize().width*0.5f, pProLoadRec->getPositionY() ) );
        
        
        /************************************************************************/
        /*					label                                                                    */
        /************************************************************************/
//       版本变化
//        CCDictionary *pDicLang = CCDictionary::createWithContentsOfFile("ui_xml/loading_xml.xml");
//        CC_BREAK_IF(pDicLang==NULL);
//        
//        //加载信息label
//        CCString *pStrLoading = dynamic_cast<CCString*>(pDicLang->objectForKey("loading_now"));
//        CCLabelTTF * pLabelLoading = CCLabelTTF::create(pStrLoading->m_sString.c_str(),"Arial",10);
//        CC_BREAK_IF(pLabelLoading==NULL);
//        pLabelLoading->setPosition(pProLoadRec->getPosition());
//        addChild(pLabelLoading,enZOrderMid+2,enTagLabel);
        
        
        ValueMap dict = FileUtils::getInstance()->getValueMapFromFile("ui_xml/loading_xml.xml");
        std::string pStrLoading = dict.at("loading_now").asString();
//        LabelTTF * pLabelLoading = LabelTTF::create(pStrLoading,"Arial",10);
        Label * pLabelLoading = Label::createWithSystemFont(pStrLoading, "Arial", 10);
//        Label * pLabelLoading = Label::createWithTTF(pStrLoading, "Arial", 10);
        CC_BREAK_IF(pLabelLoading==NULL);
        pLabelLoading->setPosition(pProLoadRec->getPosition());
        addChild(pLabelLoading,enZOrderMid+2,enTagLabel);
        
        
 
        
         return true;
    } while (false);
    log("Fun CNFLoadingLayer::init Error!");
    return false;
}


void CNFLoadingLayer::SetPro( float fRate )
{
    do
    {
        //同步进度条
        ProgressTimer *pProLoadRec = dynamic_cast<ProgressTimer *>(getChildByTag(enTagPro));
        if (pProLoadRec!=NULL)
            pProLoadRec->setPercentage(fRate*100);
        
        //同步光点
        Sprite * pLight = dynamic_cast<Sprite *>(getChildByTag(enTagLight));
        if (pLight!=NULL)
            pLight->setPositionX( pProLoadRec->getPositionX() + pProLoadRec->getContentSize().width*(fRate-0.5f) );
        
        //若加载完成
        if (fRate >= 1)
        {
          
        ValueMap dict = FileUtils::getInstance()->getValueMapFromFile("ui_xml/loading_xml.xml");
//            CC_BREAK_IF(dict==NULL);
            std::string pStrLoading = dict.at("loading_end").asString();
            Label * pLabelLoading = dynamic_cast<Label *>(getChildByTag(enTagLabel));
            CC_BREAK_IF(pLabelLoading==NULL);
            pLabelLoading->setString(pStrLoading);
            
            
            
        }
        
        return ;
    } while (false);
    log("Fun CNFLoadingLayer::SetPro Error!");
}



bool CNFLoadingLayer::onTouchBegan(Touch* touch, Event* event)
{
    CCLOG("CNFLoadingLayer::onTouchBegan id = %d, x = %f, y = %f", touch->getID(), touch->getLocation().x, touch->getLocation().y);
    
//    if ( !containsTouchLocation(touch) ) return false;
   
    return true;
}

void CNFLoadingLayer::onTouchMoved(Touch* touch, Event* event)
{
  
    CCLOG("CNFLoadingLayer::onTouchMoved id = %d, x = %f, y = %f", touch->getID(), touch->getLocation().x, touch->getLocation().y);
    
    
//    auto touchPoint = touch->getLocation();
//    
//    setPosition( Vec2(touchPoint.x, getPosition().y) );
    
    return;
    
}



void CNFLoadingLayer::onTouchEnded(Touch* touch, Event* event)
{
    return;
}


void CNFLoadingLayer::onExit()
{
    //取消独占
//    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
//    setTouchEnabled(false);
    
    _eventDispatcher->removeEventListenersForTarget(this);

    LayerColor::onExit();
}