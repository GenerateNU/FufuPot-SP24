add_executable(fufu-ui
	main.c
)

target_compile_options(fufu-ui PRIVATE -Wall)

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
)

# create map/bin/hex file etc.
pico_add_extra_outputs(fufu-ui)