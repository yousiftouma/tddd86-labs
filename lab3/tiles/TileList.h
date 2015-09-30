// This is the .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef TILELIST_H
#define TILELIST_H

#include <QGraphicsScene>
#include "Tile.h"

/*
 *
 *
 *
 *
 *
*/
class TileList {
public:
    TileList();
    ~TileList();
    void addTile(Tile tile);
    void drawAll(QGraphicsScene* scene) const;
    int indexOfTopTile(int x, int y) const;
    void lower(int x, int y);
    void raise(int x, int y);
    void remove(int x, int y);
    void removeAll(int x, int y);

private:
    int m_capacity = 10;
    int m_size = 0;
    Tile* m_tiles = new Tile[m_capacity];

    void checkResize();
    void shiftList(int x, int y, bool dir_right);
};

#endif // TILELIST_H
