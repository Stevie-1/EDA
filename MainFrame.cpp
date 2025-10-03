#include "MainFrame.h"
#include "MainMenuBar.h"
#include "CanvasPanel.h"
#include "PropertyPanel.h"
#include <wx/msgdlg.h>
#include "ToolboxPanel.h"   // ��Ĳ����
#include <wx/aui/aui.h>
#include "CanvasModel.h"
#include "my_log.h"
#include <wx/filename.h> 

extern std::vector<CanvasElement> g_elements;

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
EVT_MENU(wxID_EXIT, MainFrame::OnQuit)
EVT_MENU(wxID_HIGHEST + 900, MainFrame::OnToolboxElement)
wxEND_EVENT_TABLE()


MainFrame::MainFrame()
    : wxFrame(nullptr, wxID_ANY, "MyLogisim")
{

    wxString jsonPath = wxFileName(wxGetCwd(), "canvas_elements.json").GetFullPath();
    MyLog("MainFrame: JSON full path = [%s]\n", jsonPath.ToUTF8().data());
    g_elements = LoadCanvasElements(jsonPath);

    /* �˵� & ״̬�� */
    SetMenuBar(new MainMenuBar(this));
    CreateStatusBar(1);
    SetStatusText("Ready");
    SetTitle("Untitled");
    static_cast<MainMenuBar*>(GetMenuBar())->SetCurrentDocInWindowList("Untitled");

    /* �Ѵ��ڽ��� AUI �����������ȣ� */
    m_auiMgr.SetManagedWindow(this);

    /* �������뻭�����ȿհ�ռλ�� */
    m_canvas = new CanvasPanel(this);
    m_canvas->SetBackgroundColour(*wxWHITE);

    /* ��������� + ���Ա����µ��ţ� */
    wxPanel* sidePanel = new wxPanel(this);  // ���
    wxBoxSizer* sideSizer = new wxBoxSizer(wxVERTICAL);

    ToolboxPanel* toolbox = new ToolboxPanel(sidePanel);  // �������� sidePanel
    sideSizer->Add(toolbox, 1, wxEXPAND);    // �ϣ��������������죩

    m_propPanel = new PropertyPanel(sidePanel);  // �������� sidePanel
    sideSizer->Add(m_propPanel, 0, wxEXPAND);    // �£����Ա��ȹ̶��ߣ�

    sidePanel->SetSizer(sideSizer);

    /* �������������Ϊһ�� AUI Pane ͣ�� */
    m_auiMgr.AddPane(sidePanel, wxAuiPaneInfo()
        .Name("side")               // ͳһ����
        .Caption("Toolbox & Properties")
        .Left()
        .Layer(1)
        .Position(1)
        .CloseButton(false)
        .BestSize(280, 700)        // �ܸ߶�����������
        .MinSize(200, 400)
        .FloatingSize(280, 700)
        .Gripper(true)
        .PaneBorder(false));

    /* ��������ԭ�� */
    m_auiMgr.AddPane(m_canvas, wxAuiPaneInfo()
        .Name("canvas")
        .CenterPane()
        .CloseButton(false)
        .MinSize(400, 300));

    /* һ�����ύ */
    m_auiMgr.Update();
}

MainFrame::~MainFrame()
{
    m_auiMgr.UnInit();   // �����ֶ�����ʼ��
}


void MainFrame::OnToolboxElement(wxCommandEvent& evt)
{
    MyLog("MainFrame: received <%s>\n", evt.GetString().ToUTF8().data());

    wxString name = evt.GetString();
    auto it = std::find_if(g_elements.begin(), g_elements.end(),
        [&](const CanvasElement& e) { return e.GetName() == name; });
    if (it == g_elements.end()) return;

    CanvasElement clone = *it;
    clone.SetPos(wxPoint(100, 100));   // �ȷ����룬�������������
    m_canvas->AddElement(clone);        
}

void MainFrame::DoFileNew() { wxMessageBox("DoFileNew"); }
void MainFrame::DoFileSave() { wxMessageBox("DoFileSave"); }
void MainFrame::DoFileSaveAs() { wxMessageBox("DoFileSaveAs"); }
void MainFrame::DoFileOpen(const wxString& path)
{
    wxString msg = path.IsEmpty()
        ? wxString("DoFileOpen dialog")     // ǿ�� wxString
        : wxString::Format(wxT("DoFileOpen: %s"), path);
    wxMessageBox(msg, wxT("Info"), wxOK | wxICON_INFORMATION, this);
}
void MainFrame::OnAbout(wxCommandEvent&)
{
    wxMessageBox(wxString::Format(wxT("MyLogisim\n%s"), wxVERSION_STRING),
        wxT("About"), wxOK | wxICON_INFORMATION, this);
}

void MainFrame::DoEditUndo() { wxMessageBox("Edit->Undo"); }
void MainFrame::DoEditCut() { wxMessageBox("Edit->Cut"); }
void MainFrame::DoEditCopy() { wxMessageBox("Edit->Copy"); }
void MainFrame::DoEditPaste() { wxMessageBox("Edit->Paste"); }
void MainFrame::DoEditDelete() { wxMessageBox("Edit->Delete"); }
void MainFrame::DoEditDuplicate() { wxMessageBox("Edit->Duplicate"); }
void MainFrame::DoEditSelectAll() { wxMessageBox("Edit->SelectAll"); }
void MainFrame::DoEditRaiseSel() { wxMessageBox("Edit->Raise Selection"); }
void MainFrame::DoEditLowerSel() { wxMessageBox("Edit->Lower Selection"); }
void MainFrame::DoEditRaiseTop() { wxMessageBox("Edit->Raise to Top"); }
void MainFrame::DoEditLowerBottom() { wxMessageBox("Edit->Lower to Bottom"); }
void MainFrame::DoEditAddVertex() { wxMessageBox("Edit->Add Vertex"); }
void MainFrame::DoEditRemoveVertex() { wxMessageBox("Edit->Remove Vertex"); }

void MainFrame::DoProjectAddCircuit() { wxMessageBox("Project->Add Circuit"); }
void MainFrame::DoProjectLoadLibrary() { wxMessageBox("Project->Load Library"); }
void MainFrame::DoProjectUnloadLibraries() { wxMessageBox("Project->Unload Libraries"); }
void MainFrame::DoProjectMoveCircuitUp() { wxMessageBox("Project->Move Circuit Up"); }
void MainFrame::DoProjectMoveCircuitDown() { wxMessageBox("Project->Move Circuit Down"); }
void MainFrame::DoProjectSetAsMain() { wxMessageBox("Project->Set As Main Circuit"); }
void MainFrame::DoProjectRemoveCircuit() { wxMessageBox("Project->Remove Circuit"); }
void MainFrame::DoProjectRevertAppearance() { wxMessageBox("Project->Revert Appearance"); }
void MainFrame::DoProjectViewToolbox() { wxMessageBox("Project->View Toolbox"); }
void MainFrame::DoProjectViewSimTree() { wxMessageBox("Project->View Simulation Tree"); }
void MainFrame::DoProjectEditLayout() { wxMessageBox("Project->Edit Circuit Layout"); }
void MainFrame::DoProjectEditAppearance() { wxMessageBox("Project->Edit Circuit Appearance"); }
void MainFrame::DoProjectAnalyzeCircuit() { wxMessageBox("Project->Analyze Circuit"); }
void MainFrame::DoProjectGetStats() { wxMessageBox("Project->Get Circuit Statistics"); }
void MainFrame::DoProjectOptions() { wxMessageBox("Project->Options"); }

void MainFrame::DoSimSetEnabled(bool on)
{
    wxMessageBox(wxString::Format("Simulation %s", on ? "enabled" : "disabled"));
}
void MainFrame::DoSimReset() { wxMessageBox("Simulation reset"); }
void MainFrame::DoSimStep() { wxMessageBox("Simulation step"); }
void MainFrame::DoSimGoOut() { wxMessageBox("Go Out To State"); }
void MainFrame::DoSimGoIn() { wxMessageBox("Go In To State"); }
void MainFrame::DoSimTickOnce() { wxMessageBox("Tick Once"); }
void MainFrame::DoSimTicksEnabled(bool on)
{
    wxMessageBox(wxString::Format("Ticks %s", on ? "enabled" : "disabled"));
}
void MainFrame::DoSimSetTickFreq(int hz)
{
    wxMessageBox(wxString::Format("Tick frequency set to %d Hz", hz));
}
void MainFrame::DoSimLogging() { wxMessageBox("Logging dialog"); }

void MainFrame::DoWindowCombinationalAnalysis()
{
    wxMessageBox("Window->Combinational Analysis");
}
void MainFrame::DoWindowPreferences()
{
    wxMessageBox("Window->Preferences");
}
void MainFrame::DoWindowSwitchToDoc(const wxString& title)
{
    wxMessageBox("Switch to document: " + title);
    // �����߼�����������л�����Ӧ�Ӵ��ڻ���ͼ
}

void MainFrame::DoHelpTutorial()
{
    wxMessageBox("Help->Tutorial");
}
void MainFrame::DoHelpUserGuide()
{
    wxMessageBox("Help->User's Guide");
}
void MainFrame::DoHelpLibraryRef()
{
    wxMessageBox("Help->Library Reference");
}
void MainFrame::DoHelpAbout()
{
    wxMessageBox(wxString::Format("MyLogisim\n%s", wxVERSION_STRING),
        wxT("About"), wxOK | wxICON_INFORMATION, this);
}

