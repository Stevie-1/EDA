#pragma once
#include <wx/wx.h>
#include <vector>
#include "CanvasElement.h"

class CanvasPanel : public wxPanel
{
public:
    CanvasPanel(wxWindow* parent);
    void AddElement(const CanvasElement& elem);   // ��Ԫ��
    void OnLeftDown(wxMouseEvent& evt);  // ���񵥻�
    void OnKeyDown(wxKeyEvent& evt);     // ESC ȡ������
    void PlaceElement(const wxString& name, const wxPoint& pos); // �� MainFrame ����
private:
    std::vector<CanvasElement> m_elements;   // ���ݲ�
    void OnPaint(wxPaintEvent& evt);
    wxDECLARE_EVENT_TABLE();
};
