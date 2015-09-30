// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "TileList.h"

TileList::TileList() {}

TileList::~TileList()
{
    delete[] m_tiles;
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
    return 4;
    // TODO: write this member
}

void TileList::raise(int x, int y)
{
    Tile to_copy;
    for (int pos = m_size - 1; pos >= 0; --pos) {
        if (m_tiles[pos].contains(x, y)) {
            to_copy = m_tiles[pos];

            for (int i = pos; i < m_size - 1; ++i) {
                m_tiles[i] = m_tiles[i+1];
            }
            m_tiles[m_size-1] = to_copy;
            return;
        }
    }
}

void TileList::lower(int x, int y)
{
    Tile to_copy;
    for (int pos = m_size - 1; pos >= 0; --pos) {
        if (m_tiles[pos].contains(x, y)) {
            to_copy = m_tiles[pos];

            for (int i = pos - 1; i >= 0; --i) {
                m_tiles[i+1] = m_tiles[i];
            }
            m_tiles[0] = to_copy;
            return;
        }
    }
}

void TileList::remove(int x, int y)
{
    // TODO: write this member
}

void TileList::removeAll(int x, int y)
{
}

void TileList::checkResize() {
    if (m_size == m_capacity) { // out of space
        Tile* expanded_list = new Tile[m_capacity * 2];
        for (int i = 0; i < m_size; ++i) {
            expanded_list[i] = m_tiles[i];
        }
        delete[] m_tiles; // free old list
        m_tiles = expanded_list;
        m_capacity *= 2;
    }
}
