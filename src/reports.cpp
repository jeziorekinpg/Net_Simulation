#include "reports.hpp"

#include <utility>

SpecificTurnsReportNotifier::SpecificTurnsReportNotifier(std::set<Time> tset) {
  tset_ = std::move(tset);
}

bool SpecificTurnsReportNotifier::should_generate_report(Time t) {
  return tset_.find(t) != tset_.end();
}

IntervalReportNotifier::IntervalReportNotifier(TimeOffset toffs) {
  toffs_ = toffs;
}

bool IntervalReportNotifier::should_generate_report(Time t) {
  return (t == 1) || (t % toffs_ == 1);
}