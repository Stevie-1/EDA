#pragma once
#include <wx/wx.h>
#include <wx/treectrl.h>

class ToolboxPanel : public wxPanel
{
public:
    explicit ToolboxPanel(wxWindow* parent);
    void Rebuild();                 // �ⲿ���ã��ؽ���
private:
    wxTreeCtrl* m_tree;
    wxImageList* m_imgList;      // ͼ���
    void OnItemActivated(wxTreeEvent& evt);
    void OnBeginDrag(wxTreeEvent& evt);
    wxDECLARE_EVENT_TABLE();
};