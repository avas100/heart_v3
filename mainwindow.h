#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QStatusBar>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QDebug>
#include <QLabel>
#include<QMenuBar>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include "paint.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void openSaveWidget();

private slots:
    void openFile();
    void saveFile();
    void exitApp();
    void closeFile();

    void showAbout();
    void showHowToUse();


    void logAction(const QString &message);
    void updateStatusBar();

    void logActionCurvatureCoefficient(const QString &message);
    void logActionCurvatureFactor(const QString &message);
    void logActionAveragedData(const QString &message);

    void saveFullName();
    void saveComment();
    void newPatient();
    void logActionComment(const QString &message);
    void logActionFullName(const QString &message);

private:
    Ui::MainWindow *ui;
    Paint *paintWidget;
    QTabWidget *tabWidget;
    QWidget *tab1;
    QWidget *tab2;
    QWidget *tab3;
    QPushButton *saveFullNameButton;
    QPushButton *openSaveButton;
    QPushButton *saveCommentButton;
    QPushButton *newPatientButton;


    QTextEdit *logArea;
    QTextEdit  *logCurvatureCoefficient;
    QTextEdit  *logCurvatureFactor;
    QTextEdit  *logAveragedData;

    QTextEdit *fullName;
    QTextEdit *comment;

    void setupMenu();

};
#endif // MAINWINDOW_H
