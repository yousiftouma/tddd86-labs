// Author: Viktor Holmgren, Yousif Touma
// A implementation of the Lab3A task.

#ifndef TILELIST_H
#define TILELIST_H

#include <QGraphicsScene>
#include "Tile.h"

/*
 * A TileList is an ordered collection of tiles stored using 0-based integer
 * indexing, using an array as the internal representation. A tile's index is also
 * the same as its z-index.
*/
class TileList {
public:

    /*
     * Constructs a new empty TileList
    */
    TileList();

    /*
     * Copy constructor
    */
    TileList(const TileList &other);

    /*
     * Copy assignment
    */
    TileList& operator=(const TileList &other);

    /*
     * Destructor that frees all memory allocated internally by the list
    */
    ~TileList();

    /*
     * Appends a tile to the end (top) of the list, expanding the list if
     * necessary
    */
    void addTile(Tile tile);

    /*
     * Draws all tiles in the list, starting with the bottom tile and
     * ending with the top tile.
    */
    void drawAll(QGraphicsScene* scene) const;

    /*
     * Returns the index of the top-most tile which covers the given coords.
     * If no tile is covering the coordinates, returns -1.
    */
    int indexOfTopTile(int x, int y) const;

    /*
     * Moves the top-most tile which covers the given coords to the bottom of
     * the list.
    */
    void lower(int x, int y);

    /*
     * Moves the top-most tile which covers the given coords to the top of
     * the list.
    */
    void raise(int x, int y);

    /*
     * Removes the top-most tile which covers the given coords, shifting all
     * tiles above down one index.
    */
    void remove(int x, int y);

    /*
     * Removes all tiles covering the given coords. Shifting all tiles above
     * down one index for every remove.
    */
    void removeAll(int x, int y);

private:
    int m_capacity = 10; // length of the array
    int m_size = 0; // number of tiles currently
    Tile* m_tiles = new Tile[m_capacity]; // array of tiles

    /*
     * Checks whether if the array is full, if so doubling the capacity.
    */
    void checkResize();

    /*
     * Shifts all tiles from 0 to pos one index to the right.
    */
    void shiftRight(int pos);

    /*
     * Shifts all tiles from m_size - 1 to pos one index to the left.
    */
    void shiftLeft(int pos);

    /*
     * Copies all attributes from other to this, does a deep copy of
     * the tiles.
    */
    void copyOther(const TileList &other);
};

#endif // TILELIST_H
