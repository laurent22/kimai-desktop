#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <Config.h>
#include <KimaiPath.h>

#include <QDebug>
#include <QMessageBox>
#include <QSettings>
#include <QUrl>


KimaiJavaScriptBridge::KimaiJavaScriptBridge(MainWindow* mainWindow) {
	mainWindow_ = mainWindow;
}

void KimaiJavaScriptBridge::onTimerStarted() {
	mainWindow_->updateWindowIcon();
	onTimerUpdated();
}

void KimaiJavaScriptBridge::onTimerStopped() {
	mainWindow_->updateWindowIcon();
	mainWindow_->setWindowTitle("Kimai");
}

void KimaiJavaScriptBridge::onTimerUpdated() {
	QVariant r = mainWindow_->ui->webView->page()->mainFrame()->evaluateJavaScript("recordElapsedTime()");
	int elapsed = r.toInt();
	QTime t(0,0,0);
	t = t.addSecs(elapsed);
	mainWindow_->setWindowTitle(QString("%1 - Kimai").arg(t.toString("hh:mm:ss")));
}




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    config_(kimai::paths::dataFolder() + "Config.ini") {
	
    ui->setupUi(this);
	
	configDialog_ = NULL;	
	setWindowTitle("Kimai");
	
	QWebSettings* webSettings = QWebSettings::globalSettings();
	webSettings->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
	webSettings->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
	
	jsBridge_ = new KimaiJavaScriptBridge(this);
	
	connect(ui->webView, SIGNAL(loadFinished(bool)), this, SLOT(webView_loadFinished(bool)));
	connect(ui->webView->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(mainFrame_javaScriptWindowObjectCleared()));
	connect(ui->actionConfiguration, SIGNAL(triggered()), this, SLOT(menuBar_configuration_triggered()));
	connect(&config_, SIGNAL(valueChanged(QString)), this, SLOT(config_valueChanged(QString)));
	
	QVariant kimaiUrl = config_.value("kimaiUrl");
	if (kimaiUrl.isNull() || kimaiUrl.toString().trimmed().isEmpty()) {
		QMessageBox::information(this, "Kimai URL not set", "No Kimai URL set. Please set it in the configuration dialog.");
		showConfigDialog();
	} else {
		ui->webView->load(QUrl(kimaiUrl.toString()));
	}
	
	QSettings settings("Kimai", "Kimai Desktop Client");
	QVariant geometry = settings.value("kimai/windowGeometry");
	if (!geometry.isNull()) restoreGeometry(geometry.toByteArray());
}

void MainWindow::menuBar_configuration_triggered() {
	showConfigDialog();
}

void MainWindow::config_valueChanged(QString name) {
	if (name == "kimaiUrl") {
		QVariant kimaiUrl = config_.value("kimaiUrl");
		ui->webView->load(QUrl(kimaiUrl.toString()));
	}
}

void MainWindow::updateWindowIcon() {
	QVariant timerIsRunning = ui->webView->page()->mainFrame()->evaluateJavaScript("timerIsRunning()");
	if (timerIsRunning.toBool()) {
		setWindowIcon(QIcon(kimai::paths::dataFolder() + "PlayIcon.ico"));
	} else {
		setWindowIcon(QIcon(kimai::paths::dataFolder() + "PauseIcon.ico"));
	}
}

void MainWindow::showConfigDialog() {
	if (!configDialog_) {
		configDialog_ = new ConfigDialog(config_, this);
		configDialog_->setModal(true);
	}
	configDialog_->show();
}

void MainWindow::mainFrame_javaScriptWindowObjectCleared() {
	ui->webView->page()->mainFrame()->addToJavaScriptWindowObject("bridge", jsBridge_);
	updateWindowIcon();	
}

void MainWindow::webView_loadFinished(bool) {
	updateWindowIcon();	
}

MainWindow::~MainWindow() {
	config_.save();
	
	QSettings settings("Kimai", "Kimai Desktop Client");
	settings.setValue("kimai/windowGeometry", saveGeometry());
	
    delete ui;
}
