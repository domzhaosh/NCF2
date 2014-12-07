//
//  NFServerChangeScrollLayer.h
//  demo
//
//  Created by 瑛峰 on 14/12/5.
//
//

#ifndef _HM_SCROLL_LAYER_HEAD_
#define _HM_SCROLL_LAYER_HEAD_

#include "../publicdef/PublicDef.h"


/************************************************************************/
/*				服务器选择界面，滑动层                                                                     */
/************************************************************************/
class CNFServerChangeScrollLayer : public LayerColor ,public CMsgSender
{
protected:
    // 标签
    enum
    {
        enTagMenu = 1,
        enTagBtn = 100,
    };
    
    float			m_fTouchPassPosX;			//上一次计算触摸时，手指滑过的位置
    float			m_fTouchBeginPosX;			//用户触摸最初始的位置
    bool			m_bTouching;				//是否取消了触摸(保证不会重复调用TouchEnd)
    bool			m_bIsTouchBtn;				//是否触摸到按钮
    
    float			m_fPageWidth;				//每一页的宽度
    float			m_fEndLayerPos;				//结束边界的位置
    float			m_fStartNodePosX;			//初始节点x轴位置
    
    Rect			m_DisPlayRect;				//显示区域
    
public:

    static CNFServerChangeScrollLayer* CreateLayer(int nItemNum);
    
//    CREATE_FUNC(CNFServerChangeScrollLayer);
    //向左滑
    void SetLeftMove();
    
    //向右滑
    void SetRightMove();
    
protected:
    bool InitLayer(int nItemNum);
    
    //设置裁剪区域
//    void visit();
    void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags);
    
    //触摸函数
//    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    //触摸 版本变化
    virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
    virtual void onTouchCancelled(Touch *pTouch, Event *pEvent);
    
    //按钮回调
    void OnBtnCallBack(Ref* pObj);
    
    void OnBtnCallBack2(float dt);
    
    virtual void onExit();
    
};


#endif /* defined(_HM_SCROLL_LAYER_HEAD_) */
