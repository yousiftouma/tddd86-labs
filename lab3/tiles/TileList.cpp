// Author: Viktor Holmgren, Yousif Touma
// A implementation of the Lab3A task.

#include "TileList.h"

TileList::TileList() {}

TileList::TileList(const TileList &other) {
    copyOther(other);
}

TileList::~TileList()
{
    delete[] m_tiles; // free memory
}

TileList& TileList::operator =(const TileList &other) {
    if (this != &other) {
        delete[] m_tiles;
        copyOther(other);
    }
    return *this;
}

void TileList::addTile(Tile tile)
{
    checkResize();
    m_tiles[m_size] = tile;
    ++m_size;
}

void TileList::drawAll(QGraphicsScene* scene) const
{
    for (int i = 0; i < m_size; ++i) {
        m_tiles[i].draw(scene);
    }
}

int TileList::indexOfTopTile(int x, int y) const
{
    for (int i = m_size - 1; i >= 0; --i) {
        if (m_tiles[i].contains(x, y)) return i;
    }
    return -1; // no tile is covering x,y
}

void TileList::raise(int x, int y)
{
    int index = indexOfTopTile(x, y);
    // make sure that a tile covering x,y exists
    if (index != -1) {
        Tile to_copy = m_tiles[index];
        shiftLeft(index);
        m_tiles[m_size-1] = to_copy;
    }
}

void TileList::lower(int x, int y)
{
    int index = indexOfTopTile(x, y);
    // make sure that a tile covering x,y exists
    if (index != -1) {
        Tile to_copy = m_tiles[index];
        shiftRight(index);
        m_tiles[0] = to_copy;
    }
}

void TileList::remove(int x, int y)
{
    int index = indexOfTopTile(x, y);

    if (index != -1) {
        shiftLeft(index);
        --m_size;
    }
}

void TileList::removeAll(int x, int y)
{
    while (indexOfTopTile(x, y) != -1) {
        remove(x, y);
    }
}

void TileList::checkResize() {
    if (m_size == m_capacity) { // out of space

        int new_size = m_capacity * 2;
        Tile* expanded_list = new Tile[new_size];
        for (int i = 0; i < m_size; ++i) {
            expanded_list[i] = m_tiles[i];
        }
        delete[] m_tiles; // free old list
        m_tiles = expanded_list;
        m_capacity = new_size;
    }
}

void TileList::shiftLeft(int pos) {
    for (int i = pos; i < m_size - 1; ++i) {
        m_tiles[i] = m_tiles[i+1];
    }
}

void TileList::shiftRight(int pos) {
    for (int i = pos - 1; i >= 0; --i) {
        m_tiles[i+1] = m_tiles[i];
    }
}

void TileList::copyOther(const TileList &other) {
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_tiles = new Tile[m_capacity]; // deep copy
    for (int i = 0; i < m_size; i++) {
            m_tiles[i] = other.m_tiles[i];
    }
}


