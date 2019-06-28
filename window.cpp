﻿#include "window.h"

Window::Window(QWidget *parent) : QWidget(parent)
{
    textEdit = new QTextEdit;
    listWidget = new QListWidget;

    player = new QMediaPlayer(this);
    player->setVolume(50);

    QPushButton* downloadButton = new QPushButton("Download");
    QPushButton* playButton = new QPushButton("Play");
    QPushButton* stopButton = new QPushButton("Stop");

    QGridLayout* controllers = new QGridLayout;
    controllers->addWidget(downloadButton, 0, 0);
    controllers->addWidget(playButton, 0, 1);
    controllers->addWidget(stopButton, 0, 2);
    controllers->addWidget(textEdit, 1, 1);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addLayout(controllers);
    layout->addWidget(listWidget);

    connect(downloadButton, &QPushButton::clicked, this, &Window::getNameFromTextEdit);
    connect(playButton, &QPushButton::clicked, this, &Window::play);
    connect(stopButton, &QPushButton::clicked, this, &Window::pause);
}

void Window::play()
{
    QString audioPath = "D:/DevQt/LizaAudioTransfer/AudioTransferClient/audio/";

    QString s;
    if (listWidget->item(listWidget->currentRow()) != nullptr)
    {
        s = listWidget->item(listWidget->currentRow())->text();

        if (s != currentAudio)
        {
            player->stop();
            player->setMedia(QUrl::fromLocalFile(audioPath + s));
        }
        player->play();

        currentAudio = s;
    }
    else
    {
        qDebug() << "Файл не выбран";
    }
}

void Window::pause()
{
    player->pause();
}

void Window::getNameFromTextEdit()
{
    QString text = this->textEdit->toPlainText();
    emit sendNameToSocket(text);
}

void Window::putToList(QString name)
{
    listWidget->addItem(name);
}
