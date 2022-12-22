/*
 * Rosalie's Mupen GUI - https://github.com/Rosalie241/RMG
 *  Copyright (C) 2020 Rosalie Wanders <rosalie@mailbox.org>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 3.
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef ROMBROWSERWIDGET_HPP
#define ROMBROWSERWIDGET_HPP

#include "Thread/RomSearcherThread.hpp"
#include "UserInterface/NoFocusDelegate.hpp"

#include "RomBrowserListViewWidget.hpp"
#include "RomBrowserGridViewWidget.hpp"
#include "RomBrowserLoadingWidget.hpp"
#include "RomBrowserEmptyWidget.hpp"

#include <QHeaderView>
#include <QList>
#include <QStandardItemModel>
#include <QString>
#include <QTableView>
#include <QMenu>
#include <QAction>
#include <QGridLayout>
#include <QListWidget>
#include <QStackedWidget>

namespace UserInterface
{
namespace Widget
{
class RomBrowserWidget : public QStackedWidget
{
    Q_OBJECT

  public:
    RomBrowserWidget(QWidget *);
    ~RomBrowserWidget(void);

    void RefreshRomList(void);
    bool IsRefreshingRomList(void);
    void StopRefreshRomList(void);

    void ShowList(void);
    void ShowGrid(void);

  private:
    Widget::RomBrowserEmptyWidget*    emptyWidget    = nullptr;
    Widget::RomBrowserLoadingWidget*  loadingWidget  = nullptr;

    Widget::RomBrowserListViewWidget* listViewWidget = nullptr;
    QStandardItemModel* listViewModel                = nullptr;
    Widget::RomBrowserGridViewWidget* gridViewWidget = nullptr;
    QStandardItemModel* gridViewModel                = nullptr;

    QWidget* currentViewWidget = nullptr;

    QElapsedTimer romSearcherTimer;
    Thread::RomSearcherThread* romSearcherThread = nullptr;

    int listViewSortSection = 0;
    int listViewSortOrder = 0;

    QMenu*   contextMenu;
    QAction* action_PlayGame;
    QAction* action_PlayGameWithDisk;
    QAction* action_RefreshRomList;
    QAction* action_ChooseRomDirectory;
    QAction* action_RomInformation;
    QAction* action_EditGameSettings;
    QAction* action_EditCheats;

    QString coversDirectory;

    QStandardItemModel* getCurrentModel(void);
    QAbstractItemView*  getCurrentModelView(void);

    QString getCurrentRom(void);

    QIcon getCurrentCover(CoreRomHeader header, CoreRomSettings settings);

  protected:
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;

  private slots:
    void on_DoubleClicked(const QModelIndex& index);
    void customContextMenuRequested(QPoint point);

    void on_listViewWidget_sortIndicatorChanged(int logicalIndex, Qt::SortOrder sortOrder);
    void on_gridViewWidget_iconSizeChanged(const QSize& size);

    void on_ZoomIn(void);
    void on_ZoomOut(void);

    void on_RomBrowserThread_RomFound(QString file, CoreRomHeader header, CoreRomSettings settings);
    void on_RomBrowserThread_Finished(bool canceled);

    void on_Action_PlayGame(void);
    void on_Action_PlayGameWithDisk(void);
    void on_Action_RefreshRomList(void);
    void on_Action_ChooseRomDirectory(void);
    void on_Action_RomInformation(void);
    void on_Action_EditGameSettings(void);
    void on_Action_EditCheats(void);

  signals:
    void PlayGame(QString);
    void PlayGameWithDisk(QString);
    void FileDropped(QDropEvent *);
    void EditGameSettings(QString);
    void Cheats(QString);
    void ChooseRomDirectory(void);
    void RomInformation(QString);
};
} // namespace Widget
} // namespace UserInterface

#endif // ROMBROWSERWIDGET_HPP
