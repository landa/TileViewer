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
    map<double, vector<int64_t> >* tile_to_image_utimes = new map<double, vector<int64_t> >;
    vector<double>* tiles_seen = new vector<double>;
    map<double, int>* tiles_to_coords = new map<double, int>;
    map<int64_t, QImage>* image_utime_to_image = new map<int64_t, QImage>;

		if(!lcm_instance.good())
			return 1;

		Handler handlerObject;
		handlerObject.tile_to_image_utimes = tile_to_image_utimes;
		handlerObject.tiles_seen = tiles_seen;
		handlerObject.tiles_to_coords = tiles_to_coords;
		handlerObject.image_utime_to_image = image_utime_to_image;

		w.tile_to_image_utimes = tile_to_image_utimes;
		w.tiles_seen = tiles_seen;
		w.tiles_to_coords = tiles_to_coords;
		w.image_utime_to_image = image_utime_to_image;

		handlerObject.windowPointer = &w;

		lcm_instance.subscribe("TILE_TO_IMAGE_UTIMES", &Handler::handleMessage, &handlerObject);
		lcm_instance.subscribe("CAMLCM_IMAGE", &Handler::handleImage, &handlerObject);
		lcm_instance.subscribe("TILES_MAP", &Handler::handleMap, &handlerObject);

		QObject::connect(&handlerObject, SIGNAL(receivedImageForTile(double)),
										 &w, SLOT(receivedImageForTile(double)));
		QObject::connect(&handlerObject, SIGNAL(receivedMap()),
										 &w, SLOT(updateMap()));

		LCMThread lcmThread;
		lcmThread.setLCM(&lcm_instance);
		lcmThread.start();

    return a.exec();
}
