#include "tileviewer.h"
#include "ui_tileviewer.h"

TileViewer::TileViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TileViewer)
{
		ui->setupUi(this);
		maps = new vector<QImage>;
		ui->mapView->setWindow(this);
		selectedOrigin = 0;
}

TileViewer::~TileViewer()
{
    delete ui;
}

void TileViewer::receivedImageForTile(double tileOrigin) {
	double selectedTile = (*tiles_seen)[selectedOrigin];
	if (tileOrigin == selectedTile) {
		updateImage(tileOrigin);
	}
}

void TileViewer::setTile(int x, int y) {
  int width = ui->mapView->scene()->width();
  int height = ui->mapView->scene()->height();
  if (width == 0 || height == 0) return;
  //x -= width/2;
  //x = floor(x+0.5);
  cerr << "clicked: " << x << endl;
  double lowestDist = 9999999;
  for (size_t ii = 0; ii < (*tiles_seen).size(); ++ii) {
    double dist = fabs((*tiles_seen)[ii] - x);
    if (dist < lowestDist) {
      lowestDist = dist;
      selectedOrigin = ii;
    }
  }
  updateImage((*tiles_seen)[selectedOrigin]);
}

void TileViewer::updateImage(double tileOrigin) {
  cerr << "selected origin = " << tileOrigin << endl;
  vector<int64_t> image_utimes = (*tile_to_image_utimes)[tileOrigin];
  if (image_utimes.size() == 0) return;
  int chosen_image = MAX(0, image_utimes.size() - 1);
  int64_t image_utime = image_utimes[chosen_image];
  QImage qimage = (*image_utime_to_image)[image_utime];
  if (qimage.width() == 0 || qimage.height() == 0) return;
  qimage.rgbSwapped();
  QGraphicsScene* scene = new QGraphicsScene();
  QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(qimage));
  scene->addItem(item);
  ui->frameView->setScene(scene);
  ui->frameView->show();
}

void TileViewer::updateMap() {
  QImage mapImage = maps->back();
  //maps->pop_back();
	if (mapImage.width() == 0 || mapImage.height() == 0) return;
	QGraphicsScene* scene = new QGraphicsScene();
	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(mapImage));
	scene->addItem(item);
	ui->mapView->setScene(scene);
	ui->mapView->show();
}

void TileViewer::setFrame(int position) {
	QImage mapImage = maps->back();
	cerr << position << endl;
}
