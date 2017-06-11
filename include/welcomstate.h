#ifndef WELCOMSTATE_H
#define WELCOMSTATE_H
#include <mstate.h>

class WelcomState:public MState
{
    public:
        WelcomState(PendingList & ,sf::RenderWindow &);
        virtual ~WelcomState() {}


        virtual void handleEvent(sf::Event & event);
        virtual void update(sf::Time elapsed);
        virtual void render();

    private:
        sf::Sprite title0;
        sf::Texture title0Texture;
        sf::Sprite title1;
        sf::Texture title1Texture;
        sf::Time totalTime;
        sf::Texture title2Texture;
        bool flag;
};

inline WelcomState::WelcomState(PendingList & pendingList,sf::RenderWindow & window):MState(pendingList,window)
{
    title0Texture.loadFromFile("title0.png");
    title0.setTexture(title0Texture);
    title0.setPosition(450,300);
    title0.setColor(sf::Color(0,0,0,0));
    title1Texture.loadFromFile("title1.png");
    title1.setTexture(title1Texture);
    title1.setPosition(500,300);
    title1.setColor(sf::Color(0,0,0,0));
    title2Texture.loadFromFile("title2.png");
    flag=0;
}
void WelcomState::handleEvent(sf::Event &event)
{

}

void WelcomState::update(sf::Time elapsed)
{
    totalTime+=elapsed;
    if(totalTime<sf::seconds(2.0))
    {
        title0.setColor(sf::Color(0,0,0,totalTime.asSeconds()*255/2));
    }
    if(totalTime>sf::seconds(5))
    {
        title0.setColor(sf::Color(0,0,0,std::max(0,(int)(255-(totalTime.asSeconds()-5)*255/2))));
    }
    if(totalTime>sf::seconds(7))
    {
        title1.setColor(sf::Color(0,0,0,(totalTime.asSeconds()-7)*255/2));
    }
    if(totalTime>sf::seconds(9))
    {
        title1.setColor(sf::Color(0,0,0,std::max(0,(int)(255-(totalTime.asSeconds()-9)*255/2))));
    }
    if(totalTime>sf::seconds(10)&&!flag)
    {
        flag=1;
        title0.setTexture(title2Texture);
        title0.setPosition(0,300);
        title0.setTextureRect(sf::IntRect(0,0,title2Texture.getSize().x,title2Texture.getSize().y));
    }
    if(totalTime>sf::seconds(11)&&totalTime<sf::seconds(14))
    {
        title0.setColor(sf::Color(0,0,0,(totalTime.asSeconds()-11)*255/2));
    }
    if(totalTime>sf::seconds(13))
    {
        title0.setColor(sf::Color(0,0,0,std::max(0,(int)(255-(totalTime.asSeconds()-13)*255/2))));
    }
    if(totalTime>sf::seconds(16))
    {
        pop();
        push(1);
    }
}
inline void WelcomState::render()
{
    window.clear(sf::Color(255,255,250,255));
    window.draw(title0);
    window.draw(title1);
    window.display();
}

#endif // WELCOMSTATE_H
