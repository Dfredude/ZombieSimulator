#include "Organism.h"

Organism::Organism(int x, int y, City* parent = nullptr) : QFrame()
{
	this->height = 40;
	this->width = 40;
	this->city = parent;
	//this->setFrameStyle(QFrame::Box);
	/*this->setLineWidth(1);
	this->setMidLineWidth(1);*/
	// set Line color
	//this->setFixedSize(20, 20);
	//this->setStyleSheet("color: #FFFFFF;");
	this->symbol.setParent(this);
	// this->symbol.setGeometry(QRect(0, 0, 20, 20));
	this->symbol.setAlignment(Qt::AlignCenter);
	this->symbol.setObjectName(QString::fromUtf8("label"));
	this->symbol.setText("-");
	this->symbol.setStyleSheet("color: #FFFFFF;");
	// Increase the font size
	QFont font = this->symbol.font();
	font.setPointSize(16);
	this->symbol.setFont(font);
	setPosition(x, y);
}

Organism::~Organism()
{
	this->symbol.deleteLater();
}

City* Organism::getCity()
{
	return this->city;
}

pair<int, int> Organism::getPosition()
{
	return pair<int, int>(this->x, this->y);
}

bool Organism::isNull()
{
	return true; // Default organism is null
}

void Organism::move()
{
	qDebug() << "Organism::move()";
}

pair<int, int> Organism::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
	return pair<int, int>(this->x, this->y);
}

bool Organism::isTurn()
{
	return !this->tookTurn;
}

void Organism::resetTurn()
{
	this->tookTurn = false;
	this->setStyleSheet("background-color: #000000;");
}