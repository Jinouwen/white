#ifndef STATE_H
#define STATE_H


class State
{
    public:
        State();
        virtual void run();
    private:
        unsigned int typeId;
};

#endif // STATE_H
