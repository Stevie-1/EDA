#pragma once
#include <wx/wx.h>
#include <vector>
#include "CanvasElement.h"

class CanvasPanel : public wxPanel
{
public:
    CanvasPanel(wxWindow* parent);
    void AddElement(const CanvasElement& elem);   // ��Ԫ��
private:
    std::vector<CanvasElement> m_elements;   // ���ݲ�
    void OnPaint(wxPaintEvent& evt);
    wxDECLARE_EVENT_TABLE();
};
