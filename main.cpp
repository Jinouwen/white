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
    GameClass G(mStateStack.pendingList,mStateStack.window);
    mStateStack.initialize(&G);
    mStateStack.run();
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
