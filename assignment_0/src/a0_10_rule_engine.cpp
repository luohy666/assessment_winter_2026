#include "rm_a0/a0_lib.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
  int m = 0;
  if (!(std::cin >> m)) return 0;
  std::string dummy;
  std::getline(std::cin, dummy);

  std::vector<std::string> rule_specs;
  rule_specs.reserve(m);
  for (int i = 0; i < m; ++i) {
    std::string spec;
    if (!std::getline(std::cin, spec)) return 0;
    rule_specs.push_back(spec);
  }

  std::vector<rm_a0::Event> events;
  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.empty()) continue;
    std::istringstream iss(line);
    rm_a0::Event e;
    if (!(iss >> e.level >> e.ms)) continue;
    std::getline(iss, e.msg);
    if (!e.msg.empty() && e.msg[0] == ' ') e.msg.erase(0, 1);
    events.push_back(std::move(e));
  }

  bool ok = false;
  long long total = 0;
  auto hit = rm_a0::RunRuleEngine(rule_specs, events, total, ok);
  if (!ok || static_cast<int>(hit.size()) != m) {
    std::cout << "FAIL\n";
    return 0;
  }

  for (int i = 0; i < m; ++i) {
    std::cout << "rule" << (i + 1) << "=" << hit[i] << "\n";
  }
  std::cout << "total=" << total << "\n";
  return 0;
}
