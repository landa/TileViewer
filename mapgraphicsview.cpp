#include "clickablegraphicsview.h"

ClickableGraphicsView::ClickableGraphicsView(QObject *parent)
{
}

void ClickableGraphicsView::mousePressEvent(QMouseEvent *event)
{
  windowPointer->setTile(event->x(), event->y());
}

void ClickableGraphicsView::setWindow(TileViewer* window) {
  windowPointer = window;
}
