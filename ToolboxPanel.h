#pragma once
#include <wx/wx.h>
#include <wx/treectrl.h>

class ToolboxPanel : public wxPanel
{
public:
    explicit ToolboxPanel(wxWindow* parent);
    ~ToolboxPanel();
    void Rebuild();                 // �ⲿ���ã��ؽ���
    void OnSelectionChanged(wxTreeEvent& evt);
    void OnMouseDown(wxMouseEvent& evt);
private:
    wxTreeCtrl* m_tree;
    wxImageList* m_imgList;      // ͼ���
    wxTreeItemId m_selectedItem;    // ��¼��ǰѡ�����ѡ��
    wxString     m_itemName;        // ��¼ѡ������
    void OnItemActivated(wxTreeEvent& evt);
};