#include "backend.h"

Backend::Backend(QObject *parent) : QObject(parent){
}

void Backend::setDefaultStyleSheet(QQuickTextDocument *qd){
    auto td = qd->textDocument();
    td->setMaximumBlockCount(2000);
}
