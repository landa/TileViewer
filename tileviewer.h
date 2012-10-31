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

using namespace std;
using namespace bot_core;
using namespace text_loco;

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
    void setFrame(int position);
    void setTile(int x, int y);

		map<double, vector<int64_t> >* tile_to_image_utimes;
		vector<double>* tiles_seen;
		map<int64_t, QImage>* image_utime_to_image;
		vector<QImage>* maps;
		double selectedOrigin;

public slots:
	void receivedImageForTile(double tileOrigin);
	void updateMap();

private:
    Ui::TileViewer *ui;
};

#endif // TILEVIEWER_H
