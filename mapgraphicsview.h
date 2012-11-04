#ifndef CLICKABLEGRAPHICSVIEW_H
#define CLICKABLEGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <tileviewer.h>
#include <iostream>

class ClickableGraphicsView : public QGraphicsView
{
  Q_OBJECT
public:
  explicit ClickableGraphicsView(QObject *parent = 0);
  void mousePressEvent(QMouseEvent *event);
  void setWindow(TileViewer* window);

  TileViewer* windowPointer;
  
signals:
  
public slots:
  
};

#endif // CLICKABLEGRAPHICSVIEW_H
