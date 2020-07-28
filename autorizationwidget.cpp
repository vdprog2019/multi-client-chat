#include "autorizationwidget.h"
#include "ui_Autorization.h"
#include "mainwidget.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <sqlite3.h>
#include <qmessagebox.h>
#include "clientsocketadapter.h"
#include "registrathion.h"
#include "ui_registrathion.h"

AutorizationWidget::AutorizationWidget(QWidget *parent) : QWidget(parent), m_pAutorization(new Ui::Autorization()){
    m_pAutorization->setupUi(this);
    connect(m_pAutorization->enterBtn, SIGNAL(clicked()), SLOT(funcEnter()));
    connect(m_pAutorization->pushButton, SIGNAL(clicked()), SLOT(regEnter()));
}

void AutorizationWidget::funcEnter(){
    QString user_id = "";
      if((user_id = ClientSocketAdapter::LogIn(m_pAutorization->login->text(), m_pAutorization->password->text())) != "" )
      {
          MainWidget * m  = new MainWidget(this, user_id, m_pAutorization->login->text());
          m->setWindowTitle(m_pAutorization->login->text());
          this->setFixedSize(422, 361);
          m->show();
      }
      else{
           QMessageBox b(this);
           b.setText("лох");
           b.exec();
      }
}
void AutorizationWidget::regEnter(){
    registrathion *reg = new registrathion(this);
    reg->show();
}
