# ----------------------------------------
# Greenspun tests
# ----------------------------------------

add_subdirectory(Greenspun)

# ----------------------------------------
# Fuerte tests
# ----------------------------------------

set(FUERTE_TESTS_SOURCES
  Fuerte/VstTest.cpp
  Fuerte/ConnectionBasicTest.cpp
  Fuerte/ConnectionConcurrentTest.cpp
  Fuerte/ConnectionFailuresTest.cpp
  Fuerte/ConnectionTimeoutsTest.cpp
#    test_10000_writes.cpp
)

add_executable(fuertetest
  ${FUERTE_TESTS_SOURCES}
  Fuerte/main.cpp
)

target_link_libraries(fuertetest
    fuerte
    gtest
    boost_boost
    arango
    arango_v8server
    arango_v8
    arangoserver
    ${MSVC_LIBS}
    ${OPENSSL_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
)

target_include_directories(fuertetest SYSTEM PRIVATE
  ${V8_INTERNAL_INCLUDE_DIR}
  ${INCLUDE_DIRECTORIES}
  ${CMAKE_SOURCE_DIR}/3rdParty/fakeit-gtest
  ${CMAKE_SOURCE_DIR}/3rdParty/rocksdb/third-party/gtest-1.8.1/fused-src
  ${CMAKE_SOURCE_DIR}/3rdParty/fuerte/src
)


# ----------------------------------------
# Link directories
# ----------------------------------------

foreach (LINK_DIR ${V8_LINK_DIRECTORIES})
  link_directories("${LINK_DIR}")
endforeach()

if (WINDOWS)
  set(RCFILE Maintenance/json.rc)
endif ()

set(ARANGODB_TESTS_COMMON_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/Mocks/IResearchLinkMock.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Mocks/IResearchInvertedIndexMock.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Mocks/LogLevels.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Mocks/PreparedResponseConnectionPool.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Mocks/StorageEngineMock.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Mocks/Servers.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Mocks/MockGraph.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Mocks/MockGraphProvider.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Basics/icu-helper.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/IResearch/AgencyMock.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/IResearch/common.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/IResearch/ExpressionContextMock.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/IResearch/RestHandlerMock.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Aql/VelocyPackHelper.cpp
)

add_subdirectory(IResearch)

set(ARANGODB_TESTS_SOURCES
  ${ARANGODB_TESTS_COMMON_SOURCES}
  Agency/ActiveFailoverTest.cpp
  Agency/AddFollowerTest.cpp
  Agency/CleanOutServerTest.cpp
  Agency/CleanUpLostCollectionTest.cpp
  Agency/FailedFollowerTest.cpp
  Agency/FailedLeaderTest.cpp
  Agency/FailedServerTest.cpp
  Agency/MoveShardTest.cpp
  Agency/NodeTest.cpp
  Agency/RemoveFollowerTest.cpp
  Agency/StoreTest.cpp
  Agency/StoreTestAPI.cpp
  Agency/SupervisionTest.cpp
  Agency/TransactionBuilderTests.cpp
  Aql/AqlCallListTest.cpp
  Aql/AqlExecutorTestCase.cpp
  Aql/AqlSharedExecutionBlockImplTest.cpp
  Aql/AqlHelper.cpp
  Aql/AqlItemBlockInputRangeTest.cpp
  Aql/AqlItemBlockTest.cpp
  Aql/AqlItemMatrixTest.cpp
  Aql/AqlItemRowPrinter.cpp
  Aql/AqlItemRowTest.cpp
  Aql/AqlShadowRowTest.cpp
  Aql/AqlValueMemoryLayoutTest.cpp
  Aql/AstResourcesTest.cpp
  Aql/AttributeNamePathTest.cpp
  Aql/BitFunctionsTest.cpp
  Aql/BlockCollector.cpp
  Aql/CalculationExecutorTest.cpp
  Aql/CountCollectExecutorTest.cpp
  Aql/DateFunctionsTest.cpp
  Aql/FixedOutputExecutionBlockMock.cpp
  Aql/InRangeFunctionTest.cpp
  Aql/MinHashFunctionsTest.cpp
  Aql/JaccardFunctionTest.cpp
  Aql/LevenshteinMatchFunctionTest.cpp
  Aql/DependencyProxyMock.cpp
  Aql/DistinctCollectExecutorTest.cpp
  Aql/EngineInfoContainerCoordinatorTest.cpp
  Aql/EnumerateCollectionExecutorTest.cpp
  Aql/EnumerateListExecutorTest.cpp
  Aql/ExecutionBlockImplTest.cpp
  Aql/ExecutionBlockImplTestInstances.cpp
  Aql/ExecutionNodeTest.cpp
  Aql/ExecutorTestHelper.cpp
  Aql/FilterExecutorTest.cpp
  Aql/GatherExecutorCommonTest.cpp
  Aql/HashedCollectExecutorTest.cpp
  Aql/IdExecutorTest.cpp
  Aql/IndexNodeTest.cpp
  Aql/InputRangeTest.cpp
  Aql/InsertExecutorTest.cpp
  Aql/EnumeratePathsExecutorTest.cpp
  Aql/EnumeratePathsNodeTest.cpp
  Aql/LimitExecutorTest.cpp
  Aql/MockTypedNode.cpp
  Aql/NgramMatchFunctionTest.cpp
  Aql/NgramSimilarityFunctionTest.cpp
  Aql/NgramPosSimilarityFunctionTest.cpp
  Aql/NodeWalkerTest.cpp
  Aql/NoResultsExecutorTest.cpp
  Aql/ProjectionsTest.cpp
  Aql/QueryCursorTest.cpp
  Aql/QueryHelper.cpp
  Aql/QueryLimitsTest.cpp
  Aql/RegisterPlanTest.cpp
  Aql/RemoteExecutorTest.cpp
  Aql/RemoveExecutorTest.cpp
  Aql/ReplaceExecutorTest.cpp
  Aql/ReturnExecutorTest.cpp
  Aql/RowFetcherHelper.cpp
  Aql/ScatterExecutorTest.cpp
  Aql/ShortestPathExecutorTest.cpp
  Aql/ShortestPathNodeTest.cpp
  Aql/SkipResultTest.cpp
  Aql/SortedCollectExecutorTest.cpp
  Aql/SortExecutorTest.cpp
  Aql/SortLimitTest.cpp
  Aql/SpliceSubqueryOptimizerRuleTest.cpp
  Aql/SplicedSubqueryIntegrationTest.cpp
  Aql/SubqueryEndExecutorTest.cpp
  Aql/SubqueryStartExecutorTest.cpp
  Aql/TestEmptyExecutorHelper.cpp
  Aql/TestLambdaExecutor.cpp
  Aql/TraversalNodeTest.cpp
  Aql/UpdateExecutorTest.cpp
  Aql/UpsertExecutorTest.cpp
  Aql/VelocyPackHelper.cpp
  Aql/WaitingExecutionBlockMock.cpp
  Aql/WindowExecutorTest.cpp
  Aql/DecaysFunctionTest.cpp
  Aql/DistanceFunctionTest.cpp
  AsyncAgencyComm/AsyncAgencyCommTest.cpp
  Auth/UserManagerTest.cpp
  Auth/UserManagerClusterTest.cpp
  Basics/ConversionsTest.cpp
  Basics/CsvTest.cpp
  Basics/datetime.cpp
  Basics/FilesTest.cpp
  Basics/FpConvTest.cpp
  Basics/HashesTest.cpp
  Basics/OverloadTest.cpp
  Basics/PriorityQueueTest.cpp
  Basics/StringBufferTest.cpp
  Basics/StringBufferInternalTest.cpp
  Basics/StringTest.cpp
  Basics/StringUtf8NormalizeTest.cpp
  Basics/StringUtf8Test.cpp
  Basics/ApplicationServerTest.cpp
  Basics/AttributeNameParserTest.cpp
  Basics/CpuUsageSnapshotTest.cpp
  Basics/EncodingUtilsTest.cpp
  Basics/EndpointTest.cpp
  Basics/FixedSizeAllocatorTest.cpp
  Basics/GuardedTest.cpp
  Basics/InspectionTest.cpp
  Basics/LoggerTest.cpp
  Basics/MemoryUsageTest.cpp
  Basics/NumberUtilsTest.cpp
  Basics/RandomTest.cpp
  Basics/ReadWriteLockTest.cpp
  Basics/RecursiveLockerTest.cpp
  Basics/SpinLockTest.cpp
  Basics/StringBufferTest.cpp
  Basics/StringUtilsTest.cpp
  Basics/UnshackledMutexTest.cpp
  Basics/VelocyPackHelperTest.cpp
  Cache/BucketState.cpp
  Cache/CachedValue.cpp
  Cache/FrequencyBuffer.cpp
  Cache/Manager.cpp
  Cache/Metadata.cpp
  Cache/MockScheduler.cpp
  Cache/PlainBucket.cpp
  Cache/PlainCache.cpp
  Cache/Rebalancer.cpp
  Cache/Table.cpp
  Cache/TransactionalBucket.cpp
  Cache/TransactionalCache.cpp
  Cache/TransactionalCacheVPackKeyHasher.cpp
  Cache/TransactionalStore.cpp
  Cache/TransactionManager.cpp
  Cache/TransactionsWithBackingStore.cpp
  Cluster/AgencyPathsTest.cpp
  Cluster/ClusterHelpersTest.cpp
  Cluster/ClusterInfoTest.cpp
  Cluster/RebootTrackerTest.cpp
  Cluster/QueryAnalyzerRevisionsTest.cpp
  Containers/EnumerateTest.cpp
  Containers/HashSetTest.cpp
  Containers/MerkleTreeTest.cpp
  Containers/SmallVectorTest.cpp
  Futures/FutureTest.cpp
  Futures/PromiseTest.cpp
  Futures/TryTest.cpp
  Geo/GeoConstructorTest.cpp
  Geo/GeoFunctionsTest.cpp
  Geo/GeoJsonTest.cpp
  Geo/NearUtilsTest.cpp
  Geo/ShapeContainerTest.cpp
  Greenspun/PrimitivesTest.cpp
  HotBackup/HotBackupCoordinatorTest.cpp
  Logger/EscaperTest.cpp
  Logger/LogContextTest.cpp
  ${ARANGODB_IRESEARCH_TESTS_SOURCES}
  Maintenance/MaintenanceFeatureTest.cpp
  Maintenance/MaintenanceRestHandlerTest.cpp
  Maintenance/MaintenanceTest.cpp
  ${RCFILE}
  Metrics/MetricsTest.cpp
  Metrics/MetricsFeatureTest.cpp
  Metrics/MetricsServerTest.cpp
  Network/ConnectionPoolTest.cpp
  Network/MethodsTest.cpp
  Network/UtilsTest.cpp
  Pregel/DurationTest.cpp
  Pregel/typedbuffer.cpp
  Pregel/StatusTest.cpp
  ProgramOptions/InifileParserTest.cpp
  ProgramOptions/ParametersTest.cpp
  Replication/ReplicationClientsProgressTrackerTest.cpp
  Rest/PathMatchTest.cpp
  RestHandler/RestAnalyzerHandlerTest.cpp
  RestHandler/RestDocumentHandlerTest.cpp
  RestHandler/RestUsersHandlerTest.cpp
  RestHandler/RestViewHandlerTest.cpp
  RestHandler/VstResponseTest.cpp
  RestServer/FlushFeatureTest.cpp
  RestServer/LanguageFeatureTest.cpp
  Restore/CollectionRestoreOrder.cpp
  RocksDBEngine/Endian.cpp
  RocksDBEngine/KeyTest.cpp
  RocksDBEngine/HotBackupTest.cpp
  RocksDBEngine/EncryptionProviderTest.cpp
  RocksDBEngine/IndexEstimatorTest.cpp
  RocksDBEngine/TransactionManagerTest.cpp
  Sharding/ShardDistributionReporterTest.cpp
  SimpleHttpClient/HttpResponseCheckerTest.cpp
  SimpleHttpClient/ConnectionCacheTest.cpp
  StorageEngine/PhysicalCollectionTest.cpp
  Transaction/ContextTest.cpp
  Transaction/CountCacheTest.cpp
  Transaction/ManagerTest.cpp
  Transaction/RestTransactionHandlerTest.cpp
  Utils/CollectionNameResolverTest.cpp
  Utils/NameValidatorTest.cpp
  Utils/QuickGen.cpp
  V8Server/V8AnalyzersTest.cpp
  V8Server/V8UsersTest.cpp
  V8Server/V8ViewsTest.cpp
  VocBase/VocbaseTest.cpp
  VocBase/KeyGeneratorTest.cpp
  VocBase/LogicalDataSourceTest.cpp
  VocBase/LogicalViewTest.cpp
  VocBase/VersionTest.cpp
  VPackDeserializer/BasicTests.cpp
  Zkd/Conversion.cpp
  Zkd/Library.cpp
  ${ADDITIONAL_TEST_SOURCES} Cluster/ShardAutoRebalancerTest.cpp)

set(ARANGODB_REPLICATION2_TEST_SOURCES
  Replication2/Helper/ModelChecker/Actors.cpp
  Replication2/Helper/ModelChecker/AgencyTransition.cpp
  Replication2/Helper/WaitForQueue.cpp
  Replication2/Mocks/AsyncFollower.cpp
  Replication2/Mocks/AsyncFollower.h
  Replication2/Mocks/AsyncLeader.cpp
  Replication2/Mocks/FakeAbstractFollower.h
  Replication2/Mocks/FakeFailureOracle.cpp
  Replication2/Mocks/FakeFailureOracle.h
  Replication2/Mocks/FakeFollower.cpp
  Replication2/Mocks/FakeFollower.h
  Replication2/Mocks/FakeLeader.cpp Replication2/Mocks/FakeLeader.h
  Replication2/Mocks/FakeReplicatedLog.cpp
  Replication2/Mocks/FakeReplicatedLog.h
  Replication2/Mocks/FakeReplicatedState.cpp
  Replication2/Mocks/PersistedLog.cpp
  Replication2/Mocks/PersistedLog.cpp
  Replication2/Mocks/PersistedLog.h
  Replication2/Mocks/PersistedLog.h
  Replication2/Mocks/ReplicatedLogMetricsMock.cpp
  Replication2/Mocks/ReplicatedStateMetricsMock.cpp
  Replication2/ModelChecker/ModelChecker.cpp
  Replication2/ModelChecker/Tests/ModelCheckerTest.cpp
  Replication2/ReplicatedLog/AppendEntriesBatchTest.cpp
  Replication2/ReplicatedLog/AppendEntriesErrorReasonTest.cpp
  Replication2/ReplicatedLog/CalcCommitIndexTest.cpp
  Replication2/ReplicatedLog/ChangeStreamTests.cpp
  Replication2/ReplicatedLog/CheckLogsTest.cpp
  Replication2/ReplicatedLog/ConcurrencyTests.cpp
  Replication2/ReplicatedLog/DetectConflictTest.cpp
  Replication2/ReplicatedLog/EstablishLeadershipTest.cpp
  Replication2/ReplicatedLog/FollowerAppendEntries.cpp
  Replication2/ReplicatedLog/FollowerWaitFor.cpp
  Replication2/ReplicatedLog/InMemoryLogTest.cpp
  Replication2/ReplicatedLog/LeaderAppendEntriesTest.cpp
  Replication2/ReplicatedLog/LogFollowerCompactionTest.cpp
  Replication2/ReplicatedLog/LogParticipantWaitForResignTests.cpp
  Replication2/ReplicatedLog/LogReclaimTest.cpp
  Replication2/ReplicatedLog/LogStatusTest.cpp
  Replication2/ReplicatedLog/MaintenanceTests.cpp
  Replication2/ReplicatedLog/MultiTermTest.cpp
  Replication2/ReplicatedLog/ParticipantResignTest.cpp
  Replication2/ReplicatedLog/ParticipantsHealthTest.cpp
  Replication2/ReplicatedLog/ReplicatedLogTest.cpp
  Replication2/ReplicatedLog/RewriteLogTest.cpp
  Replication2/ReplicatedLog/RocksDBLogTest.cpp
  Replication2/ReplicatedLog/SimpleInsertTests.cpp
  Replication2/ReplicatedLog/SupervisionTest.cpp
  Replication2/ReplicatedLog/SupervisionSimulationTest.cpp
  Replication2/ReplicatedLog/TestHelper.cpp
  Replication2/ReplicatedLog/UpdateParticipantsFlags.cpp
  Replication2/ReplicatedLog/UpdateReplicatedLogTests.cpp
  Replication2/ReplicatedLog/WaitForSyncTest.cpp
  Replication2/ReplicatedState/FollowerSnapshotTest.cpp
  Replication2/ReplicatedState/FollowerWaitForTest.cpp
  Replication2/ReplicatedState/LeaderRecoveryTest.cpp
  Replication2/ReplicatedState/LeaderResignTest.cpp
  Replication2/ReplicatedState/MaintenanceTest.cpp
  Replication2/ReplicatedState/DocumentStateMachineTest.cpp
  Replication2/ReplicatedState/PrototypeConcurrencyTest.cpp
  Replication2/ReplicatedState/PrototypeStateMachineTest.cpp
  Replication2/ReplicatedState/ReplicatedStateFeatureTest.cpp
  Replication2/ReplicatedState/ReplicatedStateTest.cpp
  Replication2/ReplicatedState/StateMachines/MyStateMachine.cpp
  Replication2/ReplicatedState/SupervisionModelChecker.cpp
  Replication2/ReplicatedState/SupervisionTest.cpp
  Replication2/Serialization/AgencyLogSpecificationTest.cpp
  Replication2/Serialization/LogCommonTest.cpp
  Replication2/Serialization/LogStatusTest.cpp
  Replication2/Streams/LogMultiplexerTest.cpp
  Replication2/Streams/MultiplexerConcurrencyTest.cpp
  Replication2/Streams/TestLogSpecification.cpp
  Replication2/Streams/TestLogSpecification.h
  Replication2/ReplicatedState/ReplicatedStateMetricsTest.cpp
  Replication2/ReplicatedLog/MetricsTest.cpp
  Replication2/ReplicatedState/FollowerResignTest.cpp
)

set(ARANGODB_GRAPH_TEST_SOURCES
  Graph/ClusterTraverserCacheTest.cpp
  Graph/TraverserCacheTest.cpp
  Graph/ConstantWeightShortestPathFinder.cpp
  Graph/GenericGraphProviderTest.cpp
  Graph/GraphMockProviderInstances.cpp
  Graph/GraphTestTools.cpp
  Graph/KPathFinderTest.cpp
  Graph/AllShortestPathsFinderTest.cpp
  Graph/DFSFinderTest.cpp
  Graph/KShortestPathsFinder.cpp
  Graph/PathStoreTest.cpp
  Graph/PathValidatorTest.cpp
  Graph/FifoQueueTest.cpp
  Graph/LifoQueueTest.cpp
  Graph/WeightedQueueTest.cpp
  Graph/SingleServerProviderTest.cpp
  ${ADDITIONAL_GRAPH_TEST_SOURCES}
)


if (LINUX)
  # add "-fno-var-tracking" to the compiler flags
  # this speeds up the compilation with optimizations and newer g++ versions
  # and prevents the "variable tracking size limit exceeded warnings" from
  # occurring
  if (CMAKE_COMPILER_IS_GNUCC)
    # also turn off super-expensive global common subexpression elimination for tests
    set_source_files_properties(${ARANGODB_TESTS_SOURCES} PROPERTIES COMPILE_FLAGS "-fno-var-tracking -fno-gcse")
  else ()
    set_source_files_properties(${ARANGODB_TESTS_SOURCES} PROPERTIES COMPILE_FLAGS -fno-var-tracking)
  endif ()
endif ()

add_executable(
  arangodbtests
  ../cmake/activeCodePage.manifest
  ${ARANGODB_TESTS_SOURCES}
  ${ARANGODB_REPLICATION2_TEST_SOURCES}
  ${ARANGODB_GRAPH_TEST_SOURCES}
  main.cpp
)

set(USE_SEPARATE_REPLICATION2_TESTS_BINARY FALSE CACHE BOOL
  "Write a separate binary 'arangodbtests_replication2', containing only the Replication 2.0 tests.")

if (USE_SEPARATE_REPLICATION2_TESTS_BINARY)
  add_executable(
    arangodbtests_replication2
    ${ARANGODB_TESTS_COMMON_SOURCES}
    ${ARANGODB_REPLICATION2_TEST_SOURCES}
    main.cpp
  )
endif()

set(USE_SEPARATE_GRAPH_TESTS_BINARY FALSE CACHE BOOL
        "Write a separate binary 'arangodbtests_graph', containing only the graph tests.")

if (USE_SEPARATE_GRAPH_TESTS_BINARY)
  add_executable(
          arangodbtests_graph
          ${ARANGODB_TESTS_COMMON_SOURCES}
          ${ARANGODB_GRAPH_TEST_SOURCES}
          main.cpp
  )
endif()


#required by fakeit dtor mock -- https://github.com/eranpeer/FakeIt/issues/84
if(CMAKE_CXX_COMPILER_ID STREQUAL GNU)
  target_compile_options(arangodbtests PRIVATE -fno-devirtualize)
endif()

target_link_libraries(arangodbtests
  arango_agency
  arango_cluster_engine
  arango_rocksdb
  arango_v8server
  arangoserver
  arango_restore
  fuerte
  rocksdb
  snappy
  gtest
  boost_boost
  fmt
)


if (USE_SEPARATE_REPLICATION2_TESTS_BINARY)
  target_link_libraries(arangodbtests_replication2
    gtest
    arango_agency
    arango_v8server
    arangoserver
    arango_replication2
    arango_iresearch
    fmt
  )
endif()

if (USE_SEPARATE_GRAPH_TESTS_BINARY)
  target_link_libraries(arangodbtests_graph
          gtest
          arango_agency
          arango_v8server
          arangoserver
          arango_replication2
          arango_iresearch
          )
endif()

if (USE_ENTERPRISE)
  target_link_libraries(arangodbtests arango_rclone)
endif ()

target_include_directories(arangodbtests PRIVATE
  ${PROJECT_SOURCE_DIR}/arangod
  ${PROJECT_SOURCE_DIR}/${ENTERPRISE_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/Mocks/
)

if (USE_SEPARATE_REPLICATION2_TESTS_BINARY)
  target_include_directories(arangodbtests_replication2 PRIVATE
    ${PROJECT_SOURCE_DIR}/arangod
    ${PROJECT_SOURCE_DIR}/${ENTERPRISE_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Mocks/
  )
  target_link_libraries(arangodbtests_replication2 arango)
endif()

if (USE_SEPARATE_GRAPH_TESTS_BINARY)
  target_include_directories(arangodbtests_graph PRIVATE
          ${PROJECT_SOURCE_DIR}/arangod
          ${PROJECT_SOURCE_DIR}/${ENTERPRISE_INCLUDE_DIR}
          ${CMAKE_CURRENT_SOURCE_DIR}
          ${CMAKE_CURRENT_SOURCE_DIR}/Mocks/
          )
  target_link_libraries(arangodbtests_graph arango)
endif()

if(MSVC AND USE_FAIL_ON_WARNINGS)
  target_compile_options(arangodbtests PRIVATE /WX /D_WINSOCK_DEPRECATED_NO_WARNINGS)
  if (USE_SEPARATE_REPLICATION2_TESTS_BINARY)
    target_compile_options(arangodbtests_replication2 PRIVATE /WX /D_WINSOCK_DEPRECATED_NO_WARNINGS)
  endif()
  if (USE_SEPARATE_GRAPH_TESTS_BINARY)
    target_compile_options(arangodbtests_graph PRIVATE /WX /D_WINSOCK_DEPRECATED_NO_WARNINGS)
  endif()
  if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang") # clang-cl.exe
    # There's a warning about /MP being unused if compiling only a single file
    target_compile_options(arangodbtests PRIVATE -Wno-unused-command-line-argument)
    if (USE_SEPARATE_REPLICATION2_TESTS_BINARY)
      target_compile_options(arangodbtests_replication2 PRIVATE /WX /D_WINSOCK_DEPRECATED_NO_WARNINGS)
    endif()
    if (USE_SEPARATE_GRAPH_TESTS_BINARY)
      target_compile_options(arangodbtests_graph PRIVATE /WX /D_WINSOCK_DEPRECATED_NO_WARNINGS)
    endif()
  endif()
endif()

if (DARWIN AND USE_FAIL_ON_WARNINGS)
  # Missing Braces is broken in older CLangs - disable them here.
  target_compile_options(arangodbtests PRIVATE -Werror -Wno-error=deprecated-declarations -Wno-missing-braces)
  if (USE_SEPARATE_REPLICATION2_TESTS_BINARY)
    target_compile_options(arangodbtests_replication2 PRIVATE -Werror -Wno-error=deprecated-declarations -Wno-missing-braces)
  endif()
  if (USE_SEPARATE_GRAPH_TESTS_BINARY)
    target_compile_options(arangodbtests_graph PRIVATE -Werror -Wno-error=deprecated-declarations -Wno-missing-braces)
  endif()
endif()

# add these includes as system includes because otherwise
# the compiler will emit warnings for fakeit.hpp
target_include_directories(arangodbtests SYSTEM PRIVATE
  ${V8_INTERNAL_INCLUDE_DIR}
  ${CMAKE_SOURCE_DIR}/3rdParty/fakeit-gtest
  ${CMAKE_SOURCE_DIR}/3rdParty/rocksdb/third-party/gtest-1.8.1/fused-src
)

target_link_libraries(arangodbtests v8_interface)

if (USE_SEPARATE_REPLICATION2_TESTS_BINARY)
  target_include_directories(arangodbtests_replication2 SYSTEM PRIVATE
    ${CMAKE_SOURCE_DIR}/3rdParty/rocksdb/third-party/gtest-1.8.1/fused-src
  )
endif()

if (USE_SEPARATE_GRAPH_TESTS_BINARY)
  target_include_directories(arangodbtests_graph SYSTEM PRIVATE
          ${CMAKE_SOURCE_DIR}/3rdParty/rocksdb/${ARANGO_ROCKSDB_VERSION}/third-party/gtest-1.8.1/fused-src
          )
endif()

if (USE_JEMALLOC)
  add_dependencies(arangodbtests jemalloc_build)
endif ()

find_package(OpenSSL REQUIRED)
list(APPEND IRESEARCH_LIB_RESOURCES
  "${LIB_EAY_DEBUG_DLL}"
  "${SSL_EAY_DEBUG_DLL}"
  "${LIB_EAY_RELEASE_DLL}"
  "${SSL_EAY_RELEASE_DLL}"
)

foreach(ELEMENT ${IRESEARCH_LIB_RESOURCES})
  if (ELEMENT)
    add_custom_command(
      TARGET arangodbtests POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E echo "copying library resource:" "${ELEMENT}" " -> " "$<TARGET_FILE_DIR:arangodbtests>"
      COMMAND cp -lf ${ELEMENT} $<TARGET_FILE_DIR:arangodbtests> || ${CMAKE_COMMAND} -E copy ${ELEMENT} $<TARGET_FILE_DIR:arangodbtests>
    )
  endif()
endforeach()
