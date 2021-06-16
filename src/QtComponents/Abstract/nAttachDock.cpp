#include <qtcomponents.h>

#define plan SystemPlan

N::AttachDock:: AttachDock ( Plan * p )
              : SystemPlan (        p )
              , Trigger    ( NULL     )
              , Dock       ( NULL     )
{
}

N::AttachDock::~AttachDock (void)
{
}

bool N::AttachDock::isDocking(void)
{
  nKickOut ( IsNull ( Dock ) , false ) ;
  return Dock -> isVisible ( )         ;
}

void N::AttachDock::Show(bool shown)
{
  nDropOut ( IsNull ( Dock ) )                       ;
  LockDock   ( )                                     ;
  QWidget * w = Dock -> parentWidget ( )             ;
  Dock -> blockSignals ( true  )                     ;
  if ( NotNull ( w ) && ( ! w -> isMinimized ( ) ) ) {
    Dock -> setVisible ( shown )                     ;
  }                                                  ;
  Dock -> blockSignals ( false )                     ;
  UnlockDock           (       )                     ;
}

void N::AttachDock::Visiblity(bool visible)
{
  nDropOut ( IsNull ( Trigger ) )                    ;
  QWidget * w = Dock -> parentWidget ( )             ;
  if ( NotNull ( w ) && ( ! w -> isMinimized ( ) ) ) {
    Trigger -> setChecked ( visible )                ;
  }                                                  ;
}

void N::AttachDock::Store(QMainWindow * Main)
{
  LockDock                                        (            ) ;
  QRect     DR = Dock -> geometry                 (            ) ;
  QWidget * wx = Dock -> widget                   (            ) ;
  DockInformation DI                                             ;
  DI    . geometry = Dock -> saveGeometry         (            ) ;
  DI    . floating = Dock -> isFloating           (            ) ;
  DI    . show     = Dock -> isVisible            (            ) ;
  DI    . area     = (int) Main -> dockWidgetArea ( Dock       ) ;
  DI    . width    = DR    . width                (            ) ;
  DI    . height   = DR    . height               (            ) ;
  plan -> site . SaveDock                         ( Scope , DI ) ;
  if ( NotNull ( wx ) )                                          {
    QSize hs = wx -> size     (                                ) ;
    plan -> site . beginGroup ( Scope                          ) ;
    plan -> site . setValue   ( "HintWidth"  , hs . width  ( ) ) ;
    plan -> site . setValue   ( "HintHeight" , hs . height ( ) ) ;
    plan -> site . endGroup   (                                ) ;
  }                                                              ;
  UnlockDock                                      (            ) ;
}

void N::AttachDock::LockDock   (void)
{
  Mutex . lock ( ) ;
}

void N::AttachDock::UnlockDock (void)
{
  Mutex . unlock ( ) ;
}

void N::AttachDock::Docking       (
       QMainWindow       * Main   ,
       QWidget           * widget ,
       QString             title  ,
       Qt::DockWidgetArea  area   ,
       Qt::DockWidgetAreas areas  )
{
  if ( IsNull ( plan ) ) return                                              ;
  int             w       = plan -> screen . widthPixels ( 40 )              ;
  bool            restore = false                                            ;
  QSize           WS                                                         ;
  DockInformation DI                                                         ;
  ////////////////////////////////////////////////////////////////////////////
  switch ( area )                                                            {
    case Qt::LeftDockWidgetArea                                              :
    case Qt::RightDockWidgetArea                                             :
      DI . width    = w                                                      ;
      DI . height   = Main -> height ( )                                     ;
    break                                                                    ;
    case Qt::TopDockWidgetArea                                               :
    case Qt::BottomDockWidgetArea                                            :
      DI . width    = Main -> width  ( )                                     ;
      DI . height   = w                                                      ;
    break                                                                    ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  DI    . floating = false                                                   ;
  DI    . show     = true                                                    ;
  DI    . area     = area                                                    ;
  plan -> site . LoadDock            ( Scope , DI                          ) ;
  Dock             = new DockWidget  ( Main                                ) ;
  Dock            -> blockSignals    ( true                                ) ;
  Dock            -> setFont         ( plan->fonts[N::Fonts::Default]      ) ;
  Dock            -> setWindowTitle  ( title                               ) ;
  Dock            -> setWidget       ( widget                              ) ;
  Dock            -> setToolTip      ( title                               ) ;
  Main            -> addDockWidget   ( (Qt::DockWidgetArea) DI.area , Dock ) ;
  widget          -> setWindowTitle  ( title                               ) ;
  DockLimits [ 2 ] = widget -> minimumSize (                               ) ;
  DockLimits [ 3 ] = widget -> maximumSize (                               ) ;
  ////////////////////////////////////////////////////////////////////////////
  Dock            -> setAllowedAreas ( areas                               ) ;
  if ( DI . geometry . size ( ) > 0 )                                        {
    Dock -> restoreGeometry          ( DI . geometry                       ) ;
  }                                                                          ;
  Dock            -> setFloating     ( DI . floating                       ) ;
  WS               . setWidth        ( DI . width                          ) ;
  WS               . setHeight       ( DI . height                         ) ;
  if ( ( WS . width ( ) > 0 ) && ( WS . height ( ) > 0 ) ) restore = true    ;
  if ( restore )                                                             {
    QSize DS = Dock -> maximumSize   (       )                               ;
    widget          -> resize        ( WS    )                               ;
    plan      -> site . beginGroup   ( Scope )                               ;
    if ( plan -> site . contains ( "HintWidth" ) )                           {
      if ( plan -> site . contains ( "HintHeight" ) )                        {
        QSize         hs                                                     ;
        AbstractGui * ag = dynamic_cast<AbstractGui *>(widget)               ;
        hs . setWidth  ( plan -> site . value ( "HintWidth"  ) . toInt() )   ;
        hs . setHeight ( plan -> site . value ( "HintHeight" ) . toInt() )   ;
        if ( NotNull ( ag ) ) ag -> setSuggestion ( hs )                     ;
      }                                                                      ;
    }                                                                        ;
    plan            -> site . endGroup                 (    )                ;
    Dock            -> DockGeometry = Dock -> geometry (    )                ;
    Dock            -> DockGeometry . setSize          ( WS )                ;
    DockLimits [ 0 ] = WS                                                    ;
    DockLimits [ 1 ] = DS                                                    ;
  }                                                                          ;
  Dock -> setVisible     ( DI . show )                                       ;
  Dock -> blockSignals   ( false     )                                       ;
  plan -> setFont        ( Dock      )                                       ;
  plan -> processEvents  (           )                                       ;
}

void N::AttachDock::Detach(QMainWindow * Main)
{
  nDropOut ( IsNull ( Dock ) )      ;
  Main -> removeDockWidget ( Dock ) ;
  Dock -> deleteLater      (      ) ;
  Dock  = NULL                      ;
  plan -> processEvents    (      ) ;
}

void N::AttachDock::Restrict(bool strict,QWidget * widget)
{
}
