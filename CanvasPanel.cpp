#include "CanvasPanel.h"
#include <wx/dcbuffer.h>   // ˫����

wxBEGIN_EVENT_TABLE(CanvasPanel, wxPanel)
EVT_PAINT(CanvasPanel::OnPaint)
wxEND_EVENT_TABLE()

CanvasPanel::CanvasPanel(wxWindow* parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
        wxFULL_REPAINT_ON_RESIZE | wxBORDER_NONE)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT); // ˫�������
}

void CanvasPanel::OnPaint(wxPaintEvent&)
{
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();

    const int grid = 20;
    const wxColour c(240, 240, 240);
    dc.SetPen(wxPen(c, 1));

    wxSize sz = GetClientSize();   // ȡ��ǰ������С
    for (int x = 0; x < sz.x; x += grid) {
        dc.DrawLine(x - 2, 0, x + 2, sz.y);   // ��ֱ�ᴩ
        dc.DrawLine(0, x - 2, sz.x, x + 2);   // ˮƽ�ᴩ
    }
}