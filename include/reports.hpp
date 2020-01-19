#ifndef NETSIM_REPORTS_HPP
#define NETSIM_REPORTS_HPP
#include "types.hpp"
#include <set>

class SpecificTurnsReportNotifier {
public:
  explicit SpecificTurnsReportNotifier(std::set<Time>);
  bool should_generate_report(Time);

private:
  std::set<Time> tset_;
};

class IntervalReportNotifier {
public:
  explicit IntervalReportNotifier(TimeOffset);
  bool should_generate_report(Time);

private:
  TimeOffset toffs_;
};

#endif // NETSIM_REPORTS_HPP
