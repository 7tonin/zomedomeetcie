#include <QGLWidget>
#include <QMatrix4x4>
#include <QVector2D>
#include <QVector3D>
#include <qmath.h>

#include "complexes.h"
#include "mathema.h"
#include "heliyourte.h"

heliyourte::heliyourte()
{
}

void heliyourte::setParametres(double h_diametreYourte, double h_hauteurMurs, int h_nbrePans, double h_penteToit, double h_epaisseurPerche, double h_retombeePerche, double h_depassementHautPerche, double h_retombeeTonoo, double h_retombeeTraverse, double h_epaisseurCroix, double h_retombeeCroix, double h_epaisseurLiteaux)
{
    // transfert des parametres on met tout en metres
    hel_diametreYourte = h_diametreYourte;
    hel_hauteurMurs = h_hauteurMurs;
    hel_nbrePans = h_nbrePans;
    hel_penteToit = radians(h_penteToit);
    hel_epaisseurPerche = h_epaisseurPerche/100.0;
    hel_retombeePerche = h_retombeePerche/100.0;
    hel_depassementHautPerche = h_depassementHautPerche/100.0;
    hel_retombeeTonoo = h_retombeeTonoo/100.0;
    hel_retombeeTraverse = h_retombeeTraverse/100.0;
    hel_epaisseurCroix = h_epaisseurCroix/100.0;
    hel_retombeeCroix = h_retombeeCroix/100.0;
    hel_epaisseurLiteaux = h_epaisseurLiteaux/100.0;

    calcul();
}

double heliyourte::pointPlusEloigne()
{
    return hel_diametreYourte*2.0;
}

QString heliyourte::generalTraverse()
{
    QString str,str2,str3,resu;

    resu += "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Il y a")+" "+str.setNum(hel_nbrePans)+" "+QObject::tr("traverses. Les points not�s V sont sur la face sup�rieure, les points not�s W sont sur la face de derri�re.Les coordonn�es des points W ne sont donn�s que dans le cas o� ils diff�rent de celles de leur point correspondant en V")+".<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Pr�cisons que lorsqu\'on regarde les traverses depuis l\'int�rieur de l\'h�liyourte, le c�t� gauche est coup� �  l\'�querre, alors que le c�t� droit est coup� l�g�rement en biais")+" </p>";
    resu += "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Les dimensions des planches \"brutes\" dans lesquelles seront taill�es les traverses sont les suivantes")+" :<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Epaisseur")+" : "+str.setNum(hel_epaisseurTraverse*100.0,'f',1)+" cm<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Retomb�e")+" : "+str2.setNum(hel_retombeeTraverse*100.0,'f',1)+" cm<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Longueur")+" : "+str3.setNum((2.0*hel_tetonTraverse+hel_H9_H13)*100.0,'f',1)+" cm</p>";
    return resu;
}

QString heliyourte::tableauTraverse()
{
    //les tableaux de coordonnees
    QString tableau,str,str2;

    tableau = "<table cellpadding=\"2\" border=\"1\" align=\"center\"><tbody><tr>";
    tableau += "<td bgcolor=\"#cccc99\"></td><td bgcolor=\"#cccc99\"><p align=\"center\"><strong>X</strong></p></td><td bgcolor=\"#cccc99\"><p align=\"center\"><strong>Y</strong></p></td bgcolor=\"#cccc99\"><td bgcolor=\"#cccc99\"></td><td bgcolor=\"#cccc99\"><p align=\"center\"><strong>X</strong></p></td><td bgcolor=\"#cccc99\"><p align=\"center\"><strong>Y</strong></p></td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V0</strong></td><td>"+str.setNum(0)+"</td><td>"+str2.setNum(0)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>V6</strong></td><td>"+str.setNum((2.0*hel_tetonTraverse+hel_H12_H14)*100.0,'f',1)+"</td><td>"+str2.setNum(hel_hauteurMiBoisTraverse*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V1</strong></td><td>"+str.setNum(0)+"</td><td>"+str2.setNum(hel_hauteurMiBoisTraverse*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>V7</strong></td><td>"+str.setNum((2.0*hel_tetonTraverse+hel_H12_H14)*100.0,'f',1)+"</td><td>"+str2.setNum(0)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V2</strong></td><td>"+str.setNum(hel_tetonTraverse*100.0,'f',1)+"</td><td>"+str2.setNum(hel_hauteurMiBoisTraverse*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>W4</strong></td><td>"+str.setNum((hel_tetonTraverse+hel_H9_H13)*100.0,'f',1)+"</td><td>"+str2.setNum(hel_retombeeTraverse*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V3</strong></td><td>"+str.setNum(hel_tetonTraverse*100.0,'f',1)+"</td><td>"+str2.setNum(hel_retombeeTraverse*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>W5</strong></td><td>"+str.setNum((hel_tetonTraverse+hel_H9_H13)*100.0,'f',1)+"</td><td>"+str2.setNum(hel_hauteurMiBoisTraverse*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V4</strong></td><td>"+str.setNum((hel_tetonTraverse+hel_H12_H14)*100.0,'f',1)+"</td><td>"+str2.setNum(hel_retombeeTraverse*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>W6</strong></td><td>"+str.setNum((2.0*hel_tetonTraverse+hel_H9_H13)*100.0,'f',1)+"</td><td>"+str2.setNum(hel_hauteurMiBoisTraverse*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V5</strong></td><td>"+str.setNum((hel_tetonTraverse+hel_H12_H14)*100.0,'f',1)+"</td><td>"+str2.setNum(hel_hauteurMiBoisTraverse*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>W7</strong></td><td>"+str.setNum((2.0*hel_tetonTraverse+hel_H9_H13)*100.0,'f',1)+"</td><td>"+str2.setNum(0)+"</td></tr>";
    tableau += "</tbody></table>";

    return tableau;
}

QString heliyourte::generalCroix()
{
    QString str,str2,str3,resu;

    resu += "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Il y a")+" "+str.setNum(2.0*hel_nbrePans)+" "+QObject::tr("�l�ments de croix. On donne les coordonn�es des points sur une des faces, ce sont les m�mes sur la face de derri�re (pas de coupes de biais)")+".<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Pr�cisons que les 2 pi�ces constitutives d'une croix sont bien les m�mes, qu'elles soient pench�es d\'un c�t� ou de l\'autre. Par contre, les 2 bouts ne sont pas exactement taill�s aux m�me c�tes")+".</p>";
    resu += "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Les dimensions des planches \"brutes\" dans lesquelles seront taill�es les �l�ments de croix sont les suivantes")+" :<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Epaisseur")+" : "+str.setNum(hel_epaisseurCroix*100.0,'f',1)+" cm<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Retomb�e")+" : "+str2.setNum(hel_retombeeCroix*100.0,'f',1)+" cm<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Longueur")+" : "+str3.setNum(hel_cr_2[13].x()*100.0-hel_cr_2[10].x()*100.0+2.0+2.0,'f',1)+" cm</p>";
    return resu;
}

QString heliyourte::tableauCroix()
{
    //les tableaux de coordonnees
    QString tableau,str,str2;
    double rajout_x = -hel_cr_2[10].x()*100.0+2.0;
    tableau = "<table cellpadding=\"2\" border=\"1\" align=\"center\"><tbody><tr>";
    tableau += "<td bgcolor=\"#cccc99\"></td><td bgcolor=\"#cccc99\"><p align=\"center\"><strong>X</strong></p></td><td bgcolor=\"#cccc99\"><p align=\"center\"><strong>Y</strong></p></td bgcolor=\"#cccc99\"><td bgcolor=\"#cccc99\"></td><td bgcolor=\"#cccc99\"><p align=\"center\"><strong>X</strong></p></td><td bgcolor=\"#cccc99\"><p align=\"center\"><strong>Y</strong></p></td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V0</strong></td><td>"+str.setNum(hel_cr_2[5].x()*100.0+rajout_x,'f',1)+"</td><td>"+str2.setNum(0)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>V7</strong></td><td>"+str.setNum(hel_cr_2[18].x()*100.0+rajout_x,'f',1)+"</td><td>"+str2.setNum(hel_retombeeCroix*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V1</strong></td><td>"+str.setNum(hel_cr_2[16].x()*100.0+rajout_x,'f',1)+"</td><td>"+str2.setNum(0)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>V8</strong></td><td>"+str.setNum(hel_cr_2[3].x()*100.0+rajout_x,'f',1)+"</td><td>"+str2.setNum(hel_retombeeCroix*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V2</strong></td><td>"+str.setNum(hel_cr_2[14].x()*100.0+rajout_x,'f',1)+"</td><td>"+str2.setNum(hel_cr_2[14].y()*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>V9</strong></td><td>"+str.setNum(hel_cr_2[1].x()*100.0+rajout_x,'f',1)+"</td><td>"+str2.setNum(hel_cr_2[1].y()*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V3</strong></td><td>"+str.setNum(hel_cr_2[13].x()*100.0+rajout_x,'f',1)+"</td><td>"+str2.setNum(hel_cr_2[13].y()*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>V10</strong></td><td>"+str.setNum(hel_cr_2[0].x()*100.0+rajout_x,'f',1)+"</td><td>"+str2.setNum(hel_cr_2[0].y()*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V4</strong></td><td>"+str.setNum(hel_cr_2[23].x()*100.0+rajout_x,'f',1)+"</td><td>"+str2.setNum(hel_cr_2[23].y()*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>V11</strong></td><td>"+str.setNum(hel_cr_2[10].x()*100.0+rajout_x,'f',1)+"</td><td>"+str2.setNum(hel_cr_2[10].y()*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V5</strong></td><td>"+str.setNum(hel_cr_2[22].x()*100.0+rajout_x,'f',1)+"</td><td>"+str2.setNum(hel_cr_2[22].y()*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>V12</strong></td><td>"+str.setNum(hel_cr_2[9].x()*100.0+rajout_x,'f',1)+"</td><td>"+str2.setNum(hel_cr_2[9].y()*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V6</strong></td><td>"+str.setNum(hel_cr_2[17].x()*100.0+rajout_x,'f',1)+"</td><td>"+str2.setNum(hel_cr_2[17].y()*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>V13</strong></td><td>"+str.setNum(hel_cr_2[4].x()*100.0+rajout_x,'f',1)+"</td><td>"+str2.setNum(hel_cr_2[4].y()*100.0,'f',1)+"</td></tr>";
    tableau += "</tbody></table>";

    return tableau;
}

QString heliyourte::generalPoteaux()
{
    QString str,resu;

    resu += "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Il y a")+" "+str.setNum(hel_nbrePans)+" "+QObject::tr("poteaux � fabriquer, dont nous allons d�tailler les plans ci-apr�s.")+"<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Chaque poteau est un assemblage de \"trois\" montants que nous appelerons A, B, C")+".<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Une mani�re d\'assembler le poteau est de visser d\'abord les montants B avec le A, les vis allant de B vers A, puis de rajouter le montant C. Cela de permet de cacher la moiti� des vis")+".<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Attention, ne pas l�siner sur la fixation du bout du montant B qui est le plus haut, car c\'est lui qui va reprendre une partie du poids des perches")+".</p>";
    return resu;
}

QString heliyourte::PoteauMontantA()
{
    QString str,str2,str3,resu;

    resu += "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Il y a")+" "+str.setNum(hel_nbrePans)+" "+QObject::tr("montants A. Les coordonn�es des points sur la face qui va �tre � l\'ext�rieur du poteau sont not�s V, ceux sur la face interne W.Les coordonn�es des points W ne sont donn�s que dans le cas o� ils diff�rent de celles de leur point correspondant en V")+".<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Pr�cisons que les 3 trous de ce montants sont taill�s en biais, avec un angle de")+" "+str3.setNum(degres(hel_DdansA.angleBiais),'f',1)+" �.</p>";
    resu += "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Les dimensions des planches \"brutes\" dans lesquelles seront taill�es les montants A sont les suivantes")+" :<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Epaisseur")+" : "+str.setNum(hel_epaisseurPlancheAetC*100.0,'f',1)+" cm<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Retomb�e")+" : "+str2.setNum(hel_retombeePlanchesMontant*100.0,'f',1)+" cm<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Longueur")+" : "+str3.setNum((hel_hauteurMurs+hel_retombeePlanchesMontant*qTan(hel_penteToit))*100.0,'f',1)+" cm</p>";
    return resu;
}

QString heliyourte::PoteauMontantATable()
{
    //les tableaux de coordonnees
    QString tableau,str,str2;
    tableau = "<table cellpadding=\"2\" border=\"1\" align=\"center\"><tbody><tr>";
    tableau += "<td bgcolor=\"#cccc99\"></td><td bgcolor=\"#cccc99\"><p align=\"center\"><strong>X</strong></p></td><td bgcolor=\"#cccc99\"><p align=\"center\"><strong>Y</strong></p></td bgcolor=\"#cccc99\"><td bgcolor=\"#cccc99\"></td><td bgcolor=\"#cccc99\"><p align=\"center\"><strong>X</strong></p></td><td bgcolor=\"#cccc99\"><p align=\"center\"><strong>Y</strong></p></td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V0</strong></td><td>"+str.setNum(0)+"</td><td>"+str2.setNum(0)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>V14</strong></td><td>"+str.setNum(hel_FdansA.haut*100.0,'f',1)+"</td><td>"+str2.setNum((hel_FdansA.distanceRapportBordInt+hel_FdansA.largeur)*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V1</strong></td><td>"+str.setNum((hel_hauteurMurs+hel_retombeePlanchesMontant*qTan(hel_penteToit))*100.0,'f',1)+"</td><td>"+str2.setNum(0)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>V15</strong></td><td>"+str.setNum(hel_FdansA.bas*100.0,'f',1)+"</td><td>"+str2.setNum((hel_FdansA.distanceRapportBordInt+hel_FdansA.largeur)*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V2</strong></td><td>"+str.setNum(hel_hauteurMurs*100.0,'f',1)+"</td><td>"+str2.setNum(hel_retombeePlanchesMontant*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>W4</strong></td><td>"+str.setNum(hel_DdansA.bas*100.0,'f',1)+"</td><td>"+str2.setNum((hel_retombeePlanchesMontant-hel_DdansA.distanceRapportBordInt-hel_DdansA.largeur)*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V3</strong></td><td>"+str.setNum(0)+"</td><td>"+str2.setNum(hel_retombeePlanchesMontant*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>W5</strong></td><td>"+str.setNum(hel_DdansA.haut*100.0,'f',1)+"</td><td>"+str2.setNum((hel_retombeePlanchesMontant-hel_DdansA.distanceRapportBordInt-hel_DdansA.largeur)*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V4</strong></td><td>"+str.setNum(hel_DdansA.bas*100.0,'f',1)+"</td><td>"+str2.setNum(hel_DdansA.distanceRapportBordInt*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>W6</strong></td><td>"+str.setNum(hel_DdansA.haut*100.0,'f',1)+"</td><td>"+str2.setNum((hel_retombeePlanchesMontant-hel_DdansA.distanceRapportBordInt),'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V5</strong></td><td>"+str.setNum(hel_DdansA.haut*100.0,'f',1)+"</td><td>"+str2.setNum(hel_DdansA.distanceRapportBordInt*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>W7</strong></td><td>"+str.setNum(hel_DdansA.bas*100.0,'f',1)+"</td><td>"+str2.setNum((hel_retombeePlanchesMontant-hel_DdansA.distanceRapportBordInt)*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V6</strong></td><td>"+str.setNum(hel_DdansA.haut*100.0,'f',1)+"</td><td>"+str2.setNum((hel_DdansA.distanceRapportBordInt+hel_DdansA.largeur)*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>W8</strong></td><td>"+str.setNum(hel_CdansA.bas*100.0,'f',1)+"</td><td>"+str2.setNum((hel_retombeePlanchesMontant-hel_CdansA.distanceRapportBordInt-hel_CdansA.largeur)*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V7</strong></td><td>"+str.setNum(hel_DdansA.bas*100.0,'f',1)+"</td><td>"+str2.setNum((hel_DdansA.distanceRapportBordInt+hel_DdansA.largeur)*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>W9</strong></td><td>"+str.setNum(hel_CdansA.haut*100.0,'f',1)+"</td><td>"+str2.setNum((hel_retombeePlanchesMontant-hel_CdansA.distanceRapportBordInt-hel_CdansA.largeur)*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V8</strong></td><td>"+str.setNum(hel_CdansA.bas*100.0,'f',1)+"</td><td>"+str2.setNum(hel_CdansA.distanceRapportBordInt*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>W10</strong></td><td>"+str.setNum(hel_CdansA.haut*100.0,'f',1)+"</td><td>"+str2.setNum((hel_retombeePlanchesMontant-hel_CdansA.distanceRapportBordInt)*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V9</strong></td><td>"+str.setNum(hel_CdansA.haut*100.0,'f',1)+"</td><td>"+str2.setNum(hel_CdansA.distanceRapportBordInt*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>W11</strong></td><td>"+str.setNum(hel_CdansA.bas*100.0,'f',1)+"</td><td>"+str2.setNum((hel_retombeePlanchesMontant-hel_CdansA.distanceRapportBordInt)*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V10</strong></td><td>"+str.setNum(hel_CdansA.haut*100.0,'f',1)+"</td><td>"+str2.setNum((hel_CdansA.distanceRapportBordInt+hel_CdansA.largeur)*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>W12</strong></td><td>"+str.setNum(hel_FdansA.bas*100.0,'f',1)+"</td><td>"+str2.setNum((hel_retombeePlanchesMontant-hel_FdansA.distanceRapportBordInt-hel_FdansA.largeur)*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V11</strong></td><td>"+str.setNum(hel_CdansA.bas*100.0,'f',1)+"</td><td>"+str2.setNum((hel_CdansA.distanceRapportBordInt+hel_CdansA.largeur)*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>W13</strong></td><td>"+str.setNum(hel_FdansA.haut*100.0,'f',1)+"</td><td>"+str2.setNum((hel_retombeePlanchesMontant-hel_FdansA.distanceRapportBordInt-hel_FdansA.largeur)*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V12</strong></td><td>"+str.setNum(hel_FdansA.bas*100.0,'f',1)+"</td><td>"+str2.setNum(hel_FdansA.distanceRapportBordInt*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>W14</strong></td><td>"+str.setNum(hel_FdansA.haut*100.0,'f',1)+"</td><td>"+str2.setNum((hel_retombeePlanchesMontant-hel_FdansA.distanceRapportBordInt)*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V13</strong></td><td>"+str.setNum(hel_FdansA.haut*100.0,'f',1)+"</td><td>"+str2.setNum(hel_FdansA.distanceRapportBordInt*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>W15</strong></td><td>"+str.setNum(hel_FdansA.bas*100.0,'f',1)+"</td><td>"+str2.setNum((hel_retombeePlanchesMontant-hel_FdansA.distanceRapportBordInt)*100.0,'f',1)+"</td></tr>";
    tableau += "</tbody></table>";

    return tableau;
}

QString heliyourte::PoteauMontantB()
{
    QString str,str2,str3,resu;

    resu += "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Il y a")+" "+str.setNum(hel_nbrePans)+" \""+QObject::tr("montants B")+"\". "+QObject::tr("Ce ne sont pas vraiment des montants mais trois bouts d\'�paisseur et de retomb�e similaires, mais de longueurs diff�rentes")+".</p>";
    resu += "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Les 3 bouts peuvent �tre d�coup�s dans une planche \"brute\" de dimensions")+" :<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Epaisseur")+" : "+str.setNum(hel_epaisseurPlancheB*100.0,'f',1)+" cm<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Retomb�e")+" : "+str2.setNum(hel_retombeePlanchesMontant*100.0,'f',1)+" cm<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Longueur")+" : "+str3.setNum((hel_montantB_1.hauteur+hel_montantB_2.hauteur+hel_montantB_3.hauteur)*100.0+1,'f',1)+" cm</p>";
    resu += "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Le premier bout mesure")+" "+str.setNum(hel_montantB_1.hauteur*100.0,'f',1)+" cm. "+QObject::tr("Son bas est �")+" "+str2.setNum(hel_montantB_1.bas*100.0,'f',1)+" cm "+QObject::tr("du bas, son haut �")+" "+str3.setNum(hel_montantB_1.haut*100.0,'f',1)+" cm.</p>";
    resu += "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Le premier bout mesure")+" "+str.setNum(hel_montantB_2.hauteur*100.0,'f',1)+" cm. "+QObject::tr("Son bas est �")+" "+str2.setNum(hel_montantB_2.bas*100.0,'f',1)+" cm "+QObject::tr("du bas, son haut �")+" "+str3.setNum(hel_montantB_2.haut*100.0,'f',1)+" cm.</p>";
    resu += "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Le premier bout mesure")+" "+str.setNum(hel_montantB_3.hauteur*100.0,'f',1)+" cm. "+QObject::tr("Son bas est �")+" "+str2.setNum(hel_montantB_3.bas*100.0,'f',1)+" cm "+QObject::tr("du bas, son haut �")+" "+str3.setNum(hel_montantB_3.haut*100.0,'f',1)+" cm.</p>";
    return resu;
}

QString heliyourte::PoteauMontantC()
{
    QString str,str2,str3,resu;

    resu += "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Il y a")+" "+str.setNum(hel_nbrePans)+" "+QObject::tr("montants C. On donne les coordonn�es des points sur une des faces, ce sont les m�mes sur la face de derri�re (pas de coupes de biais)")+".</p>";
    resu += "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Les dimensions des planches \"brutes\" dans lesquelles seront taill�es les montants C sont les suivantes")+" :<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Epaisseur")+" : "+str.setNum(hel_epaisseurPlancheAetC*100.0,'f',1)+" cm<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Retomb�e")+" : "+str2.setNum(hel_retombeePlanchesMontant*100.0,'f',1)+" cm<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Longueur")+" : "+str3.setNum((hel_hauteurMurs+hel_retombeePlanchesMontant*qTan(hel_penteToit))*100.0,'f',1)+" cm</p>";
    return resu;
}

QString heliyourte::PoteauMontantCTable()
{
    //les tableaux de coordonnees
    QString tableau,str,str2;
    tableau = "<table cellpadding=\"2\" border=\"1\" align=\"center\"><tbody><tr>";
    tableau += "<td bgcolor=\"#cccc99\"></td><td bgcolor=\"#cccc99\"><p align=\"center\"><strong>X</strong></p></td><td bgcolor=\"#cccc99\"><p align=\"center\"><strong>Y</strong></p></td bgcolor=\"#cccc99\"><td bgcolor=\"#cccc99\"></td><td bgcolor=\"#cccc99\"><p align=\"center\"><strong>X</strong></p></td><td bgcolor=\"#cccc99\"><p align=\"center\"><strong>Y</strong></p></td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V0</strong></td><td>"+str.setNum(0)+"</td><td>"+str2.setNum(0)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>V8</strong></td><td>"+str.setNum(hel_AdansC.bas*100.0,'f',1)+"</td><td>"+str2.setNum(0)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V1</strong></td><td>"+str.setNum((hel_hauteurMurs+hel_retombeePlanchesMontant*qTan(hel_penteToit))*100.0,'f',1)+"</td><td>"+str2.setNum(0)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>V9</strong></td><td>"+str.setNum(hel_AdansC.haut*100.0,'f',1)+"</td><td>"+str2.setNum(0)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V2</strong></td><td>"+str.setNum(hel_hauteurMurs*100.0,'f',1)+"</td><td>"+str2.setNum(hel_retombeePlanchesMontant*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>V10</strong></td><td>"+str.setNum(hel_AdansC.haut*100.0,'f',1)+"</td><td>"+str2.setNum((hel_AdansC.largeur)*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V3</strong></td><td>"+str.setNum(0)+"</td><td>"+str2.setNum(hel_retombeePlanchesMontant*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>V11</strong></td><td>"+str.setNum(hel_AdansC.bas*100.0,'f',1)+"</td><td>"+str2.setNum((hel_AdansC.largeur)*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V4</strong></td><td>"+str.setNum(hel_BdansC.bas*100.0,'f',1)+"</td><td>"+str2.setNum(hel_BdansC.distanceRapportBordInt*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>V12</strong></td><td>"+str.setNum(hel_EdansC.bas*100.0,'f',1)+"</td><td>"+str2.setNum(hel_EdansC.distanceRapportBordInt*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V5</strong></td><td>"+str.setNum(hel_BdansC.haut*100.0,'f',1)+"</td><td>"+str2.setNum(hel_BdansC.distanceRapportBordInt*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>V13</strong></td><td>"+str.setNum(hel_EdansC.haut*100.0,'f',1)+"</td><td>"+str2.setNum(hel_EdansC.distanceRapportBordInt*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V6</strong></td><td>"+str.setNum(hel_BdansC.haut*100.0,'f',1)+"</td><td>"+str2.setNum((hel_BdansC.distanceRapportBordInt+hel_BdansC.largeur)*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>V14</strong></td><td>"+str.setNum(hel_EdansC.haut*100.0,'f',1)+"</td><td>"+str2.setNum((hel_EdansC.distanceRapportBordInt+hel_EdansC.largeur)*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V7</strong></td><td>"+str.setNum(hel_BdansC.bas*100.0,'f',1)+"</td><td>"+str2.setNum((hel_BdansC.distanceRapportBordInt+hel_BdansC.largeur)*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>V15</strong></td><td>"+str.setNum(hel_EdansC.bas*100.0,'f',1)+"</td><td>"+str2.setNum((hel_EdansC.distanceRapportBordInt+hel_EdansC.largeur)*100.0,'f',1)+"</td></tr>";
    tableau += "</tbody></table>";

    return tableau;
}

QString heliyourte::PercheGeneral()
{
    QString str,str2,str3,resu;

    resu += "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Il y a")+" "+str.setNum(hel_nbrePans)+" "+QObject::tr("perches, dont voici les plans ci-apr�s. Les coordonn�es des points sur la face sup�rieure de la planche sont not�s V, ceux sur la face de derri�re W. Les coordonn�es des points W ne sont donn�s que dans le cas o� ils diff�rent de celles de leur point correspondant en V")+".</p>";
    resu += "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Les dimensions des planches \"brutes\" dans lesquelles seront taill�es les perches sont les suivantes")+" :<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Epaisseur")+" : "+str.setNum(hel_epaisseurPerche*100.0,'f',1)+" cm<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Retomb�e")+" : "+str2.setNum(hel_retombeePerche*100.0,'f',1)+" cm<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Longueur")+" : "+str3.setNum((hel_longueurMiniPlanchesPerches)*100.0,'f',1)+" cm</p>";
    resu += "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Au montage, les perches seront \"pos�es\" les unes sur les autres : la 2�me sur la premi�re, la 3�me sur la 2�me et ainsi de suite jusqu\'� la derni�re qui elle, recevra le poids de la premi�re. C\'est ce qu \'on appelle une charpente autoport�e. Afin que les perches restent en place, nous leur rajoutons un t�ton (au point I) perpendiculaire � la face V8-V9-W9-W8, au milieu de l\'�paisseur de la perche. Le plus simple � faire est de percer � ce point I pour y fixer une tige filet� (diam�tre 8mm, �a suffit) qui sera viss� de 5 cm dans la perche et ressortira de 5-6 cm")+".<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Afin que la perche puisse s\'enficher sur la pr�c�dente, il faudra percer en J, au milieu de l\'�paisseur de la perche et perpendiculairement � la face V2-V3-W3-W2, d\'une profondeur et d\'un diam�tre un peu sup�rieur � ceux du t�ton")+".</p>";
    return resu;
}

QString heliyourte::PercheTable()
{
    //les tableaux de coordonnees
    QString tableau,str,str2;
    tableau = "<table cellpadding=\"2\" border=\"1\" align=\"center\"><tbody><tr>";
    tableau += "<td bgcolor=\"#cccc99\"></td><td bgcolor=\"#cccc99\"><p align=\"center\"><strong>X</strong></p></td><td bgcolor=\"#cccc99\"><p align=\"center\"><strong>Y</strong></p></td bgcolor=\"#cccc99\"><td bgcolor=\"#cccc99\"></td><td bgcolor=\"#cccc99\"><p align=\"center\"><strong>X</strong></p></td><td bgcolor=\"#cccc99\"><p align=\"center\"><strong>Y</strong></p></td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V0</strong></td><td>"+str.setNum(hel_perche_face[4].x()*100.0,'f',1)+"</td><td>"+str2.setNum(0)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>V10</strong></td><td>"+str.setNum(hel_perche_face[0].x()*100.0,'f',1)+"</td><td>"+str2.setNum(hel_perche_face[0].y()*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V1</strong></td><td>"+str.setNum(hel_perche_derriere[11].x()*100.0,'f',1)+"</td><td>"+str2.setNum(0)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>V11</strong></td><td>"+str.setNum(0)+"</td><td>"+str2.setNum(hel_perche_face[1].y()*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V2</strong></td><td>"+str.setNum(hel_perche_derriere[10].x()*100.0,'f',1)+"</td><td>"+str2.setNum(hel_perche_derriere[10].y()*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>V12</strong></td><td>"+str.setNum(hel_perche_face[2].x()*100.0,'f',1)+"</td><td>"+str2.setNum(hel_perche_face[2].y()*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V3</strong></td><td>"+str.setNum(hel_perche_face[12].x()*100.0,'f',1)+"</td><td>"+str2.setNum(0)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>V13</strong></td><td>"+str.setNum(hel_perche_face[3].x()*100.0,'f',1)+"</td><td>"+str2.setNum(hel_perche_face[3].y()*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V4</strong></td><td>"+str.setNum(hel_perche_face[13].x()*100.0,'f',1)+"</td><td>"+str2.setNum(0)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>W1</strong></td><td>"+str.setNum(hel_perche_face[11].x()*100.0,'f',1)+"</td><td>"+str2.setNum(0)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V5</strong></td><td>"+str.setNum(hel_perche_face[14].x()*100.0,'f',1)+"</td><td>"+str2.setNum(hel_perche_face[14].y()*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>W2</strong></td><td>"+str.setNum(hel_perche_face[10].x()*100.0,'f',1)+"</td><td>"+str2.setNum(hel_perche_face[10].y()*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V6</strong></td><td>"+str.setNum(hel_perche_face[9].x()*100.0,'f',1)+"</td><td>"+str2.setNum(hel_perche_face[9].y()*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>W7</strong></td><td>"+str.setNum(hel_perche_face[8].x()*100.0,'f',1)+"</td><td>"+str2.setNum(hel_perche_face[8].y()*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V7</strong></td><td>"+str.setNum(hel_perche_derriere[8].x()*100.0,'f',1)+"</td><td>"+str2.setNum(hel_perche_derriere[8].y()*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>W8</strong></td><td>"+str.setNum(hel_perche_face[7].x()*100.0,'f',1)+"</td><td>"+str2.setNum(hel_perche_face[7].y()*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V8</strong></td><td>"+str.setNum(hel_perche_derriere[7].x()*100.0,'f',1)+"</td><td>"+str2.setNum(hel_perche_derriere[7].y()*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>I</strong></td><td>"+str.setNum(hel_perche_face[15].x()*100.0,'f',1)+"</td><td>"+str2.setNum(hel_perche_face[15].y()*100.0,'f',1)+"</td></tr>";
    tableau += "<tr><td bgcolor=\"#cccc99\"><strong>V9</strong></td><td>"+str.setNum(hel_perche_face[6].x()*100.0,'f',1)+"</td><td>"+str2.setNum(hel_perche_face[6].y()*100.0,'f',1)+"</td>";
    tableau += "<td bgcolor=\"#cccc99\"><strong>J</strong></td><td>"+str.setNum(hel_perche_face[16].x()*100.0,'f',1)+"</td><td>"+str2.setNum(hel_perche_face[16].y()*100.0,'f',1)+"</td></tr>";
    tableau += "</tbody></table>";

    return tableau;
}

QString heliyourte::debit()
{
    QString str,str2,resu;

    resu = "<p><span style=\"font-size: 12pt; color: #ff9900;\"><strong>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Perches")+"</strong></span></p>";
    resu += "<p>"+QObject::tr("Il faut")+" <strong>"+str.setNum(hel_nbrePans)+"</strong> "+QObject::tr("planches aux dimensions suivantes")+" :<br />";
    resu += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- "+QObject::tr("epaisseur")+" : <strong>"+str.setNum(hel_epaisseurPerche*100.0,'f',1)+"</strong> cm<br />";
    resu += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- "+QObject::tr("retomb�e")+" : <strong>"+str.setNum(hel_retombeePerche*100.0,'f',1)+"</strong> cm<br />";
    resu += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- "+QObject::tr("longueur")+" : <strong>"+str.setNum(hel_longueurMiniPlanchesPerches,'f',2)+"</strong> m</p>";
    double hly_debitPerche, hly_debitTraverse, hly_debitCroix, hly_debitMontantsAetC, hly_debitMontantB, hly_debitLiteaux, hly_debitTotal;
    hly_debitPerche = hel_nbrePans*hel_epaisseurPerche*hel_retombeePerche*hel_longueurMiniPlanchesPerches;
    resu += "<p>"+QObject::tr("Ce qui nous donne un d�bit pour les perches de")+" <strong>"+str.setNum(hly_debitPerche,'f',2)+"</strong> m3.</p>";
    resu += "<p></p>";
    resu += "<p><span style=\"font-size: 12pt; color: #ff9900;\"><strong>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Poteaux")+"</strong></span></p>";
    resu += "<p>"+QObject::tr("Pour les montants")+" <strong>A "+QObject::tr("et")+" C</strong> "+QObject::tr("ensemble, il faut")+" <strong>"+str.setNum(2.0*(double)hel_nbrePans,'f',0)+"</strong> "+QObject::tr("planches aux dimensions suivantes")+" : <br />";
    resu += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- "+QObject::tr("�paisseur")+" : <strong>"+str.setNum(hel_epaisseurPlancheAetC*100.0,'f',1)+"</strong> cm<br />";
    resu += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- "+QObject::tr("retomb�e")+" : <strong>"+str.setNum(hel_retombeePlanchesMontant*100.0,'f',1)+"</strong> cm<br />";
    resu += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- "+QObject::tr("longueur")+" : <strong>"+str.setNum((hel_hauteurMurs+hel_retombeePlanchesMontant*qTan(hel_penteToit)),'f',2)+"</strong> m</p>";
    hly_debitMontantsAetC = 2.0*hel_nbrePans*(hel_hauteurMurs+hel_retombeePlanchesMontant*qTan(hel_penteToit))*hel_epaisseurPlancheAetC*hel_retombeePlanchesMontant;
    resu += "<p>"+QObject::tr("Ce qui nous donne un d�bit pour les montants A et C de")+" <strong>"+str.setNum(hly_debitMontantsAetC,'f',2)+"</strong> m3.</p>";
    resu += "<p></p>";
    resu += "<p>"+QObject::tr("Pour les montants")+" <strong>B</strong>, "+QObject::tr("il faut")+" <strong>"+str.setNum(hel_nbrePans)+"</strong> "+QObject::tr("planches aux dimensions suivantes")+" : <br />";
    resu += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- "+QObject::tr("�paisseur")+" : <strong>"+str.setNum(hel_epaisseurPlancheB*100.0,'f',1)+"</strong> cm<br />";
    resu += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- "+QObject::tr("retomb�e")+" : <strong>"+str.setNum(hel_retombeePlanchesMontant*100.0,'f',1)+"</strong> cm<br />";
    resu += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- "+QObject::tr("longueur")+" : <strong>"+str.setNum((hel_montantB_1.hauteur+hel_montantB_2.hauteur+hel_montantB_3.hauteur)+0.01,'f',2)+"</strong> m</p>";
    hly_debitMontantB = hel_nbrePans*((hel_montantB_1.hauteur+hel_montantB_2.hauteur+hel_montantB_3.hauteur)+0.01)*hel_epaisseurPlancheB*hel_retombeePlanchesMontant;
    resu += "<p>"+QObject::tr("Ce qui nous donne un d�bit pour les montants B de")+" <strong>"+str.setNum(hly_debitMontantB,'f',2)+"</strong> m3.</p>";
    resu += "<p></p>";
    resu += "<p><span style=\"font-size: 12pt; color: #ff9900;\"><strong>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Croix")+"</strong></span></p>";
    resu += "<p>"+QObject::tr("Pour les croix, il faut")+" <strong>"+str.setNum(2.0*(double)hel_nbrePans,'f',0)+"</strong> "+QObject::tr("planches aux dimensions suivantes")+" : <br />";
    resu += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- "+QObject::tr("�paisseur")+" : <strong>"+str.setNum(hel_epaisseurCroix*100.0,'f',1)+"</strong> cm<br />";
    resu += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- "+QObject::tr("retomb�e")+" : <strong>"+str.setNum(hel_retombeeCroix*100.0,'f',1)+"</strong> cm<br />";
    resu += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- "+QObject::tr("longueur")+" : <strong>"+str.setNum(hel_cr_2[13].x()-hel_cr_2[10].x()+0.04,'f',2)+"</strong> m</p>";
    hly_debitCroix = (hel_cr_2[13].x()-hel_cr_2[10].x()+0.04)*2.0*hel_nbrePans*hel_retombeeCroix*hel_epaisseurCroix;
    resu += "<p>"+QObject::tr("Ce qui nous donne un d�bit pour les croix de")+" <strong>"+str.setNum(hly_debitCroix,'f',2)+"</strong> m3.</p>";
    resu += "<p></p>";
    resu += "<p><span style=\"font-size: 12pt; color: #ff9900;\"><strong>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Traverses")+"</strong></span></p>";
    resu += "<p>"+QObject::tr("Pour les traverses, il faut")+" <strong>"+str.setNum(hel_nbrePans)+"</strong> "+QObject::tr("planches aux dimensions suivantes")+" : <br />";
    resu += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- "+QObject::tr("�paisseur")+" : <strong>"+str.setNum(hel_epaisseurTraverse*100.0,'f',1)+"</strong> cm<br />";
    resu += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- "+QObject::tr("retomb�e")+" : <strong>"+str.setNum(hel_retombeeTraverse*100.0,'f',1)+"</strong> cm<br />";
    resu += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- "+QObject::tr("longueur")+" : <strong>"+str.setNum(hel_H9_H13+2.0*hel_tetonTraverse,'f',2)+"</strong> m</p>";
    hly_debitTraverse = hel_nbrePans*hel_retombeeTraverse*hel_epaisseurTraverse*(hel_H9_H13+2.0*hel_tetonTraverse);
    resu += "<p>"+QObject::tr("Ce qui nous donne un d�bit pour les traverses de")+" <strong>"+str.setNum(hly_debitTraverse,'f',2)+"</strong> m3.</p>";
    resu += "<p></p>";
    resu += "<p><span style=\"font-size: 12pt; color: #ff9900;\"><strong>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("D�bit Total")+"</strong></span></p>";
    hly_debitTotal = hly_debitPerche+hly_debitTraverse+hly_debitCroix+hly_debitMontantsAetC+hly_debitMontantB;
    resu += "<p>"+QObject::tr("Soit un d�bit total de bois pour toute l\'h�liyourte de")+" <strong>"+str.setNum(hly_debitTotal,'f',2)+"</strong> m3.</p>";

    return resu;
}

QString heliyourte::aideGenerale()
{
    QString str,str2,str3,resu;

    resu = "<html><p><span style=\"font-size: 12pt; color: #ff9900;\"><strong>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;A) "+QObject::tr("G�n�ralit�s")+"</strong></span></p>";
    resu += "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("L\'h�liyourte est une formidable �volution de la yourte traditionnelle, se basant sur les charpentes autoport�es, mise au point par Florian Journot. C\'est costaud, facile � r�aliser, � monter, moins r�p�titif � fabriquer qu\'une yourte classique. Il est aussi beaucoup plus simple de rajouter des ouvertures (et de poser des meubles), les murs �tant droits. Pour en savoir plus, n\'h�sitez pas � visiter")+" <a href=\"http://heliyourte.blogspot.fr\">"+QObject::tr("son site")+"</a>.</p>";
    resu += "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("L\'h�liyourte est un concept en license libre Cr�ative Commons, les publications au sujet de l\'h�liyourte doivent donc citer leur source et mentionner le label Cr�ative Commons")+".</p>";
    resu += "<p align=center><a href=\"http://creativecommons.org/licenses/by-nc-sa/3.0/fr/\"><img height=\"31\" width=\"88\" src=\":/images/licenseCC\" /></a></p>";
    resu += "<p><br /></p>";
    resu += "<p><span style=\"color: #ff9900;\"><strong><span style=\"font-size: 12pt;\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;B) "+QObject::tr("La structure")+"</span></strong></span></p>";
    resu += "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("D�coupez et assemblez les diff�rents �l�ments en testant au fur et � mesure les assemblages dans les poteaux, �a sera plus simple � ajuster maintenant qu\'au montage. Pour les �l�ments de croix, une foix en place il vont se croiser � peu pr�s dans le m�me plan ... Si vous avez choisi une �paisseur fine, pas de probl�mes, sinon, il pourra �tre n�cessaire de les amincir l� o� ils se croisent, sans pour autant raliser un mi-bois. Il peut �tre int�ressant de travailler directement avec du bois s�ch� et rabot�, vous �conomiserez du temps et des bras")+".<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; "+QObject::tr("Pr�voyez � l\'avance la position de vos ouvertures, car vous ne serez pas oblig�s de tailler de croix pour les murs o� seront pos�es les ouvertures, et donc pas forc�ment de trous dans les montants de chaque c�t� de l'\'ouverture pour les croix. Ca vous �vitera du travail et �a sera plus \"propre\"")+".</p>";
    resu += "<p align=center><img height=\"400\" width=\"297\" src=\":/images/hly/hlyAssemblage\" /></p>";
    resu += "<p><br /></p>";
    resu += "<p><span style=\"color: #ff9900;\"><strong><span style=\"font-size: 12pt;\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;C) "+QObject::tr("Implantation")+"</span></strong></span></p>";
    resu += "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Pour pr�parez le plancher qui va acceuillir la yourte, voici les dimensions � prendre en compte")+" : <br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;r ("+QObject::tr("rayon du cercle passant par les poteaux")+") : <strong> "+str.setNum(hel_rayonYourte+0.02,'f',2)+" m</strong><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;h : <strong> "+str2.setNum((hel_rayonYourte+0.02)*qCos(hel_angleDivision/2.0),'f',2)+" m</strong><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;d ("+QObject::tr("distance entre les poteaux")+") : <strong> "+str3.setNum(2.0*(hel_rayonYourte+0.02)*qSin(hel_angleDivision/2.0),'f',2)+" m</strong></p>";
    resu += "<p align=center><img height=\"649\" width=\"600\" src=\":/images/hly/hlyImplantation\" /></p>";
    resu += "<p><br /></p>";
    resu += "<p><span style=\"font-size: 12pt;\"><strong><span style=\"color: #ff9900;\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;D) "+QObject::tr("Le montage")+"</span></strong></span></p>";
    resu += "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Dans un premier temps, nous allons �videmment commencer par assembler les murs. Pour le premier, vous pouvez le faire au sol. Positionnez � peu pr�s les 2 poteaux, un de chaque c�t�, embo�tez l\'�l�ment de croix qui, lorsqu\'on est � l\'int�rieur de la yourte, part en bas � gauche et finit en haut � droite. Il sera s�rement n�cessaire d\incliner un des poteaux afin de venir clipser l\'�l�ment de croix dans ses 2 trous")+".<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Une fois cette �tape r�alis�e, vous pouvez mettre en place la traverse entre les deux poteaux")+".<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Vous pourrez enfin venir verrouiller votre mur avec le deuxi�me �l�ment de croix, en le clipsant d\'abord dans son trou en bas � droite puis en venant le clipser en haut � gauche dans son encoche. Afin qu'il ne sorte pas de son encoche, vous pourrez le visse dans le montant C. Une vis au centre de la croix sera aussi utile, vous pouvez la cacher en la mettant depuis l'ext�rieur de la yourte")+".</p>";
    resu += "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Une fois tout les murs assembl�s, il vous faut poser les perches. La premi�re sera mise en place et soutenue en l\'air. Vous pouvez utiliser � cette effet un \"�tai\" fait maison que vous enleverez � la fin. La deuxi�me vient donc se fixer sur la premi�re, et ainsi de suite jusqu\'� la derni�re, qu\'il faut arriver � la fois � clipser sur l\'avant derni�re et � glisser sous la premi�re, ce qui se fait en soulevant un peu l\'�tai de la premi�re. Et voil� !")+"</p>";
    resu += "<p align=center><img height=\"300\" width=\"400\" src=\":/images/hly/hlyTonoo\" /></p>";
    resu += "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Afin de consolider l\'h�liyourte et d\'augmenter le support de la toile, il faut rajouter des liteaux, en les posant sur le toit dans le sens inverse du sens de \"rotation\" des perches. Le nombre de liteaux d�pend de la taille de votre yourte, entre 2 ou 3 fois plus que les perches, en section 35*35 par exemple")+".</p>";
    resu += "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+QObject::tr("Plus qu\'� rajouter une sangle de maintien qui vient ceinturer l\'h�liyourte au niveau du haut des murs (comme sur une yourte classique), puis les fen�tres, les portes, l'isolant et la toile")+".</p>";
    resu += "<p><br /></p></html>";

    return resu;
}

void heliyourte::calcul()
{
    // general
    hel_rayonYourte = hel_diametreYourte/2.0;
    hel_angleDivision = 2.0*pi/hel_nbrePans;
    hel_dIntMur = 2.0*hel_rayonYourte*qSin(hel_angleDivision/2.0);

    // tonoo
    double phel_A, phel_B, phel_C, phel_Delta, phel_X1, phel_X2;
    double phel_hIntTonoo, phel_lprimePerche, phel_lsecondePerche, phel_lPerche;

    phel_A = qPow(qCos(hel_angleDivision/2.0),2.0);
    phel_B = -qPow(hel_rayonYourte,2.0);
    phel_C = qPow(hel_rayonYourte,4.0)*qPow(qSin(hel_angleDivision/2.0),2.0);
    phel_Delta = qPow(phel_B,2.0)-4.0*phel_A*phel_C;
    phel_X1 = (-phel_B+qSqrt(phel_Delta))/(2.0*phel_A);
    phel_X2 = (-phel_B-qSqrt(phel_Delta))/(2.0*phel_A);
    hel_rayonTonoo = qSqrt(phel_X2);
    hel_diametreTonoo = 2.0*hel_rayonTonoo;

    phel_hIntTonoo = hel_rayonTonoo*qCos(hel_angleDivision/2.0);
    phel_lprimePerche = qSqrt(qPow(hel_rayonYourte,2.0)-qPow(phel_hIntTonoo,2.0));
    hel_dIntTonoo = 2.0*hel_rayonTonoo*qSin(hel_angleDivision/2.0);
    phel_lPerche = phel_lprimePerche+hel_dIntTonoo/2.0;
    phel_lsecondePerche = phel_lprimePerche-hel_dIntTonoo/2.0;


    // perches
    double phel_z1, phel_Lhaut2, phel_Lhaut1, phel_Lhaut0, phel_Lhaut3, phel_Lbas;

    hel_decalageTigeRapportBord = (hel_epaisseurPerche/qTan(hel_angleDivision)+hel_epaisseurPerche/qSin(hel_angleDivision))/2.0;
    hel_AB = qSqrt(qPow((hel_dIntTonoo/2.0-phel_lprimePerche),2.0)+qPow((hel_rayonYourte-hel_rayonTonoo),2.0)*qPow(qTan(hel_penteToit),2.0));
    hel_angleInclinaisonPerches = qAcos(qAbs(hel_dIntTonoo/2.0-phel_lprimePerche)/hel_AB);
    hel_retombeeMiniPerches = (2.0*hel_decalageTigeRapportBord+hel_dIntTonoo)*qSin(hel_angleInclinaisonPerches);
    phel_z1 = hel_depassementHautPerche*qTan(hel_angleInclinaisonPerches);
    phel_Lhaut2 = qSin(hel_angleInclinaisonPerches)*(hel_retombeeMiniPerches-phel_z1);
    phel_Lhaut1 = hel_depassementHautPerche/qCos(hel_angleInclinaisonPerches);
    phel_Lhaut0 = hel_retombeeMiniPerches/qTan(hel_angleInclinaisonPerches);
    phel_Lhaut3 = hel_decalageTigeRapportBord/qCos(hel_angleInclinaisonPerches);
    phel_Lbas = hel_retombeeMiniPerches*qTan(hel_angleInclinaisonPerches);
    hel_longueurMiniPlanchesPerches = hel_AB+phel_Lhaut2+phel_Lhaut1+phel_Lhaut0+phel_Lbas-phel_Lhaut3;

    // traverse et montants
    hel_retombeePlanchesMontant = 3.0*(hel_epaisseurCroix+0.005);
    hel_epaisseurPlancheAetC = hel_epaisseurCroix;
    hel_epaisseurPlancheB = hel_epaisseurPerche;
    hel_epaisseurTraverse = hel_epaisseurPerche;
    hel_angleBeta3 = pi/2.0-hel_angleDivision;

    QVector<QVector2D> phel_H;

    phel_H.resize(20);
    phel_H[6].setX((hel_epaisseurPlancheAetC+hel_epaisseurPlancheB)/2.0);
    phel_H[6].setY(-hel_retombeePlanchesMontant/2.0);
    phel_H[8].setX(hel_dIntMur-qCos(hel_angleDivision)*phel_H[6].x());
    phel_H[8].setY(qSin(hel_angleDivision)*phel_H[6].x());
    phel_H[5].setX(phel_H[8].x()-qCos(hel_angleBeta3)*hel_retombeePlanchesMontant/2.0);
    phel_H[5].setY(phel_H[8].y()-qSin(hel_angleBeta3)*hel_retombeePlanchesMontant/2.0);
    phel_H[7].setX(hel_dIntMur);phel_H[7].setY(0.0);
    phel_BetaTraverse = qAtan((phel_H[5].y()-phel_H[6].y())/(phel_H[5].x()-phel_H[6].x()));
    phel_H[10].setX(phel_H[6].x()-qSin(phel_BetaTraverse)*hel_epaisseurTraverse/2.0);phel_H[10].setY(phel_H[6].y()+qCos(phel_BetaTraverse)*hel_epaisseurTraverse/2.0);
    phel_H[11].setX(hel_epaisseurPlancheB/2.0+hel_epaisseurPlancheAetC);phel_H[11].setY(phel_H[10].y());
    phel_H[9].setX(phel_H[11].x());phel_H[9].setY(phel_H[10].y()+(phel_H[11].x()-phel_H[10].x())*qTan(hel_angleBeta3));

    hel_largeurTrouTraverseMontantCdroit = 2.0*(phel_H[9].y()-phel_H[6].y());
    phel_H[18].setX(phel_H[6].x()+qSin(phel_BetaTraverse)*hel_epaisseurTraverse/2.0);phel_H[18].setY(phel_H[6].y()-qCos(phel_BetaTraverse)*hel_epaisseurTraverse/2.0);
    phel_H[19].setX(hel_epaisseurPlancheB/2.0+hel_epaisseurPlancheAetC);phel_H[19].setY(phel_H[18].y());
    phel_H[12].setX(phel_H[19].x());phel_H[12].setY(phel_H[18].y()+(phel_H[19].x()-phel_H[18].x())*qTan(phel_BetaTraverse));
    phel_H[15].setX(phel_H[5].x()-qSin(phel_BetaTraverse)*hel_epaisseurTraverse/2.0);phel_H[15].setY(phel_H[5].y()-qCos(phel_BetaTraverse)*hel_epaisseurTraverse/2.0);
    phel_H[16].setX(hel_dIntMur-qCos(hel_angleDivision)*(hel_epaisseurPlancheAetC+hel_epaisseurPlancheB/2.0));phel_H[16].setY(qSin(hel_angleDivision)*(hel_epaisseurPlancheAetC+hel_epaisseurPlancheB/2.0));
    phel_H[17].setX(phel_H[5].x()+qSin(phel_BetaTraverse)*hel_epaisseurTraverse/2.0);phel_H[17].setY(phel_H[5].y()+qCos(phel_BetaTraverse)*hel_epaisseurTraverse/2.0);

    double phel_b1, phel_b2, phel_b3, phel_b4;
    phel_b1 = phel_H[15].y()-phel_H[15].x()*qTan(phel_BetaTraverse);
    phel_b2 = phel_H[16].y()-phel_H[16].x()*qTan(hel_angleBeta3);
    phel_H[14].setX((phel_b2-phel_b1)/(-qTan(hel_angleBeta3)+qTan(phel_BetaTraverse)));phel_H[14].setY(qTan(phel_BetaTraverse)*phel_H[14].x()+phel_b1);
    phel_b3 = phel_H[17].y()-phel_H[17].x()*qTan(phel_BetaTraverse);
    phel_b4 = phel_b2;
    phel_H[13].setX((phel_b4-phel_b3)/(qTan(phel_BetaTraverse)-qTan(hel_angleBeta3)));phel_H[13].setY(qTan(phel_BetaTraverse)*phel_H[13].x()+phel_b3);

    hel_H14_H5 = (phel_H[14]-phel_H[5]).length();
    hel_H12_H14 = (phel_H[12]-phel_H[14]).length();
    hel_H9_H13 = (phel_H[9]-phel_H[13]).length();
    hel_tetonTraverse = (hel_epaisseurPlancheAetC+hel_epaisseurPlancheB/2.0)-0.002;
    hel_hauteurMiBoisTraverse = hel_retombeeTraverse/2.0;
    hel_largeurTrouTraverseMontantAdroit = 2.0*qSqrt(qPow(hel_H14_H5,2.0)-qPow(hel_epaisseurPlancheAetC,2.0));
    hel_largeurTrouTraverseMontantAbiais = (phel_H[13]-phel_H[14]).length();
    hel_angleTrouTraverseMontantA = pi/2.0-(hel_angleBeta3-phel_BetaTraverse);

    hel_longueurMiniPlanchesTraverse = hel_H9_H13+2.0*hel_tetonTraverse;
    hel_angleCoupeTraverseGauche = phel_BetaTraverse;
    hel_angleCoupeTraverseDroite = hel_angleTrouTraverseMontantA;

    // croix
    hel_margeHautBas = 0.05;

    double phel_crA, phel_crB, phel_crC, phel_crE, phel_crF, phel_crG, phel_crDelta;
    phel_crA = hel_hauteurMurs-2.0*hel_margeHautBas-hel_retombeeTraverse;
    phel_crB = -hel_dIntMur-hel_epaisseurPlancheB;
    phel_crC = 2.0*hel_retombeeCroix;
    phel_crE = qPow(phel_crA,2.0)+qPow(phel_crB,2.0);
    phel_crF = -2.0*phel_crA*phel_crC;
    phel_crG = qPow(phel_crC,2.0)-qPow(phel_crB,2.0);
    phel_crDelta = qPow(phel_crF,2.0)-4.0*phel_crE*phel_crG;
    hel_OmegaCroix = qAcos((-phel_crF+qSqrt(phel_crDelta))/(2.0*phel_crE));
    if(hel_OmegaCroix>radians(45))
    {
        hel_OmegaCroix = radians(45);
    }
    hel_margeHautBas = -0.5*(qTan(hel_OmegaCroix)*(hel_dIntMur+hel_epaisseurPlancheB)+2.0*hel_retombeeCroix/qCos(hel_OmegaCroix)-hel_hauteurMurs+hel_retombeeTraverse);
    double phel_lprimeCroix, phel_lsecondeCroix;
    phel_lprimeCroix = (hel_dIntMur+hel_epaisseurPlancheB)/qCos(hel_OmegaCroix);
    phel_lsecondeCroix = hel_retombeeCroix*qTan(hel_OmegaCroix);
    hel_longueurMiniPlanchesCroix = phel_lprimeCroix+phel_lsecondeCroix;

    double phel_epaisseurVirtuelleAtournedeBeta3, phel_epaisseurVirtuelleBtournedeBeta3;

    hel_cr.resize(28);
    hel_cr_2.resize(28);
    // cote montant C
    hel_cr[0].setX(-hel_epaisseurPlancheB/2.0);hel_cr[0].setY(qTan(hel_OmegaCroix)*hel_epaisseurPlancheB/2.0+0.005);
    hel_cr[1].setX(-hel_epaisseurPlancheB);hel_cr[1].setY(hel_cr[0].y()+hel_epaisseurPlancheB);
    hel_cr[6].setX(-hel_epaisseurPlancheB-hel_epaisseurPlancheAetC);hel_cr[6].setY(hel_cr[1].y());
    hel_cr[2].setX(hel_cr[6].x());hel_cr[2].setY(hel_cr[1].y()+0.007);
    hel_cr[3].setX((hel_cr[1].y()-hel_cr[1].x()*((hel_cr[1].y()-hel_cr[2].y())/(hel_cr[1].x()-hel_cr[2].x())))/(-qTan(hel_OmegaCroix)-((hel_cr[1].y()-hel_cr[2].y())/(hel_cr[1].x()-hel_cr[2].x()))));hel_cr[3].setY(-qTan(hel_OmegaCroix)*hel_cr[3].x());
    hel_cr[12].setX(hel_cr[6].x());hel_cr[12].setY(hel_retombeeCroix/qCos(hel_OmegaCroix)+qTan(hel_OmegaCroix)*(hel_epaisseurPlancheAetC+hel_epaisseurPlancheB));
    hel_cr[11].setX(hel_cr[1].x());hel_cr[11].setY(hel_epaisseurPlancheB*qTan(hel_OmegaCroix));
    hel_cr[4].setX(hel_cr[12].x());hel_cr[4].setY(hel_cr[12].y()-(hel_cr[1].y()-hel_cr[11].y()));
    hel_cr[5].setX(hel_cr[3].x());hel_cr[5].setY(hel_cr[3].y()+hel_retombeeCroix/qCos(hel_OmegaCroix));
    hel_cr[7].setX(-hel_epaisseurPlancheB);hel_cr[7].setY(hel_cr[4].y());
    hel_cr[8].setX(hel_cr[7].x());hel_cr[8].setY(hel_cr[7].y()-(hel_cr[2].y()-hel_cr[6].y()));
    hel_cr[10].setX(-0.002);hel_cr[10].setY(hel_cr[1].y());
    hel_cr[9].setX(hel_cr[10].x());hel_cr[9].setY(((hel_cr[8].y()-hel_cr[4].y())/(hel_cr[8].x()-hel_cr[4].x()))*hel_cr[9].x()+hel_cr[4].y()-hel_cr[4].x()*((hel_cr[8].y()-hel_cr[4].y())/(hel_cr[8].x()-hel_cr[4].x()))-0.025);

    // cote montant A
    phel_epaisseurVirtuelleAtournedeBeta3 = hel_epaisseurCroix/qTan(hel_angleBeta3)+hel_epaisseurPlancheAetC/qSin(hel_angleBeta3);
    phel_epaisseurVirtuelleBtournedeBeta3 = hel_epaisseurPlancheB/qSin(hel_angleBeta3)-hel_epaisseurCroix/qTan(hel_angleBeta3);
    hel_cr[13].setX(-phel_epaisseurVirtuelleBtournedeBeta3/2.0);hel_cr[13].setY(hel_cr[0].y());
    hel_cr[14].setX(-phel_epaisseurVirtuelleBtournedeBeta3);hel_cr[14].setY(hel_cr[1].y());
    hel_cr[19].setX(-phel_epaisseurVirtuelleBtournedeBeta3-phel_epaisseurVirtuelleAtournedeBeta3);hel_cr[19].setY(hel_cr[14].y());
    hel_cr[15].setX(hel_cr[19].x());hel_cr[15].setY(hel_cr[2].y());
    hel_cr[16].setX((hel_cr[14].y()-hel_cr[14].x()*((hel_cr[14].y()-hel_cr[15].y())/(hel_cr[14].x()-hel_cr[15].x())))/(-qTan(hel_OmegaCroix)-((hel_cr[14].y()-hel_cr[15].y())/(hel_cr[14].x()-hel_cr[15].x()))));hel_cr[16].setY(-qTan(hel_OmegaCroix)*hel_cr[16].x());
    hel_cr[25].setX(hel_cr[19].x());hel_cr[25].setY(hel_retombeeCroix/qCos(hel_OmegaCroix)+qTan(hel_OmegaCroix)*(phel_epaisseurVirtuelleAtournedeBeta3+phel_epaisseurVirtuelleBtournedeBeta3));
    hel_cr[24].setX(hel_cr[14].x());hel_cr[24].setY(phel_epaisseurVirtuelleBtournedeBeta3*qTan(hel_OmegaCroix));
    hel_cr[17].setX(hel_cr[19].x());hel_cr[17].setY(hel_cr[25].y()-(hel_cr[14].y()-hel_cr[24].y()));
    hel_cr[18].setX(hel_cr[16].x());hel_cr[18].setY(hel_cr[16].y()+hel_retombeeCroix/qCos(hel_OmegaCroix));
    hel_cr[20].setX(-phel_epaisseurVirtuelleBtournedeBeta3);hel_cr[20].setY(hel_cr[17].y());
    hel_cr[21].setX(hel_cr[20].x());hel_cr[21].setY(hel_cr[20].y()-(hel_cr[15].y()-hel_cr[19].y()));
    hel_cr[23].setX(0.0);hel_cr[23].setY(hel_cr[14].y());
    hel_cr[22].setX(hel_cr[23].x());hel_cr[22].setY(((hel_cr[21].y()-hel_cr[17].y())/(hel_cr[21].x()-hel_cr[17].x()))*hel_cr[22].x()+hel_cr[17].y()-hel_cr[17].x()*((hel_cr[21].y()-hel_cr[17].y())/(hel_cr[21].x()-hel_cr[17].x()))-0.025);
    // centre
    hel_cr[26].setX(-hel_epaisseurPlancheAetC-hel_epaisseurPlancheB-((hel_H12_H14+hel_H9_H13)/2.0)/2.0);hel_cr[26].setY(hel_cr[26].x()*(-qTan(hel_OmegaCroix))+hel_retombeeCroix/(2.0*qCos(hel_OmegaCroix)));

    double phel_cr_ltrou, phel_cr_decbord, phel_cr_lseconde, phel_cr_lprime, phel_cr_interB;
    QVector2D phel_cr_ba, phel_cr_ba_bord, phel_cr_bc, phel_cr_bc_bord;
    phel_cr_ltrou = hel_epaisseurCroix/qSin(hel_angleBeta3);
    phel_cr_decbord = (hel_retombeePlanchesMontant-(qTan(hel_angleDivision)*hel_epaisseurPlancheAetC+phel_cr_ltrou))/2.0;
    phel_cr_lseconde = hel_epaisseurPlancheB*qSin(hel_angleBeta3)/2.0;
    phel_cr_lprime = phel_cr_decbord*qCos(hel_angleBeta3);
    phel_cr_interB = hel_dIntMur-hel_epaisseurPlancheB/2.0-(phel_cr_lprime+phel_cr_lseconde);

    phel_cr_ba.setX(hel_cr[14].x());phel_cr_ba.setY(hel_cr[14].y());
    phel_cr_ba_bord.setX((-phel_cr_ba.y()+phel_cr_ba.x()/qTan(hel_OmegaCroix))/(qTan(hel_OmegaCroix)+1.0/qTan(hel_OmegaCroix)));phel_cr_ba_bord.setY(-qTan(hel_OmegaCroix)*phel_cr_ba_bord.x());
    phel_cr_bc.setX(phel_cr_ba.x()-phel_cr_interB);phel_cr_bc.setY(qTan(hel_OmegaCroix)*(phel_cr_interB-phel_cr_ba.x())+hel_retombeeCroix/qCos(hel_OmegaCroix)-(hel_cr[1].y()-hel_cr[11].y()));
    phel_cr_bc_bord.setX((-phel_cr_bc.y()+phel_cr_bc.x()/qTan(hel_OmegaCroix))/(qTan(hel_OmegaCroix)+1.0/qTan(hel_OmegaCroix)));phel_cr_bc_bord.setY(-qTan(hel_OmegaCroix)*phel_cr_bc_bord.x());
    phel_cr_distanceEntre2B = (phel_cr_bc_bord-phel_cr_ba_bord).length();

    // une petite rotation de -omega ca fait du bien
    for(int i=0;i<27;i++)
    {
        hel_cr_2[i].setX(hel_cr[i].x()*qCos(-hel_OmegaCroix)+hel_cr[i].y()*qSin(-hel_OmegaCroix));
        hel_cr_2[i].setY(-hel_cr[i].x()*qSin(-hel_OmegaCroix)+hel_cr[i].y()*qCos(-hel_OmegaCroix));
    }

    hel_cr_2[27].setX(hel_cr_2[26].x());hel_cr_2[27].setY(0.0);

    // puis une petite translation c est toujours bon
    double valeurTranslation = hel_cr_2[1].x();
    for(int i=0;i<13;i++)
    {
        hel_cr_2[i].setX(-hel_cr_2[i].x()+valeurTranslation);
        hel_cr_2[i].setY(hel_retombeeCroix-hel_cr_2[i].y());
    }

    double valeurTranslation2 = hel_cr_2[14].x();
    for(int i=13;i<26;i++)
    {
        hel_cr_2[i].setX(hel_cr_2[i].x()- valeurTranslation2 +phel_cr_distanceEntre2B);
    }

    hel_margeTrous = 0.001;


    hel_DdansA.bas = hel_margeHautBas+hel_cr[14].y();
    hel_DdansA.haut = hel_margeHautBas+hel_cr[17].y()+hel_margeTrous;
    hel_DdansA.hauteur = hel_DdansA.haut-hel_DdansA.bas;
    hel_DdansA.largeur = (hel_margeTrous+hel_epaisseurCroix)/qCos(hel_angleDivision);
    hel_DdansA.angleBiais = 90-degres(hel_angleBeta3-phel_BetaTraverse);
    hel_DdansA.distanceRapportBordInt = (hel_retombeePlanchesMontant-(hel_epaisseurPlancheAetC*qTan(hel_angleDivision)+hel_DdansA.largeur))/2.0;

    hel_BdansC.bas = hel_margeHautBas+hel_cr[14].y()+hel_retombeeCroix/qCos(hel_OmegaCroix);
    hel_BdansC.haut = hel_margeHautBas+hel_cr[4].y()+hel_margeTrous+hel_retombeeCroix/qCos(hel_OmegaCroix);
    hel_BdansC.hauteur = hel_BdansC.haut-hel_BdansC.bas;
    hel_BdansC.largeur = hel_margeTrous+hel_epaisseurCroix;
    hel_BdansC.angleBiais = 0;
    hel_BdansC.distanceRapportBordInt = (hel_retombeePlanchesMontant-hel_BdansC.largeur)/2.0;

    hel_AdansC.haut = phel_cr_bc.y()-phel_cr_ba.y()+hel_DdansA.bas+hel_margeTrous;
    hel_AdansC.bas = hel_AdansC.haut-hel_margeTrous-(hel_cr[4].y()-hel_cr[1].y());
    hel_AdansC.hauteur = hel_AdansC.haut-hel_AdansC.bas;
    hel_AdansC.largeur = hel_margeTrous+hel_epaisseurCroix;
    hel_AdansC.angleBiais = 0;
    hel_AdansC.distanceRapportBordInt = 0;

    hel_CdansA.haut = hel_BdansC.bas+hel_margeTrous+phel_cr_bc.y()-phel_cr_ba.y();
    hel_CdansA.bas = hel_CdansA.haut-hel_margeTrous-(hel_cr[17].y()-hel_cr[14].y());
    hel_CdansA.hauteur = hel_CdansA.haut-hel_CdansA.bas;
    hel_CdansA.largeur = (hel_margeTrous+hel_epaisseurCroix)/qCos(hel_angleDivision);
    hel_CdansA.angleBiais = hel_DdansA.angleBiais;
    hel_CdansA.distanceRapportBordInt = (hel_retombeePlanchesMontant-(hel_epaisseurPlancheAetC*qTan(hel_angleDivision)+hel_CdansA.largeur))/2.0;

    hel_EdansC.bas = hel_hauteurMurs-hel_retombeeTraverse;
    hel_EdansC.haut = hel_EdansC.bas+hel_margeTrous+hel_hauteurMiBoisTraverse;
    hel_EdansC.hauteur = hel_EdansC.haut-hel_EdansC.bas;
    hel_EdansC.largeur = hel_margeTrous+hel_epaisseurTraverse;
    hel_EdansC.angleBiais = 0;
    hel_EdansC.distanceRapportBordInt = (hel_retombeePlanchesMontant-hel_EdansC.largeur)/2.0;

    hel_FdansA.haut = hel_EdansC.haut;
    hel_FdansA.bas = hel_EdansC.bas;
    hel_FdansA.hauteur = hel_FdansA.haut-hel_FdansA.bas;
    hel_FdansA.largeur = (hel_margeTrous+hel_epaisseurTraverse)/qCos(hel_angleDivision);
    hel_FdansA.angleBiais = hel_DdansA.angleBiais;
    hel_FdansA.distanceRapportBordInt = (hel_retombeePlanchesMontant-(hel_epaisseurPlancheAetC*qTan(hel_angleDivision)+hel_FdansA.largeur))/2.0;

    hel_montantB_1.bas = 0;
    hel_montantB_1.haut = hel_DdansA.bas-(hel_cr[14].y()-hel_cr[13].y())-5.0*hel_margeTrous;
    hel_montantB_1.hauteur = hel_montantB_1.haut-hel_montantB_1.bas;

    hel_montantB_2.bas = hel_BdansC.haut;
    hel_montantB_2.haut = hel_AdansC.bas;
    hel_montantB_2.hauteur = hel_montantB_2.haut-hel_montantB_2.bas;

    hel_montantB_3.bas = hel_CdansA.haut+(hel_cr[14].y()-hel_cr[13].y())+5.0*hel_margeTrous;
    hel_montantB_3.haut = hel_EdansC.bas;
    hel_montantB_3.hauteur = hel_montantB_3.haut-hel_montantB_3.bas;

    //calcul de l angle de rotation selon y du morceau de la croix un peu vrille
    QVector2D cr1,cr2,cr3;
    cr1 = QVector2D(hel_epaisseurPlancheB/2.0,-hel_retombeePlanchesMontant+hel_AdansC.largeur);
    cr3 = QVector2D(phel_cr_distanceEntre2B-qSin(hel_angleBeta3)*hel_epaisseurPlancheB/2.0,qCos(hel_angleBeta3)*hel_epaisseurPlancheB/2.0);
    cr2 = QVector2D(cr3.x()-qCos(hel_angleBeta3)*(hel_DdansA.distanceRapportBordInt),cr3.y()-qSin(hel_angleBeta3)*(hel_DdansA.distanceRapportBordInt));
    hel_angleVrilleCroix = qAtan((cr2.y()-cr1.y())/(cr2.x()-cr1.x()));

    cr1 = QVector2D(hel_epaisseurPlancheB/2.0,-hel_retombeePlanchesMontant+hel_BdansC.largeur+hel_BdansC.distanceRapportBordInt+hel_margeTrous);
    cr3 = QVector2D(phel_cr_distanceEntre2B-qSin(hel_angleBeta3)*hel_epaisseurPlancheB/2.0,qCos(hel_angleBeta3)*hel_epaisseurPlancheB/2.0);
    cr2 = QVector2D(cr3.x()-qCos(hel_angleBeta3)*(hel_CdansA.distanceRapportBordInt),cr3.y()-qSin(hel_angleBeta3)*(hel_CdansA.distanceRapportBordInt));
    hel_angleVrilleCroix2 = qAtan((cr2.y()-cr1.y())/(cr2.x()-cr1.x()));

    //on reprend les coordonnes de la perche
    hel_perche_face << QVector2D(0.0,hel_hauteurMurs);
    hel_perche_face << QVector2D(0.0,hel_montantB_3.haut+hel_hauteurMiBoisTraverse);
    hel_perche_face << QVector2D(hel_retombeePlanchesMontant-hel_EdansC.distanceRapportBordInt,hel_perche_face[1].y());
    hel_perche_face << QVector2D(hel_perche_face[2].x(),hel_montantB_3.haut);

    double aa, bb1, bb2;
    aa = tan(hel_angleInclinaisonPerches);
    bb1 = hel_perche_face[0].y()-aa*hel_perche_face[0].x();
    bb2 = hel_perche_face[0].y()-hel_retombeeMiniPerches*qCos(hel_angleInclinaisonPerches)-aa*(hel_perche_face[0].x()+hel_retombeeMiniPerches*qSin(hel_angleInclinaisonPerches));

    hel_perche_face << QVector2D((hel_perche_face[3].y()-bb2)/aa,hel_perche_face[3].y());
    hel_perche_face << QVector2D(hel_perche_face[2].x(),aa*hel_perche_face[2].x()+bb1);

    QVector2D B;
    B = QVector2D(hel_AB*qCos(hel_angleInclinaisonPerches),hel_AB*qSin(hel_angleInclinaisonPerches));
    double lh;
    lh = hel_retombeeMiniPerches/qSin(hel_angleInclinaisonPerches);

    hel_perche_face << QVector2D(B.x()-hel_decalageTigeRapportBord,aa*(B.x()-hel_decalageTigeRapportBord)+bb1);
    hel_perche_face << QVector2D(hel_perche_face[6].x()+hel_epaisseurPerche/qSin(hel_angleDivision),hel_perche_face[6].y());
    hel_perche_face << QVector2D(hel_perche_face[7].x(),aa*hel_perche_face[7].x()+bb1);
    hel_perche_face << QVector2D((hel_perche_face[7].y()+hel_retombeeTonoo-bb1)/aa,hel_perche_face[7].y()+hel_retombeeTonoo);
    hel_perche_face << QVector2D(B.x()+hel_dIntTonoo-hel_decalageTigeRapportBord+hel_epaisseurPerche/qTan(hel_angleDivision),hel_perche_face[7].y());
    hel_perche_face << QVector2D(hel_perche_face[10].x(),aa*hel_perche_face[10].x()+bb2);
    hel_perche_face << QVector2D((hel_perche_face[10].y()-bb2)/aa,hel_perche_face[10].y());
    hel_perche_face << QVector2D(hel_perche_face[12].x()+hel_depassementHautPerche,(hel_perche_face[12].x()+hel_depassementHautPerche)*aa+bb2);
    hel_perche_face << QVector2D(hel_perche_face[13].x(),hel_perche_face[9].y());

    hel_perche_face << QVector2D(B.x(),hel_perche_face[7].y());
    hel_perche_face << QVector2D(B.x()+hel_dIntTonoo,hel_perche_face[7].y());

    hel_hauteurTotale = hel_perche_face[9].y();

    double rayon_tige;
    rayon_tige = 0.005;

    for(int i=0;i<17;i++)
    {
        hel_perche_derriere << hel_perche_face[i];
    }

    hel_perche_derriere[7].setX(B.x()+hel_decalageTigeRapportBord);
    hel_perche_derriere[8].setX(hel_perche_derriere[7].x());
    hel_perche_derriere[8].setY(aa*hel_perche_derriere[8].x()+bb1);


    bool percheTropEpaisse = false;
    // si la perche est tres epaisse
    if(hel_perche_derriere[8].x()>hel_perche_derriere[9].x())
    {
        hel_perche_derriere[8].setY(hel_perche_derriere[9].y());
        percheTropEpaisse = true;
    }

    hel_perche_derriere[10].setX(B.x()+hel_dIntTonoo-hel_decalageTigeRapportBord);
    hel_perche_derriere[11].setX(hel_perche_derriere[10].x());
    hel_perche_derriere[11].setY(aa*hel_perche_derriere[11].x()+bb2);

    double dx,dy;
    dx = hel_perche_face[4].x();
    dy = hel_perche_face[4].y();
    for(int i=0;i<17;i++)
    {
        hel_perche_face[i] -= QVector2D(dx,dy);
        hel_perche_derriere[i] -= QVector2D(dx,dy);
    }

    double engle = -hel_angleInclinaisonPerches;

    for(int i=0;i<17;i++)
    {
        double tx,ty;
        tx = hel_perche_face[i].x();
        ty = hel_perche_face[i].y();
        hel_perche_face[i].setX(tx*qCos(engle)-ty*qSin(engle));
        hel_perche_face[i].setY(tx*qSin(engle)+ty*qCos(engle));
        tx = hel_perche_derriere[i].x();
        ty = hel_perche_derriere[i].y();
        hel_perche_derriere[i].setX(tx*qCos(engle)-ty*qSin(engle));
        hel_perche_derriere[i].setY(tx*qSin(engle)+ty*qCos(engle));
    }
    dx = hel_perche_face[1].x();
    for(int i=0;i<17;i++)
    {
        hel_perche_face[i].setX(hel_perche_face[i].x()-dx);
        hel_perche_derriere[i].setX(hel_perche_derriere[i].x()-dx);
    }
    hel_longueurMiniPlanchesPerches = hel_perche_face[14].x();

}

double heliyourte::surfaceAuSol()
{
    double surf;
    surf = (hel_nbrePans*hel_dIntMur*hel_rayonYourte*qCos(hel_angleDivision/2.0))/2.0;
    return surf;
}

double heliyourte::surfaceMur()
{
    double surf;
    surf = (hel_nbrePans*hel_dIntMur*hel_hauteurMurs);
    return surf;
}

double heliyourte::surfaceToit()
{
    double surf,ha;
    ha = hel_rayonYourte*qTan(hel_penteToit);
    surf = pi*hel_rayonYourte*qSqrt(qPow(hel_rayonYourte,2.0)+qPow(ha,2.0))-pi*hel_rayonTonoo*qSqrt(qPow(hel_rayonTonoo,2.0)+qPow((ha+hel_hauteurMurs-hel_hauteurTotale),2.0));
    return surf;
}

double heliyourte::volume()
{
    double volum,ha;
    ha = hel_rayonYourte*qTan(hel_penteToit);
    volum = surfaceAuSol()*hel_hauteurMurs+surfaceAuSol()*ha/3.0-(ha+hel_hauteurMurs-hel_hauteurTotale)*pi*qPow(hel_rayonTonoo,2.0)/3.0;
    return volum;
}

double heliyourte::hauteurTonoo()
{
    return hel_hauteurTotale;
}
