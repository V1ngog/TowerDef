#include "settingspage.h"
#include "factories.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

SettingsPage::SettingsPage(QWidget *parent) 
    : BasePage(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    m_titleLabel = new QLabel("Settings", this);
    m_titleLabel->setStyleSheet("font: bold 28px;");
    m_titleLabel->setAlignment(Qt::AlignCenter);
    
    m_difficultyLabel = new QLabel("Select Difficulty:", this);
    m_difficultyLabel->setStyleSheet("font: 16px;");
    m_difficultyLabel->setAlignment(Qt::AlignCenter);
    
    m_easyButton = new QPushButton("Easy", this);
    m_mediumButton = new QPushButton("Medium", this);
    m_hardButton = new QPushButton("Hard", this);
    
    m_easyButton->setFixedSize(150, 40);
    m_mediumButton->setFixedSize(150, 40);
    m_hardButton->setFixedSize(150, 40);
    
    QHBoxLayout *difficultyLayout = new QHBoxLayout();
    difficultyLayout->addStretch();
    difficultyLayout->addWidget(m_easyButton);
    difficultyLayout->addSpacing(20);
    difficultyLayout->addWidget(m_mediumButton);
    difficultyLayout->addSpacing(20);
    difficultyLayout->addWidget(m_hardButton);
    difficultyLayout->addStretch();
    
    m_cancelButton = new QPushButton("Back to Menu", this);
    m_cancelButton->setFixedSize(200, 50);
    
    mainLayout->addStretch();
    mainLayout->addWidget(m_titleLabel);
    mainLayout->addSpacing(40);
    mainLayout->addWidget(m_difficultyLabel);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(difficultyLayout);
    mainLayout->addStretch();
    mainLayout->addWidget(m_cancelButton, 0, Qt::AlignCenter);
    mainLayout->addSpacing(30);
    
    setLayout(mainLayout);
    
    connect(m_easyButton, &QPushButton::clicked, this, &SettingsPage::onEasyClicked);
    connect(m_mediumButton, &QPushButton::clicked, this, &SettingsPage::onMediumClicked);
    connect(m_hardButton, &QPushButton::clicked, this, &SettingsPage::onHardClicked);
    connect(m_cancelButton, &QPushButton::clicked, this, &SettingsPage::onCancelClicked);
    
    updateButtonStyles(m_mediumButton);
    emit difficultySelected(new MediumFactory());
}

void SettingsPage::onEasyClicked()
{
    updateButtonStyles(m_easyButton);
    m_difficultyLabel->setText("Selected: Easy");
    emit difficultySelected(new EasyFactory());
}

void SettingsPage::onMediumClicked()
{
    updateButtonStyles(m_mediumButton);
    m_difficultyLabel->setText("Selected: Medium");
    emit difficultySelected(new MediumFactory());
}

void SettingsPage::onHardClicked()
{
    updateButtonStyles(m_hardButton);
    m_difficultyLabel->setText("Selected: Hard");
    emit difficultySelected(new HardFactory());
}

void SettingsPage::onCancelClicked()
{
    emit cancelClicked();
}

void SettingsPage::updateButtonStyles(QPushButton* activeButton)
{
    QString activeStyle = "background-color: #4CAF50; color: white; border: none; border-radius: 5px;";
    QString inactiveStyle = "background-color: #333333; color: white; border: none; border-radius: 5px;";
    
    m_easyButton->setStyleSheet(m_easyButton == activeButton ? activeStyle : inactiveStyle);
    m_mediumButton->setStyleSheet(m_mediumButton == activeButton ? activeStyle : inactiveStyle);
    m_hardButton->setStyleSheet(m_hardButton == activeButton ? activeStyle : inactiveStyle);
}