#include "mapgraphicsview.h"

MapGraphicsView::MapGraphicsView(QObject *parent)
{
}

void MapGraphicsView::mousePressEvent(QMouseEvent *event)
{
  windowPointer->setTile(event->x(), event->y());
}

void MapGraphicsView::setWindow(TileViewer* window) {
  windowPointer = window;
}
