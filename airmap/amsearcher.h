#ifndef AMSEARCHER_H
#define AMSEARCHER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <queue>

#include "amglobal.h"

#include "amsearcherbase.h"

using namespace std;
using namespace AMStd;

class AMSearcher : public AMSearcherBase
{
    Q_OBJECT
public:
    explicit AMSearcher(QObject *parent = 0);
    QJsonObject path();

    AMLocationManagerBase *locationManager();
    AMMapPainter *mapPainter();

signals:

public slots:
    void clearSearchResult();
    void setMapPainter(AMMapPainter *mapPainter);
    void searchPath(const QJsonObject &target);
    void setLocationManager(AMLocationManagerBase *locationManager);

private:
    enum DotType
    {
        Normal = 0,
        Walked = 1,
        Destiation = 2
    };
    struct Dot
    {
        int x;
        int y;
        int z;
        int total;
        int toFrom;
        int toDest;
        int status;
        int Fx;
        int Fy;
        friend bool operator < (const Dot &a, const Dot &b)
        {
            if (a.total == b.total)
                return a.toDest > b.toDest;
            return a.total > b.total;
        }
    };
    Dot m_dot[2009][2009];
    void loadMap(const Map &map,
                 const int &startX,
                 const int &startY,
                 int &endX,
                 int &endY,
                 const int &type,
                 const int &index);
    bool aStarCanbe(int x, int y);
    void aStarRecall(Dot m_now);
    bool aStarSearch(Dot m_now, int value, int startarr, int endarr);
    AMLocationManagerBase *m_locationManager=nullptr;
    AMMapPainter *m_mapPainter=nullptr;
    priority_queue<Dot> m_q;
    Dot m_start, m_end, m_now;

    QJsonObject m_pathResult;

    int m_arr[16] = { 0, 1, 1, 0, -1, 0, 0, -1, 1, 1, -1, -1, 1, -1, -1, 1 };
    int m_borderWidth=0;
    int m_mapIndex=-1;
};

#endif // AMSEARCHER_H
