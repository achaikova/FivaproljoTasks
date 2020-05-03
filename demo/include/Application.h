#pragma once

#include <QApplication>

class Application : public QApplication
{
Q_OBJECT

public:
    explicit Application(int & argc, char ** argv);

   // bool notify(QObject * receiver, QEvent * e) override; //later  in order to use exceptions
};