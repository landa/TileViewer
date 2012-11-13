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

  /**
   * Process image timestamp --> tile association LCM messages.
   */
  void handleImageTileAssoc(const lcm::ReceiveBuffer* rbuf,
                     const std::string& chan,
                     const text_loco::tile_to_image_t* msg);

  /**
   * Process image LCM messages.
   */
  void handleImageFrame(const lcm::ReceiveBuffer* rbuf,
                   const std::string& chan,
                   const bot_core::image_t* msg);

  /**
   * Process map image LCM messages.
   */
  void handleMapImage(const lcm::ReceiveBuffer* rbuf,
                 const std::string& chan,
                 const bot_core::image_t* msg);

  // store tile --> image timestamps
  map<double, vector<int64_t> >* mapTileOriginToImageTimestamp;

  // store a list of all tile origins
  vector<double>* allTileOrigins; // TODO(landa): change this to a QSet

  // tile origin --> map coords
  map<double, int>* mapTileOriginToMapCoords;

  // image timestamp --> image
  map<int64_t, Mat*>* mapImageTimestampToImage;

  // image timestamp --> map index
  map<int64_t, unsigned int>* mapImageTimestampToMapIndex;

  // pointer to the ui
  TileViewer* windowPointer;

signals:
  void receivedImageForTile(double tileOrigin);
  void receivedMap();

};

#endif // HANDLER_H
