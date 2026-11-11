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
#include "learycircumplex.h"

#include <algorithm>
#include <cmath>

#include <QPainter>
#include <QPointF>

#include "dotmatrix.h"

namespace {

constexpr double pi = 3.14159265358979323846;

/// Point on a circle around (midx, midy), where angle 0.0 is at the top
/// and angles increase clockwise
QPointF GetPoint(
  const double midx, const double midy, const double angle, const double ray)
{
  return QPointF(
    midx + (std::sin(angle) * ray),
    midy - (std::cos(angle) * ray)
  );
}

} // namespace

QImage DrawLearyCircumplex(
  const std::array<double, n_leary_scores>& scores,
  const std::array<std::string, n_leary_scores>& legend,
  const int any_image_size)
{
  const int image_size = std::max(100, any_image_size);
  //Scale the dot-matrix text with the image size, so it stays readable
  const int text_scale = std::max(1, image_size / 300);
  const int char_width = 6 * text_scale;
  const int char_height = 8 * text_scale;

  QImage image(image_size, image_size, QImage::Format_RGB32);
  image.fill(Qt::white);

  //Calculate image center and circumplex ray
  const double midx = static_cast<double>(image_size) / 2.0;
  const double midy = static_cast<double>(image_size) / 2.0;
  const double ray = std::min(midx, midy) - 2.0 - (2.0 * char_height);

  QPainter painter(&image);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setPen(QPen(Qt::black, text_scale));

  //Create the vertices
  std::array<QPointF, n_leary_scores> vertices;
  for (int i = 0; i != n_leary_scores; ++i)
  {
    vertices[i] = GetPoint(midx, midy, static_cast<double>(i) * pi * 0.25, ray);
  }

  //Draw the perimeter and the pie pieces
  for (int i = 0; i != n_leary_scores; ++i)
  {
    painter.drawLine(vertices[(i + n_leary_scores - 1) % n_leary_scores], vertices[i]);
    painter.drawLine(QPointF(midx, midy), vertices[i]);
  }

  //Draw the scores
  for (int i = 0; i != n_leary_scores; ++i)
  {
    const double angle1 = static_cast<double>(i) * pi * 0.25;
    const double angle2 = static_cast<double>(i + 1) * pi * 0.25;
    painter.drawLine(
      GetPoint(midx, midy, angle1, ray * scores[i]),
      GetPoint(midx, midy, angle2, ray * scores[i])
    );
  }

  //Draw the legend, rotated along the circle
  const double text_ray
    = ray + (std::sqrt(2.0) * static_cast<double>(std::max(char_width, char_height)));
  painter.setRenderHint(QPainter::SmoothPixmapTransform);
  for (int i = 0; i != n_leary_scores; ++i)
  {
    const QImage text = CreateDotMatrixImage(
      legend[i], text_scale, Qt::black, Qt::transparent
    );
    const double angle = (pi * 0.125) + (static_cast<double>(i) * pi * 0.25);
    const double text_angle = (0.175 * pi) + (static_cast<double>(i) * 0.25 * pi);
    painter.save();
    painter.translate(GetPoint(midx, midy, angle, text_ray));
    painter.rotate(text_angle * 180.0 / pi);
    painter.drawImage(QPointF(-text.width() / 2.0, -text.height() / 2.0), text);
    painter.restore();
  }
  return image;
}
