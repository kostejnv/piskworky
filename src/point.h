//
// Created by flgn on 18.02.21.
//

#ifndef PISKWORKY_POINT_H
#define PISKWORKY_POINT_H

class point {

public:
    int x, y;

    point(int x1, int y1) {
        x = x1;
        y = y1;
    }

    point(const point &p) {
        x = p.x;
        y = p.y;
    }

    point &operator=(const point &p) = default;

};

#endif //PISKWORKY_POINT_H
