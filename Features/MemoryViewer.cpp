#include "MemoryViewer.h"

MemoryViewer::MemoryViewer()
{
    name = "Memory Viewer";
    ZeroMemory(inputBuffer, 256);
    std::cout << std::hex << &inputBuffer;
}

void MemoryViewer::Draw()
{
    ImGui::Begin("Memory Viewer");

    if (Memory::currentProc.pid == 0)
    {
        ImGui::Text("Select a process to view its memory");
    }
    else
    {
        std::vector<byte> bytes = Memory::ReadMemory(address, 256);
        std::stringstream stream;
        stream << std::hex << address;
        std::string result(stream.str());

        ImGui::Text((currentModule.name + " [" + result + "]").c_str());
        if (ImGui::InputText("GoTo", inputBuffer, 256, ImGuiInputTextFlags_EnterReturnsTrue))
        {
            address = hexNum(inputBuffer);
        }

        ImGui::BeginTable("table", 2);

        ImGui::TableNextColumn();
        ImGui::BeginChild("Memory", {0, 0}, ImGuiChildFlags_Border);
        for (int i = 0; i < bytes.size(); i++)
        {
            if (i % 16 != 0)
                ImGui::SameLine();
            ImGui::Text(hexStr((unsigned char *)&bytes[i], 1).c_str());
        }
        ImGui::EndChild();

        ImGui::TableNextColumn();
        ImGui::BeginChild("Strings", {0, 0}, ImGuiChildFlags_Border);
        for (int i = 0; i < bytes.size(); i++)
        {
            if (i % 16 != 0)
                ImGui::SameLine();
            char c = bytes[i];
            if (c < 32 || c > 126)
                c = '.';
            ImGui::Text((std::string("") + c).c_str());
        }
        ImGui::EndChild();

        ImGui::EndTable();

        if (ImGui::Button("<"))
        {
            address -= 16;
        }

        ImGui::SameLine();

        if (ImGui::Button(">"))
        {
            address += 16;
        }
    }

    ImGui::End();
}

std::string hexStr(unsigned char *data, int len)
{
    std::stringstream ss;
    ss << std::hex;
    for (int i = 0; i < len; ++i)
        ss << std::setw(2) << std::setfill('0') << (int)data[i];
    return ss.str();
}

uintptr_t hexNum(std::string data)
{
    std::stringstream ss;
    uintptr_t result = 0;
    
    ss << std::hex << data;
    ss >> result;

    return result;
}