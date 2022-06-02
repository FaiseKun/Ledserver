#ifndef GPIO_H
#define GPIO_H

#include <QObject>
#include "config.h"

class Gpio : public QObject
{
    Q_OBJECT
public:
    explicit Gpio(QObject *parent = nullptr);  // Constructor
    ~Gpio(); // Destructor
    void set(int pin, int state);
    void set(unsigned int pattern);

signals:

public slots:

private:
    int m_handle;
};

#endif // GPIO_H
