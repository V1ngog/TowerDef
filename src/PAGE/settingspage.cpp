#include "settingspage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

SettingsPage::SettingsPage(QWidget *parent) : BasePage (parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    cancelButton = new QPushButton("Cancel");
    cancelButton->setFixedSize(200, 50);

    namePage = new QLabel("Settings");
    namePage->setStyleSheet("font: bold 24px;");

    QHBoxLayout *helpLayout1 = new QHBoxLayout();
    helpLayout1->addWidget(cancelButton);
    helpLayout1->addStretch();

    QHBoxLayout *helpLayout2 = new  QHBoxLayout();
    helpLayout2->addWidget(namePage, 0, Qt::AlignCenter);

    layout->addLayout(helpLayout2);
    layout->addStretch();
    layout->addLayout(helpLayout1);

    connect(cancelButton, &QPushButton::clicked, this, &SettingsPage::cancelClicked);
}