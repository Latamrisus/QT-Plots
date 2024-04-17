#include "MainWindow.h"

#include <QApplication>
#include <QSettings>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	QCoreApplication::setOrganizationName("settings");
	QSettings::setDefaultFormat(QSettings::IniFormat);
	QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::applicationDirPath());

	MainWindow *application = new MainWindow();
	application->makeWindow();
	application->show();

	return app.exec();
}
