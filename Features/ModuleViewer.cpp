#include "ModuleViewer.h"

ModuleViewer::ModuleViewer(MemoryViewer* memViewer)
    :
    memoryViewer(memViewer)
{
    name = "Module Viewer";
    
    moduleSearch = (char*)malloc(MAX_PATH);
    ZeroMemory(moduleSearch, MAX_PATH);
}

void ModuleViewer::Draw()
{
    ImGui::Begin("Module Viewer");

    if (Memory::currentProc.pid == 0)
    {
        ImGui::Text("Select a process to view its modules");
    }
    else
    {
        std::vector<procModule> mods = Memory::GetMods();

        if (mods.size() == 0)
        {
            ImGui::Text("Cannot get modules!");
        }
        else
        {
            ImGui::Text(Memory::currentProc.name.c_str());

            ImGui::InputText("Search", moduleSearch, MAX_PATH);

            ImGui::BeginChild("Module", {0, 0}, ImGuiChildFlags_Border);
            for (procModule m : mods)
            {
                if (std::string(m.name).find(moduleSearch) != std::string::npos)
                {
                    if (ImGui::Button(m.name.c_str()))
                    {
                        memoryViewer->currentModule = m;
                        memoryViewer->address = m.address;

                        std::string addyString = hexStr((unsigned char*)&m.address, sizeof(uintptr_t));

                        strcpy_s(memoryViewer->inputBuffer, addyString.c_str());
                    }
                }
            }

            ImGui::EndChild();
        }
    }

    ImGui::End();
}
