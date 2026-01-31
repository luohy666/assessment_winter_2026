#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace rm_a0 {

// A0-09
std::vector<std::string> RunTextPipeline(const std::string& pipeline,
                                        const std::vector<std::string>& lines,
                                        bool& ok);

// A0-10
struct Event {
  std::string level;
  long long ms = 0;
  std::string msg;
};

std::vector<long long> RunRuleEngine(const std::vector<std::string>& rule_specs,
                                    const std::vector<Event>& events,
                                    long long& total_any,
                                    bool& ok);

// A0-11
std::string RunCommandDispatcher(const std::string& full_stdin, bool& ok);

}  // namespace rm_a0
