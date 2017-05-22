#ifndef ENEMYCLASS_H
#define ENEMYCLASS_H

#include <cstdio>
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

struct enemy
{
    float HP;
    unsigned int typeId;
    bool active;
    sf::Vector2f towards;
    sf::Vector2f velocity;
    sf::Time enemyElapsed;
    sf::Transform enemyTransform;
    enemy(unsigned int typeId0,sf::Vector2f velocity0,sf::Vector2f pos)
    :typeId(typeId0),active(0),velocity(velocity0)
    {
        enemyTransform.translate(pos);
    }
    enemy():active(0){}
    void move(float xx,float yy)
    {
        enemyTransform.translate(xx,yy);
    }
    void move(sf::Time elapsed0)
    {
        enemyTransform.translate(velocity.x*elapsed0.asSeconds(),velocity.y*elapsed0.asSeconds());
    }
    sf::Transform getTransform()
    {
        return enemyTransform;
    }
};

class EnemiesDataClass
{

    private:
        unsigned int num;
        unsigned int nowNum;
        std::vector<enemy> enemies;
        std::vector<sf::Time> timeList;

    public:
        void load(int index)
        {
            enemies.clear();
            timeList.clear();
            nowNum=0;

            std::string str="enemiesData";
            str+=Int_to_String(index);
            str+=".txt";
            freopen(str.c_str(),"r",stdin);

            std::cin>>num;
            unsigned int typeId;
            sf::Vector2f vel;
            sf::Vector2f pos;
            float askTime;
            for(unsigned int i=0;i<num;++i)
            {
                std::cin >> (typeId) >> (vel.x) >> (vel.y) >> (pos.x) >> (pos.y) >>askTime;
                enemies.push_back(enemy(typeId,vel,pos));
                timeList.push_back(sf::seconds(askTime));
            }

            freopen("con","r",stdin);
        }
        int check(sf::Time totalTime)
        {
            if(nowNum>num) return -1;
            if(totalTime>=timeList[nowNum]) return 1;
            return 0;
        }
        enemy getEnemyRequest()
        {
            enemy temp(enemies[nowNum]);
            nowNum++;
            return temp;
        }
};

class EnemyClass:public sf::Drawable, public sf::Transformable
{
    public:
        EnemyClass(unsigned int count0);
        virtual ~EnemyClass() {}
        unsigned int getCount(){return count;}
        void update(sf::Time elapsed);
        void pushEnemyRequest(enemy enemyRequest);
        void readyToCheck(){nowNum=0;}
        int pushNextActive();
        sf::FloatRect getEnemyRect();
    private:
        std::vector<enemy> enemies;
        unsigned int count;
        sf::Sprite enemySprite[20];
        sf::Texture enemyTexture[20];
        sf::Vector2f enemyVelocity[20];
        void loadEnemy(unsigned int typeId,sf::IntRect textureRect,sf::Vector2f orignPos,float HP,sf::Vector2f velocity,float sizeChange);
        sf::Time totalTime;
        EnemiesDataClass enemiesData[3];
        unsigned int nowStates;
        unsigned int nowNum;
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates   states) const
        {
            states.transform *= getTransform();

            for(unsigned int i=0;i<enemies.size();++i)
            if(enemies[i].active)
            {
                states.transform = getTransform();
                states.transform *= enemies[i].enemyTransform;
                target.draw(enemySprite[enemies[i].typeId] ,states);
            }
        }
};
EnemyClass::EnemyClass(unsigned int count0):enemies(count0),count(count0),nowStates(0)
{
    loadEnemy(0,sf::IntRect(1,1,16,16),sf::Vector2f(8,8),1,sf::Vector2f(0,200),3);
    enemiesData[0].load(0);
}
void EnemyClass::loadEnemy(unsigned int typeId,sf::IntRect textureRect,sf::Vector2f orignPos,float HP,sf::Vector2f velocity,float sizeChange)
{
    if(!enemyTexture[typeId].loadFromFile("enemyTexture.png",textureRect))
        std::cout<<"enemyTexture[typeId].loadFromFile error!!"<<std::endl;
    enemySprite[typeId].setTexture(enemyTexture[typeId]);
    enemySprite[typeId].setOrigin(orignPos);
    enemySprite[typeId].setScale(sizeChange,sizeChange);
}
void EnemyClass::update(sf::Time elapsed)
{

    for(unsigned int i=0; i<enemies.size() ; ++i)
    if(enemies[i].active)
    {
        enemies[i].enemyElapsed+=elapsed;
        enemies[i].move(elapsed);

        sf::Vector2f pos;
        pos=(enemies[i].getTransform())*pos;
        if(pos.x<-300||pos.x>2000||pos.y<-300||pos.y>2000)
        {
          enemies[i].active=0;
        }
    }

    totalTime+=elapsed;
    while(enemiesData[nowStates].check(totalTime)==1)
    {
        pushEnemyRequest(enemiesData[nowStates].getEnemyRequest());
    }
}
void EnemyClass::pushEnemyRequest(enemy enemyRequest)
{
    enemyRequest.active=1;
    for(unsigned int i=0;i<enemies.size();++i)
    if(!enemies[i].active)
    {
        enemies[i]=enemyRequest;
        break;
    }
}
int EnemyClass::pushNextActive()
{
    while(nowNum<enemies.size()&& !(enemies[nowNum].active) )
        nowNum++;
    if(nowNum>=enemies.size()) return -1;
    return nowNum;
}
sf::FloatRect EnemyClass::getEnemyRect()
{
    sf::Sprite temp(enemySprite[enemies[nowNum].typeId]);
    temp.move((enemies[nowNum].getTransform()*sf::Vector2f(0,0)));
    nowNum++;
    return temp.getGlobalBounds();
}
#endif // ENEMYCLASS_H
