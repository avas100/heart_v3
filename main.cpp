#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QFont font;
    font.setPointSize(12);  // Устанавливаем размер шрифта (например, 16 пунктов)
    a.setFont(font);
    w.show();
    return a.exec();
}
