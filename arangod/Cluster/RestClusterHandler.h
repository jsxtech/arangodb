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
/// @author Simon Grätzer
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "RestHandler/RestBaseHandler.h"

namespace arangodb {
class RestClusterHandler : public arangodb::RestBaseHandler {
 public:
  RestClusterHandler(ArangodServer&, GeneralRequest*, GeneralResponse*);

 public:
  virtual char const* name() const override { return "RestClusterHandler"; }
  RequestLane lane() const override final { return RequestLane::CLIENT_FAST; }
  RestStatus execute() override;

 private:
  /// _api/cluster/endpoints
  void handleCommandEndpoints();

  /// _api/cluster/agency-dump
  void handleAgencyDump();

  /// _api/cluster/agency-cache
  void handleAgencyCache();

  /// _api/cluster/cluster-info
  void handleClusterInfo();
};
}  // namespace arangodb
