#include <bits/stdc++.h>

#define EPS 1e-6   /// precision error tolerance

/**
    Various geometric tasks are implemented
    Main source:
        Competitive Programming 3 by Steven & Felix Halim
**/

using namespace std;

struct Point {  /// (x, y)
    double x;
    double y;

    Point(double x, double y) : x(x), y(y) {}
};

struct Line {  /// y = mx + c
    double m;  /// we can also use ax + by + c = 0 to deal with vertical
    double c;

    Line(double m, double c) : m(m), c(c) {}
};

struct Polygon {  /// N number of points in polygon, point vector of points in clockwise order
    int N;
    vector < Point > point;
};

bool areEqual(double d1, double d2) {
    return (abs(d1-d2) < EPS);
}

double distancePointPoint(Point A, Point B) {   /// distance from point A to point B
    double d = (A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y); /// can also use hypot(...)
    d = sqrt(d);
    return d;
}

double CCW(Point A, Point B, Point C) {  /// if ccw < 0 then A-B-C is a left turn
    double x1 = A.x-B.x, y1 = A.y-B.y;  /// if ccw = 0 then A-B-C are colinear
    double x2 = B.x-C.x, y2 = B.y-C.y; /// if ccw > 0 then A-B-C is a right turn
    double ccw = x1*y2 - y1*x2;
    return ccw;
}

double distancePointLine(Point A, Line L) {   /// distance form point A to line L
     ///   y = |mx - y + c|
    ///        sqrt(1 + m^2)
    double numerator = abs(L.m*A.x - A.y + L.c);
    double denominator = sqrt(1 + L.m*L.m);
    double d = numerator/denominator;
    return d;
}

double areaOfPolygon(Polygon P) {  /// area of polygon P
    double area = 0.0;
    for (int i=0; i<P.N; i++) {
        Point p1 = P.point[i];
        Point p2 = P.point[(i+1)%P.N];
        area += (p1.x * p2.y) - (p1.y * p2.x);
    }
    area /= 2.0;
    return abs(area);
}

bool areLinesParallel(Line L1, Line L2) {   /// return true if L1//L2
    return areEqual(L1.m, L2.m);
}

bool lineIntersection(Line L1, Line L2, Point& P) {  /// returns true if they intersect and point
    if (areLinesParallel(L1, L2)) return false;     /// of intersection is in P
                                                   /// otherwise false
    P.x = (L1.c-L2.c) / (L2.m-L1.m);
    P.y = P.x*L1.m + L1.c;
    return true;
}

Point base(0.0, 0.0);

bool angleCompare(Point A, Point B) {
    if (abs(CCW(base, A, B)) < EPS)  /// are colinear
        return distancePointPoint(base, A) < distancePointPoint(base, B);
    return (atan2(A.y-base.y, A.x-base.x) - atan2(B.y-base.y, B.x-base.x) < 0);
}

Polygon convexHull(vector < Point > P) {  /// find convex hull using graham scan
    stack < Point > S;  /// temporary stack
    Polygon convHull;  /// resulting convex hull

    if (P.size() <= 3) {  /// convex hull is all points
        for (int i=0; i<P.size(); i++)
            convHull.point.push_back(P[i]);
        convHull.N = P.size();
        return convHull;
    }

    /// find bottommost and rightmost point for base
    int idxOfBase = 0;
    base = P[0];
    for (int i=1; i<P.size(); i++) {
        if (P[i].y < base.y || areEqual(P[i].y, base.y) && P[i].y > base.y) {
            base = P[i];
            idxOfBase = i;
        }
    }

    swap(P[0], P[idxOfBase]);

    sort(++P.begin(), P.end(), angleCompare);

    S.push(P[0]);
    S.push(P[1]);
    int i = 2;
    while (i < P.size()) {
        /// obtain last two points
        Point candidate = S.top();
        S.pop();
        Point prev = S.top();
        S.push(candidate);

        if (CCW(prev, candidate, P[i]) > 0) {
            S.push(P[i]);
            i ++;
        }
        else {
            S.pop();
        }
    }

    while (!S.empty()) {
        convHull.point.push_back(S.top());
        S.pop();   /// will be in counter-clockwise order
    }

    convHull.N = convHull.point.size();
    return convHull;
}

int main()
{
    /// test for convex hull
    vector < Point > test1;
    test1.push_back(Point(0.0, 0.0));
    test1.push_back(Point(10.0, 3.5));
    test1.push_back(Point(2.43, 5.35));
    test1.push_back(Point(34.25, 6.786));
    test1.push_back(Point(42.63, 6.334));
    test1.push_back(Point(-20.3, 5.53));
    test1.push_back(Point(34.32, -54.22));

    Polygon CH = convexHull(test1);

    cout << CH.N << endl;  /// must be 4

    /// test for distance point to line
    cout << distancePointLine(Point(1.0, 2.0), Line(1.0, 2.5)) << endl;

    /// test for area of Polygon
    cout << areaOfPolygon(CH) << endl;

    /// test for line intersection
    Point test2(0.0, 0.0);
    if (lineIntersection(Line(1.0, 1.0), Line(2.0, 2.0), test2));
    cout << test2.x << " " << test2.y << endl;

    return 0;
}
