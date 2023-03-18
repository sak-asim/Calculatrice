#include "calculatrice.h"
#include "ui_calculatrice.h"

double valeurCalcul = 0.0;
bool divisionDeclanche = false;
bool multiplicationDeclanche = false;
bool aditionDeclanche = false;
bool soustractionDeclanche = false;

Calculatrice::Calculatrice(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculatrice)
{
    ui->setupUi(this);

    ui->Affichage->setText(QString::number(valeurCalcul));
    QPushButton *numBoutons[10];
    for (int i=0; i<10 ; ++i ) {
        QString nomBouton = "Bouton" + QString::number(i);
        numBoutons[i] = Calculatrice::findChild<QPushButton *>(nomBouton);
        connect(numBoutons[i], SIGNAL(released()), this, SLOT(NumPresse()));
    }
}

Calculatrice::~Calculatrice()
{
    delete ui;
}

void Calculatrice::NumPresse(){
    QPushButton *bouton = (QPushButton * )sender();
    QString valBouton = bouton->text();
    QString valAffichage = ui->Affichage->text();
    if((valAffichage.toDouble() == 0) || (valAffichage.toDouble() == 0.0)){
        ui->Affichage->setText(valBouton);
    }else {
        QString newVal = valAffichage + valBouton;
        double dblNewVal = newVal.toDouble();
        ui->Affichage->setText(QString::number(dblNewVal, 'g', 16));
    }
}

void Calculatrice::MathBoutonPresse(){
    divisionDeclanche = false;
    multiplicationDeclanche = false;
    aditionDeclanche = false;
    soustractionDeclanche = false;
    QString valAffichage = ui->Affichage->text();
    valeurCalcul = valAffichage.toDouble();
    QPushButton *bouton = (QPushButton *)sender();
    QString valBouton = bouton->text();
    if(QString::compare(valBouton, "/", Qt::CaseInsensitive) == 0){
        divisionDeclanche = true;
    }else if(QString::compare(valBouton, "*", Qt::CaseInsensitive) == 0){
        multiplicationDeclanche = true;
    }else if(QString::compare(valBouton, "+", Qt::CaseInsensitive) == 0){
        aditionDeclanche = true;
    }else{
        soustractionDeclanche = true;
    }
    ui->Affichage->setText("");

}

