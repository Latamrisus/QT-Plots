#include "MainWindow.h"

#include <iostream>

MainWindow::MainWindow() : QMainWindow()
{
	graph = new QtDataVisualization::Q3DSurface();
	;
	graph->setAxisX(new QtDataVisualization::QValue3DAxis);
	graph->setAxisY(new QtDataVisualization::QValue3DAxis);
	graph->setAxisZ(new QtDataVisualization::QValue3DAxis);
	plot = new Plot();
	plot->fillSincProxy();
	plot->fillSincXZProxy();

	actSave = new QAction(style()->standardIcon(QStyle::SP_DialogSaveButton), "&Save", this);
	actSave->setShortcuts(QKeySequence::Save);
	actSave->setStatusTip("Save state");
	connect(actSave, &QAction::triggered, this, &MainWindow::doSave);

	actRevert = new QAction(style()->standardIcon(QStyle::SP_DialogResetButton), "&Revert", this);
	actRevert->setShortcuts(QKeySequence::Refresh);
	actRevert->setStatusTip("Revert state");
	connect(actRevert, &QAction::triggered, this, &MainWindow::doRevert);

	settings.setIniCodec("UTF-8");

	menu = this->menuBar()->addMenu("&Settings");
	menu->addAction(actSave);
	menu->addAction(actRevert);
}

MainWindow::~MainWindow() {}

void MainWindow::enableSincModel(bool enable)
{
	if (enable)
	{
		plot->sincSeries->setDrawMode(QtDataVisualization::QSurface3DSeries::DrawSurfaceAndWireframe);
		plot->sincSeries->setFlatShadingEnabled(true);

		graph->axisX()->setLabelFormat("%.2f");
		graph->axisZ()->setLabelFormat("%.2f");
		graph->axisX()->setRange(plot->sampleMin, plot->sampleMax);
		graph->axisY()->setRange(0.0f, 2.0f);
		graph->axisZ()->setRange(plot->sampleMin, plot->sampleMax);
		graph->axisX()->setLabelAutoRotation(30);
		graph->axisY()->setLabelAutoRotation(90);
		graph->axisZ()->setLabelAutoRotation(30);

		graph->removeSeries(plot->sincXZSeries);
		graph->addSeries(plot->sincSeries);

		xMinRange = plot->sampleMin;
		zMinRange = plot->sampleMin;
		stepX = (plot->sampleMax - plot->sampleMin) / float(plot->sampleCountX - 1);
		stepZ = (plot->sampleMax - plot->sampleMin) / float(plot->sampleCountZ - 1);
		suportiveAxisMinSliderX->setMaximum(plot->sampleCountX - 2);
		suportiveAxisMinSliderX->setValue(0);
		suportiveAxisMaxSliderX->setMaximum(plot->sampleCountX - 1);
		suportiveAxisMaxSliderX->setValue(plot->sampleCountX - 1);
		suportiveAxisMinSliderZ->setMaximum(plot->sampleCountZ - 2);
		suportiveAxisMinSliderZ->setValue(0);
		suportiveAxisMaxSliderZ->setMaximum(plot->sampleCountZ - 1);
		suportiveAxisMaxSliderZ->setValue(plot->sampleCountZ - 1);
	}
}

void MainWindow::enableSincXZModel(bool enable)
{
	if (enable)
	{
		plot->sincSeries->setDrawMode(QtDataVisualization::QSurface3DSeries::DrawSurfaceAndWireframe);
		plot->sincSeries->setFlatShadingEnabled(true);

		graph->axisX()->setLabelFormat("%.2f");
		graph->axisZ()->setLabelFormat("%.2f");
		graph->axisX()->setRange(plot->sampleMin, plot->sampleMax);
		graph->axisY()->setRange(0.0f, 2.0f);
		graph->axisZ()->setRange(plot->sampleMin, plot->sampleMax);
		graph->axisX()->setLabelAutoRotation(30);
		graph->axisY()->setLabelAutoRotation(90);
		graph->axisZ()->setLabelAutoRotation(30);

		graph->removeSeries(plot->sincSeries);
		graph->addSeries(plot->sincXZSeries);

		xMinRange = plot->sampleMin;
		zMinRange = plot->sampleMin;
		stepX = (plot->sampleMax - plot->sampleMin) / float(plot->sampleCountX - 1);
		stepZ = (plot->sampleMax - plot->sampleMin) / float(plot->sampleCountZ - 1);
		suportiveAxisMinSliderX->setMaximum(plot->sampleCountX - 2);
		suportiveAxisMinSliderX->setValue(0);
		suportiveAxisMaxSliderX->setMaximum(plot->sampleCountX - 1);
		suportiveAxisMaxSliderX->setValue(plot->sampleCountX - 1);
		suportiveAxisMinSliderZ->setMaximum(plot->sampleCountZ - 2);
		suportiveAxisMinSliderZ->setValue(0);
		suportiveAxisMaxSliderZ->setMaximum(plot->sampleCountZ - 1);
		suportiveAxisMaxSliderZ->setValue(plot->sampleCountZ - 1);
	}
}

void MainWindow::adjustXMin(int min)
{
	float minX = stepX * float(min) + xMinRange;

	int max = suportiveAxisMaxSliderX->value();
	if (min >= max)
	{
		max = min + 1;
		suportiveAxisMaxSliderX->setValue(max);
	}
	float maxX = stepX * max + xMinRange;

	setAxisXRange(minX, maxX);
}

void MainWindow::adjustXMax(int max)
{
	float maxX = stepX * float(max) + xMinRange;

	int min = suportiveAxisMinSliderX->value();
	if (max <= min)
	{
		min = max - 1;
		suportiveAxisMinSliderX->setValue(min);
	}
	float minX = stepX * min + xMinRange;

	setAxisXRange(minX, maxX);
}

void MainWindow::adjustZMin(int min)
{
	float minZ = stepZ * float(min) + zMinRange;

	int max = suportiveAxisMaxSliderZ->value();
	if (min >= max)
	{
		max = min + 1;
		suportiveAxisMaxSliderZ->setValue(max);
	}
	float maxZ = stepZ * max + zMinRange;

	setAxisZRange(minZ, maxZ);
}

void MainWindow::adjustZMax(int max)
{
	float maxX = stepZ * float(max) + zMinRange;

	int min = suportiveAxisMinSliderZ->value();
	if (max <= min)
	{
		min = max - 1;
		suportiveAxisMinSliderZ->setValue(min);
	}
	float minX = stepZ * min + zMinRange;

	setAxisZRange(minX, maxX);
}

void MainWindow::setAxisXRange(float min, float max)
{
	graph->axisX()->setRange(min, max);
}

void MainWindow::setAxisZRange(float min, float max)
{
	graph->axisZ()->setRange(min, max);
}

void MainWindow::handleGridToggle(bool checked)
{
	if (checked)
	{
		graph->activeTheme()->setGridEnabled(true);
	}
	else
	{
		graph->activeTheme()->setGridEnabled(false);
	}
}

void MainWindow::handleLabelToggle(bool checked)
{
	if (checked)
	{
		graph->activeTheme()->setLabelTextColor(Qt::black);
		labelBorderCheckBox->setEnabled(true);
		labelBorderCheckBox->setChecked(true);
	}
	else
	{
		graph->activeTheme()->setLabelTextColor(Qt::white);
		labelBorderCheckBox->setChecked(false);
		labelBorderCheckBox->setEnabled(false);
	}
}

void MainWindow::handleLabelBorderToggle(bool checked)
{
	if (checked)
	{
		graph->activeTheme()->setLabelBorderEnabled(true);
	}
	else
	{
		graph->activeTheme()->setLabelBorderEnabled(false);
	}
}

void MainWindow::setYellowToBlackGradient()
{
	QLinearGradient gr;
	gr.setColorAt(1.0, Qt::yellow);
	gr.setColorAt(0.67, Qt::red);
	gr.setColorAt(0.33, Qt::darkMagenta);
	gr.setColorAt(0.0, Qt::black);
	firstGr = true;
	secondGr = false;
	graph->seriesList().at(0)->setBaseGradient(gr);
	graph->seriesList().at(0)->setColorStyle(QtDataVisualization::Q3DTheme::ColorStyleRangeGradient);
}

void MainWindow::setYellowToPurpleGradient()
{
	QLinearGradient gr;
	gr.setColorAt(0.0, Qt::yellow);
	gr.setColorAt(0.5, Qt::green);
	gr.setColorAt(0.67, Qt::blue);
	gr.setColorAt(1.0, Qt::magenta);
	firstGr = false;
	secondGr = true;
	graph->seriesList().at(0)->setBaseGradient(gr);
	graph->seriesList().at(0)->setColorStyle(QtDataVisualization::Q3DTheme::ColorStyleRangeGradient);
}

void MainWindow::pointSelectionEnabled(bool is)
{
	is ? graph->setSelectionMode(QtDataVisualization::QAbstract3DGraph::SelectionNone)
	   : graph->setSelectionMode(QtDataVisualization::QAbstract3DGraph::SelectionItem);
}

void MainWindow::screenBuild()
{
	windowContainer = QWidget::createWindowContainer(graph);
	QSize screenSize = graph->screen()->size();
	windowContainer->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.5));
	windowContainer->setMaximumSize(screenSize);
	windowContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	windowContainer->setFocusPolicy(Qt::StrongFocus);
	widget = new QWidget();
	QHBoxLayout *hLayout = new QHBoxLayout(widget);
	vLayout = new QVBoxLayout();
	hLayout->addWidget(windowContainer, 1);
	hLayout->addLayout(vLayout);
	vLayout->setAlignment(Qt::AlignTop);
	widget->setWindowTitle(QStringLiteral("Sinc by kstr"));
}

void MainWindow::displayStyle()
{
	QGroupBox *appearence = new QGroupBox(QStringLiteral("Display"));
	gridCheckBox = new QCheckBox("Show Grid");
	gridCheckBox->setChecked(true);
	labelCheckBox = new QCheckBox("Show Label");
	labelCheckBox->setChecked(true);
	labelBorderCheckBox = new QCheckBox("Show Label Border");
	labelBorderCheckBox->setChecked(true);
	QVBoxLayout *checkBoxes = new QVBoxLayout;
	checkBoxes->addWidget(gridCheckBox);
	checkBoxes->addWidget(labelCheckBox);
	checkBoxes->addWidget(labelBorderCheckBox);
	appearence->setLayout(checkBoxes);
	vLayout->addWidget(appearence);
}

void MainWindow::graphChoose()
{
	QGroupBox *modelGroupBox = new QGroupBox(QStringLiteral("Plot"));
	sincMode = new QRadioButton(widget);
	sincMode->setText(QStringLiteral("Sinc1"));
	sincMode->setChecked(false);
	sincXZMode = new QRadioButton(widget);
	sincXZMode->setText(QStringLiteral("Sinc2"));
	sincXZMode->setChecked(false);
	QVBoxLayout *modelVBox = new QVBoxLayout;
	modelVBox->addWidget(sincMode);
	modelVBox->addWidget(sincXZMode);
	modelGroupBox->setLayout(modelVBox);
	vLayout->addWidget(modelGroupBox);
}

void MainWindow::pointChoose()
{
	QGroupBox *pointMode = new QGroupBox(QStringLiteral("Point"));
	QVBoxLayout *pointLayout = new QVBoxLayout;
	point = new QCheckBox("Disable point selection");
	pointLayout->addWidget(point);
	pointMode->setLayout(pointLayout);
	vLayout->addWidget(pointMode);
}

void MainWindow::setSliders()
{
	QVBoxLayout *sliderV = new QVBoxLayout;
	QGroupBox *sliderGroupBox = new QGroupBox(QStringLiteral("Range"));
	axisXMinSlider = new QSlider(Qt::Horizontal, widget);
	axisXMinSlider->setMinimum(0);
	axisXMinSlider->setTickInterval(1);
	axisXMinSlider->setEnabled(true);
	axisXMaxSlider = new QSlider(Qt::Horizontal, widget);
	axisXMaxSlider->setMinimum(1);
	axisXMaxSlider->setTickInterval(1);
	axisXMaxSlider->setEnabled(true);
	axisZMinSlider = new QSlider(Qt::Horizontal, widget);
	axisZMinSlider->setMinimum(0);
	axisZMinSlider->setTickInterval(1);
	axisZMinSlider->setEnabled(true);
	axisZMaxSlider = new QSlider(Qt::Horizontal, widget);
	axisZMaxSlider->setMinimum(1);
	axisZMaxSlider->setTickInterval(1);
	axisZMaxSlider->setEnabled(true);
	sliderV->addWidget(new QLabel(QStringLiteral("Column range")));
	sliderV->addWidget(axisXMinSlider);
	sliderV->addWidget(axisXMaxSlider);
	sliderV->addWidget(new QLabel(QStringLiteral("Row range")));
	sliderV->addWidget(axisZMinSlider);
	sliderV->addWidget(axisZMaxSlider);
	sliderGroupBox->setLayout(sliderV);
	vLayout->addWidget(sliderGroupBox);
}

void MainWindow::setStep()
{
	QGroupBox *stepSets = new QGroupBox(QStringLiteral("Steps"));
	QVBoxLayout *stepsV = new QVBoxLayout;
	stepsX = new QSpinBox(widget);
	stepsX->setEnabled(true);
	stepsX->setValue(100);
	stepsX->setRange(1, 200);
	stepsX->setSingleStep(1);
	stepsZ = new QSpinBox(widget);
	stepsZ->setEnabled(true);
	stepsZ->setValue(100);
	stepsZ->setRange(1, 200);
	stepsZ->setSingleStep(1);
	stepsV->addWidget(new QLabel(QStringLiteral("X axis")));
	stepsV->addWidget(stepsX);
	stepsV->addWidget(new QLabel(QStringLiteral("Z axis")));
	stepsV->addWidget(stepsZ);
	stepSets->setLayout(stepsV);
	vLayout->addWidget(stepSets);
}

void MainWindow::setupGradient()
{
	QGroupBox *colorGroupBox = new QGroupBox(QStringLiteral("Custom gradient"));
	QLinearGradient grBtoY(0, 0, 1, 100);
	grBtoY.setColorAt(1.0, Qt::yellow);
	grBtoY.setColorAt(0.67, Qt::red);
	grBtoY.setColorAt(0.33, Qt::darkMagenta);
	grBtoY.setColorAt(0.0, Qt::black);
	QPixmap pm(24, 100);
	QPainter pmp(&pm);
	pmp.setBrush(QBrush(grBtoY));
	pmp.setPen(Qt::NoPen);
	pmp.drawRect(0, 0, 24, 100);
	gradientBtoY = new QPushButton(widget);
	gradientBtoY->setIcon(QIcon(pm));
	gradientBtoY->setIconSize(QSize(24, 100));
	QLinearGradient grYtoM(0, 0, 1, 100);
	grYtoM.setColorAt(0.0, Qt::magenta);
	grYtoM.setColorAt(0.25, Qt::blue);
	grYtoM.setColorAt(0.5, Qt::green);
	grYtoM.setColorAt(1.0, Qt::yellow);
	pmp.setBrush(QBrush(grYtoM));
	pmp.drawRect(0, 0, 24, 100);
	gradientYtoM = new QPushButton(widget);
	gradientYtoM->setIcon(QIcon(pm));
	gradientYtoM->setIconSize(QSize(24, 100));
	QHBoxLayout *colorHBox = new QHBoxLayout;
	colorHBox->addWidget(gradientBtoY);
	colorHBox->addWidget(gradientYtoM);
	colorGroupBox->setLayout(colorHBox);
	vLayout->addWidget(colorGroupBox);
	widget->show();
}

void MainWindow::connectAll()
{
	QObject::connect(sincXZMode, &QRadioButton::toggled, this, &MainWindow::enableSincXZModel);
	QObject::connect(sincMode, &QRadioButton::toggled, this, &MainWindow::enableSincModel);
	QObject::connect(axisXMinSlider, &QSlider::valueChanged, this, &MainWindow::adjustXMin);
	QObject::connect(axisXMaxSlider, &QSlider::valueChanged, this, &MainWindow::adjustXMax);
	QObject::connect(axisZMinSlider, &QSlider::valueChanged, this, &MainWindow::adjustZMin);
	QObject::connect(axisZMaxSlider, &QSlider::valueChanged, this, &MainWindow::adjustZMax);
	QObject::connect(gradientBtoY, &QPushButton::pressed, this, &MainWindow::setYellowToBlackGradient);
	QObject::connect(gradientYtoM, &QPushButton::pressed, this, &MainWindow::setYellowToPurpleGradient);
	QObject::connect(gridCheckBox, &QCheckBox::toggled, this, &MainWindow::handleGridToggle);
	QObject::connect(labelCheckBox, &QCheckBox::toggled, this, &MainWindow::handleLabelToggle);
	QObject::connect(labelBorderCheckBox, &QCheckBox::toggled, this, &MainWindow::handleLabelBorderToggle);
	QObject::connect(point, &QCheckBox::toggled, this, &MainWindow::pointSelectionEnabled);
	QObject::connect(stepsX, QOverload< int >::of(&QSpinBox::valueChanged), plot, &Plot::changeSampleCountX);
	QObject::connect(stepsZ, QOverload< int >::of(&QSpinBox::valueChanged), plot, &Plot::changeSampleCountZ);
}

void MainWindow::setRange()
{
	setAxisMinSliderX(axisXMinSlider);
	setAxisMaxSliderX(axisXMaxSlider);
	setAxisMinSliderZ(axisZMinSlider);
	setAxisMaxSliderZ(axisZMaxSlider);
}

// void MainWindow::setupSettings()
//{

//}

void MainWindow::doSave()
{
	settings.setValue("gridCheckBox", gridCheckBox->isChecked());
	settings.setValue("labelCheckBox", labelCheckBox->isChecked());
	settings.setValue("labelBorderCheckBox", labelBorderCheckBox->isChecked());
	settings.setValue("sincMode", sincMode->isChecked());
	settings.setValue("sincXZMode", sincXZMode->isChecked());
	settings.setValue("point", point->isChecked());
	settings.setValue("stepsX", stepsX->value());
	settings.setValue("axisMinSliderX", axisXMinSlider->value());
	settings.setValue("axisMaxSliderX", axisXMaxSlider->value());
	settings.setValue("stepsZ", stepsZ->value());
	settings.setValue("axisMinSliderZ", axisZMinSlider->value());
	settings.setValue("axisMaxSliderZ", axisZMaxSlider->value());
	settings.setValue("firstGr", firstGr);
	settings.setValue("secondGr", secondGr);
}

void MainWindow::doRevert()
{
	if (settings.contains("gridCB"))
	{
		gridCheckBox->setChecked(settings.value("gridCheckBox").toBool());
	}
	if (settings.contains("labelsCB"))
	{
		labelCheckBox->setChecked(settings.value("labelCheckBox").toBool());
	}
	if (settings.contains("labelBordersCB"))
	{
		labelBorderCheckBox->setChecked(settings.value("labelBorderCheckBox").toBool());
	}
	if (settings.contains("sincMode"))
	{
		sincMode->setChecked(settings.value("sincMode").toBool());
	}
	if (settings.contains("multSincModelRB"))
	{
		sincXZMode->setChecked(settings.value("sincXZMode").toBool());
	}
	if (settings.contains("modeNoneRB"))
	{
		point->setChecked(settings.value("point").toBool());
	}
	if (settings.contains("stepsX") && settings.value("stepsX").canConvert< int >())
	{
		stepsX->setValue(settings.value("stepsX").toInt());
	}
	if (settings.contains("axisMinSliderX") && settings.value("axisMinSliderX").canConvert< int >())
	{
		axisXMinSlider->setValue(settings.value("axisMinSliderX").toInt());
	}
	if (settings.contains("axisMaxSliderX") && settings.value("axisMaxSliderX").canConvert< int >())
	{
		axisXMaxSlider->setValue(settings.value("axisMaxSliderX").toInt());
	}
	if (settings.contains("stepsZ") && settings.value("stepsZ").canConvert< int >())
	{
		stepsZ->setValue(settings.value("stepsZ").toInt());
	}
	if (settings.contains("axisMinSliderZ") && settings.value("axisMinSliderZ").canConvert< int >())
	{
		axisZMinSlider->setValue(settings.value("axisMinSliderZ").toInt());
	}
	if (settings.contains("axisMaxSliderZ") && settings.value("axisMaxSliderZ").canConvert< int >())
	{
		axisZMaxSlider->setValue(settings.value("axisMaxSliderZ").toInt());
	}
	if (settings.contains("firstGr"))
	{
		if (firstGr)
		{
			gradientBtoY->click();
		}
	}
	if (settings.contains("secondGr"))
	{
		if (secondGr)
		{
			gradientYtoM->click();
		}
	}
}

void MainWindow::makeWindow()
{
	screenBuild();
	displayStyle();
	graphChoose();
	pointChoose();
	setStep();
	setSliders();
	setupGradient();
	connectAll();
	setRange();
	doRevert();
	sincMode->setChecked(true);
}
