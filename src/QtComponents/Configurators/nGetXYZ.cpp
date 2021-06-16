#include <qtcomponents.h>
#include "ui_nGetXYZ.h"

N::GetXYZ:: GetXYZ ( QWidget * parent , Plan * p )
          : Dialog (           parent ,        p )
          , ui     ( new Ui::nGetXYZ             )
{
  WidgetClass            ;
  ui -> setupUi ( this ) ;
}

N::GetXYZ::~GetXYZ(void)
{
  delete ui;
}

N::ControlPoint N::GetXYZ::Point(void)
{
  ControlPoint p(ui->X->value(),ui->Y->value(),ui->Z->value()) ;
  return p                                                     ;
}

QVector3D N::GetXYZ::Vector(void)
{
  QVector3D v(ui->X->value(),ui->Y->value(),ui->Z->value()) ;
  return v                                                  ;
}

double N::GetXYZ::X(void)
{
  return ui->X->value() ;
}

double N::GetXYZ::Y(void)
{
  return ui->Y->value() ;
}

double N::GetXYZ::Z(void)
{
  return ui->Z->value() ;
}

void N::GetXYZ::setXYZ(double x,double y,double z)
{
  ui -> X -> setValue ( x ) ;
  ui -> Y -> setValue ( y ) ;
  ui -> Z -> setValue ( z ) ;
}

void N::GetXYZ::setPoint(ControlPoint & point)
{
  setXYZ(point.x,point.y,point.z) ;
}

void N::GetXYZ::setVector(QVector3D & vector)
{
  setXYZ(vector.x(),vector.y(),vector.z()) ;
}
