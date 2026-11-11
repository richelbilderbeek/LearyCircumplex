/*
  Leary Circumplex, tool to draw a Leary circumplex
  Copyright (C) 2009-2026  Richel Bilderbeek

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// From http://www.richelbilderbeek.nl
#include "qtmaindialog.h"

#include <array>
#include <string>
#include <utility>

#include <QBuffer>
#include <QByteArray>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>

#include "learycircumplex.h"
#include "qtaboutdialog.h"
#include "qtdrawdialog.h"

namespace {

/// Show a message box without blocking.
/// A blocking (nested) event loop does not work in a web browser
void ShowMessage(
  QWidget* const parent,
  const QMessageBox::Icon icon,
  const QString& title,
  const QString& text)
{
  QMessageBox* const box = new QMessageBox(icon, title, text, QMessageBox::Ok, parent);
  box->setAttribute(Qt::WA_DeleteOnClose);
  box->open();
}

} // namespace

QtMainDialog::QtMainDialog(QWidget* parent)
  : QDialog(parent),
    m_table{new QTableWidget(n_leary_scores, 2)},
    m_draw_dialog{}
{
  setWindowTitle(QString::fromUtf8("LearyCircumplex (C) 2009 Richèl Bilderbeek"));

  m_table->setHorizontalHeaderLabels({"Legend", "Score"});
  m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  m_table->verticalHeader()->hide();
  const std::array<std::pair<const char*, const char*>, n_leary_scores> defaults{{
    {"BS", "5.3"}, {"SB", "6.2"}, {"SO", "6.6"}, {"OS", "5.8"},
    {"OT", "2.9"}, {"TO", "2.8"}, {"TB", "2.6"}, {"BT", "3.7"}
  }};
  for (int i = 0; i != n_leary_scores; ++i)
  {
    m_table->setItem(i, 0, new QTableWidgetItem(defaults[i].first));
    m_table->setItem(i, 1, new QTableWidgetItem(defaults[i].second));
  }

  QPushButton* const button_draw = new QPushButton("Draw");
  QPushButton* const button_save = new QPushButton("Save");
  QPushButton* const button_about = new QPushButton("About");
  connect(button_draw, &QPushButton::clicked, this, &QtMainDialog::OnDraw);
  connect(button_save, &QPushButton::clicked, this, &QtMainDialog::OnSave);
  connect(button_about, &QPushButton::clicked, this, &QtMainDialog::OnAbout);

  QVBoxLayout* const buttons = new QVBoxLayout;
  buttons->addWidget(button_draw);
  buttons->addWidget(button_save);
  buttons->addStretch();
  buttons->addWidget(button_about);

  QHBoxLayout* const layout = new QHBoxLayout(this);
  layout->addWidget(m_table);
  layout->addLayout(buttons);
  resize(340, 300);
}

QtMainDialog::~QtMainDialog() = default;

void QtMainDialog::OnDraw()
{
  std::array<double, n_leary_scores> scores;
  std::array<std::string, n_leary_scores> legend;
  for (int i = 0; i != n_leary_scores; ++i)
  {
    const QTableWidgetItem* const legend_item = m_table->item(i, 0);
    const QTableWidgetItem* const score_item = m_table->item(i, 1);
    legend[i] = legend_item ? legend_item->text().toStdString() : std::string();
    bool ok = false;
    const double score = score_item
      ? score_item->text().replace(',', '.').toDouble(&ok)
      : 0.0;
    if (!ok || score < 0.0 || score > 10.0)
    {
      ShowMessage(
        this,
        QMessageBox::Warning,
        "Invalid score",
        QString("Score on row %1 must be a number from 0.0 to 10.0").arg(i + 1)
      );
      return;
    }
    scores[i] = score / 10.0; //In the Netherlands, scores range from [0.0,10.0]
  }
  m_draw_dialog = std::make_unique<QtDrawDialog>(scores, legend);
  //Put the drawing next to this dialog
  m_draw_dialog->move(frameGeometry().right() + 10, frameGeometry().top());
  m_draw_dialog->show();
}

void QtMainDialog::OnSave()
{
  if (!m_draw_dialog)
  {
    ShowMessage(
      this,
      QMessageBox::Information,
      "Nothing to save",
      "Please draw a Leary circumplex first"
    );
    return;
  }
#ifdef Q_OS_WASM
  //In a web browser, let the browser download the image
  QByteArray data;
  QBuffer buffer(&data);
  buffer.open(QIODevice::WriteOnly);
  m_draw_dialog->GetImage().save(&buffer, "PNG");
  QFileDialog::saveFileContent(data, "leary_circumplex.png");
#else
  const QString filename = QFileDialog::getSaveFileName(
    this,
    "Please select a filename to save your Leary Circumplex",
    "leary_circumplex.png",
    "PNG image (*.png);;24-bit bitmap (*.bmp)"
  );
  if (filename.isEmpty()) return;
  if (!m_draw_dialog->GetImage().save(filename))
  {
    ShowMessage(
      this,
      QMessageBox::Warning,
      "Save failed",
      "Could not save image as " + filename
    );
    return;
  }
  ShowMessage(this, QMessageBox::Information, "Saved", "Image saved as " + filename);
#endif
}

void QtMainDialog::OnAbout()
{
  QtAboutDialog* const d = new QtAboutDialog(this);
  d->setAttribute(Qt::WA_DeleteOnClose);
  d->open();
}
