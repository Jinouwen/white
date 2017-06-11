#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <gameclass.h>
#include <mstate.h>
#include <welcomstate.h>
int main()
{
///////////////////////////////////////////////////
    MStateStack mStateStack;
    WelcomState W(mStateStack.pendingList,mStateStack.window);

    std::cout<<233;
    mStateStack.initialize(&W);
    mStateStack.run();
    //GameClass game(p);
//    game.run();
///////////////////////////////////////////////////
    return 0;
}


void MStateStack::handlePending()
{
    while(!pendingList.mlist.empty())
    {
        Pending p(pendingList.mlist.front());
        pendingList.mlist.pop();
        if(p.opt==1)
        {
            if(p.typeId==1)
            {
                MState* temp( new GameClass(pendingList,window) );
                mStack.push_back(temp);
            }
        }
        else if(p.opt==2)
        {
            mStack.pop_back();
        }

    }
}
