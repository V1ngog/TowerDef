#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include "basepage.h"
#include <QPushButton>
#include <QLabel>
#include <QButtonGroup>
#include "gamefactory.h"

class SettingsPage : public BasePage
{
    Q_OBJECT

public:
    explicit SettingsPage(QWidget *parent = nullptr);

signals:
    void difficultySelected(GameFactory* factory);
    void cancelClicked();

private slots:
    void onEasyClicked();
    void onMediumClicked();
    void onHardClicked();
    void onCancelClicked();

private:
    void updateButtonStyles(QPushButton *activeButton);
    
    QLabel *m_titleLabel;
    QLabel *m_difficultyLabel;
    
    QPushButton *m_easyButton;
    QPushButton *m_mediumButton;
    QPushButton *m_hardButton;
    
    QPushButton *m_cancelButton;
};

#endif