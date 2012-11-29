#include "Config.h"

#include <QDebug>

using namespace kimai;

Config::Config(QString iniFilePath) {
	filePath_ = iniFilePath;
	SI_Error error = ini_.LoadFile(filePath_.toAscii());
	if (error != SI_OK) qDebug() << "Could not open INI file:" << error << errno;

	saveTimer_.setInterval(2000);
	saveTimer_.setSingleShot(true);
	
	QObject::connect(&saveTimer_, SIGNAL(timeout()), this, SLOT(saveTimer_timeout()));
}


QVariant Config::value(QString name, QVariant defaultValue) const {
	const char* v = ini_.GetValue("Config", name.toAscii());
	if (v == NULL) return defaultValue;
	
	QString s = QString("%1").arg(v);
	QVariant output(s);
	return output;
}


void Config::setValue(QString name, QVariant value) {
	QVariant current = this->value(name);
	if (current.isNull() && value.isNull()) return;
	if (current.toString() == value.toString()) return;
	
	ini_.SetValue("Config", name.toAscii(), value.toString().toAscii());
	saveTimer_.stop();
	saveTimer_.start();
	
	emit valueChanged(name);
}


void Config::save() {
	saveTimer_.stop();
	ini_.SaveFile(filePath_.toAscii());
}


void Config::saveTimer_timeout() {
	save();
}
