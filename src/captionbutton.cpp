/*
The MIT License (MIT)

Copyright © 2018-2021 Antonio Dias

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "captionbutton.h"

CaptionButton::CaptionButton(IconType type, qreal pixel_ratio, QWidget *parent) : QWidget(parent)
{
    m_type = type;
    m_pixel_ratio = pixel_ratio;
    m_is_active = false;
    m_is_under_mouse = false;
    m_is_pressed = false;
    m_icon_dark = false;

    setAttribute(Qt::WA_Hover);

    setColors();
    drawIcons();
}

void CaptionButton::drawIcons()
{
    int w = qCeil(10 * m_pixel_ratio);

    if (w <= 10)
        w = 10;
    else if (w <= 12)
        w = 12;
    else
        w = 15;

    switch (m_type)
    {
    case IconType::Minimize:
    {
        if (m_icon_dark)
        {
            m_active_icon = QIcon(":/icons/min-10.ico").pixmap(w, 2); // 1, minimize-active-dark
            m_inactive_icon = QIcon(":/icons/min-10.ico").pixmap(w, 2); // 1, minimize-inactive-dark
        }
        else
        {
            m_active_icon = QIcon(":/icons/min-10.ico").pixmap(w, 2); // 1, minimize-active-light
            m_inactive_icon = QIcon(":/icons/min-10.ico").pixmap(w, 2); // 1, minimize-inactive-light
        }

        break;
    }
    case IconType::Restore:
    {
        if (m_icon_dark)
        {
            m_active_icon = QIcon(":/icons/restore-active-dark.ico").pixmap(w, w);
            m_inactive_icon = QIcon(":/icons/restore-inactive-dark.ico").pixmap(w, w);
        }
        else
        {
            m_active_icon = QIcon(":/icons/restore-active-light.ico").pixmap(w, w);
            m_inactive_icon = QIcon(":/icons/restore-inactive-light.ico").pixmap(w, w);
        }

        break;
    }
    case IconType::Back:
    {
    if (m_icon_dark)
    {
        m_active_icon = QIcon(":/icons/back_arrow_3.png").pixmap(13, 12);
        m_inactive_icon = QIcon(":/icons/back_arrow_3.png").pixmap(13, 12);
    }
    else
    {
        m_active_icon = QIcon(":/icons/back_arrow_3.png").pixmap(13, 12);
        m_inactive_icon = QIcon(":/icons/back_arrow_3.png").pixmap(13, 12);
    }

    break;
    }
    case IconType::Maximize:
    {
        if (m_icon_dark)
        {
            m_active_icon = QIcon(":/icons/max-10.ico").pixmap(w, w); // w, maximize-active-dark
            m_inactive_icon = QIcon(":/icons/max-10.ico").pixmap(w, w); // w, maximize-inactive-dark
        }
        else
        {
            m_active_icon = QIcon(":/icons/max-10.ico").pixmap(w, w); // w, maximize-active-light
            m_inactive_icon = QIcon(":/icons/max-10.ico").pixmap(w, w); // w, maximize-inactive-light
        }

        break;
    }
    case IconType::Close:
    {
        if (m_icon_dark)
        {
            m_active_icon = QIcon(":/icons/close-10.ico").pixmap(w, w);  // w, close-active-dark
            m_inactive_icon = QIcon(":/icons/close-10.ico").pixmap(w, w);  // w, close-inactive-dark
            m_close_icon_hover = QIcon(":/icons/close-10.ico").pixmap(w, w);  // w, close-active-light
        }
        else
        {
            m_active_icon = QIcon(":/icons/close-10.ico").pixmap(w, w);  // w, close-active-light
            m_inactive_icon = QIcon(":/icons/close-10.ico").pixmap(w, w);  // w, close-inactive-light
        }

        break;
    }
    }
}

void CaptionButton::setColors()
{
    if (m_icon_dark)
    {
        if (m_type == IconType::Close)
        {
            m_normal = QColor("transparent");
            m_hover = QColor("#F00000");
            m_pressed = QColor("#F1707A");
        }
        else
        {
            m_normal = QColor("transparent");
            m_hover = QColor("#E5E5E5");
            m_pressed = QColor("#CACACB");
        }
    }
    else
    {
        if (m_type == IconType::Close)
        {
            m_normal = QColor("transparent");
            m_hover = QColor("#F00000");
            m_pressed = QColor("#F1707A");
        }
        else
        {
            m_normal = QColor("transparent");
            m_hover = QColor("#505050");
            m_pressed = QColor("#3F3F3F");
        }
    }

    repaint();
}

void CaptionButton::setIconMode(bool icon_dark)
{
    m_icon_dark = icon_dark;

    drawIcons();
    setColors();

    repaint();
}

void CaptionButton::setActive(bool is_active)
{
    m_is_active = is_active;

    repaint();
}

bool CaptionButton::event(QEvent *event)
{
    switch (event->type())
    {
#ifdef Q_OS_MAC
    case QEvent::ShowToParent:
    {
        QPainterPath path;
        path.addRoundedRect(rect(), 10, 10);
        QRegion mask = QRegion(path.toFillPolygon().toPolygon());
        setMask(mask);

        break;
    }
#endif
    case QEvent::HoverEnter:
    {
        m_is_under_mouse = true;

        repaint();

        break;
    }
    case QEvent::HoverLeave:
    {
        m_is_under_mouse = false;

        repaint();

        break;
    }
    case QEvent::MouseMove:
    {
        m_is_under_mouse = isUnderMouse();

        repaint();

        break;
    }
    case QEvent::MouseButtonPress:
    {
        QMouseEvent *e = static_cast<QMouseEvent*>(event);

        if (e->button() != Qt::LeftButton)
            break;

        m_is_pressed = true;

        m_is_under_mouse = true;

        repaint();

        break;
    }
    case QEvent::MouseButtonRelease:
    {
        QMouseEvent *e = static_cast<QMouseEvent*>(event);

        if (e->button() != Qt::LeftButton)
            break;

        m_is_pressed = false;

        m_is_under_mouse = false;

        repaint();

        if (isUnderMouse())
        {
            emit clicked();
        }

        break;
    }
    default:
        break;
    }

    return QWidget::event(event);
}

void CaptionButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPixmap current_icon = m_active_icon;
    QColor current_color = m_normal;

    //Change icon if needed
    if (m_is_under_mouse)
    {
        if (m_type == IconType::Close && m_icon_dark)
            current_icon = m_close_icon_hover;
    }
    else
    {
        if (!m_is_active)
            current_icon = m_inactive_icon;
    }

    //Change background color if needed
    if (m_is_pressed)
    {
        if (m_is_under_mouse)
            current_color = m_pressed;
    }
    else
    {
        if (m_is_under_mouse)
            current_color = m_hover;
    }

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

    painter.fillRect(rect(), current_color);

    int w = qCeil(10 * m_pixel_ratio);

    if (w <= 10)
        w = 10;
    else if (w <= 12)
        w = 12;
    else
        w = 15;

    int h = (m_type != IconType::Minimize) ? w : 2; // 1
    w = (m_type == IconType::Back) ? 13 : w;
    h = (m_type == IconType::Back) ? 12 : h;

    QRect target_rect;
    target_rect = current_icon.rect();
    target_rect.setSize(QSize(w, h));
    target_rect = QRect(rect().center() - target_rect.center(), target_rect.size());
    painter.drawPixmap(target_rect, current_icon);
}

bool CaptionButton::isUnderMouse()
{
    return (rect().contains(mapFromGlobal(QCursor::pos())));
}