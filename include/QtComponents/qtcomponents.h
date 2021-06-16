/****************************************************************************
 *                                                                          *
 * Copyright (C) 2001 ~ 2016 Neutrino International Inc.                    *
 *                                                                          *
 * Author : Brian Lin <lin.foxman@gmail.com>, Skype: wolfram_lin            *
 *                                                                          *
 ****************************************************************************/

#ifndef QT_COMPONENTS_H
#define QT_COMPONENTS_H

#include <QtCore>
#include <QtGui>
#include <QtNetwork>
#include <QtSql>
#ifdef QT_SCRIPT_LIB
#include <QtScript>
#endif
#include <QtPositioning>
#include <QtWidgets>
#include <QtOpenGL>
#include <QtPrintSupport>
#include <QtMultimedia>
#include <QtMultimediaWidgets>
#include <QtCUDA>
#include <QtOpenCV>
#include <Essentials>
#include <QtCalendar>
#include <QtGMP>
#include <QtGSL>
#include <QtAlgebra>
#include <QtDiscrete>
#include <QtFFT>
#include <Mathematics>
#include <QtFuzzy>
#include <QtFLP>
#include <QtFoundation>
#include <QtGeometry>
#include <QtGadgets>
#include <QtWorld>
#include <QScintilla2>

QT_BEGIN_NAMESPACE

#ifndef QT_STATIC
#  if defined(QT_BUILD_QTCOMPONENTS_LIB)
#    define Q_COMPONENTS_EXPORT Q_DECL_EXPORT
#  else
#    define Q_COMPONENTS_EXPORT Q_DECL_IMPORT
#  endif
#else
#    define Q_COMPONENTS_EXPORT
#endif

namespace Ui                                     {
class Q_COMPONENTS_EXPORT nTextAlignEditor       ;
class Q_COMPONENTS_EXPORT nFontSelector          ;
class Q_COMPONENTS_EXPORT nGetSize               ;
class Q_COMPONENTS_EXPORT nGetXYZ                ;
class Q_COMPONENTS_EXPORT nLanguageSelections    ;
class Q_COMPONENTS_EXPORT nUuidSelection         ;
class Q_COMPONENTS_EXPORT DesktopSqlConfigurator ;
class Q_COMPONENTS_EXPORT PhoneSqlConfigurator   ;
class Q_COMPONENTS_EXPORT nScreenConfigurator    ;
class Q_COMPONENTS_EXPORT nFontConfigurator      ;
class Q_COMPONENTS_EXPORT ContainerDialog        ;
class Q_COMPONENTS_EXPORT CtrlPadPoint           ;
class Q_COMPONENTS_EXPORT CtrlPadSize            ;
class Q_COMPONENTS_EXPORT CtrlPadRect            ;
class Q_COMPONENTS_EXPORT CtrlPadPointF          ;
class Q_COMPONENTS_EXPORT CtrlPadSizeF           ;
class Q_COMPONENTS_EXPORT CtrlPadRectF           ;
}

typedef QList<QShortcut *> QShortcuts ;

Q_COMPONENTS_EXPORT extern unsigned char TraditionalSource [ ] ;
Q_COMPONENTS_EXPORT extern unsigned char SimplifiedSource  [ ] ;

namespace N
{

class Q_COMPONENTS_EXPORT FullSettings       ;
class Q_COMPONENTS_EXPORT Plan               ;
class Q_COMPONENTS_EXPORT ScriptPlan         ;
class Q_COMPONENTS_EXPORT SqlPlugin          ;
class Q_COMPONENTS_EXPORT HunterPlugin       ;
class Q_COMPONENTS_EXPORT DocumentPlugin     ;
class Q_COMPONENTS_EXPORT MonitorPlugin      ;
class Q_COMPONENTS_EXPORT DataRetriever      ;
class Q_COMPONENTS_EXPORT AbstractGui        ;
class Q_COMPONENTS_EXPORT VirtualGui         ;
class Q_COMPONENTS_EXPORT DockWidget         ;
class Q_COMPONENTS_EXPORT AttachDock         ;
class Q_COMPONENTS_EXPORT MenuManager        ;
class Q_COMPONENTS_EXPORT ScopedProgress     ;
class Q_COMPONENTS_EXPORT GraphicsManager    ;
class Q_COMPONENTS_EXPORT GroupItems         ;
class Q_COMPONENTS_EXPORT FileDeputy         ;
class Q_COMPONENTS_EXPORT VcfFont            ;
class Q_COMPONENTS_EXPORT VcfOptions         ;
class Q_COMPONENTS_EXPORT VcfShape           ;
class Q_COMPONENTS_EXPORT VcfPainter         ;
class Q_COMPONENTS_EXPORT VcfDisplay         ;
class Q_COMPONENTS_EXPORT VcfItem            ;
class Q_COMPONENTS_EXPORT VcfManager         ;
class Q_COMPONENTS_EXPORT VcfPaperConf       ;
class Q_COMPONENTS_EXPORT VcfRectangle       ;
class Q_COMPONENTS_EXPORT VcfCursor          ;
class Q_COMPONENTS_EXPORT VcfCanvas          ;
class Q_COMPONENTS_EXPORT VcfLabel           ;
class Q_COMPONENTS_EXPORT VcfPaper           ;
class Q_COMPONENTS_EXPORT VcfRuler           ;
class Q_COMPONENTS_EXPORT VcfGrid            ;
class Q_COMPONENTS_EXPORT VcfPath            ;
class Q_COMPONENTS_EXPORT VcfLines           ;
class Q_COMPONENTS_EXPORT VcfContours        ;
class Q_COMPONENTS_EXPORT VcfLinker          ;
class Q_COMPONENTS_EXPORT VcfNode            ;
class Q_COMPONENTS_EXPORT VcfBlock           ;
class Q_COMPONENTS_EXPORT VcfInterface       ;
class Q_COMPONENTS_EXPORT VcfSlider          ;
class Q_COMPONENTS_EXPORT VcfPaperManager    ;
class Q_COMPONENTS_EXPORT BalloonTip         ;
class Q_COMPONENTS_EXPORT DragDropStatusBar  ;
class Q_COMPONENTS_EXPORT Widget             ;
class Q_COMPONENTS_EXPORT ToolWrapper        ;
class Q_COMPONENTS_EXPORT ProgressIndicator  ;
class Q_COMPONENTS_EXPORT ReflexWidget       ;
class Q_COMPONENTS_EXPORT Dialog             ;
class Q_COMPONENTS_EXPORT StackedWidget      ;
class Q_COMPONENTS_EXPORT ScrollArea         ;
class Q_COMPONENTS_EXPORT MdiArea            ;
class Q_COMPONENTS_EXPORT MdiSubWindow       ;
class Q_COMPONENTS_EXPORT HeaderView         ;
class Q_COMPONENTS_EXPORT SplitterHandle     ;
class Q_COMPONENTS_EXPORT Splitter           ;
class Q_COMPONENTS_EXPORT SpinBox            ;
class Q_COMPONENTS_EXPORT DoubleSpinBox      ;
class Q_COMPONENTS_EXPORT ToolBar            ;
class Q_COMPONENTS_EXPORT TabBar             ;
class Q_COMPONENTS_EXPORT LineEdit           ;
class Q_COMPONENTS_EXPORT ComboBox           ;
class Q_COMPONENTS_EXPORT ColumnView         ;
class Q_COMPONENTS_EXPORT TabWidget          ;
class Q_COMPONENTS_EXPORT TextBrowser        ;
class Q_COMPONENTS_EXPORT TextEdit           ;
class Q_COMPONENTS_EXPORT TableView          ;
class Q_COMPONENTS_EXPORT TableWidget        ;
class Q_COMPONENTS_EXPORT TreeView           ;
class Q_COMPONENTS_EXPORT TreeWidget         ;
class Q_COMPONENTS_EXPORT ListView           ;
class Q_COMPONENTS_EXPORT ListWidget         ;
class Q_COMPONENTS_EXPORT PaintWidget        ;
class Q_COMPONENTS_EXPORT PaperArrangement   ;
class Q_COMPONENTS_EXPORT GraphicsView       ;
class Q_COMPONENTS_EXPORT FlipRoundRect      ;
class Q_COMPONENTS_EXPORT FlipWidget         ;
class Q_COMPONENTS_EXPORT PictureFlow        ;
class Q_COMPONENTS_EXPORT GLWidget           ;
class Q_COMPONENTS_EXPORT TreeDock           ;
class Q_COMPONENTS_EXPORT ListDock           ;
class Q_COMPONENTS_EXPORT IconDock           ;
class Q_COMPONENTS_EXPORT ScrollDock         ;
class Q_COMPONENTS_EXPORT PanWidget          ;
class Q_COMPONENTS_EXPORT ControlPad         ;
class Q_COMPONENTS_EXPORT RowTable           ;
class Q_COMPONENTS_EXPORT ProgressManager    ;
class Q_COMPONENTS_EXPORT DebugView          ;
class Q_COMPONENTS_EXPORT ClipboardView      ;
class Q_COMPONENTS_EXPORT ClickableLabel     ;
class Q_COMPONENTS_EXPORT CpuLabel           ;
class Q_COMPONENTS_EXPORT TextAlignEditor    ;
class Q_COMPONENTS_EXPORT GetSize            ;
class Q_COMPONENTS_EXPORT GetXYZ             ;
class Q_COMPONENTS_EXPORT LanguageSelections ;
class Q_COMPONENTS_EXPORT UuidSelection      ;
class Q_COMPONENTS_EXPORT FontSelector       ;
class Q_COMPONENTS_EXPORT SqlConfigurator    ;
class Q_COMPONENTS_EXPORT ScreenConfigurator ;
class Q_COMPONENTS_EXPORT FontConfigurator   ;
class Q_COMPONENTS_EXPORT ContainerDialog    ;
class Q_COMPONENTS_EXPORT CtrlPadPoint       ;
class Q_COMPONENTS_EXPORT CtrlPadSize        ;
class Q_COMPONENTS_EXPORT CtrlPadRect        ;
class Q_COMPONENTS_EXPORT CtrlPadPointF      ;
class Q_COMPONENTS_EXPORT CtrlPadSizeF       ;
class Q_COMPONENTS_EXPORT CtrlPadRectF       ;
class Q_COMPONENTS_EXPORT CtrlPadPointsIndex ;
class Q_COMPONENTS_EXPORT ControlPointEditor ;
class Q_COMPONENTS_EXPORT ContainEditor      ;
class Q_COMPONENTS_EXPORT CompanionWidget    ;
class Q_COMPONENTS_EXPORT EditToolBar        ;
class Q_COMPONENTS_EXPORT GeneralDispatcher  ;
class Q_COMPONENTS_EXPORT Scintilla          ;
class Q_COMPONENTS_EXPORT SceneWidget        ;
class Q_COMPONENTS_EXPORT UniverseWidget     ;
class Q_COMPONENTS_EXPORT ScriptableRunner   ;
class Q_COMPONENTS_EXPORT ProgressObject     ;
class Q_COMPONENTS_EXPORT RangeBar           ;
class Q_COMPONENTS_EXPORT ValueObject        ;
class Q_COMPONENTS_EXPORT PictureObject      ;
class Q_COMPONENTS_EXPORT IconObject         ;
class Q_COMPONENTS_EXPORT TextObject         ;
class Q_COMPONENTS_EXPORT SelectItem         ;
class Q_COMPONENTS_EXPORT ProgressButton     ;
class Q_COMPONENTS_EXPORT PickItem           ;
class Q_COMPONENTS_EXPORT PickBox            ;
class Q_COMPONENTS_EXPORT ListBox            ;
class Q_COMPONENTS_EXPORT ListShelf          ;
class Q_COMPONENTS_EXPORT NamesShelf         ;
class Q_COMPONENTS_EXPORT CameraShelf        ;
class Q_COMPONENTS_EXPORT Trademark          ;

typedef QList < QTreeWidgetItem                * > TreeWidgetItems  ;
typedef QMap  < SUID    , QTreeWidgetItem      * > TreeWidgetMaps   ;
typedef QList < QListWidgetItem                * > ListWidgetItems  ;
typedef QMap  < SUID    , QListWidgetItem      * > ListWidgetMaps   ;
typedef QList < QTableWidgetItem               * > TableWidgetItems ;
typedef QMap  < SUID    , QTableWidgetItem     * > TableWidgetMaps  ;
typedef QMap  < SUID    , QWidget              * > Widgets          ;
typedef QMap  < SUID    , QAction              * > Actions          ;
typedef QMap  < QString , QAction              * > NamedActions     ;
typedef QMap  < int     , QMenu                * > MENUs            ;
typedef QMap  < int     , QPainterPath           > Pathes           ;
typedef QMap  < int     , QGraphicsProxyWidget * > VcfProxys        ;
typedef QMap  < int     , QWidget              * > VcfWidgets       ;
typedef QMap  < int     , QPointF                > VcfPoints        ;
typedef QMap  < int     , QRectF                 > VcfRectangles    ;
typedef QList < VcfItem *                        > VcfItems         ;
typedef QMap  < VcfItem * , VcfItem            * > VcfMaps          ;
typedef QList < VcfLinker                      * > VcfLinkers       ;
typedef QList < VcfNode                        * > VcfNodes         ;
typedef QMap  < int , DataRetriever            * > DataRetrievers   ;
typedef QMap  < int , CvHaarClassifierCascade  * > CvClassifiers    ;

namespace Scripts
{

Q_COMPONENTS_EXPORT QString StringMapper   (QString script,QString source) ;
Q_COMPONENTS_EXPORT bool    StringMatching (QString script,QString source) ;
Q_COMPONENTS_EXPORT QString DocumentMapper (QString script,QString source) ;

}

/*****************************************************************************
 *                                                                           *
 *                              GUI Accessors                                *
 *                                                                           *
 *****************************************************************************/

Q_COMPONENTS_EXPORT SUID  GetUuid      (QComboBox       * combo ) ;
Q_COMPONENTS_EXPORT SUID  RetrieveUuid (QTreeWidgetItem * item  , int column ) ;
Q_COMPONENTS_EXPORT int   AddItems     (QComboBox       & Combo , NAMEs & Names ) ;
Q_COMPONENTS_EXPORT int   AddItems     (QComboBox       & Combo , UUIDs & Uuids , NAMEs & Names ) ;

/*****************************************************************************
 *                                                                           *
 *                                System Plans                               *
 *                                                                           *
 *****************************************************************************/

class Q_COMPONENTS_EXPORT FullSettings : public Settings
{
  Q_OBJECT
  public:

    explicit FullSettings (const QString & organization, const QString & application = QString(), QObject * parent = 0);
    explicit FullSettings (QSettings::Scope scope, const QString & organization, const QString & application = QString(), QObject * parent = 0);
    explicit FullSettings (QSettings::Format format,QSettings::Scope scope, const QString & organization, const QString & application = QString(), QObject * parent = 0);
    explicit FullSettings (const QString & fileName,QSettings::Format format, QObject * parent = 0);
    explicit FullSettings (Sql & SQL,QObject * parent = 0);
    explicit FullSettings (QObject * parent = 0);
    explicit FullSettings (const Settings & settings) ;
    virtual ~FullSettings (void);

    QAuthenticator getUser (QString Scope);

  protected:

  private:

  public slots:

    void SaveUserRecord    (QString Scope,QAuthenticator  & user);
    void SaveFont          (QString scope,QFont           & font);
    void LoadFont          (QString scope,QFont           & font);
    void SaveFont          (QString scope,Font            & font);
    void LoadFont          (QString scope,Font            & font);
    void LoadDock          (QString scope,DockInformation & dock);
    void SaveDock          (QString scope,DockInformation & dock);

  protected slots:

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT Plan : public PurePlan
{
  public:

    FullSettings             settings        ;
    FullSettings             site            ;
    int                      dpi             ;
    Screen                   screen          ;
    QMap<int,Screen       *> Screens         ;
    Paper                    paper           ;
    ICONs                    icons           ;
    Font                     font            ;
    FONTs                    fonts           ;
    QColors                  colors          ;
    Actions                  actions         ;
    QMap<int,QActionGroup *> actiongroups    ;
    NamedActions             menuitems       ;
    Widgets                  widgets         ;
    MENUs                    menus           ;
    QStatusBar             * status          ;
    DebugView              * debugWidget     ;
    ProgressManager        * progressManager ;
    ProgressIndicator      * indicator       ;
    ControlPad             * pad             ;
    XmlRpcLogHandler       * xmllog          ;
    XmlRpcErrorHandler     * xmlerr          ;
    RpcLogHandler          * rpclog          ;
    RpcErrorHandler        * rpcerr          ;
    MachineProfiler        * profiler        ;
    CvClassifiers            classifiers     ;
    bool                     Expiration      ;
    QDateTime                Trial           ;

    explicit Plan             (void) ;
    virtual ~Plan             (void) ;

    virtual int type (void) const { return GUI ; }

    virtual bool Initialize    (void) ;
    void      shutdown         (void) ;

    int       Port             (QString setting,QString username,QString application,int DefaultPort) ;

    // Network service
    bool      bindService      (QString hostname,int port) ;

    void      setWidget        (QWidget     * parent) ;
    void      setMain          (QMainWindow * window) ;

    // Fonts
    Font &    selectFont       (int FontId                 ) ;
    bool      setFont          (QFont   & font             ) ;
    void      setFont          (QWidget * widget,int FontId) ;
    void      setFont          (QObject * widget           ) ;

    // Actions
    int       addAction        (int Id,QAction * act ) ;
    QAction * Action           (int Id               ) ;
    QAction * connectAction    (int Id,QObject * parent,const char * method,bool enable = true) ;
    void      disableAction    (int Id               ) ;
    void      actionVisible    (int Id,bool visible  ) ;
    void      nameAction       (int Id,QString name  ) ;
    void      disableAllAction (void                 ) ;

    // Menus
    int       addMenu          (int Id,QMenu * menu  ) ;
    QMenu   * Menu             (int Id) ;

    int       addWidget        (int Id,QWidget * widget) ;
    QWidget * Widget           (int Id) ;

    // Screen settings
    bool    loadScreen         (QString scope        ) ;
    bool    saveScreen         (QString scope        ) ;

    QPointF toCentimeter       (QPoint  point        ) ;
    QPoint  toScreen           (QPointF cmPoint      ) ;
    QRectF  toCentimeter       (QRect   rect         ) ;
    QRect   toScreen           (QRectF  cmRect       ) ;

    // Paper settings
    bool       loadPaper       (QString table        ) ;
    QTransform toPaper         (int DPI = 0          ) ;

    QSizeF  PaperPixels        (QString name   ,int DPI,int Direction);
    QPointF toCentimeter       (QPointF point  ,int DPI) ;
    QRectF  toCentimeter       (QRectF  rect   ,int DPI) ;
    QPointF toPaper            (QPointF cmPoint,int DPI) ;
    QPointF ScreenToPaper      (QPoint  point  ,int DPI) ;
    QPoint  PaperToScreen      (QPointF point  ,int DPI) ;

    // Events
    void    setExpiration      (QString timestring   ) ;
    virtual void processEvents (void                 ) ;
    virtual void showMessage   (QString message      ) ;

    // Debug
    virtual void Debug         (QString message);
    virtual void Debug         (int verbose,QString message);

    virtual void Notify        (QString sound,QString message) ;

    // GUI
    QComboBox    * ComboBox    (QWidget * parent = NULL);
    QTreeWidget  * TreeWidget  (QWidget * parent = NULL);
    QProgressBar * Progress    (QString format = "");

    virtual void * Percentage  (QString format = "") ;
    virtual void   setRange    (void * bar,int Min,int Max) ;
    virtual void   setValue    (void * bar,int value) ;
    virtual void   Finish      (void * bar) ;

    // Progress Manager
    virtual int  Progress      (QString name,QString format) ;
    virtual void ProgressName  (int Id,QString name) ;
    virtual void ProgressText  (int Id,QString message) ;
    virtual void setProgress   (int Id,QString format) ;
    virtual void setRange      (int Id,qint64 Min,qint64 Max) ;
    virtual void setFrequency  (int Id,QString cFmt,QString rFmt) ;
    virtual void Start         (int Id,qint64 * Value,bool * Running) ;
    virtual void Finish        (int Id) ;
    virtual bool ProgressReady (int Id,int msecs = 1000) ;

    // Progress indicator
    virtual void StartBusy     (void) ;
    virtual void StopBusy      (void) ;
    virtual void RealStart     (void) ;
    virtual void RealStop      (void) ;

    // Icon Manager
    void  addIcon              (int ObjectType,int ObjectId,int State,QIcon icon) ;
    QIcon Icon                 (int ObjectType,int ObjectId,int State,QIcon defaultIcon = QIcon()) ;

    void DetachControl         (QWidget * widget) ;
    void addControl            (QString name,QWidget * widget,QWidget * parent) ;
    void addControl            (QString name,QWidget * widget,QObject * parent) ;

    bool setManipulator        (QString key,int size) ;
    bool setProfiler           (QString key) ;
    bool Profiling             (void) ;

} ;

class Q_COMPONENTS_EXPORT ScriptPlan : public QObject
                 , public QScriptable
                 , public Plan
{
  Q_OBJECT
  public:

    explicit     ScriptPlan  (QObject * parent = NULL) ;
    virtual     ~ScriptPlan  (void                   ) ;

    virtual int  type        (void) const { return Script ; }

    // Progress indicator
    virtual void StartBusy   (void) ;
    virtual void StopBusy    (void) ;

    virtual void showMessage (QString message) ;

  protected:

    QString statusMessage ;

  private:

  public slots:

    virtual void setObject   (QObject * parent) ;

  protected slots:

  private slots:

    void         AlertStart (void) ;
    void         AlertStop  (void) ;
    void         SendStatus (void) ;

  signals:

    void         EmitStart  (void) ;
    void         EmitStop   (void) ;
    void         EmitStatus (void) ;

} ;

/*****************************************************************************
 *                                                                           *
 *                                   Plugins                                 *
 *                                                                           *
 *****************************************************************************/

class Q_COMPONENTS_EXPORT SqlPlugin
{
  public:

    explicit  SqlPlugin           (void) { ; }
    virtual ~ SqlPlugin           (void) { ; }

    virtual QString   name        ( void                    ) const = 0 ;
    virtual bool      initialize  ( Plan * plan             )       = 0 ;
    virtual bool      exists      ( void                    )       = 0 ;
    virtual bool      create      ( void                    )       = 0 ;
    virtual bool      startup     ( QObject * parent = NULL )       = 0 ;

} ;

class Q_COMPONENTS_EXPORT HunterPlugin
{
  public:

    explicit  HunterPlugin        (void) { ; }
    virtual ~ HunterPlugin        (void) { ; }

    virtual QString     name        (void                        ) const = 0 ;
    virtual QString     identifier  (void                        ) const = 0 ;
    virtual QString     catalog     (void                        ) const = 0 ;
    virtual QStringList listings    (void                        ) const = 0 ;
    virtual bool        initialize  (Sql     & sql               )       = 0 ;
    virtual QWidget   * create      (QWidget * parent,Plan * plan)       = 0 ;
    virtual bool        startup     (QWidget * widget            )       = 0 ;

} ;

class Q_COMPONENTS_EXPORT DocumentPlugin
{
  public:

    explicit  DocumentPlugin          (void) { ; }
    virtual ~ DocumentPlugin          (void) { ; }

    virtual QString     name          (void                          ) const = 0 ;
    virtual QString     identifier    (void                          ) const = 0 ;
    virtual QString     catalog       (void                          ) const = 0 ;
    virtual QStringList listings      (void                          ) const = 0 ;
    virtual int         type          (void                          ) const = 0 ;
    virtual bool        hasGui        (void                          ) const = 0 ;
    virtual bool        canDock       (void                          ) const = 0 ;
    virtual bool        available     (void                          )       = 0 ;
    virtual int         instances     (void                          )       = 0 ;
    virtual bool        initialize    (Plan * plan                   )       = 0 ;
    virtual QObject *   create        (QWidget * parent,Plan * plan  )       = 0 ;
    virtual bool        docking       (QMainWindow * M,QObject * O   )       = 0 ;
    virtual bool        startup       (QObject     * object          )       = 0 ;
    virtual bool        startup       (QObject * object,UUIDs & Uuids)       = 0 ;

} ;

class Q_COMPONENTS_EXPORT MonitorPlugin
{
  public:

    explicit  MonitorPlugin    (void) { ; }
    virtual ~ MonitorPlugin    (void) { ; }

    virtual QString name       ( void                                 ) const = 0 ;
    virtual bool    initialize ( Plan * plan                          )       = 0 ;
    virtual bool    prepare    ( QObject * parent = NULL              )       = 0 ;
    virtual bool    startup    ( QObject * parent , QByteArray & conf )       = 0 ;

} ;

class Q_COMPONENTS_EXPORT DataRetriever
{
  public:

    int        row      ;
    int        column   ;
    int        language ;
    Plan     * plan     ;
    QWidget  * widget   ;
    QObject  * parent   ;
    NAMEs      Keywords ;
    QByteArray conf     ;

    explicit  DataRetriever (void) ;
    explicit  DataRetriever (QObject * owner,Plan * p) ;
    virtual ~ DataRetriever (void) ;

    virtual int          Type      (void) const = 0 ;

    virtual QValidator * Validator (void) = 0 ;

    virtual bool         Obtain    (SqlConnection    & Connection  ,
                                    SUID               uuid        ,
                                    QString          & string) = 0 ;
    virtual bool         Obtain    (SqlConnection    & Connection  ,
                                    SUID               uuid        ,
                                    QTreeWidgetItem  * item  ) = 0 ;
    virtual bool         Obtain    (SqlConnection    & Connection  ,
                                    SUID               uuid        ,
                                    QTableWidgetItem * item  ) = 0 ;
    virtual bool         Obtain    (SqlConnection    & Connection  ,
                                    SUID               uuid        ,
                                    QListWidgetItem  * item  ) = 0 ;

    virtual QWidget    * Editor    (SqlConnection    & Connection  ,
                                    SUID               uuid        ,
                                    QString          & string) = 0 ;
    virtual QWidget    * Editor    (SqlConnection    & Connection  ,
                                    SUID               uuid        ,
                                    QTreeWidgetItem  * item  ) = 0 ;
    virtual QWidget    * Editor    (SqlConnection    & Connection  ,
                                    SUID               uuid        ,
                                    QTableWidgetItem * item  ) = 0 ;
    virtual QWidget    * Editor    (SqlConnection    & Connection  ,
                                    SUID               uuid        ,
                                    QListWidgetItem  * item  ) = 0 ;

} ;

/*****************************************************************************
 *                                                                           *
 *                             Essential Widgets                             *
 *                                                                           *
 *****************************************************************************/

Q_COMPONENTS_EXPORT bool getAbstractStopable(QVariant pointer) ;
Q_COMPONENTS_EXPORT bool setAbstractStopable(QVariant pointer,bool stopable) ;

class Q_COMPONENTS_EXPORT AbstractGui
{
  public:

    typedef enum          {
      DesktopGui = 300001 ,
      PadGui     = 300002 ,
      PhoneGui   = 300003 }
      GuiOperateMethod    ;

    typedef enum                 {
      GuiLeftButton   =   100001 ,
      GuiRightButton  =   100002 ,
      GuiMiddleButton =   100003 ,
      GuiShift        =   100004 ,
      GuiControl      =   100005 ,
      GuiAlt          =   100006 ,
      GuiMeta         =   100007 ,
      GuiResize       =   100101 ,
      GuiPainted      =   100102 ,
      GuiTap          =   100201 ,
      GuiTapHold      =   100202 ,
      GuiPan          =   100203 ,
      GuiPinch        =   100204 ,
      GuiSwipe        =   100205 ,
      GuiNotEvent     =   199999 }
      InputStatus                ; // For decision actions

    typedef enum                 {
      DropText          = 1001   ,
      DropUrls          = 1002   ,
      DropImage         = 1003   ,
      DropHtml          = 1004   ,
      DropColor         = 1005   ,
      DropTag           = 1006   ,
      DropPicture       = 1007   ,
      DropPeople        = 1008   ,
      DropAudio         = 1009   ,
      DropVideo         = 1010   ,
      DropAlbum         = 1011   ,
      DropGender        = 1012   ,
      DropDivision      = 1013   ,
      DropURIs          = 1014   ,
      DropBookmark      = 1015   ,
      DropFont          = 1016   ,
      DropPen           = 1017   ,
      DropBrush         = 1018   ,
      DropGradient      = 1019   ,
      DropShape         = 1020   ,
      DropMember        = 1021   ,
      DropSet           = 1022   ,
      DropActions       = 1023   ,
      DropDecision      = 1024   ,
      DropCondition     = 1025   ,
      DropExecution     = 1026   ,
      DropSqlTable      = 1027   ,
      DropDatabase      = 1028   ,
      DropTask          = 1029   ,
      DropNation        = 1030   ,
      DropContour       = 1031   ,
      DropManifold      = 1032   ,
      DropSource        = 1033   ,
      DropDocument      = 1034   ,
      DropEyes          = 1035   ,
      DropHairs         = 1036   ,
      DropKeyword       = 1037   ,
      DropTerminology   = 1038   ,
      DropKnowledge     = 1039   ,
      DropField         = 1040   ,
      DropKnowledgeBase = 1041   ,
      DropSqlColumn     = 1042   ,
      DropUuid          = 1043   ,
      DropCommodity     = 1044   ,
      DropOrganization  = 1045   ,
      DropBlob          = 1046   ,
      DropVariable      = 1047   ,
      DropTorrent       = 1048   ,
      DropCamera        = 1049   ,
      DropFace          = 1050   ,
      DropColorGroup    = 1051   ,
      DropSetsAlgebra   = 1052   ,
      DropName          = 1053   ,
      DropStar          = 1054   ,
      DropPhoneme       = 1055   ,
      DropModel         = 1056   ,
      DropReality       = 1057   ,
      DropMusic         = 1058   }
      DropTypes                  ;

    typedef enum           {
      GuiNativeId =      0 ,
      GuiMainId   =  10001 ,
      GuiUserId   = 100001 }
      DecisionMapId        ; // Decision table id

    typedef enum               {
      InterfaceHasMenu  = 1001 ,
      CommonFunctionEnd = 1002
    } CommonFunctionIDs        ;

    Plan             *  plan       ;
    double              opacity    ;
    Pens                pens       ;
    Brushes             brushes    ;
    Pathes              pathes     ;
    DecisionTables      decisions  ;
    bool                designable ;
    QMap<QString,QIcon> LocalIcons ;
    NAMEs               LocalMsgs  ;

    explicit        AbstractGui       (QWidget       * widget,Plan * plan = NULL);
    explicit        AbstractGui       (QGraphicsItem * item  ,Plan * plan = NULL);
    virtual        ~AbstractGui       (void);

    virtual bool    canDesign         (void) ;
    virtual void    setDesignable     (bool edit) ;

    void            setDropFlag       (DropTypes dropType,bool enabled);
    virtual bool    setAcceptVocal    (bool enabled) ;
    QIcon           Icon              (SUID ID) ;
    bool            changeFont        (void) ;

    void            acceptMouse       (Qt::MouseButtons      buttons  ) ;
    void            acceptModifiers   (Qt::KeyboardModifiers modifiers) ;

    virtual bool    addSequence       (VarArgs args) ;
    virtual bool    addSequence       (int command) ;
    virtual bool    Apportion         (void) ;

    virtual QString toCpp             (QString functionName) ;

    virtual void    assignTitle       (QString title) ;
    virtual void    assignLanguage    (nDeclWidget = NULL) ;
    virtual void    assignStyleSheet  (QString title,nDeclWidget = NULL) ;
    virtual void    assignMinimumSize (nDeclWidget) ;
    virtual void    assignMaximumSize (nDeclWidget) ;
    virtual bool    getGridSize       (nDeclWidget,QString title,QSize current,QSize & newSize) ;

    virtual QString GetName          (nConnectUuid) ;

    int             LimitValue       (int index) ;
    void            setLimitValue    (int index,int value) ;
    bool            ArgsToGroup      (int start,VarArgs & args,Group & group) ;
    bool            ArgsToUuids      (int start,VarArgs & args,UUIDs & uuids) ;
    bool            FixUuids         (UUIDs & Uuids) ;

    virtual void    setCanStop       (int value) ;
    virtual void    pushCanStop      (void) ;
    virtual void    popCanStop       (void) ;
    virtual bool    canStop          (void) ;
    virtual bool    isLoading        (void) ;
    virtual bool    isStopped        (void) ;
    virtual bool    startLoading     (void) ;
    virtual bool    stopLoading      (void) ;
    virtual void    stopForcely      (void) ;

    virtual bool    setFunction      (int Id,bool enable) ;
    virtual bool    isFunction       (int Id) ;
    virtual void    setGui           (QWidget * widget) ;

    void            setSuggestion    (QSize size) ;
    QSize           SizeSuggestion   (QSize size) const ;
    QSize           SizeSuggestion   (int width,int height) const ;

    virtual bool    RecoverySettings (QString scope) ;
    virtual bool    StoreSettings    (QString scope) ;

    virtual void    alert            (QString sound,QString message) ;

  protected:

    QTimer            * Commando        ;
    QMutex              Mutex           ;
    QMutex              PainterMutex    ;
    QMutex              CommandMutex    ;
    QWidget           * Gui             ;
    QDrag             * Drag            ;
    QString             localTitle      ;
    QShortcuts          Shortcuts       ;
    VcfWidgets          ChildWidgets    ;
    IMAPs               TimerIDs        ;
    bool                PassDragDrop    ;
    bool                Dumping         ;
    BMAPs               AllowDrops      ;
    BMAPs               Functionalities ;
    IMAPs               LimitValues     ;
    VarArgLists         Sequences       ;
    DataRetrievers      Retrievers      ;
    int                 vLanguageId     ;
    bool                allowGesture    ;
    bool                localModified   ;

    bool         EnterPainter        (void) ;
    void         LeavePainter        (void) ;

    void         StartCommando       (void) ;
    bool         EnterCommando       (void) ;
    void         LeaveCommando       (void) ;
    virtual void LaunchCommands      (void) ;
    virtual void DispatchCommands    (void) ;

    void         FadeIn              (nDeclWidget,int steps);
    void         FadeOut             (nDeclWidget,int steps);

    // message posting
    void         Notify              (QString message);
    void         Notify              (QString caption,QString message);

    // focus management
    virtual bool focusIn             (QFocusEvent * event) ;
    virtual bool focusOut            (QFocusEvent * event) ;

    virtual bool FocusIn             (void);
    virtual bool FocusOut            (void);

    // Shortcut management
    int          addShortcut         (const QKeySequence & key                                   ,
                                      QWidget            * parent                                ,
                                      const char         * member          = 0                   ,
                                      const char         * ambiguousMember = 0                   ,
                                      Qt::ShortcutContext  context         = Qt::WindowShortcut) ;

    QAction *    connectAction       (int Id,QObject * parent,const char * method,bool enable = true) ;
    QAction *    actionLabel         (int Id,QString message) ;

    QString      MimeType            (const QMimeData * mime,QString formats);

    // drag management
    bool         dragStart           (QMouseEvent * event);
    bool         dragMoving          (QMouseEvent * event);
    bool         dragEnd             (QMouseEvent * event);

    virtual bool hasItem             (void);
    virtual bool startDrag           (QMouseEvent * event);
    virtual bool fetchDrag           (QMouseEvent * event);
    virtual QMimeData * dragMime     (void);
    virtual void dragDone            (Qt::DropAction dropIt,QMimeData * mime);
    virtual bool finishDrag          (QMouseEvent * event);

    virtual bool acceptDrop          (nDeclWidget,const QMimeData * mime);
    virtual bool dropNew             (nDeclWidget,const QMimeData * mime,QPoint pos);
    virtual bool dropMoving          (nDeclWidget,const QMimeData * mime,QPoint pos);
    virtual bool dropAppend          (nDeclWidget,const QMimeData * mime,QPoint pos);
    virtual bool removeDrop          (void);

    virtual bool dragEnter           (QDragEnterEvent * event) ;
    virtual bool dragMove            (QDragMoveEvent  * event) ;
    virtual bool drop                (QDropEvent      * event) ;

    virtual void imState             (QInputMethodEvent * event) ;
    virtual void keyState            (QKeyEvent         * event) ;
    virtual void mouseState          (QMouseEvent       * event) ;
    virtual void wheelState          (QWheelEvent       * event) ;

    virtual bool permitGesture       (void) ;
    virtual bool gestureEvent        (QEvent             * event  ) ;
    virtual bool acceptTap           (QTapGesture        * gesture) ;
    virtual bool acceptTapHold       (QTapAndHoldGesture * gesture) ;
    virtual bool acceptPan           (QPanGesture        * gesture) ;
    virtual bool acceptPinch         (QPinchGesture      * gesture) ;
    virtual bool acceptSwipe         (QSwipeGesture      * gesture) ;
    virtual bool acceptCustom        (QGesture           * gesture) ;

    virtual void InstallDecisions    (void) ;

    void         Debug               (QEvent * event) ;

    UUIDs        GetUuids            (QByteArray & data) ;
    SUID         GetUuid             (QByteArray & data) ;
    QByteArray   CreateByteArray     (SUID    uuid ) ;
    QByteArray   CreateByteArray     (UUIDs & Uuids) ;
    void         setMime             (QMimeData * mime,QString mtype,SUID    uuid ) ;
    void         setMime             (QMimeData * mime,QString mtype,UUIDs & Uuids) ;

    virtual bool acceptTextDrop      (void) ;
    virtual bool acceptUrlsDrop      (void) ;
    virtual bool acceptImageDrop     (void) ;
    virtual bool acceptHtmlDrop      (void) ;
    virtual bool acceptColorDrop     (void) ;
    virtual bool acceptTagDrop       (void) ;
    virtual bool acceptPictureDrop   (void) ;
    virtual bool acceptPeopleDrop    (void) ;
    virtual bool acceptAudioDrop     (void) ;
    virtual bool acceptVideoDrop     (void) ;
    virtual bool acceptAlbumDrop     (void) ;
    virtual bool acceptGenderDrop    (void) ;
    virtual bool acceptDivisionDrop  (void) ;
    virtual bool acceptUriDrop       (void) ;
    virtual bool acceptBookmarkDrop  (void) ;
    virtual bool acceptFont          (void) ;
    virtual bool acceptPen           (void) ;
    virtual bool acceptBrush         (void) ;
    virtual bool acceptGradient      (void) ;
    virtual bool acceptShapes        (void) ;
    virtual bool acceptMembers       (void) ;
    virtual bool acceptSets          (void) ;
    virtual bool acceptActions       (void) ;
    virtual bool acceptDecision      (void) ;
    virtual bool acceptCondition     (void) ;
    virtual bool acceptExecution     (void) ;
    virtual bool acceptSqlTable      (void) ;
    virtual bool acceptDatabase      (void) ;
    virtual bool acceptTask          (void) ;
    virtual bool acceptNation        (void) ;
    virtual bool acceptContour       (void) ;
    virtual bool acceptManifold      (void) ;
    virtual bool acceptSources       (void) ;
    virtual bool acceptDocuments     (void) ;
    virtual bool acceptEyes          (void) ;
    virtual bool acceptHairs         (void) ;
    virtual bool acceptKeywords      (void) ;
    virtual bool acceptTerminologies (void) ;
    virtual bool acceptKnowledge     (void) ;
    virtual bool acceptFields        (void) ;
    virtual bool acceptKnowledgeBase (void) ;
    virtual bool acceptSqlColumn     (void) ;
    virtual bool acceptUuids         (void) ;
    virtual bool acceptCommodities   (void) ;
    virtual bool acceptOrganizations (void) ;
    virtual bool acceptBlobs         (void) ;
    virtual bool acceptVariables     (void) ;
    virtual bool acceptTorrents      (void) ;
    virtual bool acceptCameras       (void) ;
    virtual bool acceptFaces         (void) ;
    virtual bool acceptColorGroups   (void) ;
    virtual bool acceptSetsAlgebras  (void) ;
    virtual bool acceptNames         (void) ;
    virtual bool acceptStars         (void) ;
    virtual bool acceptPhonemes      (void) ;
    virtual bool acceptModels        (void) ;
    virtual bool acceptReality       (void) ;
    virtual bool acceptMusic         (void) ;

    virtual bool acceptPrivate       (const QMimeData * mime) ;

    virtual bool dropHandler         (const QMimeData * mime) ;

    virtual bool dropItems           (nDeclWidget,const QMimeData * mime,QPoint  pos) ;
    virtual bool dropItems           (nDeclWidget,const QMimeData * mime,QPointF pos) ;
    virtual bool dropPrivate         (nDeclWidget,const QMimeData * mime,QPointF pos) ;

    virtual bool dropText            (nDeclWidget,QPointF pos,const QString & text    ) ;
    virtual bool dropUrls            (nDeclWidget,QPointF pos,const QList<QUrl> & urls) ;
    virtual bool dropImage           (nDeclWidget,QPointF pos,const QImage  & image   ) ;
    virtual bool dropHtml            (nDeclWidget,QPointF pos,const QString & html    ) ;
    virtual bool dropColor           (nDeclWidget,QPointF pos,const QColor  & color   ) ;
    virtual bool dropTags            (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropPictures        (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropPeople          (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropAudios          (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropVideos          (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropAlbums          (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropGender          (nDeclWidget,QPointF pos,const SUID      gender  ) ;
    virtual bool dropDivisions       (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropURIs            (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropBookmarks       (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropFont            (nDeclWidget,QPointF pos,const SUID      font    ) ;
    virtual bool dropPen             (nDeclWidget,QPointF pos,const SUID      pen     ) ;
    virtual bool dropBrush           (nDeclWidget,QPointF pos,const SUID      brush   ) ;
    virtual bool dropGradient        (nDeclWidget,QPointF pos,const SUID      gradient) ;
    virtual bool dropShapes          (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropMembers         (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropSets            (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropActions         (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropDecision        (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropCondition       (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropExecution       (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropSqlTable        (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropDatabase        (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropTask            (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropNation          (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropContour         (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropManifold        (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropSources         (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropDocuments       (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropEyes            (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropHairs           (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropKeywords        (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropTerminologies   (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropKnowledge       (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropFields          (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropKnowledgeBase   (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropSqlColumn       (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropUuids           (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropCommodities     (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropOrganizations   (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropBlobs           (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropVariables       (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropTorrents        (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropCameras         (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropFaces           (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropColorGroups     (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropSetsAlgebras    (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropNames           (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropStars           (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropPhonemes        (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropModels          (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropReality         (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;
    virtual bool dropMusic           (nDeclWidget,QPointF pos,const UUIDs   & Uuids   ) ;

    virtual bool Bustle              (void) ;
    virtual bool Vacancy             (void) ;
    virtual bool isLocked            (int timeout = 100) ;
    virtual void LockGui             (void) ;
    virtual void UnlockGui           (void) ;

    virtual bool ForUuid             (SUID & u,qint64 & i,UUIDs & U) ;

  private:

    void * PrivateStopable ;

    bool         allowDrops          (DropTypes dropType) ;

} ;

class Q_COMPONENTS_EXPORT VirtualGui : public AbstractGui
{
  public:

    explicit VirtualGui          (StandardConstructor) ;
    virtual ~VirtualGui          (void) ;

    Qt::WindowFlags Frameless    (nDeclWidget);

    virtual void addConnector    (QString                 name     ,
                                  const QObject         * sender   ,
                                  const char            * signal   ,
                                  const QObject         * receiver ,
                                  const char            * method   ,
                                  enum Qt::ConnectionType type   ) ;
    virtual void addConnector    (QString                 name     ,
                                  const QObject         * sender   ,
                                  const char            * signal   ,
                                  const QObject         * receiver ,
                                  const char            * method ) ;
    virtual void addConnector    (QString         name             ,
                                  const QObject * receiver         ,
                                  const char    * signal           ,
                                  const char    * method         ) ;
    virtual void addConnector    (QString         name             ,
                                  const char    * signal           ,
                                  const char    * method         ) ;
    virtual void onlyConnector   (QString name) ;
    virtual void doConnector     (QString name) ;
    virtual void undoConnector   (QString name) ;
    virtual void removeConnector (QString name) ;

  protected:

    QMap<QString,void *> SignalConnectors ;

    void addIntoWidget           (QWidget * parent,QWidget * widget) ;
    bool allowDrag               (QAbstractItemView::DragDropMode dragDrop);
    bool allowDrop               (QAbstractItemView::DragDropMode dragDrop);

    virtual bool CopyToFile      (QString filename         ,
                                  QString ToFile           ,
                                  QString progressName     ,
                                  QString progressFormat ) ;

  private:

} ;

class Q_COMPONENTS_EXPORT DockWidget : public QDockWidget
{
  Q_OBJECT
  public:

    bool  Regular      ;
    QRect DockGeometry ;

    explicit      DockWidget (const QString & title, QWidget * parent = 0, Qt::WindowFlags flags = 0) ;
    explicit      DockWidget (QWidget * parent = 0, Qt::WindowFlags flags = 0) ;
    virtual      ~DockWidget (void) ;

    virtual QSize sizeHint   (void) const ;

  protected:

    virtual bool  event      (QEvent * event) ;

  private:

  public slots:

  protected slots:

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT AttachDock
{
  public:

    enum AttachDockMenuId          {
      FunctionDocking = 1271293849 ,
      AttachToMdi     = 1000001    ,
      AttachToDock    = 1000002  } ;

    Plan       * SystemPlan ;
    QAction    * Trigger    ;
    QString      Scope      ;
    DockWidget * Dock       ;

    explicit AttachDock     (Plan * plan = NULL) ;
    virtual ~AttachDock     (void) ;

    virtual bool isDocking  (void) ;
    virtual void Store      (QMainWindow * Main) ;
    virtual void Docking    (QMainWindow       * Main    ,
                             QWidget           * widget  ,
                             QString             title   ,
                             Qt::DockWidgetArea  area    ,
                             Qt::DockWidgetAreas areas ) ;
    virtual void Show       (bool shown) ;
    virtual void Visiblity  (bool visible) ;
    virtual void Detach     (QMainWindow * Main) ;
    virtual void Restrict   (bool strict,QWidget * widget) ;

    virtual void LockDock    (void) ;
    virtual void UnlockDock  (void) ;

  protected:

    QMutex          Mutex      ;
    QMap<int,QSize> DockLimits ;

  private:

} ;

class Q_COMPONENTS_EXPORT MenuManager
{
  public:

    QMenu * menu ;

    explicit MenuManager    (nDeclWidget) ;
    virtual ~MenuManager    (void);

    QAction * exec          (QPoint pos = QCursor::pos()) ;

    void      add           (NAMEs Menu);
    QAction * add           (int Id,QString text);
    QAction * add           (int Id,QIcon icon,QString text);
    QAction * add           (int Id,QString text,bool checkable,bool checked);
    QAction * add           (int Id,QIcon icon,QString text,bool checkable,bool checked);
    QAction * addSeparator  (void) ;

    QMenu   * addMenu       (QString title) ;
    QMenu   * addMenu       (QMenu * m,QString title) ;
    QAction * add           (QMenu * m,int Id,QString text);
    QAction * add           (QMenu * m,int Id,QIcon icon,QString text);
    QAction * add           (QMenu * m,int Id,QString text,bool checkable,bool checked);
    QAction * add           (QMenu * m,int Id,QIcon icon,QString text,bool checkable,bool checked);
    QAction * addSeparator  (QMenu * m) ;

    QAction * add           (int Id,nDeclWidget) ;
    QAction * add           (QMenu * m,int Id,nDeclWidget) ;

    bool      contains      (QAction * action) ;
    int       operator []   (QAction * action) ;

    void      setFont       (QFont  font) ;
    void      setFont       (Font   font) ;
    void      setFont       (Plan * plan) ;

    QActionGroup * group    (int Id) ;
    int            setGroup (int Id,QActionGroup * group) ;

    QWidget      * widget   (int Id) ;

  protected:

    QList<QAction *                > actions      ;
    QList<QMenu   *                > menus        ;
    QMap <QAction *, int           > IDs          ;
    QMap <int      , QWidget      *> Widgets      ;
    QMap <int      , QActionGroup *> actionGroups ;

  private:

} ;

class Q_COMPONENTS_EXPORT ScopedProgress
{
  public:

    explicit ScopedProgress  (Plan * plan,QString format,int gap) ;
    virtual ~ScopedProgress  (void);

    void show                (void) ;
    void setRange            (int minimum,int maximum) ;
    void setValue            (int value) ;
    void Final               (int value) ;

    void Start               (int index = 0) ;
    void Finish              (void) ;
    int  operator ++         (void) ;

    int  Value               (void) const ;

    QDateTime Estimated      (void) ;
    QString   ETA            (void) ;

  protected:

    Plan         * plan     ;
    QProgressBar * Progress ;
    int            Gap      ;
    QDateTime      Lastest  ;
    QDateTime      Launch   ;

  private:

    int            Index    ;

} ;

class Q_COMPONENTS_EXPORT GraphicsManager
{
  public:

    Plan * GraphicPlan ;

    explicit   GraphicsManager  (Plan * plan = NULL);
    virtual   ~GraphicsManager  (void);

    QByteArray CompressPNG      (QImage & image) ;

    bool       assureName       (nConnectUuid,int language,QString name) ;
    QString    Name             (nConnectUuid,int language) ;

    bool       DeletePainter    (nConnectUuid) ;
    QByteArray PainterParaments (nConnectUuid) ;
    bool       PainterEditable  (nConnectUuid) ;
    bool       SaveParaments    (nConnectUuid,int Type,QByteArray & Data) ;

    Font       GetFont          (nConnectUuid) ;
    Pen        GetPen           (nConnectUuid) ;
    Brush      GetBrush         (nConnectUuid) ;
    Gradient   GetGradient      (nConnectUuid) ;

    Font       GetFont          (nConnectName) ;
    Pen        GetPen           (nConnectName) ;
    Brush      GetBrush         (nConnectName) ;
    Gradient   GetGradient      (nConnectName) ;

    bool       SaveFont         (SqlConnection & Connection,Font     & gont    ) ;
    bool       SavePen          (SqlConnection & Connection,Pen      & pen     ) ;
    bool       SaveBrush        (SqlConnection & Connection,Brush    & brush   ) ;
    bool       SaveGradient     (SqlConnection & Connection,Gradient & gradient) ;

    SUID       NewShape         (nConnectName,int language) ;

    Contour    GetContour       (SqlConnection & connection,SUID uuid) ;
    QImage     ContourSnap      (QSize size,QPointF center ,Contour & contour) ;
    bool       SaveContour      (SqlConnection & connection,Contour & contour,QImage & Snap) ;

    bool       LoadColors       (SqlConnection & connection,SUID   colorgroup,Colors & colors) ;
    bool       SaveColors       (SqlConnection & connection,SUID & colorgroup,Colors & colors) ;

  protected:

  private:

} ;

class Q_COMPONENTS_EXPORT GroupItems
{
  public:

    Plan *  GroupPlan    ;
    int     HiddenItems  ;
    bool    AutoMap      ;
    QString GroupTable   ;
    NAMEs   GroupMappers ;

    explicit    GroupItems    (Plan * plan = NULL) ;
    virtual    ~GroupItems    (void);

    QString     LookTable     (int t1,int t2,int relation) ;

    UUIDs       Groups        (SqlConnection & connection              ,
                               N::Types::ObjectTypes Type              ,
                               QString options = "order by id asc"   ) ;
    UUIDs       Divisions     (SqlConnection & connection              ,
                               N::Types::ObjectTypes Type              ,
                               QString options = "order by id asc"   ) ;
    int         Count         (SqlConnection & connection              ,
                               SUID            group                   ,
                               int             t1                      ,
                               int             t2                      ,
                               int             relation              ) ;
    int         LastPosition  (SqlConnection & connection              ,
                               SUID            group                   ,
                               int             t1                      ,
                               int             t2                      ,
                               int             relation              ) ;
    void        Join          (SqlConnection & connection              ,
                               SUID            group                   ,
                               int             t1                      ,
                               int             t2                      ,
                               int             relation                ,
                               SUID            before                  ,
                               SUID            uuid                    ,
                               bool            gui = true            ) ;
    void        Join          (SqlConnection & connection              ,
                               SUID            group                   ,
                               int             t1                      ,
                               int             t2                      ,
                               int             relation                ,
                               SUID            before                  ,
                               UUIDs         & Uuids                   ,
                               bool            gui = true            ) ;
    void        JoinOwner     (SqlConnection & connection              ,
                               SUID            objectUuid              ,
                               int             t1                      ,
                               int             t2                      ,
                               int             relation                ,
                               UUIDs         & Uuids                   ,
                               bool            gui = true            ) ;
    // Insert and InsertItem are actually identical
    // However, InsertItem does not use bindValue, which provide a faster SQL operation
    bool        Insert        (SqlConnection & connection              ,
                               SUID            first                   ,
                               SUID            second                  ,
                               int             t1                      ,
                               int             t2                      ,
                               int             relation              ) ;
    bool        InsertItem    (SqlConnection & connection              ,
                               SUID            first                   ,
                               SUID            second                  ,
                               int             t1                      ,
                               int             t2                      ,
                               int             relation              ) ;
    bool        Insert        (SqlConnection & connection              ,
                               SUID            first                   ,
                               SUID            second                  ,
                               int             t1                      ,
                               int             t2                      ,
                               int             relation                ,
                               int             position              ) ;
    bool        InsertItem    (SqlConnection & connection              ,
                               SUID            first                   ,
                               SUID            second                  ,
                               int             t1                      ,
                               int             t2                      ,
                               int             relation                ,
                               int             position              ) ;
    bool        DeleteFrom    (SqlConnection & connection              ,
                               QString         whereOptions          ) ;
    void        Detach        (SqlConnection & connection              ,
                               SUID            group                   ,
                               int             t1                      ,
                               int             t2                      ,
                               int             relation                ,
                               UUIDs         & Uuids                 ) ;
    bool        FullDetach    (SqlConnection & connection              ,
                               SUID            group                   ,
                               int             t1                      ,
                               int             t2                      ,
                               int             relation              ) ;
    bool        ExactDetach   (SqlConnection & connection              ,
                               SUID            first                   ,
                               SUID            second                  ,
                               int             t1                      ,
                               int             t2                      ,
                               int             relation              ) ;
    bool        ExactDetach   (SqlConnection & connection              ,
                               Group         & group                 ) ;
    bool        Delegate      (SqlConnection & connection              ,
                               SUID            first                   ,
                               SUID            second                  ,
                               int             t1                      ,
                               int             t2                      ,
                               int             relation              ) ;
    void        Relocate      (SqlConnection & connection              ,
                               SUID            group                   ,
                               int             t1                      ,
                               int             t2                      ,
                               int             relation              ) ;
    QString     ItemName      (SqlConnection & connection              ,
                               SUID            uuid                  ) ;
    QStringList Names         (SqlConnection & connection              ,
                               SUID            uuid                  ) ;
    SUID        FindFirst     (SqlConnection & connection              ,
                               SUID            Second                  ,
                               int             t1                      ,
                               int             t2                      ,
                               int             relation                ,
                               QString         options     = ""        ,
                               QString         limitString = ""      ) ;
    SUID        FindSecond    (SqlConnection & connection              ,
                               SUID            group                   ,
                               int             t1                      ,
                               int             t2                      ,
                               int             relation                ,
                               QString         options     = ""        ,
                               QString         limitString = ""      ) ;
    UUIDs       Subordination (SqlConnection & connection              ,
                               SUID            group                   ,
                               int             t1                      ,
                               int             t2                      ,
                               int             relation                ,
                               QString         options     = ""        ,
                               QString         limitString = ""      ) ;
    UUIDs       GetOwners     (SqlConnection & connection              ,
                               SUID            Second                  ,
                               int             t1                      ,
                               int             t2                      ,
                               int             relation                ,
                               QString         options     = ""        ,
                               QString         limitString = ""      ) ;
    bool        InsertNameMap (SqlConnection & connection              ,
                               SUID            uuid                    ,
                               SUID            nuid                  ) ;
    SUID        NewDivision   (SqlConnection & connection              ,
                               QString         name                    ,
                               N::Types::ObjectTypes Type            ) ;
    bool        CopyTo        (SqlConnection & connection              ,
                               SUID            Source                  ,
                               SUID            Target                  ,
                               int             t1                      ,
                               int             t2                      ,
                               int             relation                ,
                               bool            gui          = false    ,
                               QString         progressText = "%v/%m") ;
    bool        Substract     (SqlConnection & connection              ,
                               SUID            Source                  ,
                               SUID            Target                  ,
                               int             t1                      ,
                               int             t2                      ,
                               int             relation                ,
                               bool            gui          = false    ,
                               QString         progressText = "%v/%m") ;
    UUIDs       RelateUuids   (SqlConnection & connection              ,
                               UUIDs         & Uuids                   ,
                               int             t1                      ,
                               int             t2                      ,
                               int             relation                ,
                               bool            gui          = false    ,
                               QString         progressText = "%v/%m") ;
    NAMEs       UuidNames     (SqlConnection & connection              ,
                               UUIDs         & Uuids                   ,
                               int             language              ) ;

    static QString ExactItem  (SUID    first                           ,
                               SUID    second                          ,
                               int     t1                              ,
                               int     t2                              ,
                               int     relation                        ,
                               QString options     = ""                ,
                               QString limitString = ""              ) ;
    static QString FirstItem  (SUID    group                           ,
                               int     t1                              ,
                               int     t2                              ,
                               int     relation                        ,
                               QString options     = ""                ,
                               QString limitString = ""              ) ;
    static QString SecondItem (SUID    Second                          ,
                               int     t1                              ,
                               int     t2                              ,
                               int     relation                        ,
                               QString options     = ""                ,
                               QString limitString = ""              ) ;

    bool AllowType            (SqlConnection & connection ,
                               int             Type       ,
                               UUIDs         & Source     ,
                               UUIDs         & Target   ) ;
    bool AllowObjectsTypes    (SqlConnection & Connection ,
                               UUIDs         & Source     ,
                               CUIDs         & Types      ,
                               UUIDs         & Target   ) ;
    bool AllowDivisionType    (SqlConnection & connection ,
                               int             Type       ,
                               UUIDs         & Source     ,
                               UUIDs         & Target   ) ;

    bool Variable             (SqlConnection & SC,SUID uuid,QString name,QString & result) ;
    bool assureVariable       (SqlConnection & SC,SUID uuid,int type,QString name,QString value) ;
    bool deleteVariable       (SqlConnection & SC,SUID uuid,QString name) ;

    bool assignLanguage       (SqlConnection & SC,SUID first,int t1,int language) ;
    int  usingLanguage        (SqlConnection & SC,SUID first,int t1) ;
    int  usingLanguage        (SqlConnection & SC,SUID first,int t1,int defaultLanguage) ;

    // move to GroupItems
    virtual bool ObtainNames  (SqlConnection & SC       ,
                               int             language ,
                               UUIDs         & Uuids    ,
                               NAMEs         & Names  ) ;

    // add to GroupItems
    bool FromNames            (SqlConnection & Connection ,
                               QString         Name       ,
                               UUIDs         & Uuids    ) ;
    bool FromNames            (SqlConnection & Connection ,
                               QStringList   & Names      ,
                               UUIDs         & Uuids    ) ;
    bool FromNames            (SqlConnection & Connection ,
                               QString         Table      ,
                               QString         Name       ,
                               UUIDs         & Uuids    ) ;
    bool FromNames            (SqlConnection & Connection ,
                               QString         Table      ,
                               QStringList   & Names      ,
                               UUIDs         & Uuids    ) ;
    bool NamesOwners          (SqlConnection & Connection ,
                               UUIDs         & Names      ,
                               UUIDs         & Owners   ) ;
    bool NamesOwners          (SqlConnection & Connection ,
                               QString         Table      ,
                               UUIDs         & Names      ,
                               UUIDs         & Owners   ) ;
    bool EradicateNames       (SqlConnection & Connection ,
                               SUID            nuid     ) ;
    bool FindByNames          (SqlConnection & Connection ,
                               int             TargetType ,
                               QStringList   & Names      ,
                               UUIDs         & Uuids    ) ;

  protected:

  private:

} ;

class Q_COMPONENTS_EXPORT FileDeputy
{
  public:

    Plan * FilePlan ;

    explicit FileDeputy (Plan * plan = NULL);
    virtual ~FileDeputy (void);

    QStringList Scan    (bool        & keepGoing,QString message,QStringList startDirs = QStringList() ) ;
    QStringList Scan    (QToolButton * keepGoing,QString message,QStringList startDirs = QStringList() ) ;
    QStringList Scan    (bool        & keepGoing,QString message,QStringList filters,QStringList & Dirs) ;
    QStringList Scan    (QToolButton * keepGoing,QString message,QStringList filters,QStringList & Dirs) ;

  protected:

  private:

} ;

/*****************************************************************************
 *                                                                           *
 *                              VCF Base objects                             *
 *                                                                           *
 *****************************************************************************/

class Q_COMPONENTS_EXPORT VcfFont
{
  public:

    SUID   uuid      ;
    double size      ;
    QFont  font      ;
    QPen   pen       ;
    QBrush penBrush  ;
    QBrush brush     ;
    QBrush selection ;
    bool   changed   ;

    explicit VcfFont         (void) ;
    virtual ~VcfFont         (void) ;

    QByteArray Configuration (void) ;
    void       Set           (QByteArray Conf);
    void       setFont       (QPainter * painter,int DPI);
    QRectF     boundingRect  (QString text,int DPI);
    VcfFont &  operator =    (Font & font) ;

  protected:

  private:

} ;

class Q_COMPONENTS_EXPORT VcfOptions
{
  public:

    explicit VcfOptions     (void) ;
    virtual ~VcfOptions     (void) ;

    bool                Private    ;
    bool                ColorMode  ;
    int                 DPI        ;
    double              PictureDPI ;
    bool                Insert     ;
    double              LineSpace  ;
    QSizeF              ScaleRatio ;
    QMap<int,VcfFont *> fonts      ;

    QPointF position        (QPointF cm           ) ;
    QRectF  Region          (QRectF  cm           ) ;
    QPointF Standard        (QPointF paper        ) ;
    QRectF  Standard        (QRectF  paper        ) ;
    QSizeF  PictureOnPaper  (QSize   size         ) ;
    QSizeF  PictureOnPaper  (QSize   size ,int DPI) ;

    VcfOptions & operator = (VcfOptions & options ) ;

  protected:

  private:

} ;

class Q_COMPONENTS_EXPORT VcfShape
{
  public:

    explicit VcfShape   (void) ;
    virtual ~VcfShape   (void) ;

    QPolygonF WideLine  (double width,QLineF & line) ;
    QPolygonF WideLine  (double width,QPointF & P1,QPointF & P2) ;
    QPolygonF FoldLines (double width,QPolygonF & lines) ;
    QPolygonF Triangle  (double width,double length,QLineF & line) ;

    QPolygonF Symmetry  (QPointF Center,int N,double shift,double radius) ;

  protected:

  private:

} ;

class Q_COMPONENTS_EXPORT VcfPainter
{
  public:

    UMAPs     Names     ;
    Pens      pens      ;
    Brushes   brushes   ;
    Gradients gradients ;
    FONTs     fonts     ;
    Pathes    pathes    ;
    BMAPs     switches  ;

    explicit VcfPainter        (void) ;
    virtual ~VcfPainter        (void) ;

    int           addPen       (int Id,QColor color) ;
    int           addBrush     (int Id,QColor color) ;
    void          addMap       (QString name,int Id) ;
    void          setPainter   (QPainter * painter,QString name) ;
    void          drawRect     (QPainter * painter,QString name,QRectF rect) ;
    void          drawBorder   (QPainter * painter,QString name,QRectF rect) ;
    QFontMetricsF FontMetrics  (int Id) ;
    QRectF        boundingRect (int Id,QString text);

  protected:

  private:

} ;

class Q_COMPONENTS_EXPORT VcfDisplay
{
  public:

    CUIDs Zooms ;

    explicit VcfDisplay           (void) ;
    virtual ~VcfDisplay           (void) ;

    void     Enlarge              (void);
    void     Shrink               (void);

    QDoubleSpinBox * ZoomSpin     (QWidget * parent,QWidget * widget,const char * method);
    void ZoomSpinChanged          (double value);

  protected:

    QGraphicsScene * Scene         ;
    VcfOptions       Options       ;
    QMargins         Margins       ;
    QTransform       Transform     ;
    QPointF          Origin        ;
    QRectF           View          ;
    Screen           screen        ;
    double           MonitorFactor ;
    double           ZoomFactor    ;
    int              DPI           ;

    QSize          available      (QSize  size) ;
    QSizeF         centimeter     (QSize  size) ;
    QSizeF         toPaper        (QSizeF cm  ) ;
    QRectF         asPaper        (QSize  size) ;

    QString        Percentage     (void);

    qreal          FactorLevel    (qreal factor,bool enlarge);

    void           setDefaultZoom (void) ;

  private:

} ;

class Q_COMPONENTS_EXPORT VcfItem : public QObject
                                  , public QGraphicsItem
                                  , public AbstractGui
{
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)
  public:

    VcfOptions        * Options   ;
    VcfPainter          Painter   ;
    bool                Printable ;
    bool                Editable  ;
    bool                Modified  ;
    bool                Overlay   ;
    bool                Lockup    ;
    VcfItems            Related   ;
    QMap<VcfItem *,int> Relations ;

    explicit VcfItem                 (QObject       * parent       ,
                                      QGraphicsItem * item         ,
                                      Plan          * plan = NULL) ;
    virtual ~VcfItem                 (void);

    void ItemMarriage                (VcfItem * item,int relationship);
    void ItemDivorce                 (VcfItem * item);
    int  Relationship                (VcfItem * item);

    void setOptions                  (VcfOptions & options,bool privated = false) ;
    void setPenStyle                 (int Id,Qt::PenStyle style) ;
    void setPenColor                 (int Id,QColor color) ;
    void setBrushStyle               (int Id,Qt::BrushStyle style) ;
    void setBrushColor               (int Id,QColor color) ;

    QPointF         toPaper          (QPointF cm) ;
    QRectF          toPaper          (QRectF region) ;
    QPolygonF       toPaper          (QPolygonF & polygon) ;

    QPoint          toView           (QPointF pos) ;
    QPoint          toGlobal         (QPointF pos) ;

    QPointF         FromView         (QPoint pos) ;

    QGraphicsView * GraphicsView     (void) ;

    QPointF Quadratic                (double t,QPointF & P1,QPointF & P2,QPointF & P3) ;
    QPointF Quadratic                (double t,int index,QPolygonF & polygon) ;
    QPointF Cubic                    (double t,int index,QPolygonF & polygon) ;

    QPainterPath UnitedPathes        (void) ;

    bool FetchFont                   (int Id,SUID uuid) ;
    bool FetchPen                    (int Id,SUID uuid) ;
    bool FetchBrush                  (int Id,SUID uuid) ;
    bool FetchGradient               (int Id,SUID uuid) ;

    bool FetchFont                   (int Id,QString name) ;
    bool FetchPen                    (int Id,QString name) ;
    bool FetchBrush                  (int Id,QString name) ;
    bool FetchGradient               (int Id,QString name) ;

    virtual void   settings          (int item) ;

    void           pushTransform     (void) ;
    void           popTransform      (void) ;
    void           adjustTransform   (void) ;
    virtual void   PaperTransform    (int DPI,QRectF Paper) ;

    virtual QRectF clipRect          (void) ;
    virtual QRectF visibleRect       (void) ;

    virtual QPointF mousePosition    (void) ;

  protected:

    QList<QPen      > pens         ;
    QList<QBrush    > brushes      ;
    QList<QFont     > fonts        ;
    QList<QTransform> transforms   ;
    QRectF            WritingPaper ;
    int               PaperDPI     ;

    void           pushPainters      (QPainter * p) ;
    void           popPainters       (QPainter * p) ;

    virtual bool Bustle              (void) ;
    virtual bool Vacancy             (void) ;

    virtual void focusInEvent        (QFocusEvent * event);
    virtual void focusOutEvent       (QFocusEvent * event);

    virtual void dragEnterEvent      (QGraphicsSceneDragDropEvent * event);
    virtual void dragLeaveEvent      (QGraphicsSceneDragDropEvent * event);
    virtual void dragMoveEvent       (QGraphicsSceneDragDropEvent * event);
    virtual void dropEvent           (QGraphicsSceneDragDropEvent * event);

    bool allowDrop                   (void);

    virtual bool        acceptDrop   (nDeclWidget,const QMimeData * mime);
    virtual bool        dropNew      (nDeclWidget,const QMimeData * mime,QPointF pos);
    virtual bool        dropMoving   (nDeclWidget,const QMimeData * mime,QPointF pos);
    virtual bool        dropAppend   (nDeclWidget,const QMimeData * mime,QPointF pos);
    virtual bool        removeDrop   (void);

    virtual bool        dragEnter    (QGraphicsSceneDragDropEvent * event) ;
    virtual bool        dragMove     (QGraphicsSceneDragDropEvent * event) ;
    virtual bool        drop         (QGraphicsSceneDragDropEvent * event) ;

  private:

  public slots:

    virtual void Paint               (QPainter * painter,QRectF Region,bool clip,bool color) = 0 ;

    virtual void PaintPath           (QPainter * painter,int Id) ;
    virtual void PaintPathes         (QPainter * painter) ;
    virtual void PaintLines          (QPainter * painter,int Id,QPolygonF & Lines);

    virtual void setPoints           (int Id,QSizeF radius,QPolygonF & dots) ;
    virtual void setWideLine         (int Id,double width,QLineF & Line) ;
    virtual void setFoldLines        (int Id,double width,QPolygonF & Lines) ;
    virtual void setQuadratic        (int Id,QPolygonF & polygon);

    virtual bool FocusIn             (void) ;
    virtual bool FocusOut            (void) ;

    virtual void ClearPathes         (void) ;
    virtual void MergePathes         (int TargetId) ;
    virtual void EnablePath          (int Id,bool enable) ;

  protected slots:

  private slots:

  signals:

    void FocusIn                     (VcfItem * item);
    void FocusOut                    (VcfItem * item);
    void contentModified             (VcfItem * item);
    void Canvas                      (VcfItem * item,QRectF Screen);
    void Selection                   (VcfItem * item,QRectF Screen);

} ;

class Q_COMPONENTS_EXPORT VcfManager
{
  public:

    VcfItems Items ;
    VcfMaps  Maps  ;

    explicit VcfManager (void);
    virtual ~VcfManager (void);

    QList<VcfContours *> ItemContours (VcfItem * parent) ;

  protected:

    QRectF   United     (QGraphicsView * view) ;
    QRectF   United     (QGraphicsView * view,QRectF & rectangle) ;
    QRectF   toScene    (QGraphicsView * view,VcfItem * item) ;
    QRect    toView     (QGraphicsView * view,VcfItem * item) ;
    int      addItem    (VcfItem * item,VcfItem * parent) ;
    int      takeItem   (VcfItem * item) ;

  private:

} ;

class Q_COMPONENTS_EXPORT VcfPaperConf
{
  public:

    QString paper     ;
    DMAPs   borders   ;
    int     paperX    ;
    int     paperY    ;
    int     dpi       ;
    int     direction ; // Qt::Vertical , Qt::Horizontal
    int     arrange   ; // Neutrino::Texts::...

    explicit VcfPaperConf     (void) ;
             VcfPaperConf     (const VcfPaperConf & conf) ;
    virtual ~VcfPaperConf     (void) ;

    VcfPaperConf & operator = (const VcfPaperConf & conf) ;

    int X                     (int page) ;
    int Y                     (int page) ;

    QRectF PaperAt            (int page,QRectF PaperSize) ;

  protected:

  private:

} ;

class Q_COMPONENTS_EXPORT VcfRectangle : public VcfItem
{
  Q_OBJECT
  public:

    QPointF    PaperPos   ;
    QRectF     PaperRect  ;
    QRectF     ScreenRect ;
    bool       Scaling    ;
    bool       Editing    ;
    double     Angle      ;
    QTransform Transform  ;

    enum { Type = UserType + VCF::Rectangle } ;
    virtual int type(void) const { return Type ; }

    explicit VcfRectangle          (QObject       * parent        ,
                                    QGraphicsItem * item          ,
                                    Plan          * plan = NULL ) ;
    virtual ~VcfRectangle          (void);

    virtual QRectF  boundingRect   (void) const;
    virtual QSizeF  PaperSize      (void) const;
    virtual QPointF PaperMiddle    (void) const;
    virtual QRectF  PaperRange     (void) const;

    QLineEdit     * NewLineEdit    (int Id) ;
    QComboBox     * NewComboBox    (int Id) ;

  protected:

    enum CornerPosition {
      NoSide      = 0   ,
      TopLeft     = 1   ,
      TopRight    = 2   ,
      BottomLeft  = 3   ,
      BottomRight = 4   ,
      LeftSide    = 5   ,
      RightSide   = 6   ,
      TopSide     = 7   ,
      BottomSide  = 8   ,
      Inside      = 9 } ;

    VcfProxys     Proxys     ;
    VcfWidgets    Widgets    ;
    VcfPoints     Points     ;
    VcfRectangles Rectangles ;
    IMAPs         Markers    ;

    virtual QVariant itemChange    (GraphicsItemChange change  ,
                                    const QVariant   & value ) ;

    virtual int  atCorner          (QPointF pos);

    virtual void hoverEnterEvent   (QGraphicsSceneHoverEvent * event);
    virtual void hoverLeaveEvent   (QGraphicsSceneHoverEvent * event);
    virtual void hoverMoveEvent    (QGraphicsSceneHoverEvent * event);

    virtual void Hovering          (QPointF pos);
    virtual void setCornerCursor   (int corner);

    virtual bool CursorMoving      (QGraphicsSceneMouseEvent * event) ;
    virtual bool ResizeStart       (QGraphicsSceneMouseEvent * event) ;
    virtual bool ResizeMoving      (QGraphicsSceneMouseEvent * event) ;
    virtual bool ResizeFinish      (QGraphicsSceneMouseEvent * event) ;

    virtual void ResizeRect        (QPointF P1,QPointF P2) ;
    virtual void ResizeWidth       (QPointF P1,QPointF P2) ;
    virtual void ResizeHeight      (QPointF P1,QPointF P2) ;

    virtual void scalePressEvent   (QGraphicsSceneMouseEvent * event) ;
    virtual void scaleMoveEvent    (QGraphicsSceneMouseEvent * event) ;
    virtual void scaleReleaseEvent (QGraphicsSceneMouseEvent * event) ;

    void DeleteGadgets             (void);
    void AttachZLevel              (void);
    void AttachOpacity             (void);
    void AttachRotation            (void);

    virtual void MountZLevel       (QGraphicsProxyWidget * proxy,QSlider * slider);
    virtual void MountOpacity      (QGraphicsProxyWidget * proxy,QSlider * slider);
    virtual void MountRotation     (QGraphicsProxyWidget * proxy,QDial   * dial  );
    virtual void RotationUpdated   (void);

  private:

  public slots:

    virtual void setPos            (QPointF CM);
    virtual void setRect           (QRectF  Region);
    virtual void setRange          (QRectF  paper);

  protected slots:

    void modifyZLevel              (int Z);
    void modifyOpacity             (int Opacity);
    void modifyRotation            (int Rotation);

  private slots:

  signals:

    void GeometryChanged           (VcfItem * item) ;

} ;

class Q_COMPONENTS_EXPORT VcfCursor : public VcfRectangle
{
  Q_OBJECT
  public:

    enum { Type = UserType + VCF::Cursor } ;
    virtual int type(void) const { return Type ; }

    explicit VcfCursor       (QObject       * parent        ,
                              QGraphicsItem * item          ,
                              Plan          * plan = NULL );
    virtual ~VcfCursor       (void);

    virtual void paint       (QPainter                       * painter      ,
                              const QStyleOptionGraphicsItem * option       ,
                              QWidget                        * widget = 0 ) ;

  protected:

    QTimer * Timer   ;
    bool     Showing ;

  private:

  public slots:

    virtual void Paint       (QPainter * painter,QRectF Region,bool clip,bool color) ;
    void         Start       (void);
    void         setInterval (int milliseconds) ;

  protected slots:

    void         Twinkling   (void);

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT VcfCanvas : public VcfRectangle
                                    , public Object
{
  Q_OBJECT
  public:

    enum CanvasMode {
      Empty  = 0    ,
      Border = 1    ,
      Board  = 2    ,
      Custom = 3  } ;

    int  Mode       ;

    enum { Type = UserType + VCF::Canvas };
    virtual int type(void) const { return Type; }

    explicit VcfCanvas                 (QObject       * parent       ,
                                        QGraphicsItem * item         ,
                                        Plan          * plan = NULL) ;
    virtual ~VcfCanvas                 (void);

    virtual void paint                 (QPainter * painter,const QStyleOptionGraphicsItem * option,QWidget * widget = 0);

    virtual void settings              (int item) ;

  protected:

    bool GradientEditing ;

    virtual void contextMenuEvent      (QGraphicsSceneContextMenuEvent * event);
    virtual void Hovering              (QPointF pos);
    virtual void setCornerCursor       (int corner);

    virtual void mouseDoubleClickEvent (QGraphicsSceneMouseEvent * event);
    virtual void mouseMoveEvent        (QGraphicsSceneMouseEvent * event);
    virtual void mousePressEvent       (QGraphicsSceneMouseEvent * event);
    virtual void mouseReleaseEvent     (QGraphicsSceneMouseEvent * event);

    virtual void MountZLevel           (QGraphicsProxyWidget * proxy,QSlider * slider);
    virtual void MountOpacity          (QGraphicsProxyWidget * proxy,QSlider * slider);
    virtual void MountRotation         (QGraphicsProxyWidget * proxy,QDial   * dial  );
    virtual void RotationUpdated       (void);
    virtual void NormalTransform       (void);

    virtual bool dropColor             (QWidget * source,QPointF pos,const QColor & color   ) ;
    virtual bool dropTags              (QWidget * source,QPointF pos,const UUIDs  & Uuids   ) ;
    virtual bool dropPen               (QWidget * source,QPointF pos,const SUID     pen     ) ;
    virtual bool dropBrush             (QWidget * source,QPointF pos,const SUID     brush   ) ;
    virtual bool dropGradient          (QWidget * source,QPointF pos,const SUID     gradient) ;

  private:

    QRectF       PanelRect             (void);
    QRectF       CenterRect            (void);

  public slots:

    virtual void Paint                 (QPainter * painter,QRectF Region,bool clip,bool color) ;
    virtual void setCanvas             (QRectF selection) ;

    virtual void addAdjustMenu         (MenuManager & menu) ;
    virtual void addFontMenu           (MenuManager & menu) ;
    virtual void addPenMenu            (MenuManager & menu) ;
    virtual void addBrushMenu          (MenuManager & menu) ;
    virtual void addGradientMenu       (MenuManager & menu) ;

    virtual bool MenuCommands          (int Id,QAction * Action) ;

    virtual void SavePen               (void) ;
    virtual void SaveBrush             (void) ;
    virtual void SaveGradient          (void) ;

    virtual void SaveContours          (void) ;

  protected slots:

    virtual void PenFinished           (void) ;
    virtual void BrushFinished         (void) ;
    virtual void GradientFinished      (void) ;
    virtual void ContourFinished       (void) ;

  private slots:

  signals:

    void Menu                          (VcfCanvas * canvas,QPointF pos);
    void ShapeName                     (VcfCanvas * canvas,QString name);

} ;

class Q_COMPONENTS_EXPORT VcfLabel : public VcfCanvas
{
  Q_OBJECT
  public:

    int     TextAlignment ;
    QString Content       ;

    enum { Type = UserType + VCF::Label };
    virtual int type(void) const { return Type; }

    explicit VcfLabel                  (QObject       * parent       ,
                                        QGraphicsItem * item         ,
                                        Plan          * plan = NULL) ;
    virtual ~VcfLabel                  (void) ;

    virtual QRectF ContentRect         (void) ;
    virtual QRectF EditorRect          (void) ;
    virtual QSizeF FitSize             (void) ;

  protected:

    virtual void mouseDoubleClickEvent (QGraphicsSceneMouseEvent * event) ;

  private:

  public slots:

    virtual void Paint                 (QPainter * painter,QRectF Region,bool clip,bool color) ;
    virtual void PaintText             (QPainter * painter,QRectF Region,bool clip,bool color);

    virtual void setText               (QString text);
    virtual void MountEditor           (void) ;

  protected slots:

    virtual void NameFinished          (void) ;

  private slots:

  signals:

    void Changed                       (VcfLabel * label) ;

} ;

class Q_COMPONENTS_EXPORT VcfPaper : public VcfRectangle
{
  Q_OBJECT
  public:

    enum BorderNames {
      Left   = 1 ,
      Top    = 2 ,
      Right  = 3 ,
      Bottom = 4
    };

    enum DrawingStyle {
      Editing   = 0 ,
      FrameOnly = 1
    };

    QString   Paper     ;
    int       DPI       ;
    int       Direction ;
    int       Alignment ;
    SUID      Page      ;
    QString   Name      ;
    DMAPs     Borders   ;
    bool      Movable   ;
    int       Style     ;
    VcfFont * Font      ;

    enum { Type = UserType + VCF::Paper } ;
    virtual int type(void) const { return Type; }

    explicit VcfPaper             (QObject       * parent       ,
                                   QGraphicsItem * item         ,
                                   Plan          * plan = NULL) ;
    virtual ~VcfPaper             (void);

    virtual void         paint    (QPainter * painter,const QStyleOptionGraphicsItem * option,QWidget * widget);
    virtual QPainterPath shape    (void) const ;
    virtual QRectF PaperEditing   (void) const ;

  protected:

    QMenu * menu ;

    virtual void contextMenuEvent (QGraphicsSceneContextMenuEvent * event);
    virtual void hoverMoveEvent   (QGraphicsSceneHoverEvent       * event);

  private:

  public slots:

    virtual void   Paint          (QPainter * painter,QRectF Region,bool clip,bool color) ;

    virtual void   PaintEditing   (QPainter * painter,QRectF Region,bool clip,bool color) ;
    virtual void   PaintFrame     (QPainter * painter,QRectF Region,bool clip,bool color) ;

    void Print                    (QPainter * painter,QRectF rect);
    void PaintRegion              (QPainter * painter);
    void PaintBorder              (QPainter * painter);
    void PaintName                (QPainter * painter,QRectF rect,bool clip);

    void setMargins               (qreal left,qreal top,qreal right,qreal bottom);
    void setMovable               (bool enable);
    void setMenu                  (QMenu * menu) ;

  protected slots:

    virtual bool Menu             (QPointF pos) ;

  private slots:

  signals:

    void Menu                     (VcfPaper * paper,QPointF pos) ;
    void Moving                   (QString name,QPointF pos,QPointF paper,QPointF scene);

} ;

class Q_COMPONENTS_EXPORT VcfRuler : public VcfRectangle
{
  Q_OBJECT
  public:

    Direction direction ;

    enum { Type = UserType + VCF::Ruler };
    virtual int type(void) const { return Type; }

    explicit VcfRuler  (QObject * parent,QGraphicsItem * item,Plan * plan = NULL) ;
    virtual ~VcfRuler  (void);

    virtual void paint (QPainter * painter,const QStyleOptionGraphicsItem * option,QWidget * widget = 0);

  protected:

  private:

  public slots:

    void CreatePath    (void) ;
    void Paint         (QPainter * painter,QRectF Region,bool clip,bool color);
    void PaintNorth    (QPainterPath * painter);
    void PaintSouth    (QPainterPath * painter);
    void PaintEast     (QPainterPath * painter);
    void PaintWest     (QPainterPath * painter);

  protected slots:

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT VcfGrid : public VcfCanvas
{
  Q_OBJECT
  public:

    QSizeF Gap ;
    QSizeF Dot ;

    enum { Type = UserType + VCF::Grid };
    virtual int type(void) const { return Type; }

    explicit VcfGrid  (QObject * parent,QGraphicsItem * item,Plan * plan = NULL);
    virtual ~VcfGrid  (void);

  protected:

  private:

  public slots:

    void CreatePath    (void) ;
    void CreateShape   (QPainterPath * p);
    void Paint         (QPainter * painter,QRectF Region,bool clip,bool color);

  protected slots:

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT VcfPath : public VcfItem
                                  , public Object
{
  Q_OBJECT
  public:

    bool Editing ;

    enum { Type = UserType + VCF::Path };
    virtual int type(void) const { return Type; }

    explicit VcfPath            (QObject * parent,QGraphicsItem * item,Plan * plan = NULL);
    virtual ~VcfPath            (void);

    virtual void paint          (QPainter * painter,const QStyleOptionGraphicsItem * option,QWidget * widget = 0);
    virtual QRectF boundingRect (void) const ;
    virtual QPainterPath shape  (void) const ;

    QPolygonF Polyline          (Contour & contour,bool closed = true) ;

  protected:

  private:

  public slots:

    virtual void Paint          (QPainter * painter,QRectF Region,bool clip,bool color) ;

    virtual void setPoints      (int Id,Contour & contour) ;
    virtual void setLines       (int Id,Contour & contour) ;
    virtual void setSplines     (int Id,Contour & contour) ;
    virtual void setContour     (int Id,Contour & contour) ;

  protected slots:

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT VcfLines : public VcfPath
{
  Q_OBJECT
  public:

    Contour   contour ;
    QPolygonF lines   ;

    enum { Type = UserType + VCF::Lines };
    virtual int type(void) const { return Type; }

    explicit VcfLines            (QObject       * parent       ,
                                  QGraphicsItem * item         ,
                                  Plan          * plan = NULL) ;
    virtual ~VcfLines            (void);

  protected:

  private:

  public slots:

    virtual void Paint          (QPainter * painter,QRectF Region,bool clip,bool color) ;

    virtual void Prepare        (bool line = false,bool dot = false) ;
    virtual void ShowLines      (bool line = false) ;

  protected slots:

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT VcfContours : public VcfPath
{
  Q_OBJECT
  public:

    Contour   contour ;
    QPolygonF lines   ;

    enum { Type = UserType + VCF::Contours };
    virtual int type(void) const { return Type; }

    explicit VcfContours          (QObject       * parent       ,
                                   QGraphicsItem * item         ,
                                   Plan          * plan = NULL) ;
    virtual ~VcfContours          (void);

  protected:

    virtual void contextMenuEvent (QGraphicsSceneContextMenuEvent * event);

    virtual bool dropColor        (QWidget * source,QPointF pos,const QColor & color) ;
    virtual bool dropTags         (QWidget * source,QPointF pos,const UUIDs & Uuids) ;
    virtual bool dropPen          (QWidget * source,QPointF pos,const SUID pen) ;
    virtual bool dropBrush        (QWidget * source,QPointF pos,const SUID brush) ;

  private:

  public slots:

    virtual void Paint            (QPainter * painter,QRectF Region,bool clip,bool color) ;

    virtual void Prepare          (bool line = false,bool dot = false) ;
    virtual void ShowLines        (bool line = false) ;

  protected slots:

  private slots:

  signals:

    void Menu                     (VcfContours * contour,QPointF pos);

} ;

class Q_COMPONENTS_EXPORT VcfLinker : public VcfLines
                                    , public Relation
{
  Q_OBJECT
  public:

    enum EditModel   {
      Freehand = 0   ,
      Node     = 1   ,
      Tree     = 2 } ;

    enum EditStatus   {
      Display  = 0    ,
      Line     = 1    ,
      Connect  = 2  } ;

    enum MovementMethod {
      Ignore     = 0    ,
      Direct     = 1    ,
      Horizontal = 2    ,
      Vertical   = 3    ,
      Optimize   = 4  } ;

    IMAPs                    Arrows     ;
    DMAPs                    Paraments  ;
    QMap<int,QPainterPath *> Intersects ;
    QMap<int,QPointF       > Melts      ;
    QMap<int,VcfNode      *> Linking    ;
    enum EditModel           Model      ;
    enum EditStatus          Status     ;
    enum MovementMethod      Movement   ;

    enum { Type = UserType + VCF::Linker } ;
    virtual int type(void) const { return Type; }

    explicit VcfLinker             (QObject       * parent       ,
                                    QGraphicsItem * item         ,
                                    Plan          * plan = NULL) ;
    virtual ~VcfLinker             (void) ;

    virtual void     setType       (int Type,SUID relation = 0) ;
    virtual Contour  Render        (void) ;

    virtual void settings          (int item) ;

    virtual bool hasFirst          (void) ;
    virtual bool hasSecond         (void) ;

  protected:

    VcfProxys     Proxys     ;
    VcfWidgets    Widgets    ;
    VcfPoints     Points     ;
    VcfRectangles Rectangles ;
    IMAPs         Markers    ;

    virtual void Configure        (void) ;

    virtual void contextMenuEvent (QGraphicsSceneContextMenuEvent * event) ;
    virtual QVariant itemChange   (GraphicsItemChange change,const QVariant & value) ;

  private:

  public slots:

    virtual void Paint            (QPainter * p,QRectF Region,bool,bool) ;

    virtual bool FocusIn          (void) ;
    virtual bool FocusOut         (void) ;

    virtual bool Menu             (QPointF pos) ;

    virtual void Prepare          (bool line = false,bool dot = false) ;

    virtual void setArrowLine     (int Id,Contour & contour,IMAPs & arrows,DMAPs & paraments) ;
    virtual void setArrowSegments (int Id,Contour & contour,IMAPs & arrows,DMAPs & paraments) ;
    virtual void setArrowLines    (int Id,Contour & contour,IMAPs & arrows,DMAPs & paraments) ;

    virtual void setFirst         (VcfNode * first ) ;
    virtual void setSecond        (VcfNode * second) ;
    virtual void detach           (void) ;

    virtual void setFirst         (QPointF pos) ;
    virtual void setEnd           (QPointF pos) ;

    virtual void ClipPath         (QPainterPath & Path) ;

    virtual void EnableArrow      (int id,bool enable = true) ;

  protected slots:

  private slots:

  signals:

    void Append                   (VcfItem * item,VcfItem * parent) ;
    void Remove                   (VcfItem * item) ;
    void Dissolve                 (VcfItem * item) ;

} ;

class Q_COMPONENTS_EXPORT VcfNode : public VcfItem
                                  , public Object
                                  , public Node
{
  Q_OBJECT
  public:

    enum BorderNames {
      Left   = 1     ,
      Top    = 2     ,
      Right  = 3     ,
      Bottom = 4   } ;

    QPointF    PaperPos      ;
    QRectF     PaperRect     ;
    QRectF     ScreenRect    ;
    QRectF     ParagraphRect ;
    QPolygonF  Lines         ;
    Contour    contour       ;
    double     Angle         ;
    QTransform Transform     ;
    DMAPs      Borders       ;
    int        Mode          ;
    int        Drawing       ;
    int        Alignment     ;
    bool       Scaling       ;
    bool       Bounding      ;
    bool       Editing       ;
    bool       Updated       ;

    enum { Type = UserType + VCF::Node } ;
    virtual int type(void) const { return Type; }

    explicit VcfNode                        (QObject       * parent       ,
                                             QGraphicsItem * item         ,
                                             Plan          * plan = NULL) ;
    virtual ~VcfNode                        (void);

    virtual QRectF       boundingRect       (void) const ;
    virtual QPainterPath shape              (void) const ;
    virtual void         paint              (QPainter * painter,const QStyleOptionGraphicsItem * option,QWidget * widget = 0);

    virtual void setUuid                    (SUID uuid,int type) ;
    virtual bool AttemptMelt                (VcfLinker * Linker,QPointF base) ;
    virtual bool AllowMelts                 (int side) ;

    virtual void settings                   (int item) ;

    QLineEdit *  NewLineEdit                (int Id) ;
    QPointF      PaperPosition              (VcfItem * item,QPointF position) ;

  protected:

    enum CornerPosition  {
      NoSide      =  0   ,
      TopLeft     =  1   ,
      TopRight    =  2   ,
      BottomLeft  =  3   ,
      BottomRight =  4   ,
      LeftSide    =  5   ,
      RightSide   =  6   ,
      TopSide     =  7   ,
      BottomSide  =  8   ,
      Inside      =  9   ,
      Holder      = 10   ,
      Dragger     = 11 } ;

    enum EditWays          {
      EditNothing    = 0   ,
      DragEditing    = 1   ,
      ScaleEditing   = 2   ,
      ContentEditing = 3   ,
      ShapeEditing   = 4   ,
      ConnectEditing = 5 } ;

    VcfProxys     Proxys       ;
    VcfWidgets    Widgets      ;
    VcfPoints     Points       ;
    VcfRectangles Rectangles   ;
    IMAPs         Markers      ;
    BMAPs         AllowCorners ;

    virtual enum EditWays       CastEditing (void) ;
    virtual enum CornerPosition atCorner    (QPointF pos) ;
    virtual void setCornerCursor            (enum CornerPosition corner) ;

    virtual void Configure                  (void) ;

    virtual void hoverEnterEvent            (QGraphicsSceneHoverEvent * event);
    virtual void hoverLeaveEvent            (QGraphicsSceneHoverEvent * event);
    virtual void hoverMoveEvent             (QGraphicsSceneHoverEvent * event);
    virtual void Hovering                   (QPointF pos);

    virtual void contextMenuEvent           (QGraphicsSceneContextMenuEvent * event);
    virtual void mouseDoubleClickEvent      (QGraphicsSceneMouseEvent * event);

    virtual void mousePressEvent            (QGraphicsSceneMouseEvent * event);
    virtual void mouseMoveEvent             (QGraphicsSceneMouseEvent * event);
    virtual void mouseReleaseEvent          (QGraphicsSceneMouseEvent * event);

    virtual void draggingPressEvent         (QGraphicsSceneMouseEvent * event);
    virtual void draggingMoveEvent          (QGraphicsSceneMouseEvent * event);
    virtual void draggingReleaseEvent       (QGraphicsSceneMouseEvent * event);

    virtual void scalePressEvent            (QGraphicsSceneMouseEvent * event);
    virtual void scaleMoveEvent             (QGraphicsSceneMouseEvent * event);
    virtual void scaleReleaseEvent          (QGraphicsSceneMouseEvent * event);

    virtual bool CursorMoving               (QGraphicsSceneMouseEvent * event) ;
    virtual bool ResizeStart                (QGraphicsSceneMouseEvent * event) ;
    virtual bool ResizeMoving               (QGraphicsSceneMouseEvent * event) ;
    virtual bool ResizeFinish               (QGraphicsSceneMouseEvent * event) ;

    virtual void ResizeRect                 (QPointF P1,QPointF P2) ;
    virtual void ResizeWidth                (QPointF P1,QPointF P2) ;
    virtual void ResizeHeight               (QPointF P1,QPointF P2) ;
    virtual void NewSize                    (QRectF rect) ;
    virtual void FinalSize                  (void) ;

    virtual void contentPressEvent          (QGraphicsSceneMouseEvent * event);
    virtual void contentMoveEvent           (QGraphicsSceneMouseEvent * event);
    virtual void contentReleaseEvent        (QGraphicsSceneMouseEvent * event);

    virtual void shapePressEvent            (QGraphicsSceneMouseEvent * event);
    virtual void shapeMoveEvent             (QGraphicsSceneMouseEvent * event);
    virtual void shapeReleaseEvent          (QGraphicsSceneMouseEvent * event);

    virtual void connectPressEvent          (QGraphicsSceneMouseEvent * event);
    virtual void connectMoveEvent           (QGraphicsSceneMouseEvent * event);
    virtual void connectReleaseEvent        (QGraphicsSceneMouseEvent * event);

    virtual QVariant itemChange             (GraphicsItemChange change,const QVariant & value);

    virtual bool dropFont                   (QWidget * source,QPointF pos,const SUID font ) ;
    virtual bool dropPen                    (QWidget * source,QPointF pos,const SUID pen  ) ;
    virtual bool dropBrush                  (QWidget * source,QPointF pos,const SUID brush) ;

    virtual void setContour                 (int Id,Contour & contour) ;

  private:

  public slots:

    virtual void Paint                      (QPainter * painter,QRectF Region,bool clip,bool color) ;
    virtual void RenderAppearance           (QPainter * painter,QRectF Region,bool clip,bool color) ;
    virtual void RenderObjects              (QPainter * painter,QRectF Region,bool clip,bool color) ;
    virtual void RenderParagraph            (QPainter * painter,QRectF Region,bool clip,bool color) ;
    virtual void RenderDocument             (QPainter * painter,QRectF Region,bool clip,bool color) ;

    virtual bool FocusIn                    (void) ;
    virtual bool FocusOut                   (void) ;

    virtual void EditMenu                   (MenuManager & menu,QPointF pos) ;
    virtual void RelationMenu               (MenuManager & menu,QPointF pos) ;
    virtual void AdjustmentMenu             (MenuManager & menu,QPointF pos) ;
    virtual void NodeMenu                   (VcfNode * node,QPointF pos) ;
    virtual bool Menu                       (QPointF pos) ;
    virtual bool MenuProcess                (QAction * action,MenuManager & menu) ;

    void         DeleteGadgets              (void) ;

    virtual void setPos                     (QPointF pos) ;
    virtual void setRect                    (QRectF rect) ;
    virtual void setRoundedRect             (QRectF rect,double xRadius,double yRadius) ;
    virtual void setPolygon                 (QPolygonF polygon) ;
    virtual void setContour                 (Contour & contour) ;

    virtual void DisplayBounding            (bool enabled) ;

    virtual bool doubleClicked              (QPointF pos) ;

  protected slots:

    virtual void connectNode                (VcfNode   * node) ;
    virtual void connectLinker              (VcfLinker * linker) ;
    virtual void AcceptAppend               (VcfItem   * item,VcfItem * parent) ;
    virtual void AcceptRemove               (VcfItem   * item) ;
    virtual void AcceptDissolve             (VcfItem   * item) ;
    virtual void AcceptMoving               (VcfItem   * item) ;
    virtual void SignalReceiver             (int command) ;

  private slots:

  signals:

    void Append                             (VcfItem * item,VcfItem * parent) ;
    void Remove                             (VcfItem * item) ;
    void Moving                             (VcfItem * item) ;
    void Menu                               (VcfNode * node,QPointF pos) ;

} ;

class Q_COMPONENTS_EXPORT VcfBlock : public VcfNode
{
  Q_OBJECT
  public:

    QRectF ChildRect ;
    QRectF NameRect  ;

    enum { Type = UserType + VCF::Block } ;
    virtual int type(void) const { return Type; }

    explicit VcfBlock                 (QObject       * parent       ,
                                       QGraphicsItem * item         ,
                                       Plan          * plan = NULL) ;
    virtual ~VcfBlock                 (void) ;

    virtual QRectF childRect          (void) ;
    virtual QRectF nameRect           (void) ;

    virtual bool AttemptMelt          (VcfLinker * Linker,QPointF base) ;
    virtual bool AllowMelts           (int side) ;

  protected:

    virtual void Configure            (void) ;
    virtual void Hovering             (QPointF pos);
    virtual enum EditWays CastEditing (void) ;

    virtual void NewSize              (QRectF rect) ;
    virtual void FinalSize            (void) ;

  private:

  public slots:

    virtual void Compactified         (void) ;

    virtual bool FocusIn              (void) ;
    virtual bool FocusOut             (void) ;

    virtual void setRange             (QRectF rect) ;
    virtual void EnterEditor          (void) ;
    virtual bool doubleClicked        (QPointF pos) ;

  protected slots:

    virtual void nameFinished         (void) ;

  private slots:

  signals:

    void Update                       (VcfBlock * block,int item) ;

} ;

class Q_COMPONENTS_EXPORT VcfInterface : public VcfCanvas
{
  Q_OBJECT
  public:

    bool    showHeader       ;
    QRectF  HeaderRect       ;
    QString Title            ;

    enum { Type = UserType + VCF::Interface } ;
    virtual int type(void) const { return Type; }

    explicit VcfInterface              (QObject       * parent       ,
                                        QGraphicsItem * item         ,
                                        Plan          * plan = NULL) ;
    virtual ~VcfInterface              (void) ;

    virtual QPainterPath shape         (void) const ;

    QRect mapToPixel                   (QRectF rect) ;

  protected:

    QMap<int,double> Margins ;

    virtual void Configure             (void) ;

    virtual QVariant itemChange        (GraphicsItemChange change,const QVariant & value);

    virtual void hoverEnterEvent       (QGraphicsSceneHoverEvent * event);
    virtual void hoverLeaveEvent       (QGraphicsSceneHoverEvent * event);
    virtual void hoverMoveEvent        (QGraphicsSceneHoverEvent * event);
    virtual void Hovering              (QPointF pos);

    virtual void contextMenuEvent      (QGraphicsSceneContextMenuEvent * event) ;
    virtual void mouseDoubleClickEvent (QGraphicsSceneMouseEvent * event) ;
    virtual void mouseMoveEvent        (QGraphicsSceneMouseEvent * event);
    virtual void mousePressEvent       (QGraphicsSceneMouseEvent * event);
    virtual void mouseReleaseEvent     (QGraphicsSceneMouseEvent * event);

    virtual bool CursorMoving          (QGraphicsSceneMouseEvent * event) ;
    virtual bool ResizeStart           (QGraphicsSceneMouseEvent * event) ;
    virtual bool ResizeMoving          (QGraphicsSceneMouseEvent * event) ;
    virtual bool ResizeFinish          (QGraphicsSceneMouseEvent * event) ;

    virtual bool ResizeWidget          (void) ;

  private:

  public slots:

    virtual void Paint                 (QPainter * painter,QRectF  Region,bool clip,bool color) ;
    virtual void setWidget             (QWidget  * widget ,QPointF CM,QRect Frame,QRect Child) ;
    virtual void setChild              (QWidget  * widget ,QPointF CM,QRect Frame,QRect Child) ;

    virtual void AdjustHeader          (void) ;
    virtual void Finish                (void) ;

  protected slots:

    virtual bool InterfaceMenu         (QPointF pos) ;

  private slots:

  signals:

    void Resized                       (VcfItem * item) ;
    void Finish                        (VcfItem * item) ;

} ;

class Q_COMPONENTS_EXPORT VcfSlider : public VcfItem
{
  Q_OBJECT
  public:

    QString ToolTip ;

    enum { Type = UserType + VCF::Slider } ;
    virtual int type(void) const { return Type; }

    explicit VcfSlider                 (QObject       * parent       ,
                                        QGraphicsItem * item         ,
                                        Plan          * plan = NULL) ;
    virtual ~VcfSlider                 (void);

    virtual QRectF       boundingRect  (void) const ;
    virtual QPainterPath shape         (void) const ;
    virtual void         paint         (QPainter * painter,const QStyleOptionGraphicsItem * option,QWidget * widget = 0);

    double Minimum                     (void) ;
    double Maximum                     (void) ;
    double Value                       (QPointF pos) ;

  protected:

    DMAPs             Values ;
    QMap<int,QPointF> Points ;

    virtual void Configure             (void) ;

    virtual void hoverEnterEvent       (QGraphicsSceneHoverEvent * event);
    virtual void hoverLeaveEvent       (QGraphicsSceneHoverEvent * event);
    virtual void hoverMoveEvent        (QGraphicsSceneHoverEvent * event);
    virtual void Hovering              (QPointF pos);

    virtual void mouseDoubleClickEvent (QGraphicsSceneMouseEvent * event) ;
    virtual void mouseMoveEvent        (QGraphicsSceneMouseEvent * event);
    virtual void mousePressEvent       (QGraphicsSceneMouseEvent * event);
    virtual void mouseReleaseEvent     (QGraphicsSceneMouseEvent * event);

  private:

  public slots:

    virtual void Paint                 (QPainter * painter,QRectF Region,bool clip,bool color) ;

    virtual void setLine               (double width,double inside,QPointF P1,QPointF P2) ;
    virtual void setLine               (double width,double inside,QLineF L) ;

    virtual void setRange              (double minimum,double maximum) ;
    virtual void setVisible            (double start  ,double final  ) ;

    virtual void startPosition         (QPointF pos) ;
    virtual void setPosition           (QPointF pos) ;
    virtual void endPosition           (void) ;
    virtual void updatePosition        (void) ;

  protected slots:

  private slots:

  signals:

    void Visible                       (double start,double final,int step) ;

} ;

class Q_COMPONENTS_EXPORT VcfPaperManager
{
  public:

    Plan              *  paperPlan ;
    VcfPaperConf         paperConf ;
    QList<VcfPaper    *> papers    ;
    QList<VcfRuler    *> rulers    ;
    QList<VcfGrid     *> grids     ;
    QMap<int,VcfPaper *> pages     ;
    QMap<int,QString   > tables    ;
    QRectF               range     ;

    explicit VcfPaperManager (Plan * plan = NULL) ;
    virtual ~VcfPaperManager (void) ;

    void   ClearPapers       (void) ;
    QRectF CalculateRange    (void) ;
    QRectF CalculateView     (void) ;
    void   ClearRulers       (void) ;

    bool Add                 (QGraphicsView * View,QGraphicsScene * Scene,VcfOptions * Options,const char * method,PaperArrangement * Arrangement) ;
    void AddPaper            (QGraphicsView * view,QGraphicsScene * scene,VcfOptions * options,const char * method) ;
    bool Default             (QGraphicsView * View,QGraphicsScene * Scene,VcfOptions * Options,const char * method) ;
    int  AddGrid             (QGraphicsView * View,QGraphicsScene * Scene,VcfOptions * Options,QRectF Range);
    bool contains            (QGraphicsItem * item) ;

    #ifndef Q_OS_IOS
    QPrinter * PrintFile     (QWidget * widget,QString caption,QString filepath,QString filters);
    QRectF     startPage     (QPrinter * printer,int PageId);
    bool       endPage       (QPrinter * printer,int PageId);
    #endif

    VcfGrid  * CreateGrid    (QGraphicsView * View,QGraphicsScene * Scene,VcfOptions * Options,QRectF Range);
    virtual void PapersMenu  (QGraphicsView * View,const char * method) ;

  protected:

    VcfPaper * CreatePaper(
            int              dpi       ,
            QGraphicsView  * view      ,
            QGraphicsScene * scene     ,
            VcfOptions     * Options   ,
            const char     * method    ,
            int              direction ,
            QString          name      ,
            QString          paperSpec ,
            QPointF          Start     ,
            DMAPs            Borders ) ;

    void CreatePapers        (int dpi,QGraphicsView * View,QGraphicsScene * Scene,VcfOptions * Options,const char * method,int X,int Y,int Direction,QString paperSpec,DMAPs Borders);
    void CreateRulers        (int dpi,QGraphicsView * View,QGraphicsScene * Scene,VcfOptions * Options);

  private:

    #ifndef Q_OS_IOS
    QPrinter::PaperSize   paperSize        (QString name);
    QPrinter::Orientation paperOrientation (int orientation);
    #endif

} ;

/*****************************************************************************
 *                                                                           *
 *                   First level traditional GUI enhancements                *
 *                                                                           *
 *****************************************************************************/

class Q_COMPONENTS_EXPORT BalloonTip : public QWidget
{
  public:

    explicit BalloonTip          (const QString & title   ,
                                  const QString & msg     ,
                                  nDeclWidget   = NULL  ) ;
    virtual ~BalloonTip          (void) ;

    static QWidget * showBalloon (const QString & title              ,
                                  const QString & msg                ,
                                  int             timeout   = 0      ,
                                  bool            showArrow = true ) ;
    static void hideBalloon      (void) ;

  protected:

    QPixmap pixmap  ;
    int     timerId ;

    virtual void paintEvent      (QPaintEvent   * event) ;
    virtual void resizeEvent     (QResizeEvent  * event) ;
    virtual void mousePressEvent (QMouseEvent   * event) ;
    virtual void timerEvent      (QTimerEvent   * event) ;

    virtual void Configure       (const QString & title ,
                                  const QString & msg ) ;

  private:

    void balloon                 ( int , bool ) ;

  public slots:

  protected slots:

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT DragDropStatusBar : public QStatusBar
{
  Q_OBJECT
  public:

    explicit DragDropStatusBar  (nDeclWidget = NULL) ;
    virtual ~DragDropStatusBar  (void);

  protected:

    virtual void dragEnterEvent (QDragEnterEvent * event) ;
    virtual void dropEvent      (QDropEvent      * event) ;

  private:

  public slots:

    virtual void Report         (const QMimeData * mime) ;
    void         postMessage    (const QString & message,int timeout = 0) ;

  protected slots:

  private slots:

  signals:

    void pendMessage            (const QString & message,int timeout) ;

} ;

class Q_COMPONENTS_EXPORT Widget : public QWidget
                                 , public VirtualGui
                                 , public Thread
{
  Q_OBJECT
  Q_PROPERTY(bool designable READ canDesign WRITE setDesignable DESIGNABLE true)
  public:

    explicit Widget (StandardConstructor) ;
    virtual ~Widget (void               ) ;

  protected:

    virtual bool event         (QEvent * event) ;

  private:

  public slots:

  protected slots:

     virtual void DropCommands (void) ;

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT ToolWrapper : public QWidget
                                      , public VirtualGui
                                      , public Thread
{
  Q_OBJECT
  Q_PROPERTY(bool designable READ canDesign WRITE setDesignable DESIGNABLE true)
  public:

    explicit      ToolWrapper  (StandardConstructor,Qt::WindowFlags f = Qt::Popup) ;
    virtual      ~ToolWrapper  (void               ) ;

    virtual QSize sizeHint     (void) const ;

    QWidget *     widget       (void) ;

  protected:

    QWidget     * LocalWidget ;
    AbstractGui * Abstract    ;

    virtual void  closeEvent   (QCloseEvent  * event) ;
    virtual void  resizeEvent  (QResizeEvent * event) ;
    virtual void  showEvent    (QShowEvent   * event) ;

    virtual void focusInEvent  (QFocusEvent  * event) ;
    virtual void focusOutEvent (QFocusEvent  * event) ;

  private:

  public slots:

    virtual bool Relocation    (void) ;
    virtual void setWidget     (QWidget * widget) ;
    virtual void setAbstract   (AbstractGui * abstract) ;
    virtual void setDisappear  (int msec) ;
    virtual void DelayedClose  (void) ;

  protected slots:

  private slots:

  signals:

    void GainFocus             (QWidget * w) ;
    void LostFocus             (QWidget * w) ;
    void Leave                 (QWidget * w) ;

} ;

class Q_COMPONENTS_EXPORT ProgressIndicator : public Widget
{
  Q_OBJECT
  Q_PROPERTY(int delay READ animationDelay WRITE setAnimationDelay)
  Q_PROPERTY(bool displayedWhenStopped READ isDisplayedWhenStopped WRITE setDisplayedWhenStopped)
  Q_PROPERTY(QColor color READ color WRITE setColor)
  Q_PROPERTY(int ticks READ TickCount WRITE setTicks)
  Q_PROPERTY(double radius READ RadiusFactor WRITE setRadiusFactor)
  public:

    explicit       ProgressIndicator      (StandardConstructor) ;
    explicit       ProgressIndicator      (QWidget * widget,Plan * plan,QSize hint) ;
    virtual       ~ProgressIndicator      (void               ) ;

    int            animationDelay         (void) const ;
    bool           isAnimated             (void) const ;
    bool           isDisplayedWhenStopped (void) const ;
    const QColor & color                  (void) const ;
    int            TickCount              (void) const ;
    double         RadiusFactor           (void) const ;

    virtual QSize  sizeHint               (void) const ;
    int            heightForWidth         (int w) const ;

  protected:

    virtual void timerEvent               (QTimerEvent * event) ;
    virtual void paintEvent               (QPaintEvent * event) ;

  private:

    int    m_angle                ;
    int    m_timerId              ;
    int    m_delay                ;
    int    m_entry                ;
    int    m_count                ;
    double m_factor               ;
    bool   m_displayedWhenStopped ;
    QColor m_color                ;
    QSize  hint                   ;

  public slots:

    virtual void startAnimation           (void);
    virtual int  stopAnimation            (void);
    virtual void setAnimationDelay        (int delay);
    virtual void setDisplayedWhenStopped  (bool state);
    virtual void setColor                 (const QColor & color);
    virtual void setTicks                 (int count) ;
    virtual void setRadiusFactor          (double factor) ;

  protected slots:

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT ReflexWidget : public Widget
{
  Q_OBJECT
  Q_PROPERTY(QColor colorBg READ colorBack WRITE setColorBg)
  Q_PROPERTY(QColor colorTx READ colorTxt WRITE setColorTx)
  Q_PROPERTY(int alphaFst READ alphaFirst WRITE setAlphaFst)
  Q_PROPERTY(int alphaSnd READ alphaSecond WRITE setAlphaSnd)
  Q_PROPERTY(int alphaTxt READ alphaText WRITE setAlphaTxt)
  Q_PROPERTY(int reflexLgh READ reflex WRITE setReflexLgh)
  Q_PROPERTY(double shear READ shearDim WRITE setShear)
  Q_PROPERTY(QString text READ txt WRITE setText)
  Q_PROPERTY(QFont font READ fnt WRITE setFont)
  public:

    explicit ReflexWidget   (StandardConstructor) ;
    virtual ~ReflexWidget   (void) ;

    QSize   minimumSizeHint (void) const ;
    QSize   sizeHint        (void) const ;

    QColor  colorBack       (void) const ;
    QColor  colorTxt        (void) const ;
    QString txt             (void) const ;
    QFont   fnt             (void) const ;
    int     alphaFirst      (void) const ;
    int     alphaSecond     (void) const ;
    int     alphaText       (void) const ;
    int     reflex          (void) const ;
    double  shearDim        (void) const ;

  protected:

    void paintEvent         (QPaintEvent * event) ;
    void paintWidget        (void) ;

  private:

    QString text            ;
    double  shear           ;
    QColor  colorBg         ;
    QColor  colorTx         ;
    QColor  reflexColorBg   ;
    QColor  reflexColorBord ;
    QColor  reflexColorFst  ;
    QColor  reflexColorSnd  ;
    QColor  reflexColorTx   ;
    QFont   font            ;
    int     alphaFst        ;
    int     alphaSnd        ;
    int     alphaTxt        ;
    int     sizeTx          ;
    int     reflexLgh       ;

  public slots:

    void setColorBg         (QColor) ;
    void setColorTx         (QColor) ;
    void setAlphaFst        (int) ;
    void setAlphaSnd        (int) ;
    void setAlphaTxt        (int) ;
    void setReflexLgh       (int) ;
    void setShear           (double) ;
    void setText            (QString) ;
    void setFont            (QFont) ;

  protected slots:

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT Dialog : public QDialog
                                 , public VirtualGui
                                 , public Thread
{
  Q_OBJECT
  Q_PROPERTY(bool designable READ canDesign WRITE setDesignable DESIGNABLE true)
  public:

    explicit Dialog (StandardConstructor) ;
    virtual ~Dialog (void               ) ;

  protected:

  private:

  public slots:

  protected slots:

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT StackedWidget : public QStackedWidget
                                        , public VirtualGui
                                        , public Thread
{
  Q_OBJECT
  Q_PROPERTY(bool designable READ canDesign WRITE setDesignable DESIGNABLE true)
  public:

    explicit StackedWidget     (StandardConstructor) ;
    virtual ~StackedWidget     (void               ) ;

  protected:

  private:

  public slots:

    virtual void  AttachMenu   (QMenu * menu,QActionGroup * group) ;

  protected slots:

     virtual void DropCommands (void) ;

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT ScrollArea : public QScrollArea
                                     , public VirtualGui
{
  Q_OBJECT
  Q_PROPERTY(bool designable READ canDesign WRITE setDesignable DESIGNABLE true)
  public:

    explicit ScrollArea        (StandardConstructor) ;
    virtual ~ScrollArea        (void               ) ;

  protected:

  private:

  public slots:

  protected slots:

     virtual void DropCommands (void) ;

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT MdiSubWindow : public QMdiSubWindow
{
  Q_OBJECT
  public:

    AbstractGui * abstract ;

    explicit MdiSubWindow   (QWidget * parent = NULL,Qt::WindowFlags flags = 0) ;
    virtual ~MdiSubWindow   (void) ;

  protected:

    virtual void closeEvent (QCloseEvent * e) ;

  private:

  public slots:

  protected slots:

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT MdiArea : public QMdiArea
                                  , public VirtualGui
                                  , public Thread
{
  Q_OBJECT
  Q_PROPERTY(bool designable READ canDesign WRITE setDesignable DESIGNABLE true)
  public:

    QGraphicsDropShadowEffect *  Shadow ;

    explicit MdiArea              (StandardConstructor) ;
    virtual ~MdiArea              (void);

    bool             contains     (QString accessibleName) ;
    QWidget *        findWidget   (QString accessibleName) ;
    QList<QWidget *> getWidgets   (QString accessibleName) ;

  protected:

    QMenu         *  WindowLists ;
    QList<QAction *> MenuActions ;

    virtual void Configure        (void) ;

    virtual void focusInEvent     (QFocusEvent       * event) ;
    virtual void focusOutEvent    (QFocusEvent       * event) ;
    virtual void contextMenuEvent (QContextMenuEvent * event) ;

    virtual void dragEnterEvent   (QDragEnterEvent   * event) ;
    virtual void dragLeaveEvent   (QDragLeaveEvent   * event) ;
    virtual void dragMoveEvent    (QDragMoveEvent    * event) ;
    virtual void dropEvent        (QDropEvent        * event) ;

    virtual bool acceptDrop       (nDeclWidget,const QMimeData * mime);
    virtual bool dropNew          (nDeclWidget,const QMimeData * mime,QPoint pos);
    virtual bool dropMoving       (nDeclWidget,const QMimeData * mime,QPoint pos);
    virtual bool dropAppend       (nDeclWidget,const QMimeData * mime,QPoint pos);

    virtual bool dropUrls         (nDeclWidget,QPointF pos,const QList<QUrl> & urls) ;

    void MenuStatus               (void) ;

    QMdiSubWindow * append        (QWidget * widget) ;

  private:

  public slots:

    void setWindowMenu            (QMenu * menu) ;
    void Connect                  (nDeclWidget) ;
    void Adjustment               (nDeclWidget,QSize size) ;
    void Adjustment               (nDeclWidget) ;
    void Leave                    (nDeclWidget) ;
    void Fit                      (nDeclWidget) ;
    void Attach                   (nDeclWidget) ;
    void Attach                   (nDeclWidget,int direction) ;
    void Subwindow                (void) ;
    void Tabbed                   (void) ;
    void Tile                     (void) ;
    void Cascade                  (void) ;
    void CloseAll                 (void) ;

  protected slots:

    virtual bool Menu             (QPoint pos) ;
    void subActivated             (QMdiSubWindow * window) ;
    void menuToShow               (void) ;
    void subwindowChecked         (bool checked) ;
    virtual void DropCommands     (void) ;

  private slots:

  signals:

    void lastClosed               (void);
    void childChanged             (void);
    void Files                    (const QList<QUrl> & urls) ;

} ;

class Q_COMPONENTS_EXPORT HeaderView : public QHeaderView
                                     , public VirtualGui
{
  Q_OBJECT
  Q_PROPERTY(bool designable READ canDesign WRITE setDesignable DESIGNABLE true)
  public:

    explicit HeaderView           (Qt::Orientation orientation,StandardConstructor);
    virtual ~HeaderView           (void);

  protected:

    virtual void contextMenuEvent (QContextMenuEvent * event) ;

  private:

  public slots:

  protected slots:

  private slots:

  signals:

    void HeaderMenu               (QHeaderView * view,QPoint pos) ;

} ;

class Q_COMPONENTS_EXPORT SplitterHandle : public QSplitterHandle
                                         , public VirtualGui
{
  Q_OBJECT
  Q_PROPERTY(bool designable READ canDesign WRITE setDesignable DESIGNABLE true)
  public:

    explicit SplitterHandle       (Qt::Orientation orientation   ,
                                   Splitter      * parent        ,
                                   Plan          * plan = NULL ) ;
    virtual ~SplitterHandle       (void) ;

  protected:

    virtual void contextMenuEvent (QContextMenuEvent * event) ;

  private:

  public slots:

  protected slots:

    virtual bool Menu             (QPoint pos) ;

  private slots:

  signals:

    void assignOrientation        (Qt::Orientation orientation) ;

} ;

class Q_COMPONENTS_EXPORT Splitter : public QSplitter
                                   , public VirtualGui
{
  Q_OBJECT
  Q_PROPERTY(bool designable READ canDesign WRITE setDesignable DESIGNABLE true)
  public:

    explicit Splitter (Qt::Orientation orientation,StandardConstructor) ;
    virtual ~Splitter (void) ;

  protected:

    virtual QSplitterHandle * createHandle (void) ;

  private:

  public slots:

  protected slots:

    virtual void assignOrientation (Qt::Orientation orientation) ;

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT SpinBox : public QSpinBox
                                  , public VirtualGui
{
  Q_OBJECT
  Q_PROPERTY(bool designable READ canDesign WRITE setDesignable DESIGNABLE true)
  public:

    int * External ;

    explicit SpinBox           (StandardConstructor) ;
    virtual ~SpinBox           (void               ) ;

  protected:

  private:

  public slots:

  protected slots:

     virtual void DropCommands (void) ;
     virtual void assignValue  (int value) ;

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT DoubleSpinBox : public QDoubleSpinBox
                                        , public VirtualGui
{
  Q_OBJECT
  Q_PROPERTY(bool designable READ canDesign WRITE setDesignable DESIGNABLE true)
  public:

    double * External ;

    explicit DoubleSpinBox     (StandardConstructor) ;
    virtual ~DoubleSpinBox     (void               ) ;

  protected:

  private:

  public slots:

  protected slots:

     virtual void DropCommands (void) ;
     virtual void assignValue  (double value) ;

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT ToolBar : public QToolBar
                                  , public VirtualGui
                                  , public Thread
{
  Q_OBJECT
  Q_PROPERTY(bool designable READ canDesign WRITE setDesignable DESIGNABLE true)
  public:

    explicit ToolBar             (StandardConstructor) ;
    virtual ~ToolBar             (void               ) ;

  protected:

    virtual void Configure       (void) ;

    virtual void resizeEvent     (QResizeEvent * e) ;
    virtual void showEvent       (QShowEvent   * e) ;

  private:

  public slots:

    virtual bool Relocation      (void) ;

  protected slots:

    virtual void DropCommands    (void) ;
    virtual void geometryChanged (bool state) ;

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT TabBar : public QTabBar
                                 , public VirtualGui
{
  Q_OBJECT
  Q_PROPERTY(bool designable READ canDesign WRITE setDesignable DESIGNABLE true)
  public:

    explicit TabBar               (StandardConstructor) ;
    virtual ~TabBar               (void);

  protected:

    virtual void paintEvent       (QPaintEvent       * event) ;

    virtual void focusInEvent     (QFocusEvent       * event) ;
    virtual void focusOutEvent    (QFocusEvent       * event) ;

    virtual void contextMenuEvent (QContextMenuEvent * event) ;
    virtual void resizeEvent      (QResizeEvent      * event) ;

    virtual void closeEvent       (QCloseEvent       * event) ;

    virtual void Configure        (void);

  private:

  public slots:

    virtual bool Shutdown         (void) ;
    virtual bool Relocation       (void) ;

  protected slots:

    virtual bool Menu             (QPoint pos);

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT LineEdit : public QLineEdit
                                   , public VirtualGui
                                   , public Thread
{
  Q_OBJECT
  Q_PROPERTY(bool designable READ canDesign WRITE setDesignable DESIGNABLE true)
  public:

    explicit     LineEdit        (StandardConstructor) ;
    virtual ~    LineEdit        (void               ) ;

  protected:

    virtual void paintEvent      (QPaintEvent     * event) ;

    virtual void focusInEvent    (QFocusEvent     * event) ;
    virtual void focusOutEvent   (QFocusEvent     * event) ;

    virtual void resizeEvent     (QResizeEvent    * event) ;

    virtual void dragEnterEvent  (QDragEnterEvent * event) ;
    virtual void dragLeaveEvent  (QDragLeaveEvent * event) ;
    virtual void dragMoveEvent   (QDragMoveEvent  * event) ;
    virtual void dropEvent       (QDropEvent      * event) ;

    virtual bool acceptDrop      (nDeclWidget,const QMimeData * mime);
    virtual bool dropNew         (nDeclWidget,const QMimeData * mime,QPoint pos);
    virtual bool dropMoving      (nDeclWidget,const QMimeData * mime,QPoint pos);
    virtual bool dropAppend      (nDeclWidget,const QMimeData * mime,QPoint pos);

    virtual bool dropFont        (nDeclWidget,QPointF pos,const SUID font ) ;
    virtual bool dropPen         (nDeclWidget,QPointF pos,const SUID pen  ) ;
    virtual bool dropBrush       (nDeclWidget,QPointF pos,const SUID brush) ;

    virtual void assignFont      (Font  & font ) ;
    virtual void assignPen       (Pen   & pen  ) ;
    virtual void assignBrush     (Brush & brush) ;

  private:

  public slots:

    QCompleter * updateCompleter (QStringList & list) ;

  protected slots:

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT ComboBox : public QComboBox
                                   , public VirtualGui
                                   , public Thread
{
  Q_OBJECT
  Q_PROPERTY(bool designable READ canDesign WRITE setDesignable DESIGNABLE true)
  public:

    explicit     ComboBox        (StandardConstructor) ;
    virtual ~    ComboBox        (void               ) ;

    SUID         toUuid          (void) ;
    SUID         toUuid          (int index) ;

  protected:

    virtual void Configure       (void) ;

    virtual void paintEvent      (QPaintEvent     * event) ;

    virtual void focusInEvent    (QFocusEvent     * event) ;
    virtual void focusOutEvent   (QFocusEvent     * event) ;

    virtual void resizeEvent     (QResizeEvent    * event) ;

    virtual void dragEnterEvent  (QDragEnterEvent * event) ;
    virtual void dragLeaveEvent  (QDragLeaveEvent * event) ;
    virtual void dragMoveEvent   (QDragMoveEvent  * event) ;
    virtual void dropEvent       (QDropEvent      * event) ;

    virtual bool acceptDrop      (nDeclWidget,const QMimeData * mime);
    virtual bool dropNew         (nDeclWidget,const QMimeData * mime,QPoint pos);
    virtual bool dropMoving      (nDeclWidget,const QMimeData * mime,QPoint pos);
    virtual bool dropAppend      (nDeclWidget,const QMimeData * mime,QPoint pos);

    virtual bool dropFont        (nDeclWidget,QPointF pos,const SUID font ) ;
    virtual bool dropPen         (nDeclWidget,QPointF pos,const SUID pen  ) ;
    virtual bool dropBrush       (nDeclWidget,QPointF pos,const SUID brush) ;

    virtual void assignFont      (Font  & font ) ;
    virtual void assignPen       (Pen   & pen  ) ;
    virtual void assignBrush     (Brush & brush) ;

    virtual void run             (int Type,ThreadData * data) ;

  private:

  public slots:

    virtual void appendNames     (NAMEs & names) ;
    virtual void appendNames     (UUIDs & uuids,NAMEs & names) ;
    virtual void addItems        (UUIDs Uuids) ;
    virtual void addItems        (SqlConnection & Connection,UUIDs & Uuids) ;
    virtual void addItems        (QString table,enum Qt::SortOrder sorting) ;
    virtual void addGroups       (SUID group                                        ,
                                  int  t1                                           ,
                                  int  t2                                           ,
                                  int  relation                                     ,
                                  enum Qt::SortOrder sorting = Qt::AscendingOrder ) ;
    virtual void addDivision     (int  type                                         ,
                                  enum Qt::SortOrder sorting = Qt::AscendingOrder ) ;
    virtual void pendItems       (UUIDs Uuids) ;
    virtual void pendItems       (QString table,enum Qt::SortOrder sorting) ;
    virtual void pendGroups      (SUID group                                        ,
                                  int  t1                                           ,
                                  int  t2                                           ,
                                  int  relation                                     ,
                                  enum Qt::SortOrder sorting = Qt::AscendingOrder ) ;
    virtual void pendDivision    (int  type                                         ,
                                  enum Qt::SortOrder sorting = Qt::AscendingOrder ) ;

  protected slots:

    virtual void DropCommands    (void) ;

  private slots:

  signals:

    void assignNames             (NAMEs & names) ;

} ;

class Q_COMPONENTS_EXPORT ColumnView : public QColumnView
                                     , public VirtualGui
                                     , public Thread
{
  Q_OBJECT
  Q_PROPERTY(bool designable READ canDesign WRITE setDesignable DESIGNABLE true)
  public:

    explicit ColumnView             (StandardConstructor) ;
    virtual ~ColumnView             (void);

  protected:

    virtual void paintEvent         (QPaintEvent       * event) ;

    virtual void focusInEvent       (QFocusEvent       * event) ;
    virtual void focusOutEvent      (QFocusEvent       * event) ;

    virtual void contextMenuEvent   (QContextMenuEvent * event) ;
    virtual void resizeEvent        (QResizeEvent      * event) ;

    virtual void dragEnterEvent     (QDragEnterEvent   * event) ;
    virtual void dragLeaveEvent     (QDragLeaveEvent   * event) ;
    virtual void dragMoveEvent      (QDragMoveEvent    * event) ;
    virtual void dropEvent          (QDropEvent        * event) ;

    virtual void mousePressEvent    (QMouseEvent       * event) ;
    virtual void mouseMoveEvent     (QMouseEvent       * event) ;
    virtual void mouseReleaseEvent  (QMouseEvent       * event) ;

    virtual void closeEvent         (QCloseEvent       * event) ;
    virtual bool event              (QEvent * event) ;

    virtual void Configure          (void);

    virtual bool acceptDrop         (nDeclWidget,const QMimeData * mime);
    virtual bool dropNew            (nDeclWidget,const QMimeData * mime,QPoint pos);
    virtual bool dropMoving         (nDeclWidget,const QMimeData * mime,QPoint pos);
    virtual bool dropAppend         (nDeclWidget,const QMimeData * mime,QPoint pos);

    virtual bool dropFont           (nDeclWidget,QPointF pos,const SUID font ) ;
    virtual bool dropPen            (nDeclWidget,QPointF pos,const SUID pen  ) ;
    virtual bool dropBrush          (nDeclWidget,QPointF pos,const SUID brush) ;

    virtual void assignFont         (Font  & font ) ;
    virtual void assignPen          (Pen   & pen  ) ;
    virtual void assignBrush        (Brush & brush) ;

  private:

  public slots:

    virtual bool Shutdown           (void) ;
    virtual bool Relocation         (void) ;

    virtual void CopyToClipboard    (void) ;
    virtual void SelectNone         (void) ;
    virtual void SelectAll          (void) ;
    virtual void setFont            (void) ;

  protected slots:

    virtual bool Menu               (QPoint pos);
    virtual void DropCommands       (void) ;

  private slots:

  signals:

    void Adjustment                 (nDeclWidget,QSize size) ;
    void Adjustment                 (nDeclWidget) ;
    void Leave                      (nDeclWidget) ;
    void Command                    (SUID uuid);
    void Selected                   (SUID uuid);
    void ItemMenu                   (nDeclWidget,QPoint pos);
    void Command                    (nDeclWidget,QString name,SUID uuid);

} ;

class Q_COMPONENTS_EXPORT TabWidget : public QTabWidget
                                    , public VirtualGui
                                    , public Thread
{
  Q_OBJECT
  Q_PROPERTY(bool designable READ canDesign WRITE setDesignable DESIGNABLE true)
  public:

    explicit TabWidget            (StandardConstructor) ;
    virtual ~TabWidget            (void);

  protected:

    virtual void paintEvent       (QPaintEvent       * event) ;

    virtual void focusInEvent     (QFocusEvent       * event) ;
    virtual void focusOutEvent    (QFocusEvent       * event) ;

    virtual void contextMenuEvent (QContextMenuEvent * event) ;
    virtual void resizeEvent      (QResizeEvent      * event) ;
    virtual void showEvent        (QShowEvent        * event) ;

    virtual void closeEvent       (QCloseEvent       * event) ;

    virtual void Configure        (void);

    virtual bool event         (QEvent * event) ;

  private:

  public slots:

    virtual bool Shutdown         (void) ;
    virtual bool Relocation       (void) ;

    virtual void CopyToClipboard  (void) ;
    virtual void SelectNone       (void) ;
    virtual void SelectAll        (void) ;
    virtual void setFont          (void) ;

  protected slots:

    virtual bool Menu             (QPoint pos);
    virtual void DropCommands     (void) ;

  private slots:

  signals:

    void Adjustment               (nDeclWidget,QSize size) ;
    void Adjustment               (nDeclWidget) ;
    void Leave                    (nDeclWidget) ;
    void Command                  (SUID uuid);
    void Selected                 (SUID uuid);
    void ItemMenu                 (nDeclWidget,QPoint pos);
    void Command                  (nDeclWidget,QString name,SUID uuid);

} ;

class Q_COMPONENTS_EXPORT TextBrowser : public QTextBrowser
                                      , public VirtualGui
                                      , public Thread
{
  Q_OBJECT
  Q_PROPERTY(bool designable READ canDesign WRITE setDesignable DESIGNABLE true)
  public:

    explicit TextBrowser          (StandardConstructor) ;
    virtual ~TextBrowser          (void);

  protected:

    virtual void paintEvent       (QPaintEvent       * event) ;
    virtual void focusInEvent     (QFocusEvent       * event) ;
    virtual void focusOutEvent    (QFocusEvent       * event) ;

    virtual void contextMenuEvent (QContextMenuEvent * event) ;
    virtual void resizeEvent      (QResizeEvent      * event) ;

    virtual void dragEnterEvent   (QDragEnterEvent   * event) ;
    virtual void dragLeaveEvent   (QDragLeaveEvent   * event) ;
    virtual void dragMoveEvent    (QDragMoveEvent    * event) ;
    virtual void dropEvent        (QDropEvent        * event) ;

    virtual void closeEvent       (QCloseEvent       * event) ;

  private:

  public slots:

    virtual bool Shutdown         (void) ;
    virtual bool Relocation       (void) ;
    virtual void setFont          (void) ;

  protected slots:

    virtual void DropCommands     (void) ;

  private slots:

  signals:

    void Adjustment               (nDeclWidget,QSize size) ;
    void Adjustment               (nDeclWidget) ;
    void Leave                    (nDeclWidget) ;

} ;

class Q_COMPONENTS_EXPORT TextEdit : public QTextEdit
                                   , public VirtualGui
                                   , public Thread
{
  Q_OBJECT
  Q_PROPERTY(bool designable READ canDesign WRITE setDesignable DESIGNABLE true)
  public:

    explicit TextEdit             (StandardConstructor) ;
    virtual ~TextEdit             (void);

  protected:

    virtual void paintEvent       (QPaintEvent       * event) ;
    virtual void focusInEvent     (QFocusEvent       * event) ;
    virtual void focusOutEvent    (QFocusEvent       * event) ;

    virtual void contextMenuEvent (QContextMenuEvent * event) ;
    virtual void resizeEvent      (QResizeEvent      * event) ;

    virtual void closeEvent       (QCloseEvent       * event) ;

  private:

  public slots:

    virtual bool Shutdown         (void);
    virtual bool Relocation       (void);
    virtual void setFont          (void) ;

  protected slots:

    virtual void DropCommands     (void) ;

  private slots:

  signals:

    void Adjustment               (nDeclWidget,QSize size) ;
    void Adjustment               (nDeclWidget) ;
    void Leave                    (nDeclWidget) ;

} ;

class Q_COMPONENTS_EXPORT TableView : public QTableView
                                    , public VirtualGui
                                    , public Thread
{
  Q_OBJECT
  Q_PROPERTY(bool designable READ canDesign WRITE setDesignable DESIGNABLE true)
  public:

    explicit TableView             (StandardConstructor) ;
    virtual ~TableView             (void);

  protected:

    virtual void paintEvent        (QPaintEvent       * event) ;
    virtual void focusInEvent      (QFocusEvent       * event) ;
    virtual void focusOutEvent     (QFocusEvent       * event) ;

    virtual void contextMenuEvent  (QContextMenuEvent * event) ;
    virtual void resizeEvent       (QResizeEvent      * event) ;

    virtual void dragEnterEvent    (QDragEnterEvent   * event) ;
    virtual void dragLeaveEvent    (QDragLeaveEvent   * event) ;
    virtual void dragMoveEvent     (QDragMoveEvent    * event) ;
    virtual void dropEvent         (QDropEvent        * event) ;

    virtual void mousePressEvent   (QMouseEvent       * event) ;
    virtual void mouseMoveEvent    (QMouseEvent       * event) ;
    virtual void mouseReleaseEvent (QMouseEvent       * event) ;

    virtual void closeEvent        (QCloseEvent       * event) ;
    virtual bool event             (QEvent * event) ;

  private:

  public slots:

    virtual bool Shutdown          (void);
    virtual bool Relocation        (void);
    virtual void setFont           (void) ;

  protected slots:

    virtual void DropCommands      (void) ;

  private slots:

  signals:

    void Adjustment                (nDeclWidget,QSize size) ;
    void Adjustment                (nDeclWidget) ;
    void Leave                     (nDeclWidget) ;

} ;

class Q_COMPONENTS_EXPORT TableWidget : public QTableWidget
                                      , public VirtualGui
                                      , public Thread
{
  Q_OBJECT
  Q_PROPERTY(bool designable READ canDesign WRITE setDesignable DESIGNABLE true)
  public:

    explicit TableWidget           (StandardConstructor) ;
    virtual ~TableWidget           (void);

    virtual QSize sizeHint         (void) const ;

    virtual void setDesignable     (bool edit);

    TableWidgetItems horizontalHeaderItems (void) ;
    TableWidgetItems verticalHeaderItems   (void) ;
    TableWidgetItems allItems              (void) ;

  protected:

    QString InheritClass ;

    virtual void paintEvent        (QPaintEvent       * event) ;
    virtual void focusInEvent      (QFocusEvent       * event) ;
    virtual void focusOutEvent     (QFocusEvent       * event) ;

    virtual void contextMenuEvent  (QContextMenuEvent * event) ;
    virtual void resizeEvent       (QResizeEvent      * event) ;

    virtual void dragEnterEvent    (QDragEnterEvent   * event) ;
    virtual void dragLeaveEvent    (QDragLeaveEvent   * event) ;
    virtual void dragMoveEvent     (QDragMoveEvent    * event) ;
    virtual void dropEvent         (QDropEvent        * event) ;

    virtual void mousePressEvent   (QMouseEvent       * event) ;
    virtual void mouseMoveEvent    (QMouseEvent       * event) ;
    virtual void mouseReleaseEvent (QMouseEvent       * event) ;

    virtual void closeEvent        (QCloseEvent       * event) ;
    virtual bool event             (QEvent * event) ;

    virtual void Configure         (void) ;

    virtual void ThreadEvent       (void) ;

    virtual bool Bustle            (void) ;
    virtual bool Vacancy           (void) ;

  private:

  public slots:

    virtual bool Shutdown          (void) ;
    virtual bool Relocation        (void) ;
    virtual void assignColumns     (int columns) ;
    virtual void assignRows        (int rows) ;
    virtual void assignItem        (int row,int column,QTableWidgetItem * item) ;
    virtual void setFont           (void) ;
    virtual void setFont           (TableWidgetItems & items,Font & font  ) ;
    virtual void setFont           (TableWidgetItems & items,int    FontId) ;
    virtual void setFont           (QTableWidgetItem * item ,Font & font  ) ;
    virtual void setFont           (QTableWidgetItem * item ,int    FontId) ;
    virtual void CopyToClipboard   (void) ;
    virtual void SelectNone        (void) ;
    virtual void SelectAll         (void) ;

  protected slots:

    virtual bool Menu              (QPoint pos) ;
    virtual void DropCommands      (void) ;

    virtual void AtBusy            (void) ;
    virtual void OnRelax           (void) ;

    virtual void setWaitCursor     (void) ;
    virtual void setArrowCursor    (void) ;
    virtual void setEnabling       (bool enable) ;
    virtual void writeToolTip      (QString tooltip) ;
    virtual void writeTitle        (QString title) ;

    virtual void cleanItems        (void) ;
    virtual void changeColumns     (int columns) ;
    virtual void changeRows        (int rows) ;

  private slots:

  signals:

    void Adjustment                (nDeclWidget,QSize size) ;
    void Adjustment                (nDeclWidget) ;
    void Leave                     (nDeclWidget) ;
    void putItem                   (int row,int column,QTableWidgetItem * item) ;
    void ColumnsFit                (void) ;
    void RowsFit                   (void) ;
    void assignToolTip             (QString tooltip) ;
    void assignWindowTitle         (QString tooltip) ;
    void assignEnabling            (bool enable) ;
    void assignModified            (bool modified) ;
    void OnBusy                    (void) ;
    void GoRelax                   (void) ;
    void assignWaitCursor          (void) ;
    void assignArrowCursor         (void) ;
    void clearItems                (void) ;
    void emitColumns               (int columns) ;
    void emitRows                  (int rows) ;

} ;

class Q_COMPONENTS_EXPORT TreeView : public QTreeView
                                   , public VirtualGui
                                   , public Thread
{
  Q_OBJECT
  Q_PROPERTY(bool designable READ canDesign WRITE setDesignable DESIGNABLE true)
  public:

    explicit TreeView                 (StandardConstructor) ;
    virtual ~TreeView                 (void);

  protected:

    virtual void paintEvent           (QPaintEvent       * event) ;

    virtual void focusInEvent         (QFocusEvent       * event) ;
    virtual void focusOutEvent        (QFocusEvent       * event) ;

    virtual void contextMenuEvent     (QContextMenuEvent * event) ;
    virtual void resizeEvent          (QResizeEvent      * event) ;

    virtual void dragEnterEvent       (QDragEnterEvent   * event) ;
    virtual void dragLeaveEvent       (QDragLeaveEvent   * event) ;
    virtual void dragMoveEvent        (QDragMoveEvent    * event) ;
    virtual void dropEvent            (QDropEvent        * event) ;

    virtual void mousePressEvent      (QMouseEvent       * event) ;
    virtual void mouseMoveEvent       (QMouseEvent       * event) ;
    virtual void mouseReleaseEvent    (QMouseEvent       * event) ;

    virtual void closeEvent           (QCloseEvent       * event) ;
    virtual bool event                (QEvent * event) ;

    virtual void Configure            (void);

    virtual bool acceptDrop           (nDeclWidget,const QMimeData * mime);
    virtual bool dropNew              (nDeclWidget,const QMimeData * mime,QPoint pos);
    virtual bool dropMoving           (nDeclWidget,const QMimeData * mime,QPoint pos);
    virtual bool dropAppend           (nDeclWidget,const QMimeData * mime,QPoint pos);

    virtual bool dropFont             (nDeclWidget,QPointF pos,const SUID font ) ;
    virtual bool dropPen              (nDeclWidget,QPointF pos,const SUID pen  ) ;
    virtual bool dropBrush            (nDeclWidget,QPointF pos,const SUID brush) ;

    virtual void assignFont           (Font  & font ) ;
    virtual void assignPen            (Pen   & pen  ) ;
    virtual void assignBrush          (Brush & brush) ;

  private:

  public slots:

    virtual bool Shutdown             (void);
    virtual bool Relocation           (void);

    virtual void CopyToClipboard      (void) ;
    virtual void SelectNone           (void) ;
    virtual void SelectAll            (void) ;
    virtual void setFont              (void) ;

  protected slots:

    virtual bool Menu                 (QPoint pos);
    virtual void DropCommands         (void) ;

  private slots:

  signals:

    void Adjustment                   (nDeclWidget,QSize size) ;
    void Adjustment                   (nDeclWidget) ;
    void Leave                        (nDeclWidget) ;

} ;

class Q_COMPONENTS_EXPORT TreeWidget : public QTreeWidget
                                     , public VirtualGui
                                     , public Thread
{
  Q_OBJECT
  Q_PROPERTY(bool designable READ canDesign WRITE setDesignable DESIGNABLE true)
  public:

    explicit TreeWidget                (StandardConstructor) ;
    virtual ~TreeWidget                (void);

    virtual QStringList defaultHeader  (void) ;
    CUIDs               columnWidths   (void) ;
    virtual QSize       SuitableSize   (void) ;
    virtual QSize       sizeHint       (void) const ;

    void         SuitableColumns       (void) ;
    void         SuitableColumns       (int columns) ;

    virtual void reportItems           (void) ;
    virtual void installHeader         (void) ;

    virtual void setAlignment          (int position,int alignment) ;
    virtual void setAlignments         (QTreeWidgetItem * item) ;
    virtual void setAllAlignments      (QTreeWidgetItem * item,int alignment) ;
    virtual void setFont               (QTreeWidgetItem * item,Font & font) ;
    virtual void setFont               (QTreeWidgetItem * item,int FontId) ;

    virtual UUIDs selectedUuids        (int column) ;
    virtual UUIDs itemUuids            (int column) ;

    virtual void  setDesignable        (bool gui) ;

    virtual QString writeCpp           (void) ;
    virtual QString writeHpp           (void) ;
    virtual QString toHtml             (QTreeWidgetItem * item,bool accordingToAlignment = false) ;
    virtual QString toHtml             (bool accordingToAlignment = false) ;
    virtual QString toTeX              (QTreeWidgetItem * item,bool accordingToAlignment = false) ;
    virtual QString toTeX              (bool accordingToAlignment = false) ;
    virtual QString toText             (QTreeWidgetItem * item,bool accordingToAlignment = false) ;
    virtual QString toText             (bool accordingToAlignment = false) ;

    virtual QStringList columnStrings  (int column) ;

    virtual int  addItems              (int column,QStringList & lists) ;
    virtual void PrepareItem           (QTreeWidgetItem * item) ;

    QTreeWidgetItem * uuidAtItem       (SUID uuid,int column) ;
    SUID        atUuid                 (QPoint pos,int column = 0) ;

    bool holdItem                      (void) ;
    bool holdItems                     (void) ;
    void assignItems                   (QTreeWidgetItem * item,QStringList & S) ;

    virtual void setGui                (QWidget * widget) ;

  protected:

    QTreeWidgetItem * ItemEditing     ;
    QWidget         * ItemWidget      ;
    int               ItemColumn      ;
    IMAPs             Alignments      ;
    IMAPs             EditStyles      ;
    BMAPs             EditAttributes  ;
    QString           InheritClass    ;
    bool              dbClicked       ;
    bool              Commanding      ;
    QTimer          * CommandSequence ;

    virtual void paintEvent            (QPaintEvent       * event) ;

    virtual void focusInEvent          (QFocusEvent       * event) ;
    virtual void focusOutEvent         (QFocusEvent       * event) ;

    virtual void contextMenuEvent      (QContextMenuEvent * event) ;
    virtual void resizeEvent           (QResizeEvent      * event) ;

    virtual void dragEnterEvent        (QDragEnterEvent   * event) ;
    virtual void dragLeaveEvent        (QDragLeaveEvent   * event) ;
    virtual void dragMoveEvent         (QDragMoveEvent    * event) ;
    virtual void dropEvent             (QDropEvent        * event) ;

    virtual void mousePressEvent       (QMouseEvent       * event) ;
    virtual void mouseMoveEvent        (QMouseEvent       * event) ;
    virtual void mouseReleaseEvent     (QMouseEvent       * event) ;
    virtual void mouseDoubleClickEvent (QMouseEvent       * event) ;

    virtual void keyPressEvent         (QKeyEvent * event) ;
    virtual void keyReleaseEvent       (QKeyEvent * event) ;

    virtual void closeEvent            (QCloseEvent       * event) ;
    virtual bool event                 (QEvent * event) ;

    virtual void Configure             (void);

    virtual bool acceptDrop            (nDeclWidget,const QMimeData * mime);
    virtual bool dropNew               (nDeclWidget,const QMimeData * mime,QPoint pos);
    virtual bool dropMoving            (nDeclWidget,const QMimeData * mime,QPoint pos);
    virtual bool dropAppend            (nDeclWidget,const QMimeData * mime,QPoint pos);

    QLineEdit      * setLineEdit       (QTreeWidgetItem * item     ,
                                        int               column   ,
                                        const char      * Signal   ,
                                        const char      * method ) ;
    QComboBox      * setComboBox       (QTreeWidgetItem * item     ,
                                        int               column   ,
                                        const char      * Signal   ,
                                        const char      * method ) ;
    QSpinBox       * setSpinBox        (QTreeWidgetItem * item     ,
                                        int               column   ,
                                        int               Min      ,
                                        int               Max      ,
                                        const char      * Signal   ,
                                        const char      * method ) ;
    QDoubleSpinBox * setDoubleSpin     (QTreeWidgetItem * item     ,
                                        int               column   ,
                                        double            Min      ,
                                        double            Max      ,
                                        const char      * Signal   ,
                                        const char      * method ) ;

    QMimeData * standardMime           (QString objectName) ;

    virtual bool dropFont              (nDeclWidget,QPointF pos,const SUID font ) ;
    virtual bool dropPen               (nDeclWidget,QPointF pos,const SUID pen  ) ;
    virtual bool dropBrush             (nDeclWidget,QPointF pos,const SUID brush) ;

    virtual void assignFont            (Font  & font ) ;
    virtual void assignPen             (Pen   & pen  ) ;
    virtual void assignBrush           (Brush & brush) ;

    QLineEdit *  headerEditor          (const char * emitter = NULL,const char * method = NULL) ;

    virtual bool acceptTapHold         (QTapAndHoldGesture * gesture) ;
    virtual bool acceptPan             (QPanGesture        * gesture) ;

    virtual void NewItem               (int column) ;
    virtual void RenameItem            (int column) ;

    virtual void ThreadEvent           (void) ;

    virtual bool Bustle                (void) ;
    virtual bool Vacancy               (void) ;

    virtual void DropInObjects         (ThreadData * data) ;

  private:

  public slots:

    virtual bool startup               (void) ;
    virtual void pendingStartup        (void) ;
    virtual bool Shutdown              (void) ;
    virtual bool Relocation            (void) ;
    void         setColumnWidths       (CUIDs & widths) ;
    bool         takeItem              (QTreeWidgetItem * item) ;
    void         setAllExpanded        (bool expand) ;
    void         MountClicked          (int clicks) ;
    virtual void WaitClear             (void) ;

    virtual void CopyToClipboard       (void) ;
    virtual void CopyIt                (void) ;
    virtual void SelectNone            (void) ;
    virtual void SelectAll             (void) ;
    virtual void setFont               (void) ;
    virtual void Language              (void) ;

    virtual void ExportToCpp           (void) ;

    virtual void HeaderMenu            (QHeaderView * view,QPoint pos) ;
    virtual void assignHeaderItems     (QTreeWidgetItem * head) ;
    virtual void assignHeaderItems     (QStringList headers) ;

    virtual void Execute               (int command) ;
    virtual bool RunCommand            (VarArgs & arguments) ;

    virtual void PageHome              (void) ;
    virtual void PageEnd               (void) ;
    virtual void PageUp                (void) ;
    virtual void PageDown              (void) ;

    virtual bool PageChanged           (int StartId,int PageSize) ;

    virtual QMenu * PageMenu           (MenuManager & menu       ,
                                        QString       total      ,
                                        int         & StartId    ,
                                        int         & PageSize ) ;

  protected slots:

    virtual void SortingMenu           (MenuManager & Menu,QMenu   * SortMenu  ) ;
    virtual bool RunSorting            (MenuManager & Menu,QAction * action    ) ;
    virtual void AdjustMenu            (MenuManager & Menu,QMenu   * EditMenu  ) ;
    virtual bool RunAdjustment         (MenuManager & Menu,QAction * action    ) ;
    virtual void SelectionsMenu        (MenuManager & Menu,QMenu   * SelectMenu) ;
    virtual bool RunSelections         (MenuManager & Menu,QAction * action    ) ;
    virtual bool RunPageMenu           (MenuManager & menu       ,
                                        QAction     * action     ,
                                        int         & StartId    ,
                                        int         & PageSize ) ;
    virtual bool AppMenu               (void) ;
    virtual bool Menu                  (QPoint pos);
    virtual void selectLanguage        (nDeclWidget,QTreeWidgetItem * item,int column,const char * method) ;
    virtual void singleClicked         (QTreeWidgetItem * item,int column) ;
    virtual void doubleClicked         (QTreeWidgetItem * item,int column) ;
    virtual void stateChanged          (QTreeWidgetItem * item,int column) ;
    virtual void removeOldItem         (bool checkUuid = false,int column = 0) ;
    virtual void DropCommands          (void) ;

    virtual void AtBusy                (void) ;
    virtual void OnRelax               (void) ;

    virtual void setWaitCursor         (void) ;
    virtual void setArrowCursor        (void) ;
    virtual void setEnabling           (bool enable) ;
    virtual void writeSortingEnabled   (bool enable) ;
    virtual void writeToolTip          (QString tooltip) ;
    virtual void writeTitle            (QString title) ;

    virtual void cleanItems            (void) ;

    virtual void StartCommand          (void) ;
    virtual void CommandHandler        (void) ;

  private slots:

    virtual void AutoResize            (void) ;

  signals:

    void AdjustColumns                 (void) ;
    void Adjustment                    (nDeclWidget,QSize size) ;
    void Adjustment                    (nDeclWidget) ;
    void Leave                         (nDeclWidget) ;
    void assignToolTip                 (QString tooltip) ;
    void assignWindowTitle             (QString tooltip) ;
    void Follow                        (int command) ;
    void assignEnabling                (bool enable) ;
    void assignSortingEnabled          (bool enable) ;
    void assignModified                (bool modified) ;
    void AutoFit                       (void) ;
    void OnBusy                        (void) ;
    void GoRelax                       (void) ;
    void assignWaitCursor              (void) ;
    void assignArrowCursor             (void) ;
    void clearItems                    (void) ;
    void TriggerCommand                (void) ;

} ;

class Q_COMPONENTS_EXPORT ListView : public QListView
                                   , public VirtualGui
                                   , public Thread
{
  Q_OBJECT
  Q_PROPERTY(bool designable READ canDesign WRITE setDesignable DESIGNABLE true)
  public:

    explicit ListView               (StandardConstructor) ;
    virtual ~ListView               (void);

  protected:

    virtual void paintEvent         (QPaintEvent       * event) ;

    virtual void focusInEvent       (QFocusEvent       * event) ;
    virtual void focusOutEvent      (QFocusEvent       * event) ;

    virtual void contextMenuEvent   (QContextMenuEvent * event) ;
    virtual void resizeEvent        (QResizeEvent      * event) ;

    virtual void dragEnterEvent     (QDragEnterEvent   * event) ;
    virtual void dragLeaveEvent     (QDragLeaveEvent   * event) ;
    virtual void dragMoveEvent      (QDragMoveEvent    * event) ;
    virtual void dropEvent          (QDropEvent        * event) ;

    virtual void mousePressEvent    (QMouseEvent       * event) ;
    virtual void mouseMoveEvent     (QMouseEvent       * event) ;
    virtual void mouseReleaseEvent  (QMouseEvent       * event) ;

    virtual void closeEvent         (QCloseEvent       * event) ;
    virtual bool event              (QEvent * event) ;

    virtual void Configure          (void);

    virtual bool acceptDrop         (nDeclWidget,const QMimeData * mime);
    virtual bool dropNew            (nDeclWidget,const QMimeData * mime,QPoint pos);
    virtual bool dropMoving         (nDeclWidget,const QMimeData * mime,QPoint pos);
    virtual bool dropAppend         (nDeclWidget,const QMimeData * mime,QPoint pos);

    virtual bool dropFont           (nDeclWidget,QPointF pos,const SUID font ) ;
    virtual bool dropPen            (nDeclWidget,QPointF pos,const SUID pen  ) ;
    virtual bool dropBrush          (nDeclWidget,QPointF pos,const SUID brush) ;

    virtual void assignFont         (Font  & font ) ;
    virtual void assignPen          (Pen   & pen  ) ;
    virtual void assignBrush        (Brush & brush) ;

  private:

  public slots:

    virtual bool Shutdown           (void) ;
    virtual bool Relocation         (void) ;

    virtual void CopyToClipboard    (void) ;
    virtual void SelectNone         (void) ;
    virtual void SelectAll          (void) ;
    virtual void setFont            (void) ;

  protected slots:

    virtual bool Menu               (QPoint pos);
    virtual void DropCommands       (void) ;

  private slots:

  signals:

    void Adjustment                 (nDeclWidget,QSize size) ;
    void Adjustment                 (nDeclWidget) ;
    void Leave                      (nDeclWidget) ;
    void Command                    (SUID uuid);
    void Selected                   (SUID uuid);
    void ItemMenu                   (nDeclWidget,QPoint pos);
    void Command                    (nDeclWidget,QString name,SUID uuid);

} ;

class Q_COMPONENTS_EXPORT ListWidget : public QListWidget
                                     , public VirtualGui
                                     , public Thread
{
  Q_OBJECT
  Q_PROPERTY(bool designable READ canDesign WRITE setDesignable DESIGNABLE true)
  public:

    explicit ListWidget              (StandardConstructor) ;
    virtual ~ListWidget              (void);

    virtual QSize   sizeHint         (void) const ;
    QIcon           EmptyIcon        (QSize size) ;
    int             Page             (void) ;
    UUIDs           Selected         (void) ;
    UUIDs           ItemUuids        (void) ;

    virtual void    setDesignable    (bool gui) ;

    virtual QString writeCpp         (void) ;
    virtual QString writeHpp         (void) ;

  protected:

    QListWidgetItem         * ItemEditing    ;
    QWidget                 * ItemWidget     ;
    BMAPs                     EditAttributes ;
    QString                   InheritClass   ;
    UUIDs                     PickedUuids    ;
    QMap<int,ListWidgetItems> ItemMaps       ;
    QMap<int,UUIDs          > UuidMaps       ;

    virtual void paintEvent          (QPaintEvent       * event) ;

    virtual void focusInEvent        (QFocusEvent       * event) ;
    virtual void focusOutEvent       (QFocusEvent       * event) ;

    virtual void contextMenuEvent    (QContextMenuEvent * event) ;
    virtual void resizeEvent         (QResizeEvent      * event) ;
    virtual void showEvent           (QShowEvent        * event) ;

    virtual void dragEnterEvent      (QDragEnterEvent   * event) ;
    virtual void dragLeaveEvent      (QDragLeaveEvent   * event) ;
    virtual void dragMoveEvent       (QDragMoveEvent    * event) ;
    virtual void dropEvent           (QDropEvent        * event) ;
    virtual void dragDone            (Qt::DropAction dropIt,QMimeData * mime) ;

    virtual void mousePressEvent     (QMouseEvent       * event) ;
    virtual void mouseMoveEvent      (QMouseEvent       * event) ;
    virtual void mouseReleaseEvent   (QMouseEvent       * event) ;

    virtual void closeEvent          (QCloseEvent       * event) ;
    virtual bool event               (QEvent * event) ;

    virtual void Configure           (void);

    SUID         ItemUuid            (QListWidgetItem * it) ;

    virtual bool acceptDrop          (nDeclWidget,const QMimeData * mime);
    virtual bool dropNew             (nDeclWidget,const QMimeData * mime,QPoint pos);
    virtual bool dropMoving          (nDeclWidget,const QMimeData * mime,QPoint pos);
    virtual bool dropAppend          (nDeclWidget,const QMimeData * mime,QPoint pos);

    virtual bool dropFont            (nDeclWidget,QPointF pos,const SUID font ) ;
    virtual bool dropPen             (nDeclWidget,QPointF pos,const SUID pen  ) ;
    virtual bool dropBrush           (nDeclWidget,QPointF pos,const SUID brush) ;

    virtual void assignFont          (Font  & font ) ;
    virtual void assignPen           (Pen   & pen  ) ;
    virtual void assignBrush         (Brush & brush) ;

    virtual void reportItems         (void) ;

    virtual void AdjustMenu          (MenuManager & Menu,QMenu   * adjustment) ;
    virtual bool RunAdjustment       (MenuManager & Menu,QAction * action    ) ;
    virtual void SelectionsMenu      (MenuManager & Menu,QMenu   * SelectMenu) ;
    virtual bool RunSelections       (MenuManager & Menu,QAction * action    ) ;

    virtual bool acceptTapHold       (QTapAndHoldGesture * gesture) ;

    virtual ListWidgetItems New      (UUIDs & Uuids) ;
    virtual bool MoveUuids           (SqlConnection & Connection       ,
                                      Group         & group            ,
                                      UUIDs         & Uuids            ,
                                      RMAPs         & Positions        ,
                                      QString         format = ""      ,
                                      bool            gui    = false ) ;
    virtual bool setUuidsName        (SqlConnection & Connection,int from,int to) ;
    virtual bool setUuidsName        (SqlConnection & Connection) ;
    virtual bool setUuidsNames       (SqlConnection & Connection,int from,int to) ;
    virtual bool setUuidsNames       (SqlConnection & Connection) ;

    virtual void ThreadEvent         (void) ;

    virtual bool Bustle              (void) ;
    virtual bool Vacancy             (void) ;

    virtual void DropInObjects       (ThreadData * data) ;

  private:

  public slots:

    QListWidgetItem * addItem        (SUID Uuid,QString Description,QIcon Icon) ;
    QListWidgetItem * addItem        (SUID Uuid,QIcon Icon,QString text,QString tooltip) ;
    virtual void appendItems         (ListWidgetItems & items) ;

    virtual void MountCommands       (void) ;
    virtual void WaitClear           (void) ;

    virtual bool startup             (void) ;
    virtual bool Shutdown            (void) ;
    virtual bool Relocation          (void) ;

    virtual void CopyToClipboard     (void) ;
    virtual void SelectNone          (void) ;
    virtual void SelectAll           (void) ;
    virtual void setFont             (void) ;
    virtual void Language            (void) ;
    virtual void ModifySpacing       (void) ;
    virtual void AssignGridSize      (void) ;

    virtual void setSelections       (UUIDs & Uuids) ;
    virtual void setSelections       (ListWidgetItems & Items) ;

    virtual void ExportToCpp         (void) ;

    virtual void MoveTo              (QListWidgetItem * at,ListWidgetItems & Items) ;

    virtual void Execute             (int command) ;

    virtual void PageHome            (void) ;
    virtual void PageEnd             (void) ;
    virtual void PageUp              (void) ;
    virtual void PageDown            (void) ;

    virtual bool PageChanged         (int StartId,int PageSize) ;

    virtual QMenu * PageMenu         (MenuManager & menu       ,
                                      QString       total      ,
                                      int         & StartId    ,
                                      int         & PageSize ) ;

  protected slots:

    virtual bool AppMenu             (void) ;
    virtual bool Menu                (QPoint pos);
    virtual void singleClicked       (QListWidgetItem * item) ;
    virtual void doubleClicked       (QListWidgetItem * item) ;
    virtual void DropCommands        (void) ;

    virtual void AtBusy              (void) ;
    virtual void OnRelax             (void) ;

    virtual void setWaitCursor       (void) ;
    virtual void setArrowCursor      (void) ;
    virtual void setEnabling         (bool enable) ;
    virtual void writeSortingEnabled (bool enable) ;
    virtual void writeToolTip        (QString tooltip) ;
    virtual void writeTitle          (QString title) ;
    virtual void cleanItems          (void) ;

    virtual bool RunPageMenu         (MenuManager & menu       ,
                                      QAction     * action     ,
                                      int         & StartId    ,
                                      int         & PageSize ) ;

    virtual void removeListItem      (QListWidgetItem * item) ;

  private slots:

  signals:

    void Adjustment                  (nDeclWidget,QSize size) ;
    void Adjustment                  (nDeclWidget) ;
    void Leave                       (nDeclWidget) ;
    void Command                     (SUID uuid);
    void Selected                    (SUID uuid);
    void assignSelections            (UUIDs & Uuids) ;
    void assignSelections            (ListWidgetItems & Items) ;
    void takeListItem                (QListWidgetItem * item) ;
    void ItemMenu                    (nDeclWidget,QPoint pos);
    void Command                     (nDeclWidget,QString name,SUID uuid);
    void assignToolTip               (QString tooltip) ;
    void assignWindowTitle           (QString tooltip) ;
    void Follow                      (int command) ;
    void assignEnabling              (bool enable) ;
    void assignSortingEnabled        (bool enable) ;
    void assignModified              (bool modified) ;
    void OnBusy                      (void) ;
    void GoRelax                     (void) ;
    void assignWaitCursor            (void) ;
    void assignArrowCursor           (void) ;
    void clearItems                  (void) ;

} ;

class Q_COMPONENTS_EXPORT PaintWidget : public Widget
{
  Q_OBJECT
  public:

    QImage Painting   ;
    QImage Background ;
    QImage Drawing    ;

    explicit PaintWidget     (StandardConstructor) ;
    virtual ~PaintWidget     (void) ;

  protected:

    virtual void Configure   (void) ;

    virtual void showEvent   (QShowEvent   * event) ;
    virtual void resizeEvent (QResizeEvent * event) ;
    virtual void paintEvent  (QPaintEvent  * event) ;

  private:

  public slots:

    virtual void relocation  (void) ;
    virtual void LockImage   (void) ;
    virtual void UnlockImage (void) ;

  protected slots:

  private slots:

  signals:

    void reflush             (void) ;

} ;

class Q_COMPONENTS_EXPORT PaperArrangement : public Dialog
{
  Q_OBJECT
  public:

    QString paper     ;
    DMAPs   borders   ;
    int     paperX    ;
    int     paperY    ;
    int     dpi       ;
    int     direction ; // Paper direction
    int     arrange   ; // Qt::Vertical -> Vertical first , Qt::Horizontal , horizontal first (default)
    bool    rulers    ;

    explicit PaperArrangement (QWidget * parent = NULL,Plan * plan = NULL) ;
    virtual ~PaperArrangement (void);

  protected:

  private:

  public slots:

    virtual bool prepare      (void) = 0;
    virtual bool store        (void) = 0;
    virtual bool retrieve     (void) = 0;

  protected slots:

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT GraphicsView : public QGraphicsView
                                       , public VirtualGui
                                       , public VcfDisplay
                                       , public VcfManager
                                       , public VcfPaperManager
                                       , public Thread
{
  Q_OBJECT
  Q_PROPERTY(bool designable READ canDesign WRITE setDesignable DESIGNABLE true)
  public:

    typedef enum        {
      PerfectRegion = 0 ,
      UnitedRegion  = 1 ,
      PaperRegion   = 2 }
      ResizeViewMode    ;

    int  mode   ;
    int  method ;
    SUID group  ;
    SUID uuid   ;

    explicit     GraphicsView       (StandardConstructor) ;
    virtual     ~GraphicsView       (void);

    void         setRelocation      (ResizeViewMode mode) ;
    void         setScrollBarPolicy (enum Qt::ScrollBarPolicy policy) ;

  protected:

    ResizeViewMode RelocationMode  ;
    VcfPainter     DefaultPainters ;

    virtual bool event              (QEvent      * event) ;
    virtual void closeEvent         (QCloseEvent * event) ;

  private:

  public slots:

    virtual bool Shutdown           (void) ;

  protected slots:

    virtual void ConnectScrolls     (void) ;
    virtual void ScrollMoved        (int) ;

    void         connectItem        (VcfItem * item) ;
    void         Remove             (VcfItem * item) ;
    void         Append             (VcfItem * item,VcfItem * parent) ;

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT FlipRoundRect : public QObject
                                        , public QGraphicsRectItem
{
  Q_OBJECT
  public:

    explicit FlipRoundRect  ( const QRectF & rect                 ,
                              const QBrush & brush                ,
                              QWidget      * embeddedWidget = 0 ) ;
    virtual ~FlipRoundRect  ( void ) ;

    QRectF   boundingRect   ( void ) const;

    void     setPixmap      ( const QPixmap & pixmap );
    qreal    opacity        ( void ) const;
    void     setOpacity     ( qreal opacity );
    void     setBorderWidth ( qreal width );
    void     setRoundBorder ( bool round );
    void     setBorderBrush ( const QBrush& brush );

  protected:

    void paint ( QPainter * , const QStyleOptionGraphicsItem * , QWidget * ) ;

  private:

    QBrush                 m_brush       ;
    QPixmap                m_pixmap      ;
    qreal                  m_opacity     ;
    qreal                  m_borderWidth ;
    bool                   m_roundBorder ;
    QGraphicsProxyWidget * m_proxyWidget ;

} ;

class Q_COMPONENTS_EXPORT FlipWidget : public GraphicsView
{
  Q_OBJECT
  public:

    typedef enum     {
      FRONT = 0      ,
      BACK  = 1      }
      WIDGET_SIDE    ;

    typedef enum     {
      NORMAL    = 0  , /* The widget appears to rotate in 3D space, moving away and then back towards the screen. */
      TURNSTILE = 1  , /* The widget rotates as if connected to a turning vertical or horizontal bar. */
      FLYAWAY   = 2  } /* The widget disappears some distance into the monitor before zooming back. Use SetFlyAwayDistance to control the distance. */
      ANIMATIONS     ;

    typedef enum     {
      HORIZONTAL = 0 ,
      VERTICAL   = 1 }
      FLIP_DIRECTION ;

    explicit FlipWidget ( QRectF    bounds             ,
                          QWidget * frontWidget        ,
                          QWidget * backWidget         ,
                          bool      useOpenGL = false  ,
                          QWidget * parent    = NULL   ,
                          Plan    * plan      = NULL ) ;
    virtual ~FlipWidget ( void ) ;

    void           SetFlipDirection   (FLIP_DIRECTION direction) ;
    FLIP_DIRECTION GetFlipDirection   (void) ;
    void           SetFlipAnimation   (ANIMATIONS type) ;
    ANIMATIONS     GetFlipAnimation   (void) ;
    void           SetFlyAwayDistance (int distance) ;
    int            GetFlyAwayDistance (void) ;
    void           SetFlipDuration    (int duration) ;
    int            GetFlipDuration    (void) ;
    void           SetBorder          (WIDGET_SIDE side                       ,
                                       bool        useBorder                  ,
                                       int         borderSize     = 0         ,
                                       bool        roundedCorners = false     ,
                                       QBrush      borderBrush    = QBrush()) ;
    void           SetBorderPixmap    (WIDGET_SIDE     side     ,
                                       const QPixmap & pixmap ) ;
    bool           isFlipped          (void) ;
    bool           isFlippedLeft      (void) ;
    bool           isOpenGL           (void) ;

  protected:

    void resizeEvent ( QResizeEvent * event ) ;

  private:

    QRectF           m_bounds             ;
    FlipRoundRect  * m_frontItem          ;
    FlipRoundRect  * m_backItem           ;
    QWidget        * m_frontWidget        ;
    QWidget        * m_backWidget         ;
    QGraphicsScene * m_scene              ;
    QTimeLine      * m_flipTimeLine       ;
    ANIMATIONS       m_animatedStyle      ;
    FLIP_DIRECTION   m_flipDirection      ;
    int              m_flyAwayDistance    ;
    qreal            m_xrot               ;
    qreal            m_yrot               ;
    bool             m_flipped            ;
    bool             m_flipLeft           ;
    bool             m_useOpenGL          ;
    int              m_frontBorderSize    ;
    int              m_backBorderSize     ;
    bool             m_frontRoundedBorder ;
    bool             m_backRoundedBorder  ;
    QBrush           m_frontBorderBrush   ;
    QBrush           m_backBorderBrush    ;

  public slots:

    void Flip           ( bool flipLeft = true ) ;

  protected slots:

  private slots:

    void updateFlipStep ( qreal val ) ;

} ;

class Q_COMPONENTS_EXPORT PictureFlow : public Widget
{
  Q_OBJECT
  Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
  Q_PROPERTY(QSize  slideSize       READ slideSize       WRITE setSlideSize)
  Q_PROPERTY(int    slideCount      READ slideCount)
  Q_PROPERTY(int    centerIndex     READ centerIndex     WRITE setCenterIndex)
  public:

    enum ReflectionEffect     {
      NoReflection      = 0   ,
      PlainReflection   = 1   ,
      BlurredReflection = 2 } ;

    explicit         PictureFlow         (StandardConstructor) ;
    virtual         ~PictureFlow         (void) ;

    QColor           backgroundColor     (void) const ;
    void             setBackgroundColor  (const QColor & c) ;
    QSize            slideSize           (void) const ;
    void             setSlideSize        (QSize size) ;
    int              slideCount          (void) const ;
    QImage           slide               (int index) const ;
    int              centerIndex         (void) const ;
    ReflectionEffect reflectionEffect    (void) const ;
    void             setReflectionEffect (ReflectionEffect effect) ;
    virtual QSize    sizeHint            (void) const ;

  protected:

    virtual void paintEvent              (QPaintEvent  * event) ;
    virtual void keyPressEvent           (QKeyEvent    * event) ;
    virtual void mousePressEvent         (QMouseEvent  * event) ;
    virtual void resizeEvent             (QResizeEvent * event) ;

  private:

    void * D ;

  public slots:

    void addSlide                        (const QImage  & image ) ;
    void addSlide                        (const QPixmap & pixmap) ;
    void setSlide                        (int index,const QImage  & image ) ;
    void setSlide                        (int index,const QPixmap & pixmap) ;
    void setCenterIndex                  (int index) ;
    void clear                           (void) ;
    void showPrevious                    (void) ;
    void showNext                        (void) ;
    void showSlide                       (int index) ;
    void render                          (void) ;
    void triggerRender                   (void) ;

  private slots:

    void updateAnimation                 (void) ;

  signals:

    void centerIndexChanged              (int index) ;

} ;

class Q_COMPONENTS_EXPORT RowTable : public TableWidget
                                   , public Group
{
  Q_OBJECT
  public:

    explicit      RowTable              (StandardConstructor) ;
    virtual      ~RowTable              (void) ;

    virtual QSize sizeHint              (void) const ;

    void          SuitableColumns       (void) ;
    void          SuitableColumns       (int columns) ;

  protected:

    bool                       Commanding      ;
    QTimer                   * CommandSequence ;
    QPoint                     dragPoint       ;
    TableWidgetItems           Items           ;
    QString                    MasterTable     ;
    NAMEs                      AlterTables     ;
    QMap<int,TableWidgetItems> ItemMaps        ;
    QMap<int,UUIDs           > UuidMaps        ;
    LineEdit                *  HeaderName      ;
    int                        ItemRow         ;
    int                        ItemColumn      ;
    QTableWidgetItem        *  ItemEditing     ;
    QWidget                 *  ItemWidget      ;

    virtual void        Configure       (void) ;

    virtual bool        hasItem         (void) ;
    virtual bool        startDrag       (QMouseEvent * event) ;
    virtual bool        fetchDrag       (QMouseEvent * event) ;
    virtual void        dragDone        (Qt::DropAction dropIt,QMimeData * mime) ;
    virtual bool        finishDrag      (QMouseEvent * event) ;

    virtual bool        acceptDrop      (QWidget * source,const QMimeData * mime) ;
    virtual bool        dropNew         (QWidget * source,const QMimeData * mime,QPoint pos) ;
    virtual bool        dropMoving      (QWidget * source,const QMimeData * mime,QPoint pos) ;
    virtual bool        dropAppend      (QWidget * source,const QMimeData * mime,QPoint pos) ;
    virtual bool        removeDrop      (void) ;

    virtual void        run             (int Type,ThreadData * data) ;
    virtual void        ThreadEvent     (void) ;

    virtual bool        isOwner         (void) ;

    virtual bool        LoadUuids       (SqlConnection & Connection,UUIDs & Uuids) ;
    virtual bool        LoadCells       (SqlConnection & Connection,int row,SUID uuid) ;
    virtual bool        LoadCell        (SqlConnection & Connection,int row,int column,SUID uuid) ;
    virtual bool        LoadName        (SqlConnection & Connection,int row,int column,SUID uuid) ;
    virtual bool        LoadNames       (SqlConnection & Connection,int row,int column,SUID uuid) ;
    virtual bool        LoadColumn      (SqlConnection & Connection,int column,UUIDs & Uuids) ;
    virtual bool        LoadItems       (SqlConnection & Connection,UUIDs & Uuids) ;

    virtual bool        PageChanged     (int StartId,int PageSize) ;
    virtual QMenu *     PageMenu        (MenuManager & menu       ,
                                         QString       total      ,
                                         int         & StartId    ,
                                         int         & PageSize ) ;

  private:

  public slots:

    virtual void        setTable        (QString table) ;
    virtual void        FolderLanguage  (void) ;
    virtual void        ResumeLanguage  (void) ;
    virtual bool        startup         (void) ;
    virtual void        List            (void) ;
    virtual void        Paste           (void) ;
    virtual void        Paste           (int row,QString text) ;
    virtual void        Paste           (int row,int column,QString text) ;

    virtual void        ExportHtml      (void) ;
    virtual void        ExportTeX       (void) ;
    virtual void        Export          (void) ;
    virtual void        Copy            (void) ;

    virtual void        Original        (void) ;
    virtual void        ZoomIn          (void) ;
    virtual void        ZoomOut         (void) ;

    virtual void        setSelections   (UUIDs & Uuids) ;

    virtual void        showMessage     (QString message) ;
    virtual void        assignWidget    (int row,int column,QWidget * widget) ;

    virtual void        Execute         (int command) ;
    virtual bool        RunCommand      (VarArgs & arguments) ;

  protected slots:

    virtual void        StartCommand    (void) ;
    virtual void        CommandHandler  (void) ;

    virtual void        AtBusy          (void) ;
    virtual void        OnRelax         (void) ;

    virtual void        assignMessage   (QString message) ;

    virtual void        SortingMenu     (MenuManager & Menu,QMenu   * SortMenu  ) ;
    virtual bool        RunSorting      (MenuManager & Menu,QAction * action    ) ;
    virtual void        AdjustMenu      (MenuManager & Menu,QMenu   * EditMenu  ) ;
    virtual bool        RunAdjustment   (MenuManager & Menu,QAction * action    ) ;
    virtual void        SelectionsMenu  (MenuManager & Menu,QMenu   * SelectMenu) ;
    virtual bool        RunSelections   (MenuManager & Menu,QAction * action    ) ;
    virtual bool        RunPageMenu     (MenuManager & menu       ,
                                         QAction     * action     ,
                                         int         & StartId    ,
                                         int         & PageSize ) ;

  private slots:

    void                AutoResize      (void) ;

  signals:

    void                AutoFit         (void) ;
    void                OnBusy          (void) ;
    void                GoRelax         (void) ;
    void                TriggerCommand  (void) ;
    void                Follow          (int command) ;
    void                setMessage      (QString message) ;
    void                putWidget       (int row,int column,QWidget * widget) ;

} ;

#ifdef QT_OPENGL_LIB

class Q_COMPONENTS_EXPORT GLWidget : public QGLWidget
                                   , public VirtualGui
                                   , public Thread
{
  Q_OBJECT
  Q_PROPERTY(bool designable READ canDesign WRITE setDesignable DESIGNABLE true)
  public:

    explicit GLWidget (const QGLFormat & format,QWidget * widget,Plan * plan) ;
    virtual ~GLWidget (void                ) ;

  protected:

    virtual bool event         (QEvent * event) ;

  private:

  public slots:

  protected slots:

     virtual void DropCommands (void) ;

  private slots:

  signals:

} ;

#endif

/*****************************************************************************
 *                                                                           *
 *                         Traditional GUI enhancements                      *
 *                                                                           *
 *****************************************************************************/

class Q_COMPONENTS_EXPORT TreeDock : public TreeWidget
                                   , public AttachDock
{
  Q_OBJECT
  public:

    int                 dockingOrientation ;
    Qt::DockWidgetArea  dockingPlace       ;
    Qt::DockWidgetAreas dockingPlaces      ;

    explicit TreeDock    (StandardConstructor) ;
    virtual ~TreeDock    (void);

  protected:

  private:

  public slots:

    virtual void Docking (QMainWindow * Main,QString title,Qt::DockWidgetArea area,Qt::DockWidgetAreas areas);
    virtual void DockIn  (bool shown);

    virtual QTreeWidgetItem * addItem (QString text,SUID uuid,int column = 0);
    virtual QTreeWidgetItem * addItem (QIcon icon,QString text,SUID uuid,int column = 0);

  protected slots:

    virtual void DockingMenu          (MenuManager & Menu) ;
    virtual bool RunDocking           (MenuManager & Menu,QAction * action) ;
    void         Visible              (bool visible);
    void         doubleClicked        (QTreeWidgetItem * item,int column);

  private slots:

  signals:

    DockSignals ;

    void Clicked         (SUID uuid);

} ;

class Q_COMPONENTS_EXPORT ListDock : public ListWidget
                                   , public AttachDock
{
  Q_OBJECT
  public:

    int                 dockingOrientation ;
    Qt::DockWidgetArea  dockingPlace       ;
    Qt::DockWidgetAreas dockingPlaces      ;

    explicit ListDock        (StandardConstructor) ;
    virtual ~ListDock        (void);

  protected:

  private:

  public slots:

    virtual void Docking     (QMainWindow *       Main    ,
                              QString             title   ,
                              Qt::DockWidgetArea  area    ,
                              Qt::DockWidgetAreas areas ) ;
    virtual void DockIn      (bool shown);

  protected slots:

    virtual void DockingMenu (MenuManager & Menu) ;
    virtual bool RunDocking  (MenuManager & Menu,QAction * action) ;
    void Visible             (bool visible);

  private slots:

  signals:

    DockSignals ;

} ;

class Q_COMPONENTS_EXPORT IconDock : public ListDock
{
  Q_OBJECT
  public:

    explicit IconDock      (StandardConstructor) ;
    virtual ~IconDock      (void);

  protected:

    virtual void Configure (void);

  private:

  public slots:

    virtual bool startup   (void);

  protected slots:

    virtual bool Menu      (QPoint pos) ;

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT ScrollDock : public ScrollArea
                                     , public AttachDock
{
  Q_OBJECT
  public:

    explicit ScrollDock  (StandardConstructor) ;
    virtual ~ScrollDock  (void) ;

    virtual QSize sizeHint (void) const ;

  protected:

  private:

  public slots:

    virtual void Docking (QMainWindow * Main,QString title,Qt::DockWidgetArea area,Qt::DockWidgetAreas areas);
    virtual void DockIn  (bool shown);

  protected slots:

    void Visible         (bool visible);

  private slots:

  signals:

    DockSignals ;

} ;

class Q_COMPONENTS_EXPORT PanWidget : public Splitter
{
  Q_OBJECT
  Q_PROPERTY(int Hidden READ isHidden WRITE setHidden)
  public:

    explicit PanWidget      (StandardConstructor) ;
    virtual ~PanWidget      (void) ;

    int       addWidget     (QWidget * widget) ;
    int       count         (void) const ;
    int       currentIndex  (void) const ;
    QWidget * currentWidget (void) const ;
    int       indexOf       (QWidget * widget) const ;
    int       insertWidget  (int index,QWidget * widget) ;
    void      removeWidget  (QWidget * widget) ;
    QWidget * widget        (int index) const ;

    bool      isHidden      (void) ;
    void      setHidden     (bool enable) ;

  protected:

    StackedWidget * Stack  ;
    QToolButton   * Left   ;
    QToolButton   * Right  ;
    bool            Hidden ;

    virtual void Configure  (void) ;
    virtual bool FocusIn    (void) ;

  private:

  public slots:

    void setHandleSize      (int width) ;
    void setCurrentIndex    (int index) ;
    void setCurrentWidget   (QWidget * widget) ;

    void CheckIndex         (void) ;

    void Previous           (void) ;
    void Next               (void) ;

  protected slots:

  private slots:

  signals:

    void currentChanged     (int index) ;
    void widgetRemoved      (int index) ;

} ;

class Q_COMPONENTS_EXPORT ControlPad : public Splitter
                                     , public AttachDock
{
  Q_OBJECT
  public:

    int                 dockingOrientation ;
    Qt::DockWidgetArea  dockingPlace       ;
    Qt::DockWidgetAreas dockingPlaces      ;

    explicit     ControlPad     (StandardConstructor) ;
    virtual     ~ControlPad     (void) ;

    virtual QWidget * Find      (QString AccessibleName) ;

  protected:

    QMap<QWidget *,QObject *> Parents   ;
    QMap<QWidget *,int      > WidgetId  ;
    QMap<int      ,QWidget *> WidgetMap ;
    NAMEs                     Titles    ;
    QStackedWidget         *  ToolStack ;
    QStackedWidget         *  ViewStack ;
    QSplitter              *  Top       ;
    QWidget                *  ButtonPad ;
    QToolButton            *  Close     ;
    QToolButton            *  Position  ;
    QComboBox              *  Tools     ;
    QLabel                 *  Empty     ;
    int                       Lastest   ;

    virtual void Configure      (void) ;
    virtual void resizeEvent    (QResizeEvent * event) ;

  private:

  public slots:

    virtual void Relocation     (void) ;
    virtual void Docking        (QMainWindow       * Main    ,
                                 QString             title   ,
                                 Qt::DockWidgetArea  area    ,
                                 Qt::DockWidgetAreas areas ) ;
    virtual void DockIn         (bool shown) ;

    virtual void Leave          (QWidget * widget) ;
    virtual void Leave          (QObject * object) ;
    virtual void Detach         (QWidget * widget) ;
    virtual void addControl     (QString name,QWidget * widget,QWidget * parent) ;
    virtual void addControl     (QString name,QWidget * widget,QObject * parent) ;

    virtual void CloseWidget    (void) ;
    virtual void ChangePosition (void) ;

  protected slots:

    virtual void FindCurrent    (int index) ;
    virtual void Delete         (QWidget * widget) ;
    virtual void ActualLeave    (QObject * object) ;
    virtual void ActualAdd      (QString name,QWidget * widget,QObject * parent) ;

  private slots:

    virtual void Visible        (bool visible);
    virtual void WidgetChanged  (int index) ;

  signals:

    void SendAdd                (QString name,QWidget * control,QObject * parent) ;
    void SendLeave              (QObject * object) ;

    DockSignals ;

} ;

class Q_COMPONENTS_EXPORT ProgressManager : public TreeDock
{
  Q_OBJECT
  public:

    explicit ProgressManager   (StandardConstructor) ;
    virtual ~ProgressManager   (void) ;

  protected:

    int                         Id            ;
    bool                        Fitting       ;
    QTimer                   *  Timer         ;
    QMap<int,QTreeWidgetItem *> Items         ;
    QMap<int,QToolButton     *> Buttons       ;
    QMap<int,QProgressBar    *> Progress      ;
    QMap<int,bool            *> Booleans      ;
    QMap<int,qint64          *> Values        ;
    QMap<int,QDateTime        > Begins        ;
    QMap<int,qint64           > Final         ;
    QMap<int,qint64           > Minimum       ;
    QMap<int,qint64           > StartAt       ;
    QMap<int,qint64           > Maximum       ;
    EMAPs                       Connects      ;
    EMAPs                       Message       ;
    EMAPs                       Formats       ;
    EMAPs                       FREQs         ;
    EMAPs                       FREQr         ;
    VOIDs                       Queues        ;
    CUIDs                       Stoppings     ;
    CUIDs                       WIDTHs        ;
    CUIDs                       EnableButtons ;
    QMutex                      QueueMutex    ;
    QMutex                      IdMutex       ;

    virtual void Configure     (void) ;

    virtual void Report        (int Id) ;
    void         reportTasks   (void) ;

    virtual void run           (int type,ThreadData * data) ;

    virtual void GetSettings   (VarArgs & args) ;

  private:

  public slots:

    virtual bool Shutdown      (void) ;
    virtual void StartFlush    (void) ;
    virtual void Update        (void) ;
    virtual void Clean         (void) ;

    virtual void Recovery      (QString scope) ;
    virtual void Store         (QString scope) ;

    int          Request       (QString name,QString format) ;
    void         setName       (int Id,QString name) ;
    void         setRange      (int Id,qint64 Min,qint64 Max) ;
    void         setMessage    (int Id,QString mesage) ;
    void         setFormat     (int Id,QString format) ;
    void         setFrequency  (int Id,QString cFmt,QString rFmt) ;
    void         Start         (int Id,qint64 * Value,bool * Running) ;
    void         Finish        (int Id) ;
    bool         isReady       (int Id) ;
    bool         waitForReady  (int Id,int msecs = 1000) ;

  protected slots:

    virtual bool Menu          (QPoint pos) ;
    bool         End           (int Id) ;

  private slots:

    void         Accepting     (int ID,QString name,QString format) ;
    void         Accepting     (void) ;
    void         LocalAccept   (void) ;
    void         setWidths     (void) ;
    void         EnsureTimer   (void) ;

  signals:

    void         AdjustWidth   (void) ;
    void         LocalRequest  (void) ;
    void         Requesting    (void) ;
    void         EmitTimer     (void) ;
    void         Hidden        (QWidget * widget) ;

} ;

class Q_COMPONENTS_EXPORT DebugView : public TextBrowser
                                    , public AttachDock
{
  Q_OBJECT
  public:

    explicit DebugView            (StandardConstructor);
    virtual ~DebugView            (void);

  protected:

    QStringList Queue ;
    QTimer    * Timer ;

    virtual bool FocusIn          (void) ;
    virtual void Configure        (void) ;

    virtual void closeEvent       (QCloseEvent       * event) ;
    virtual void contextMenuEvent (QContextMenuEvent * event) ;

  private:

  public slots:

    virtual void Docking          (QMainWindow       * Main    ,
                                   QString             title   ,
                                   Qt::DockWidgetArea  area    ,
                                   Qt::DockWidgetAreas areas ) ;
    virtual void DockIn           (bool shown) ;

    virtual void Append           (const QString & text) ;
    virtual void Save             (void) ;
    virtual void FlushQueue       (void) ;

    virtual void Startup          (void) ;
    virtual void Flush            (void) ;
    virtual void Stop             (void) ;

    virtual void ZoomIn           (void) ;
    virtual void ZoomOut          (void) ;

  protected slots:

    virtual void Visible                  (bool visible) ;
    virtual bool Menu             (QPoint pos) ;

  private slots:

  signals:

    DockSignals ;

    void        StartFlush        (void) ;

} ;

class Q_COMPONENTS_EXPORT ClipboardView : public TextBrowser
{
  Q_OBJECT
  public:

    explicit      ClipboardView    (StandardConstructor) ;
    virtual      ~ClipboardView    (void) ;

    virtual QSize sizeHint         (void) const ;

  protected:

    virtual void  contextMenuEvent (QContextMenuEvent * event) ;

    virtual void  Configure        (void) ;

    virtual bool  FocusIn          (void) ;

  private:

  public slots:

    virtual bool  startup          (void) ;

  protected slots:

    virtual bool Menu             (QPoint pos) ;

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT TextAlignEditor : public QDialog
{
  Q_OBJECT
  public:

    explicit TextAlignEditor (QWidget * parent = NULL) ;
    virtual ~TextAlignEditor (void) ;

    int  Alignment           (void) ;
    void setAlignment        (int alignment) ;

  protected:

    Ui::nTextAlignEditor * ui ;

    virtual void Configure   (void) ;

  private:

} ;

class Q_COMPONENTS_EXPORT GetSize : public Dialog
{
  Q_OBJECT
  public:

    explicit GetSize   (StandardConstructor) ;
    virtual ~GetSize   (void) ;

    QSize Size         (void) ;
    int   value        (int index) ;

  protected:

    Ui::nGetSize * ui ;

  private:

  public slots:

    void setSize       (QSize size) ;
    void setValue      (int index,int v) ;
    void setRange      (int index,int MinV,int MaxV) ;
    void setSingleStep (int index,int v) ;
    void setPrefix     (int index,QString name) ;
    void setSuffix     (int index,QString name) ;

  protected slots:

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT GetXYZ : public Dialog
{
  Q_OBJECT
  public:

    explicit GetXYZ        (StandardConstructor) ;
    virtual ~GetXYZ        (void) ;

    ControlPoint  Point    (void) ;
    QVector3D     Vector   (void) ;
    double        X        (void) ;
    double        Y        (void) ;
    double        Z        (void) ;

  protected:

    Ui::nGetXYZ * ui ;

  private:

  public slots:

    virtual void setXYZ    (double x,double y,double z) ;
    virtual void setPoint  (ControlPoint & point) ;
    virtual void setVector (QVector3D & vector) ;

  protected slots:

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT LanguageSelections : public Dialog
{
  Q_OBJECT
  public:

    explicit LanguageSelections (StandardConstructor) ;
    virtual ~LanguageSelections (void) ;

    int   Language              (void) ;
    CUIDs AllLanguages          (void) ;

  protected:

    Ui::nLanguageSelections * ui       ;

    virtual void Configure      (void) ;

  private:

  public slots:

    void List                    (int language = 0) ;
    void List                    (CUIDs IDs) ;

  protected slots:

    void doubleClicked           (QTreeWidgetItem * item,int column) ;

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT UuidSelection : public Dialog
                                        , public GroupItems
{
  Q_OBJECT
  public:

    explicit UuidSelection (StandardConstructor) ;
    virtual ~UuidSelection (void) ;

    SUID     currentUuid   (void) ;

  protected:

    Ui::nUuidSelection * ui ;

  private:

  public slots:

    virtual void setUuids  (UUIDs & Uuids,int language = 0) ;
    virtual void setNames  (UUIDs & Uuids,NAMEs & Names) ;

  protected slots:

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT FontSelector : public Widget
{
  Q_OBJECT
  public:

    explicit FontSelector  (StandardConstructor);
    virtual ~FontSelector  (void);

  protected:

    Font                font ;
    Ui::nFontSelector * ui   ;

    virtual void Configure (void) ;
    void setFontParaments  (void) ;

  private:

  public slots:

    void Done              (void) ;
    void Fetch             (void) ;
    void setFont           (QString name,Font & font) ;

  protected slots:

    void NameChanged       (QString text ) ;
    void doubleChanged     (double  value) ;
    void valueChanged      (int     value) ;
    void FontChanged       (QFont   font ) ;

  private slots:

  signals:

    void Update            (QString name,Font * font) ;

} ;

class Q_COMPONENTS_EXPORT SqlConfigurator : public StackedWidget
                                          , public Object
{
  Q_OBJECT
  public:

    typedef enum     {
      DesktopSQL = 0 ,
      PhoneSQL   = 1 }
      ConfTemplates  ;

    explicit SqlConfigurator (StandardConstructor) ;
    explicit SqlConfigurator (ConfTemplates templ,StandardConstructor) ;
    virtual ~SqlConfigurator (void) ;

    bool setTemplate         (ConfTemplates templ) ;

  protected:

    Ui::DesktopSqlConfigurator * uid ;
    Ui::PhoneSqlConfigurator   * uip ;

  private:

    Sql PrivateSql ;

  public slots:

    void set                 (Sql & sql) ;

    void Selector            (void) ;

    void MySQL               (void) ;
    void PostgreSQL          (void) ;
    void Firebird            (void) ;
    void ODBC                (void) ;
    void SQLite              (void) ;

    void TestMySQL           (void) ;
    void TestPostgreSQL      (void) ;
    void TestFirebird        (void) ;
    void TestODBC            (void) ;
    void TestSQLite          (void) ;

    void ApplyMySQL          (void) ;
    void ApplyPostgreSQL     (void) ;
    void ApplyFirebird       (void) ;
    void ApplyODBC           (void) ;
    void ApplySQLite         (void) ;

    void StringMySQL         (QString text) ;
    void StringPostgreSQL    (QString text) ;
    void StringFirebird      (QString text) ;
    void StringODBC          (QString text) ;
    void StringSQLite        (QString text) ;

    void BrowseFirebird      (void) ;
    void BrowseSQLite        (void) ;

    bool ObtainMySQL         (Sql & sql) ;
    bool ObtainPostgreSQL    (Sql & sql) ;
    bool ObtainFirebird      (Sql & sql) ;
    bool ObtainODBC          (Sql & sql) ;
    bool ObtainSQLite        (Sql & sql) ;

  protected slots:

  private slots:

  signals:

    void apply               (QWidget * widget,Sql * sql) ;
    void apply               (SUID      uuid  ,Sql * sql) ;

} ;

class Q_COMPONENTS_EXPORT ScreenConfigurator : public Widget
{
  Q_OBJECT
  public:

    explicit ScreenConfigurator (StandardConstructor) ;
    virtual ~ScreenConfigurator (void               ) ;

  protected:

    Ui::nScreenConfigurator * ui  ;
    Screen                    Pad ;

    virtual void resizeEvent    (QResizeEvent * event) ;

  private:

  public slots:

    virtual void Refresh        (void) ;
    virtual void Changed        (int ) ;
    virtual void Apply          (void) ;
    virtual void Measure        (void) ;
    virtual void setMeasure     (bool visible) ;

  protected slots:

  private slots:

  signals:

    void Details                (void) ;

} ;

class Q_COMPONENTS_EXPORT FontConfigurator : public Widget
{
  Q_OBJECT
  public:

    explicit FontConfigurator (StandardConstructor) ;
    virtual ~FontConfigurator (void) ;

  protected:

    Ui::nFontConfigurator * ui ;

    virtual void Configure    (void) ;
    virtual bool Obtain       (Font & font) ;
    virtual void showText     (Font & font) ;

  private:

  public slots:

    virtual void addItem      (int Id,QString name) ;
    virtual void startup      (void) ;
    virtual void Update       (void) ;
    virtual void ItemChanged  (int index) ;

  protected slots:

    virtual void FontChanged  (int state) ;
    virtual void FontChanged  (double state) ;

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT ContainerDialog : public Dialog
{
  Q_OBJECT
  public:

    explicit ContainerDialog (StandardConstructor) ;
    virtual ~ContainerDialog (void) ;

  protected:

    Ui::ContainerDialog * ui ;

  private:

  public slots:

    virtual void setWidget (QWidget * widget) ;

  protected slots:

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT CtrlPadPoint : public Widget
{
  Q_OBJECT
  public:

    explicit CtrlPadPoint     (StandardConstructor) ;
    virtual ~CtrlPadPoint     (void) ;

    QPoint   & Create         (void) ;
    QPoint   & Value          (void) ;
    QPoint   & setValue       (QPoint & point) ;
    void       setIdentifier  (int id) ;

    QSpinBox * SpinBox        (int index) ;

  protected:

    Ui::CtrlPadPoint * ui         ;
    QPoint           * point      ;
    int                identifier ;

    virtual void Configure    (void) ;
    virtual void closeEvent   (QCloseEvent * event) ;

  private:

  public slots:

    virtual void ValueChanged (int value) ;

  protected slots:

  private slots:

  signals:

    void Changed              (int id,QWidget * widget) ;
    void Closed               (int id,QWidget * widget) ;

} ;

class Q_COMPONENTS_EXPORT CtrlPadPointF : public Widget
{
  Q_OBJECT
  public:

    explicit CtrlPadPointF    (StandardConstructor) ;
    virtual ~CtrlPadPointF    (void) ;

    QPointF  & Create         (void) ;
    QPointF  & Value          (void) ;
    QPointF  & setValue       (QPointF & point) ;
    void       setIdentifier  (int id) ;

    QDoubleSpinBox * SpinBox  (int index) ;

  protected:

    Ui::CtrlPadPointF * ui         ;
    QPointF           * point      ;
    int                 identifier ;

    virtual void Configure    (void) ;
    virtual void closeEvent   (QCloseEvent * event) ;

  private:

  public slots:

    virtual void ValueChanged (double value) ;

  protected slots:

  private slots:

  signals:

    void Changed              (int id,QWidget * widget) ;
    void Closed               (int id,QWidget * widget) ;

} ;

class Q_COMPONENTS_EXPORT CtrlPadSize : public Widget
{
  Q_OBJECT
  public:

    explicit CtrlPadSize      (StandardConstructor) ;
    virtual ~CtrlPadSize      (void) ;

    QSize    & Create         (void) ;
    QSize    & Value          (void) ;
    QSize    & setValue       (QSize & size) ;
    void       setIdentifier  (int id) ;

    QSpinBox * SpinBox        (int index) ;

  protected:

    Ui::CtrlPadSize * ui         ;
    QSize           * size       ;
    int               identifier ;

    virtual void Configure    (void) ;
    virtual void closeEvent   (QCloseEvent * event) ;

  private:

  public slots:

    virtual void ValueChanged (int value) ;

  protected slots:

  private slots:

  signals:

    void Changed              (int id,QWidget * widget) ;
    void Closed               (int id,QWidget * widget) ;

} ;

class Q_COMPONENTS_EXPORT CtrlPadSizeF : public Widget
{
  Q_OBJECT
  public:

    explicit CtrlPadSizeF     (StandardConstructor) ;
    virtual ~CtrlPadSizeF     (void) ;

    QSizeF  & Create          (void) ;
    QSizeF  & Value           (void) ;
    QSizeF  & setValue        (QSizeF & size) ;
    void      setIdentifier   (int id) ;

    QDoubleSpinBox * SpinBox  (int index) ;

  protected:

    Ui::CtrlPadSizeF * ui         ;
    QSizeF           * size       ;
    int                identifier ;

    virtual void Configure    (void) ;
    virtual void closeEvent   (QCloseEvent * event) ;

  private:

  public slots:

    virtual void ValueChanged (double value) ;

  protected slots:

  private slots:

  signals:

    void Changed              (int id,QWidget * widget) ;
    void Closed               (int id,QWidget * widget) ;

} ;

class Q_COMPONENTS_EXPORT CtrlPadRect : public Widget
{
  Q_OBJECT
  public:

    explicit CtrlPadRect      (StandardConstructor) ;
    virtual ~CtrlPadRect      (void) ;

    QRect    & Create         (void) ;
    QRect    & Value          (void) ;
    QRect    & setValue       (QRect & rect) ;
    void       setIdentifier  (int id) ;

    QSpinBox * SpinBox        (int index) ;

  protected:

    Ui::CtrlPadRect * ui         ;
    QRect           * rect       ;
    int               identifier ;

    virtual void Configure    (void) ;
    virtual void closeEvent   (QCloseEvent * event) ;

  private:

  public slots:

    virtual void ValueChanged (int value) ;

  protected slots:

  private slots:

  signals:

    void Changed              (int id,QWidget * widget) ;
    void Closed               (int id,QWidget * widget) ;

} ;

class Q_COMPONENTS_EXPORT CtrlPadRectF : public Widget
{
  Q_OBJECT
  public:

    explicit CtrlPadRectF     (StandardConstructor) ;
    virtual ~CtrlPadRectF     (void) ;

    QRectF  & Create          (void) ;
    QRectF  & Value           (void) ;
    QRectF  & setValue        (QRectF & size) ;
    void      setIdentifier   (int id) ;

    QDoubleSpinBox * SpinBox  (int index) ;

  protected:

    Ui::CtrlPadRectF * ui         ;
    QRectF           * rect       ;
    int                identifier ;

    virtual void Configure    (void) ;
    virtual void closeEvent   (QCloseEvent * event) ;

  private:

  public slots:

    virtual void ValueChanged (double value) ;

  protected slots:

  private slots:

  signals:

    void Changed              (int id,QWidget * widget) ;
    void Closed               (int id,QWidget * widget) ;

} ;

class Q_COMPONENTS_EXPORT CtrlPadPointsIndex : public TreeWidget
{
  Q_OBJECT
  public:

    explicit CtrlPadPointsIndex       (StandardConstructor) ;
    virtual ~CtrlPadPointsIndex       (void) ;

    QMap<int,QPointF> & Create        (void) ;
    QMap<int,QPointF> & Value         (void) ;
    QMap<int,QPointF> & setPoints     (QMap<int,QPointF> & points) ;
    void                setIdentifier (int id) ;
    void                setDigits     (int digits) ;

    virtual bool        toPlainText   (QByteArray & text) ;
    virtual bool        toHtml        (QByteArray & text) ;
    virtual bool        toTeX         (QByteArray & text) ;

  protected:

    int                 identifier ;
    int                 digits     ;
    QMap<int,QPointF> * Points     ;

    virtual void Configure            (void) ;
    virtual bool FocusIn              (void) ;

    virtual void closeEvent           (QCloseEvent * event) ;

    virtual void assignItem           (QTreeWidgetItem * item,int id,QPointF p) ;
    QString      DoubleString         (double v) ;

  private:

  public slots:

    virtual bool startup              (void) ;

    virtual void New                  (void) ;
    virtual void Delete               (void) ;
    virtual void Paste                (void) ;
    virtual void Paste                (QString text) ;
    virtual void Copy                 (void) ;
    virtual void Export               (void) ;

  protected slots:

    virtual bool Menu                 (QPoint pos) ;

    virtual void singleClicked        (QTreeWidgetItem * item,int column) ;
    virtual void doubleClicked        (QTreeWidgetItem * item,int column) ;
    virtual void editingFinished      (void) ;

  private slots:

  signals:

    void Changed                      (int id,QWidget * widget) ;
    void Closed                       (int id,QWidget * widget) ;

} ;

class Q_COMPONENTS_EXPORT ControlPointEditor : public Widget
{
  Q_OBJECT
  public:

    ControlPoint * point ;

    explicit ControlPointEditor (StandardConstructor) ;
    virtual ~ControlPointEditor (void) ;

  protected:

    QMap<int,DoubleSpinBox *> Spins ;

  private:

  public slots:

    virtual void prepare        (void) ;

  protected slots:

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT ContainEditor : public Widget
{
  Q_OBJECT
  public:

    VcfInterface * vcf ;

    explicit ContainEditor  (StandardConstructor) ;
    virtual ~ContainEditor  (void) ;

  protected:

    StackedWidget * stacked  ;
    TabWidget     * tab      ;
    QPushButton   * complete ;
    QSize           range    ;

    virtual void Configure  (void) ;

  private:

  public slots:

    virtual void Close      (void) ;

    virtual void addStacked (QWidget * widget) ;
    virtual void setStacked (QWidget * widget) ;
    virtual void addTab     (QWidget * widget,QString title) ;

  protected slots:

  private slots:

  signals:

    void Close              (ContainEditor * ce) ;

} ;

class Q_COMPONENTS_EXPORT CompanionWidget : public IconDock
{
  Q_OBJECT
  public:

    explicit     CompanionWidget   (StandardConstructor) ;
    virtual     ~CompanionWidget   (void) ;

  protected:

    ToolWrapper                      *   wrapper   ;
    QTimer                           *   cpu       ;
    QImage                           *   bgimg     ;
    QImage                           *   desktop   ;
    QImage                           *   monitors  ;
    Mutexz                               mutex     ;
    QMap < QString , QListWidgetItem * > HostItems ;

    virtual void Configure         (void) ;

    virtual void run               (int Type,ThreadData * data) ;
    virtual bool ItemRunner        (int Type,ThreadData * data) ;

  private:

    virtual void DrawMachine       (QListWidgetItem * item,QString host) ;

  public slots:

    virtual void setMachineIcon    (QImage & image) ;

    virtual void setWrapper        (ToolWrapper * wrapper) ;
    virtual void Appear            (void) ;
    virtual void Disappear         (void) ;
    virtual void Vanish            (void) ;
    virtual void Eradicate         (void) ;

    virtual void Start             (void) ;
    virtual void Stop              (void) ;

    virtual void Visit             (void) ;
    virtual void Close             (void) ;

    virtual void Listing           (void) ;

  protected slots:

    virtual bool Menu              (QPoint pos) ;

    virtual void singleClicked     (QListWidgetItem * item) ;
    virtual void doubleClicked     (QListWidgetItem * item) ;

    virtual void Reflush           (void) ;

  private slots:

  signals:

    void         CompanionsChanged (void) ;
    void         Changes           (void) ;
    void         Complete          (void) ;
    void         ParallelComputing (void) ;
    void         Details           (QString host) ;
    void         Chat              (QString host) ;
    void         CommandTo         (QString host) ;
    void         Quit              (QString host) ;

} ;

class Q_COMPONENTS_EXPORT Scintilla : public QsciScintilla
                                    , public VirtualGui
                                    , public AttachDock
                                    , public Thread
{
  Q_OBJECT
  public:

    int                 dockingOrientation ;
    Qt::DockWidgetArea  dockingPlace       ;
    Qt::DockWidgetAreas dockingPlaces      ;

    explicit     Scintilla   (StandardConstructor) ;
    virtual     ~Scintilla   (void) ;

  protected:

    bool     Commanding      ;
    QTimer * CommandSequence ;

    virtual void focusInEvent          (QFocusEvent       * event) ;
    virtual void focusOutEvent         (QFocusEvent       * event) ;
    virtual void contextMenuEvent      (QContextMenuEvent * event) ;
    virtual void resizeEvent           (QResizeEvent      * event) ;
    virtual void closeEvent            (QCloseEvent       * event) ;

    virtual void Configure   (void) ;

    virtual void ThreadEvent (void) ;

    virtual void run         (int type,ThreadData * data) ;

  private:

  public slots:

    virtual bool startup               (void) ;
    virtual void pendingStartup        (void) ;
    virtual bool Shutdown              (void) ;
    virtual bool Relocation            (void) ;

    virtual void Docking     (QMainWindow       * Main    ,
                              QString             title   ,
                              Qt::DockWidgetArea  area    ,
                              Qt::DockWidgetAreas areas ) ;
    virtual void DockIn      (bool shown) ;

    virtual void Execute               (int command) ;
    virtual bool RunCommand            (VarArgs & arguments) ;

  protected slots:

    virtual bool Menu                  (QPoint pos);

    virtual void DockingMenu (MenuManager & Menu) ;
    virtual bool RunDocking  (MenuManager & Menu,QAction * action) ;
    void         Visible     (bool visible) ;

    virtual void AtBusy      (void) ;
    virtual void OnRelax     (void) ;

    virtual void StartCommand          (void) ;
    virtual void CommandHandler        (void) ;
    virtual void DropCommands          (void) ;

  private slots:

  signals:

    DockSignals ;

    void Leave               (nDeclWidget) ;
    void Follow              (int command) ;
    void OnBusy              (void) ;
    void GoRelax             (void) ;
    void TriggerCommand      (void) ;

} ;

/*****************************************************************************
 *                                                                           *
 *                           Enhanced Item View                              *
 *                                                                           *
 *****************************************************************************/

class Q_COMPONENTS_EXPORT ClickableLabel : public QLabel
                                         , public VirtualGui
{
  Q_OBJECT
  public:

    explicit ClickableLabel      (StandardConstructor) ;
    virtual ~ClickableLabel      (void) ;

  protected:

    virtual void mousePressEvent (QMouseEvent * event) ;

  private:

  public slots:

  protected slots:

  private slots:

  signals:

    void clicked                 (Qt::MouseButtons buttons) ;

} ;

class Q_COMPONENTS_EXPORT EditToolBar : public ToolBar
{
  Q_OBJECT
  public:

    enum                                   {
      AttacheId = Menus::DeviceMenuId + 1730
    }                                      ;

    explicit     EditToolBar (StandardConstructor) ;
    virtual     ~EditToolBar (void) ;

    ComboBox *   Listing (void)  ;

  protected:

    QAction  * action ;
    QAction  * widget ;
    LineEdit * line   ;
    ComboBox * combo  ;

    virtual void Configure   (void) ;

  private:

  public slots:

    virtual bool Relocation  (void) ;
    virtual void setIcon     (QIcon icon) ;
    virtual void LinkToLine  (QObject * widget,const char * receiver,const char * member) ;
    virtual void LinkToList  (QObject * widget,const char * receiver,const char * member) ;
    virtual void ClearCombo  (void) ;

  protected slots:

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT GeneralDispatcher : public QObject
                                            , public SyntaxDispatcher
                                            , public UuidSyntax
{
  Q_OBJECT
  public:

    explicit     GeneralDispatcher (QObject * parent) ;
    virtual     ~GeneralDispatcher (void) ;

    virtual int  type              (void) const ; // CiosMenuId ( 51 , 0 , 1 )
    virtual int  matching          (QString command) ;
    virtual bool execute           (int id) ;
    virtual void setExtras         (void * data) ;
    virtual void Help              (QStringList & help) ;

  protected:

    Plan * plan      ;
    WMAPs  Variables ;

  private:

  public slots:

    virtual void GroupsPosition    (void) ;
    virtual void setVariable       (void) ;
    virtual void showVariables     (void) ;
    virtual void InchesToCGS       (void) ;
    virtual void CGSToInches       (void) ;
    virtual void ShowCPU           (void) ;

  protected slots:

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT CpuLabel : public ClickableLabel
                                   , public CPU::Usage
{
  Q_OBJECT
  public:

    bool Flag ;

    explicit CpuLabel   (StandardConstructor,bool flags = true) ;
    virtual ~CpuLabel   (void) ;

  protected:

    QTimer * Timer ;

  private:

  public slots:

    virtual void Update (void) ;
    virtual void Start  (void) ;
    virtual void Stop   (void) ;

  protected slots:

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT SceneWidget : public QObject
                                      , public QScriptable
                                      , public SceneObject
                                      , public Thread
{
  Q_OBJECT
  public:

    typedef enum                 {
      DropText          = 1001   ,
      DropUrls          = 1002   ,
      DropImage         = 1003   ,
      DropHtml          = 1004   ,
      DropColor         = 1005   ,
      DropTag           = 1006   ,
      DropPicture       = 1007   ,
      DropPeople        = 1008   ,
      DropAudio         = 1009   ,
      DropVideo         = 1010   ,
      DropAlbum         = 1011   ,
      DropGender        = 1012   ,
      DropDivision      = 1013   ,
      DropURIs          = 1014   ,
      DropBookmark      = 1015   ,
      DropFont          = 1016   ,
      DropPen           = 1017   ,
      DropBrush         = 1018   ,
      DropGradient      = 1019   ,
      DropShape         = 1020   ,
      DropMember        = 1021   ,
      DropSet           = 1022   ,
      DropActions       = 1023   ,
      DropDecision      = 1024   ,
      DropCondition     = 1025   ,
      DropExecution     = 1026   ,
      DropSqlTable      = 1027   ,
      DropDatabase      = 1028   ,
      DropTask          = 1029   ,
      DropNation        = 1030   ,
      DropContour       = 1031   ,
      DropManifold      = 1032   ,
      DropSource        = 1033   ,
      DropDocument      = 1034   ,
      DropEyes          = 1035   ,
      DropHairs         = 1036   ,
      DropKeyword       = 1037   ,
      DropTerminology   = 1038   ,
      DropKnowledge     = 1039   ,
      DropField         = 1040   ,
      DropKnowledgeBase = 1041   ,
      DropSqlColumn     = 1042   ,
      DropUuid          = 1043   ,
      DropCommodity     = 1044   ,
      DropOrganization  = 1045   ,
      DropBlob          = 1046   ,
      DropVariable      = 1047   ,
      DropTorrent       = 1048   ,
      DropCamera        = 1049   ,
      DropFace          = 1050   ,
      DropColorGroup    = 1051   ,
      DropSetsAlgebra   = 1052   ,
      DropName          = 1053   ,
      DropStar          = 1054   ,
      DropPhoneme       = 1055   ,
      DropModel         = 1056   ,
      DropReality       = 1057   ,
      DropMusic         = 1058   }
      DropTypes                  ;

    static QScriptValue SceneAttachment (QScriptContext * context,QScriptEngine * engine) ;

    explicit     SceneWidget         (QObject * parent,Plan * plan) ;
    explicit     SceneWidget         (QObject * parent,Plan * plan,SceneDestructor * destructor) ;
    virtual     ~SceneWidget         (void) ;

    static int   MenuBindings        (void * data,void * dispatcher,QVariants & v) ;

    virtual void suicide             (void) ;
    virtual void ObjectPointer       (QByteArray & pointer) ;

    virtual QAction * connectAction  (int          Id              ,
                                      QObject    * parent          ,
                                      const char * method          ,
                                      bool         enable = true ) ;

    virtual bool canDrag             (void) ;
    void         setDropFlag         (DropTypes dropType,bool enabled) ;
    virtual bool dropNew             (QWidget         * widget ,
                                      const QMimeData * mime   ,
                                      ControlPoint    & From   ,
                                      ControlPoint    & To     ,
                                      ControlPoint    & At   ) ;
    virtual bool dropMoving          (QWidget         * widget ,
                                      const QMimeData * mime   ,
                                      ControlPoint    & From   ,
                                      ControlPoint    & To     ,
                                      ControlPoint    & At   ) ;
    virtual bool dropAppend          (QWidget         * widget ,
                                      const QMimeData * mime   ,
                                      ControlPoint    & From   ,
                                      ControlPoint    & To     ,
                                      ControlPoint    & At   ) ;
    virtual bool removeDrop          (void) ;
    virtual bool dragEnter           (ControlPoint    & From    ,
                                      ControlPoint    & To      ,
                                      QDragEnterEvent * event ) ;
    virtual bool dragMove            (ControlPoint    & From    ,
                                      ControlPoint    & To      ,
                                      QDragMoveEvent  * event ) ;
    virtual bool drop                (ControlPoint    & From    ,
                                      ControlPoint    & To      ,
                                      QDropEvent      * event ) ;

    virtual int  GroupType           (int index) ;
    virtual int  RelationType        (void) ;
    virtual int  SortingType         (void) ;
    virtual QString SortItem         (void) ;
    virtual QString MainTable        (void) ;
    virtual SUID FirstUuid           (void) ;
    virtual SUID SecondUuid          (void) ;

    virtual bool hasDrag             (void) ;
    virtual bool doDrag              (void) ;

  protected:

    Plan      * plan       ;
    QDrag     * Drag       ;
    QMimeData * mimeDrag   ;
    bool        Dumping    ;
    BMAPs       AllowDrops ;

    virtual void Configure           (void) ;

    virtual bool endDrag             (void) ;

    UUIDs        GetUuids            (QByteArray & data) ;
    SUID         GetUuid             (QByteArray & data) ;
    QByteArray   CreateByteArray     (SUID    uuid ) ;
    QByteArray   CreateByteArray     (UUIDs & Uuids) ;
    void         setMime             (QMimeData * mime,QString mtype,SUID    uuid ) ;
    void         setMime             (QMimeData * mime,QString mtype,UUIDs & Uuids) ;

    // drag management
    bool         dragStart           (ControlPoint & From    ,
                                      ControlPoint & To      ,
                                      ControlPoint & At      ,
                                      QMouseEvent  * event ) ;
    bool         dragMoving          (ControlPoint & From    ,
                                      ControlPoint & To      ,
                                      ControlPoint & At      ,
                                      QMouseEvent  * event ) ;
    bool         dragEnd             (QMouseEvent  * event ) ;

    virtual bool hasItem             (ControlPoint & From    ,
                                      ControlPoint & To      ,
                                      ControlPoint & At    ) ;
    virtual bool startDrag           (ControlPoint & From    ,
                                      ControlPoint & To      ,
                                      ControlPoint & At      ,
                                      QMouseEvent  * event ) ;
    virtual bool fetchDrag           (ControlPoint & From    ,
                                      ControlPoint & To      ,
                                      ControlPoint & At      ,
                                      QMouseEvent  * event ) ;
    virtual QMimeData * dragMime     (ControlPoint & From    ,
                                      ControlPoint & To      ,
                                      ControlPoint & At    ) ;
    virtual void dragDone            (Qt::DropAction dropIt,QMimeData * mime);
    virtual bool finishDrag          (QMouseEvent * event);

    virtual bool acceptTextDrop      (void) ;
    virtual bool acceptUrlsDrop      (void) ;
    virtual bool acceptImageDrop     (void) ;
    virtual bool acceptHtmlDrop      (void) ;
    virtual bool acceptColorDrop     (void) ;
    virtual bool acceptTagDrop       (void) ;
    virtual bool acceptPictureDrop   (void) ;
    virtual bool acceptPeopleDrop    (void) ;
    virtual bool acceptAudioDrop     (void) ;
    virtual bool acceptVideoDrop     (void) ;
    virtual bool acceptAlbumDrop     (void) ;
    virtual bool acceptGenderDrop    (void) ;
    virtual bool acceptDivisionDrop  (void) ;
    virtual bool acceptUriDrop       (void) ;
    virtual bool acceptBookmarkDrop  (void) ;
    virtual bool acceptFont          (void) ;
    virtual bool acceptPen           (void) ;
    virtual bool acceptBrush         (void) ;
    virtual bool acceptGradient      (void) ;
    virtual bool acceptShapes        (void) ;
    virtual bool acceptMembers       (void) ;
    virtual bool acceptSets          (void) ;
    virtual bool acceptActions       (void) ;
    virtual bool acceptDecision      (void) ;
    virtual bool acceptCondition     (void) ;
    virtual bool acceptExecution     (void) ;
    virtual bool acceptSqlTable      (void) ;
    virtual bool acceptDatabase      (void) ;
    virtual bool acceptTask          (void) ;
    virtual bool acceptNation        (void) ;
    virtual bool acceptContour       (void) ;
    virtual bool acceptManifold      (void) ;
    virtual bool acceptSources       (void) ;
    virtual bool acceptDocuments     (void) ;
    virtual bool acceptEyes          (void) ;
    virtual bool acceptHairs         (void) ;
    virtual bool acceptKeywords      (void) ;
    virtual bool acceptTerminologies (void) ;
    virtual bool acceptKnowledge     (void) ;
    virtual bool acceptFields        (void) ;
    virtual bool acceptKnowledgeBase (void) ;
    virtual bool acceptSqlColumn     (void) ;
    virtual bool acceptUuids         (void) ;
    virtual bool acceptCommodities   (void) ;
    virtual bool acceptOrganizations (void) ;
    virtual bool acceptBlobs         (void) ;
    virtual bool acceptVariables     (void) ;
    virtual bool acceptTorrents      (void) ;
    virtual bool acceptCameras       (void) ;
    virtual bool acceptFaces         (void) ;
    virtual bool acceptColorGroups   (void) ;
    virtual bool acceptSetsAlgebras  (void) ;
    virtual bool acceptNames         (void) ;
    virtual bool acceptStars         (void) ;
    virtual bool acceptPhonemes      (void) ;
    virtual bool acceptModels        (void) ;
    virtual bool acceptReality       (void) ;
    virtual bool acceptMusic         (void) ;

    virtual bool acceptPrivate       (const QMimeData * mime) ;

    virtual bool dropHandler         (const QMimeData * mime) ;

    virtual bool dropItems           (nDeclWidget,const QMimeData * mime,ControlPoint pos) ;
    virtual bool dropPrivate         (nDeclWidget,const QMimeData * mime,ControlPoint pos) ;

    virtual bool dropText            (nDeclWidget,ControlPoint pos,const QString & text    ) ;
    virtual bool dropUrls            (nDeclWidget,ControlPoint pos,const QList<QUrl> & urls) ;
    virtual bool dropImage           (nDeclWidget,ControlPoint pos,const QImage  & image   ) ;
    virtual bool dropHtml            (nDeclWidget,ControlPoint pos,const QString & html    ) ;
    virtual bool dropColor           (nDeclWidget,ControlPoint pos,const QColor  & color   ) ;
    virtual bool dropTags            (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropPictures        (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropPeople          (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropAudios          (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropVideos          (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropAlbums          (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropGender          (nDeclWidget,ControlPoint pos,const SUID      gender  ) ;
    virtual bool dropDivisions       (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropURIs            (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropBookmarks       (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropFont            (nDeclWidget,ControlPoint pos,const SUID      font    ) ;
    virtual bool dropPen             (nDeclWidget,ControlPoint pos,const SUID      pen     ) ;
    virtual bool dropBrush           (nDeclWidget,ControlPoint pos,const SUID      brush   ) ;
    virtual bool dropGradient        (nDeclWidget,ControlPoint pos,const SUID      gradient) ;
    virtual bool dropShapes          (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropMembers         (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropSets            (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropActions         (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropDecision        (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropCondition       (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropExecution       (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropSqlTable        (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropDatabase        (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropTask            (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropNation          (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropContour         (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropManifold        (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropSources         (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropDocuments       (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropEyes            (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropHairs           (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropKeywords        (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropTerminologies   (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropKnowledge       (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropFields          (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropKnowledgeBase   (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropSqlColumn       (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropUuids           (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropCommodities     (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropOrganizations   (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropBlobs           (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropVariables       (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropTorrents        (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropCameras         (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropFaces           (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropColorGroups     (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropSetsAlgebras    (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropNames           (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropStars           (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropPhonemes        (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropModels          (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropReality         (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;
    virtual bool dropMusic           (nDeclWidget,ControlPoint pos,const UUIDs   & Uuids   ) ;

    virtual bool LoadGroups          (SqlConnection & Connection                    ,
                                      int             type                          ,
                                      UUIDs         & uuids                         ,
                                      int             orderby = Qt::DescendingOrder ,
                                      QString         item    = "position"        ) ;
    virtual QString FetchName        (SqlConnection & SC,SUID uuid) ;
    virtual QString FetchNames       (SqlConnection & SC,SUID uuid) ;
    virtual QString FetchAsynName    (SqlConnection & SC,SUID uuid,int Language) ;
    virtual SUID AppendGroup         (QString name,int type) ;

    virtual bool Equal               (QImage & image   ,
                                      QSize    size  ) ;
    virtual bool Smaller             (QImage & image   ,
                                      QSize    size  ) ;
    virtual QImage * toIcon          (QImage * image   ,
                                      QSize    size  ) ;
    virtual QImage   toIcon          (QImage & image   ,
                                      QSize    size  ) ;

    virtual void ThreadEvent         (void) ;
    virtual void AssignFocus         (void) ;

  private:

    bool         allowDrops          (DropTypes dropType) ;

  public slots:

    virtual void CloseChild          (SUID u) ;
    virtual bool shutdown            (void) ;

    virtual void ZoomIn              (void) ;
    virtual void ZoomOut             (void) ;
    virtual void SelectNothing       (void) ;
    virtual void SelectAll           (void) ;

    virtual int  MenuBinder          (MenuManager & mm           ,
                                      QAction     * action       ,
                                      QVariants   & v            ,
                                      void        * dispatcher ) ;
    virtual void BindingMenu         (SceneObject * node) ;
    virtual int  CallToMenu          (MenuManager & mm         ,
                                      QAction     * aa         ,
                                      bool          executed ) ;
    virtual int  CallTapping         (QString tapping,QVariants & args) ;
    virtual int  CallRequests        (QVariants & args) ;
    virtual int  CallBinding         (QVariants & args) ;

  protected slots:

    virtual void SortingMenu         (MenuManager & mm,QMenu   * ms) ;
    virtual void SelectionMenu       (MenuManager & mm,QMenu   * ma) ;
    virtual void AdjustMenu          (MenuManager & mm,QMenu   * ma) ;
    virtual bool SortingProcessor    (MenuManager & mm,QAction * aa) ;
    virtual bool SelectProcessor     (MenuManager & mm,QAction * aa) ;
    virtual bool AdjustProcessor     (MenuManager & mm,QAction * aa) ;

  private slots:

    void         localCursor         (int cursorType) ;

  signals:

    void         CloseObject         (SUID u) ;
    void         assignCursor        (int cursorType) ;

} ;

class Q_COMPONENTS_EXPORT UniverseWidget : public QObject
                                         , public QScriptable
                                         , public Universe
                                         , public Thread
{
  Q_OBJECT
  public:

    static QScriptValue UniverseAttachment (QScriptContext * context,QScriptEngine * engine) ;

    explicit     UniverseWidget (QObject * parent,Plan * plan) ;
    explicit     UniverseWidget (QObject * parent,Plan * plan,SceneDestructor * destructor) ;
    virtual     ~UniverseWidget (void) ;

    static int   MenuBindings   (void * data,void * dispatcher,QVariants & v) ;

  protected:

    Plan * plan ;

    virtual void Configure      (void) ;

  private:

  public slots:

    virtual int  MenuBinder     (MenuManager & mm           ,
                                 QAction     * action       ,
                                 QVariants   & v            ,
                                 void        * dispatcher ) ;
    virtual void BindingMenu    (SceneObject * node) ;
    virtual int  CallToMenu     (MenuManager & mm         ,
                                 QAction     * aa         ,
                                 bool          executed ) ;
    virtual int  CallTapping    (QString tapping,QVariants & args) ;
    virtual int  CallBinding    (QVariants & args) ;

  protected slots:

  private slots:

    void         localCursor    (int cursorType) ;

  signals:

    void         assignCursor   (int cursorType) ;

} ;

class Q_COMPONENTS_EXPORT ScriptableRunner : public QObject
                                           , public QScriptable
                                           , public PathRunner
{
  Q_OBJECT
  public:

    UniverseWidget * universe ;

    explicit     ScriptableRunner (QObject * parent = NULL) ;
    virtual     ~ScriptableRunner (void) ;

    virtual int  step             (int after = -1) ;
    virtual bool execute          (void) ;

  protected:

    QScriptEngine * Script   ;
    QScriptValue    Step     ;
    QScriptValue    Execute  ;
    QString         Function ;

  private:

  public slots:

    virtual bool setScript        (QString step,QString execute,QString script) ;

  protected slots:

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT ProgressObject : public SceneWidget
{
  Q_OBJECT
  public:

    explicit     ProgressObject (QObject * parent,Plan * plan) ;
    explicit     ProgressObject (QObject * parent,Plan * plan,SceneDestructor * destructor) ;
    virtual     ~ProgressObject (void) ;

    virtual void renderFaces    (void) ;

  protected:

    ProgressReporter * reporter ;

    virtual void Configure      (void) ;

  private:

  public slots:

    virtual void setReporter    (ProgressReporter * reporter) ;

  protected slots:

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT RangeBar : public SceneWidget
{
  Q_OBJECT
  public:

    qint64 * Index ;

    explicit        RangeBar     (QObject * parent,Plan * plan) ;
    explicit        RangeBar     (QObject * parent,Plan * plan,SceneDestructor * destructor) ;
    virtual        ~RangeBar     (void) ;

    virtual qint64  Total        (void) ;
    virtual qint64  CurrentIndex (void) ;

    virtual void    renderFaces  (void) ;

    virtual bool    FocusIn      (void) ;
    virtual bool    FocusOut     (void) ;

    virtual bool    MouseVector  (ControlPoint & From      ,
                                  ControlPoint & To        ,
                                  BMAPs        & buttons ) ;
    virtual bool    MouseHover   (ControlPoint & From      ,
                                  ControlPoint & To        ,
                                  BMAPs        & buttons ) ;
    virtual bool    MouseMove    (ControlPoint & From1     ,
                                  ControlPoint & To1       ,
                                  ControlPoint & From2     ,
                                  ControlPoint & To2       ,
                                  BMAPs        & buttons ) ;

    virtual bool    Spot         (ControlPoint & From ,
                                  ControlPoint & To   ,
                                  ControlPoint & At ) ;

    virtual bool    Menu         (QWidget      * widget ,
                                  QPointF        pos    ,
                                  ControlPoint & From   ,
                                  ControlPoint & To   ) ;

    virtual int     AtRegion     (ControlPoint & At) ;
    virtual QString ToolTip      (void) ;

  protected:

    virtual void    Configure    (void) ;

    virtual RangeDouble  Holder  (void) ;

    virtual void    indexChanged (void) ;
    virtual double  Shifting     (void) ;

    virtual void    CursorIndex  (void) ;

    virtual void    renderLayout (void) ;
    virtual void    renderHolder (void) ;

    virtual QString ToolTip      (qint64 start,qint64 end,qint64 from,qint64 to) ;

  private:

  public slots:

    virtual void    setTotal     (qint64 total) ;
    virtual void    setRange     (qint64 start,qint64 end) ;
    virtual void    setPage      (qint64 page) ;
    virtual void    setStep      (qint64 step) ;
    virtual void    setIndex     (qint64 index) ;
    virtual void    assignIndex  (qint64 * index) ;

    virtual void    GoHome       (void) ;
    virtual void    GoEnd        (void) ;
    virtual void    PreviousPage (void) ;
    virtual void    NextPage     (void) ;

  protected slots:

  private slots:

  signals:

    void valueChanged            (void) ;
    void valueChanged            (SceneObject * object) ;
    void valueChanged            (RangeBar    * range ) ;
    void indexChanged            (qint64 index) ;
    void indexChanged            (qint64 index,qint64 page) ;
    void pageChanged             (qint64 page) ;
    void rangeChanged            (qint64 start,qint64 end) ;
    void stepChanged             (qint64 step) ;

} ;

class Q_COMPONENTS_EXPORT ValueObject : public SceneWidget
{
  Q_OBJECT
  public:

    qint64 * iValue ;
    double * dValue ;

    explicit        ValueObject  (QObject * parent,Plan * plan) ;
    explicit        ValueObject  (QObject * parent,Plan * plan,SceneDestructor * destructor) ;
    virtual        ~ValueObject  (void) ;

    virtual void    renderFaces  (void) ;

    virtual bool    FocusIn      (void) ;
    virtual bool    FocusOut     (void) ;

    virtual bool    MouseVector  (ControlPoint & From      ,
                                  ControlPoint & To        ,
                                  BMAPs        & buttons ) ;
    virtual bool    MouseHover   (ControlPoint & From      ,
                                  ControlPoint & To        ,
                                  BMAPs        & buttons ) ;
    virtual bool    MouseMove    (ControlPoint & From1     ,
                                  ControlPoint & To1       ,
                                  ControlPoint & From2     ,
                                  ControlPoint & To2       ,
                                  BMAPs        & buttons ) ;

    virtual bool    Spot         (ControlPoint & From ,
                                  ControlPoint & To   ,
                                  ControlPoint & At ) ;

    virtual bool    Menu         (QWidget      * widget ,
                                  QPointF        pos    ,
                                  ControlPoint & From   ,
                                  ControlPoint & To   ) ;

    virtual int     AtRegion     (ControlPoint & At) ;
    virtual QString ToolTip      (void) ;

  protected:

    virtual void    Configure    (void) ;

    virtual void    indexChanged (void) ;

    virtual void    renderLayout (void) ;
    virtual void    renderGauge  (void) ;

    virtual QString ToolTip      (double start,double end,double value) ;

    virtual double  toPosition   (void) ;
    virtual void    toValue      (ControlPoint & At) ;

  private:

  public slots:

    virtual void    setRange     (double start,double end) ;
    virtual void    setStep      (double   step) ;
    virtual void    setCurrent   (qint64   value) ;
    virtual void    setDouble    (double   value) ;
    virtual void    assignValue  (qint64 * value) ;
    virtual void    assignValue  (double * value) ;

    virtual void    Previous     (void) ;
    virtual void    Next         (void) ;

  protected slots:

  private slots:

  signals:

    void valueChanged            (void) ;
    void valueChanged            (SceneObject * object) ;
    void valueChanged            (ValueObject * value ) ;
    void valueChanged            (qint64 value) ;
    void valueChanged            (double value) ;
    void rangeChanged            (double start,double end) ;
    void stepChanged             (double value) ;

} ;

class Q_COMPONENTS_EXPORT PictureObject : public SceneWidget
{
  Q_OBJECT
  public:

    explicit        PictureObject  (QObject * parent,Plan * plan) ;
    explicit        PictureObject  (QObject * parent,Plan * plan,SceneDestructor * destructor) ;
    virtual        ~PictureObject  (void) ;

    virtual void    renderUser     (void) ;

    virtual bool    FocusIn        (void) ;
    virtual bool    FocusOut       (void) ;

    virtual bool    MouseVector    (ControlPoint & From      ,
                                    ControlPoint & To        ,
                                    BMAPs        & buttons ) ;
    virtual bool    MouseHover     (ControlPoint & From      ,
                                    ControlPoint & To        ,
                                    BMAPs        & buttons ) ;
    virtual bool    MouseMove      (ControlPoint & From1     ,
                                    ControlPoint & To1       ,
                                    ControlPoint & From2     ,
                                    ControlPoint & To2       ,
                                    BMAPs        & buttons ) ;

    virtual bool    Spot           (ControlPoint & From ,
                                    ControlPoint & To   ,
                                    ControlPoint & At ) ;

    virtual bool    Menu           (QWidget      * widget ,
                                    QPointF        pos    ,
                                    ControlPoint & From   ,
                                    ControlPoint & To   ) ;

    virtual int     AtRegion       (ControlPoint & At) ;
    virtual QString ToolTip        (void) ;

  protected:

    virtual void    Configure      (void) ;

    virtual void    renderXY       (QRectF & r,double z,QSizeF s) ;
    virtual void    renderXY       (QRectF & r,double z) ;
    virtual void    renderXY       (double z) ;
    virtual void    renderFront    (void) ;
    virtual void    renderBack     (void) ;

    virtual QString ToolTip        (QSize size) ;

    virtual QImage * CurrentImage  (void) ;

  private:

  public slots:

    virtual void    setTexture    (SUID uuid,QImage * image,bool Lod = false) ;
    virtual void    assignTexture (SUID uuid,QImage * image,bool Lod = false) ;
    virtual void    assignUuid    (SUID uuid) ;

  protected slots:

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT IconObject : public PictureObject
{
  Q_OBJECT
  public:

    explicit        IconObject     (QObject * parent,Plan * plan) ;
    explicit        IconObject     (QObject * parent,Plan * plan,SceneDestructor * destructor) ;
    virtual        ~IconObject     (void) ;

    virtual void    renderBox      (void) ;
    virtual void    renderUser     (void) ;

    virtual bool    MouseVector    (ControlPoint & From      ,
                                    ControlPoint & To        ,
                                    BMAPs        & buttons ) ;
    virtual bool    MouseHover     (ControlPoint & From      ,
                                    ControlPoint & To        ,
                                    BMAPs        & buttons ) ;

    virtual QString ToolTip        (void) ;

  protected:

    virtual void    Configure      (void) ;

  private:

  public slots:

    virtual void    setToolTip     (QString tooltip) ;
    virtual void    setIconSize    (QSize size) ;
    virtual void    setIcon        (SUID uuid,QImage * image) ;
    virtual void    setCheckable   (bool enabled) ;
    virtual bool    setChecked     (bool enabled) ;
    virtual bool    isChecked      (void) ;
    virtual void    Pressed        (ControlPoint & At,bool pressed) ;

  protected slots:

  private slots:

  signals:

    void            clicked       (void) ;
    void            released      (void) ;
    void            toggled       (bool enable) ;

} ;

class Q_COMPONENTS_EXPORT TextObject : public IconObject
{
  Q_OBJECT
  public:

    explicit     TextObject   (QObject * parent,Plan * plan) ;
    explicit     TextObject   (QObject * parent,Plan * plan,SceneDestructor * destructor) ;
    virtual     ~TextObject   (void) ;

  protected:

    QFont font ;

    virtual void Configure    (void) ;

    virtual void renderFront  (void) ;
    virtual void renderBack   (void) ;

  private:

  public slots:

    virtual void setTextFlags (int flags) ;
    virtual void setFont      (QFont font) ;
    virtual void setPixelSize (float pixels) ;
    virtual void setTextRange (SUID uuid,QSize size) ;
    virtual void setTextColor (QColor c) ;
    virtual void setText      (QString text) ;

  protected slots:

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT SelectItem : public SceneWidget
{
  Q_OBJECT
  public:

    explicit     SelectItem   (QObject * parent,Plan * plan) ;
    explicit     SelectItem   (QObject * parent,Plan * plan,SceneDestructor * destructor) ;
    virtual     ~SelectItem   (void) ;

    static int   AcceptSelect (void * data,void * dispatcher,QVariants & v) ;

    virtual bool FocusIn      (void) ;
    virtual bool FocusOut     (void) ;

    virtual bool MouseClicked (ControlPoint & From      ,
                               ControlPoint & To        ,
                               BMAPs        & buttons ) ;
    virtual bool MouseVector  (ControlPoint & From      ,
                               ControlPoint & To        ,
                               BMAPs        & buttons ) ;
    virtual bool MouseHover   (ControlPoint & From      ,
                               ControlPoint & To        ,
                               BMAPs        & buttons ) ;
    virtual bool MouseMove    (ControlPoint & From1     ,
                               ControlPoint & To1       ,
                               ControlPoint & From2     ,
                               ControlPoint & To2       ,
                               BMAPs        & buttons ) ;
    virtual bool Spot         (ControlPoint & From ,
                               ControlPoint & To   ,
                               ControlPoint & At ) ;

  protected:

    virtual void Configure    (void) ;

    virtual void DecideShell  (void) ;

  private:

  public slots:

    virtual int  addItem      (IconObject * item) ;
    virtual void setCheckable (bool enabled) ;
    virtual bool setChecked   (bool enabled) ;
    virtual bool isChecked    (void) ;

    virtual int  Selecting    (SceneObject * sox,QVariants & v) ;

  protected slots:

  private slots:

  signals:

    void            doubleClicked (void) ;
    void            clicked       (void) ;
    void            released      (void) ;
    void            toggled       (bool enable) ;

} ;

class Q_COMPONENTS_EXPORT ProgressButton : public SceneWidget
{
  Q_OBJECT
  public:

    explicit        ProgressButton (QObject * parent,Plan * plan) ;
    explicit        ProgressButton (QObject * parent,Plan * plan,SceneDestructor * destructor) ;
    virtual        ~ProgressButton (void) ;

    virtual bool    FocusIn        (void) ;
    virtual bool    FocusOut       (void) ;

    virtual bool    MouseVector    (ControlPoint & From      ,
                                    ControlPoint & To        ,
                                    BMAPs        & buttons ) ;
    virtual bool    MouseHover     (ControlPoint & From      ,
                                    ControlPoint & To        ,
                                    BMAPs        & buttons ) ;
    virtual bool    Spot           (ControlPoint & From ,
                                    ControlPoint & To   ,
                                    ControlPoint & At ) ;
    virtual int     AtRegion       (ControlPoint & At) ;

    virtual QString ToolTip        (void) ;

    virtual void    renderUser     (void) ;

  protected:

    ProgressReporter * reporter ;

    virtual void    Configure      (void) ;

    virtual double  Radius         (void) ;
    virtual void    renderDonut    (ControlPoint & center    ,
                                    double         R1        ,
                                    double         R2        ,
                                    double         Z1        ,
                                    double         Z2        ,
                                    double         completed ,
                                    int            op      ) ;
    virtual void    renderDonut    (void) ;
    virtual void    renderPause    (void) ;
    virtual void    renderButton   (void) ;

    virtual void    ButtonReleased (void) ;

  private:

  public slots:

    virtual bool    isAttached     (void) ;
    virtual void    setReporter    (ProgressReporter * reporter) ;
    virtual void    Toggle         (void) ;
    virtual void    PauseOrResume  (void) ;

  protected slots:

  private slots:

  signals:

    void            Starting       (void) ;
    void            Complete       (void) ;
    void            Pause          (void) ;
    void            Resume         (void) ;

} ;


#define AllowPickItemMenu                                           \
  ControlPoint At                                                 ; \
  {                                                                 \
    bool answer = false                                           ; \
    if ( ! AllowMenu ( widget , pos , From , To , At , answer ) ) { \
      return answer                                               ; \
    }                                                               \
  }

#define RunPickItemMenu                       \
  {                                           \
    mm . addSeparator (                   ) ; \
    CallToMenu        ( mm , NULL , false ) ; \
    mm  . setFont     ( plan              ) ; \
    aa  = mm . exec   (                   ) ; \
  }

class Q_COMPONENTS_EXPORT PickItem : public SceneWidget
{
  Q_OBJECT
  public:

    explicit      PickItem          (QObject * parent,Plan * plan) ;
    explicit      PickItem          (QObject * parent,Plan * plan,SceneDestructor * destructor) ;
    virtual      ~PickItem          (void) ;

    virtual void  render            (Camera & camera,QMap<int,Matrix> & matrices) ;
    virtual void  renderFaces       (void) ;

    static int    AcceptSelect      (void * data,void * dispatcher,QVariants & v) ;
    static int    AcceptIndexing    (void * data,void * dispatcher,QVariants & v) ;

    virtual bool  FocusIn           (void) ;
    virtual bool  FocusOut          (void) ;

    virtual bool  MouseClicked      (ControlPoint & From      ,
                                     ControlPoint & To        ,
                                     BMAPs        & buttons ) ;
    virtual bool  MouseVector       (ControlPoint & From      ,
                                     ControlPoint & To        ,
                                     BMAPs        & buttons ) ;
    virtual bool  MouseHover        (ControlPoint & From      ,
                                     ControlPoint & To        ,
                                     BMAPs        & buttons ) ;
    virtual bool  MouseMove         (ControlPoint & From1     ,
                                     ControlPoint & To1       ,
                                     ControlPoint & From2     ,
                                     ControlPoint & To2       ,
                                     BMAPs        & buttons ) ;
    virtual bool  Spot              (ControlPoint & From ,
                                     ControlPoint & To   ,
                                     ControlPoint & At ) ;
    virtual int   AtRegion          (ControlPoint & At) ;

    virtual SelectItem     * CurrentItem  (void) ;
    virtual SelectItem     * NearestItem  (ControlPoint & From,ControlPoint & To) ;
    virtual SelectItem     * New          (void) ;
    virtual SelectItem     * NewIcon      (QImage * image,QSize size) ;
    virtual SelectItem     * NewItem      (QString text,QImage * image,QSize size) ;
    virtual SelectItem     * NewText      (QString text,QSize size) ;
    virtual IconObject     * IconItem     (SelectItem * item) ;
    virtual TextObject     * TextItem     (SelectItem * item) ;
    virtual TextObject     * GetTitle     (void) ;
    virtual IconObject     * AddButton    (void) ;
    virtual IconObject     * NewButton    (QImage * image,QSize size) ;
    virtual ProgressButton * ProgressTool (void) ;
    virtual RangeBar       * ScrollBar    (void) ;
    virtual RangeBar       * ScrollBar    (Qt::Orientation orientation) ;
    virtual bool             setScrollBar (Qt::Orientation orientation,bool enabled) ;

    virtual int   lineCount         (void) ;
    virtual int   columnCount       (void) ;
    virtual int   depthCount        (void) ;

    virtual bool  isInside          (ControlPoints & Box,SelectItem * item) ;

    virtual void  ClosePad          (SUID uuid) ;

    virtual SUID  OnItem            (ControlPoint & From ,
                                     ControlPoint & To   ,
                                     ControlPoint & At ) ;

    virtual bool  dropNew           (QWidget         * widget ,
                                     const QMimeData * mime   ,
                                     ControlPoint    & From   ,
                                     ControlPoint    & To     ,
                                     ControlPoint    & At   ) ;
    virtual bool  dropMoving        (QWidget         * widget ,
                                     const QMimeData * mime   ,
                                     ControlPoint    & From   ,
                                     ControlPoint    & To     ,
                                     ControlPoint    & At   ) ;
    virtual bool  dropAppend        (QWidget         * widget ,
                                     const QMimeData * mime   ,
                                     ControlPoint    & From   ,
                                     ControlPoint    & To     ,
                                     ControlPoint    & At   ) ;
    virtual bool  removeDrop        (void) ;

  protected:

    UUIDs            CurrentItems    ;
    UUIDs            PadItems        ;
    qint64           horizontalIndex ;
    qint64           verticalIndex   ;
    Camera         * UsingCamera     ;
    QMap<int,Matrix> UsingMatrix     ;

    virtual UUIDs SelectedItems     (void) ;
    virtual bool  beginDrag         (ControlPoint & From ,
                                     ControlPoint & To   ,
                                     ControlPoint & At ) ;

    virtual void  Configure         (void) ;

    virtual void  doSelection       (SelectItem * item) ;
    virtual void  CleanItems        (void) ;

    virtual void  MarkSelections    (void) ;
    virtual void  ItemSelections    (void) ;
    virtual void  AssignCursor      (int region) ;
    virtual void  ArrangeScrollBars (void) ;
    virtual void  ArrangeTitle      (void) ;
    virtual void  ArrangePads       (void) ;
    virtual void  ArrangeItem       (SUID   uuid     ,
                                     qint64 position ,
                                     qint64 columns  ,
                                     qint64 rows   ) ;
    virtual void  ArrangeItems      (qint64 startId,UUIDs & U) ;
    virtual void  RearrangeItems    (UUIDs & Items) ;
    virtual void  UpdateVScroll     (qint64 total) ;
    virtual void  UpdateHScroll     (qint64 total) ;
    virtual bool  AllowMenu         (QWidget      * widget   ,
                                     QPointF        pos      ,
                                     ControlPoint & From     ,
                                     ControlPoint & To       ,
                                     ControlPoint & At       ,
                                     bool         & answer ) ;

    virtual bool  LocalClicked      (ControlPoint & From      ,
                                     ControlPoint & To        ,
                                     ControlPoint & At        ,
                                     BMAPs        & buttons   ,
                                     bool           after     ,
                                     bool           overlap ) ;
    virtual bool  LocalVector       (ControlPoint & From      ,
                                     ControlPoint & To        ,
                                     ControlPoint & At        ,
                                     BMAPs        & buttons   ,
                                     bool           after     ,
                                     bool           overlap ) ;
    virtual bool  LocalHover        (ControlPoint & From      ,
                                     ControlPoint & To        ,
                                     ControlPoint & At        ,
                                     BMAPs        & buttons   ,
                                     bool           after     ,
                                     bool           overlap ) ;

  private:

  public slots:

    virtual void  setBase           (ControlPoint & base) ;
    virtual void  setBox            (ControlPoint & box) ;
    virtual void  setGap            (ControlPoint & gap) ;
    virtual void  setAppear         (ControlPoint & appear) ;
    virtual void  setDefaultMin     (ControlPoint & minp) ;
    virtual void  setDefaultMax     (ControlPoint & maxp) ;
    virtual void  setContainer      (ControlPoint & minp,ControlPoint & maxp) ;
    virtual void  setTitle          (QString title) ;
    virtual void  SortBy            (int orderby,QString item = "position") ;
    virtual void  setAccess         (QString method) ;

    virtual int   addItem           (SelectItem * item,bool bounding = true) ;

    virtual int   Selecting         (SelectItem * sox,QVariants & v) ;
    virtual int   Indexing          (RangeBar   * rbu,int direction,QVariants & v) ;

    virtual bool  prepare           (void) ;
    virtual bool  startup           (void) ;

  protected slots:

    virtual void atDoubleClicked    (SelectItem * item) ;
    virtual void atClicked          (SelectItem * item) ;
    virtual void atSelected         (SelectItem * item) ;
    virtual void atSelectClicked    (SelectItem * item) ;

  private slots:

  signals:

    void          Clicked           (SelectItem * item) ;
    void          SelectClicked     (SelectItem * item) ;
    void          DoubleClicked     (SelectItem * item) ;
    void          Selected          (SelectItem * item) ;

} ;

class Q_COMPONENTS_EXPORT PickBox : public PickItem
{
  Q_OBJECT
  public:

    explicit     PickBox           (QObject * parent,Plan * plan) ;
    explicit     PickBox           (QObject * parent,Plan * plan,SceneDestructor * destructor) ;
    virtual     ~PickBox           (void) ;

    virtual void renderBox         (void) ;

  protected:

    UUIDs RealItems  ;
    SMAPs RealToView ;
    NAMEs ViewNames  ;

    virtual void Configure         (void) ;

    virtual void run               (int type,ThreadData * data) ;
    virtual bool ItemRunner        (int type,ThreadData * data) ;

    virtual void BoxChanged        (bool hover) ;
    virtual void FinalizeSelection (void) ;
    virtual void ArrangeItems      (void) ;
    virtual void ArrangeName       (void) ;
    virtual void ArrangeLanguage   (void) ;
    virtual void ArrangeNames      (void) ;
    virtual void RearrangeItems    (void) ;
    virtual void UpdateScrollPages (qint64 total) ;
    virtual void ScrollByStart     (qint64 total) ;
    virtual void ScrollByCurrent   (qint64 total) ;

  private:

  public slots:

    virtual bool prepare           (void) ;
    virtual bool startup           (void) ;

    virtual bool LoadItems         (void) ;
    virtual bool LoadFull          (void) ;
    virtual bool LoadDivisions     (void) ;
    virtual bool LoadLimits        (void) ;
    virtual bool LoadFirst         (void) ;
    virtual bool LoadSecond        (void) ;
    virtual bool ReportDetails     (void) ;

  protected slots:

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT ListBox : public PickBox
{
  Q_OBJECT
  public:

    explicit     ListBox   (QObject * parent,Plan * plan) ;
    explicit     ListBox   (QObject * parent,Plan * plan,SceneDestructor * destructor) ;
    virtual     ~ListBox   (void) ;

  protected:

    virtual void Configure (void) ;

  private:

  public slots:

    virtual void addItem   (SUID uuid,QString text) ;

  protected slots:

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT ListShelf : public ListBox
{
  Q_OBJECT
  public:

    explicit     ListShelf (QObject * parent,Plan * plan) ;
    explicit     ListShelf (QObject * parent,Plan * plan,SceneDestructor * destructor) ;
    virtual     ~ListShelf (void) ;

  protected:

    virtual void Configure (void) ;

  private:

  public slots:

  protected slots:

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT NamesShelf : public ListShelf
{
  Q_OBJECT
  public:

    explicit     NamesShelf (QObject * parent,Plan * plan) ;
    explicit     NamesShelf (QObject * parent,Plan * plan,SceneDestructor * destructor) ;
    virtual     ~NamesShelf (void) ;

  protected:

    virtual void Configure  (void) ;

  private:

  public slots:

  protected slots:

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT CameraShelf : public NamesShelf
{
  Q_OBJECT
  public:

    explicit     CameraShelf       (QObject * parent,Plan * plan) ;
    explicit     CameraShelf       (QObject * parent,Plan * plan,SceneDestructor * destructor) ;
    virtual     ~CameraShelf       (void) ;

  protected:

    virtual void Configure         (void) ;

    virtual void run               (int type,ThreadData * data) ;

    virtual void BoxChanged        (bool hover) ;
    virtual void FinalizeSelection (void) ;

  private:

  public slots:

    virtual bool prepare           (void) ;
    virtual bool startup           (void) ;
    virtual void setCameras        (SUID current,NAMEs & cameras) ;

    virtual int  Selecting         (SelectItem * sox,QVariants & v) ;
    virtual int  Indexing          (RangeBar * rbu,int direction,QVariants & v) ;

  protected slots:

    virtual void atDoubleClicked   (SelectItem * item) ;
    virtual void CloseSelection    (void) ;

  private slots:

  signals:

} ;

class Q_COMPONENTS_EXPORT Trademark : public SceneWidget
{
  Q_OBJECT
  public:

    static QScriptValue TrademarkAttachment (QScriptContext * context,QScriptEngine * engine) ;

    explicit     Trademark      (QObject * parent,Plan * plan) ;
    explicit     Trademark      (QObject * parent,Plan * plan,SceneDestructor * destructor) ;
    virtual     ~Trademark      (void) ;

    virtual void renderSegments (void) ;
    virtual void renderFaces    (void) ;

    virtual bool FocusIn        (void) ;
    virtual bool FocusOut       (void) ;

    virtual bool MouseVector    (ControlPoint & From      ,
                                 ControlPoint & To        ,
                                 BMAPs        & buttons ) ;
    virtual bool MouseHover     (ControlPoint & From      ,
                                 ControlPoint & To        ,
                                 BMAPs        & buttons ) ;
    virtual bool MouseMove      (ControlPoint & From1     ,
                                 ControlPoint & To1       ,
                                 ControlPoint & From2     ,
                                 ControlPoint & To2       ,
                                 BMAPs        & buttons ) ;

    virtual bool Spot           (ControlPoint & From ,
                                 ControlPoint & To   ,
                                 ControlPoint & At ) ;

    virtual bool Menu           (QWidget      * widget ,
                                 QPointF        pos    ,
                                 ControlPoint & From   ,
                                 ControlPoint & To   ) ;

    virtual int  AtRegion       (ControlPoint & At) ;

  protected:

    PackedPoint * packedPoints ;
    int         * lines        ;
    int         * faces        ;

    virtual void Configure      (void) ;

  private:

  public slots:

    virtual void setPoints      (PackedPoint * points) ;
    virtual void setLines       (int         * lines ) ;
    virtual void setFaces       (int         * faces ) ;
    virtual void setLength      (double        length) ;

  protected slots:

  private slots:

  signals:

} ;

}

Q_COMPONENTS_EXPORT void operator <= (QComboBox   & Combo    , QString        name      ) ;
Q_COMPONENTS_EXPORT void operator <= (QComboBox   & Combo    , int            id        ) ;
Q_COMPONENTS_EXPORT void operator <= (QComboBox   & Combo    , SUID           uuid      ) ;
Q_COMPONENTS_EXPORT void operator << (QComboBox   * Combo    , NAMEs        & names     ) ;
Q_COMPONENTS_EXPORT void operator << (QComboBox   * Combo    , N::Languages & languages ) ;
Q_COMPONENTS_EXPORT void operator  , (QComboBox   & Combo    , N::Plan      & plan      ) ;
Q_COMPONENTS_EXPORT void operator  , (QTreeWidget & Tree     , N::Plan      & plan      ) ;
Q_COMPONENTS_EXPORT void operator << (QTreeWidget * Tree     , N::Languages & languages ) ;
Q_COMPONENTS_EXPORT void operator <= (QLineEdit   & lineEdit , QString        name      ) ;

Q_DECLARE_METATYPE  ( QShortcuts          )
Q_DECLARE_METATYPE  ( N::FullSettings     )
Q_DECLARE_METATYPE  ( N::Plan             )
Q_DECLARE_METATYPE  ( N::GraphicsManager  )
Q_DECLARE_METATYPE  ( N::GroupItems       )
Q_DECLARE_METATYPE  ( N::FileDeputy       )
Q_DECLARE_METATYPE  ( N::TreeWidgetItems  )
Q_DECLARE_METATYPE  ( N::TreeWidgetMaps   )
Q_DECLARE_METATYPE  ( N::ListWidgetItems  )
Q_DECLARE_METATYPE  ( N::ListWidgetMaps   )
Q_DECLARE_METATYPE  ( N::TableWidgetItems )
Q_DECLARE_METATYPE  ( N::TableWidgetMaps  )
Q_DECLARE_METATYPE  ( N::Widgets          )
Q_DECLARE_METATYPE  ( N::Actions          )
Q_DECLARE_METATYPE  ( N::NamedActions     )
Q_DECLARE_METATYPE  ( N::MENUs            )
Q_DECLARE_METATYPE  ( N::Pathes           )
Q_DECLARE_METATYPE  ( N::VcfFont          )
Q_DECLARE_METATYPE  ( N::VcfOptions       )
Q_DECLARE_METATYPE  ( N::VcfShape         )
Q_DECLARE_METATYPE  ( N::VcfPainter       )
Q_DECLARE_METATYPE  ( N::VcfPaperConf     )
Q_DECLARE_METATYPE  ( N::VcfProxys        )
Q_DECLARE_METATYPE  ( N::VcfWidgets       )
Q_DECLARE_METATYPE  ( N::VcfPoints        )
Q_DECLARE_METATYPE  ( N::VcfRectangles    )
Q_DECLARE_METATYPE  ( N::VcfItems         )
Q_DECLARE_METATYPE  ( N::VcfMaps          )
Q_DECLARE_METATYPE  ( N::VcfLinkers       )
Q_DECLARE_METATYPE  ( N::VcfNodes         )
Q_DECLARE_METATYPE  ( N::DataRetrievers   )
Q_DECLARE_METATYPE  ( N::CvClassifiers    )

Q_DECLARE_INTERFACE ( N::SqlPlugin      , "com.neutrino.sql.plugins"        )
Q_DECLARE_INTERFACE ( N::MonitorPlugin  , "com.neutrino.system.monitor"     )
Q_DECLARE_INTERFACE ( N::HunterPlugin   , "com.neutrino.network.hunter"     )
Q_DECLARE_INTERFACE ( N::DocumentPlugin , "com.neutrino.document.processor" )
Q_DECLARE_INTERFACE ( N::DataRetriever  , "com.neutrino.gui.retriever"      )

QT_END_NAMESPACE

#endif
