#include "ConfigDialog.h"
#include "ui_ConfigDialog.h"

#include <QDebug>

ConfigDialog::ConfigDialog(kimai::Config& config, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog),
    config_(config) {

    ui->setupUi(this);
	
	connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(buttonBar_accepted()));
}


ConfigDialog::~ConfigDialog() {
    delete ui;
}


void ConfigDialog::showEvent(QShowEvent*) {
	ui->kimaiUrlInput->setText(config_.value("kimaiUrl").toString());
}


void ConfigDialog::buttonBar_accepted() {
	config_.setValue("kimaiUrl", ui->kimaiUrlInput->text().trimmed());
}
