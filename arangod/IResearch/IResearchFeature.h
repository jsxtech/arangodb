////////////////////////////////////////////////////////////////////////////////
/// DISCLAIMER
///
/// Copyright 2014-2022 ArangoDB GmbH, Cologne, Germany
/// Copyright 2004-2014 triAGENS GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is ArangoDB GmbH, Cologne, Germany
///
/// @author Andrey Abramov
/// @author Vasily Nabatchikov
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "StorageEngine/StorageEngine.h"
#include "RestServer/arangod.h"
#include "VocBase/voc-types.h"

namespace arangodb {
struct IndexTypeFactory;

namespace aql {

struct Function;

}  // namespace aql

namespace iresearch {

class IResearchAsync;
class IResearchLink;
class ResourceMutex;

////////////////////////////////////////////////////////////////////////////////
/// @enum ThreadGroup
/// @brief there are 2 thread groups for execution of asynchronous maintenance
///        jobs.
////////////////////////////////////////////////////////////////////////////////
enum class ThreadGroup : size_t { _0 = 0, _1 };

////////////////////////////////////////////////////////////////////////////////
/// @returns true if the specified 'func' is an ArangoSearch filter function,
///          false otherwise
////////////////////////////////////////////////////////////////////////////////
bool isFilter(aql::Function const& func) noexcept;

////////////////////////////////////////////////////////////////////////////////
/// @returns true if the specified 'func' is an ArangoSearch scorer function,
///          false otherwise
////////////////////////////////////////////////////////////////////////////////
bool isScorer(aql::Function const& func) noexcept;

#ifdef USE_ENTERPRISE
////////////////////////////////////////////////////////////////////////////////
/// @returns true if the specified 'func' is an ArangoSearch OFFSET_INFO
///          function, false otherwise
////////////////////////////////////////////////////////////////////////////////
bool isOffsetInfo(aql::Function const& func) noexcept;
#endif

////////////////////////////////////////////////////////////////////////////////
/// @class IResearchFeature
////////////////////////////////////////////////////////////////////////////////
class IResearchFeature final : public ArangodFeature {
 public:
  static constexpr std::string_view name() noexcept { return "ArangoSearch"; }

  explicit IResearchFeature(Server& server);

  void beginShutdown() override;
  void collectOptions(std::shared_ptr<options::ProgramOptions>) override;
  void prepare() override;
  void start() override;
  void stop() override;
  void unprepare() override;
  void validateOptions(std::shared_ptr<options::ProgramOptions>) override;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief schedule an asynchronous task for execution
  /// @param id thread group to handle the execution
  /// @param fn the function to execute
  /// @param delay how log to sleep before the execution
  //////////////////////////////////////////////////////////////////////////////
  bool queue(ThreadGroup id, std::chrono::steady_clock::duration delay,
             std::function<void()>&& fn);

  std::tuple<size_t, size_t, size_t> stats(ThreadGroup id) const;
  std::pair<size_t, size_t> limits(ThreadGroup id) const;

  template<typename Engine,
           typename std::enable_if_t<std::is_base_of_v<StorageEngine, Engine>,
                                     int> = 0>
  IndexTypeFactory& factory();

 private:
  struct State {
    std::mutex mtx;
    std::condition_variable cv;
    size_t counter{0};
  };

  std::shared_ptr<State> _startState;
  std::shared_ptr<IResearchAsync> _async;
  std::atomic<bool> _running;
  uint32_t _consolidationThreads;
  uint32_t _consolidationThreadsIdle;
  uint32_t _commitThreads;
  uint32_t _commitThreadsIdle;
  uint32_t _threads;
  uint32_t _threadsLimit;
  std::map<std::type_index, std::shared_ptr<IndexTypeFactory>> _factories;
};

}  // namespace iresearch
}  // namespace arangodb
