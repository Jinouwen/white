#ifndef FIRESYSTEM_H
#define FIRESYSTEM_H

#include <SFML/Graphics.hpp>
struct Shell
{
    sf::Vector2f shellTransform;
    sf::Vector2f velocity;
    sf::Time elapsed;
    sf::RenderStates states;
    bool active;
    unsigned int typeId;
    Shell(sf::Vector2f pos,sf::Vector2f vel,unsigned int typeId0)
        :shellTransform(sf::Vector2f(0,0)),velocity(vel),active(1),typeId(typeId0)
    {
        states.transform.translate(pos);
    }
    Shell():active(0){}
    void move(sf::Vector2f pos)
    {
        states.transform.translate(pos);
    }
};

////////////////////////////////////////////////////////////////////////////
class FireSystem:public sf::Drawable, public sf::Transformable
{
    public:
        FireSystem(unsigned int count0):count(count0),shells(count0)
        {
            loadShell(0,sf::IntRect(0, 0, 6, 12),1300,sf::Vector2f(3.0,12.0),sf::seconds(0.10),3);
            loadShell(1,sf::IntRect(7, 0, 8, 8),700,sf::Vector2f(4.0,4.0),sf::seconds(0.6),8);
            loadShell(2,sf::IntRect(16, 0, 11, 11),500,sf::Vector2f(5.0,5.0),sf::seconds(0.05),4);
        }
        virtual ~FireSystem() {}
        void pushFireRequest(Shell fireRequest);
        void update(sf::Time elapsed);
        bool checkFire(unsigned int typeId);
        unsigned int getCount(){return count;}
    private:
        unsigned int count;
        std::vector<Shell> shells;
        sf::Texture shellTexture[20];
        float typeVelocity[20];
        sf::Time firePause[20];
        sf::Clock fireClock[20];
        sf::Time fireElapsed[20];
        sf::Sprite shellSprite[20];
        float shellSize[20];
        void loadShell(unsigned int typeId,sf::IntRect rec,float vel,sf::Vector2f opos,sf::Time pauseTime,float sizeChange);
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates   states) const
        {
            states.transform *= getTransform();
            for(unsigned int i=0;i<shells.size();++i)
            if(shells[i].active == 1  )
            {
                states.transform=getTransform();
                //states.transform.translate(shells[i].position);
                states.transform*=shells[i].states.transform;
                states.transform.rotate
                (
                    atan2( shells[i].velocity.x , -shells[i].velocity.y ) * 180.0/3.1415926
                );
                if(shells[i].typeId == 2)
                {
                    states.transform.rotate(shells[i].elapsed.asMilliseconds()/4);
                    states.transform.translate(sf::Vector2f(120.0*std::cos(shells[i].elapsed.asMilliseconds()/50.0+4),120.0*std::sin(shells[i].elapsed.asMilliseconds()/50.0+4)));
                }
                target.draw(shellSprite[shells[i].typeId],states);
                //target.draw(shellSprite[shells[i].typeId],shells[i].states);
            }
        }
};

void FireSystem::pushFireRequest(Shell fireRequest)
{
    //if(!checkFire(fireRequest.typeId)) return;
    fireRequest.active=1;
    double angle=atan2(fireRequest.velocity.y,fireRequest.velocity.x);
    fireRequest.velocity=sf::Vector2f(std::cos(angle) * typeVelocity[fireRequest.typeId], std::sin(angle) * typeVelocity[fireRequest.typeId]);
    for(unsigned int i=1;i<=shells.size();++i)
    if(shells[i].active == 0)
    {
        shells[i]=fireRequest;
        shells[i].elapsed=sf::Time();
        break;
    }
}
void FireSystem::update(sf::Time elapsed)
{
    for(unsigned int i=0;i<shells.size();++i)
    if(shells[i].active)
    {

        shells[i].move(  sf::Vector2f(
                         elapsed.asSeconds()*shells[i].velocity.x
                        ,elapsed.asSeconds()*shells[i].velocity.y )  );

        shells[i].elapsed+=elapsed;
        sf::Vector2f nowPos=shells[i].states.transform*sf::Vector2f(0,0);

        if(   nowPos.x>2000||nowPos.x<-100
            ||nowPos.y>2000||nowPos.y<-100)
        {
            shells[i].active=0;
        }
        if(shells[i].typeId == 2)
        {

        }
    }
}
bool FireSystem::checkFire(unsigned int typeId)
{
    fireElapsed[typeId]+=fireClock[typeId].restart();
    bool flag=0;
    while(fireElapsed[typeId]>firePause[typeId])
    {
        flag=1;
        fireElapsed[typeId]=sf::Time::Zero;
    }
    return flag;
}
void FireSystem::loadShell(unsigned int typeId,sf::IntRect rec,float vel,sf::Vector2f opos,sf::Time pauseTime,float sizeChange)
{
    if(!shellTexture[typeId].loadFromFile("shell1.png",rec))
        std::cout<<"shellTexture[0].loadFromFile error!!"<<std::endl;
    shellSprite[typeId].setTexture(shellTexture[typeId]);
    shellSprite[typeId].setOrigin(opos);
    shellSprite[typeId].setScale(sizeChange,sizeChange);
    typeVelocity[typeId]=vel;
    firePause[typeId]=pauseTime;

}
#endif // FIRESYSTEM_H
