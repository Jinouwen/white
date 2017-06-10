#ifndef GAMECLASS_H
#define GAMECLASS_H

#include <state.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <myshipclass.h>
#include <firesystem.h>
#include <enemyclass.h>
#include <effectssystem.h>
#include <animationsystem.h>
#include <iostream>
#include <string>
#include <sstream>

class GameClass:public State
{
    public:
        GameClass();
        virtual ~GameClass() {}
        virtual void run();
    protected:

    private:
        void processEvents();
        void update(sf::Time elapsed);
        void render();

        void updateMyship(sf::Time elapsed);
        void myShipFire(unsigned int typeId,unsigned int level);
        void myshipPFR(unsigned int getemitter,sf::Vector2f vel,unsigned int typeId);
        void checkCollision();
        bool isCollision(sf::Vector2f,sf::Vector2f);
        void playBGM(sf::Music &music);
        void updateBackground(sf::Time elapsed);
        void viewUpdate();
    private:
        sf::RenderWindow window;
        FireSystem fireSystem;
        MyshipClass myship;
        EnemyClass enemySystem;
        AnimationSystem animationSystem;


        sf::Vector2f mainboardPos;
        sf::Vector2f mainboardsize;
        sf::RectangleShape mainboard;
        sf::RectangleShape leftboard;
        sf::RectangleShape rightboard;
        sf::RectangleShape background0;
        sf::RectangleShape background1;
        sf::Texture backgroundTexture0;
        sf::Texture backgroundTexture1;
        sf::Text shellTypeText;
        sf::Text levelText;
        std::string shellTypeText0;
        std::string levelText0;
        unsigned int nowShellType;
        unsigned int nowLevel;
        sf::Font font;
        sf::Time totalTime;
        sf::Event event;
        sf::View gameView;
        sf::View totalView;


};
/////////////////////////////////////////////////////////////////////////////constructor
GameClass::GameClass()
:window(sf::VideoMode(1600, 900), "SFML works!", sf::Style::Close)
,fireSystem(500),enemySystem(10)
,mainboardPos(400,0),mainboardsize(800,900)//400 1200
,shellTypeText0("Now shell type: "),levelText0("Now level: ")
,nowShellType(0),nowLevel(0)
{
    window.setPosition(sf::Vector2i(100,50));
    window.setFramerateLimit(120);
    totalView=window.getDefaultView();
    gameView.setCenter(sf::Vector2f(800,450));
    gameView.setSize(sf::Vector2f(600,700));
    gameView.setViewport(sf::FloatRect(0.25,0,0.5,1));


    backgroundTexture0.loadFromFile("backGround0.png");
    backgroundTexture1.loadFromFile("backGround1.png");
    backgroundTexture0.setRepeated(1);
    backgroundTexture1.setRepeated(1);
    myship.setPosition(sf::Vector2f(800,700));
    mainboard.setPosition(mainboardPos);
    mainboard.setSize(mainboardsize);
    leftboard.setPosition(sf::Vector2f(0.0,0.0));
    leftboard.setSize(sf::Vector2f(400.0,900.0));
    leftboard.setFillColor(sf::Color(20,20,20));
    rightboard.setPosition(sf::Vector2f(1200,0));
    rightboard.setSize(sf::Vector2f(400.0,900.0));
    rightboard.setFillColor(sf::Color(20,20,20));

    background0=mainboard;
    background0.setTexture(&backgroundTexture0);
    background0.setTextureRect(sf::IntRect(0,0,1600,1800));
    background0.setFillColor(sf::Color(255,255,255,100));
    background1=background0;
    background1.setTexture(&backgroundTexture1);


    mainboard.setFillColor(sf::Color(170,170,170));
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
    sf::Music music;

    playBGM(music);
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
    while (window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            window.close();
        }
        else if(event.type == sf::Event::LostFocus)
        {

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
            if(event.key.code ==sf::Keyboard::Num1)
            {
                nowLevel= nowLevel==0?nowLevel:nowLevel-1;
                levelText.setString(levelText0+Int_to_String(nowLevel));
            }
            else if(event.key.code ==sf::Keyboard::Num2)//B
            {
                nowShellType = nowShellType == 2 ?nowShellType :nowShellType+1;
                shellTypeText.setString(shellTypeText0+Int_to_String(nowShellType));
            }
            else if(event.key.code ==sf::Keyboard::Num3)//X
            {
                nowShellType = nowShellType ==0? nowShellType :nowShellType-1;
                shellTypeText.setString(shellTypeText0+Int_to_String(nowShellType));
            }
            else if(event.key.code ==sf::Keyboard::Num4)//Y
            {
                nowLevel= nowLevel==4?nowLevel:nowLevel+1;
                levelText.setString(levelText0+Int_to_String(nowLevel));
            }
            else if(event.key.code ==sf::Keyboard::K)//Y
            {

            }
        }
    }
}
void GameClass::render()
{
    window.clear(sf::Color(200,200,200));

    window.setView(totalView);
    window.draw(leftboard);
    window.draw(rightboard);
    window.draw(shellTypeText);
    window.draw(levelText);

    window.setView(gameView);
    window.draw(mainboard);
    window.draw(background0);
    window.draw(background1);
    window.draw(myship);
    window.draw(fireSystem);
    window.draw(enemySystem);
    window.draw(shellTypeText);
    window.draw(levelText);
    window.draw(leftboard);
    window.draw(rightboard);
    window.draw(animationSystem);

    window.display();
}
void GameClass::update(sf::Time elapsed)
{
    totalTime+=elapsed;
    updateBackground(elapsed);
    updateMyship(elapsed);
    animationSystem.update(elapsed);
    fireSystem.update(elapsed);
    enemySystem.update(elapsed,fireSystem,myship.getPosition());
    viewUpdate();
    checkCollision();
}

void GameClass::updateMyship(sf::Time elapsed)
{

    float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
    float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        x-=100;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        x+=100;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        y+=100;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        y-=100;

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
    if(  sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
       ||sf::Keyboard::isKeyPressed(sf::Keyboard::J)      )
    {
        myShipFire(nowShellType,nowLevel);
    }
    myship.update(elapsed);
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

        myshipPFR(10,sf::Vector2f(0,-1000),0);
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
void GameClass::checkCollision()
{
    fireSystem.readyToCheck();
    int shellId;
    int enemyId;
    while( (shellId=fireSystem.pushNextActive()) != -1 )
    {
        sf::Vector2f shellPos(fireSystem.getCollisionPos());
        if(fireSystem.getType()<10)
        {
            enemySystem.readyToCheck();
            while((enemyId=enemySystem.pushNextActive()) != -1)
            {
            // std::cout<<++sz<<std::endl;
                sf::Vector2f enemyPos(enemySystem.getCollisionPos());
                if(isCollision(shellPos,enemyPos))
                {
               // std::cout<<"collision!!"<<std::endl;
                enemySystem.dealCollison(fireSystem.dealCollision(),animationSystem);
                }
            }
        }
        else
        {
            if(isCollision(shellPos,myship.getPosition()))
            {
                myship.dealCollison(fireSystem.dealCollision(),animationSystem);
            }
        }
    }
}
bool GameClass::isCollision(sf::Vector2f p1,sf::Vector2f p2)
{
    return (p1.x-p2.x)*(p1.x-p2.x)<=400 && (p1.y-p2.y)*(p1.y-p2.y) <= 800;
}
void GameClass::playBGM(sf::Music &music)
{
    music.openFromFile("1.NieR- Automata OST - Intro.wav");
    music.play();
}
void GameClass::updateBackground(sf::Time elapsed)
{
    background0.setTextureRect(sf::IntRect(totalTime.asSeconds()*-20,-totalTime.asSeconds()*250,1600,1800));
    background1.setTextureRect(sf::IntRect(totalTime.asSeconds()*50,-totalTime.asSeconds()*200,1600,1800));
}
void GameClass::viewUpdate()
{
    sf::Vector2f p(myship.getPosition()-mainboardPos);
    p.x/=4;
    p.y/=4.5;

    gameView.setCenter(mainboardPos+sf::Vector2f(300,350)+p);

}
#endif // GAMECLASS_H
