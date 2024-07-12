#include "paint.h"
#include <QGraphicsView>
#include <QVBoxLayout>
Paint::Paint(QWidget *parent) :
    QWidget(parent),
    scene(new paintScene(this))
{
    QGraphicsView *view = new QGraphicsView(scene, this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(view);
    setLayout(layout);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Paint::slotTimer);
    timer->start(100);
}

Paint::~Paint()
{
    delete timer;
    delete scene;
}

void Paint::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}

void Paint::slotTimer()
{
    // Реализация...
}
