#include "plot.h"

const float Plot::sampleMax = 10.0f;
const float Plot::sampleMin = -10.0f;
int Plot::sampleCountX = 100;
int Plot::sampleCountZ = 100;

Plot::Plot()
{
	sincProxy = new QtDataVisualization::QSurfaceDataProxy();
	sincSeries = new QtDataVisualization::QSurface3DSeries(sincProxy);
	sincXZProxy = new QtDataVisualization::QSurfaceDataProxy();
	sincXZSeries = new QtDataVisualization::QSurface3DSeries(sincXZProxy);
}

Plot::~Plot()
{
	delete sincProxy;
	delete sincSeries;
	delete sincXZProxy;
	delete sincXZSeries;
}

void Plot::fillSincProxy()
{
	float stepX = (sampleMax - sampleMin) / float(sampleCountX - 1);
	float stepZ = (sampleMax - sampleMin) / float(sampleCountZ - 1);

	QtDataVisualization::QSurfaceDataArray *dataArray = new QtDataVisualization::QSurfaceDataArray;
	dataArray->reserve(sampleCountZ);
	for (int i = 0; i < sampleCountZ; i++)
	{
		QtDataVisualization::QSurfaceDataRow *newRow = new QtDataVisualization::QSurfaceDataRow(sampleCountX);
		float z = qMin(sampleMax, (i * stepZ + sampleMin));
		int index = 0;
		for (int j = 0; j < sampleCountX; j++)
		{
			float x = qMin(sampleMax, (j * stepX + sampleMin));
			float R = qSqrt(z * z + x * x) + 0.01f;
			float y = (qSin(R) / R + 0.24f) * 1.61f;
			(*newRow)[index++].setPosition(QVector3D(x, y, z));
		}
		*dataArray << newRow;
	}

	sincProxy->resetArray(dataArray);
}

void Plot::fillSincXZProxy()
{
	float stepX = (sampleMax - sampleMin) / float(sampleCountX - 1);
	float stepZ = (sampleMax - sampleMin) / float(sampleCountZ - 1);

	QtDataVisualization::QSurfaceDataArray *dataArray = new QtDataVisualization::QSurfaceDataArray;
	dataArray->reserve(sampleCountZ);
	for (int i = 0; i < sampleCountZ; i++)
	{
		QtDataVisualization::QSurfaceDataRow *newRow = new QtDataVisualization::QSurfaceDataRow(sampleCountX);
		float z = qMin(sampleMax, (i * stepZ + sampleMin));
		int index = 0;
		for (int j = 0; j < sampleCountX; j++)
		{
			float x = qMin(sampleMax, (j * stepX + sampleMin));
			float sincX = (x != 0) ? (qSin(x) / x) : 1.0f;
			float sincZ = (z != 0) ? (qSin(z) / z) : 1.0f;
			float value = sincX * sincZ + 0.2f;
			(*newRow)[index++].setPosition(QVector3D(x, value, z));
		}
		*dataArray << newRow;
	}

	sincXZProxy->resetArray(dataArray);
}

void Plot::changeSampleCountX(int newStep)
{
	sampleCountX = newStep;
	fillSincProxy();
	fillSincXZProxy();
}
void Plot::changeSampleCountZ(int newStep)
{
	sampleCountZ = newStep;
	fillSincProxy();
	fillSincXZProxy();
}
