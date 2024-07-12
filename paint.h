#ifndef PAINT_H
#define PAINT_H

#include <QWidget>
#include <QTimer>
#include <QResizeEvent>
#include "paintscene.h"

class Paint : public QWidget
{
    Q_OBJECT

public:
    explicit Paint(QWidget *parent = 0);
    ~Paint();
    QTimer *timer;
    paintScene *scene;

private:
    void resizeEvent(QResizeEvent *event);

private slots:
    void slotTimer();
};

#endif // PAINT_H
