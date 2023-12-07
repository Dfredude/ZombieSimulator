#pragma once

#include <QtWidgets/QWidget>
#include "ui_ZombieSim.h"

class ZombieSim : public QWidget
{
    Q_OBJECT

public:
    ZombieSim(QWidget *parent = nullptr);
    ~ZombieSim();

private:
    Ui::ZombieSimClass ui;
};
