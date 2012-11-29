#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>

#include <Config.h>

namespace Ui {
    class ConfigDialog;
}

class ConfigDialog : public QDialog {
	
    Q_OBJECT

public:
	
    explicit ConfigDialog(kimai::Config& config, QWidget *parent = 0);
    ~ConfigDialog();
	
protected:
	
	void showEvent(QShowEvent*);
	
public slots:
	
	void buttonBar_accepted();

private:
	
    Ui::ConfigDialog *ui;
	kimai::Config& config_;
	
};

#endif // CONFIGDIALOG_H
