#ifndef DIALOGCREATE_H
#define DIALOGCREATE_H

#include <QDialog>

class dialogCreate : public QDialog
{
public:
    dialogCreate();

    void vue_cree();

private slots:
    void onGO();
    void onGOV();
    void onGNO();
    void onGNOV();

};

#endif // DIALOGCREATE_H
