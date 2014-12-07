//
//  NFLoadingLayer.h
//  NCF
//
//  Created by 瑛峰 on 14/11/12.
//
//

#ifndef _NF_LOADING_SCENE_HEAD_
#define _NF_LOADING_SCENE_HEAD_

#include "PublicDef.h"
//#include "cocos2d.h"
//using namespace cocos2d;

/************************************************************************/
/*			Loading层                                                                    */
/************************************************************************/
class CNFLoadingLayer : public LayerColor
{
protected:
    //标签
    enum
    {
        enTagPro = 1,
        enTagLight,
        enTagLabel,
    };
    
public:
//    static CNFLoadingLayer * CreateLayer();
    
    CREATE_FUNC(CNFLoadingLayer);
    
    //设置进度条
    void SetPro(float fRate);
    
protected:
    virtual bool init();
    
    //触摸
    virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
    
    virtual void onExit();
    
};

#endif /* defined(_NF_LOADING_SCENE_HEAD_) */
