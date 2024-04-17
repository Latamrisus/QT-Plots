#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "plot.h"
#include <QtGui/QPainter>
#include <QtGui/QScreen>

#include <Q3DSurface>
#include <QCheckBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QRadioButton>
#include <QSettings>
#include <QSlider>
#include <QSpinBox>
#include <QStyle>
#include <QSurface3DSeries>
#include <QToolBar>
#include <QVBoxLayout>

class QAction;

class MainWindow : public QMainWindow
{
	Q_OBJECT
	QSettings settings;

  public:
	explicit MainWindow();
	~MainWindow();
	void makeWindow();

  public slots:
	void enableSincXZModel(bool enable);
	void enableSincModel(bool enable);
	void adjustXMin(int min);
	void adjustXMax(int max);
	void adjustZMin(int min);
	void adjustZMax(int max);
	void setYellowToBlackGradient();
	void setYellowToPurpleGradient();
	void handleGridToggle(bool checked);
	void handleLabelBorderToggle(bool checked);
	void handleLabelToggle(bool checked);
	void pointSelectionEnabled(bool is);
	void doSave();
	void doRevert();

  private:
	QWidget *windowContainer;
	QWidget *widget;
	QVBoxLayout *vLayout;
	QCheckBox *gridCheckBox, *labelCheckBox, *labelBorderCheckBox, *point;
	QRadioButton *sincMode, *sincXZMode;
	QSlider *axisXMinSlider, *axisXMaxSlider, *axisZMinSlider, *axisZMaxSlider;
	QPushButton *gradientBtoY, *gradientYtoM;
	Plot *plot;
	QtDataVisualization::Q3DSurface *graph;
	QAction *actRevert, *actSave;
	QSlider *suportiveAxisMinSliderX;
	QSlider *suportiveAxisMaxSliderX;
	QSlider *suportiveAxisMinSliderZ;
	QSlider *suportiveAxisMaxSliderZ;
	QSpinBox *stepsX, *stepsZ;
	QMenu *menu;
	QToolBar *toolBar;
	bool firstGr, secondGr;
	float xMinRange, zMinRange, stepX, stepZ;
	void screenBuild();
	void displayStyle();
	void graphChoose();
	void pointChoose();
	void setSliders();
	void setupGradient();
	void connectAll();
	void setRange();
	void setStep();
	void langSelec();
	void setAxisXRange(float min, float max);
	void setAxisZRange(float min, float max);
	void setAxisMinSliderX(QSlider *slider) { suportiveAxisMinSliderX = slider; }
	void setAxisMaxSliderX(QSlider *slider) { suportiveAxisMaxSliderX = slider; }
	void setAxisMinSliderZ(QSlider *slider) { suportiveAxisMinSliderZ = slider; }
	void setAxisMaxSliderZ(QSlider *slider) { suportiveAxisMaxSliderZ = slider; }
};

#endif	  // MAINWINDOW_H
