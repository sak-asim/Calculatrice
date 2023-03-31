#include "calculatrice.h"
#include "ui_calculatrice.h"
#include <cmath>

double valeurCalcul = 0.0;
bool divisionDeclanche = false;
bool multiplicationDeclanche = false;
bool aditionDeclanche = false;
bool soustractionDeclanche = false;
bool moduloDeclanche = false;

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
    connect(ui->Point, SIGNAL(released()), this, SLOT(PointPresse()));
    connect(ui->Additionner, SIGNAL(released()), this, SLOT(MathBoutonPresse()));
    connect(ui->Soustraire, SIGNAL(released()), this, SLOT(MathBoutonPresse()));
    connect(ui->Multiplier, SIGNAL(released()), this, SLOT(MathBoutonPresse()));
    connect(ui->Diviser, SIGNAL(released()), this, SLOT(MathBoutonPresse()));
    connect(ui->Modulo, SIGNAL(released()), this, SLOT(MathBoutonPresse()));
    connect(ui->Egal, SIGNAL(released()), this, SLOT(BoutonEgalPresse()));
    connect(ui->ChangeSigne, SIGNAL(released()), this, SLOT(ChangeNumSigne()));
    connect(ui->Effacer, SIGNAL(released()), this, SLOT(EcranEffacerPresse()));
    connect(ui->Del, SIGNAL(released()), this, SLOT(DelPresse()));
    connect(ui->Carre, SIGNAL(released()), this, SLOT(carrerPresse()));
    connect(ui->Racine, SIGNAL(released()), this, SLOT(RacinePresse()));
    connect(ui->Factorial, SIGNAL(released()), this, SLOT(FactorialPresse()));


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
    moduloDeclanche = false;
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
    }else if(QString::compare(valBouton, "-", Qt::CaseInsensitive) == 0){
        soustractionDeclanche = true;
    }else if(QString::compare(valBouton, "%", Qt::CaseInsensitive) == 0){
        moduloDeclanche = true;
    }
    ui->Affichage->setText("");
}

void Calculatrice::BoutonEgalPresse(){
    double solution = 0.0;
    QString valAffichage = ui->Affichage->text();
    double dblValAffichage = valAffichage.toDouble();
    if(aditionDeclanche || soustractionDeclanche || multiplicationDeclanche || divisionDeclanche || moduloDeclanche){
        if(aditionDeclanche){
            solution = valeurCalcul + dblValAffichage;
        }else if(soustractionDeclanche){
            solution = valeurCalcul - dblValAffichage;
        }else if(multiplicationDeclanche){
            solution = valeurCalcul * dblValAffichage;
        }else if(divisionDeclanche){
            solution = valeurCalcul / dblValAffichage;
        }else if(moduloDeclanche){
            solution = fmod(valeurCalcul, dblValAffichage);
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

void Calculatrice::PointPresse(){
    QPushButton *bouton = (QPushButton *)sender();
    QString valBouton = bouton->text();
    QString valAffichage = ui->Affichage->text();

    if(valAffichage.toDouble() == 0 || valAffichage.toDouble() == 0.0){
        ui->Affichage->setText("Erreur Math");
    }else{
        QString newValue = valAffichage + valBouton;
        double valeur = newValue.toDouble();

        if(!valeur){
            ui->Affichage->setText("Erreur Math");
        }else {
            ui->Affichage->setText(newValue);
        }
    }

}

void Calculatrice::EcranEffacerPresse(){
    ui->Affichage->setText("0");
}

void Calculatrice::DelPresse(){

    QString val = ui->Affichage->text();
        val = val.left(val.length() - 1);
        ui->Affichage->setText(val);

}

void Calculatrice::carrerPresse(){
    QString valAffichage = ui->Affichage->text();
    double dblValAffichage = valAffichage.toDouble();
    double resultat = dblValAffichage * dblValAffichage;
    ui->Affichage->setText(QString::number(resultat));
}

void Calculatrice::RacinePresse() {
    QString valAffichage = ui->Affichage->text();
    double dblValAffichage = valAffichage.toDouble();
    double resultat = sqrt(dblValAffichage);
    ui->Affichage->setText(QString::number(resultat));
}

void Calculatrice::FactorialPresse() {
    QString valAffichage = ui->Affichage->text();
    int n = valAffichage.toInt();
    int resultat = 1;
       for (int i = 1; i <= n; i++) {
           resultat *= i;
       }
    ui->Affichage->setText(QString::number(resultat));
}






