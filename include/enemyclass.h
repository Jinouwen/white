#ifndef ENEMYCLASS_H
#define ENEMYCLASS_H
#include <cstdio>
struct enemy
{
    float HP;
    sf::Vector2f position;
    sf::Vector2f towards;
    sf::Vector2f velocity;
    sf::Time elapsed;
    bool active;
    unsigned int typeId;

    enemy():active(0){}
    void move(float xx,float yy)
    {
        position.x+=xx;
        position.y+=yy;
    }
    void move(sf::Time elapsed0)
    {
        position.x+=velocity.x*elapsed0.asSeconds();
        position.y+=velocity.y*elapsed0.asSeconds();
    }
};

class EnemyClass:public sf::Drawable, public sf::Transformable
{
    public:
        EnemyClass(unsigned int count0);
        virtual ~EnemyClass() {}
        unsigned int getCount(){return count;}
        void update(sf::Time elapsed);
    private:
        std::vector<enemy> enemies;
        unsigned int count;
        sf::Sprite enemySprite[20];
        sf::Texture enemyTexture[20];
        sf::Vector2f enemyVelocity[20];
        void loadEnemy(unsigned int typeId,sf::IntRect textureRect,sf::Vector2f orignPos,float HP,sf::Vector2f velocity,float sizeChange);
        void pushEnemyRequest(unsigned int typreId,sf::Vector2f position);
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates   states) const
        {
            states.transform *= getTransform();
            states.transform.translate(500,200);
            target.draw(enemySprite[0],states);
        }
};
EnemyClass::EnemyClass(unsigned int count0):enemies(count0),count(count0)
{
    loadEnemy(0,sf::IntRect(1,1,16,16),sf::Vector2f(8,8),1,sf::Vector2f(0,200),5);
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
        enemies[i].move(elapsed);
    }
}
void pushEnemyRequest(unsigned int typreId,sf::Vector2f position)
{

}

#endif // ENEMYCLASS_H
