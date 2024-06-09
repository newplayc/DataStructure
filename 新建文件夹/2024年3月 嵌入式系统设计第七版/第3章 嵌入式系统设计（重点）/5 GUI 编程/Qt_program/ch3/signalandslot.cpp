#include "signalandslot.h"

signalandslot::signalandslot(QObject *parent) :
    QObject(parent)
{
    Data=0;
}

void signalandslot::SetData(int inputData)
{
    if(Data!=inputData)
    {
        Data=inputData;
        emit DataChanged(Data);
    }
}

