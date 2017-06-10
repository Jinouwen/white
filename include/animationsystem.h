#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

struct Animation
{
    unsigned int typeId;
    unsigned int frameNum;
    sf::Time nowElapsed;
    float TPF;//time per frame
    sf::Sprite sprite;
    sf::Texture texture;
    sf::IntRect nowRect;
    unsigned int width;
    unsigned int height;
    bool active;
    Animation():active(0)
    {
        texture.setRepeated(1);
        nowElapsed=sf::Time::Zero;
    }
};
class AnimationSystem:public sf::Drawable, public sf::Transformable
{
    public:
        AnimationSystem();
        virtual ~AnimationSystem() {}
        void update(sf::Time elapsed);
        void pushAnimationRequest(unsigned int typeId,sf::Vector2f pos);
    private:
        Animation temp;
        void test();
        void load(unsigned int typeId,std::string str,unsigned int frameNum,unsigned int width,unsigned int height,float TPF,float scale);

        Animation animations[20];
        Animation animationMould[10];
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates   states) const
        {
            states.transform *= getTransform();
            for(int i=0;i<20;++i)
            if(animations[i].active)
            {
                target.draw(animations[i].sprite,states);
            }
        }
};
AnimationSystem::AnimationSystem()
{
    load(0,"boom1.png",24,64,64,0.02,2);
    test();
}
void AnimationSystem::test()
{
}
void AnimationSystem::update(sf::Time elapsed)
{
    for(int i=0;i<20;++i)
    if(animations[i].active)
    {
        Animation &p(animations[i]);
        p.nowElapsed+=elapsed;
        unsigned int now=(p.nowElapsed.asSeconds()/p.TPF);
        if(now>=p.frameNum)
            p.active=0;
        p.sprite.setTextureRect(sf::IntRect(p.width*now,0,p.width,p.height));
    }

}
void AnimationSystem::load(unsigned int typeId,std::string str,unsigned int frameNum,unsigned int width,unsigned int height,float TPF,float scale)
{
    Animation &t=animationMould[typeId];
    t.typeId=typeId;
    t.texture.loadFromFile(str);
    t.TPF=TPF;
    t.sprite.setTexture(t.texture);
    t.width=width;
    t.height=height;
    t.sprite.setTextureRect(sf::IntRect(0,0,width,height));
    t.sprite.setOrigin(width/2,height/2);
    t.sprite.setScale(scale,scale);
    t.frameNum=frameNum;
    t.active=1;
}
void AnimationSystem::pushAnimationRequest(unsigned int typeId,sf::Vector2f pos)
{
    for(int i=0;i<20;++i)
    if(!animations[i].active)
    {
        Animation &now(animations[i]);
        now=animationMould[typeId];
        now.sprite.setPosition(pos);
        break;
    }
}
#endif // ANIMATIONSYSTEM_H
