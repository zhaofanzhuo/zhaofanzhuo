#include "HelloWorldScene.h"
//11·32人都是公开举报你1
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();//场景类
    auto layer = HelloWorld::create();
    scene->addChild(layer);//优先级0

    auto layer2=AlertLayer::create();
    scene->addChild(layer2);//优先级 0 先调用
    
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    _sprite=Sprite::create("CloseSelected.png");
    _sprite->setPosition(Vec2(100, 100));
    this->addChild(_sprite);
    
   //1,获取分发中心
    auto d=Director::getInstance()->getEventDispatcher();
    //2,创建监听器
    auto l=EventListenerTouchOneByOne::create();
    
    l->onTouchBegan=CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    l->onTouchMoved=CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    
    l->onTouchEnded=CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
   
    l->onTouchCancelled=CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
    
    //3注册
   // d->addEventListenerWithSceneGraphPriority(l, this);
    //默认注册 优先级为0 分发中心看：谁在上面就先分发给谁，先判断优先级，在判断谁在层内，谁在层外数字越小优先级越高                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             ，
    
    
    d->addEventListenerWithFixedPriority(l, -1);//修改优先级
    return true;
}

//这四个函数是単点触摸，第二个参数：
 bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)//手指进入屏幕的时候
{
    Vec2 v=touch->getLocation();//获取当前点击时的确切位置
    log("位置：%f,%f",v.x,v.y);
    Rect rect = _sprite->getBoundingBox();//获取精灵所在的矩形区域
    //rect.intersectsRect(const cocos2d::Rect &rect);//两个矩形区域是否相交
    
    if (rect.containsPoint(v)) {//判断矩形区域是否包含某个点
        return true;
    }
    log("HelloWorld手指进入屏幕的时候");
    return true;//false不处理， true：当前对象是否处理这个事件，
}
 void HelloWorld::onTouchMoved(Touch *touch, Event *unused_event)//手指在屏幕移动 多次
{
    Vec2 v=touch->getLocation();
    _sprite->setPosition(v);
    log("HelloWorld手指在屏幕移动 多次");
}
 void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event)//手指离开屏幕
{
    log("HelloWorld手指离开屏幕");
}
 void HelloWorld::onTouchCancelled(Touch *touch, Event *unused_event)//出问题的时候
{
    log("HelloWorld出问题的时候");
}
void HelloWorld::onExit()
{//删除注册
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);//通过对象删除
    //Director::getInstance()->getEventDispatcher()->removeAllEventListeners(l);//通过监听器删除
    //Director::getInstance()->getEventDispatcher()->removeAllEventListeners();//一定不能使用这个函数删除，否则菜单等都不能点击了
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
