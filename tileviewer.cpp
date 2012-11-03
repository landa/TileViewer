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
		QObject::connect(ui->frameChoice, SIGNAL(valueChanged(int)),
										 this, SLOT(setFrame(int)));
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
  double lowestDist = 9999999;
  for (size_t ii = 0; ii < (*tiles_seen).size(); ++ii) {
    double dist = fabs((*tiles_seen)[ii] - x);
    if (dist < lowestDist) {
      lowestDist = dist;
      selectedOrigin = ii;
    }
  }
  updateImage((*tiles_seen)[selectedOrigin]);
  updateMap();
}

void TileViewer::updateImage(double tileOrigin) {
  // display the image
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
  ui->frameView->setBackgroundBrush(QBrush(QColor(144, 133, 134), Qt::SolidPattern));
  ui->frameView->setScene(scene);
  ui->frameView->show();
  // update the slider
  ui->frameChoice->blockSignals(true);
  ui->frameChoice->setMinimum(1);
  ui->frameChoice->setMaximum(image_utimes.size());
  ui->frameChoice->setValue(chosen_image+1);
  ui->frameChoice->blockSignals(false);
  stringstream labelValue;
  labelValue << "Frame " << (chosen_image+1) << "/" << image_utimes.size();
  ui->frameLabel->setText(labelValue.str().c_str());
}

void TileViewer::updateMap() {
  QImage mapImage = maps->back();
  //maps->pop_back();
	if (mapImage.width() == 0 || mapImage.height() == 0) return;
	QGraphicsScene* scene = new QGraphicsScene();
	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(mapImage));
	scene->addItem(item);
	double origin = (*tiles_seen)[selectedOrigin];
	int x_c = origin;
	int y_c = (*tiles_to_coords)[origin];
	scene->addRect(x_c - 10, y_c - 10, 20, 20);
	ui->mapView->setScene(scene);
	ui->mapView->show();
}

void TileViewer::setFrame(int position) {
  cerr << "!!!!!! set frame at " << position << endl;
  // display the image
  double selectedTile = (*tiles_seen)[selectedOrigin];
  vector<int64_t> image_utimes = (*tile_to_image_utimes)[selectedTile];
  if (image_utimes.size() == 0) return;
  int chosen_image = position-1;
  int64_t image_utime = image_utimes[chosen_image];
  QImage qimage = (*image_utime_to_image)[image_utime];
  cerr << "checking width and height..." << endl;
  if (qimage.width() == 0 || qimage.height() == 0) return;
  cerr << "displaying image!!!" << endl;
  QGraphicsScene* scene = new QGraphicsScene();
  QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(qimage));
  scene->addItem(item);
  ui->frameView->setScene(scene);
  ui->frameView->show();
}
