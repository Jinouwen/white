#ifndef STATE_H
#define STATE_H


class mState
{
    public:
        mState()
        {
            typeId=0;
        }
        virtual void run();
    private:
        unsigned int typeId;
};

#endif // STATE_H
