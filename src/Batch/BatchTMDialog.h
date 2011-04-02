/**
 * This file is a part of LuminanceHDR package.
 * ---------------------------------------------------------------------- 
 * Copyright (C) 2007 Giuseppe Rota
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * ---------------------------------------------------------------------- 
 *
 * Original Work
 * @author Giuseppe Rota <grota@users.sourceforge.net>
 * Improvements, bugfixing 
 * @author Franco Comida <fcomida@users.sourceforge.net>
 *
 */

#ifndef BATCH_IMPL_H
#define BATCH_IMPL_H

#include <QVector>
#include <QStringListModel>
#include <QSortFilterProxyModel>
#include <QFuture>
#include <QMutex>
#include <QSemaphore> 
#include <QtGui/QCloseEvent> 

#include "ui_BatchTMDialog.h"

#include "Batch/BatchTMJob.h"
#include "Common/options.h"
#include "Common/global.h"
#include "Libpfs/pfs.h"
#include "Threads/LoadHdrThread.h"
#include "Threads/TMOFactory.h"

class BatchTMDialog : public QDialog, public Ui::BatchTMDialog
{
Q_OBJECT

public:
	BatchTMDialog(QWidget *parent = 0);
	~BatchTMDialog();
// protected:
private slots:
	void add_dir_HDRs();
	void add_HDRs();
	void add_dir_TMopts();
	void add_TMopts();
	void out_folder_clicked();
	void check_enable_start();
	void remove_HDRs();
	void remove_TMOpts();
  void filterChanged(const QString&);
	void filterComboBoxActivated(int);

  //fuction that adds a log message to the model
	void add_log_message(const QString &);
  
  void batch_core();
  void release_thread(int t_id);
  void start_batch_thread(); 
  void stop_batch_tm_ui();
  void increment_progress_bar(int);
protected:
  void closeEvent(QCloseEvent *);
private:
  //Parses a TM_opts file (return NULL on error)
	TonemappingOptions* parse_tm_opt_file(QString filename); 
  
  //required for the cache path
  LuminanceOptions *luminance_options;
  
	//selection start/stop left/right
  //TODO: remove this rubbish, thanks!
	int start_left;
  int stop_left;
  int start_right;
  int stop_right;
  
	//Application-wide settings, loaded via QSettings
	QString RecentDirHDRSetting, RecentPathLoadSaveTmoSettings, recentPathSaveLDR;  
  
  //data structure (model) for left-side list: HDRs
	QStringList HDRs_list;
  
  // the class that performs regexp filtering
  QSortFilterProxyModel * log_filter;
  
  // the model that holds the data
	QStringListModel    * full_Log_Model;
	TonemappingOptions  * opts;
  
  QMutex          m_add_log_message_mutex;
  
  QList< TonemappingOptions* > m_tm_options_list;
  
  // Davide Anastasia <davideanastasia@users.sourceforge.net>
  //Max number of threads allowed
  int             m_max_num_threads;
  QSemaphore      m_thread_slot;
  QMutex          m_thread_control_mutex;
  QMutex          m_class_data_mutex;
  bool            m_is_batch_running;
  bool        *   m_available_threads;
  int             m_next_hdr_file;
  
  int   get_available_thread_id();

  void  init_batch_tm_ui();
  //when removing we cycle through the list to grab the selected interval
	void update_selection_interval(bool left);
  //updates graphica widget (view) and data structure (model) for HDR list
	void add_view_model_HDRs(QStringList);
  //updates graphica widget (view) and data structure (model) for TM_opts list
	void add_view_model_TM_OPTs(QStringList);
};
#endif
