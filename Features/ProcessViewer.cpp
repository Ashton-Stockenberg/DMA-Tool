#include "ProcessViewer.h"

ProcessViewer::ProcessViewer()
{
	name = "Process Viewer";
    
    processSearch = (char*)malloc(MAX_PATH);
    ZeroMemory(processSearch, MAX_PATH);
}

void ProcessViewer::Draw()
{
    ImGui::Begin("Process Viewer");

    ImGui::InputText("Search", processSearch, MAX_PATH);

    ImGui::BeginChild("Processes", { 0,0 }, ImGuiChildFlags_Border);
    std::vector<proc> procs = Memory::GetProcs();
    for (proc p : procs)
    {
        if (std::string(p.name).find(processSearch) != std::string::npos)
        {
            if (ImGui::Button(p.name))
            {
                Memory::OpenProc(p);
            }
        }
    }
    ImGui::EndChild();

    ImGui::End();
}