#include "ProcessViewer.h"

ProcessViewer::ProcessViewer()
{
    name = "Process Viewer";

    processSearch = (char *)malloc(MAX_PATH);
    ZeroMemory(processSearch, MAX_PATH);
}

void ProcessViewer::Draw()
{
    ImGui::Begin("Process Viewer");

    ImGui::InputText("Search", processSearch, MAX_PATH);

    ImGui::BeginChild("Processes", {0, 0}, ImGuiChildFlags_Border);
    std::vector<proc> procs = Memory::GetProcs();
    for (const proc &p : procs)
    {
        if (std::string(p.name).find(processSearch) != std::string::npos)
        {
            if (ImGui::Button(p.name.c_str()))
            {
                Memory::OpenProc(p);
            }
        }
    }
    ImGui::EndChild();

    ImGui::End();
}