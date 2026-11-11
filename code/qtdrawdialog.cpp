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
#include "qtdrawdialog.h"

#include <algorithm>

#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>

QtDrawDialog::QtDrawDialog(
  const std::array<double, n_leary_scores>& scores,
  const std::array<std::string, n_leary_scores>& legend,
  QWidget* parent)
  : QWidget(parent),
    m_label{new QLabel},
    m_scores{scores},
    m_legend{legend},
    m_image{}
{
  setWindowTitle(QString::fromUtf8("Leary Circumplex (C) 2009 Richèl Bilderbeek"));
  m_label->setAlignment(Qt::AlignCenter);
  m_label->setMinimumSize(100, 100);
  QVBoxLayout* const layout = new QVBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(m_label);
  resize(422, 356);
  Redraw();
}

void QtDrawDialog::resizeEvent(QResizeEvent* event)
{
  QWidget::resizeEvent(event);
  Redraw();
}

void QtDrawDialog::Redraw()
{
  const int size = std::min(m_label->width(), m_label->height());
  m_image = DrawLearyCircumplex(m_scores, m_legend, size);
  m_label->setPixmap(QPixmap::fromImage(m_image));
}
