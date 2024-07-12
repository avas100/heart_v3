#include "splineinterpolation.h"
#include <cmath>

SplineInterpolation::SplineInterpolation() {}

QVector<double> SplineInterpolation::initializeParameteric(QVector<QPointF> Points) {
    int N = Points.size();
    QVector<double> t(N);
    t[0] = 0.0;

    for (int i = 1; i < N; ++i) {
        double dx = Points[i].x() - Points[i - 1].x();
        double dy = Points[i].y() - Points[i - 1].y();
        t[i] = t[i - 1] + std::sqrt(dx * dx + dy * dy);
    }

    return t;
}

QVector<QPointF> SplineInterpolation::initializeFreeTerms(QVector<QPointF> Points) {
    int N = Points.size();
    QVector<double> t = initializeParameteric(Points);

    QVector<QPointF> b_vec(N);

    b_vec[0] = QPointF(0.0, 0.0);
    for (int i = 1; i < N - 1; i++) {
        QPointF b;
        b.setX(6.0 * ((Points[i + 1].x() - Points[i].x()) / (t[i + 1] - t[i]) - (Points[i].x() - Points[i - 1].x()) / (t[i] - t[i - 1])));
        b.setY(6.0 * ((Points[i + 1].y() - Points[i].y()) / (t[i + 1] - t[i]) - (Points[i].y() - Points[i - 1].y()) / (t[i] - t[i - 1])));
        b_vec[i] = b;
    }
    b_vec[N - 1] = QPointF(0.0, 0.0);

    return b_vec;
}

QVector<QVector<double>> SplineInterpolation::initializeMatrix(QVector<QPointF> Points) {
    int N = Points.size();
    QVector<double> t = initializeParameteric(Points);

    QVector<QVector<double>> A(N, QVector<double>(N, 0.0));


    A[0][0] = 1.0;
    int k = 1;
    for (int i = 1; i <= N - 2; i++) {
        A[k][k - 1] = t[i] - t[i - 1];
        A[k][k] = 2 * (t[i + 1] - t[i - 1]);
        A[k][k + 1] = t[i + 1] - t[i];
        k++;
        if (k + 2 > N) break;
    }
    A[N - 1][N - 1] = 1.0;

    return A;
}

QVector<QPointF> SplineInterpolation::solveTridiagonal(QVector<double> a, QVector<double> b, QVector<double> c, QVector<QPointF> d) {
    int N = d.size();
    QVector<QPointF> result(N);
    QVector<double> c_star(N, 0.0);
    QVector<QPointF> d_star(N);

    c_star[0] = c[0] / b[0];
    d_star[0] = d[0] / b[0];

    for (int i = 1; i < N; i++) {
        double m = 1.0 / (b[i] - a[i] * c_star[i - 1]);
        c_star[i] = c[i] * m;
        d_star[i].setX((d[i].x() - a[i] * d_star[i - 1].x()) * m);
        d_star[i].setY((d[i].y() - a[i] * d_star[i - 1].y()) * m);
    }

    result[N - 1] = d_star[N - 1];

    for (int i = N - 2; i >= 0; i--) {
        result[i].setX(d_star[i].x() - c_star[i] * result[i + 1].x());
        result[i].setY(d_star[i].y() - c_star[i] * result[i + 1].y());
    }

    return result;
}

QVector<QPointF> SplineInterpolation::calculateSecondDerivative(QVector<QPointF> Points) {
    int N = Points.size();

    QVector<QPointF> b = initializeFreeTerms(Points);

    QVector<QVector<double>> A = initializeMatrix(Points);

    QVector<double> a(N, 0.0), b_diag(N, 0.0), c(N, 0.0);
    for (int i = 1; i < N - 1; i++) {
        a[i] = A[i][i - 1];
        b_diag[i] = A[i][i];
        c[i] = A[i][i + 1];
    }
    b_diag[0] = A[0][0];
    b_diag[N - 1] = A[N - 1][N - 1];

    QVector<QPointF> s = solveTridiagonal(a, b_diag, c, b);

    return s;
}

double SplineInterpolation::W(double t, double t_i, double t_ip) {
    return ((t - t_i) / (t_ip - t_i));
}

QVector<QPointF> SplineInterpolation::R(QVector<QPointF> Points) {
    QVector<double> t = initializeParameteric(Points);
    int N = Points.size();
    QVector<QPointF> s = calculateSecondDerivative(Points);
    QVector<QPointF> pointsArray = Points;
    QVector<QPointF> Res;
    for (int i = 0; i < N - 1; i++) {
        double t_i = t[i];
        double t_ii = t[i + 1];
        for (double t_val = t_i; t_val <= t_ii - H; t_val += H) {
            QPointF Fun_R(0.0, 0.0);
            double w = W(t_val, t_i, t_ii);

            Fun_R.setX(pointsArray[i].x() * (1.0 - w) + pointsArray[i + 1].x() * w +
                       (-2.0 * w + 3 * pow(w, 2.0) - pow(w, 3.0)) * s[i].x() +
                       (-1.0 * w + pow(w, 3.0)) * s[i + 1].x() * (pow(t_ii - t_i, 2.0) / 6.0));

            Fun_R.setY(pointsArray[i].y() * (1.0 - w) + pointsArray[i + 1].y() * w +
                       (-2.0 * w + 3 * pow(w, 2.0) - pow(w, 3.0)) * s[i].y() +
                       (-1.0 * w + pow(w, 3.0)) * s[i + 1].y() * (pow(t_ii - t_i, 2.0) / 6.0));

            Res.push_back(Fun_R);
        }
    }
    return Res;
}


QVector<QPointF> SplineInterpolation::calculateFirstDerivative(QVector<QPointF> Points) {
    QVector<double> t = initializeParameteric(Points);
    int N = Points.size();
    QVector<QPointF> S = calculateSecondDerivative(Points);
    QVector<QPointF> pointsArray;

    for (int i = 0; i < N - 1; i++) {
        QPointF D;
        D.setX((Points[i + 1].x() - Points[i].x()) / (t[i + 1] - t[i]));
        D.setY((Points[i + 1].y() - Points[i].y()) / (t[i + 1] - t[i]));

        D.setX(D.x() - 1.0 / 6.0 * (2.0 * S[i].x() + S[i + 1].x()) * (t[i + 1] - t[i]));
        D.setY(D.y() - 1.0 / 6.0 * (2.0 * S[i].y() + S[i + 1].y()) * (t[i + 1] - t[i]));

        pointsArray.push_back(D);
    }
    return pointsArray;
}

QVector<double> SplineInterpolation::curvature(QVector<QPointF> Points) {
    QVector<QPointF> d1 = calculateFirstDerivative(Points);
    QVector<QPointF> d2 = calculateSecondDerivative(Points);

    int N = Points.size();
    QVector<double> curvatures(N - 2);

    for (int i = 1; i < N - 1; i++) {
        double dx = d1[i].x();
        double dy = d1[i].y();
        double ddx = d2[i].x();
        double ddy = d2[i].y();

        double numerator = std::abs(dx * ddy - dy * ddx);
        double denominator = std::pow(dx * dx + dy * dy, 1.5);

        if (denominator != 0) {
            curvatures[i - 1] = numerator / denominator;
        } else {
            curvatures[i - 1] = 0;
        }
    }
    return curvatures;
}

