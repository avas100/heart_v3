#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QVector>
#include <QMap>
#include <QPainterPath>
#include <QPdfWriter>
#include <QKeyEvent>
#include <QWheelEvent>
#include "splineinterpolation.h"
#include <cmath>

class paintScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit paintScene(QObject *parent = 0);
    ~paintScene();
    void plotCurve();
    int getPointsCount() const;
    void clearPoints();
    void clearLastPoint();
    void clearDataForImage();
    void clearMap();

    void setSelectedTypeArteryIndex(int index);
    void setSelectedImageIndex(int index);
    int getSelectedImageIndex();
    int getSelectedPatientIndex();

    QVector<QString> imageFileNames;
    void openImage(const QString &fileName);
    QPointF lastPoint();
    QPointF getPoint(int index) const;
    int pointCount();
    bool isCalculated();

    QVector<double> getCurvature();
    void getAverageCurvature();

    int newPatient();
    void savePdfWithImagesAndText(const QString &filePath);
    void savePointTxt(const QString &filePath);
    void saveComment(const QString &comment);
    void saveFullName (const QString &comment);


signals:

    // Изменения QTextEdit
    void actionPerformedLog(const QString &message);
    void actionPerformedCurvatureCoefficient(const QString &message);
    void actionPerformedFactor(const QString &message);
    void actionPerformedAverage(const QString &message);
    void actionPerformedFullName(const QString &message);
    void actionPerformedComment(const QString &message);

    void actionPerformedStatusBar(const QString &message);

    void imageIndexChanged(int index);
    void imageOpened(const QString &fileName);

private:
    QPointF previousPoint;
    SplineInterpolation spline;

    int selectedImageIndex = 0;
    int patientIndex = 0;

    QVector<QVector<QPointF>> pointsForImages;
    QVector<bool> isCurvatureCalculated;
    QVector<QVector<double>> imageCurvature;
    QVector<QString> imageComment;
    QVector<QString> imageFullName;
    QMap<QString, QList<int>> typeArteryMap;
    QVector<QImage> changedImage;
    QVector<double> averageCurvature;
    QVector<int> typeArteryIndex;

    void saveChangedImage();

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

};

#endif // PAINTSCENE_H
