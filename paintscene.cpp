#include "paintscene.h"
#include <QPdfWriter>
#include <QPainter>
#include <QImage>
#include <QDebug>
#include <QPixmap>
#include <QMessageBox>
#include <QFile>
#include <QGraphicsView>
#include <QTextStream>

paintScene::paintScene(QObject *parent) :
    QGraphicsScene(parent),
    imageFileNames(27),
    pointsForImages(27),
    isCurvatureCalculated(27, false),
    imageCurvature(27),
    imageComment(27),
    imageFullName(27),
    changedImage(27),
    typeArteryMap(),
    averageCurvature(27)
{}

paintScene::~paintScene()
{}

void paintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!imageFileNames[selectedImageIndex].isEmpty()) {
        imageCurvature[selectedImageIndex].clear();
        emit actionPerformedCurvatureCoefficient("clear");
        emit actionPerformedFactor("clear");
        emit actionPerformedAverage("clear");

        QString fileName = imageFileNames[selectedImageIndex];
        isCurvatureCalculated[selectedImageIndex] = false;
        pointsForImages[selectedImageIndex].append(event->scenePos());
        openImage(fileName);
        for (const auto &point : pointsForImages[selectedImageIndex])
        {
            addEllipse(point.x() - 5, point.y() - 5, 10, 10, QPen(), QBrush(Qt::red));
        }
    }
}

void paintScene::setSelectedImageIndex(int index)
{
    if (index == selectedImageIndex)
        return;

    selectedImageIndex = index;

    clear();
    emit actionPerformedFactor("clear");
    emit actionPerformedAverage("clear");
    emit actionPerformedFullName("clear");
    emit actionPerformedComment("clear");

    QString key;
    for (auto it = typeArteryMap.begin(); it != typeArteryMap.end(); ++it) {
        if (it.value().contains(selectedImageIndex)) {
            key= it.key();
        }
    }
    emit actionPerformedFactor(key);
    emit actionPerformedFullName(imageComment[selectedImageIndex]);
    emit actionPerformedComment(imageFullName[patientIndex]);

    // переоткрытие
    if (!imageFileNames[selectedImageIndex].isEmpty()) {
        QString fileName = imageFileNames[selectedImageIndex];
        openImage(fileName);
    }

    // прошлые тчк
    if(isCurvatureCalculated[selectedImageIndex])
    {
        emit actionPerformedAverage(QString("%1").arg(averageCurvature[selectedImageIndex]));
        QVector<QPointF> points = pointsForImages[selectedImageIndex];
        QVector<QPointF> r = spline.R(points);
        QVector<double> t = spline.initializeParameteric(points);
        int r_count = 0;

        QPainterPath path(points.first());
        for (int i = 0; i < pointsForImages[selectedImageIndex].size() - 1; i++) {
            double t_i = t[i];
            double t_ii = t[i + 1];
            for (double t = t_i; t < t_ii - H; t += H) {
                path.lineTo(r[r_count]);
                r_count++;
            }
        }
        addPath(path, QPen(Qt::blue, 2));
    }
    if (!pointsForImages[selectedImageIndex].isEmpty())
    {
        for (const auto &point : pointsForImages[selectedImageIndex])
        {
            addEllipse(point.x() - 5, point.y() - 5, 10, 10, QPen(), QBrush(Qt::red));
        }
    }
    emit actionPerformedCurvatureCoefficient("clear");

    if(!imageCurvature[selectedImageIndex].isEmpty()){
        for(const auto &curentCurvature: imageCurvature[selectedImageIndex]){
            emit actionPerformedCurvatureCoefficient(QString::number(curentCurvature));
        }
    }

    emit imageIndexChanged(selectedImageIndex);
}

void paintScene::setSelectedTypeArteryIndex(int index)
{
    typeArteryIndex[selectedImageIndex] = index;
}

void paintScene::saveComment (const QString &comment){
    actionPerformedLog("Комментарий для снимка сохранен");
    imageComment[selectedImageIndex] = comment;
}

void paintScene::saveFullName (const QString &comment){
    actionPerformedLog("Ф. И. О.   записано");
    imageFullName[patientIndex] = comment;
}

void paintScene::saveChangedImage()
{
    QImage image(sceneRect().size().toSize(), QImage::Format_ARGB32);
    image.fill(Qt::white);
    QPainter painter(&image);
    render(&painter);
    changedImage[selectedImageIndex] = image;
}

int paintScene::getSelectedImageIndex(){
    return selectedImageIndex;
}

int paintScene::getSelectedPatientIndex()
{
    return patientIndex;
}

void paintScene::openImage(const QString &fileName)
{
    QImage image(fileName);
    if (image.isNull()) {
        return;
    }

    clear();
    addPixmap(QPixmap::fromImage(image));

    imageFileNames[selectedImageIndex] = fileName;

    emit imageOpened(fileName);
}

void paintScene::clearDataForImage(){
    pointsForImages[selectedImageIndex].clear();
    imageCurvature[selectedImageIndex].clear();
    isCurvatureCalculated[selectedImageIndex] = false;
    clearMap();
    if (!imageFileNames[selectedImageIndex].isEmpty()) {
        imageFileNames[selectedImageIndex].clear();
    }
    emit actionPerformedCurvatureCoefficient("clear");
    emit actionPerformedFactor("clear");
    emit actionPerformedAverage("clear");
    clearMap();
    QString logMessage = QString("Данные для снимка %1 очищены").arg(selectedImageIndex+1);
    emit actionPerformedLog(logMessage);
}

void paintScene::clearMap()
{
    typeArteryMap["Неизвитая"].removeOne(selectedImageIndex);
    typeArteryMap["Умеренно извитая"].removeOne(selectedImageIndex);
    typeArteryMap["Извитая"].removeOne(selectedImageIndex);
}

void paintScene::plotCurve()
{
    if (selectedImageIndex == -1) return;
    if (pointsForImages[selectedImageIndex].size() < 2) return;

    emit actionPerformedCurvatureCoefficient("clear");

    if (!isCurvatureCalculated[selectedImageIndex]) {
        QVector<QPointF> points = pointsForImages[selectedImageIndex];
        QVector<QPointF> r = spline.R(points);
        QVector<double> t = spline.initializeParameteric(points);
        int r_count = 0;

        QPainterPath path(points.first());
        for (int i = 0; i < pointsForImages[selectedImageIndex].size() - 1; i++) {
            double t_i = t[i];
            double t_ii = t[i + 1];
            for (double t = t_i; t < t_ii - H; t += H) {
                path.lineTo(r[r_count]);
                r_count++;
            }
        }
        QString logMessage = QString("Кривизна для снимка %1 рассчитана.").arg(selectedImageIndex +1);
        emit actionPerformedLog(logMessage);

        addPath(path, QPen(Qt::blue, 2));
        isCurvatureCalculated[selectedImageIndex] = true;
    }
}

QVector<double> paintScene::getCurvature() {
    if (pointsForImages[selectedImageIndex].size() < 2) return {0};
    imageCurvature[selectedImageIndex] = spline.curvature(pointsForImages[selectedImageIndex]);
    for(const auto &curentCurvature : imageCurvature[selectedImageIndex] ){
        emit actionPerformedCurvatureCoefficient(QString::number(curentCurvature));
    }
    emit actionPerformedFactor("clear");
    emit actionPerformedAverage("clear");
    // после вычисления коэфициента индекс артерии записывается в словарь с разновид. арт
    getAverageCurvature();
    if (averageCurvature[selectedImageIndex]<0.015){
        typeArteryMap["Неизвитая"] << selectedImageIndex;
        QString logMessage = "Степень извитости записана (неизвитая)";
        emit actionPerformedLog(logMessage);
        emit actionPerformedFactor("Неизвитая");

    }
    else if(0.015<=averageCurvature[selectedImageIndex] && averageCurvature[selectedImageIndex]<0.04){
        typeArteryMap["Умеренно извитая"] << selectedImageIndex;
        QString logMessage = "Степень извитости записана (умерено извитая)";
        emit actionPerformedLog(logMessage);
        emit actionPerformedFactor("Умеренно извитая");
    }
    else if(0.04<=averageCurvature[selectedImageIndex]){
        typeArteryMap["Извитая"] << selectedImageIndex;
        QString logMessage = "Степень извитости записана (извитая)";
        emit actionPerformedLog(logMessage);
        emit actionPerformedFactor("Извитая");
    }
    saveChangedImage();
    emit actionPerformedAverage(QString("%1").arg(averageCurvature[selectedImageIndex]));
    return imageCurvature[selectedImageIndex];
}

void paintScene::getAverageCurvature()
{
    if(!pointsForImages.isEmpty()){
        double avarage = 0;
        for (const auto &current_curvature : imageCurvature[selectedImageIndex]) {
            avarage += current_curvature;
        }
        avarage = avarage / pointsForImages.size();
        averageCurvature[selectedImageIndex] = avarage;
    }
}

int paintScene::getPointsCount() const {
    QVector<QPointF> points = pointsForImages[selectedImageIndex];
    return points.size();
}

void paintScene::clearPoints() {
    if (selectedImageIndex != -1) {
        clearMap();
        pointsForImages[selectedImageIndex].clear();
        imageCurvature[selectedImageIndex].clear();
        isCurvatureCalculated[selectedImageIndex] = false;
        clear();
        QString fileName = imageFileNames[selectedImageIndex];
        openImage(fileName);
        emit actionPerformedCurvatureCoefficient("clear");
        emit actionPerformedFactor("clear");
        emit actionPerformedAverage("clear");

        emit actionPerformedLog("Очищены точки для снимка");
        emit imageOpened(fileName);
    }
}

void paintScene::clearLastPoint() {
    if (selectedImageIndex != -1 && !pointsForImages[selectedImageIndex].isEmpty()) {
        imageCurvature[selectedImageIndex].clear();
        emit actionPerformedCurvatureCoefficient("clear");
        emit actionPerformedFactor("clear");
        emit actionPerformedAverage("clear");
        pointsForImages[selectedImageIndex].removeLast();
        clearMap();
        clear();
        isCurvatureCalculated[selectedImageIndex] = false;
        averageCurvature.remove(selectedImageIndex);
        QString fileName = imageFileNames[selectedImageIndex];
        openImage(fileName);
        for (const auto &point : pointsForImages[selectedImageIndex])
        {
            addEllipse(point.x() - 5, point.y() - 5, 10, 10, QPen(), QBrush(Qt::red));
        }
        emit actionPerformedLog("Отмена добавления точки.");
        emit imageOpened(fileName);

    }
}

QPointF paintScene::lastPoint() {
    QVector<QPointF> points = pointsForImages[selectedImageIndex];
    return points.isEmpty() ? QPointF() : points.last();
}

QPointF paintScene::getPoint(int index) const {
    QVector<QPointF> points = pointsForImages[selectedImageIndex];
    return points[index];
}

int paintScene::pointCount()
{
    int count = pointsForImages[selectedImageIndex].size();
    return count;
}

bool paintScene::isCalculated()
{
    return isCurvatureCalculated[selectedImageIndex];
}

int paintScene::newPatient()
{
    for(int i =0;i < (patientIndex )*3; i++){
        if(imageFileNames[i].isEmpty()){
            actionPerformedLog("Данные заполнены не полностью, проверте текущие снимки артерий");
            return 0;
        }
        if(!isCurvatureCalculated[i]){
            actionPerformedLog("Данные заполнены не полностью, не рассчитаны коэффициенты");
            return 1;
        }
    }
    if(imageFullName[patientIndex].isEmpty()){
        actionPerformedLog("Данные заполнены не полностью, не введено Ф. И. О. ");
        return 2;
    }
    clear();
    patientIndex++;
    emit actionPerformedFactor("clear");
    emit actionPerformedAverage("clear");
    emit actionPerformedFullName("clear");
    emit actionPerformedComment("clear");
    selectedImageIndex +=3;

    QString logMessage = QString("Пациент сменился %1").arg(patientIndex +1);
    actionPerformedLog(logMessage);
    return 3;
}

void paintScene::savePdfWithImagesAndText(const QString &filePath)
{
    QPdfWriter writer(filePath);
    writer.setPageSize(QPageSize(QPageSize::A4));
    //   (А4, dpi=300) => (9921 x13703)

    QPainter painter;
    if (!painter.begin(&writer))
        return;

    QFont font("Arial", 12);
    painter.setFont(font);

    int pageCount = 0;
    int w = 4450;

    for (int i = 0; i <= patientIndex; ++i) {
        if (i != 0) {
            writer.newPage();
        }
        pageCount++;

        QRect titleRect(0, 0, 1640, 350);
        painter.drawText(titleRect, Qt::AlignLeft, imageFullName[i]);

        for (int j = 0; j < 3; ++j) {
            int index = j + i * 3;

            QRect arteryTitleRect(100, 300+ w*j, 1640, 350);
            if (j == 0) {
                painter.drawText(arteryTitleRect, Qt::AlignLeft, "ОА");
            } else if (j == 1) {
                painter.drawText(arteryTitleRect, Qt::AlignLeft, "ПКА");
            } else if (j == 2) {
                painter.drawText(arteryTitleRect, Qt::AlignLeft, "ПМЖА");
            }

            QImage image = changedImage[index];
            if (!image.isNull()) {
                painter.drawImage(QRectF(100, 600+ w*j, 2500, 2500), image);
            } else {
                painter.drawText(QRect(100, 600+ w*j, 2500, 2500), Qt::AlignLeft, "Ошибка загрузки");
            }

            painter.drawText(QRect(2900, 600+ w*j, 1720, 350), Qt::AlignLeft, "Коэффициенты:");
            QString curvature;
            for (const auto &current_curvature : imageCurvature[index]) {
                if(current_curvature == imageCurvature[index].back()){
                    curvature += QString("k = %1. ").arg(QString::number(current_curvature, 'f', 4));
                }
                else{
                    curvature += QString("k = %1, ").arg(QString::number(current_curvature, 'f', 4));
                }
            }
            painter.drawText(QRect(3000, 800+ w*j, 6400, 2000), Qt::AlignTop | Qt::TextWordWrap, curvature);

            QString key;
            for (auto it = typeArteryMap.begin(); it != typeArteryMap.end(); ++it) {
                if (it.value().contains(index)) {
                    key= it.key();
                }
            }
            painter.drawText(QRect(2900, 3000 + w*j, 6500, 350), Qt::AlignLeft, "Степень извитости: " + key.toLower());

            QString averageData = QString("Усредненное: %1. ").arg(averageCurvature[index]);
            painter.drawText(QRect(100, 3300+ w*j, 9300, 350), Qt::AlignLeft, averageData);

            painter.drawText(QRect(100, 3600+ w*j, 1640, 600), Qt::AlignLeft, "Комментарий:");
            painter.drawText(QRect(200, 3800+ w*j, 9200, 700), Qt::AlignTop | Qt::TextWordWrap, imageComment[index]+ ".");
        }

        QRect pageContentRect(9420, 13303, 350, 350);
        QString pageNumber = QString("%1").arg(pageCount);
        painter.drawText(pageContentRect, Qt::AlignLeft, pageNumber);
    }

    painter.end();
}

void paintScene::savePointTxt(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    out.setCodec("UTF-8");
    for (int i = 0; i <= patientIndex; ++i) {
        out << imageFullName[i] << "\n";

        for (int j = 0; j < 3; ++j) {
            int index = j + i * 3;

            QString artery = "Артерия №";
            QString coords = "Координаты:";
            out << "    "<<artery << (j + 1) << "\n";
            out << "        "<<coords<<"\n";

            for (const auto &current_point : pointsForImages[index]) {
                out << "            (" << current_point.x() << ", " << current_point.y() << "),\n";
            }

            out << "\n";
        }
    }

    file.close();
}




