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

class Handler : public QObject
{

	Q_OBJECT

	public:
	Handler() {}
	~Handler() {}

  void handleMessage(const lcm::ReceiveBuffer* rbuf,
                     const std::string& chan,
                     const text_loco::tile_to_image_t* msg);

  void handleImage(const lcm::ReceiveBuffer* rbuf,
                     const std::string& chan,
                     const bot_core::image_t* msg);

  void handleMap(const lcm::ReceiveBuffer* rbuf,
                     const std::string& chan,
                     const bot_core::image_t* msg);

  map<double, vector<int64_t> >* tile_to_image_utimes;
  vector<double>* tiles_seen;
  map<double, int>* tiles_to_coords;
  map<int64_t, QImage>* image_utime_to_image;
  TileViewer* windowPointer;

	signals:
		void receivedImageForTile(double tileOrigin);
		void receivedMap();

};

#endif // HANDLER_H
