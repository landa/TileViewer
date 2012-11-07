#ifndef CLICKABLEGRAPHICSVIEW_H
#define CLICKABLEGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <tileviewer.h>
#include <iostream>

/**
 * Used to represent a clickable 2D map of the world with tiles.
 */
class MapGraphicsView : public QGraphicsView
{
  Q_OBJECT
public:
  explicit MapGraphicsView(QObject *parent = 0);
  void mousePressEvent(QMouseEvent *event);
  void setWindow(TileViewer* window);

  TileViewer* windowPointer;

signals:
  void mapResized(int x, int y);

public slots:

};

#endif // CLICKABLEGRAPHICSVIEW_H
