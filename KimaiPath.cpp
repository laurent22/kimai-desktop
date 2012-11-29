#include "KimaiPath.h"

#include <QApplication>
#include <QFileInfo>

namespace kimai { namespace paths {

namespace {
	
	QString applicationFolder_;

}

QString applicationFolder() {
	if (!applicationFolder_.isEmpty()) return applicationFolder_;
	
	QString applicationFile = qApp->applicationFilePath();
	
	int idx = applicationFile.lastIndexOf(".app");
	if (idx > -1) applicationFile = applicationFile.left(idx + 4);
	
	applicationFolder_ = QFileInfo(applicationFile).path() + "/";
	return applicationFolder_;
}

QString dataFolder() {
	return applicationFolder() + "Data/";
}

}}
