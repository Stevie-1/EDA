#include <wx/defs.h>
#include "ToolboxPanel.h"
#include "ToolboxModel.h"
#include <wx/artprov.h>
#include <wx/dnd.h>
#include <wx/treectrl.h>
#include <wx/textfile.h>
#include <wx/tokenzr.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/msgdlg.h>        
#include <wx/file.h>
#include <json/json.h>
#include "my_log.h"
#include <wx/clntdata.h>

static void MY_LOG(const wxString& s)
{
    wxFile f(wxStandardPaths::Get().GetTempDir() + "\\logsim_tools.log",
        wxFile::write_append);
    if (f.IsOpened()) {
        f.Write(wxDateTime::Now().FormatISOCombined() + "  " + s + "\n");
        f.Close();
    }
}

static const wxDataFormat myFormat("application/my-canvas-elem");



// ���������ݽڵ�
class wxStringTreeItemData : public wxTreeItemData
{
public:
    explicit wxStringTreeItemData(const wxString& s) : m_str(s) {}
    const wxString& GetStr() const { return m_str; }
private:
    wxString m_str;
};



ToolboxPanel::ToolboxPanel(wxWindow* parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(250, -1))
{
    // �� �ȴ�����
    m_tree = new wxTreeCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
        wxTR_DEFAULT_STYLE | wxTR_HIDE_ROOT | wxTR_FULL_ROW_HIGHLIGHT);

    // �� �ٰ��¼��������� new ֮��
    m_tree->Bind(wxEVT_TREE_SEL_CHANGED, &ToolboxPanel::OnSelectionChanged, this);
    m_tree->Bind(wxEVT_LEFT_DOWN, &ToolboxPanel::OnMouseDown, this);
    m_tree->Bind(wxEVT_TREE_ITEM_ACTIVATED, &ToolboxPanel::OnItemActivated, this);
    // �� ����/��ۣ������еģ�����Ҫ�ٴ� new��
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_tree, 1, wxEXPAND | wxALL, 0);
    SetSizer(sizer);

    wxBitmap transparent(24, 24);
    transparent.SetMask(new wxMask(transparent, *wxBLACK));
    m_imgList = new wxImageList(24, 24, true, 10);
    m_imgList->Add(wxArtProvider::GetBitmap(wxART_FOLDER, wxART_OTHER, wxSize(24, 24)));
    m_imgList->Add(transparent);
    m_tree->AssignImageList(m_imgList);

    wxFont font(wxFontInfo(11).FaceName("Segoe UI"));
    m_tree->SetFont(font);
    m_tree->SetIndent(20);

    Rebuild();
}

ToolboxPanel::~ToolboxPanel()
{
    m_tree->Unbind(wxEVT_TREE_SEL_CHANGED, &ToolboxPanel::OnSelectionChanged, this);
    m_tree->Unbind(wxEVT_LEFT_DOWN, &ToolboxPanel::OnMouseDown, this);
}

void ToolboxPanel::Rebuild()
{
    m_tree->DeleteAllItems();
    wxTreeItemId root = m_tree->AddRoot("root", 0, 0);

    wxVector<wxString> mains = GetMainElements();
    wxVector<ToolCategory> cats = GetToolboxCategories();

    MY_LOG("Rebuild: main count = " + wxString::Format("%zu", mains.size()) +
        ", category count = " + wxString::Format("%zu", cats.size()));

    /* main �ڵ� */
    for (const auto& m : mains) {
        wxTreeItemId item = m_tree->AppendItem(root, m, 1, 1);
        m_tree->SetItemData(item, new wxStringTreeItemData(m));
    }

    /* ����ڵ� */
    for (const auto& cat : cats) {
        wxTreeItemId folderId = m_tree->AppendItem(root, cat.name, 0, 0);
        m_tree->SetItemBold(folderId, true);
        for (const auto& item : cat.items) {
            wxTreeItemId leafId = m_tree->AppendItem(folderId, item, 1, 1);
            m_tree->SetItemData(leafId, new wxStringTreeItemData(item));
        }
        m_tree->Expand(folderId);
    }
}


void ToolboxPanel::OnItemActivated(wxTreeEvent& evt)
{
    wxString name = m_tree->GetItemText(evt.GetItem());
    MyLog("Toolbox: activated <%s>\n", name.ToUTF8().data());
    wxCommandEvent cmdEvt(wxEVT_COMMAND_MENU_SELECTED, wxID_HIGHEST + 900);
    cmdEvt.SetString(name);
    wxPostEvent(GetParent(), cmdEvt);   // �׸�������
}


void ToolboxPanel::OnSelectionChanged(wxTreeEvent& evt)
{
    if (m_tree->GetItemText(evt.GetItem()).IsEmpty())
    {
        // ���ѡ�е���Ϊ�գ�ֱ�ӷ���
        return;
    }

    m_itemName = m_tree->GetItemText(evt.GetItem());
    MyLog("Toolbox: selection changed to <%s>\n", m_itemName.ToUTF8().data());
}

void ToolboxPanel::OnMouseDown(wxMouseEvent& evt)
{
    MyLog("OnMouseDown: entered\n");
    evt.Skip();                // �� wx ����������������߼�
}

