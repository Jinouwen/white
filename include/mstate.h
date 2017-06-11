#ifndef MSTATE_H
#define MSTATE_H
#include <queue>
struct Pending
{
    unsigned int opt;
    unsigned int typeId;
    Pending(unsigned int opt,unsigned int typeId):opt(opt),typeId(typeId){}
};
class PendingList
{
    public:
        std::queue<Pending> mlist;
        unsigned int opt;
        unsigned int typeId;

};

class MState
{
    public:
        MState( PendingList &pendingList ,sf::RenderWindow & );
        virtual ~MState() {}

        virtual void handleEvent(sf::Event & event)=0;
        virtual void update(sf::Time elapsed)=0;
        virtual void render()=0;
        PendingList &pendingList;
        sf::RenderWindow & window;
        void push(int typeId);
        void pop();
        void clear();
    private:

    private:
        MState& getReference();
};

inline MState::MState(PendingList &pendingList,sf::RenderWindow & window)
:pendingList(pendingList),window(window)
{

}
void MState::push(int typeId)
{
    pendingList.mlist.push(Pending(1,typeId));
}
void MState::pop()
{
    pendingList.mlist.push(Pending(2,0));
}
void MState::clear()
{
    pendingList.mlist.push(Pending(3,0));
}/*
MState & MState::getReference()
{
    return (*this);
}*/

////////////////////////////////////////////////////////////////
class MStateStack
{
    public:
        MStateStack();
        virtual ~MStateStack(){}
        void run();
        void initialize(MState * temp);
        sf::RenderWindow window;
        PendingList pendingList;
    private:
        sf::Event event;
        sf::Clock clock;
        sf::Time elapsed;
        std::vector<MState *> mStack;
    private:
        void handleEvent(sf::Event& evnet);
        void update(sf::Time elapsed);
        void render();
        void handlePending();

};

inline MStateStack::MStateStack():window(sf::VideoMode(1600, 900), "SFML works!", sf::Style::Close)
{

}

void MStateStack::initialize ( MState * temp )
{
    mStack.push_back(temp);
    window.setPosition(sf::Vector2i(100,50));
    window.setFramerateLimit(120);
}
void MStateStack::run()
{
    clock.restart();
    while(window.isOpen())
    {
        elapsed=clock.restart();
        handlePending();
        printf("%8d ",clock.getElapsedTime().asMilliseconds());
        while(window.pollEvent(event))
        {
            handleEvent(event);
        }
        printf("%8d ",clock.getElapsedTime().asMilliseconds());
        update(elapsed);
        printf("%8d ",clock.getElapsedTime().asMilliseconds());
        render();
        printf("%8d \n",clock.getElapsedTime().asMilliseconds());
        handlePending();
    }
}
void MStateStack::handleEvent(sf::Event &event)
{
    (mStack.back())->handleEvent(event);
}
void MStateStack::update(sf::Time elapsed)
{
    (mStack.back())->update(elapsed);
}
void MStateStack::render()
{
    (mStack.back())->render();
}


#endif // MSTATE_H
