#ifndef HANDLER_H
#define HANDLER_H

#include <stdio.h>
#include <iostream>
#include <lcm/lcm-cpp.hpp>
#include "lcmtypes/cpp/lcmtypes/text_loco/tile_to_image_t.hpp"
#include "lcmtypes/cpp/lcmtypes/bot_core/image_t.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>
#include <QImage>
#include <tileviewer.h>

using namespace std;
using namespace cv;
using namespace bot_core;
using namespace text_loco;

/**
 * LCM Handler, used to process messages received over LCM
 * including images, image-tile associations, and map updates
 */
class Handler : public QObject
{

  Q_OBJECT

public:
  Handler() {}
  ~Handler() {}

  void handleImageTileAssoc(const lcm::ReceiveBuffer* rbuf,
                     const std::string& chan,
                     const text_loco::tile_to_image_t* msg);

  void handleImageFrame(const lcm::ReceiveBuffer* rbuf,
                   const std::string& chan,
                   const bot_core::image_t* msg);

  void handleMapImage(const lcm::ReceiveBuffer* rbuf,
                 const std::string& chan,
                 const bot_core::image_t* msg);

  map<double, vector<int64_t> >* mapTileOriginToImageTimestamp;
  vector<double>* allTileOrigins;
  map<double, int>* mapTileOriginToMapCoords;
  map<int64_t, QImage>* mapImageTimestampToImage;
  map<int64_t, unsigned int>* mapImageTimestampToMapIndex;
  TileViewer* windowPointer;

signals:
  void receivedImageForTile(double tileOrigin);
  void receivedMap();

};

#endif // HANDLER_H
