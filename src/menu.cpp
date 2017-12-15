#include "menu.h"
#include "imgui/imgui.h"
#include "gui/updateWindow.h"
#include "updater/updater.h"

Menu::Menu()
{
    ffxiv_ = new FFXIV();
}

Menu::~Menu()
{
    delete ffxiv_;
    ffxiv_ = nullptr;
}

void Menu::menu()
{
    static bool init = false;

    static bool no_titlebar = false;
    static bool no_scrollbar = false;
    static bool no_menu = false;
    static bool no_move = false;
    static bool no_resize = false;
    static bool no_collapse = false;


    static bool show_column = true;
    static bool show_update_window = false;


    static Updater update;
    
    ffxiv_->arch_->updateNames(ffxiv_->ffxiv_, ffxiv_->partyMembers_);

    // Demonstrate the various window flags. Typically you would just use the default.
    ImGuiWindowFlags window_flags = 0;
    if (no_titlebar)  window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (no_scrollbar) window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!no_menu)     window_flags |= ImGuiWindowFlags_MenuBar;
    if (no_move)      window_flags |= ImGuiWindowFlags_NoMove;
    if (no_resize)    window_flags |= ImGuiWindowFlags_NoResize;
    if (no_collapse)  window_flags |= ImGuiWindowFlags_NoCollapse;
    ImGui::SetNextWindowSize(ImVec2(500, 600), ImGuiCond_FirstUseEver);


    if (!ImGui::Begin("FFXIV Party Logs", false, window_flags))
    {
        // Early out if the window is collapsed, as an optimization.
        ImGui::End();
        return;
    }

    if(!init)
    {
        if (!update.compareVersion())
            show_update_window = true;

        init = true;
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Menu"))
        {
            ImGui::MenuItem("(dummy menu)", NULL, false, false);
            ImGui::EndMenu();
        }


        if (ImGui::BeginMenu("Help"))
        {
            ImGui::MenuItem("Check for Updates", NULL, &show_update_window);
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    if (show_update_window)
    {
        UPDATE::update(&show_update_window, update);
    }

    if (show_column)
    {
        if (ffxiv_->arch_->getCrossWorldStatus())
            ImGui::TextColored(ImColor(244, 66, 226), "CROSS WORLD");
        else
            ImGui::TextColored(ImColor(76, 153, 255), "NORMAL PARTY");

        ImGui::Columns(1, "mycolumns3", false);  // 3-ways, no border
        ImGui::Separator();
        //draw(foobar, globalCount);
        //draw(ffxiv->arch_->getFilteredAllies());
        draw();
        ImGui::Columns(1);
        ImGui::Separator();
    }

    if(ImGui::Button("All"))
    {
        ffxiv_->arch_->openAll(ffxiv_->partyMembers_);
    }

    // DEBUG
    ImGui::Text("party members %d", ffxiv_->partyMembers_);


    ImGui::End();
}

void Menu::draw()
{
    int partyMembers = ffxiv_->partyMembers_;

    if(ffxiv_->arch_->getCrossWorldStatus())
    {
        if (ffxiv_->arch_->getFilteredAlliesCW().size() < ffxiv_->partyMembers_)
            partyMembers = ffxiv_->arch_->getFilteredAlliesCW().size();

        for(int i = 0; i < partyMembers; i++)
        {
            if(ImGui::Selectable(ffxiv_->arch_->getFilteredAlliesCW()[i]->name_))
                ffxiv_->arch_->getFilteredAlliesCW()[i]->openBrowser();

            ImGui::NextColumn();
        }

    }
    else
    {
        if (ffxiv_->arch_->getFilteredAllies().size() < ffxiv_->partyMembers_)
            partyMembers = ffxiv_->arch_->getFilteredAllies().size();

        for (int i = 0; i < partyMembers; i++)
        {
            if (ImGui::Selectable(ffxiv_->arch_->getFilteredAllies()[i]->name_))
                ffxiv_->arch_->getFilteredAllies()[i]->openBrowser();

            ImGui::NextColumn();
        }
    }
}