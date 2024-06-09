#ifndef SIGNALANDSLOT_H
#define SIGNALANDSLOT_H

#include <QObject>

class signalandslot : public QObject
{
    Q_OBJECT
public:
    explicit signalandslot(QObject *parent = 0);
    int Data;
signals:
    void DataChanged(int Data);
public slots:
    void SetData(int Data);
};

#endif // SIGNALANDSLOT_H
