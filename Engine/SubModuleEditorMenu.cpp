#include "SubModuleEditorMenu.h"
#include "ModuleEditor.h"
#include "Application.h"
#include "imgui/imgui.h"
#include <vector>


void SubModuleEditorMenu::Show()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("SubModules")) {
			for (std::vector<SubModuleEditor*>::iterator it = App->editor->subModules.begin() + 1; it != App->editor->subModules.end(); ++it)
			{
				ImGui::Checkbox((*it)->editorModuleName.c_str(), &(*it)->enabled);
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help")) {

			if (ImGui::MenuItem("Documentation"))
				ShellExecute(NULL, "open", "https://github.com/solidajenjo/Engine---Master/wiki",
					NULL, NULL, SW_SHOWNORMAL);
			if (ImGui::MenuItem("Download latest"))
				ShellExecute(NULL, "open", "https://github.com/solidajenjo/Engine---Master",
					NULL, NULL, SW_SHOWNORMAL);
			if (ImGui::MenuItem("Report a bug"))
				ShellExecute(NULL, "open", "https://github.com/solidajenjo/Engine---Master/issues",
					NULL, NULL, SW_SHOWNORMAL);
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}
