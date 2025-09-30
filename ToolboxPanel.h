#pragma once
#include <wx/wx.h>
#include <wx/treectrl.h>
#include <wx/propgrid/propgrid.h> // �������Ա��ͷ�ļ�
#include <wx/propgrid/advprops.h> 
#include <wx/variant.h> 
#include <map>
#include <vector>

// ����������ṹ�壨�洢�������Ե���Ϣ��
struct ToolProperty {
    wxString propName;       // ����������"On Color"��
    wxString propType;       // �������ͣ�"bool""int""string""color"��
    wxVariant defaultValue;  // Ĭ��ֵ��֧�ֲ�ͬ���ͣ�

    // ��ӹ��캯���Խ�� vector ��ʼ������
    ToolProperty(const wxString& name, const wxString& type, const wxVariant& value)
        : propName(name), propType(type), defaultValue(value) {
    }
};

class ToolboxPanel : public wxPanel
{
public:
    explicit ToolboxPanel(wxWindow* parent);
    void Rebuild();                 // �ⲿ���ã��ؽ�������
private:
    wxTreeCtrl* m_tree;
    wxImageList* m_imgList;         // ͼ���б�
    wxPropertyGrid* m_propGrid;     // ���������Ա�����
    // ������������ �� �����б��ӳ�䣨�洢ÿ�����ߵ��������ԣ�
    std::map<wxString, std::vector<ToolProperty>> m_toolPropMap;

    // ԭ�к�������
    void LoadToolIcon(const wxString& toolName, const wxString& pngFileName);
    int GetToolIconIndex(const wxString& toolName);
    void OnItemActivated(wxTreeEvent& evt);
    void OnBeginDrag(wxTreeEvent& evt);

    // �������¼�������
    void OnToolSelected(wxTreeEvent& evt); // ����ѡ���¼������ģ�
    void InitToolPropertyMap();            // ��ʼ������-����ӳ���
    void UpdatePropertyPanel(const wxString& toolName); // �����������

    wxDECLARE_EVENT_TABLE();
};