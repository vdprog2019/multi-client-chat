#include "autorizationwidget.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  AutorizationWidget widget;

  widget.show();
  app.exec();
}
