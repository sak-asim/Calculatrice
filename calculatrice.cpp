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
    connect(ui->Additionner, SIGNAL(released()), this, SLOT(MathBoutonPresse()));
    connect(ui->Soustraire, SIGNAL(released()), this, SLOT(MathBoutonPresse()));
    connect(ui->Multiplier, SIGNAL(released()), this, SLOT(MathBoutonPresse()));
    connect(ui->Diviser, SIGNAL(released()), this, SLOT(MathBoutonPresse()));
    connect(ui->Egal, SIGNAL(released()), this, SLOT(BoutonEgalPresse()));
    connect(ui->ChangeSigne, SIGNAL(released()), this, SLOT(ChangeNumSigne()));

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

void Calculatrice::BoutonEgalPresse(){
    double solution = 0.0;
    QString valAffichage = ui->Affichage->text();
    double dblValAffichage = valAffichage.toDouble();
    if(aditionDeclanche || soustractionDeclanche || multiplicationDeclanche || divisionDeclanche){
        if(aditionDeclanche){
            solution = valeurCalcul + dblValAffichage;
        }else if(soustractionDeclanche){
            solution = valeurCalcul - dblValAffichage;
        }else if(multiplicationDeclanche){
            solution = valeurCalcul * dblValAffichage;
        }else{
            solution = valeurCalcul /dblValAffichage;
        }
    }
    ui->Affichage->setText(QString::number(solution));
}

void Calculatrice::ChangeNumSigne(){
    QString valAffichage = ui->Affichage->text();
    QRegExp reg("[-]?[0-9]*");
    if(reg.exactMatch(valAffichage)){
        double dblValAffichage = valAffichage.toDouble();
        double dblValAffichageSinge = -1 * dblValAffichage;
        ui->Affichage->setText(QString::number(dblValAffichageSinge));
    }
}










