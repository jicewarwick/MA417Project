find_package(Boost REQUIRED COMPONENTS random )

include_directories(${Boost_INCLUDE_IDR})

add_library(dataExport SHARED dataExport )
add_library(HestonModel SHARED HestonModel )
add_library(NormalRandomNumberGenerator SHARED NormalRandomNumberGenerator ${Boost_random_library} )


