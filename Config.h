#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QTimer>
#include <QVariant>

#include <third_party/simpleini/SimpleIni.h>

namespace kimai {

class Config : public QObject {
	
	Q_OBJECT
	
public:
    
	explicit Config(QString iniFilePath);
	QVariant value(QString name, QVariant defaultValue = QVariant()) const;
	void setValue(QString name, QVariant value);
	void save();
	
public slots:
	
	void saveTimer_timeout();
	
signals:
	
	void valueChanged(QString name);
	
private:
	
	QString filePath_;
	CSimpleIniA ini_;
	QTimer saveTimer_;
	
};

}

#endif // CONFIG_H
