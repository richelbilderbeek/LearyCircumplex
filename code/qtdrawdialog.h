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
#ifndef QTDRAWDIALOG_H
#define QTDRAWDIALOG_H

#include <array>
#include <string>

#include <QImage>
#include <QWidget>

#include "learycircumplex.h"

class QLabel;

/// Window that displays a Leary circumplex, redrawn when resized
class QtDrawDialog : public QWidget
{
  Q_OBJECT

public:
  QtDrawDialog(
    const std::array<double, n_leary_scores>& scores,
    const std::array<std::string, n_leary_scores>& legend,
    QWidget* parent = nullptr
  );

  /// The currently displayed image
  const QImage& GetImage() const noexcept { return m_image; }

protected:
  void resizeEvent(QResizeEvent* event) override;

private:
  QLabel* const m_label;
  const std::array<double, n_leary_scores> m_scores;
  const std::array<std::string, n_leary_scores> m_legend;
  QImage m_image;

  void Redraw();
};

#endif // QTDRAWDIALOG_H
