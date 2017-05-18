#ifndef GAMECLASS_H
#define GAMECLASS_H

#include <SFML/Graphics.hpp>
#include <myshipclass.h>
#include <firesystem.h>
#include <enemyclass.h>
#include <iostream>
#include <string>
#include <sstream>

std::string Int_to_String(int n)
{
    std::stringstream ss;
    ss<<n;
    return ss.str();
}

class GameClass
{
    public:
        GameClass();
        virtual ~GameClass() {}
        void run();
    protected:

    private:
        void processEvents();
        void update(sf::Time elapsed);
        void render();

        void updateMyship(sf::Time elapsed);
        void myShipFire(unsigned int typeId,unsigned int level);
        void myshipPFR(unsigned int getemitter,sf::Vector2f vel,unsigned int typeId);
    private:
        sf::ContextSettings settings;
        sf::RenderWindow window;
        FireSystem fireSystem;
        MyshipClass myship;
        EnemyClass enemySystem;


        sf::Vector2f mainboardPos;
        sf::Vector2f mainboardsize;
        sf::RectangleShape mainboard;
        sf::RectangleShape leftboard;
        sf::RectangleShape rightboard;
        sf::Text shellTypeText;
        sf::Text levelText;
        std::string shellTypeText0;
        std::string levelText0;
        unsigned int nowShellType;
        unsigned int nowLevel;
        sf::Font font;
};
/////////////////////////////////////////////////////////////////////////////constructor
GameClass::GameClass()
:window(sf::VideoMode(1600, 900), "SFML works!", sf::Style::Close , settings)
,fireSystem(300),enemySystem(40)
,mainboardPos(400,0),mainboardsize(800,900)
,shellTypeText0("Now shell type: "),levelText0("Now level: ")
,nowShellType(0),nowLevel(0)
{
    settings.antialiasingLevel = 0;
    window.setPosition(sf::Vector2i(100,50));
    window.setFramerateLimit(60);
    //window.setVerticalSyncEnabled(true);

    myship.setPosition(sf::Vector2f(800,700));
    mainboard.setPosition(mainboardPos);
    mainboard.setSize(mainboardsize);
    mainboard.setFillColor(sf::Color(170,170,170));
    leftboard.setPosition(sf::Vector2f(0.0,0.0));
    leftboard.setSize(sf::Vector2f(400.0,900.0));
    leftboard.setFillColor(sf::Color(200,200,200));
    rightboard.setPosition(sf::Vector2f(1200,0));
    rightboard.setSize(sf::Vector2f(400.0,900.0));
    rightboard.setFillColor(sf::Color(200,200,200));

    if(!font.loadFromFile("myfont.ttf"))
    {
        std::cout<<"font.loadFromFile(myfont.ttf) error!!"<<std::endl;
    }
    shellTypeText.setFont(font);
    levelText.setFont(font);
    levelText.setPosition(0,50);
    shellTypeText.setString("Now shell type: 0");
    levelText.setString("Now level: 0");

}
////////////////////////////////////////////////////////////////////////////
void GameClass::run()
{
    const sf::Time TPF(sf::seconds(1.f / 60.f));///Time Per Frame
    sf::Clock clock;
    sf::Time elapsed(sf::Time::Zero);
    while(window.isOpen())
    {
        elapsed=clock.restart();
        processEvents();
        update(elapsed);
        render();
    }
}
void GameClass::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            window.close();
        }
        else if(event.type == sf::Event::LostFocus)
        {
            //
        }
        else if(event.type == sf::Event::JoystickButtonPressed)
        {
            if(event.joystickButton.button == 5)
            {
                myShipFire(nowShellType,nowLevel);
            }
            else if(event.joystickButton.button == 0)//A
            {
                nowLevel= nowLevel==0?nowLevel:nowLevel-1;
                levelText.setString(levelText0+Int_to_String(nowLevel));
            }
            else if(event.joystickButton.button == 1)//B
            {
                nowShellType = nowShellType == 2 ?nowShellType :nowShellType+1;
                shellTypeText.setString(shellTypeText0+Int_to_String(nowShellType));
            }
            else if(event.joystickButton.button == 2)//X
            {
                nowShellType = nowShellType ==0? nowShellType :nowShellType-1;
                shellTypeText.setString(shellTypeText0+Int_to_String(nowShellType));
            }
            else if(event.joystickButton.button == 3)//Y
            {
                nowLevel= nowLevel==4?nowLevel:nowLevel+1;
                levelText.setString(levelText0+Int_to_String(nowLevel));
            }
            else if(event.joystickButton.button == 4)//LB
            {
            }
        }
        else if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Space)
            {
                myShipFire(0,5);
            }
        }
    }
}
void GameClass::render()
{
    window.clear(sf::Color(200,200,200));
    window.draw(mainboard);
    window.draw(enemySystem);
    window.draw(myship);
    window.draw(fireSystem);
    window.draw(leftboard);
    window.draw(rightboard);
    window.draw(shellTypeText);
    window.draw(levelText);
    window.display();
}
void GameClass::update(sf::Time elapsed)
{
    updateMyship(elapsed);
    fireSystem.update(elapsed);
    enemySystem.update(elapsed);
}

void GameClass::updateMyship(sf::Time elapsed)
{

    float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
    float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
    float v = 5;

    myship.setRotation(x/10);

    if( (myship.getPosition().x>=mainboardPos.x+35&&x<0 )
    ||  (myship.getPosition().x<=mainboardPos.x+mainboardsize.x-35&&x>0) )
        myship.move( x*v*elapsed.asSeconds() ,0.0);
    if( (myship.getPosition().y>=mainboardPos.y+55&&y<0)
    ||  (myship.getPosition().y<=mainboardPos.y+mainboardsize.y-35&&y>0) )
        myship.move(0.0, y*v*elapsed.asSeconds() );

    if(sf::Joystick::isButtonPressed(0,5))
    {
        myShipFire(nowShellType,nowLevel);
    }
}


void GameClass::myShipFire(unsigned int typeId,unsigned int level)
{
    if(!fireSystem.checkFire(typeId)) return;

    if(typeId == 0 )
    {
        if(level >= 0)
        {
            myshipPFR(0,sf::Vector2f(0,-1000),0);
        }
        if(level >= 1)
        {
            myshipPFR(1,sf::Vector2f(-100,-1000),0);
            myshipPFR(2,sf::Vector2f(100,-1000),0);
        }
        if(level >= 2)
        {
            myshipPFR(1,sf::Vector2f(0,-1000),0);
            myshipPFR(2,sf::Vector2f(0,-1000),0);
        }
        if(level >= 3)
        {
            myshipPFR(3,sf::Vector2f(-200,-1000),0);
            myshipPFR(4,sf::Vector2f(200,-1000),0);
            myshipPFR(3,sf::Vector2f(-300,-1000),0);
            myshipPFR(4,sf::Vector2f(300,-1000),0);
        }
        if(level >=4)
        {
            myshipPFR(4,sf::Vector2f(-200,-1000),0);
            myshipPFR(3,sf::Vector2f(200,-1000),0);
            myshipPFR(4,sf::Vector2f(-350,-1000),0);
            myshipPFR(3,sf::Vector2f(350,-1000),0);
            myshipPFR(4,sf::Vector2f(-250,-1000),0);
            myshipPFR(3,sf::Vector2f(250,-1000),0);
        }
    }
    else if(typeId == 1)
    {
        if(level >= 0)
        {
            myshipPFR(0,sf::Vector2f(0,-1000),1);
        }
        if( level >=1)
        {
            myshipPFR(1,sf::Vector2f(-100,-1000),0);
            myshipPFR(2,sf::Vector2f(100,-1000),0);
        }
    }
    else if(typeId == 2)
    {
        if(level >= 0)
        {
            myshipPFR(0,sf::Vector2f(0,-1000),typeId);
        }
        if( level >=1)
        {
            myshipPFR(1,sf::Vector2f(-100,-1000),typeId);
            myshipPFR(2,sf::Vector2f(100,-1000),typeId);
        }
    }
}
void GameClass::myshipPFR(unsigned int getemitter,sf::Vector2f vel,unsigned int typeId)
{
    fireSystem.pushFireRequest(Shell(myship.getemitter(getemitter),vel,typeId));
}
#endif // GAMECLASS_H
