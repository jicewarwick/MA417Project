find_package(Boost REQUIRED COMPONENTS random )

include_directories(${Boost_INCLUDE_IDR})

add_library(dataExport SHARED dataExport )
#add_library(Model SHARED Model)
add_library(HestonModel SHARED HestonModel Model)
add_library(NormalRandomNumberGenerator SHARED NormalRandomNumberGenerator ${Boost_random_library} )
add_library(MonteCarloSimulation SHARED MonteCarloSimulation)
add_library(Options SHARED Options)
add_library(f SHARED f ${GSL_LINK_DIRECTORIES})
