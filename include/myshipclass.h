#ifndef MYSHIPCLASS_H
#define MYSHIPCLASS_H

#include <SFML/Graphics.hpp>
#include <iostream>

class MyshipClass:public sf::Drawable, public sf::Transformable
{
    public:
        MyshipClass();
        virtual ~MyshipClass() {}
        sf::Vector2f getemitter(int index);
    private:
        sf::Sprite body;
        sf::Texture bodyTexture;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates   states) const
        {
            states.transform *= getTransform();
            states.texture = &bodyTexture;
            target.draw(body,states);
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
    body.setScale(2,2);
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
}

#endif // MYSHIPCLASS_H
