add_executable(fufu-ui
	main.cpp
)

#[[
# Specify path to own LVGL config header
set(LV_CONF_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lv_conf.h
    CACHE STRING "" FORCE)
]]


# Fetch LVGL from GitHub
include(FetchContent)
FetchContent_Declare(lvgl GIT_REPOSITORY https://github.com/lvgl/lvgl.git)
FetchContent_MakeAvailable(lvgl)

target_compile_definitions(fufu-ui PRIVATE
	DVI_DEFAULT_SERIAL_CONFIG=${DVI_DEFAULT_SERIAL_CONFIG}
	)

target_link_libraries(fufu-ui
	pico_stdlib
	pico_multicore
	pico_util
	hardware_gpio
	hardware_pwm
	libdvi
	libsprite
	#lvgl::lvgl
)

# create map/bin/hex file etc.
pico_add_extra_outputs(fufu-ui)