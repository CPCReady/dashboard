#include <cstdio>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <fstream>

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <yaml-cpp/yaml.h>

using namespace ftxui;

std::string ExecuteCommand(const char* cmd) {
  std::string result = "";
  char buffer[128];
  FILE* pipe = popen(cmd, "r");
  if (!pipe) {
    return "Error al ejecutar el comando";
  }
  while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
    result += buffer;
  }
  pclose(pipe);

  const std::regex ansi_escape_codes("\x1B\[[0-9;]*[mK]");
  result = std::regex_replace(result, ansi_escape_codes, "");

  if (!result.empty() && result[result.length() - 1] == '\n') {
    result.erase(result.length() - 1);
  }
  return result;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <path_to_project>" << std::endl;
    return 1;
  }

  std::string project_path = argv[1];
  std::string yaml_path = project_path + "/.cpcready.yml";

  YAML::Node config;
  try {
    config = YAML::LoadFile(yaml_path);
  } catch (const YAML::Exception& e) {
    std::cerr << "Error loading YAML file: " << e.what() << std::endl;
    return 1;
  }

  std::string project_name = config["project"] ? config["project"].as<std::string>() : "N/A";
  std::string mode = config["mode"] ? config["mode"].as<std::string>() : "N/A";
  std::string title = config["title"] ? config["title"].as<std::string>() : "N/A";
  std::string drive_a = config["drive_a"] ? config["drive_a"].as<std::string>() : "N/A";
  std::string drive_b = config["drive_b"] ? config["drive_b"].as<std::string>() : "N/A";
  std::string drive_select = config["drive_select"] ? config["drive_select"].as<std::string>() : "N/A";
  std::string cpc_model = config["cpc_model"] ? config["cpc_model"].as<std::string>() : "N/A";

  if (drive_select == "a" || drive_select == "A") {
    drive_a = "🟢 Drive A: " + drive_a;
    drive_b = "🔴 Drive B: " + drive_b;
  } else if (drive_select == "b" || drive_select == "B") {
    drive_a = "🔴 Drive A: " + drive_a;
    drive_b = "🟢 Drive B: " + drive_b;
  } else {
    drive_a = "Drive A: " + drive_a;
    drive_b = "Drive B: " + drive_b;
  }

  std::string cpc_version;
  const char* home_dir = getenv("HOME");
  if (home_dir) {
    std::string command_path = std::string(home_dir) + "/.cpcready/src/cpcready-version.sh";
    cpc_version = ExecuteCommand(command_path.c_str());
  } else {
    cpc_version = "Error: $HOME no está definido";
  }

  auto screen = ScreenInteractive::Fullscreen();

  auto panel_0 = Renderer([]() {
    return window(text(""), vbox({
        text("") ,
        text("▞▀▖▛▀▖▞▀▖▛▀▖        ▌   ") | center | color(Color::Yellow1) | bold,
        text("▌  ▙▄▘▌  ▙▄▘▞▀▖▝▀▖▞▀▌▌ ▌") | center | color(Color::Yellow1) | bold,
        text("▌ ▖▌  ▌ ▖▌▚ ▛▀ ▞▀▌▌ ▌▚▄▌") | center | color(Color::Yellow1) | bold,
        text("▝▀ ▘  ▝▀ ▘ ▘▝▀▘▝▀▘▝▀▘▗▄▘") | center | color(Color::Yellow1) | bold,
        text("") 
        // text("      1.0.0 Sep 14 2005") | center | color(Color::Blue1),
    }));
  });

  auto panel_1 = Renderer([&cpc_model] { return window(text(""), text(" 🟥🟩🟦 AMSTRAD CPC " + cpc_model) | center | vcenter); });
  auto panel_2 = Renderer([&mode] { return window(text(""), text(" 📺 Mode: " + mode) ); });
  auto panel_3 = Renderer([&drive_a, &drive_b]() -> ftxui::Element {
    return window(text(""), vbox({
        text(" 💾 " + drive_a),
        text(" 💾 " + drive_b)
    }));
  });
  auto panel_4 = Renderer([&project_path, &project_name] { return window(text(""), 
    vbox({text(" 📁 Path: " + project_path), 
          text(" 🛠️  Project: " + project_name)})) | flex; 
  });

  auto panel_doc = Renderer([]() -> ftxui::Element {
    return window(text(""), vbox({
        text(" 📚 https://cpcready.readthedocs.io/"),
        text(" ⚙️  https://github.com/orgs/CPCReady/repositories") 
    }));
  });
  auto panel_6 = Renderer([&cpc_version] {
    return window(text(""), text(" 🏷️  " + cpc_version + " by Destroyer") | color(Color::Yellow));
  });

  auto layout = Container::Vertical({
      panel_0,
      panel_1,
      panel_2,
      panel_3,
      panel_4,
      panel_doc,
      panel_6
  });

  screen.Loop(layout);

  return 0;
}
