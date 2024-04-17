#ifndef PLOT_H
#define PLOT_H

#include <QtCore/qmath.h>

#include <Q3DSurface>
#include <QMainWindow>
#include <QObject>
#include <QSurfaceDataProxy>
#include <QWidget>

class Plot : public QWidget
{
	Q_OBJECT

  public:
	static int sampleCountX;
	static int sampleCountZ;
	static const float sampleMin;
	static const float sampleMax;

	Plot();
	~Plot();
	QtDataVisualization::QSurfaceDataProxy *sincProxy;
	QtDataVisualization::QSurfaceDataProxy *sincXZProxy;
	QtDataVisualization::QSurface3DSeries *sincSeries;
	QtDataVisualization::QSurface3DSeries *sincXZSeries;
	void fillSincProxy();
	void fillSincXZProxy();

  public slots:
	void changeSampleCountX(int newStep);
	void changeSampleCountZ(int newStep);
};

#endif	  // PLOT_H
