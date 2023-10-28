#include "MainWindow.h"
#include <ui_mainwindow.h>

#include <QCloseEvent>
#include <QMessageBox>

CMainWindow::CMainWindow() : QMainWindow(NULL)
{
	m_pUI = new Ui::MainWindow();
	m_pUI->setupUi(this);

	m_pMainTab = new CMainTab();
	m_pConsoleTab = new CConsoleTab();
	m_pSessionTab = new CSessionTab();
	m_pRoomListTab = new CRoomListTab();

	m_pUI->tabWidget->addTab(m_pMainTab, "MainTab");
	m_pUI->tabWidget->addTab(m_pConsoleTab, "ConsoleTab");
	m_pUI->tabWidget->addTab(m_pSessionTab, "SessionTab");
	m_pUI->tabWidget->addTab(m_pRoomListTab, "RoomListTab");
}

CMainWindow::~CMainWindow()
{
	delete m_pUI;
	delete m_pMainTab;
	delete m_pConsoleTab;
	delete m_pSessionTab;
	delete m_pRoomListTab;
}

CMainTab* CMainWindow::GetMainTab()
{
	return m_pMainTab;
}

CConsoleTab* CMainWindow::GetConsoleTab()
{
	return m_pConsoleTab;
}

void CMainWindow::ShowMessageBox(const std::string& title, const std::string& msg, bool fatalError)
{
	if (fatalError)
	{
		QMessageBox::critical(this, QString::fromStdString(title), QString::fromStdString(msg));
		QApplication::exit();
	}
	else
	{
		QMessageBox::information(this, QString::fromStdString(title), QString::fromStdString(msg));
	}
}

// handle close event to warn user that there are still users on the server
void CMainWindow::closeEvent(QCloseEvent* event)
{
	QMessageBox msgBox;
	QPushButton* quitAndSendMaintenanceMsgBtn = msgBox.addButton("Quit and send maintenance message", QMessageBox::ActionRole);
	QPushButton* quitBtn = msgBox.addButton("Quit", QMessageBox::ActionRole);
	QPushButton* cancelBtn = msgBox.addButton(QMessageBox::Cancel);
	msgBox.setWindowTitle("Quit");
	msgBox.setText("Do you wish to stop the server now?");

	msgBox.exec();

	if (msgBox.clickedButton() == (QAbstractButton*)quitAndSendMaintenanceMsgBtn)
	{
		// send maintenance msg to all users and quit
		event->accept();
	}
	else if (msgBox.clickedButton() == (QAbstractButton*)quitBtn)
	{
		// just quit
		event->accept();
	}
	else
	{
		event->ignore();
	}
}