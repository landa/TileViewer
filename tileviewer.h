#ifndef TILEVIEWER_H
#define TILEVIEWER_H

#include <stdio.h>
#include <iostream>
#include <QMainWindow>
#include <cmath>
#include <lcm/lcm-cpp.hpp>
#include "lcmtypes/cpp/lcmtypes/text_loco/tile_to_image_t.hpp"
#include "lcmtypes/cpp/lcmtypes/bot_core/image_t.hpp"
#include <QImage>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QScrollBar>

using namespace std;
using namespace bot_core;
using namespace text_loco;
using namespace cv;

namespace Ui {
  class TileViewer;
}

class TileViewer : public QMainWindow
{
  Q_OBJECT

public:
  explicit TileViewer(QWidget *parent = 0);
  ~TileViewer();
  void updateImage(double tileOrigin);
  void setTile(int x, int y);

  map<double, vector<int64_t> >* mapTileOriginToImageTimestamp;
  vector<double>* allTileOrigins;
  map<double, int>* mapTileOriginToMapCoords;
  map<int64_t, Mat*>* mapImageTimestampToImage;
  map<int64_t, unsigned int>* mapImageTimestampToMapIndex;
  vector<QImage>* maps;
  double selectedOrigin;

public slots:
  void receivedImageForTile(double tileOrigin);
  void updateMap(int mapIndex = -1);
  void setFrame(int position);

private:
  Ui::TileViewer *ui;
};

#endif // TILEVIEWER_H
