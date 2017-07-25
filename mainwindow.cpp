#include "mainwindow.h"

#include <QVBoxLayout>

#include <DTitlebar>
#include <QCheckBox>
#include <QDebug>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    :DMainWindow(parent) {
    setMinimumSize(1050, 850);
    setMouseTracking(false);
    m_topToolbar = new TopToolbar(this);
    titlebar()->setCustomWidget(m_topToolbar, Qt::AlignCenter);
    m_titlebarWidth = titlebar()->width();
    m_topToolbar->setFixedWidth(this->width() - m_titlebarWidth);

    m_mainWidget = new MainWidget(this);
    m_mainWidget->setFocusPolicy(Qt::StrongFocus);
    setContentsMargins(QMargins(0, 0, 0, 0));
    setCentralWidget(m_mainWidget);

    connect(m_topToolbar, &TopToolbar::openImage,
                    m_mainWidget, &MainWidget::setImageInCanvas);
    connect(m_topToolbar, &TopToolbar::initShapeWidgetAction,
            m_mainWidget, &MainWidget::prepareInitShapesWidget);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    DMainWindow::resizeEvent(event);
    m_topToolbar->setFixedWidth(this->width() -  m_titlebarWidth);

    this->update();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->modifiers() == Qt::ShiftModifier && event->key() == Qt::Key_Plus) {
        emit m_mainWidget->zoomOutAction();
    } else if (event->key() == Qt::Key_Minus) {
        emit m_mainWidget->zoomInAction();
    }

    DMainWindow::keyPressEvent(event);
}

MainWindow::~MainWindow() {

}
