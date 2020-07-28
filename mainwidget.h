#ifndef MAINWIDGET_H
# define MAINWIDGET_H

# include <QWidget>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class Form;

}

class ISocketAdapter;
class MainWidget : public QWidget {
  Q_OBJECT
public:
  explicit MainWidget(QWidget *parent = 0, QString user_id_from = "", QString login = "");
public slots:
  void on_message(QString text);
  void on_send();
  void EnterPressed();
  bool eventFilter(QObject *watched, QEvent *event);
protected:
  Ui::Form *m_pForm;
  ISocketAdapter *m_pSock;
  QString login;
  QString user_id_from;
  QString user_id_to;
};

#endif // MAINWIDGET_H
