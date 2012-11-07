#include "tileviewer.h"
#include <iostream>
#include <QApplication>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <lcm/lcm-cpp.hpp>
#include "lcmtypes/cpp/lcmtypes/text_loco/tile_to_image_t.hpp"
#include "lcmtypes/cpp/lcmtypes/bot_core/image_t.hpp"
#include "handler.h"
#include "lcmthread.h"
#include <QImage>
#include <QObject>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  TileViewer w;
  w.show();

  lcm::LCM lcm_instance;

  // map from tile origins (represented as doubles) to a vector of timestamps
  // representing the images belonging to that tile
  map<double, vector<int64_t> >* mapTileOriginToImageTimestamp = new map<double, vector<int64_t> >;
  // vector of all tile origins seen
  vector<double>* allTileOrigins = new vector<double>;
  // map from tile origins to map coordinates (to handle mouse clicks on the map)
  map<double, int>* mapTileOriginToMapCoords = new map<double, int>;
  // map from an image timestamp to the image itself
  map<int64_t, QImage>* mapImageTimestampToImage = new map<int64_t, QImage>;
  map<int64_t, unsigned int>* mapImageTimestampToMapIndex = new map<int64_t, unsigned int>;

  if(!lcm_instance.good()) return 1;

  Handler handlerObject;
  handlerObject.mapTileOriginToImageTimestamp = mapTileOriginToImageTimestamp;
  handlerObject.allTileOrigins = allTileOrigins;
  handlerObject.mapTileOriginToMapCoords = mapTileOriginToMapCoords;
  handlerObject.mapImageTimestampToImage = mapImageTimestampToImage;
  handlerObject.mapImageTimestampToMapIndex = mapImageTimestampToMapIndex;

  w.mapTileOriginToImageTimestamp = mapTileOriginToImageTimestamp;
  w.allTileOrigins = allTileOrigins;
  w.mapTileOriginToMapCoords = mapTileOriginToMapCoords;
  w.mapImageTimestampToImage = mapImageTimestampToImage;
  w.mapImageTimestampToMapIndex = mapImageTimestampToMapIndex;

  handlerObject.windowPointer = &w;

  // handle LCM messages on the following channels
  lcm_instance.subscribe("TILE_TO_IMAGE_UTIMES", &Handler::handleImageTileAssoc, &handlerObject);
  lcm_instance.subscribe("CAMLCM_IMAGE", &Handler::handleImageFrame, &handlerObject);
  lcm_instance.subscribe("TILES_MAP", &Handler::handleMapImage, &handlerObject);

  // connect tile image receipt signals to the corresponding window update slot
  QObject::connect(&handlerObject, SIGNAL(receivedImageForTile(double)),
                   &w, SLOT(receivedImageForTile(double)));
  // connect a map image receipt signal to the corresponding window update slot
  QObject::connect(&handlerObject, SIGNAL(receivedMap()),
                   &w, SLOT(updateMap()));

  LCMThread lcmThread;
  lcmThread.setLCM(&lcm_instance);
  lcmThread.start();

  return a.exec();
}
