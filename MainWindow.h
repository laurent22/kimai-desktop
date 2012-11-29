#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWebKit>

#include <Config.h>
#include <ConfigDialog.h>

namespace Ui {
    class MainWindow;
}

class MainWindow;



class KimaiJavaScriptBridge : public QObject {
	
	Q_OBJECT

public:

	KimaiJavaScriptBridge(MainWindow* mainWindow);	
	Q_INVOKABLE void onTimerStarted();
	Q_INVOKABLE void onTimerStopped();
	Q_INVOKABLE void onTimerUpdated();
	
private:
	
	MainWindow* mainWindow_;
	
};



class MainWindow : public QMainWindow {
	
    Q_OBJECT

public:
	
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	 Ui::MainWindow *ui;
	 void updateWindowIcon();
	 void showConfigDialog();

private:
	 
	KimaiJavaScriptBridge* jsBridge_;
	kimai::Config config_;
	ConfigDialog* configDialog_;
	
public slots:
	
	void mainFrame_javaScriptWindowObjectCleared();
	void webView_loadFinished(bool);
	void menuBar_configuration_triggered();
	void config_valueChanged(QString name);
	
};


#endif // MAINWINDOW_H
