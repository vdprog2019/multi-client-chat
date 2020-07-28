#ifndef AUTORIZATIONWIDGET_H
# define AUTORIZATIONWIDGET_H

# include <QWidget>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlDatabase>

namespace Ui {
class Autorization;
}

class AutorizationWidget : public QWidget {
  Q_OBJECT
public:
  explicit AutorizationWidget(QWidget *parent = 0);
protected:
  Ui::Autorization *m_pAutorization;
public slots:
  void funcEnter();
  void regEnter();
};

#endif // MAINWIDGET_H
