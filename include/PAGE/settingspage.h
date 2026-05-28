#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include "basepage.h"
#include <QPushButton>
#include <QLabel>

class SettingsPage : public BasePage
{
    Q_OBJECT

public:
    explicit SettingsPage(QWidget *parent = nullptr);

signals:
    void cancelClicked();

private:
    QLabel *namePage;
    QPushButton *cancelButton;

};
#endif