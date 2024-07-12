#pragma once
#ifndef SPLINEINTERPOLATION_H
#define SPLINEINTERPOLATION_H

#include <QPointF>
#include <QVector>

const double H = 0.01;

class SplineInterpolation {
public:
    SplineInterpolation();

    QVector<double> initializeParameteric(QVector<QPointF> Points);
    QVector<QPointF> initializeFreeTerms(QVector<QPointF> Points);
    QVector<QVector<double>> initializeMatrix(QVector<QPointF> Points);
    QVector<QPointF> solveTridiagonal(QVector<double> a, QVector<double> b, QVector<double> c, QVector<QPointF> d);
    QVector<QPointF> calculateSecondDerivative(QVector<QPointF> Points);
    double W(double t, double t_i, double t_ip);
    QVector<QPointF> R(QVector<QPointF> Points);
    QVector<QPointF> calculateFirstDerivative(QVector<QPointF> Points);
    QVector<double> curvature(QVector<QPointF> Points);
};

#endif // SPLINEINTERPOLATION_H
