#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    statusBar()->showMessage("Готово");

    paintWidget = new Paint(this);
    paintWidget->setFixedWidth(700);
    paintWidget->setFixedHeight(700);

    QFont font;
    font.setPointSize(12);

    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *centralLayout = new QHBoxLayout;
    QVBoxLayout *lefttLayout = new QVBoxLayout;

    //Данные о пациенте
    tabWidget = new QTabWidget(this);
    tabWidget->setFixedSize(250,21);
    tab1 = new QWidget(this);
    tab2 = new QWidget(this);
    tab3 = new QWidget(this);
    tabWidget->addTab(tab1, "ОА");
    tabWidget->addTab(tab2, "ПКА");
    tabWidget->addTab(tab3, "ПМЖА");
    connect(tabWidget, &QTabWidget::currentChanged,
            [this](int index){
                int patientIndex = paintWidget->scene->getSelectedPatientIndex();
                paintWidget->scene->setSelectedImageIndex(patientIndex*3 + index);
                updateStatusBar();
            });
    lefttLayout->addWidget(tabWidget);

    QLabel *fullNameLabel = new QLabel("Введите Ф. И. О.:", this);
    lefttLayout->addWidget(fullNameLabel);

    fullName = new QTextEdit(this);
    fullName->setFixedHeight(100);
    connect(paintWidget->scene, &paintScene::actionPerformedComment, this, &MainWindow::logActionFullName);
    lefttLayout->addWidget(fullName);

    QPushButton *saveFullNameButton = new QPushButton("Записать Ф. И. О.", this);
    connect(saveFullNameButton, &QPushButton::clicked, this, &MainWindow::saveFullName);
    lefttLayout->addWidget(saveFullNameButton);

    QPushButton *newPatientButton = new QPushButton("Новый пациент", this);
    connect(newPatientButton, &QPushButton::clicked, this, &MainWindow::newPatient);
    lefttLayout->addWidget(newPatientButton);

    lefttLayout->addStretch();

    //Работа с файлом

    QPushButton *openButton = new QPushButton("Открыть", this);
    connect(openButton, &QPushButton::clicked, [this](bool)
            {
                QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Открыть снимки"), "", tr("Images (*.png *.xpm *.jpg);;All Files (*)"));
                int previousSelectedIndex = paintWidget->scene->getSelectedImageIndex();
                int index = paintWidget->scene->getSelectedPatientIndex()*3;

                if (fileNames.size() > 3 || fileNames.size() == 2) {
                    QMessageBox::warning(this, tr("Предупреждение"), tr("Пожалуйста, выберите либо один файл, либо ровно три файла."));
                }
                else{
                    for (int i = 0; i < fileNames.size(); i++) {
                        if(fileNames.size()==1){
                            index = previousSelectedIndex;
                        }
                        QString fileName = fileNames.at(i);
                        QImage image(fileName);
                        if (image.isNull()) {
                            QMessageBox::information(this, tr("Ошибка"), tr("Невозможно загрузить %1.").arg(fileName));
                            continue; // Пропустить этот файл и перейти к следующему
                        }

                        // Если снимок уже был открыт и файл успешно загружен, то очищаем прошлые данные
                        if (!paintWidget->scene->imageFileNames[index].isEmpty()) {
                            paintWidget->scene->setSelectedImageIndex(index);
                            paintWidget->scene->clearDataForImage();
                            updateStatusBar();
                        }

                        paintWidget->scene->clear();
                        paintWidget->scene->setSelectedImageIndex(index);
                        paintWidget->scene->openImage(fileName);
                        paintWidget->scene->addPixmap(QPixmap::fromImage(image));
                        logAction(QString("Снимок %1 открыт").arg(paintWidget->scene->getSelectedImageIndex()+1));
                        index++;
                        updateStatusBar();
                    }
                }
                paintWidget->scene->setSelectedImageIndex(previousSelectedIndex);
            });
    lefttLayout->addWidget(openButton);

    QPushButton *closeButton = new QPushButton("Закрыть", this);
    connect(closeButton, &QPushButton::clicked,
            [this](){
                paintWidget->scene->clearDataForImage();
                paintWidget->scene->clear();
                updateStatusBar();
            });
    lefttLayout->addWidget(closeButton);

    QPushButton *openSaveButton = new QPushButton("Сохранить", this);
    connect(openSaveButton, &QPushButton::clicked, this, &MainWindow::openSaveWidget);
    lefttLayout->addWidget(openSaveButton);

    lefttLayout->addStretch();

    // Работа с точками
    QPushButton *cancelButton = new QPushButton("Отмена", this);
    connect(cancelButton, &QPushButton::clicked,
            [this](){
                paintWidget->scene->clearLastPoint();
                updateStatusBar();
            });
    lefttLayout->addWidget(cancelButton);
    cancelButton->setFont(font);

    QPushButton *clearButton = new QPushButton("Очистить", this);
    connect(clearButton, &QPushButton::clicked,
            [this](){
                paintWidget->scene->clearPoints();
                updateStatusBar();
            });
    lefttLayout->addWidget(clearButton);

    lefttLayout->addStretch();

    // Высчиление результата
    // если добавить возможность изменять степень извиточти
    // QComboBox *typeArteryComboBox = new QComboBox(this);
    // typeArteryComboBox->addItem("Неизвитая");
    // typeArteryComboBox->addItem("Умеренно извитая");
    // typeArteryComboBox->addItem("Извитая");
    // connect(typeArteryComboBox, QOverload<int>::of(&QComboBox::activated),
    //         [this](int index){
    //             paintWidget->scene->setSelectedTypeArteryIndex(index);
    //             updateStatusBar();
    //         });
    // lefttLayout->addWidget(typeArteryComboBox);

    QPushButton *calculateButton = new QPushButton("Вычислить", this);
    connect(calculateButton, &QPushButton::clicked,
            [this](){
                paintWidget->scene->plotCurve();
                paintWidget->scene->getCurvature();
                updateStatusBar();
            });
    lefttLayout->addWidget(calculateButton);


    centralLayout->addLayout(lefttLayout);

    // Снимок
    QHBoxLayout *paintLayout = new QHBoxLayout;
    paintLayout->addWidget(paintWidget);

    centralLayout->addLayout(paintLayout);

    // Данные
    QVBoxLayout *dataLayout = new QVBoxLayout;

    QLabel *curvatureLabel = new QLabel("Кривизна:", this);
    dataLayout->addWidget(curvatureLabel);

    logCurvatureCoefficient = new QTextEdit(this);
    logCurvatureCoefficient->setReadOnly(true);
    connect(paintWidget->scene, &paintScene::actionPerformedCurvatureCoefficient, this, &MainWindow::logActionCurvatureCoefficient);
    dataLayout->addWidget(logCurvatureCoefficient);

    QLabel *curvatureFactorLabel = new QLabel("Степень извитости:", this);
    dataLayout->addWidget(logCurvatureFactor);
    dataLayout->addWidget(curvatureFactorLabel);


    logCurvatureFactor = new QTextEdit(this);
    logCurvatureFactor->setReadOnly(true);
    connect(paintWidget->scene, &paintScene::actionPerformedFactor, this, &MainWindow::logActionCurvatureFactor);

    dataLayout->addWidget(logCurvatureFactor);


    QLabel *averagedDataLabel = new QLabel("Среднее значение кривизны:", this);
    dataLayout->addWidget(averagedDataLabel);

    logAveragedData = new QTextEdit(this);
    logAveragedData->setReadOnly(true);
    connect(paintWidget->scene, &paintScene::actionPerformedAverage, this, &MainWindow::logActionAveragedData);
    dataLayout->addWidget(logAveragedData);

    centralLayout->addLayout(dataLayout);


    // log и комментарии
    QVBoxLayout *logLayout = new QVBoxLayout;

    QLabel *logLabel = new QLabel("Журнал:", this);
    logLayout->addWidget(logLabel);

    logArea = new QTextEdit(this);
    logArea->setReadOnly(true);
    connect(paintWidget->scene, &paintScene::actionPerformedLog, this, &MainWindow::logAction);
    logLayout->addWidget(logArea);

    QLabel *commentLabel = new QLabel("Ввод комментария:", this);
    logLayout->addWidget(commentLabel);

    comment = new QTextEdit(this);
    connect(paintWidget->scene, &paintScene::actionPerformedFullName, this, &MainWindow::logActionComment);
    logLayout->addWidget(comment);

    QPushButton *saveCommentButton = new QPushButton("Закомментировать", this);
    connect(saveCommentButton, &QPushButton::clicked, this, &MainWindow::saveComment);
    logLayout->addWidget(saveCommentButton);

    centralLayout->addLayout(logLayout);

    // итоговое
    centralWidget->setLayout(centralLayout);
    setCentralWidget(centralWidget);

    setupMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupMenu(){
    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    QMenu *fileMenu = menuBar->addMenu("Файл");

    QAction *saveAction = new QAction("Сохранить", this);
    connect(saveAction, &QAction::triggered, this, &MainWindow::openSaveWidget);
    fileMenu->addAction(saveAction);

    QAction *openAction = new QAction("Открыть", this);
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    fileMenu->addAction(openAction);

    QAction *exitAction = new QAction("Выход", this);
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);
    fileMenu->addAction(exitAction);

    QMenu *analysisMenu = menuBar->addMenu("Анализ");

    QAction *calculateAction = new QAction("Вычислить", this);
    connect(calculateAction, &QAction::triggered, [this](){
        paintWidget->scene->plotCurve();
        paintWidget->scene->getCurvature();
        updateStatusBar();
    });
    analysisMenu->addAction(calculateAction);

    // анализ + справка

    QMenu *helpMenu = menuBar->addMenu("Справка");

    QAction *aboutAction = new QAction("О программе", this);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAbout);
    helpMenu->addAction(aboutAction);

    QAction *howToUseAction = new QAction("Как работать", this);
    connect(howToUseAction, &QAction::triggered, this, &MainWindow::showHowToUse);
    helpMenu->addAction(howToUseAction);
}

void MainWindow::openSaveWidget()
{
    bool ok;
    QString folder = QFileDialog::getExistingDirectory(this, "Выберите путь для папки");
    QString name = QInputDialog::getText(this, "Сохранить данные", "Сохранить как:", QLineEdit::Normal, "", &ok);
    paintWidget->scene->savePointTxt(QString("%1/%2.txt").arg(folder).arg(name));
    // три разных файла :name извитые, name неизвитые, name умеренно извитые
    paintWidget->scene->savePdfWithImagesAndText(QString("%1/%2.pdf").arg(folder).arg(name));
}

void MainWindow::saveFullName() {
    QString fullNameText = fullName->toPlainText();
    paintWidget->scene->saveFullName(fullNameText);
}

void MainWindow::saveComment() {
    QString commentText = comment->toPlainText();
    paintWidget->scene->saveComment(commentText);
}

void MainWindow::newPatient()
{
    int isNewPatient = paintWidget->scene->newPatient();
    if(isNewPatient==0)QMessageBox::warning(this, "Предупреждение", "Данные запонены не полностью, проверте текущие снимки артерий");
    else if(isNewPatient==1)QMessageBox::warning(this, "Предупреждение", "Данные запонены не полностью, не рассчитаны коэффициенты");
    else if(isNewPatient==2)QMessageBox::warning(this, "Предупреждение", "Данные запонены не полностью, не введено ФИО");
}
// для открытия прошлых анализов и сохранения  прошлых анализов
void MainWindow::openFile()
{
    // Реализация...
}

void MainWindow::saveFile()
{
    // Реализация...
}

void MainWindow::exitApp()
{
    qApp->exit();
}

void MainWindow::closeFile()
{
    paintWidget->scene->clearPoints();
    paintWidget->scene->clear();
    logAction("Снимок закрыт");
    updateStatusBar();
}

void MainWindow::showAbout()
{
    QMessageBox::about(this, "О программе", "   Программа предназначена для автоматизации и синхронизации сбора данных и анализа пациентов с сердечно-сосудистыми заболеваниями. \n"
                            "Основная цель – упрощение процесса диагностики, мониторинга и профилактики заболеваний сердца и сосудов у пациентов.\n"
                            "\n"
                            "   В программу вводятся три снимка различных артерий сердца. После того как пользователь проставит точки на местах изгиба, программа строит кривую по данным точкам и вычисляет степень извитости артерии. \n"
                            "\n"
                            "   Также есть возможность сохранить проведенный анализ в документ, с сохраненными данными о пациенте. ");
}

void MainWindow::showHowToUse()
{
    QString instructions = "Как использовать программу:\n\n"
                           "- Шаг 1: Выберите пациента, артерию и номер снимка в верхней части окна.\n"
                           "- Шаг 2: Нажмите кнопку 'Открыть', чтобы загрузить выбранный снимок.\n"
                           "- Шаг 3: Поставьте точки на снимке в местах изгибов артерии.\n"
                           "         Кликните мышью по снимку для добавления точки.\n"
                           "- Шаг 4: Нажмите кнопку 'Вычислить', чтобы программа рассчитала коэффициент кривизны.\n"
                           "- Шаг 5: Опционально введите комментарий в нижнем правом углу окна.\n"
                           "- Шаг 6: Повторите шаги с 1 по 5 для других снимков и пациентов.\n"
                           "         Вернитесь к Шагу 1 для нового анализа или завершите работу.\n\n"
                           "После завершения анализа можно сохранить результаты в PDF-файл.";

    QMessageBox::information(this, "Как работать", instructions);

}

void MainWindow::logAction(const QString &message) {
    QString formattedMessage = message;
    logArea->append(formattedMessage);
}

void MainWindow::logActionCurvatureCoefficient(const QString &message)
{
    if(message == "clear") {
        logCurvatureCoefficient->clear();
    }
    else{
        QString formattedMessage = message;
        logCurvatureCoefficient->append(formattedMessage);
    }
}

void MainWindow::logActionCurvatureFactor(const QString &message) {
    if(message == "clear") {
        logCurvatureFactor->clear();
    }
    else{
        QString formattedMessage = message;
        logCurvatureFactor->append(formattedMessage);
    }
}

void MainWindow::logActionAveragedData(const QString &message) {
    if(message == "clear") {
        logAveragedData->clear();
    }
    else{
        QString formattedMessage = message;
        logAveragedData->append(formattedMessage);
    }
}

void MainWindow::logActionComment(const QString &message) {
    if(message == "clear") {
        comment->clear();
    }
    else{
        QString formattedMessage = message;
        comment->append(formattedMessage);
    }
}

void MainWindow::logActionFullName(const QString &message)
{
    if(message == "clear") {
        fullName->clear();
    }
    else{
        QString formattedMessage = message;
        fullName->append(formattedMessage);
    }
}

void MainWindow::updateStatusBar() {
    int pointCount = paintWidget->scene->pointCount();
    bool curvatureCalculated = paintWidget->scene->isCalculated();
    QString statusMessage = QString("Количество точек: %1;  Кривизна: %2")
                                .arg(pointCount)
                                .arg(curvatureCalculated ? "рассчитана" : "не рассчитана");
    statusBar()->showMessage(statusMessage);
}
