#ifndef MYSHIPCLASS_H
#define MYSHIPCLASS_H

#include <SFML/Graphics.hpp>
#include <animationsystem.h>
#include <iostream>

class MyshipClass:public sf::Drawable, public sf::Transformable
{
    public:
        MyshipClass();
        virtual ~MyshipClass() {}
        sf::Vector2f getemitter(int index);
        void update(sf::Time elapsed);
        void dealCollison(float damage,AnimationSystem &animationSystem);
    private:
        sf::Time totalTime;
        sf::Sprite body;
        sf::Sprite sprite;
        sf::Sprite light;
        sf::Texture bodyTexture;
        sf::Texture lightTexture;
        sf::Sprite spriteLight;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates   states) const
        {
            states.transform *= getTransform();
            states.texture = &bodyTexture;
            target.draw(sprite,states);
            target.draw(body,states);
            target.draw(light,states);
            target.draw(spriteLight,states);
        }
};
MyshipClass::MyshipClass()
{
    if(!bodyTexture.loadFromFile("myship.png"))
    {
        std::cout<<"Mysshipclass bodyTexture.loadFromFile(myship.png) error!!"<<std::endl;
    }
    body.setTexture(bodyTexture);
    body.setTextureRect(sf::IntRect(0,0,29,34));
    body.setOrigin(14,20);
    body.setScale(1.6,1.6);
    sprite.setTexture(bodyTexture);
    sprite.setTextureRect(sf::IntRect(0,0,29,34));
    sprite.setOrigin(14,20);
    sprite.setScale(0.8,0.8);
    light.setOrigin(500,500);
    light.setScale(0.08,0.08);
    lightTexture.loadFromFile("light0.png");
    light.setTexture(lightTexture);
    spriteLight=light;
    spriteLight.setScale(0.05,0.05);
}
void MyshipClass::update(sf::Time elapsed)
{
    totalTime+=elapsed;
    light.setScale(0.10+0.02*std::cos(totalTime.asMilliseconds()/700.0),
                   0.10+0.02*std::cos(totalTime.asMilliseconds()/700.0));
    sprite.setPosition(
             sf::Vector2f( 60.0*std::cos(totalTime.asMilliseconds()/300.0)
                          ,60.0*std::sin(totalTime.asMilliseconds()/300.0) ) );
    spriteLight.setPosition(sprite.getPosition());
}
sf::Vector2f MyshipClass::getemitter(int index)
{
    if(index == 0)
    return sf::Vector2f((*this).getPosition().x,(*this).getPosition().y-40);
    else if(index == 1)
    return sf::Vector2f((*this).getPosition().x-20,(*this).getPosition().y-35);
    else if(index == 2)
    return sf::Vector2f((*this).getPosition().x+20,(*this).getPosition().y-35);
    else if(index == 3)
    return sf::Vector2f((*this).getPosition().x-30,(*this).getPosition().y-25);
    else if(index == 4)
    return sf::Vector2f((*this).getPosition().x+30,(*this).getPosition().y-25);
    else if(index == 10)//sprite
    return (*this).getPosition()+sprite.getPosition();

}
void MyshipClass::dealCollison(float damage,AnimationSystem &animationSystem)
{

}

#endif // MYSHIPCLASS_H
